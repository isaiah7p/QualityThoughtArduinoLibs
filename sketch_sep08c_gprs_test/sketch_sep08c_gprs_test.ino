#include "SIM800.h"

#define APN "connect"
#define con Serial
static const char* url = "http://arduinodev.com/datetime.php";

CGPRS_SIM800 gprs;

void setup()
{
  con.begin(9600);
  while (!con);

  for (;;) {
    con.print("Resetting...");
    while (!gprs.init());
    con.println("OK");
    
    con.print("Setting up network...");
    byte ret = gprs.setup(APN);
    if (ret == 0)
      break;
    con.print("Error code:");
    con.println(ret);
  }
  con.println("OK");

  for (;;) {
    if (gprs.httpInit()) break;
    con.println(gprs.buffer);
    gprs.httpUninit();
    delay(1000);
  }
}

void loop()
{
  gprs.httpConnect(url);
  while (gprs.httpIsConnected() == 0) {
    // can do something here while waiting
  }
  if (gprs.httpState == HTTP_ERROR) {
    con.println("Connect error");
    return; 
  }
  con.println();
  gprs.httpRead();
  int ret;
  while ((ret = gprs.httpIsRead()) == 0) {
    // can do something here while waiting
  }
  if (gprs.httpState == HTTP_ERROR) {
    con.println("Read error");
    return; 
  }

  // now we have received payload
  con.print("[Payload]");
  con.println(gprs.buffer);

  // show position
  GSM_LOCATION loc;
  if (gprs.getLocation(&loc)) {
    con.print("LAT:");
    con.print(loc.lat, 6);
    con.print(" LON:");
    con.print(loc.lon, 6);
    con.print(" TIME:");
    con.print(loc.hour);
    con.print(':');
    con.print(loc.minute);
    con.print(':');
    con.println(loc.second);
  }
}
