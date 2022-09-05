//Including the following libraries is a must to use the IoT functions and features of esp32
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "analogWrite.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;


const char* ssid = "Velociraptor"; // This will show up when you turn on your mobile WIFI
const char* password = "KSVY1234";  // change to more unique password

AsyncWebServer server(80); // These will start the webserver // If you don't know much, Ignore this line

// These pins are the Enable pins of the L293D motor driver which connects to esp32 gpio pins to implement the PWM function
int enable1_2 = 25; // choose the GPIO pin of esp32;
int enable3_4 = 5;// choose the GPIO pin of esp32; */

// These pins are the input pins of l293d on the left side
int inp1 = 19;// Choose your GPIO pin of esp32 for the input 1
int inp2 = 18 ;// Choose your GPIO pin of esp32 for the input 2

// These pins are the input pins of l293d on the right side
int inp3 = 26; // Choose your GPIO pin of esp32 for the input 3
int inp4 = 27 ;// Choose your GPIO pin of esp32 for the input 4 
int trigger ;
int trig_circ;
int trig_eight;
int trig_star;


int led = 2; // until now you must know what is the inbuilt led pin number of esp32. 

void setup(){

  // Fill in the blanks
  SerialBT.begin("Velociraptors"); //Bluetooth device name
  Serial.begin(115200);
  pinMode(enable1_2, OUTPUT);
  pinMode(enable3_4, OUTPUT);
  // The inputs
  pinMode(inp1, OUTPUT);
  pinMode(inp2, OUTPUT);
  pinMode(inp3, OUTPUT);
  pinMode(inp4, OUTPUT);


  pinMode(led, OUTPUT);
  digitalWrite(2,HIGH);

// We use the following function to run the bot at variable speed.
  
  
  WiFi.softAP(ssid, password);  // This sets your esp32's name as per above mentioned

  IPAddress IP = WiFi.softAPIP();

// A bit of WEB DEV stuff 
  server.on("/control", HTTP_GET, [](AsyncWebServerRequest *request){
    if(request->hasArg("up")){
      // You have to develop the logic that, when the Button "up" on the webpage is pressed, Then the esp32 executes the following commands
      // Refer to the this for the webpage photo
      digitalWrite(inp1, HIGH);
      digitalWrite(inp2, LOW);
      digitalWrite(inp3, LOW);
      digitalWrite(inp4, HIGH);

      digitalWrite(led, HIGH);
    }

    if(request->hasArg("down")){
      digitalWrite(inp1, LOW);
      digitalWrite(inp2, HIGH);
      digitalWrite(inp3, HIGH);
      digitalWrite(inp4, LOW);
      digitalWrite(led,LOW);
    }

    if(request->hasArg("left")){
      digitalWrite(inp1, HIGH);
      digitalWrite(inp2, LOW);
      digitalWrite(inp3, HIGH);
      digitalWrite(inp4, LOW);
    }
    
    if(request->hasArg("right")){
      digitalWrite(inp1, LOW);
      digitalWrite(inp2, HIGH);
      digitalWrite(inp3, LOW);
      digitalWrite(inp4, HIGH);
    }

    if(request->hasArg("slow")){ 
// if '255' is the equivalent to digital '1', and '0' is eqvivalent to digial '0', We vary the pwm values to vary the speed of the motor
      analogWrite(enable1_2, 200);   
      analogWrite(enable3_4, 200);  
    }

   if(request->hasArg("fast")){
      analogWrite(enable1_2, 255);   
      analogWrite(enable3_4, 255); 
      digitalWrite(2,HIGH);
    }
    if(request->hasArg("off")){
      digitalWrite(inp1, LOW);
      digitalWrite(inp2, LOW);
      digitalWrite(inp3, LOW);
      digitalWrite(inp4, LOW);
    }
    if(request->hasArg("Square")){
       trigger = 1;
    }
    if(request->hasArg("Circle")){
        trig_circ = 1;
    }
   if(request->hasArg("Eight")){
      trig_eight = 1;
    }
    if(request->hasArg("Star")){
      trig_star = 1;
    }
    
    request->send_P(200, "text/plain", "");  
  });
  

  server.begin();
}
 
