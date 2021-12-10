#include <Wire.h>

#define pressurePin A2
#define tempPin A3
#define times 10
#define vcc 4.6
#define vref 3.3

double x = 0;
double y = 0;
double voltagePres = 0;
double voltageTemp = 0;
double pressure = 0;
double pressureAverage = 0;
double tempAverage = 0;
static double m = 5.6313;
static double b = -1.0276;
byte address = 1;


void sendData();

void setup() {
  Serial.begin(115200);
  Wire.begin(8);
  Wire.onRequest(sendData);
  analogReference(EXTERNAL);
  delay(1000);

}

void loop() {
      for (int i = 0; i < times; i++)
    {
        x += analogRead(pressurePin);
        y += analogRead(tempPin);
    }
    pressureAverage = x/double(times);
    tempAverage = y/double(times);
    voltagePres = pressureAverage*vcc/1023.0; // [voltage]
    voltageTemp = tempAverage*vcc/1023.0;
    // pressure = m * voltage + b;
    x=0;
    y=0;
    //Serial.println(voltage);
//    Serial.print(voltagePres);
//    Serial.print(",");
//    Serial.println(voltageTemp);
}

void sendData(){
  String Mensaje1=String(pressureAverage,DEC);
  String Mensaje2=String(tempAverage,DEC); 
  char MensajeTemp1[6];
  Mensaje1.toCharArray(MensajeTemp1,6);
  char MensajeTemp2[6];
  Mensaje2.toCharArray(MensajeTemp2,6);
  //Wire.beginTransmission(0);
  //Wire.write(6);
  Wire.write(MensajeTemp1);
  Wire.write(",");
  Wire.write(MensajeTemp2);
  //Wire.endTransmission();
//  Serial.println(MensajeTemp1);
//  Serial.print(",");
//  Serial.print(MensajeTemp2);
}
