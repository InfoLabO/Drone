'''
Created on 2011-12-02

@author: Bobby Wood
'''

## import the serial library
import serial

## Boolean variable that will represent 
## whether or not the arduino is connected
connected = False

## open the serial port that your ardiono 
## is connected to.
ser = serial.Serial("/dev/ttyACM0", 9600)

## loop until the arduino tells us it is ready
while not connected:
    serin = ser.read()
    connected = True

## Tell the arduino to blink!
ser.write(b"1")

"""
## Wait until the arduino tells us it 
## is finished blinking
while ser.read() == '1':
    ser.read()
"""
while True:
    s = ser.readline()
    #print(s.decode())
    if(s.decode()[:5] =="ACCEL"):
        i=s.decode().find("X")
        x=float(s.decode()[i+2:i+2+4].replace(" ",""))
        if(x<2 and x >-2):
            print("|")
        elif(x>2):
            print("/")
        else:
            print("\ ")        
        print("i : ",i)

## close the port and end the program
ser.close()
