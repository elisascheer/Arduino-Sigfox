   
// Inclusion de la librairie nécessaire pour la lecture du DHT
#include <DHT.h>
//Déclaration des pins reliées aux capteurs
#define DHTPIN A0
// Déclaration du type de capteur utilisé et initialisation
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Inclusion des librairies nécessaires pour l'Akeru
#include <Akeru.h>
#include <SoftwareSerial.h>
// Définition des RX/TX de l'Akeru
#define TX 5
#define RX 4
// Initialisation objet
Akeru Akeru(RX, TX);
unsigned long lastSend;
void setup()
{
  Serial.begin(9600);
 
  // Initialisation Akeru
  Akeru.begin();
 
  // Initialisation DHT
  dht.begin();
  lastSend=0;

}

void loop()
{
  if ( millis() - lastSend > 600000 ) {
    getAndSendData();
    lastSend = millis();
  }
}


void getAndSendData(){
  float temp = dht.readTemperature();
  Serial.print("\ttemp = ");
  Serial.print(temp);
  String temperature = Akeru.toHex(temp);
  String message = temperature;
  Serial.print("\n");
  Serial.print(message);
  Akeru.sendPayload(message);
}
