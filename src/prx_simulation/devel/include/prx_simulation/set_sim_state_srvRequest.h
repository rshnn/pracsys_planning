// Generated by gencpp from file prx_simulation/set_sim_state_srvRequest.msg
// DO NOT EDIT!


#ifndef PRX_SIMULATION_MESSAGE_SET_SIM_STATE_SRVREQUEST_H
#define PRX_SIMULATION_MESSAGE_SET_SIM_STATE_SRVREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace prx_simulation
{
template <class ContainerAllocator>
struct set_sim_state_srvRequest_
{
  typedef set_sim_state_srvRequest_<ContainerAllocator> Type;

  set_sim_state_srvRequest_()
    : sim_state()
    , node_name()  {
    }
  set_sim_state_srvRequest_(const ContainerAllocator& _alloc)
    : sim_state(_alloc)
    , node_name(_alloc)  {
    }



   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _sim_state_type;
  _sim_state_type sim_state;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _node_name_type;
  _node_name_type node_name;




  typedef boost::shared_ptr< ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> const> ConstPtr;

}; // struct set_sim_state_srvRequest_

typedef ::prx_simulation::set_sim_state_srvRequest_<std::allocator<void> > set_sim_state_srvRequest;

typedef boost::shared_ptr< ::prx_simulation::set_sim_state_srvRequest > set_sim_state_srvRequestPtr;
typedef boost::shared_ptr< ::prx_simulation::set_sim_state_srvRequest const> set_sim_state_srvRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace prx_simulation

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'prx_simulation': ['/home/rshnn/Documents/CS598/pracsys/src/prx_simulation/msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "33a7b8b2ef07b59c7ef6feae729bf484";
  }

  static const char* value(const ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x33a7b8b2ef07b59cULL;
  static const uint64_t static_value2 = 0x7ef6feae729bf484ULL;
};

template<class ContainerAllocator>
struct DataType< ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "prx_simulation/set_sim_state_srvRequest";
  }

  static const char* value(const ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64[] sim_state\n\
string node_name\n\
";
  }

  static const char* value(const ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.sim_state);
      stream.next(m.node_name);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct set_sim_state_srvRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::prx_simulation::set_sim_state_srvRequest_<ContainerAllocator>& v)
  {
    s << indent << "sim_state[]" << std::endl;
    for (size_t i = 0; i < v.sim_state.size(); ++i)
    {
      s << indent << "  sim_state[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.sim_state[i]);
    }
    s << indent << "node_name: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.node_name);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PRX_SIMULATION_MESSAGE_SET_SIM_STATE_SRVREQUEST_H
