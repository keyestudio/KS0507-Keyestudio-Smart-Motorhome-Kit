/*
  keyestudio smart RV
  lesson 13.1
  DHT11
  http://www.keyestudio.com
*/
#include <dht11.h>  //include the library code:
dht11 DHT;
#define DHT11_PIN 47 //define DHT11 as 48

void setup() {
  Serial.begin(9600);

}

void loop () {
  int chk;
  chk = DHT.read(DHT11_PIN);    // READ DATA
  switch (chk) {
    case DHTLIB_OK:
      break;
    case DHTLIB_ERROR_CHECKSUM:
      break;
    case DHTLIB_ERROR_TIMEOUT:
      break;
    default:
      break;
  }
  // DISPLAT DATA
  Serial.print("humidity:");
  Serial.print(DHT.humidity);
  Serial.print("   temperature:");
  Serial.println(DHT.temperature);
  delay(100);
}
