## COMMANDS


```
roslaunch erc_bringup mapserver.launch
```

> If plan A: 
```
roslaunch erc_bringup secondary_software_1A.launch
```

> If plan B: 
```
roslaunch erc_bringup secondary_software_1B.launch
```
```
roslaunch erc_bringup secondary_software_2.launch
```
```
roslaunch erc_bringup secondary_software_3.launch
```

> Goal Cancel
```
rostopic pub /move_base/cancel actionlib_msgs/GoalID -- {}
```
> pROBE
```
rosrun erc_bringup waypoint_probe_deployment.py 
```
>Velocity Command
```
rostopic pub -1 /cmd_vel geometry_msgs/Twist -- '[0.5, 0.0, 0.0]' '[0.0, 0.0, 0.3]'
```