void loop(){
  if(trigger==1){
  for(int i=0;i<4;i++){
        digitalWrite(2,HIGH);
        digitalWrite(inp1, HIGH);
        digitalWrite(inp2, LOW);
        digitalWrite(inp3, LOW);
        digitalWrite(inp4, HIGH);
        delay(500);
        digitalWrite(inp1, HIGH);
        digitalWrite(inp2, LOW);
        digitalWrite(inp3, LOW);
        digitalWrite(inp4, HIGH);
        delay(500);
        digitalWrite(inp1, HIGH);
        digitalWrite(inp2, LOW);
        digitalWrite(inp3, LOW);
        digitalWrite(inp4, HIGH);
        delay(500);
        digitalWrite(inp1, HIGH);
        digitalWrite(inp2, LOW);
        digitalWrite(inp3, LOW);
        digitalWrite(inp4, HIGH);
        delay(500);
        digitalWrite(inp1, HIGH);
        digitalWrite(inp2, LOW);
        digitalWrite(inp3, LOW);
        digitalWrite(inp4, HIGH);
        delay(500);
        digitalWrite(inp1, LOW);
        digitalWrite(inp2, HIGH);
        digitalWrite(inp3, LOW);
        digitalWrite(inp4, HIGH);
        delay(400);
        digitalWrite(inp1, LOW);
        digitalWrite(inp2, HIGH);
        digitalWrite(inp3, LOW);
        digitalWrite(inp4, HIGH);
        delay(315);
        digitalWrite(inp1, LOW);
        digitalWrite(inp2, LOW);
        digitalWrite(inp3, LOW);
        digitalWrite(inp4, LOW);
        digitalWrite(2,LOW);
      }
      trigger=0;
  }
  if(trig_circ==1){
    for(int i=0;i<278;i++){
      digitalWrite(inp1, LOW);
      digitalWrite(inp2, HIGH);
      digitalWrite(inp3, LOW);
      digitalWrite(inp4, HIGH);
      delay(10);
      digitalWrite(inp1, HIGH);
      digitalWrite(inp2, LOW);
      digitalWrite(inp3, LOW);
      digitalWrite(inp4, HIGH);
      delay(10);
      digitalWrite(inp1, LOW);
      digitalWrite(inp2, LOW);
      digitalWrite(inp3, LOW);
      digitalWrite(inp4, LOW);
      }
      trig_circ = 0;
  }
  if(trig_eight == 1){
    for(int i=0;i<278;i++){
        digitalWrite(inp1, LOW);
        digitalWrite(inp2, HIGH);
        digitalWrite(inp3, LOW);
        digitalWrite(inp4, HIGH);
        delay(10);
        digitalWrite(inp1, HIGH);
        digitalWrite(inp2, LOW);
        digitalWrite(inp3, LOW);
        digitalWrite(inp4, HIGH);
        delay(10);
        digitalWrite(inp1, LOW);
      digitalWrite(inp2, LOW);
      digitalWrite(inp3, LOW);
      digitalWrite(inp4, LOW);
      }
      for(int i=0;i<278;i++){
        digitalWrite(inp1, HIGH);
        digitalWrite(inp2, LOW);
        digitalWrite(inp3, HIGH);
        digitalWrite(inp4, LOW);
        delay(10);
        digitalWrite(inp1, HIGH);
        digitalWrite(inp2, LOW);
        digitalWrite(inp3, LOW);
        digitalWrite(inp4, HIGH);
        delay(10);
        digitalWrite(inp1, LOW);
      digitalWrite(inp2, LOW);
      digitalWrite(inp3, LOW);
      digitalWrite(inp4, LOW);
      }
      trig_eight = 0;
  }
  if(trig_star==1){
      digitalWrite(inp1, LOW);
      digitalWrite(inp2, HIGH);
      digitalWrite(inp3, LOW);
      digitalWrite(inp4, HIGH);
      delay(208);
      for(int i=0;i<5;i++){
        digitalWrite(inp1, HIGH);
        digitalWrite(inp2, LOW);
        digitalWrite(inp3, LOW);
        digitalWrite(inp4, HIGH);
        delay(2500);
        digitalWrite(inp1, LOW);
        digitalWrite(inp2, HIGH);
        digitalWrite(inp3, LOW);
        digitalWrite(inp4, HIGH);
        delay(1030);
        digitalWrite(inp1, LOW);
        digitalWrite(inp2, LOW);
        digitalWrite(inp3, LOW);
        digitalWrite(inp4, LOW);
      }
      trig_star=0;
  }

}
