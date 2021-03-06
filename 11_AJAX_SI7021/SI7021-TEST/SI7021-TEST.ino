#include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  Serial.begin(9600);
  
  if(!sensor.begin()){
     Serial.println("Did not find Si7021 sensor!");
  }

  Serial.print("Found model ");
  switch(sensor.getModel()) {
    case SI_Engineering_Samples:
      Serial.print("SI engineering samples"); break;
    case SI_7013:
      Serial.print("Si7013"); break;
    case SI_7020:
      Serial.print("Si7020"); break;
    case SI_7021:
      Serial.print("Si7021"); break;
    case SI_UNKNOWN:
    default:
      Serial.print("Unknown");
  }
  Serial.print(" Rev(");
  Serial.print(sensor.getRevision());
  Serial.print(")");
  Serial.print(" Serial #"); Serial.print(sensor.sernum_a, HEX); Serial.println(sensor.sernum_b, HEX); Serial.print(" ");
}

void loop() {

 Serial.print("Temperature: "); Serial.print(sensor.readTemperature()); Serial.print(" C");
 Serial.print("\t\t");
 Serial.print("Humidity: ");    Serial.print(sensor.readHumidity()); Serial.println(" %");
 delay(500);

}
