#include <ESP32Servo.h>

#include <Ultrasonic.h>
Ultrasonic u = Ultrasonic(15, 4);

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

NetworkServer server = NetworkServer(80);

Servo s = Servo();

int ENA = 18;
int IN1 = 19;
int IN2 = 21;

int ENB = 5;
int IN3 = 22;
int IN4 = 23;



void setup() {
  s.attach(2);  // Servo

  // Motor A
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  analogWrite(ENA, 250);

  // Motor B
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  analogWrite(ENB, 250);

  Serial.begin(115200);  // Serial
  WiFi.begin("le routeur", "sixfeetfromtheedge");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("WiFi Still Connecting... ");
  }

  Serial.println("WiFi Connected Successfully");

  server.begin();
  Serial.println("Server Started Successfully");
  Serial.println(WiFi.localIP());
}



void loop() {
  NetworkClient client = server.accept();

  if (client) {
    String requestText = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        requestText += c;

        if (c == '\n') {
          Serial.println(requestText);

          // Forward
          if (requestText.startsWith("GET /?status=1")) {
            s.write(90);
            delay(300);
            int d = u.read();
            if (d > 15) {
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN4, LOW);
              digitalWrite(IN3, HIGH);
              delay(500);
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, LOW);
              digitalWrite(IN4, LOW);
              digitalWrite(IN3, LOW);
            } else {
              delay(800);
              HTTPClient request = HTTPClient();
              request.begin("https://fawn-bursting-adversely.ngrok-free.app/ArduinoTest1/StoppingDistanceSave?distance="+String(d));
              
              int status = request.GET();
              if (status > 0) {
                if (status == HTTP_CODE_OK) {
                  String responseText = request.getString();
                  Serial.println(responseText);
                }
              } else {
                Serial.println("Error");
              }
              request.end();
            }
          }

          // Reverse
          if (requestText.startsWith("GET /?status=2")) {
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            digitalWrite(IN4, HIGH);
            digitalWrite(IN3, LOW);
            delay(500);
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
            digitalWrite(IN4, LOW);
            digitalWrite(IN3, LOW);
          }

          // Stop
          if (requestText.startsWith("GET /?status=3")) {
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
            digitalWrite(IN4, LOW);
            digitalWrite(IN3, LOW);
            int d = u.read();
            delay(800);
            HTTPClient request = HTTPClient();
            request.begin("https://fawn-bursting-adversely.ngrok-free.app/ArduinoTest1/StoppingDistanceSave?distance="+String(d));
            int status = request.GET();
            if (status > 0) {
              if (status == HTTP_CODE_OK) {
                String responseText = request.getString();
                Serial.println(responseText);
              }
            } else {
              Serial.println("Error");
            }
            request.end();
          }

          // Turn Right
          if (requestText.startsWith("GET /?status=4")) {
            s.write(45);
            delay(300);
            int d = u.read();
            if (d > 15) {
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, LOW);
              digitalWrite(IN4, LOW);
              digitalWrite(IN3, HIGH);
              delay(500);
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, LOW);
              digitalWrite(IN4, LOW);
              digitalWrite(IN3, LOW);
            }
            s.write(90);
          }

          // Turn Left
          if (requestText.startsWith("GET /?status=5")) {
            s.write(135);
            delay(300);
            int d = u.read();
            if (d > 15) {
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN4, HIGH);
              digitalWrite(IN3, LOW);
              delay(500);
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, LOW);
              digitalWrite(IN4, LOW);
              digitalWrite(IN3, LOW);
            }
            s.write(90);
          }

          break;
        }
      }
    }
    client.stop();
  }
}