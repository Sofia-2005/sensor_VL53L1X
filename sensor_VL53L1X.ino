#include <Wire.h>
#include "SparkFun_VL53L1X.h" //Click here to get the library: http://librarymanager/All#SparkFun_VL53L1X

//Optional interrupt and shutdown pins.
#define SHUTDOWN_PIN 2
#define INTERRUPT_PIN 3
//SDA A4 SCL A5

SFEVL53L1X distanceSensor;
//Uncomment the following line to use the optional shutdown and interrupt pins.
//SFEVL53L1X distanceSensor(Wire, SHUTDOWN_PIN, INTERRUPT_PIN);

void setup(void)
{
  Wire.begin();

  Serial.begin(115200);

  if (distanceSensor.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    while (1)
      ;
  }
  distanceSensor.setDistanceModeLong();
  distanceSensor.setTimingBudgetInMs(200);
  distanceSensor.setOffset(-50); //setear offset en mm
  Serial.println("Sensor online!");
}

void loop(void)
{
  const int numReadings = 7;
  long totalDistance = 0;

  for (int i = 0; i < numReadings; i++) {
    distanceSensor.startRanging();
    while (!distanceSensor.checkForDataReady()) {
      delay(1);
    }
    totalDistance += distanceSensor.getDistance();
    distanceSensor.clearInterrupt();
    distanceSensor.stopRanging();
    delay(10); // Esperar un poco antes de la siguiente medición
  }

  int averageDistance = totalDistance / numReadings;
  Serial.print("Distance(cm): ");
  Serial.println(averageDistance / 10); // Convertir de mm a cm
}
