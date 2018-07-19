#include <LedControl.h>
#include <TimerOne.h>

#define DIN           5
#define CLK           6
#define LOAD          7

        
const int sensorPin = 8;
const unsigned long sampleTime = 1000;


LedControl displayCtrl = LedControl(DIN, CLK, LOAD, 1);

void setup() {

  Serial.begin(9600);
  
  Timer1.initialize(1500); // set a timer of length 1500
  
  pinMode(sensorPin,INPUT);

  displayCtrl.shutdown(0,false);
  displayCtrl.setIntensity(0,8);
  displayCtrl.clearDisplay(0);
  
}

void loop() {

  int rpm = getRPM();
  Serial.println(rpm);
  writeInDisplay(rpm);
}


int getRPM() {
  
  int i = 0;
  boolean flag = LOW;
  unsigned long currentTime = 0;
  unsigned long startTime = millis();
  
  while (currentTime <= sampleTime) {  
    if (digitalRead(sensorPin) == HIGH) {
      flag = HIGH;
    }
    if (digitalRead(sensorPin)==LOW && flag == HIGH) {
      i++;
      flag = LOW;
    }
    currentTime = millis() - startTime;
  }
  
  int rpm = int(60000.0/float(sampleTime))*i;
  
  return rpm;
}

int getArraySize(int number){
  
  int i = 0;
  
  while (number != 0)
  {
      number /= 10;
      i++;
  }

  return i;
  
}

int* setArray(int number) {
  
  int *arr;
  int i = getArraySize(number);
  
  if(i!=0){
    arr = (int*) malloc(i * sizeof(int));
    i = 0;

   while (number != 0){
      arr[i] = number%10;
      number /= 10;
      i++;
   }
  }

  return arr;
}

void writeInDisplay(int n) {
  
  displayCtrl.clearDisplay(0);

  int sizeArr = getArraySize(n)-1;
  int* valueArr = setArray(n);

  for(int i = sizeArr; i >= 0; i--){
    displayCtrl.setDigit(0,i,valueArr[i],false);
//    Serial.println(valueArr[i]);/
  }
}


