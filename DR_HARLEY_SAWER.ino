#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySerial(10, 11); // RX, TX
DFRobotDFPlayerMini player;

unsigned long previousMillis = 0;
const unsigned long interval = 3600000 / 2; // 2 sons par heure = toutes les 30 min

int lastTrack = -1;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);

  if (!player.begin(mySerial)) {
    Serial.println("DFPlayer non détecté");
    while (true);
  }

  player.volume(25); // volume (0-30)
  randomSeed(analogRead(0)); // pour l'aléatoire
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int track;

    // éviter de rejouer le même son directement
    do {
      track = random(1, 11); // 1 à 10
    } while (track == lastTrack);

    lastTrack = track;

    playTwice(track);
  }
}

void playTwice(int track) {
  for (int i = 0; i < 2; i++) {
    player.play(track);

    // attendre que le son se termine
    delay(5000); // ⚠️ à adapter selon durée réelle du son
  }
}
