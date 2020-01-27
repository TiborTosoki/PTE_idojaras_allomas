#include <OneWire.h>                              // OneWire és DallasTemperature library a DS18B20 hőszenzorhoz
#include <DallasTemperature.h>
#include <LowPower.h>

float temperature;
int windDirection;
float windSpeed;
float solarIrradiance;
String weatherDatas;

#define ONE_WIRE_BUS 7                              // a OneWire busz (hőszenzor) a D7-es bemeneten
OneWire oneWire(ONE_WIRE_BUS);                      // egy OneWire példány a busz bemeneti pinjével
DallasTemperature sensors(&oneWire);

void setup() {
  sensors.begin();
  Serial.begin(115200);
  // Az NodeMCU reset pinje, magas -> nem resetel, alacsony -> resetel
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);

  // a tranzisztor bázisa, amellyel a szenzorokat kapcsoljuk be, ha olvasni akarunk
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  
}

void loop() {
  
  

  digitalWrite(5, HIGH);                                                          // tranzisztor megnyitása, majd megvárjuk, hogy a szenzorok bekapcsoljanak és kiolvassuk az adatokat
  delay(1000);
  windDirection = map(analogRead(A0), 212, 1023, 0, 360);                          
  float windSpeedVoltage = analogRead(A1) * (5.0 / 1023);
  windSpeed = 6 * windSpeedVoltage;                                               // a datasheet alapján: szélsebesség [m/s] = mért fesz.[V] * 6
  float solarIrradianceVoltage = (analogRead(A3) * (5.0/1023)) * 1000;
  solarIrradiance = solarIrradianceVoltage * 0.25;                                 // a datasheet alapján: sugárzás[W/m^2] = mért fesz.[mV] * 0.25
  
  for(int i = 0; i < 5; i++){                                                   // 5 mérést végzünk, az érvénytelen eredmények (jellemzően 85 és -127) kiszűrésére
  sensors.requestTemperatures();                                                // kérjük a hőmérsékleteket a hőszenzortól
  float temp = sensors.getTempCByIndex(0);                                     // Celsiusban kérjük a hőmérsékletet a 0-s indexű (most az egyetlen) hőszenzortól
  if (temp != -127 && temp != 85){
      temperature = temp;
    }
}

  digitalWrite(5, LOW);                                         // szenzorok kikapcsolása


  weatherDatas += temperature;                                  
  weatherDatas += ";";
  weatherDatas += windDirection;
  weatherDatas += ";";
  weatherDatas += windSpeed;
  weatherDatas += ";";
  weatherDatas += solarIrradiance;

  digitalWrite(6, LOW);                                   // nodeMCU felébresztése a mélyalvásból a RESET pinje ideiglenes alacsonyra húzásával
  delay(100);
  digitalWrite(6, HIGH);

  delay(1000);
  Serial.println(weatherDatas);                           // az adatokat tartalmazó String elküldése a soros kapcsolaton a nodeMCU-nak

  weatherDatas = "";

  delay(2000);
  goToSleep();                                              // alvó mód, csak maximum 8 mp-re lehet, így ezeket halmozzuk, hogy 6 perc legyen

}


void goToSleep(){
  // 2 perc
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 

    // + 2 perc (4p)
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 

    // + 2 perc (6p)
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
    
  }
