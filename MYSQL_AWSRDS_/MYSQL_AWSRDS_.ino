#include <DHT.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define sensorPin1 5

//#define sensorPin2 D2
#define typeDHT DHT11
DHT dht(sensorPin1, typeDHT);

char ssid[] = "Quality Thought 605B";                 // Network Name
char pass[] = "b4b3c69b";                 // Network Password
byte mac[6];

WiFiServer server(80);

//IPAddress ip(192, 168, x, x);
//IPAddress gateway(192, 168, x, x);
//IPAddress subnet(255, 255, 255, 0);

WiFiClient client;
MySQL_Connection conn((Client *)&client);

char INSERT_SQL[] = "INSERT INTO deviceinfo(ID, temp,hum) VALUES (%d, %d, %d)";
//char INSERT_SQL[] = "INSERT INTO officeto_plants.TBL_READINGS(ID_PLANT, AIR_HUMIDITY, AIR_TEMPERATURE, SOIL_MOISTURE_1, SOIL_MOISTURE_2) VALUES (1, NULL, NULL, %d, %d);";
char query[128];

IPAddress server_addr(192,168,1,14);          // MySQL server IP 
char user[] = "supriya";           // MySQL user
char password[] = "harisitha25";       // MySQL password
 int id_loop = 0 ; 
void setup() {

  Serial.begin(9600);

  pinMode(sensorPin1, INPUT);
  //pinMode(sensorPin2, INPUT);

  Serial.println("Initialising connection");
  Serial.print(F("Setting static ip to : "));
 // Serial.println(ip);

  Serial.println("");
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
//
//  WiFi.macAddress(mac);
//  Serial.print("MAC: ");
//  Serial.print(mac[5],HEX);
//  Serial.print(":");
//  Serial.print(mac[4],HEX);
//  Serial.print(":");
//  Serial.print(mac[3],HEX);
//  Serial.print(":");
//  Serial.print(mac[2],HEX);
//  Serial.print(":");
//  Serial.print(mac[1],HEX);
//  Serial.print(":");
//  Serial.println(mac[0],HEX);
//  Serial.println("");
  Serial.print("Assigned IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");

  Serial.println("Connecting to database");
 // id_loop;
  while (conn.connect(server_addr, 3306, user, password) != true) {
    delay(200);
    Serial.print ( "." );
  }

  Serial.println("");
  Serial.println("Connected to SQL Server!");  

}

void loop() {
  
  //int soil_hum = 1024 - analogRead(sensorPin1);
  int t = dht.readTemperature();
  int h = dht.readHumidity();
  
  //Serial.println(t);

  delay(10000); //10 sec

 // sprintf(query, INSERT_SQL, soil_hum);
  sprintf(query, INSERT_SQL,id_loop,t,h);

  Serial.println("Recording data.");
  Serial.println(query);
  
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  
  cur_mem->execute(query);

  delete cur_mem;
  id_loop++;
}
