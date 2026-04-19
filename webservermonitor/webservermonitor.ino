#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "AsyncTCP.h"
#include "SPIFFS.h"

// --- Configuration ---
const char* ssid = "brezhnev";
const char* password = "brezhnev02";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setup() {

  Serial.begin(115200);
  Serial.println("Mission Critical");
  Serial.println("SPIFFS File Content Tester");
  

  
  if (!SPIFFS.begin(true)) { Serial.println("An Error has occurred while mounting SPIFFS");return; }

  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  if (!file){
  Serial.print("FILE: HAPANA MDHRAA");
  }


  while(file)
  {
 
      Serial.print("FILE: ");
      Serial.println(file.name());
      file = root.openNextFile();
  }

  // 2. Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Print ESP32 Local IP Address
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // 3. Define Routes
  // This serves monitor.html when the user accesses the root IP
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/monitor.html", "text/html");
  });

  // Optional: Serve other assets (CSS/JS) if they are in SPIFFS
  server.serveStatic("/", SPIFFS, "/");

  // 4. Start Server
  server.begin();
}

void loop() {
  // The Async server runs in the background, 
  // so you don't need to put anything here!
}
 
