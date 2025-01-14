// Generated by gencpp from file prx_simulation/request_ground_truth_srv.msg
// DO NOT EDIT!


#ifndef PRX_SIMULATION_MESSAGE_REQUEST_GROUND_TRUTH_SRV_H
#define PRX_SIMULATION_MESSAGE_REQUEST_GROUND_TRUTH_SRV_H

#include <ros/service_traits.h>


#include <prx_simulation/request_ground_truth_srvRequest.h>
#include <prx_simulation/request_ground_truth_srvResponse.h>


namespace prx_simulation
{

struct request_ground_truth_srv
{

typedef request_ground_truth_srvRequest Request;
typedef request_ground_truth_srvResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct request_ground_truth_srv
} // namespace prx_simulation


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::prx_simulation::request_ground_truth_srv > {
  static const char* value()
  {
    return "90956c8a9d3ec220b03ff5bfba854f58";
  }

  static const char* value(const ::prx_simulation::request_ground_truth_srv&) { return value(); }
};

template<>
struct DataType< ::prx_simulation::request_ground_truth_srv > {
  static const char* value()
  {
    return "prx_simulation/request_ground_truth_srv";
  }

  static const char* value(const ::prx_simulation::request_ground_truth_srv&) { return value(); }
};


// service_traits::MD5Sum< ::prx_simulation::request_ground_truth_srvRequest> should match 
// service_traits::MD5Sum< ::prx_simulation::request_ground_truth_srv > 
template<>
struct MD5Sum< ::prx_simulation::request_ground_truth_srvRequest>
{
  static const char* value()
  {
    return MD5Sum< ::prx_simulation::request_ground_truth_srv >::value();
  }
  static const char* value(const ::prx_simulation::request_ground_truth_srvRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::prx_simulation::request_ground_truth_srvRequest> should match 
// service_traits::DataType< ::prx_simulation::request_ground_truth_srv > 
template<>
struct DataType< ::prx_simulation::request_ground_truth_srvRequest>
{
  static const char* value()
  {
    return DataType< ::prx_simulation::request_ground_truth_srv >::value();
  }
  static const char* value(const ::prx_simulation::request_ground_truth_srvRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::prx_simulation::request_ground_truth_srvResponse> should match 
// service_traits::MD5Sum< ::prx_simulation::request_ground_truth_srv > 
template<>
struct MD5Sum< ::prx_simulation::request_ground_truth_srvResponse>
{
  static const char* value()
  {
    return MD5Sum< ::prx_simulation::request_ground_truth_srv >::value();
  }
  static const char* value(const ::prx_simulation::request_ground_truth_srvResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::prx_simulation::request_ground_truth_srvResponse> should match 
// service_traits::DataType< ::prx_simulation::request_ground_truth_srv > 
template<>
struct DataType< ::prx_simulation::request_ground_truth_srvResponse>
{
  static const char* value()
  {
    return DataType< ::prx_simulation::request_ground_truth_srv >::value();
  }
  static const char* value(const ::prx_simulation::request_ground_truth_srvResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // PRX_SIMULATION_MESSAGE_REQUEST_GROUND_TRUTH_SRV_H
