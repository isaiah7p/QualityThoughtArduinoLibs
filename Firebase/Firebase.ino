
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "https://boxerdata2-e68b8.firebaseio.com"


#define FIREBASE_AUTH "5fw9HUWGD2DetGXzniLePmrlQ2hwLy8BPdfsPwNn"


#define WIFI_SSID "REDMI"


#define WIFI_PASSWORD "amangoswami123"





void setup() {


Serial.begin(9600);


pinMode(D1, OUTPUT);


// connect to wifi.


WiFi.begin(WIFI_SSID, WIFI_PASSWORD);


Serial.print("connecting");


while (WiFi.status() != WL_CONNECTED) {


Serial.print(".");


delay(500);


}


Serial.println();


Serial.print("connected: ");


Serial.println(WiFi.localIP());





Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);


Firebase.set("LedStatus", 0);


}





int n = 0;





void loop() {


// get value


n = Firebase.getInt("LedStatus");


// handle error


if (n==1) {


Serial.println("LED ON");


digitalWrite(D1,HIGH);  


return;


delay(10);


}


else {


Serial.println("LED OFF");


digitalWrite(D1,LOW);  


return;

delay(10);



}


}
