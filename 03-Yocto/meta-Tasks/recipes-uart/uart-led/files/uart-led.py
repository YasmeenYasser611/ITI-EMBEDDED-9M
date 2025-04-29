import serial
import time

serial_port = '/dev/serial0'
baud_rate = 9600

def open_serial():
    return serial.Serial(serial_port, baud_rate, timeout=1)

while True:
    try:
        ser = open_serial()
        print(f"Opened serial port {serial_port}")
        while True:
            char = ser.read(1).decode('utf-8', errors='ignore')
            if char:
                print(f"Received character: {char}")
                if char in ['0', '1']:
                    with open('/dev/gpio-led0', 'w') as led_file:
                        led_file.write(char)
                        print(f"Wrote {char} to /dev/gpio-led0")
    except serial.SerialException as e:
        print(f"Serial error: {e}")
        print("Attempting to reopen the serial port in 2 seconds...")
        time.sleep(2)
    except Exception as e:
        print(f"Unexpected error: {e}")
    finally:
        try:
            ser.close()
        except:
            pass
