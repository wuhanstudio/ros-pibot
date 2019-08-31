#include <ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include "motors.h"

ros::NodeHandle  nh;
MotorControl mtr(20, 21, 22, 23, 20, 21, 22, 23);   //Motor

const int LED = 17;
bool msgRecieved = false;
float velX = 0, turnBias = 0;
char stat_log[200];

void velCB( const geometry_msgs::Twist& twist_msg) {
  velX = twist_msg.linear.x;
  turnBias = twist_msg.angular.z;
  msgRecieved = true;
}

//Subscriber
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", velCB );

//Publisher
std_msgs::Float64 velX_tmp;
std_msgs::Float64 turnBias_tmp;
ros::Publisher xv("vel_x", &velX_tmp);
ros::Publisher xt("turn_bias", &turnBias_tmp);
int i = 0;
void setup() {

  //Init motors, specif>y the respective motor pins
  mtr.initMotors();

  //Init node>
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(xv);
  nh.advertise(xt);
  mtr.stopMotors();

  Serial.begin(115200);
}

void loop() {
  if (msgRecieved) {
    velX *= mtr.maxSpd;
    mtr.moveBot(velX, turnBias);
    msgRecieved = false;
    Serial.println("");
    Serial.println("Command Received");
  }
  velX_tmp.data = velX;
  turnBias_tmp.data = turnBias/mtr.turnFactor;
  xv.publish( &velX_tmp );
  xt.publish( &turnBias_tmp );
  nh.spinOnce();
  Serial.print(".");
  i++;
  if(i >= 20)
  {
    i = 0;
    Serial.println();
  }
  delay(10);
}
