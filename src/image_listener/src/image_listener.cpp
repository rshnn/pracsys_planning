#include <fstream>
#include <algorithm>

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <std_msgs/String.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <tf/transform_listener.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <image_listener/Num.h>

#include "threshold.hpp"
#include "pixel_coord_transform.hpp"
#include "avg_color.hpp"

using namespace cv;

class ImageListener
{
private:
  ros::NodeHandle nh_;
  image_transport::ImageTransport     transporter_;
  image_transport::Subscriber         camera_sub_;
  image_transport::CameraSubscriber   caminfo_sub_;

  ros::Subscriber                     manipulation_sub;
  int                                 total_objects;

  tf::StampedTransform                tf_transform_;
  tf::TransformListener               tf_listener_;

  ros::Publisher                      object_publisher_;  

public:
  /* CONSTRUCTOR */
  ImageListener() : transporter_(nh_)
  {
    camera_sub_ = transporter_.subscribe("/cameras/left_hand_camera/image", 1, &ImageListener::image_callback, this);
    //caminfo_sub_ = transporter_.subscribeCamera("/cameras/left_hand_camera/camera_info", 1, &ImageListener::info_callback, this);
    //object_publisher_ = nh_.advertise<std_msgs::String>("detected_objects", 1000);
    object_publisher_ = nh_.advertise<image_listener::Num>("detected_objects", 1000);
    manipulation_sub = nh_.subscribe("/manipulation_request", 1, &ImageListener::manipulation_callback, this);
    total_objects = 9;

    std::cout << "Subscribed to left_hand_camera" << std::endl;
    ros::Duration(10).sleep();
  }

  void info_callback(const sensor_msgs::ImageConstPtr, const sensor_msgs::CameraInfoConstPtr msg){

    std::cout<< "info_callback" << std::endl;

  }


  void manipulation_callback(const std_msgs::String& msg){

    total_objects--;
    std::cout << "Object count: " <<total_objects << std::endl;

  }




  /* /cameras/left_hand_camera/image callback */
  void image_callback(const sensor_msgs::ImageConstPtr& msg)
  {

    std::cout << "image_callback" << std::endl;

    /* PARAMETERS FROM CAMERA_INFO ROSTOPIC */
    double fx = 410.11718731515947;
    double fy = 410.51120062506004;
    double primary_x = 666.1770143433905;
    double primary_y = 447.51876027944303;
    
    /* APPLYING HOMO_TRANSFOMS FROM /TF */

    //p_0 = H^0_1 *p_1     Point in frame 0 is the multiplication of the homogen_matrix times the point in frame1
    try{
      tf_listener_.lookupTransform("/left_hand_camera", "/base", ros::Time(0), tf_transform_);
    }
      catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      //ros::Duration(1.0).sleep();
    }

    /* Homoegenous transformation (camera -> base) parameters */
    //Individual parameters
    double x, y, z; 
    double qw, qx, qy, qz; 
    x = tf_transform_.getOrigin().x();
    y = tf_transform_.getOrigin().y();
    z = tf_transform_.getOrigin().z();
    qx = tf_transform_.getRotation().x();
    qy = tf_transform_.getRotation().y();
    qz = tf_transform_.getRotation().z();
    qw = tf_transform_.getRotation().w();

	   //std::cout << x << " " << y << " " << z << std::endl;

    // The 3x3 rotation matrix and 3x1 translation vector.
    tf::Matrix3x3 homo_rotation = tf_transform_.getBasis();
    tf::Vector3 homo_translation = tf_transform_.getOrigin();
    //std::cout << tf_transform_.getOrigin().x() <<" "<< tf_transform_.getOrigin().y() << " "<< tf_transform_.getOrigin().z() << std::endl;



