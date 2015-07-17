from gattlib import DiscoveryService, GATTRequester, GATTResponse
from time import sleep
from threading import Event
import sys

def startProgress(title):
    global progress_x
    sys.stdout.write(title + ": [" + "-"*40 + "]" + chr(8)*41)
    sys.stdout.flush()
    progress_x = 0

def progress(x):
    global progress_x
    x = int(x * 40 // 100)
    sys.stdout.write("#" * (x - progress_x))
    sys.stdout.flush()
    progress_x = x

def endProgress():
    sys.stdout.write("#" * (40 - progress_x) + "]\n")
    sys.stdout.flush()

class Requester(GATTRequester):
    def __init__(self, wakeup, update, *args):
        GATTRequester.__init__(self, *args)
        self.wakeup = wakeup
        self.update = update

    def set_requester(self, requester):
        self.requester = requester

    def on_notification(self, handle, data):
        data = data[3:]
        if (data.find("UPDATEWAIT") != -1):
            self.update.update_progres = 1
        if (data.find("KAVR") != -1):
            self.update.update_progres = 2
        self.wakeup.set()

class update():
    def __init__(self):
        self.address = None
        self.requester = None
        self.received = Event()
        self.update_progres = None

    def status(self):
        if self.requester.is_connected():
            print("Connected")
            return True
        else:
            print("Disconnected")
            return False

    def connect(self):
        while 1: #Until device was found
            print("Scanning for SmartWatches")
            service = DiscoveryService("hci0")

            count = 0
            addresses = {}
            names = {}
            while (count==0):
                devices = service.discover(2)
                for address, name in devices.items():
                    count+=1
                    addresses[count] = address
                    names[count] = name
                    print("  [{}] {} - {}".format(count, name, address))
            print ("Scan finished")

            if (count==1 and names[1].find("SmartWatch")==0):
                print ("Autoconnect to {}".format(names[1]))
                self.address = addresses[1]
                break

            address = int(input("\nEnter address index: "))
            if (address>count or address<1):
                print("Error: Selected address does not exist\n")
            else:
                self.address = addresses[address]
                break
        print("Connecting...")
        self.requester = Requester(self.received, self, self.address)
        n = 0
        while self.requester.is_connected()!=1:
            sleep(0.5)
            n+=1
            if (n>6):
                print("Connection failed")
                return False
        return self.status()

    def update(self, filename):
        print("\nInitializing update")
        self.requester.write_by_handle(0x12, "UPDATE")
        print("Waiting for SmartWatch")
        while self.update_progres != 1:
            sleep(0.5)
        self.disconnect()
        input("Press key to reconnect")
        print("Connecting...")
        self.requester = Requester(self.received, self, self.address)
        n = 0
        while self.requester.is_connected()!=1:
            sleep(0.5)
            n+=1
            if (n>6):
                print("Connection failed")
                return 0
        print("Waiting for SmartWatch")
        while self.update_progres != 2:
            sleep(0.5)
        print("Flashing update")
        startProgress("Flashing")
        with open(filename) as f:
            lines = sum(1 for _ in f)
            count = 0
        with open(filename) as f:
            for line in f:
                count += 1
                self.requester.write_by_handle(0x12, line)
                progress(100/lines*count)
            endProgress()
        print("Update finished")
        self.disconnect()

    def disconnect(self):
        print("Disconnecting...")
        self.requester.disconnect()
        self.status()

print("\nSmartWatch Bluetooth Flashing Tool V1.0.0\n")
try:
    sys.argv[1]
except:
    print ("Please specify a file to upload")
else:
    do_update = update()
    if do_update.connect():
        do_update.update(sys.argv[1])
