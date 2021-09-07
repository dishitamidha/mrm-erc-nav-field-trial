#!/bin/bash -i

cd src/erc_bringup/scripts

chmod +x path.py
chmod +x waypoint_probe_deployment.py

# sudo service ssh start

roslaunch erc_bringup starting_software.launch
