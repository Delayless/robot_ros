/******************************************************************
����/odom_combined��/odom_raw������/odom

*******************************************************************/


#include "odom_publish_node.h"
/****************************************************************************/


nav_msgs::Odometry odom;//������̼ƶ���

void odom_combined_callback(const geometry_msgs::PoseWithCovarianceStamped & odom_combined)//����/odom_combined
{
	odom.pose = odom_combined.pose;
}
void odom_raw_callback(const nav_msgs::Odometry & odom_raw)//����/odom_raw
{
	odom.twist = odom_raw.twist;
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "odom_publish_node");//��ʼ�����ڽڵ�
    ros::NodeHandle n;  //����ڵ���̾��
	
	/***********************	/odom_combined	geometry_msgs::PoseWithCovarianceStamped********************************/
    ros::Subscriber odom_combined_sub = n.subscribe("/robot_pose_ekf/odom_combined", 200, odom_combined_callback); //����/odom_combined
	/***********************	/odom_raw	nav_msgs::Odometry********************************/
	ros::Subscriber odom_raw_sub = n.subscribe("/base_controller/odom_raw", 200, odom_raw_callback); //����/odom_combined
	/***********************	/odom	nav_msgs::Odometry********************************/
    ros::Publisher odom_pub= n.advertise<nav_msgs::Odometry>("odom", 200); //����/odom����

    ros::Rate loop_rate(50);//�������ݷ���Ƶ��
    while(ros::ok())
    {
		odom.header.stamp = ros::Time::now(); 											//������̼�ʱ���		
		odom.header.frame_id = "odom";			//(ԭʼ��ODOM����)												//��̼Ƶĸ�������ϵ
		odom.child_frame_id = "base_link";  //base_footprint 
		odom_pub.publish(odom);															//������̼�
				
		ros::spinOnce();  //callback�������봦����������ʱ���ſ����õ�//���������Ե���			//
		//ros::spin();//����ִ��
		loop_rate.sleep();//��������
    }
    return 0;
}