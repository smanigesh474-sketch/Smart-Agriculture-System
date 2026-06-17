#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define DHTPIN 15
#define DHTTYPE DHT22

#define SOIL_PIN 34
#define LED_PIN 2
#define BUZZER_PIN 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Failed");
    while(true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  int soil = analogRead(SOIL_PIN);

  display.clearDisplay();

  display.setCursor(0,0);
  display.print("Temp: ");
  display.print(temp);
  display.println(" C");

  display.print("Hum : ");
  display.print(hum);
  display.println(" %");

  display.print("Soil: ");
  display.println(soil);

  if(soil > 2500) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);

    display.println("PUMP ON");
  }
  else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);

    display.println("PUMP OFF");
  }

  display.display();

  delay(1000);
}
