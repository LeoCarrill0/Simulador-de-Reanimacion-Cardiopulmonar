#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>   //Include File System Headers
#include <Wire.h>
#include <PolledTimeout.h>
#define SDA_PIN 4
#define SCL_PIN 5
#define slave  0x11
const int16_t I2C_MASTER = 0x42;
const int16_t I2C_SLAVE = 0x08;
bool Flag_puls=false;
int Cont_puls_flag=0;
String Cpm_L, Res_L, Pul_L, Butt_L, Pul_L_C, Pul_L_NC, Res_L_C;
int Cpm_state =-1, Pul_State_L,Ciclos_state =-1;
float Cliclos_State_L;
const char* htmlfile = "/index.html";
int cont_puls_Correct=0;
int cont_puls_No_Correct=0;
int cont_puls_Correct_Ant=0;
int cont_resp_cor=0;
// Set AP credentials
#define AP_SSID "RCP_Lab"
#define AP_PASS "RCP_Lab123"

String ledState;

int sensorValue = 0; 
const int analogInPin = A0;

#define LED 2
ESP8266WebServer server(80);

void handlePuls() {
  int cont = 0;
  String t1, t2, t3, t4;
  {
    Wire.requestFrom(I2C_SLAVE, 9);    // request 6 bytes from slave device #8

    while (Wire.available()) { // slave may send less than requested
      char c = Wire.read(); // receive a byte as character
      if(cont>2 && cont<6)
        t2 += c;
      else if(cont>5 && cont<9)
        t3 += c;
      else if(cont>8 && cont<10)
        t4 += c;
      else
        t1 += c;
      cont++;
    }
    Res_L = String(map(t1.toInt(), 100, 355, 0, 255));
    }
  server.send(200, "text/plane", Res_L);
}

void handlePuls1(){
  int cont = 0;
  String t1, t2, t3, t4;
  {
    Wire.requestFrom(I2C_SLAVE, 9);    // request 6 bytes from slave device #8

    while (Wire.available()) { // slave may send less than requested
      char c = Wire.read(); // receive a byte as character
      if(cont>2 && cont<6)
        t2 += c;
      else if(cont>5 && cont<9)
        t3 += c;
      else if(cont>8 && cont<10)
        t4 += c;
      else
        t1 += c;
      cont++;
    }
    Cpm_L = String(map(t2.toInt(), 100, 355, 0, 255));
    }
  server.send(200, "text/plane", Cpm_L);
}

void handlePuls2() {
  int cont = 0;
  String t1, t2, t3, t4;
  {
    Wire.requestFrom(I2C_SLAVE, 9);    // request 6 bytes from slave device #8

    while (Wire.available()) { // slave may send less than requested
      char c = Wire.read(); // receive a byte as character
      if(cont>2 && cont<6)
        t2 += c;
      else if(cont>5 && cont<9)
        t3 += c;
      else if(cont>8 && cont<10)
        t4 += c;
      else
        t1 += c;
      cont++;
    }
    Pul_L = String(map(t3.toInt(), 100, 355, 0, 255));
    Pul_State_L = Pul_L.toInt();
    Cliclos_State_L = (float(Pul_L.toInt()))/(30.00);
    }
  server.send(200, "text/plane", Pul_L);
  vibrador();
}

void handlePuls4() {
  int cont = 0;
  String t1, t2, t3, t4, t5;
  {
    Wire.requestFrom(I2C_SLAVE, 15);    // request 6 bytes from slave device #8

    while (Wire.available()) { // slave may send less than requested
      char c = Wire.read(); // receive a byte as character
      if(cont>2 && cont<6)
        t2 += c;
      else if(cont>5 && cont<9)
        t3 += c;
      else if(cont>8 && cont<12)
        t4 += c;
      else if(cont>11 && cont<15)
        t5 += c;
      else
        t1 += c;
      cont++;
    }
    Pul_L_NC = String(map(t4.toInt(), 100, 355, 0, 255));
    }
  server.send(200, "text/plane", Pul_L_NC);
}

void handlePuls5() {
  int cont = 0;
  String t1, t2, t3, t4, t5;
  {
    Wire.requestFrom(I2C_SLAVE, 15);    // request 6 bytes from slave device #8

    while (Wire.available()) { // slave may send less than requested
      char c = Wire.read(); // receive a byte as character
      if(cont>2 && cont<6)
        t2 += c;
      else if(cont>5 && cont<9)
        t3 += c;
      else if(cont>8 && cont<12)
        t4 += c;
      else if(cont>11 && cont<15)
        t5 += c;
      else
        t1 += c;
      cont++;
    }
    Pul_L_C = String(map(t5.toInt(), 100, 355, 0, 255));
    }
  server.send(200, "text/plane", Pul_L_C);
}

