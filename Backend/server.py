from flask import Flask, request, jsonify
import math

app = Flask(__name__)

# --- CONFIGURATION ---
# Fixed Location of your Traffic Light (Set this to your college/demo location)
# Example: St. Vincent Pallotti College coordinates
TRAFFIC_LIGHT_LAT = 21.096076 
TRAFFIC_LIGHT_LNG = 79.054276 
TRIGGER_DISTANCE = 300.0  # Meters (Green Corridor Radius)

# Global variable to store latest command for the Traffic Light
current_command = {
    "priority_distance": 9999.0,
    "target_signal": "NONE",
    "override": False
}

def haversine(lat1, lon1, lat2, lon2):
    R = 6371000 # Radius of Earth in meters
    phi1 = math.radians(lat1)
    phi2 = math.radians(lat2)
    delta_phi = math.radians(lat2 - lat1)
    delta_lambda = math.radians(lon2 - lon1)
    a = math.sin(delta_phi/2)**2 + math.cos(phi1)*math.cos(phi2) * math.sin(delta_lambda/2)**2
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
    return R * c

# --- API FOR AMBULANCE ---
@app.route('/update-gps', methods=['POST'])
def update_gps():
    global current_command
    data = request.json
    lat = data.get('latitude')
    lng = data.get('longitude')
    
    if lat is None or lng is None:
        return jsonify({"status": "error", "message": "Invalid GPS data"}), 400
    
    # Calculate Distance
    dist = haversine(lat, lng, TRAFFIC_LIGHT_LAT, TRAFFIC_LIGHT_LNG)
    print(f"Ambulance is {dist:.2f} meters away.")

    # Logic: If closer than 300m, trigger Green Light
    if dist < TRIGGER_DISTANCE:
        current_command["priority_distance"] = dist
        current_command["target_signal"] = "Signal 1 (N)" # Defaulting to North Lane for demo
        current_command["override"] = True
    else:
        current_command["override"] = False
    
    return jsonify({"status": "success", "distance": dist})

# --- API FOR TRAFFIC LIGHT ---
@app.route('/get-status', methods=['GET'])
def get_status():
    return jsonify(current_command)

if __name__ == '__main__':
    # Run server on all interfaces (0.0.0.0) so ESP32 can connect
    app.run(host='0.0.0.0', port=5000, debug=True)
