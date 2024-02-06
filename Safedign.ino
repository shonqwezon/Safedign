#include<SoftwareSerial.h>
#define RX 10
#define TX 11

SoftwareSerial client(RX, TX); 	//RX, TX
String ssid = "wifi"; 			//ssid
String password = "password"; 	//password
const int buttonPin = 2;		//кнопка отслеживания положение двери	
const int REDPin = 6;				
const int YELLOWPin = 5;
const int GREENPin = 4;
int button = 0;
bool connection = false;
bool flag;
bool initState = false;

void connect_wifi(String cmd, int t, char res[]) {
  int count = 0;
  while(true) {
    Serial.println(cmd + " " + count);
    client.println(cmd);
    ledControl(YELLOWPin, t);
    delay(t);   
    if(client.find(res)) {
      Serial.println("OK");
      ledControl(GREENPin, t);
      break;
    }
    count++;
    if(count == 8) {
      delay(100);
      Serial.println("BAD COMMAND");
      initState = true;
      break;
    }
  }
}

void wifi_init() {
      connect_wifi("AT+CIPSTATUS", 500, "STATUS:");
      if(initState) {
        initState = false;
        connect_wifi("AT+CWMODE=3", 500, "OK");
        connect_wifi("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"", 500, "WIFI GOT IP"); 
      }
      connect_wifi("AT+CIPMUX=1", 500, "OK");
      connect_wifi("AT+CIPSTART=0,\"UDP\",\"192.168.1.88\",52856,1111,0", 500, "OK");
}

void send_state(int state) {
  client.println("AT+CIPSEND=0,1");
  delay(100);
  client.println(state); 
}

void ledControl(int pin, int d) {
  digitalWrite(pin, HIGH);
  delay(d);
  digitalWrite(pin, LOW);
}

void setup(){
   pinMode(buttonPin, INPUT);
   
   pinMode(REDPin, OUTPUT);
   pinMode(YELLOWPin, OUTPUT);
   pinMode(GREENPin, OUTPUT);
   
   Serial.begin(9600);
   Serial.println("Serial init..");
   
   client.begin(115200);
   wifi_init();
   
   while(initState) {
    initState = false;
    Serial.println("System doesn't Ready..");
    digitalWrite(REDPin, HIGH);
    client.println("AT+RST");
    delay(10000);
    wifi_init();
   }
   Serial.println("System Ready..");
   digitalWrite(REDPin, LOW);
   ledControl(GREENPin, 5000);
   flag = digitalRead(buttonPin); 
}
void loop() {
    button = digitalRead(buttonPin);
    if(button && flag) {
      flag = false;
      Serial.println("on");
      send_state(0);                        //on music
      return;
    }
    if (!button && !flag) {
      flag = true;
      Serial.println("off");
      send_state(1);                       //off music
      return;
    }
  delay(100);
}
    
//  if(client.available()) Serial.write(client.read());
//  if(Serial.available()) client.write(Serial.read());


























 
