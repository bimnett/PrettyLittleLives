class MaryLamb {
private:
    // Set an upperbound for tones and beats loop
    const int length = 10;
    // Frequencies for the notes E4, D4, C4, D4, E4, E4, E4, D4, D4, D4
    int tones[10] = { 329, 294, 261, 294, 329, 329, 329, 294, 294, 294 }; 
    int beats[10] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 2 }; 
     // Tempo/milliseconds, the duration the tone will be played for
    int tempo = 300;
    int buzzerPin;

public:
    MaryLamb(int pin) {
        // Buzzer pin in EnvironmentalTerminal.ino
        buzzerPin = pin;
    }

    void playSong() {
        for(int i = 0; i < length; i++) {
            // The tone will be played for the number of beats * 300
            playTone(tones[i], beats[i] * tempo);
            delay(tempo / 2);    
        }
    }

private:
    void playTone(int tone, int duration) {
        // duration * 1000L is used to convert to milliseconds
        for (long i = 0; i < duration * 1000L; i += tone * 2) {
            // Turn the buzzer on
            digitalWrite(buzzerPin, HIGH);
            delayMicroseconds(tone);
            // Turn the buzzer off
            digitalWrite(buzzerPin, LOW);
            delayMicroseconds(tone);
        }
    }
};
