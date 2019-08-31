#!/usr/bin/python

import rospy
from geometry_msgs.msg import Twist
from pynput.keyboard import Key, Listener

vel = Twist()
vel.linear.x = 0

def on_press(key):
    
    try:
        if(key.char == 'w'):
            print("Forward")
            vel.linear.x = 0.8
            vel.angular.z = 0

        if(key.char == 's'):
            print("Backward")
            vel.linear.x = -0.8
            vel.angular.z = 0

        if(key.char == 'a'):
            print("Counter Clockwise")
            vel.linear.x = 0
            vel.angular.z = -0.8

        if(key.char == 'd'):
            print("Clockwise")
            vel.linear.x = 0
            vel.angular.z = 0.8

        return False

    except AttributeError:
        print('special key {0} pressed'.format(key))
        return False

def on_release(key):
    vel.linear.x = 0
    vel.angular.z = 0

    return False

# Init Node
rospy.init_node('my_cmd_vel_publisher')
pub = rospy.Publisher('cmd_vel', Twist, queue_size=10)

# Set rate
rate = rospy.Rate(10)

listener = Listener(on_release=on_release, on_press = on_press)

while not rospy.is_shutdown():
    print(vel.linear.x)
    pub.publish(vel)
    vel.linear.x = 0
    vel.angular.z = 0
    rate.sleep()
    
    if not listener.running:
        listener = Listener(on_release=on_release, on_press = on_press)
        listener.start()
