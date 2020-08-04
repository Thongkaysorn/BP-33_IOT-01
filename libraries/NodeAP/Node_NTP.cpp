#include "NodeAP.h"

TimePara TimeDisco;
int Temp_Hour = 0;
int Temp_Min = 0;
int Temp_Sec = 0;
WiFiUDP Udp;


/*--- NTP ------------------------------------------------------------------*/
int keyIndex = 0;            // your network key Index number (needed only for WEP)
unsigned int localPort = 2390;      // local port to listen for UDP packets

IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server

//static const char ntpServerName[] = "asia.pool.ntp.org";
const int timeZone = 7;
const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

/*--- NTP function ---------------------------------------------------------*/
time_t prevDisplay = 0; // when the digital clock was displayed

void NTP_Init()
{
	Serial.println("\nStarting connection to server...");
  Udp.begin(localPort);
	delay(5000);
}

void NTP_loop()
{
  sendNTPpacket(timeServer); // send an NTP packet to a time server
  delay(1000);

  if (Udp.parsePacket())
	{
    //Serial.println("packet received");
    Udp.read(packetBuffer, NTP_PACKET_SIZE);

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

    unsigned long secsSince1900 = highWord << 16 | lowWord;
    //Serial.print("Seconds since Jan 1 1900 = ");
    //Serial.println(secsSince1900);

    //Serial.print("Unix time = ");
    const unsigned long seventyYears = 2208988800UL;
    unsigned long epoch = secsSince1900 - seventyYears;

    //Serial.println(epoch);

		Temp_Hour = ((epoch % 86400L) / 3600) + timeZone;

		if(Temp_Hour > 23)
		{
			TimeDisco.hour = Temp_Hour - 23;
		}
		else
		{
			TimeDisco.hour = Temp_Hour;
		}
    //Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
    //Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
		//Serial.print(TimeDisco.hour);

    if (((epoch % 3600) / 60) < 10)
		{
      // In the first 10 minutes of each hour, we'll want a leading '0'
			TimeDisco.min = 0;
    }
		else
		{
			TimeDisco.min = (epoch  % 3600) / 60;
		}
    //Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)

    if ((epoch % 60) < 10)
		{
      // In the first 10 seconds of each minute, we'll want a leading '0'
			TimeDisco.sec = 0;
    }
		else
		{
			TimeDisco.sec = epoch % 60;
		}
    //Serial.println(epoch % 60); // print the second
  }
  // wait ten seconds before asking for the time again
  //delay(10000);
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address) {
  //Serial.println("1");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  //Serial.println("2");
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  //Serial.println("3");

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  //Serial.println("4");
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  //Serial.println("5");
  Udp.endPacket();
  //Serial.println("6");
}

/*
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
*/
void TimeDisplay(void)
{
	Serial.print("NTP -> ");
	Serial.print(TimeDisco.hour);	Serial.print(":");
	Serial.print(TimeDisco.min);	Serial.print(":");
	Serial.print(TimeDisco.sec);	Serial.print("|");

	Serial.print("Min:");
	Serial.print(TimeDisco.Sum_min);Serial.print("|");

	/*
  	Serial.print(hour());
  	printDigits(minute());
 	printDigits(second());
  	Serial.print(" ");
  	*/
		/*
  	Serial.print(day());
  	Serial.print(".");
  	Serial.print(month());
  	Serial.print(".");
  	Serial.print(year());
		*/
  	//Serial.println();
}
