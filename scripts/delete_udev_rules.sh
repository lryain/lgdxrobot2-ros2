#!/bin/bash

echo "delete remap the device serial port(ttyUSBX) to  rplidar"
echo "sudo rm   /etc/udev/rules.d/lgdxrobot2.rules"
sudo rm   /etc/udev/rules.d/lgdxrobot2.rules
echo " "
echo "Restarting udev"
echo ""
# sudo service udev reload
# sudo service udev restart
sudo udevadm control --reload-rules
sudo udevadm trigger

echo "finish  delete"
