#!/usr/bin/env python

import sys
import pygame
from pygame.locals import *
import rospy
from std_msgs.msg import Int8

def console(dt):

    # initialize pygame screen
    pygame.init()
    SCREEN_SIZE = (640, 480)
    screen = pygame.display.set_mode(SCREEN_SIZE, 0, 32)
    pygame.display.set_caption('Console (must keep active)')
    font = pygame.font.SysFont("arial", 17)
    textSurfaceObj = font.render('Press SPACE to pause .Press LEFT to turn left. Press RIGHT to turn right', True,
                                 (0, 0, 0))
    textRectObj = textSurfaceObj.get_rect()
    textRectObj.center = (300, 150)
    screen.fill((255, 255, 255))
    screen.blit(textSurfaceObj, textRectObj)
    pygame.display.update()

    # initialize ros node
    rospy.init_node('console', anonymous=True)
    rospy.loginfo("console starts")
    pub1 = rospy.Publisher('lane_signal', Int8, queue_size=10)
    pub2 = rospy.Publisher('pause_signal', Int8, queue_size=10)
    lane_signal = Int8()
    pause_signal = 0
    rate = rospy.Rate(1 / dt)
    lane_signal = Int8()
    # detect keyboard input and publish signal
    while (rospy.is_shutdown() != 1):
        for event in pygame.event.get():
            if event.type == KEYDOWN:
                if event.key == pygame.K_LEFT:
                    lane_signal.data = 1

                if event.key == pygame.K_RIGHT:
                    lane_signal.data = -1

                if event.key == pygame.K_DOWN:
                    lane_signal.data = 0

                if event.key == pygame.K_SPACE:
                    pause_signal = Int8()
                    pause_signal.data = 1
                    pub2.publish(pause_signal)
        pub1.publish(lane_signal)
        rate.sleep()
    exit()
if __name__ == '__main__':
    console(0.02)
