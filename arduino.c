#include <Servo.h>

Servo linear, gripper;  
int val; 
double vol;
int dist, pos;
double mdist; 
const byte interruptPin = 2;
int photoVol;
volatile byte state = HIGH; 


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);    //9600 bps
  
  gripper.attach(9);  //pin 9
  linear.attach(5);    //pin 5

  gripper.write(100); // Open gripper

  dist=0; // 0 inches
  pos=map(dist,0, 10, 45, 140);   //map(value, fromLow, fromHigh, toLow, toHigh) o to 10, 45 to 140
  
  linear.write(pos);    //Move to 0 inches
  
  val=analogRead(A0);     //read the analog signal
  mdist=(double) map(val,114,812,0,100);   //analog 0 to 10, 114 to 812, 100 is 10, get the decimel value
  mdist=mdist/10;
  
  //Serial.println("The value is :");    //print the value
  //Serial.println(val);
  //delay(1000);
  while(mdist>0.1)
  {
    val=analogRead(A0);
//    Serial.println(val);
    mdist=(double) map(val,114,812,0,100);   //is this how it supposed to be??????
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
  mdist=(double) map(val,114,812,0,100);
  mdist=mdist/10;
  
  while(mdist<7.9)
  {
    val=analogRead(A0);
    Serial.println(val);
    mdist=(double) map(val,114,812,0,100);
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
  mdist=(double) map(val,114,812,0,100);
  mdist=mdist/10;
  
  while(mdist>3.1)
  {
    val=analogRead(A0);
    mdist=(double) map(val,114,812,0,100);
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

  interrupts();
  pinMode(interruptPin, INPUT_PULLUP); //changes the electricla behavior
  attachInterrupt(digitalPinToInterrupt(interruptPin), OpGripper, FALLING);  //attached the pin, always higher, triggered when fall 5v to 0 v
  delay(5000);
  
  gripper.write(100);
  delay(1000);
  Serial.println("Griper open");
}
void OpGripper()
{
  gripper.write(100);
}
void loop() {
  // put your main code here, to run repeatedly:

}
