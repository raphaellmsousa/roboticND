#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

import rospy
import cv2
import matplotlib.pyplot as plt
import rospkg
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import numpy as np
from std_msgs.msg import Float32

rospack = rospkg.RosPack()

class CamNodeClass():

	# class constructor
	def __init__(self):

		self.cx = 0
		self.area = 0
		self.camera_image = None
		self.ball = False # ball detection flag	
		self.bridge = CvBridge()

		# cam_rgb subscriber
		self.sub_cam = rospy.Subscriber('/camera/rgb/image_raw', Image, self.callback_cam)

		# publish ball center
		self.pub_ball_position = rospy.Publisher('/ball_center', Float32, queue_size=1)

		# publish ball area
		self.pub_ball_area = rospy.Publisher('/ball_area', Float32, queue_size=1)

		# defining the eternal loop frequency
		node_sleep_rate = rospy.Rate(10)

		print("Lets start!")

		# sleeps for a while
		#node_sleep_rate.sleep()

		# infinite loop
		while not rospy.is_shutdown():
			# Publishing topics 
			self.pub_ball_position.publish(self.cx)	
			self.pub_ball_area.publish(self.area)	

		# enter in rospy spin
		#rospy.spin()

	def callback_cam(self, msg):
		'''
		Cam callback function
		Input: 
			- Image from usb cam 
		'''
		self.camera_image = msg

		# 1. Conversion for opencv 
		try:
			cv_image = self.bridge.imgmsg_to_cv2(self.camera_image, "rgb8")
		except CvBridgeError as e:
 			print(e)

		# 2. From RGB to BGR, resize for visualization and flipping
		img_out = cv2.cvtColor(cv_image, cv2.COLOR_RGB2BGR)
		img_out = cv2.resize(img_out, None, fx=0.5, fy=0.5)

		# 3. Uncomment to display the image
		#cv2.imshow("ROSI Cam RGB", img_out)	
		#cv2.waitKey(1)

		self.ball_detection(img_out)

		return None

	def ball_detection(self, img):
		'''
		This routine is used to detect the ball. For this purpose,
		it was used a simple color detections function.
		Reference: https://opencv.org/
		'''

		color_select = np.copy(img)

		#print(color_select.shape)

		red_threshold = 220
		green_threshold = 220
		blue_threshold = 220

		rgb_threshold = [red_threshold, green_threshold, blue_threshold]

		color_thresholds = (color_select[:,:,0] < rgb_threshold[0]) | \
					(color_select[:,:,1] < rgb_threshold[1]) | \
					(color_select[:,:,2] < rgb_threshold[2])

		color_select[color_thresholds] = [0,0,0]
		color_select[~color_thresholds] = [0,255,0]
	
		# 1. Define color mask 
		light_color = (70, 255, 255)
		dark_color = (50, 100, 100)

		# 2. Converting BGR to HSV color space
		hsv_img = cv2.cvtColor(color_select, cv2.COLOR_BGR2HSV)

		# 3. Applying the color mask
		mask = cv2.inRange(hsv_img, dark_color, light_color)
		result = cv2.bitwise_and(color_select, color_select, mask=mask)

		# 4. Using a gaussian function to extract noises
		kernel_size = 5
		result = cv2.GaussianBlur(result,(kernel_size, kernel_size), 0)

		# 5. Find contours
		_, contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)	
		print(self.area)
		if not contours:
			self.area = 0
		else:
			for contour in contours:
				self.area = cv2.contourArea(contour)
				if cv2.contourArea(contour) > 10:
					print("Ball detected!!!")
			        	cv2.drawContours(img, contour, -1, (0, 0, 255), 4)	
					# Find center of contours
					M = cv2.moments(contour)
					if M['m00'] > 0:
						self.cx = int(M['m10']/M['m00'])
						cy = int(M['m01']/M['m00'])
						# draw the contour and center of the shape on the image
						cv2.circle(img, (self.cx, cy), 7, (0, 0, 255), -1)
						cv2.putText(img, "ball", (self.cx - 20, cy - 20),
							cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
					else:
						pass	
				else:
					pass

		# 6. Uncomment to display the image 
		cv2.imshow("Ball Detection", img)
		cv2.waitKey(1)
		return None

# instaciate the node
if __name__ == '__main__':

	# initialize the node
	rospy.init_node('cam_node', anonymous=True)

	# instantiate the class
	try:
		node_obj = CamNodeClass()
	except rospy.ROSInterruptException: pass
