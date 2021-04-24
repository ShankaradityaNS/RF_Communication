#include <SPI.h>
#include <RH_NRF24.h>
int rem[5],pinno[5]={2,3,4,5,6};
RH_NRF24 nrf24(8,10);//Declaring the 
// Singleton instance of the radio driver

void setup() 
{
  Serial.begin(9600);
  while (!Serial) 
    ; // wait for serial port to connect. Needed for nRF
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed"); 
  pinMode(2,OUTPUT); //Outputs to LEDs
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);   
}

void loop()
{
  int i;
  if (nrf24.available())// Message for Reciever
  {   
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN]; //uninitialized char message for reciever
    uint8_t len = sizeof(buf);   //Length of message
    nrf24.recv(buf, &len);
    long num = atoi((const char*) buf);  //Converting Char to long
    num=(num*10)+5;       //Adding constants to number
    num=num+5000000;      //so that compurt does not ignore 0s
    Serial.println(num);
    for(i=6;i>=0;i--)
    {
      if((i!=6)||(i!=0))   //Ignoring the last and first constant bits
      {
       rem[i]=num%10;      //To access each individual bits
       num=num/10;
       if(rem[i])
       {
         digitalWrite(pinno[i-1],1);  //Output HIGH to LED
       }
       else
       {
         digitalWrite(pinno[i-1],0);   //Output LOW to LED
       }
      }}}}
