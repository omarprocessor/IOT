import network
import socket
from machine import Pin

# Set ESP32 as an Access Point (AP)
SSID = "Smart_Parking"
PASSWORD = "12345678"  # Set your own password

ap = network.WLAN(network.AP_IF)
ap.active(True)
ap.config(essid=SSID, password=PASSWORD, authmode=network.AUTH_WPA_WPA2_PSK)

print("ESP32 Access Point Started")
print(f"Connect to WiFi: {SSID}, IP: {ap.ifconfig()[0]}")

# Define a single IR sensor on pin 2
ir_sensor = Pin(2, Pin.IN)

# Function to get parking status
def get_parking_status():
    return "Occupied" if ir_sensor.value() == 0 else "Available"

# Function to generate HTML page
def generate_webpage():
    status = get_parking_status()
    color_class = "occupied" if status == "Occupied" else "available"
    
    html = """<!DOCTYPE html>
    <html>
    <head>
        <title>ESP32 Parking System</title>
        <meta http-equiv="refresh" content="3">  <!-- Refresh every 3 seconds -->
        <style>
            body { font-family: Arial, sans-serif; text-align: center; background-color: #f0f0f0; margin: 0; padding: 0; }
            h1 { color: #333; padding: 20px; }
            .slot { width: 200px; height: 150px; display: flex; align-items: center; justify-content: center;
                    border-radius: 10px; font-size: 24px; font-weight: bold; color: white; }
            .occupied { background-color: red; }
            .available { background-color: green; }
        </style>
    </head>
    <body>
        <h1>ESP32 Parking System</h1>
        <div class="container">
            <div class="slot {}">Slot 1<br>{}</div>
        </div>
    </body>
    </html>
    """.format(color_class, status)

    return html

# Start Web Server
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('', 80))
server_socket.listen(5)

print("Web server running on 192.168.4.1...")

while True:
    try:
        client, addr = server_socket.accept()
        print(f"Connection from {addr}")
        request = client.recv(1024)

        # Send HTTP response
        response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + generate_webpage()
        client.send(response.encode())
        client.close()
    except Exception as e:
        print("Error:", e)
        client.close()
