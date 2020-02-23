/*************************************************** 
  This is an example for the Adafruit VS1053 Codec Breakout

  Designed specifically to work with the Adafruit VS1053 Codec Breakout 
  ----> https://www.adafruit.com/products/1381

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// PINOUT
// See http://arduino.cc/en/Reference/SPI "Connections"
#define CLK 13       // SPI Clock, delt med SD kort. Hedder SCLK på breakout.
#define MISO 12      // Input data, fra VS1053/SD card. 
#define MOSI 11      // Output data, til VS1053/SD card
#define BREAKOUT_RESET  9      // VS1053 reset pin (output). Hedder RST på breakout.
#define BREAKOUT_CS     10     // VS1053 chip select pin (output). Hedder CS på breakout.
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output). Hedder XDCS på breakout.
#define CARDCS 4     // Card chip select pin. Hedder SDCS på breakout.
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin
// VCC Skal i 5V
// GND skal i GND
// Den røde højtaler ledning skal i enten ROUT eller LOUT
// Den sorte højtaler ledning skal i AGND

Adafruit_VS1053_FilePlayer musicPlayer = 
  // create breakout-example object!
  Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  
void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit VS1053 Simple Test");

  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  
   if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(1,1);

 
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // Interrupt pin / If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    
    // Hvis vi skriver 's' i konsollen stopper musikken
    if (c == 's') {
      Serial.println("Stopped");
      musicPlayer.stopPlaying();
    }
    if (c == 'p') { //Hvis vi skriver 'p' i konsollen starter musikken.
    Serial.println("Playing track 001");
    musicPlayer.begin();
  musicPlayer.startPlayingFile("track001.mp3");
    }
  }
}

 
