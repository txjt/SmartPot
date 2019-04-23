
#define ref  A0
#define sens A1
#define ctrl A2
#define pump 5

#define halfpi 100

#include "analogComp.h"

boolean interrupt = false;

unsigned long time1;
unsigned long time2;
long tau;

bool stato = 1;

void setup() {
  pinMode(ref, INPUT);
  pinMode(sens, INPUT);
  pinMode(ctrl, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(pump, OUTPUT);


  digitalWrite(ctrl, LOW);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, LOW);
  digitalWrite(pump, LOW);
  
  
  analogComparator.setOn(); //we instruct the lib to use voltages on the pins
  analogComparator.enableInterrupt(changeStatus, FALLING); //FALLING when A0 ref is smaller tha A1 sensor
  Serial.begin(9600);
}
void loop() {
time1 = micros();
while (micros() < time1 + halfpi){
}
 digitalWrite(ctrl, stato);
 digitalWrite(A3, stato);
 digitalWrite(A4, !stato);

stato = !stato;
delay (1000);
if (tau < 190){
  Serial.println("dry");
}
if (tau > 2){
Serial.println("wet");
}
}

void changeStatus() {
    interrupt = true; //let's inform the main loop that the condition has been reached by the analog comparator
    time2 = micros();
    tau = time2 - time1;
 digitalWrite(pump, HIGH);
}
