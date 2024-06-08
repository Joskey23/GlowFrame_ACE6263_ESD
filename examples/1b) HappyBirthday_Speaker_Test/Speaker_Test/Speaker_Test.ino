// Define the frequencies for the musical notes
#define D4 293.66
#define E4 329.63
#define Fs4 369.99
#define G4 392.00
#define A4 440.00
#define B4 493.88
#define C5 523.25
#define D5 587.33

#define SPEAKER_PIN 23 // Define the GPIO pin for the speaker
#define CHANNEL 0 // Define the PWM channel
#define RESOLUTION 8 // Define the resolution for PWM (8 bits)
#define DUTY_CYCLE 127 // Define the duty cycle (50% of 255)

// Define the array of musical notes to play
double notes[] = {
D4, D4, E4, D4, G4, Fs4,
D4, D4, E4, D4, A4, G4,
D4, D4, D5, B4, G4, Fs4, E4,
C5, C5, B4, G4, A4, G4
};

void setup() {
ledcSetup (CHANNEL, 2000, RESOLUTION); // Initialize the PWM with a frequency of 2000Hz 
ledcAttachPin (SPEAKER_PIN, CHANNEL); // Attach the speaker pin to the PWM channel
}

void loop() {
// This loop runs once for each note in the 'notes' array
for (int i=0; i < sizeof(notes) / sizeof(double); i++) {
// Play the note by writing its frequency to the PWM channel
ledcWriteTone (CHANNEL, notes[i]);
// Wait for half a second before playing the next note 
delay(500);
}
// Stop sound by writing a frequency of 0 to the PWM channel
ledcWriteTone (CHANNEL, 0);
delay(1000); // Wait for a second before repeating the tune
} 