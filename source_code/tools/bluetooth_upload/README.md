==Bluetooth upload
Bluetooth upload is a Python 3 class to upload compile hex files of the SmartWatchs firmware using a Bluetooth 4.0 USB Dongle on Linux.
The following packages are required:
  - bluez 5
  - pygattlib (https://bitbucket.org/OscarAcena/pygattlib/overview)
  - Python3

===Preparation
To upload code to the SmartWatch, the SmartWatch has to be paired with the computer. Use the following instructions on the command line:
robin@t520-debian:~$ bluetoothctl
```
[NEW] Controller 00:1A:7D:DA:71:13 t520-debian [default]
[bluetooth]# agent on
Agent registered
[bluetooth]# default-agent
Default agent request successful
[bluetooth]# scan on
Discovery started
[CHG] Controller 00:1A:7D:DA:71:13 Discovering: yes
[NEW] Device 54:4A:16:25:82:12 HMSoft
[CHG] Device 54:4A:16:25:82:12 RSSI: -70
[CHG] Device 54:4A:16:25:82:12 RSSI: -61
[bluetooth]# scan off
[CHG] Device 54:4A:16:25:82:12 RSSI is nil
Discovery stopped
[CHG] Controller 00:1A:7D:DA:71:13 Discovering: no
[bluetooth]# connect 54:4A:16:25:82:12
Attempting to connect to 54:4A:16:25:82:12
[CHG] Device 54:4A:16:25:82:12 Connected: yes
Connection successful
[CHG] Device 54:4A:16:25:82:12 UUIDs:
    00001800-0000-1000-8000-00805f9b34fb
    00001801-0000-1000-8000-00805f9b34fb
    0000ffe0-0000-1000-8000-00805f9b34fb
[bluetooth]# pair 54:4A:16:25:82:12
Attempting to pair with 54:4A:16:25:82:12
[CHG] Device 54:4A:16:25:82:12 Paired: yes
Pairing successful
[bluetooth]# disconnect 54:4A:16:25:82:12
Attempting to disconnect from 54:4A:16:25:82:12
[bluetooth]# quit
Agent unregistered
[DEL] Controller 00:1A:7D:DA:71:13 t520-debian [default]
```

==Upload code
To upload code to the SmartWatch you have to call
python3 upload.py <firmware.hex>
<firmware.hex> represents the path to the firmware and is required.

After starting the upload tool, it will search for Bluetooth 4.0 devices. If only one device is found with the name SmartWatch*, the code is automatically uploaded there. Otherwise you have to select a device from the appearing list.

The upload tool will automatically disconnect to allow the SmartWatchs bluetooth module to configure for the update progress. After that the OLED will ask you to reconnect. Reconnect by pressing any key on the command line.
The upload will start now. Please wait until update ist completed. Otherwise the firmware could get corrupted and a reupload using an ISP programmer could become required.
After flashing, the tool will automatically disconnect and exit to allow the SmartWatchs bluetooth module to reconfigure. 
