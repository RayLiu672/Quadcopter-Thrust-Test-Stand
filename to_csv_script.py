import serial
import time
import csv

delay = 10
selection = False
arduino = serial.Serial(port='COM3', baudrate=115200, timeout=.1)
script_to_csv = open('F:\Script_to_csv.txt', 'w')
csv_writer = csv.writer(script_to_csv)

# select which data will be converted to csv
while not selection:
    data_type = input("Enter Data Type: ")
    if data_type.lower() in ['rpm']:
        script_to_csv.write("rpm, time(msec)\n")
        selection = True
        
    elif data_type.lower() in ['force']:
        selection = True
# delay to avoid buffer overflow
time.sleep(delay)

while selection:
    for i in range(100):    
        # read a byte string
        b = arduino.readline()     
        # decode byte string into Unicode  
        string_n = b.decode()         
        print(string_n)
        # Getting rid of empty lines
        script_to_csv.write(string_n.replace("\n", ""))
    script_to_csv.close()

