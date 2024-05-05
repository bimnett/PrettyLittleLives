class WheelsOnTheBus {
private:
    // Set an upperbound for tones and beats loop
    const int length = 28; 
    // Frequencies for the notes in "Wheels on the Bus"
    int tones[28] = { 261, 349, 349, 349, 349, 440, 523, 440, 349, 392, 392, 349, 329, 294, 261, 349, 349, 349, 349, 440, 523, 440, 349, 392, 392, 349, 261, 261 }; 
    int beats[28] = { 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2 };
    // Tempo/milliseconds, the duration the tone will be played for
    int tempo = 300;
    int buzzerPin;

public:
    WheelsOnTheBus(int pin) {
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
