/*************************************************************
Open Arduino IDE
Go to File > Preference
Copy this > https://dl.espressif.com/dl/package_esp32_index.json 631
Paste it at the box (besides Additional Boards Manager)
Go to Tools > Board > Boards Manager > search “esp32” by Espressif Systems > Install
Go to Sketch > Include Library > Manage Libraries
Search “Blynk” by Volodymyr Shymanskyy > Install
I prefer that you restart your Arduino IDE
Go to Tools > Board > Your ESP32 Board Type (usually Esp32 Dev Module)
You’re done.

Then, you can try Blynk example.

Go to File > Example > Blynk > Boards_WiFi > Esp32_WiFi
You can see #include <BlynkSimpleEsp32.h>



  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license

  This example code is in public domain.

/* Comment this out to disable prints and save space */

#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "FILLTHISFIELD"
#define BLYNK_DEVICE_NAME "Traffic Lights"

//#include <WiFi.h>
//#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

char auth[] = "FILLTHISFIELD";

// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[] = "FILLTHISFIELD";
char pass[] = "FILLTHISFIELD";

int red_pin = 15;
int orange_pin = 2;
int green_pin = 4;

int disco = 0;
int random_delay_time = 150;

void setup()
{
  Serial.begin(9600);

  pinMode(red_pin, OUTPUT);
  pinMode(orange_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);

  Blynk.begin(auth, ssid, pass);
  
  digitalWrite(red_pin, HIGH);
  Blynk.virtualWrite(V0, 1);
  
  digitalWrite(orange_pin, HIGH);
  Blynk.virtualWrite(V1, 1);
  
  digitalWrite(green_pin, HIGH);
  Blynk.virtualWrite(V2, 1);
  
  Blynk.virtualWrite(V3, 0);
  
  Blynk.virtualWrite(V4, random_delay_time);
}

void loop()
{
  Blynk.run();

  if (disco == 1)
    {
      randomLights();
      delay(random_delay_time);
    }
 }

void randomLights()
{
    int pin = random(3);
    int state = random(2);
  
    switch (pin)
    { 
      case 0:
      {
        if (state == 1)
        {
          digitalWrite(red_pin, HIGH); 
        } else 
        {
          digitalWrite(red_pin, LOW); 
        }
      }
      case 1:
      {
        if (state == 1)
         {
          digitalWrite(orange_pin, HIGH); 
        } else 
        {
          digitalWrite(orange_pin, LOW); 
        }
      }
      case 2:
      {
        if (state == 1)
         {
          digitalWrite(green_pin, HIGH); 
        } else 
        {
          digitalWrite(green_pin, LOW); 
        }
      }
    }
}
 
BLYNK_WRITE(V0)
{
   if (param.asInt())
   {
      digitalWrite(red_pin, HIGH); 
   } else 
   {
      digitalWrite(red_pin, LOW); 
   }
}

BLYNK_WRITE(V1)
{
   if (param.asInt())
   {
      digitalWrite(orange_pin, HIGH); 
   } else 
   {
      digitalWrite(orange_pin, LOW); 
   }
}

BLYNK_WRITE(V2)
{
    if (param.asInt())  
    {
      digitalWrite(green_pin, HIGH); 
    } else 
    {
      digitalWrite(green_pin, LOW); 
    }
}

BLYNK_WRITE(V3)
{
  disco = param.asInt();
  if (!disco)
  {
    Blynk.syncVirtual(V0, V1, V2);
  }
}

BLYNK_WRITE(V4)
{
  random_delay_time = param.asInt();
}
