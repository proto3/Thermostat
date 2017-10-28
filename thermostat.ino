#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 10
#define TEMPERATURE_PRECISION 9

#define HEATER1 11
#define HEATER2 12

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DeviceAddress sensor1 = {0x28, 0x7C, 0x11, 0x48, 0x05, 0x00, 0x00, 0x83};
DeviceAddress sensor2 = {0x28, 0x20, 0x3E, 0x48, 0x05, 0x00, 0x00, 0x47};

const float target1 = 29.5;
const float target2 = 28.5;
const float hysteresis = 0.5;

void setup()
{
    Serial.begin(9600);
    sensors.begin();
    sensors.setResolution(sensor1, TEMPERATURE_PRECISION);
    sensors.setResolution(sensor2, TEMPERATURE_PRECISION);

    pinMode(HEATER1, OUTPUT);
    pinMode(HEATER2, OUTPUT);

    digitalWrite(HEATER1, LOW);
    digitalWrite(HEATER2, LOW);
}

void loop()
{
    sensors.requestTemperatures();

    float temp1 = sensors.getTempC(sensor1);
    float temp2 = sensors.getTempC(sensor2);

    Serial.print("Temp1 : ");
    Serial.println(temp1);
    Serial.print("Temp2 : ");
    Serial.println(temp2);

    if(temp1 >= target1)
        digitalWrite(HEATER1, LOW);
    else if(temp1 < target1 - hysteresis)
        digitalWrite(HEATER1, HIGH);

    if(temp2 >= target2)
        digitalWrite(HEATER2, LOW);
    else if(temp2 < target2 - hysteresis)
        digitalWrite(HEATER2, HIGH);

    delay(1000);
}
