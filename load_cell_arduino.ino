#include <SoftwareSerial.h>
#include <EEPROM.h> 
#include <HX711_ADC.h>
const int HX711_dout = 4;
const int HX711_sck = 5;
long t;
int temp= 0;
float i;
const int calVal_eepromAdress = 0;
SoftwareSerial mySerial(10, 11);
HX711_ADC LoadCell(HX711_dout, HX711_sck);
void setup() 
     {   
      Serial.begin(9600);
      mySerial.begin(9600);
      delay(10);
      Serial.println();
      Serial.println("Starting...");
      LoadCell.begin();
      float calibrationValue;
      calibrationValue = 8.56;
#if defined(ESP8266)|| defined(ESP32)
#endif
      long stabilizingtime = 2000;
      boolean _tare = true; 
      LoadCell.start(stabilizingtime, _tare);
if (LoadCell.getTareTimeoutFlag()) 
    {
      Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
      while (1);
    }
else 
    {
      LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
      Serial.println("Startup is complete");
    }
    }
void loop()
      {
        static boolean newDataReady = 0;
        const int serialPrintInterval = 0;
if (LoadCell.update()) newDataReady = true;
if (newDataReady) 
      {
if (millis() > t + serialPrintInterval) 
      {
        i = LoadCell.getData();
        int j = i / 10;
        int k = j*10; 
        temp=k;
        Serial.print("Weight");
        Serial.println(temp);
        mySerial.print("Weight");
        mySerial.println(temp);
        delay(200);
      }
      } 
      }
