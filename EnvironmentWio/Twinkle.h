class Twinkle {
private:
    // Set an upperbound for tones and beats loop
    const int length = 12;
    // Frequencies for the notes C4, C4, G4, G4, A4, A4, G4, F4, F4, E4, E4, D4
    int tones[12] = { 261, 261, 392, 392, 440, 440, 392, 349, 349, 330, 330, 294 }; 
    int beats[12] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2 };
    // Tempo/milliseconds, the duration the tone will be played for
    int tempo = 300;
    int buzzerPin;

public:
    Twinkle(int pin) {
        // Will be the buzzer pin in EnvironmentalTerminal.ino
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
        for (long i = 0; i < duration * 1000L; i = i + tone * 2) {
            // Turn the buzzer on
            digitalWrite(buzzerPin, HIGH);
            delayMicroseconds(tone);
            // Turn the buzzer off
            digitalWrite(buzzerPin, LOW);
            delayMicroseconds(tone);
        }
    }
};
