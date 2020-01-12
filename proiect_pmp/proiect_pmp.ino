#include <Servo.h>

float resolutionADC = .0049 ; // rezoluția implicită (pentru
//referința 5V) = 0.049 [V] / unitate
float resolutionSensor = .01 ; // rezoluție senzor = 0.01V/°C 
int lightValue=0;

int moistureSensorPin= A2;
int tempSensorPin=A0;
int lightSensorPin=A1;
int moistureValue=0;

Servo srv;

void setup() {
 Serial.begin(9600);
}


void closeGateTemp(int pin)
{
 srv.attach(pin);
 srv.write(0);
 delay(1000);
 srv.detach();
}

void openGateTemp(int pin)
{
 srv.attach(pin);
 srv.write(180);
 delay(1000);
 srv.detach();
}

void closeGateLight(int pin)
{
 srv.attach(pin);
 srv.write(180);
 delay(1000);
 srv.detach();
}

void openGateLight(int pin)
{
 srv.attach(pin);
 srv.write(90);
 delay(1000);
 srv.detach();
}

void closeGateMoisture(int pin)
{
 srv.attach(pin);
 srv.write(0);
 delay(1000);
 srv.detach();
}

void openGateMoisture(int pin)
{
 srv.attach(pin);
 srv.write(120);
 delay(1000);
 srv.detach();
}

void loop(){
  
 //temp
 
 Serial.print("Temp [C]: ");
 float temp = readTempInCelsius(10, A0); // citeste temperatura
 //de 10 ori, face media
// float temp = analogRead(tempSensorPin);
 Serial.println(temp);// afisare
 if(temp>26){
  openGateTemp(9);
 }
 if(temp<24){
  closeGateTemp(9);
 }

 //light
 
 lightValue=analogRead(lightSensorPin);
 Serial.print("Light: ");
 Serial.println(lightValue);
 if(lightValue<500){
  openGateLight(10);
 }
 else if (lightValue>600){
  closeGateLight(10);
 }


 //moisture

 moistureValue=analogRead(moistureSensorPin);
 Serial.print("Moisture: ");
 Serial.println(moistureValue);
 if(moistureValue>400){
  openGateMoisture(11);
 }
 else if (moistureValue<350){
  closeGateMoisture(11);
 }

 
 delay(200);
 

}
float readTempInCelsius(int count, int pin) {
 // citește temperatura de count ori de pe pinul analogic pin
 float sumTemp = 0;
 for (int i =0; i < count; i++) {
 int reading = analogRead(pin);
 float voltage = reading * resolutionADC;
 float tempCelsius = (voltage - 0.5) / resolutionSensor ;
 // scade deplasament, convertește în grade C
 sumTemp = sumTemp + tempCelsius; // suma temperaturilor
 }
 return sumTemp / (float)count; // media returnată
}
