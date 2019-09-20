#include <Servo.h>

Servo linear, gripper;  
int val; 
double vol;
int dist, pos;
double mdist; 


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);    //9600 bps
  
  gripper.attach(9);  //pin 9
  linear.attach(5);    //pin 5

  gripper.write(100); // Open gripper

  dist=0; // 0 inches
  pos=map(dist,0, 10, 45, 140);
  
  linear.write(pos);    //Move to 0 inches
  //delay(5000); // Wait for the Linear actuator to move to 0 inches
  
  val=analogRead(A0);     //read the analog signal
  mdist=(double) map(val,100,800,0,100);
  mdist=mdist/10;
  
  while(mdist>0.1)
  {
    val=analogRead(A0);
    mdist=(double) map(val,100,800,0,100);
    mdist=mdist/10;
    Serial.println(mdist);
  }

  delay(2000); // Wait for the actualtor to come to a halt
  Serial.println("At zero inches");
  val=analogRead(A0);
  Serial.println(val);
  vol=(double) val*5/1024;    //574 to voltage conversion
  Serial.println(vol);
  delay(5000);

  dist=8; // 0 inches
  pos=map(dist,0, 10, 45, 140);
  
  linear.write(pos); // Move the linear actuator to 10 inches
  val=analogRead(A0);
  mdist=(double) map(val,100,800,0,100);
  mdist=mdist/10;
  
  while(mdist<8)
  {
    val=analogRead(A0);
    Serial.println(val);
    mdist=(double) map(val,100,800,0,100);
    mdist=mdist/10;
    Serial.println(mdist);
  }

  delay(2000); // Wait for the actualtor to come to a halt
  val=analogRead(A0);
  
  Serial.print("Val: ");
  Serial.println(val);
  vol=(double) val*5/1024;     // Value to voltage conversion
  Serial.print("Voltage: ");
  Serial.println(vol);
  delay(2000);

  // Close the gripper
  gripper.write(0);
  delay(2000);
  Serial.println("Gripper closed");

  // Move the linear actuator to 5 inches

  dist=3; // 0 inches
  pos=map(dist,0, 10, 45, 140);
  
  linear.write(pos);
  val=analogRead(A0);
  mdist=(double) map(val,100,800,0,100);
  mdist=mdist/10;
  
  while(mdist>3.1)
  {
    val=analogRead(A0);
    mdist=(double) map(val,100,800,0,100);
    mdist=mdist/10;
    Serial.println(mdist);
  }

  delay(2000); // Wait for the actualtor to come to a halt
  val=analogRead(A0);
  Serial.print("Val: ");
  Serial.println(val);
  //vol=(double) val*5/1024;     // Value to voltage conversion
  Serial.print("Voltage: ");
  Serial.println(vol);
  delay(2000);

  // Wait for the birdie to be released. 
  // Open gripper after the birdie has been released
  gripper.write(100);
  delay(1000);
  Serial.println("Griper open");
  
}



void loop() {
  // put your main code here, to run repeatedly:

}
