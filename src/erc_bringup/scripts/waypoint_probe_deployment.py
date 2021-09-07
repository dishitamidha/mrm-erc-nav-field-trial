#!/usr/bin/env python

import rospy
import time
from geometry_msgs.msg import Twist
from std_msgs.msg import Empty, UInt8
import math

pub = rospy.Publisher('/probe_deployment_unit/drop', Empty, queue_size = 1)
def drop_probe(msg):
    data = Empty()
    i = 0
    while (i < 6):
        if (i >= msg.data + 1):
            rospy.signal_shutdown('hello')
        pub.publish(data)
        i = msg.data + 1
        

if __name__ == "__main__":
    rospy.init_node('map_maker', anonymous = True)
    rospy.Subscriber('/probe_deployment_unit/probes_dropped', UInt8, drop_probe)
    rospy.spin()
