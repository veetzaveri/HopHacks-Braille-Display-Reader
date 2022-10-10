import time
import serial

print(1)
s = serial.Serial('/dev/cu.usbmodem11301', 38400)
s2 = serial.Serial('/dev/cu.usbserial-AL02AZNH', 38400)
print(2)
time.sleep(1)
i = 0

threshold = 15

prevAx1 = 0
prevAx2 = 0

timeInterval1 = 0
timeInterval2 = 0

displacement = 0

initial_calibration = s.readline().decode().rstrip().split(",")
initialAx = float(initial_calibration[1])
initialAy = float(initial_calibration[2])


print("Initial: ", initialAx, initialAy)

prevData1 = s.readline().decode().rstrip().split(",")
prevAx1 = float(prevData1[1]) - initialAx
prevAy1 = float(prevData1[2]) - initialAy

print("Data1: ", prevAx1, prevAy1)

prevData2 = s.readline().decode().rstrip().split(",")
prevAx2 = float(prevData2[1]) - initialAx
prevAy2 = float(prevData2[2]) - initialAy


print("Data2: ", prevAx2, prevAy2)

timeInterval1 = int(prevData2[0]) - int(prevData1[0])

prevDisplacement1 = 0
prevDisplacement2 = 0

flagx = True
flagy = True
timeInitiatedX = 0
timeInitiatedY = 0
with open('data.csv', 'w', newline='\n') as csvfile:
    print("Starting")
    while i < 100000:
        currData = s.readline().decode().rstrip().split(",")

        currAx = float(currData[1]) - initialAx
        currAy = float(currData[2]) - initialAy
        # print(currAx, currAy)
        i += 1

        if ((currAx > threshold or currAx < threshold*-1) and not flagx):
            flagx = True
            timeInitiatedX = time.perf_counter()
            if (currAx > threshold):
                print("Up")
                s2.write("u".encode())
            else:
                print("Down")
                s2.write("d".encode())

        if ((currAy > threshold or currAy < threshold*-1) and not flagy):
            flagy = True
            timeInitiatedY = time.perf_counter()
            if (currAy > threshold):
                print("Left")
                s2.write("l".encode())
            else:
                print("Right")
                s2.write("r".encode())

        if flagx == True:
            if (time.perf_counter() - timeInitiatedX > 0.75):
                flagx = False

        if flagy == True:
            if (time.perf_counter() - timeInitiatedY > 0.75):
                flagy = False
