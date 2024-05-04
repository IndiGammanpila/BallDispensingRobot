#include <AccelStepper.h>
#include <Stepper.h>
#include <SharpIR.h>

const int stepsPerRevolution = 100;
const int stepsPerRevolution_Dispenser = 2040;

AccelStepper motor_left(AccelStepper::DRIVER, 4, 7);  //left
AccelStepper motor_right(AccelStepper::DRIVER, 2, 5);  //right
Stepper dispenserStepper = Stepper(stepsPerRevolution_Dispenser,41,43,42,44); //1 3 2 4 
SharpIR sensor_Front( SharpIR::GP2Y0A21YK0F, A14 );
SharpIR sensor_Right( SharpIR::GP2Y0A21YK0F, A15 );

void setup() {
  motor_left.setMaxSpeed(1000); 
  motor_left.setAcceleration(500); 
  motor_right.setMaxSpeed(1000);  
  motor_right.setAcceleration(500);  
}

int distance_Front;
int distance_Right;

void loop() {
  turnRight(); //initial turn 
  distance_Front = sensor_Front.getDistance();  
  forwardWith_Right(); // wall following
  move_forward_with(250,50); //speed, distance
  turnLeft(); //t1
    distance_Front = sensor_Front.getDistance();
  forwardWith_Right();
  move_forward_with(250,60);
  Dispense(); //10
  turnLeft(); //t2
    distance_Front = sensor_Front.getDistance();
  forwardUntil();
  move_forward_with(250,60);
  turnRight(); //t3
    distance_Front = sensor_Front.getDistance();
  forwardUntil();
  move_forward_with(250,60);
  Dispense(); //20
  turnRight(); //t4
    distance_Front = sensor_Front.getDistance();
  forwardUntil();
  turnLeft(); //t5
    distance_Front = sensor_Front.getDistance();
  forwardUntil();
  move_forward_with(250,70);
  turnRight(); //t6
  move_forward_with(250,170);
    distance_Front = sensor_Front.getDistance();
    distance_Right = sensor_Right.getDistance();
  forwardUntil_Uturn();
  forwardUntil();
  move_forward_with(250,60);
  turnRight(); //t7
  move_forward_with(250,280);
  turnRight(); //t8
  move_forward_with(250,60);
    distance_Front = sensor_Front.getDistance();
  forwardWith_Right();
  move_forward_with(250,60);
  Dispense(); // 30
  turnLeft(); //t9
    distance_Front = sensor_Front.getDistance();
  forwardUntil();
  move_forward_with(250,60);
  turnRight(); //t10
    distance_Front = sensor_Front.getDistance();
  forwardUntil();
  move_forward_with(250,60);
  turnLeft(); //t11
    distance_Front = sensor_Front.getDistance();
  forwardWith_Right();
  move_forward_with(250,60);
  Dispense(); //50
    distance_Front = sensor_Front.getDistance();
  Reverse();
  turnLeft(); //t12
  move_forward_with(250,60);
    distance_Front = sensor_Front.getDistance();
  forwardWith_Right();
  move_forward_with(250,60);
  turnLeft(); //t13
    distance_Front = sensor_Front.getDistance();
  forwardWith_Right();
  move_forward_with(250,60);
  Dispense();  //40
  delay(99999999);
   //exit(0);
}
const int p=40;
void wallFollow_along_Right() {
  distance_Right = sensor_Right.getDistance();
  int distanceToWall = 10;
  int speedDiff = (distanceToWall - distance_Right)*p; 
  motor_left.setSpeed(250 - speedDiff);
  motor_right.setSpeed(250 + speedDiff);
  motor_left.runSpeed();
  motor_right.runSpeed();
}
void forwardUntil(){
  while(distance_Front>9 && distance_Front<85){
    distance_Front = sensor_Front.getDistance();
      moveForward();
  if(distance_Front <= 9){
    break;
    }
  }
}
void forwardUntil_Uturn(){
  while(distance_Front>19 && distance_Front<85){
    distance_Front = sensor_Front.getDistance();
      wallFollow_along_Right();
    if(distance_Front <= 19){
      break;
    }
  }
}
void forwardWith_Right(){
  while(distance_Front>9 && distance_Front<85){
    distance_Front = sensor_Front.getDistance();
      wallFollow_along_Right();
    if(distance_Front <= 9){
      break;
    }
  }
}
void moveForward() {
  motor_left.setSpeed(250); 
  motor_right.setSpeed(250); 
  motor_left.runSpeed();
  motor_right.runSpeed();
}
void move_forward_with(int speed, int distance){
  motor_left.setSpeed(speed); 
  motor_right.setSpeed(speed); 
  motor_left.move(distance);
  motor_right.move(distance);
  while (motor_left.distanceToGo() != 0 || motor_right.distanceToGo() != 0) {
    motor_left.run();
    motor_right.run();
  }
}
void Reverse() {
  motor_left.setSpeed(-250);
  motor_right.setSpeed(-250); 
  motor_left.move(-370);
  motor_right.move(-370);
  while (motor_left.distanceToGo() != 0 || motor_right.distanceToGo() != 0) {
    motor_left.run();
    motor_right.run();
  }
}
void turnLeft() {
  motor_left.setSpeed(-100); 
  motor_right.setSpeed(100); 
  motor_left.move(-96);
  motor_right.move(96);
  while (motor_left.distanceToGo() != 0 || motor_right.distanceToGo() != 0) {
    motor_left.run();
    motor_right.run();
  }
}
void turnRight() {
  motor_left.setSpeed(100); 
  motor_right.setSpeed(-100); 
  motor_left.move(95);
  motor_right.move(-95);
  while (motor_left.distanceToGo() != 0 || motor_right.distanceToGo() != 0) {
    motor_left.run();
    motor_right.run();
  }
}
void Dispense(){
  dispenserStepper.setSpeed(10);
  dispenserStepper.step(340);
  delay(1500);
}