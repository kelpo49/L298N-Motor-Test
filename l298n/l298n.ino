//by: kelpo49
//for: l298n bridge test
//date: october 4th 2025
//license: MIT
//add on: ALWAYS HAVE A MULTIMETER WITH YOU WHILE YOU'RE DEALING WITH ARDUINO!!!! WILL SAVE YOUR ASS AND YOUR TIME IN DEBUGGING
const int ENA = 3, IN1 = 2, IN2 = 4; //pins for motor A (remember ENA has to be a PWM digital pin, with the ~ symbol besides it)
const int ENB = 5, IN3 = 6, IN4 = 7; //pins for motor B (remember ENB has to be a PWM digital pin, with the ~ symbol besides it)
int targetSpeed = 70; //just int in case you need to control it dynamically
/*^defines the speed of both motors, if you have the jumper on both(ENA and ENB) you
don't need to put speed after a function on loop, as they'll always go at max speed*/
#define USECOMPENSATIONA false //true = applies compensation to A, false = in case you don't need compensation on A
#define USECOMPENSATIONB true //true = applies compensation to B, false = in case you don't need compensation on B
int compensation = 30; //compensation for speed differences due to the bridge not sending the same voltage to both
int speedA = 0, speedB = 0; //saves a variable for the speed of motor A and B
/*-------------startup/debug functions-------------*/
void setup() {
  Serial.begin(9600);
  int pins[] = {ENA, IN1, IN2, ENB, IN3, IN4}; //creates an array of defines values, with spaces 0-5
  for(int i = 0; i <= 5; i++) pinMode(pins[i], OUTPUT); //the pins must be output so the arduino sends de 5v to them
}
void setSpeed() { //function for determining the speed of both of them, the constrain is to... constrain... them to 0-255(analog write only accepts that)
  speedA = constrain(targetSpeed + (USECOMPENSATIONA ? compensation : 0), 0, 255); //defines your speed on motor A
  speedB = constrain(targetSpeed + (USECOMPENSATIONB ? compensation : 0), 0, 255); //defines your speed on motor B
  analogWrite(ENA, speedA); //writes the enA pin with speed A value
  analogWrite(ENB, speedB); //writes the enB pin with speed B value
}
void printOrientation (String motor, String direction) { //separate function in case you use the individual A and B movements
  Serial.print(motor);
  Serial.print(" ");
  Serial.print(direction);
  Serial.print(" ");
}
void printSpeeds() {
  Serial.print("| Speed A: ");
  Serial.print(speedA); //shows motor A speed on serial monitor
  Serial.print(" | Speed B: ");
  Serial.println(speedB); //shows motor B speed on serial motor
}
/*-------------movement functions-------------*/
void stop() { //function to stop both motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  speedA = 0;
  speedB = 0;
  Serial.print("Stopped "); //prints the orientation on serial monitor
  printSpeeds();
}
void forward() { //forward function, if they're on the wrong direction you can swap the pins on the bridge
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  setSpeed();
  Serial.print("Forward "); //prints the orientation on serial monitor
  printSpeeds();
}
void backward() { //backwards function
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  setSpeed();
  Serial.print("Backward "); //prints the orientation on serial monitor
  printSpeeds();
}
void stopA() { //function to stop A motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  speedA = 0;
  speedB = 0;
  printOrientation("A", "Stopped "); //prints the orientation on serial monitor
  printSpeeds();
}
void stopB() { //function to stop B motor
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  speedA = 0;
  speedB = 0;
  printOrientation("B", "Stopped "); //prints the orientation on serial monitor
  printSpeeds();
}
void forwardA() { //only A goes forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  setSpeed();
  printOrientation("A", "Forward "); //prints the orientation on serial monitor
  printSpeeds();
}
void forwardB() { //only B goes forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  setSpeed();
  printOrientation("B", "Forward "); //prints the orientation on serial monitor
  printSpeeds();
}
void backwardA() { //only A goes backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  setSpeed();
  printOrientation("A", "Backward "); //prints the orientation on serial monitor
  printSpeeds();
}
void backwardB() { //only B goes backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  setSpeed();
  printOrientation("B", "Backward "); //prints the orientation on serial monitor
  printSpeeds();
}
/*-------------test functions-------------*/
void test1() { //this is where you put the sequence of your test
  forward();
  delay(2000); //it'll go forward for 2 seconds
  stop();
  delay(2000); //it'll stop for 2 seconds
  backward();
  delay(2000); //it'll stop for 2 seconds
  stop();
  delay(2000);
  forwardA();
  backwardB();
  delay(2000);
  stop();
  delay(2000);
  backwardA();
  forwardB();
  delay(2000);
  stop();
}
void test2() {
}
void test3() {
}
/*-------------loop-------------*/
void loop() { //this is where you'll put the functions to control them, put the stop function every time they do something while testing
  test1(); //applies the test
  delay(10000); //interval between tests
}