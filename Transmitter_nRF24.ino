#include <SPI.h>
#include <RH_NRF24.h>

// Singleton instance of the radio driver
RH_NRF24 nrf24(8,10);
void setup() 
{
  Serial.begin(9600);
  while (!Serial) 
    ; // wait for serial port to connect. 
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    
}



void loop()
{
  int temp;
  uint8_t data[7]={0};
  if(Serial.available()>0)
  {
   // Send a message to reciever
   delay(1000);
   for(temp=0;temp<7;temp++)
   {
   data[temp]=Serial.read();
   }
   nrf24.send(data, sizeof(data));
  }
  delay(1000);
}