    cv_bridge::CvImagePtr camera_image;
    try
    {
      camera_image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

	boost::array<std::string, 8ul> colors;

	Mat _image = camera_image->image.clone();
	int width = _image.cols;
	int height = _image.rows;
	Mat image(_image.size(), _image.type());
	GaussianBlur(_image, image, Size(3,3), 0, 0);
	Mat greyscale = convert_to_greyscale(image);

	Mat output = threshold_image(greyscale);

	std::vector<Component> components;
	Mat component_output = connected_components(output, components);

	Mat hsv_image(image.size(), image.type());
	cvtColor(image, hsv_image, CV_BGR2HSV);

	//Mat h_image(image.size(), CV_8UC1);
	//Mat s_image(image.size(), CV_8UC1);
	//Mat v_image(image.size(), CV_8UC1);
	//for (int y = 0; y < height; y++) {
	//	for (int x = 0; x < width; x++) {
	//		h_image.at<uchar>(y, x) = hsv_image.at<Vec3b>(y,x)[0];
	//		s_image.at<uchar>(y, x) = hsv_image.at<Vec3b>(y,x)[1];
	//		v_image.at<uchar>(y, x) = hsv_image.at<Vec3b>(y,x)[2];
	//	}
	//}
	//imshow("h", h_image);
	//imshow("s", s_image);
	//imshow("v", v_image);

	Mat orientation = image.clone();

	std::ofstream output_file;
	output_file.open("image_debug.txt");

	output_file << "Image size: " << image.size() << std::endl;

	std::vector<tf::Vector3> global_coords;
	double object_pose[8][7];

	std::sort(components.begin(), components.end(), compare_component_size);

	std::vector<Component> biggest_components(components.end()-8, components.end());	

	std::sort(biggest_components.begin(), biggest_components.end(), compare_component_position);

	int i = 0;
	for (Component c: biggest_components) {
		auto m = c.m;
		auto masked = c.masked;
		auto c_x = c.c_x;
		auto c_y = c.c_y;

		double min_comp_size = masked.cols*masked.rows/400;
		if (m.m00 < min_comp_size) {
			continue;
		}
		i++;
		output_file << "Component ID: " << i << std::endl;
		double avg_h = avg_color(hsv_image, c);
		output_file << "avg_h: " << avg_h << std::endl;
		std::string color;
		if (avg_h < 5) {
			color = std::string("yellow");
		}
		else if (avg_h < 20) {
			color = std::string("red");
		}
		else if (avg_h < 90) {
			color = std::string("green");
		}
		else {
			color = std::string("blue");
		}
		colors[i-1] = color;
		int thickness = -1;
		int lineType = 8;

		circle( orientation,
			Point(c_x, c_y),
			5,
			Scalar(0, 0, 0),
			thickness,
			lineType );

		double axis = c.axis_angle;
		double axisLength = c.major_axis;

		line( orientation,
			Point(c_x, c_y),
			Point(c_x+axisLength*cos(axis), c_y+axisLength*sin(axis)),
			Scalar(0, 0, 0),
			5,
			lineType);

		int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
		double fontScale = 1;
		int textThickness = 3;
		char text[3];
		sprintf(text, "%d", i);
		putText(orientation, text, Point(c_x, c_y-20), fontFace, fontScale,
						Scalar::all(0), textThickness, 8);

		double zoffset = 1.0-0.9;
		// the pixels we are detecting are at the top of the cylinder, but
		// the default position of the cylinders are standing, and the z of their center is 0.9
		//if (c.upright) {
		//	zoffset-=0.07;
		//}
		//else {
		//	zoffset-=0.02-0.07;
		//}

		tf::Vector3 global_frame = pixel_to_image_plane_transform(c_x, height-c_y, primary_x, primary_y, fx, fy, z+zoffset);
		//tf::Vector3 global_frame = tf_transform_*cam_frame;
		if (c.upright) {
			global_frame.setZ(0.9);
		}
		else {
			global_frame.setZ(0.9-0.07+0.02);
		}

		global_coords.push_back(global_frame);

		output_file << "estimated coordinates: " << global_frame.getX() << " " << global_frame.getY() << " " << global_frame.getZ() << std::endl;
		output_file << "centroid: " << c_x << ", " << c_y << std::endl;
		output_file << "axis of orientation: " << axis << std::endl;
		output_file << "isupright: " << (c.m.mu20-c.m.mu02)/c.m.m00 << std::endl;
		output_file << "isuprightBool: " << c.upright << std::endl;

		output_file << "size: " << m.m00 << std::endl; 
		output_file << std::endl;

		object_pose[i-1][0] = global_frame.getX();
		object_pose[i-1][1] = global_frame.getY();
		object_pose[i-1][2] = global_frame.getZ();


    // std::cout << i << " " << m.m00 << std::endl;

    // /* Standing upright */
		if(c.upright ){
     // std::cout << i << " Upright" << std::endl;
			object_pose[i-1][3] = 0;
			object_pose[i-1][4] = 0;
			object_pose[i-1][5] = 0;
			object_pose[i-1][6] = 1;
		}
		else{
    /* Lying on side */
      //  std::cout << i << " On side" << std::endl;
			tf::Vector3 vert_vect = tf::Vector3(0, 0, 1);
			tf::Vector3 vert_horiz = tf::Vector3(0, 1, 0);

			tf::Quaternion quat = tf::Quaternion(vert_vect, -axis);


			tf::Quaternion quat2 = tf::Quaternion(vert_horiz, M_PI/2.0);

			tf::Quaternion pose =  quat*quat2;

			//std::cout << quat.getX() << std::endl;

			object_pose[i-1][3] = pose.getX();
			object_pose[i-1][4] = pose.getY();
			object_pose[i-1][5] = pose.getZ();
			object_pose[i-1][6] = pose.getW();

 		}


	}

    cv::imshow("threshold_image", output);
    cv::imshow("component_output", component_output);
    cv::imshow("orientation", orientation);
    cv::waitKey(5);
  



    /* PUBLISH INFO ON OBJECT LOCATION AND COLOR TO ROSTOPIC /DETECTED_OBJECTS */
    /*
      Still playing around with this.  Check msg/Num.msg for the elements inside the Num message.  Currently adding dummy data into the msg.
    */
    // string dummy_colors[] = {"red", "yellow", "blue", "red", "yellow", "blue", "red", "yellow"};
    image_listener::Num message;

    //Cant figure out why, but I cant pass the arrays declared above^ directly into the message.  probably some type casting needed or something.
    message.colors = colors;
    message.object1 = {object_pose[0][0], object_pose[0][1], object_pose[0][2], object_pose[0][3], object_pose[0][4], object_pose[0][5], object_pose[0][6]};
    message.object2 = {object_pose[1][0], object_pose[1][1], object_pose[1][2], object_pose[1][3], object_pose[1][4], object_pose[1][5], object_pose[1][6]};
    message.object3 = {object_pose[2][0], object_pose[2][1], object_pose[2][2], object_pose[2][3], object_pose[2][4], object_pose[2][5], object_pose[2][6]};
    message.object4 = {object_pose[3][0], object_pose[3][1], object_pose[3][2], object_pose[3][3], object_pose[3][4], object_pose[3][5], object_pose[3][6]};
    message.object5 = {object_pose[4][0], object_pose[4][1], object_pose[4][2], object_pose[4][3], object_pose[4][4], object_pose[4][5], object_pose[4][6]};
    message.object6 = {object_pose[5][0], object_pose[5][1], object_pose[5][2], object_pose[5][3], object_pose[5][4], object_pose[5][5], object_pose[5][6]};
    message.object7 = {object_pose[6][0], object_pose[6][1], object_pose[6][2], object_pose[6][3], object_pose[6][4], object_pose[6][5], object_pose[6][6]};
    message.object8 = {object_pose[7][0], object_pose[7][1], object_pose[7][2], object_pose[7][3], object_pose[7][4], object_pose[7][5], object_pose[7][6]};


    object_publisher_.publish(message);


    //std::cout << "End image_callback" << std::endl;   
  } 



};
  

int main(int argc, char **argv)
{
  std::cout << "Image Listener initiated" << std::endl;
  ros::init(argc, argv, "image_listener");

  ros::AsyncSpinner spinner(1);
  spinner.start();

  ImageListener il;

  ros::spin();

}
