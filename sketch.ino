#define BLYNK_TEMPLATE_ID "TMPL3Dg9GLHqY"
#define BLYNK_TEMPLATE_NAME "Motion Detection"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "bNd3gZhu46t33reaCh2lSO9FBl4-Ah2H";
char ssid[] = "Wokwi-GUEST";   // or your WiFi
char pass[] = "";

#define PIR_PIN 4
#define LED_PIN 2

unsigned long lastAlert = 0;
const unsigned long cooldown = 3000; // 10 sec

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Blynk.begin(auth, ssid, pass);

  Serial.println("System Ready");
}

void loop() {
  Blynk.run();

  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH) {
    digitalWrite(LED_PIN, HIGH);

    if (millis() - lastAlert > cooldown) {
      Serial.println("Motion detected!");

      Blynk.virtualWrite(V0, 1);  
      Blynk.logEvent("motion_alert", "Motion detected!");

      lastAlert = millis();
    }

  } else {
    digitalWrite(LED_PIN, LOW);
    Blynk.virtualWrite(V0, 0);
  }

  delay(200);
}