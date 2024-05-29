#include "Arduino.h"
#include <FS.h>
#include "Wav.h"
#include "I2S.h"
#include <SD.h>

#define I2S_MODE I2S_MODE_RX
#define sck 25
#define miso 33
#define mosi 26
#define cs 27

const int record_time = 5; // seconds
int fileCount = 0;
String filename = "/sound.wav";

const int headerSize = 44;
const int waveDataSize = record_time * (SAMPLE_RATE * 2);
const int numCommunicationData = 8000;
const int numPartWavData = numCommunicationData / 4;
byte header[headerSize];
char communicationData[numCommunicationData];
char partWavData[numPartWavData];
File file;

void record()
{
  CreateWavHeader(header, waveDataSize);
  SD.remove(filename);
  file = SD.open(filename, FILE_WRITE);
  if (!file)
    return;
  file.write(header, headerSize);
  for (int j = 0; j < waveDataSize / numPartWavData; ++j)
  {
    I2S_Read(communicationData, numCommunicationData);
    for (int i = 0; i < numCommunicationData / 8; ++i)
    {
      partWavData[2 * i] = communicationData[8 * i + 2];
      partWavData[2 * i + 1] = communicationData[8 * i + 3];
    }
    file.write((const byte *)partWavData, numPartWavData);
  }
  file.close();
  Serial.println("finish");
}

void setup()
{
  Serial.begin(115200);
  Serial.println("start");
  SPI.begin(sck, miso, mosi, cs);
  if (!SD.begin(cs))
    Serial.println("SD begin failed");
  while (!SD.begin(cs))
  {
    Serial.print(".");
    delay(500);
  }
  I2S_Init(I2S_MODE, I2S_BITS_PER_SAMPLE_16BIT);
}

void loop()
{
  filename = String("/sound") + fileCount + String(".wav");
  record();
  fileCount += 1;
}
