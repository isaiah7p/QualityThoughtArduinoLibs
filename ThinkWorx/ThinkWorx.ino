// Temp and Humid

  #include "DHT.h"

  #define DHTPIN 10     // what digital pin we're connected to

  #define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

//WiFi

  #include <ESP8266WiFi.h>

  const char* ssid = "AndroidAP";

  const char* password = "nslc3250x5589";

// The IP address will be dependent on your local network:

char server[] = "ohimvo0g.studio-trial.thingworx.io";

WiFiClient client;

//ThingWorx App key which replaces login credentials)

char appKey[] = "287b9c77-983c-4abf-9f75-4fc273c7183a";

// ThingWorx Thing name for which you want to set properties values

char thingName[] = "HTU21DThing";

// ThingWorx service that will set values for the properties you need

// See the documentation for this tutorial for more information

char serviceName[] = "setTempAndHumid";

//Initialize an HTU21D library object to read

// temperature and humidity data from your connected sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {

  // start serial port:

  Serial.begin(9600);

  while (!Serial) {

    ; // wait for serial port to connect. Needed for Leonardo only

  }

//initialize HTU21D object to read values from sensors

   dht.begin();

  // start the Wifi connection:

Serial.println("Trying to get an IP address using DHCP");

  WiFi.begin(ssid, password);

Serial.println("");

// Wait for connection

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

Serial.print(".");

  }

Serial.println("");

Serial.print("Connected to ");

Serial.println(ssid);

Serial.print("IP address: ");

Serial.println(WiFi.localIP());

}

void loop() {

  // Aquire sensor values

  float Temp =  dht.readTemperature();

  float Humid = dht.readHumidity();

  //through REST calls to your TWX server

  // if you get a connection, report back via serial:



  if (client.connect(server, 8443)) {

    Serial.println("Thingwork Server connected");

    // send the HTTP POST request:

client.print("POST /Thingworx/Things/");

client.print(thingName);

client.print("/Services/");

client.print(serviceName);

client.print("?appKey=");

client.print(appKey);

client.print("&method=post");

client.print("&x-thingworx-session=true");

client.print("<");

client.print("&");

client.print("Temp");

client.print("=");

client.print(Temp);

client.print("&");

client.print("Humid");

client.print("=");

client.print(Humid);

client.print(">");

client.println(" HTTP/1.1");

client.print("Host: ");

client.println(server);

client.println("Content-Type: text/html");

    client.println();

    client.stop();

    // print the request out

Serial.print("POST /Thingworx/Things/");

Serial.print(thingName);

Serial.print("/Services/");

Serial.print(serviceName);

Serial.print("?appKey=");

Serial.print(appKey);

Serial.print("&method=post");

Serial.print("&x-thingworx-session=true");

Serial.print("<");

Serial.print("&");

Serial.print("Temp");

Serial.print("=");

Serial.print(Temp);

Serial.print("&");

Serial.print("Humid");

Serial.print("=");

Serial.print(Humid);

Serial.print(">");

Serial.println(" HTTP/1.1");

Serial.print("Host: ");

Serial.println(server);

Serial.println("Content-Type: text/html");

    Serial.println();

}

  else {

    // kf you didn't get a connection to the server:

Serial.println("the connection could not be established");

    client.stop();

  }

}
