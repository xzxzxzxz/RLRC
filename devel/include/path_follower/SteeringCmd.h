// Generated by gencpp from file path_follower/SteeringCmd.msg
// DO NOT EDIT!


#ifndef PATH_FOLLOWER_MESSAGE_STEERINGCMD_H
#define PATH_FOLLOWER_MESSAGE_STEERINGCMD_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace path_follower
{
template <class ContainerAllocator>
struct SteeringCmd_
{
  typedef SteeringCmd_<ContainerAllocator> Type;

  SteeringCmd_()
    : steering_wheel_angle_cmd(0.0)
    , steering_wheel_angle_velocity(0.0)
    , enable(false)
    , clear(false)
    , ignore(false)
    , quiet(false)
    , count(0)  {
    }
  SteeringCmd_(const ContainerAllocator& _alloc)
    : steering_wheel_angle_cmd(0.0)
    , steering_wheel_angle_velocity(0.0)
    , enable(false)
    , clear(false)
    , ignore(false)
    , quiet(false)
    , count(0)  {
  (void)_alloc;
    }



   typedef float _steering_wheel_angle_cmd_type;
  _steering_wheel_angle_cmd_type steering_wheel_angle_cmd;

   typedef float _steering_wheel_angle_velocity_type;
  _steering_wheel_angle_velocity_type steering_wheel_angle_velocity;

   typedef uint8_t _enable_type;
  _enable_type enable;

   typedef uint8_t _clear_type;
  _clear_type clear;

   typedef uint8_t _ignore_type;
  _ignore_type ignore;

   typedef uint8_t _quiet_type;
  _quiet_type quiet;

   typedef uint8_t _count_type;
  _count_type count;




  typedef boost::shared_ptr< ::path_follower::SteeringCmd_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::path_follower::SteeringCmd_<ContainerAllocator> const> ConstPtr;

}; // struct SteeringCmd_

typedef ::path_follower::SteeringCmd_<std::allocator<void> > SteeringCmd;

typedef boost::shared_ptr< ::path_follower::SteeringCmd > SteeringCmdPtr;
typedef boost::shared_ptr< ::path_follower::SteeringCmd const> SteeringCmdConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::path_follower::SteeringCmd_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::path_follower::SteeringCmd_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace path_follower

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'path_follower': ['/home/chen/ProjectCodes/RLRC/RLRC/src/path_follower/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::path_follower::SteeringCmd_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::path_follower::SteeringCmd_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::path_follower::SteeringCmd_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::path_follower::SteeringCmd_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::path_follower::SteeringCmd_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::path_follower::SteeringCmd_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::path_follower::SteeringCmd_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ff1fa11624bdc2aff2aeee5aa6014057";
  }

  static const char* value(const ::path_follower::SteeringCmd_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xff1fa11624bdc2afULL;
  static const uint64_t static_value2 = 0xf2aeee5aa6014057ULL;
};

template<class ContainerAllocator>
struct DataType< ::path_follower::SteeringCmd_<ContainerAllocator> >
{
  static const char* value()
  {
    return "path_follower/SteeringCmd";
  }

  static const char* value(const ::path_follower::SteeringCmd_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::path_follower::SteeringCmd_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Steering Wheel\n\
float32 steering_wheel_angle_cmd        # rad, range -8.2 to 8.2\n\
float32 steering_wheel_angle_velocity   # rad/s, range 0 to 8.7, 0 = maximum\n\
\n\
# Enable\n\
bool enable\n\
\n\
# Clear driver overrides\n\
bool clear\n\
\n\
# Ignore driver overrides\n\
bool ignore\n\
\n\
# Disable the driver override audible warning\n\
bool quiet\n\
\n\
# Watchdog counter (optional)\n\
uint8 count\n\
";
  }

  static const char* value(const ::path_follower::SteeringCmd_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::path_follower::SteeringCmd_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.steering_wheel_angle_cmd);
      stream.next(m.steering_wheel_angle_velocity);
      stream.next(m.enable);
      stream.next(m.clear);
      stream.next(m.ignore);
      stream.next(m.quiet);
      stream.next(m.count);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SteeringCmd_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::path_follower::SteeringCmd_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::path_follower::SteeringCmd_<ContainerAllocator>& v)
  {
    s << indent << "steering_wheel_angle_cmd: ";
    Printer<float>::stream(s, indent + "  ", v.steering_wheel_angle_cmd);
    s << indent << "steering_wheel_angle_velocity: ";
    Printer<float>::stream(s, indent + "  ", v.steering_wheel_angle_velocity);
    s << indent << "enable: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.enable);
    s << indent << "clear: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.clear);
    s << indent << "ignore: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.ignore);
    s << indent << "quiet: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.quiet);
    s << indent << "count: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.count);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PATH_FOLLOWER_MESSAGE_STEERINGCMD_H