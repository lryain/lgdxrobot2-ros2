#!/bin/bash

echo "remap the device serial port(ttyUSBX) to  rplidar"
echo "rplidar usb connection as /dev/rplidar , check it using the command : ls -l /dev|grep ttyUSB"
echo "start copy lgdxrobot2.rules to  /etc/udev/rules.d/"
sudo cp scripts/lgdxrobot2.rules  /etc/udev/rules.d
echo " "
echo "Restarting udev"
echo ""
# sudo service udev reload
# sudo service udev restart
sudo udevadm control --reload-rules
sudo udevadm trigger

ls -l /dev/rplidar
ls -l /dev/lgdxrobot2
echo "finish "
