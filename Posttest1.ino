#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED1 D4
#define LED2 D7

const char* ssid = "C3";       // Nama SSID AP/Hotspot
const char* password = "11234567";    // Password Wifi

ESP8266WebServer server(80);      //Menyatakan Webserver pada port 80
String webpage;

void setup() {  //Pengaturan Pin
  Serial.begin(115200);
  delay(10);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Connect ke WiFi
  Serial.println();
  Serial.print("Configuring access point...");

  // Mengatur WiFi 
  WiFi.mode(WIFI_STA);                      // Mode Station
  WiFi.begin(ssid, password);               // Mencocokan SSID dan Password
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Print status Connect 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  
  // Isi dari Webpage 
  webpage += "<center><h1>POSTTEST 1 IoT</h1></center>";
  webpage += "<center><strong>LED 1</strong> <br><a href=\"LED1ON\"\"><button>ON</button></a> <a href=\"LED1OFF\"\"><button>OFF</button></a><br></center> <br>";
  webpage += "<center><strong>LED 2</strong> <br><a href=\"LED2ON\"\"><button>ON</button></a> <a href=\"LED2OFF\"\"><button>OFF</button></a><br> </center> <br>";

  // Membuat file webpage 
  server.on("/", []() {
    server.send(200, "text/html", webpage);
  });

  // Bagian ini untuk merespon perintah yang masuk 
  server.on("/LED1ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  });
  server.on("/LED2ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
  });
  server.on("/LED1OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1, LOW);
  });
  server.on("/LED2OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED2, LOW);
  });

  server.begin();
  Serial.println("Server dijalankan");
}

void loop() {  //Perulangan Program
  server.handleClient();
}