void handlePuls6() {
  Res_L_C=String(cont_resp_cor);
  server.send(200, "text/plane", Res_L_C);
}

void handleStart() {
  String ledState = "OFF";
  String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
  if (t_state == "1"){
    digitalWrite(LED, LOW); //LED ON
    ledState = "Parar"; //Feedback parameter
  }
  else{
    digitalWrite(LED, HIGH); //LED OFF
    ledState = "Iniciar"; //Feedback parameter
  }
  server.send(200, "text/plane", ledState); //Send web page
}

void handleState_CMP() {
  String t_state = server.arg("CPMState"); //Refer  xhttp.open("GET", "SetComp?CPMState="+Number(Comp_1), true);
  Cpm_state = t_state.toInt();
  server.send(200, "text/plane", t_state); //Send web page
}

void handleState_Ciclos() {
  String t_state = server.arg("CiclosState"); //Refer  xhttp.open("GET", "SetComp?CPMState="+Number(Comp_1), true);
  Ciclos_state = t_state.toInt();
  cont_resp_cor = t_state.toInt();
  server.send(200, "text/plane", t_state); //Send web page
}

void vibrador(){
  if(Flag_puls==true && Cont_puls_flag <10){
    digitalWrite(D7, LOW);   
    delay(500);
    digitalWrite(D7, HIGH);
    delay(520);
    digitalWrite(D7, LOW);
    Cont_puls_flag++;
    }else{
    Cont_puls_flag=0;
    Flag_puls=false;}
}

void handleRoot() {
  server.sendHeader("Location", "/index.html", true);  //Redirect to our html web page
  server.send(302, "text/plane", "");
}

void handleWebRequests() {
  if (loadFromSpiffs(server.uri())) return;
  String message = "File Not Detected\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.println(message);
}

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN, I2C_MASTER);
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  pinMode(LED, OUTPUT); //Initialize File System
  SPIFFS.begin();
  Serial.println("File System Initialized");
  pinMode(13, OUTPUT);
  //Acces Point
  
  WiFi.mode(WIFI_AP); //WIFI_AP_STA
  WiFi.softAP(AP_SSID, AP_PASS);     //Connect to your WiFi router
  Serial.println("");
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.on("/getADC", handlePuls);
  server.on("/getADC1", handlePuls1);
  server.on("/getADC2", handlePuls2);
  server.on("/getADC4", handlePuls4);
  server.on("/getADC5", handlePuls5);
  server.on("/getADC6", handlePuls6);
  server.on("/setLED", handleStart);
  server.on("/SetComp", handleState_CMP);
  server.on("/SetCiclos", handleState_Ciclos);
  server.onNotFound(handleWebRequests); //Set setver all paths are not found so we can handle as per URI
  server.begin();
}

void loop() {
  server.handleClient();
  if(Pul_State_L == Cpm_state){
    Flag_puls=true;
    Cpm_state = -1;
  }
  else if(Cliclos_State_L==Ciclos_state && Res_L.toInt() == Ciclos_state*2){
    Flag_puls=true;
    Ciclos_state=-1;
    Serial.print(Cliclos_State_L);
    Serial.print(" ");
    Serial.print(Cpm_state);
    Serial.println("Si");
    }
}

bool loadFromSpiffs(String path) {
  String dataType = "text/plain";
  if (path.endsWith("/")) path += "index.htm";

  if (path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
  else if (path.endsWith(".html")) dataType = "text/html";
  else if (path.endsWith(".htm")) dataType = "text/html";
  else if (path.endsWith(".css")) dataType = "text/css";
  else if (path.endsWith(".js")) dataType = "application/javascript";
  else if (path.endsWith(".png")) dataType = "image/png";
  else if (path.endsWith(".gif")) dataType = "image/gif";
  else if (path.endsWith(".jpg")) dataType = "image/jpeg";
  else if (path.endsWith(".ico")) dataType = "image/x-icon";
  else if (path.endsWith(".xml")) dataType = "text/xml";
  else if (path.endsWith(".pdf")) dataType = "application/pdf";
  else if (path.endsWith(".zip")) dataType = "application/zip";
  else if (path.endsWith("")) dataType = "application/javascript";
  File dataFile = SPIFFS.open(path.c_str(), "r");
  if (server.hasArg("download")) dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size()) {
  }

  dataFile.close();
  return true;
}
