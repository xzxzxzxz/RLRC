#!/usr/bin/env python
import rospy
from path_follower.msg import vehicleinfo, vehicleinfomation
from std_msgs.msg import String, Header

# define the initial states and timestep
info_mark = False
def vehicleinfoCallback(infoma):
    global info, info_mark
    info = infoma.data
    info_mark=True

def main(dt):
    global info, info_mark

    # import track file
    rospy.init_node('transfer', anonymous=True)
    rospy.Subscriber('vehicle_info', String, vehicleinfoCallback)
    pub = rospy.Publisher('vehicle_state', vehicleinfo, queue_size=1)
    rate = rospy.Rate(1/dt)

    while (rospy.is_shutdown() != 1):
        if info_mark == True and len(info) > 0:
            vinfo = vehicleinfo()
            
            print(info)
            for k in range(5):
            	if info[k] == '&':
            		number = int(info[:k])
            		break
            index = []
            length = len(info)
            for ii in range(length):
            	if info[ii] == '&':
            		index.append(ii);
            for i in range(number):
                pt = vehicleinfomation()
                pt.ind = int(float(info[index[i*9]+1:index[i*9+1]]))
                pt.X = float(info[index[i*9+1]+1:index[i*9+2]])
                pt.Y = -float(info[index[i*9+2]+1:index[i*9+3]])
                pt.psi = -float(info[index[i*9+3]+1:index[i*9+4]])
                pt.vx = float(info[index[i*9+4]+1:index[i*9+5]])
                pt.vy = float(info[index[i*9+5]+1:index[i*9+6]])
                pt.wz = float(info[index[i*9+6]+1:index[i*9+7]])
                pt.lx = float(info[index[i*9+7]+1:index[i*9+8]])
                pt.ly = float(info[index[i*9+8]+1:index[i*9+9]])
                vinfo.point.append(pt)  #list add an element in the end 
            vinfo.header = Header()
            vinfo.header.stamp = rospy.get_rostime()
            pub.publish(vinfo)
        rate.sleep()

if __name__ == '__main__':
    main(0.02)
