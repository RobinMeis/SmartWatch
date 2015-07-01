#! /usr/bin/env python3
import serial
import binascii

if __name__=='__main__':
    try:
        ser = serial.Serial("/dev/ttyUSB1", 9600, timeout=1, xonxoff=True)
        print("connected to: " + ser.portstr)
    except serial.SerialException:
        pass
    s = ""

    with open('file.hex') as f:
        for line in f:
            print(line)
            ser.write(line.encode())
            line = ser.read()
            if line:  # If it isn't a blank line
                print(line)

    # with open("file.hex") as f:
    #     while True:
    #         c = f.read(1)
    #         if not c:
    #             print ("End of file")
    #         break
    #         print ("Read a character:", c)
    #
    #         # Read a line and convert it from b'xxx\r\n' to xxx
    #         line = ser.read()
    #         if line:  # If it isn't a blank line
    #             print(line)
    ser.close()
