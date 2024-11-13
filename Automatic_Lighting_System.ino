#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;
const int lightSensorPin = A0;
const int ledPin = 9;
int lightThreshold = 500;  // Valor ajustable según las condiciones ambientales

void setup() {
  pinMode(lightSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
  if (!rtc.begin()) {
    Serial.println("No se encontró el RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC perdido, configurando la hora");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Ajustar al tiempo de compilación
  }
}

void loop() {
  int lightLevel = analogRead(lightSensorPin);
  DateTime now = rtc.now();

  Serial.print("Nivel de luz: ");
  Serial.println(lightLevel);
  Serial.print("Hora actual: ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.println(now.minute());

   // Condición para encender el LED: si la luz es baja y es de noche
  if (lightLevel < lightThreshold && (now.hour() >= 18 || now.hour() < 6)) {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED encendido");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("LED apagado");
  }

  delay(1000);  // Pausa de 1 segundo entre lecturas
}