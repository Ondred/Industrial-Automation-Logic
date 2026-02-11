import serial
import time
import csv

# Configuration: Update 'COM3' to your actual port (e.g., '/dev/ttyUSB0' on Linux)
SERIAL_PORT = 'COM3' 
BAUD_RATE = 9600

def run_monitor():
    print(f"--- Starting Industrial Monitor on {SERIAL_PORT} ---")
    
    try:
        # Initialize Serial Connection
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        time.sleep(2) # Buffer for connection stability
        
        # Create/Open a CSV file to log the data
        with open("sensor_log.csv", "a", newline="") as file:
            writer = csv.writer(file)
            
            while True:
                if ser.in_waiting > 0:
                    # Read the raw data from Arduino
                    line = ser.readline().decode('utf-8').strip()
                    
                    if line:
                        timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                        print(f"[{timestamp}] {line}")
                        
                        # Log to CSV for "Historical Data Analysis"
                        writer.writerow([timestamp, line])
                        file.flush() # Ensure data is written immediately

    except serial.SerialException:
        print("Error: Could not open Serial Port. Check connection.")
    except KeyboardInterrupt:
        print("\nMonitor stopped by user.")

if __name__ == "__main__":
    run_monitor()
