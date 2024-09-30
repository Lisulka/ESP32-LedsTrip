#include <Arduino.h>
#include <FastLED.h>
#include <math.h>  // Include for sin() and other math functions
#include <avr/pgmspace.h>  // Needed for accessing PROGMEM on AVR-based boards


// edited from code by Mark Kriegsman, December 2014

// test code for my led strip
// edited to work with VS Code + PlatformIO + ESP32
// Evgeni Vi, 2021
// Modified for Arduino nano by Jeni.S + Music Reactive 

// declaration
void nextPattern();
void prevPattern();
void psyTrain();
void rainbow();
void rainbowWithGlitter();
void palettesMarch();
void palettesGMarch(uint8_t glitterChance);
void addPGlitterOverlay(uint8_t chance);
void palettesGlitter();
void confetti();
void sinelon();
void juggle();
void bpm ();
void addGlitter( fract8 chanceOfGlitter);
void waveform();
void plasmaEffect();
void psypoliceLights();
void fireworks();
void colorComet();
void pulse();
void snake();
void snakeCyclePalettes();
void snakeComet();
void trippysnake();
void palettesSplits();
void fireflyEffect();
void paletteStrobe();
void paletteglitterEffect(uint8_t glitterChance);
void UV();
void solidUV();
void solidWhite();
void off();


// Custom TProgmemPalette16 Color Palettes:

const TProgmemPalette16 galaxyDream PROGMEM = {
    CRGB::DeepSkyBlue, CRGB::Purple, CRGB::Indigo, CRGB::DeepPink,
    CRGB::Black, CRGB::Violet, CRGB::Lavender, CRGB::Gold,
    CRGB::DarkBlue, CRGB::SteelBlue, CRGB::SlateBlue, CRGB::White,
    CRGB::Navy, CRGB::Violet, CRGB::Lavender, CRGB::PeachPuff
};


const TProgmemPalette16 lavaLamp PROGMEM = {
    CRGB::Red, CRGB::Orange, CRGB::Yellow, CRGB::HotPink,
    CRGB::Purple, CRGB::Magenta, CRGB::Crimson, CRGB::Coral,
    CRGB::LimeGreen, CRGB::BlueViolet, CRGB::Yellow, CRGB::Gold,
    CRGB::Fuchsia, CRGB::DarkMagenta, CRGB::DeepPink, CRGB::PaleVioletRed
};

const TProgmemPalette16 dmtDream PROGMEM = {
    CRGB::Magenta, CRGB::LimeGreen, CRGB::Cyan, CRGB::DeepPink,
    CRGB::Purple, CRGB::Yellow, CRGB::Orange, CRGB::Fuchsia,
    CRGB::Green, CRGB::HotPink, CRGB::Turquoise, CRGB::Chartreuse,
    CRGB::Blue, CRGB::Gold, CRGB::Crimson, CRGB::Violet
};

const TProgmemPalette16 neonVibes PROGMEM = {
    CRGB::Red, CRGB::Orange, CRGB::Yellow, CRGB::Lime,
    CRGB::Aqua, CRGB::Blue, CRGB::Purple, CRGB::Fuchsia,
    CRGB::HotPink, CRGB::LimeGreen, CRGB::Magenta, CRGB::Teal,
    CRGB::Turquoise, CRGB::Chartreuse, CRGB::DeepSkyBlue, CRGB::HotPink
};

const TProgmemPalette16 psychedelicSunset PROGMEM = {
    CRGB::Orange, CRGB::DeepPink, CRGB::Purple, CRGB::Magenta,
    CRGB::Violet, CRGB::Red, CRGB::Yellow, CRGB::HotPink,
    CRGB::Orange, CRGB::DeepPink, CRGB::Purple, CRGB::Magenta,
    CRGB::Violet, CRGB::Red, CRGB::Yellow, CRGB::HotPink
};

const TProgmemPalette16 psyTrance PROGMEM = {
    CRGB::Red, CRGB::HotPink, CRGB::Orange, CRGB::Yellow,
    CRGB::Green, CRGB::Lime, CRGB::Cyan, CRGB::Aqua,
    CRGB::Blue, CRGB::Purple, CRGB::Fuchsia, CRGB::Magenta,
    CRGB::Turquoise, CRGB::Chartreuse, CRGB::DeepPink, CRGB::Teal
};

const TProgmemPalette16 candyCrush PROGMEM = {
    CRGB::LawnGreen, CRGB::LemonChiffon, CRGB::Pink, CRGB::LightCoral,
    CRGB::MediumPurple, CRGB::Aqua, CRGB::Fuchsia, CRGB::Orange,
    CRGB::PeachPuff, CRGB::PaleGreen, CRGB::DeepPink, CRGB::SkyBlue,
    CRGB::Yellow, CRGB::LavenderBlush, CRGB::Violet, CRGB::Coral
};

const TProgmemPalette16 electricDreams PROGMEM = {
    CRGB::Pink, CRGB::HotPink, CRGB::Lavender, CRGB::Teal,
    CRGB::Coral, CRGB::Fuchsia, CRGB::Yellow, CRGB::Turquoise,
    CRGB::Purple, CRGB::LightSkyBlue, CRGB::Lavender, CRGB::Lime,
    CRGB::Coral, CRGB::Fuchsia, CRGB::Yellow, CRGB::Turquoise
};

const TProgmemPalette16 acidWave PROGMEM = {
    CRGB::LimeGreen, CRGB::Magenta, CRGB::Yellow, CRGB::DeepSkyBlue,
    CRGB::Orange, CRGB::BlueViolet, CRGB::Fuchsia, CRGB::Turquoise,
    CRGB::Purple, CRGB::Red, CRGB::Chartreuse, CRGB::Coral,
    CRGB::GreenYellow, CRGB::DeepPink, CRGB::Teal, CRGB::HotPink
};

const TProgmemPalette16 miamiVice PROGMEM = {
    CRGB::Cyan, CRGB::Pink, CRGB::Turquoise, CRGB::Lavender,
    CRGB::Fuchsia, CRGB::Gold, CRGB::Aqua, CRGB::HotPink,
    CRGB::Cyan, CRGB::Orange, CRGB::Yellow, CRGB::Violet,
    CRGB::Turquoise, CRGB::MediumVioletRed, CRGB::Pink, CRGB::Aqua
};

const TProgmemPalette16 alienJungle PROGMEM = {
    CRGB::DarkGreen, CRGB::Lime, CRGB::Aqua, CRGB::Purple,
    CRGB::Magenta, CRGB::Teal, CRGB::GreenYellow, CRGB::Violet,
    CRGB::DarkGreen, CRGB::Lime, CRGB::Aqua, CRGB::Purple,
    CRGB::Magenta, CRGB::Teal, CRGB::GreenYellow, CRGB::Violet
};

const TProgmemPalette16 acidTrip PROGMEM = {
    CRGB::Yellow, CRGB::Magenta, CRGB::Cyan, CRGB::Lime,
    CRGB::Fuchsia, CRGB::Purple, CRGB::Orange, CRGB::Green,
    CRGB::Yellow, CRGB::Magenta, CRGB::Cyan, CRGB::Lime,
    CRGB::Fuchsia, CRGB::Purple, CRGB::Orange, CRGB::Green
};

const TProgmemPalette16 cosmicDream PROGMEM = {
    CRGB::Navy, CRGB::DeepSkyBlue, CRGB::Purple, CRGB::Indigo,
    CRGB::Violet, CRGB::Lavender, CRGB::Gold, CRGB::DeepPink,
    CRGB::Navy, CRGB::DeepSkyBlue, CRGB::Purple, CRGB::Indigo,
    CRGB::Violet, CRGB::Lavender, CRGB::PeachPuff, CRGB::DeepPink
};

const TProgmemPalette16 popArt PROGMEM = {
    CRGB::Red, CRGB::Yellow, CRGB::Blue, CRGB::Green,
    CRGB::Fuchsia, CRGB::Cyan, CRGB::Orange, CRGB::Violet,
    CRGB::Pink, CRGB::Chartreuse, CRGB::Aqua, CRGB::Purple,
    CRGB::HotPink, CRGB::Yellow, CRGB::Lime, CRGB::Turquoise
};

const TProgmemPalette16 meltedCandy PROGMEM = {
    CRGB::PeachPuff, CRGB::HotPink, CRGB::LightCoral, CRGB::Lavender,
    CRGB::Aquamarine, CRGB::Yellow, CRGB::Coral, CRGB::Fuchsia,
    CRGB::PeachPuff, CRGB::HotPink, CRGB::LightCoral, CRGB::Lavender,
    CRGB::Aquamarine, CRGB::Yellow, CRGB::Coral, CRGB::Fuchsia
};

const TProgmemPalette16 digitalVortex PROGMEM = {
    CRGB::Black, CRGB::Cyan, CRGB::Magenta, CRGB::DeepSkyBlue,
    CRGB::Yellow, CRGB::Lime, CRGB::Orange, CRGB::Purple,
    CRGB::Black, CRGB::Cyan, CRGB::Magenta, CRGB::AliceBlue,
    CRGB::Yellow, CRGB::Lime, CRGB::Orange, CRGB::Purple
};

const TProgmemPalette16 toxicGlow PROGMEM = {
    CRGB::LimeGreen, CRGB::Yellow, CRGB::Green, CRGB::Black,
    CRGB::DarkGreen, CRGB::YellowGreen, CRGB::GreenYellow, CRGB::Chartreuse,
    CRGB::LimeGreen, CRGB::Yellow, CRGB::Green, CRGB::Black,
    CRGB::DarkGreen, CRGB::YellowGreen, CRGB::LimeGreen, CRGB::Chartreuse
};

const TProgmemPalette16 rainbowCandy PROGMEM = {
    CRGB::Red, CRGB::Orange, CRGB::Yellow, CRGB::Green,
    CRGB::Blue, CRGB::Purple, CRGB::Magenta, CRGB::Fuchsia,
    CRGB::Crimson, CRGB::HotPink, CRGB::Chartreuse, CRGB::Aqua,
    CRGB::Coral, CRGB::Turquoise, CRGB::Gold, CRGB::DeepPink
};

const TProgmemPalette16 cyberGlow PROGMEM = {
    CRGB::Cyan, CRGB::Magenta, CRGB::Lime, CRGB::Yellow,
    CRGB::DeepSkyBlue, CRGB::Orange, CRGB::Purple, CRGB::Fuchsia,
    CRGB::LimeGreen, CRGB::Turquoise, CRGB::HotPink, CRGB::GreenYellow,
    CRGB::DeepPink, CRGB::Gold, CRGB::Lavender, CRGB::BlueViolet
};

const TProgmemPalette16 funkyDisco PROGMEM = {
    CRGB::HotPink, CRGB::Purple, CRGB::Aqua, CRGB::Fuchsia,
    CRGB::Yellow, CRGB::Orange, CRGB::Turquoise, CRGB::DeepSkyBlue,
    CRGB::Magenta, CRGB::LawnGreen, CRGB::Red, CRGB::Lavender,
    CRGB::PeachPuff, CRGB::Coral, CRGB::Lime, CRGB::Crimson
};

const TProgmemPalette16 psychedelicDream PROGMEM = {
    CRGB::Magenta, CRGB::DeepPink, CRGB::Yellow, CRGB::Cyan,
    CRGB::Purple, CRGB::Turquoise, CRGB::Fuchsia, CRGB::Orange,
    CRGB::Lime, CRGB::Green, CRGB::HotPink, CRGB::Violet,
    CRGB::Aqua, CRGB::Chartreuse, CRGB::Coral, CRGB::Gold
};
const TProgmemPalette16 tropicalSunset PROGMEM = {
    CRGB::Orange, CRGB::Red, CRGB::Yellow, CRGB::HotPink,
    CRGB::Magenta, CRGB::Aqua, CRGB::DeepSkyBlue, CRGB::Violet,
    CRGB::Crimson, CRGB::Coral, CRGB::Fuchsia, CRGB::Gold,
    CRGB::Orchid, CRGB::Turquoise, CRGB::LimeGreen, CRGB::Purple
};

const TProgmemPalette16 cosmicWaves PROGMEM = {
    CRGB::DeepSkyBlue, CRGB::Blue, CRGB::Purple, CRGB::Lavender,
    CRGB::Magenta, CRGB::Pink, CRGB::HotPink, CRGB::Fuchsia,
    CRGB::Cyan, CRGB::Navy, CRGB::Indigo, CRGB::Turquoise,
    CRGB::LightBlue, CRGB::Aquamarine, CRGB::Gold, CRGB::Crimson
};

const TProgmemPalette16 ultravioletDreams PROGMEM = {
    CRGB::Fuchsia, CRGB::Magenta, CRGB::Indigo, CRGB::Purple,
    CRGB::DeepPink, CRGB::Violet, CRGB::Blue, CRGB::Lavender,
    CRGB::Turquoise, CRGB::Aquamarine, CRGB::GreenYellow, CRGB::Chartreuse,
    CRGB::Cyan, CRGB::SkyBlue, CRGB::Teal, CRGB::HotPink
};

const TProgmemPalette16 electricCarnival PROGMEM = {
    CRGB::Red, CRGB::Orange, CRGB::Yellow, CRGB::LimeGreen,
    CRGB::Aqua, CRGB::Fuchsia, CRGB::DeepSkyBlue, CRGB::Lime,
    CRGB::Pink, CRGB::HotPink, CRGB::Purple, CRGB::Gold,
    CRGB::Crimson, CRGB::Chartreuse, CRGB::Turquoise, CRGB::Violet
};

const TProgmemPalette16 neonParadise PROGMEM = {
    CRGB::Fuchsia, CRGB::SeaGreen, CRGB::Yellow, CRGB::Aqua,
    CRGB::Cyan, CRGB::Orange, CRGB::LimeGreen, CRGB::Purple,
    CRGB::DeepPink, CRGB::Magenta, CRGB::Teal, CRGB::Gold,
    CRGB::LightBlue, CRGB::SkyBlue, CRGB::HotPink, CRGB::Indigo
};

const TProgmemPalette16 cyberwave PROGMEM = {
    CRGB::Cyan, CRGB::Magenta, CRGB::Yellow, CRGB::LimeGreen,
    CRGB::Purple, CRGB::Fuchsia, CRGB::DeepSkyBlue, CRGB::Gold,
    CRGB::Turquoise, CRGB::HotPink, CRGB::Red, CRGB::Orange,
    CRGB::Violet, CRGB::Aqua, CRGB::Chartreuse, CRGB::Lavender
};

const TProgmemPalette16 auroraBorealis PROGMEM = {
    CRGB::Purple, CRGB::Indigo, CRGB::Blue, CRGB::Teal,
    CRGB::Green, CRGB::Cyan, CRGB::Lime, CRGB::Yellow,
    CRGB::Orange, CRGB::Red, CRGB::HotPink, CRGB::Magenta,
    CRGB::Fuchsia, CRGB::Turquoise, CRGB::Violet, CRGB::Gold
};

const TProgmemPalette16 neonGalaxy PROGMEM = {
    CRGB::Red, CRGB::LimeGreen, CRGB::Aqua, CRGB::HotPink,
    CRGB::Blue, CRGB::Orange, CRGB::Fuchsia, CRGB::Purple,
    CRGB::Yellow, CRGB::Magenta, CRGB::Turquoise, CRGB::Lavender,
    CRGB::Chartreuse, CRGB::Teal, CRGB::Gold, CRGB::SkyBlue
};

const TProgmemPalette16 vibrantWave PROGMEM = {
    CRGB::Cyan, CRGB::Magenta, CRGB::Yellow, CRGB::LimeGreen,
    CRGB::Pink, CRGB::Purple, CRGB::Red, CRGB::Orange,
    CRGB::Turquoise, CRGB::DeepSkyBlue, CRGB::Teal, CRGB::Fuchsia,
    CRGB::Gold, CRGB::HotPink, CRGB::Lavender, CRGB::Aqua
};

const TProgmemPalette16 sunsetGlow PROGMEM = {
    CRGB::Red, CRGB::Orange, CRGB::Gold, CRGB::Magenta,
    CRGB::HotPink, CRGB::Purple, CRGB::Violet, CRGB::Blue,
    CRGB::Turquoise, CRGB::Fuchsia, CRGB::Yellow, CRGB::Crimson,
    CRGB::Lime, CRGB::Coral, CRGB::LightPink, CRGB::PeachPuff
};

const TProgmemPalette16 festiveGlow PROGMEM = {
    CRGB::Red, CRGB::Gold, CRGB::Green, CRGB::Crimson,
    CRGB::Orange, CRGB::Coral, CRGB::HotPink, CRGB::Violet,
    CRGB::Yellow, CRGB::DeepPink, CRGB::Turquoise, CRGB::Magenta,
    CRGB::Fuchsia, CRGB::Purple, CRGB::LimeGreen, CRGB::PeachPuff
};

const TProgmemPalette16 hallucinogenicSunrise PROGMEM = {
    CRGB::Red, CRGB::Orange, CRGB::Yellow, CRGB::Pink,
    CRGB::Purple, CRGB::Lime, CRGB::Fuchsia, CRGB::Turquoise,
    CRGB::HotPink, CRGB::Gold, CRGB::Crimson, CRGB::MediumPurple,
    CRGB::Teal, CRGB::Magenta, CRGB::Green, CRGB::SkyBlue
};

// Updated array of palettes
const TProgmemPalette16* palettes[] = {
    &auroraBorealis, &candyCrush, &galaxyDream, &neonVibes, &ultravioletDreams, 
    &psychedelicSunset, &miamiVice, &electricDreams, &alienJungle, &neonGalaxy, 
    &acidTrip, &lavaLamp, &cosmicDream, &festiveGlow, &meltedCandy, 
    &digitalVortex, &toxicGlow, &popArt, &rainbowCandy, &cyberGlow, 
    &funkyDisco, &psychedelicDream, &tropicalSunset, &cosmicWaves, 
    &electricCarnival, &neonParadise, &cyberwave, &vibrantWave, &sunsetGlow,
    &dmtDream, &psyTrance, &acidWave, &hallucinogenicSunrise
};

// Variable to track current palette
int currentPaletteIndex = 0;
// Get the current palette
CRGBPalette16 currentPalette = *palettes[currentPaletteIndex];

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { off, psyTrain, snakeCyclePalettes, palettesGlitter, rainbowWithGlitter, confetti,  bpm, sinelon, juggle, rainbow, colorComet, fireworks, waveform, plasmaEffect, pulse, palettesMarch, snake,  snakeComet, trippysnake, palettesSplits, psypoliceLights, fireflyEffect, UV, solidUV, solidWhite };

// Store pattern names in PROGMEM to save RAM
const char pattern0[] PROGMEM = "off";
const char pattern1[] PROGMEM = "psyTrain";
const char pattern2[] PROGMEM = "snakeCyclePalettes";
const char pattern3[] PROGMEM = "palettesGlitter";
const char pattern4[] PROGMEM = "rainbowWithGlitter";
const char pattern5[] PROGMEM = "confetti";
const char pattern6[] PROGMEM = "bpm";
const char pattern7[] PROGMEM = "sinelon";
const char pattern8[] PROGMEM = "juggle";
const char pattern9[] PROGMEM = "rainbow";
const char pattern10[] PROGMEM = "colorComet";
const char pattern11[] PROGMEM = "fireworks";
const char pattern12[] PROGMEM = "waveform";
const char pattern13[] PROGMEM = "plasmaEffect";
const char pattern14[] PROGMEM = "pulse";
const char pattern15[] PROGMEM = "palettesMarch";
const char pattern16[] PROGMEM = "snake";
const char pattern17[] PROGMEM = "snakeComet";
const char pattern18[] PROGMEM = "trippysnake";
const char pattern19[] PROGMEM = "palettesSplits";
const char pattern20[] PROGMEM = "psypoliceLights";
const char pattern21[] PROGMEM = "fireflyEffect";
const char pattern22[] PROGMEM = "UV";
const char pattern23[] PROGMEM = "solidUV";
const char pattern24[] PROGMEM = "solidWhite";

// Array of pattern name pointers stored in PROGMEM
const char* const patternNames[] PROGMEM = {
  pattern0, pattern1, pattern2, pattern3, pattern4, pattern5, pattern6, pattern7, pattern8, pattern9, pattern10, pattern11, pattern12, pattern13, pattern14, 
  pattern15, pattern16, pattern17, pattern18, pattern19, pattern20, pattern21, pattern22, pattern23, pattern24
};


uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

#define DATA_PIN    13
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    300
CRGB leds[NUM_LEDS];

#define BRIGHTNESS  128 // 96
#define ONBOARD_LED 1 // pin 1 is onboard LED
#define ONBOARD_BTN 0 // pin 0 is "boot" button on ESP32

//#define COOLING 55 // For Fire Animation
//#define SPARKING 120 // For Fire Animation

// Time thresholds
#define DEBOUNCE_DELAY 5     // Debounce delay in milliseconds - Too short = multiple clicks quickly
#define LONG_CLICK_THRESHOLD 300  // Maximum time for double-click detection - Higher number = less sensitivity
#define OFF_DELAY 2000 // 2000ms = 2 seconds


// Button press tracking
unsigned long buttonPressedTime = 0;
unsigned long buttonReleaseTime = 0;

// Button press detection
void checkButton() {
  if (!digitalRead(ONBOARD_BTN)) {
    digitalWrite(ONBOARD_LED, LOW);
    buttonPressedTime = millis();
    
    while (!digitalRead(ONBOARD_BTN)) {
      delay(DEBOUNCE_DELAY);  // Debounce the button
    }
    
    buttonReleaseTime = millis();
    digitalWrite(ONBOARD_LED, HIGH);
    
    if (buttonReleaseTime - buttonPressedTime < LONG_CLICK_THRESHOLD) {
      gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
    } 
    else if (buttonReleaseTime - buttonPressedTime < OFF_DELAY) {
      gCurrentPatternNumber = (gCurrentPatternNumber - 1 + ARRAY_SIZE(gPatterns)) % ARRAY_SIZE(gPatterns);
    } 
    else {
      gCurrentPatternNumber = 0;  // Reset to first pattern (off)
    }

    // Retrieve and print the pattern name from PROGMEM
    char buffer[30];  // Create a buffer to hold the string from PROGMEM
    strcpy_P(buffer, (char*)pgm_read_word(&(patternNames[gCurrentPatternNumber])));  // Copy from PROGMEM
    Serial.print("Current Pattern Number: ");
    Serial.println(gCurrentPatternNumber);
    Serial.print("Current Pattern Name: ");
    Serial.println(buffer);
  }
}



void setup() {

  // Serial debug - temporary
  Serial.begin(9600);
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
 
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
   
  // Turn off the LEDs initially
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  
  // Setup button and onboard LED
  //pinMode(ONBOARD_BTN, INPUT);
  pinMode(ONBOARD_BTN, INPUT_PULLUP);  // Use INPUT_PULLUP for better reliability on pin 0
  pinMode(ONBOARD_LED, OUTPUT);
  digitalWrite(ONBOARD_LED, HIGH);  // onboard LED is inverted

  Serial.println("Ready");
}


void loop()
{
  // Check for button press
  checkButton();

  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // slow down - later
  //FastLED.delay(1000/FRAMES_PER_SECOND); 

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  

  // do some periodic updates
  EVERY_N_MILLISECONDS( 1 ) { gHue++; } // slowly cycle the "base color" through the rainbow

}



// All patterns below
void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(120); //80
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void psyTrain() {
    // Train effect variables
    static int minTrainLength = 15; // Minimum train's lenght
    static int maxTrainLength = 299; // Maximum train's lenght
    static int trainLength = random(minTrainLength, maxTrainLength); // Randomizing min & max lenght  // Random Length of the train
    static int trainSpeed = 25;  // train speed (lower = faster, higher = slower)
    static int trainHeadPos = 0;  // Position of the trains's head
    static int tdirection = 1;     // Direction: 1 for right, -1 for left

    int currentPaletteIndex = 0;  // Index for the custom palette array
    static uint8_t startIndex = 0;  // Palette index within the palette
    
    // Dynamic train speed control using a sine wave
    uint8_t speedVariation = sin8(millis() / 20);  // Dynamic speed variation
    trainSpeed = map(speedVariation, 0, 255, 5, 65);  // train speed varies between 5ms and 65ms delay

    // Get the current palette
    CRGBPalette16 currentPalette = *(palettes[currentPaletteIndex]);

    // Create fading trail for the train
    fadeToBlackBy(leds, NUM_LEDS, 20);  // Faster fading for a smoother trail
    
    // Draw the train using the current palette
    for (int i = 0; i < trainLength; i++) {
        int pos = (trainHeadPos - i * tdirection + NUM_LEDS) % NUM_LEDS;  // Wrap the train's position around the LED strip
        if (pos >= 0 && pos < NUM_LEDS) {  // Ensure position is within the LED strip bounds
            // Randomize brightness dynamically for each segment
            uint8_t brightness = sin8(millis() / 5 + i * 50);  // Pulsing brightness for each segment

            // Flickering effect for certain train segments
            if (random8() > 200) {
                brightness = 255;  // Occasionally, make segments very bright
            }

            // Color the train using the palette
            leds[pos] = ColorFromPalette(currentPalette, startIndex + random8(0, 5) * (i * 2), brightness, LINEARBLEND);
        }
    }

    // Update the train head position, allowing direction reversal at random
    trainHeadPos = (trainHeadPos + tdirection + NUM_LEDS) % NUM_LEDS;

    // Randomly reverse the train's direction every few passes
    if (random8() > 245 && trainHeadPos % 100 == 0) {
        tdirection *= -1;  // Reverse direction
    }

    // Gradually increment the palette index for smooth color transition
    startIndex += 1;  // Increase for faster palette transitions

    // Show the LEDs
    FastLED.show();

    // Add a small delay to control the speed
    delay(trainSpeed);  // Adjust for speed of the train movement

    // Change the palette and randomize train length after a full pass
    if (trainHeadPos == 0) {
        currentPaletteIndex = (currentPaletteIndex + 1) % (sizeof(palettes) / sizeof(palettes[0]));  // Switch palette

        // Randomize train length between mintrainLength and maxtrainLength
        trainLength = random(minTrainLength, maxTrainLength);
    }
}

void palettesMarch() {
    static uint8_t startIndex = 0;
    startIndex += 10; // Adjust for faster/slower palette movement

    // Change palette every half second
    EVERY_N_SECONDS(2) {
        currentPaletteIndex = (currentPaletteIndex + 1) % (sizeof(palettes) / sizeof(palettes[0]));
    }

    // Get the current palette
    CRGBPalette16 currentPalette = *(palettes[currentPaletteIndex]);

    // March the colors across the strip using the palette
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(currentPalette, startIndex + i * 6, 255, LINEARBLEND);
    }
    FastLED.show();  // Ensure the LEDs update
    FastLED.delay(15); // Adjust for speed (15ms delay)
}

// New glitter function that overlays the glitter without disturbing the base pattern
void addPGlitterOverlay(uint8_t chance) {
    if (random8() < chance) {
        int pos = random16(NUM_LEDS);  // Pick a random LED
        CRGB glitterColor = CHSV(random8(), 255, random8(128, 255)); // Random hue, random brightness

        // Overlay glitter without changing the base pattern permanently
        leds[pos] = leds[pos] + glitterColor;  // Add glitter temporarily by blending with the base color
    }

    // Apply fade to the glitter overlay only, to give it a fading effect
    uint8_t fadeAmount = random8(1, 10);  // Random fading from slow to fast (lower values to avoid drastic fading)
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].fadeToBlackBy(fadeAmount);  // Apply gentle fading
    }
}

// Function to reverse the palette and create bright glitter
void addPGlitterWithReversedPalette(uint8_t chance) {
    CRGBPalette16 currentPalette = *(palettes[currentPaletteIndex]);
    CRGBPalette16 reversedPalette;

    // Reverse the current palette for glitter effect
    for (int i = 0; i < 16; i++) {
        reversedPalette[i] = currentPalette[15 - i]; // Reverse the palette
    }

    // Add glitter more frequently and make it brighter
    if (random8() < chance) {
        int pos = random16(NUM_LEDS);  // Pick a random LED
        uint8_t colorIndex = random8(); // Random index for glitter color from reversed palette

        // Brighter glitter from reversed palette
        CRGB glitterColor = ColorFromPalette(reversedPalette, colorIndex, 255); // Full brightness for glitter

        // Blend the glitter color with the current LED color
        leds[pos] += glitterColor;
    }

    // Apply fade to give glitter a fading effect without ruining the base pattern
    uint8_t fadeAmount = random8(5, 10);  // Keep fading gentle (range 5-10)
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].fadeToBlackBy(fadeAmount);  // Apply fading
    }
}


void palettesGMarch(uint8_t glitterChance) {
    static float startIndex = 0;
    
    // Use a sine wave to create non-linear movement (trippy movement)
    float speedFactor = (sin(millis() / 35.0) + 1) / 2;  // Create smooth speed variations between 0 and 1
    startIndex += 0.2 + (speedFactor * 0.3);  // Adjust base speed and speed factor to vary movement

    // Change palette every 16 seconds
    EVERY_N_SECONDS(35) {
        currentPaletteIndex = (currentPaletteIndex + 1) % (sizeof(palettes) / sizeof(palettes[0]));
    }

    // Get the current palette
    CRGBPalette16 currentPalette = *(palettes[currentPaletteIndex]);

    // Create a wave-like color movement across the strip using the palette
    for (int i = 0; i < NUM_LEDS; i++) {
        // Make the color index move with a sine wave pattern for more trippy motion
        float waveOffset = sin(i / 35.0 + millis() / 4500.0) * 55.0;  // Wave effect with sin()
        float colorIndex = startIndex + (i * 0.2) + waveOffset;       // Combine movement and wave effect

        // Apply color from the palette with smooth blending
        leds[i] = ColorFromPalette(currentPalette, (int)colorIndex % 255, 255, LINEARBLEND);
    }

    // Add brighter, more frequent glitter using the reversed palette
    addPGlitterWithReversedPalette(glitterChance);   // Add glitter with a reversed custom palette
    FastLED.show();                      // Show the updated LED strip
    FastLED.delay(20);                   // Small delay to allow smooth transitions
}

void palettesGlitter() {
    // Execute the palette march with brighter, frequent glitter
    palettesGMarch(255);  // Increase glitter chance for more frequent glitter
}

void confetti() {
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(39,0,NUM_LEDS); //13
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 142; // 42
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 23); // 20
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 220, 255); // CHSV(dothue, 200, 255)
    dothue += 42; //32
  }
}


void waveform() {
  // Added 25/9/24 - J.S
  // A wave pattern moves down the strip with a sin wave-like motion
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(sin8(i * 10 + millis() / 16), 255, 255);  // waveform with color
  }
}

void plasmaEffect() {
// Added 25/9/24 - J.S
// A plasma-like noise effect that changes and evolves over time.
for (int i = 0; i < NUM_LEDS; i++){
  uint8_t noise = inoise8(i * 10, millis() / 10);  // generate noise over time
  leds[i] = CHSV(noise, 255, 255);  // map noise to color
  }
}

void psypoliceLights() {
  // Added 25/9/24 - J.S
  // Alternating blue and red flashes, simulating police lights.
  // Set up a UV-like color pattern
  // Updated UV-like police lights with stronger colors and corrections
  static int currentPaletteIndex = 0;     // Track current palette
  static unsigned long previousMillis = 0;  // Timing variable for color transitions
  const long interval = 2000;  // Time between palette changes (2 seconds)

  // Get the current time
  unsigned long currentMillis = millis();

  // Check if enough time has passed to switch palettes
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the time for the next transition
    currentPaletteIndex = (currentPaletteIndex + 1) % 33;  // Cycle through the palettes
  }

  // Create a dynamic moving wave pattern
  for (int i = 0; i < NUM_LEDS; i++) {
  // Get color from palette and map it to the position for a moving effect
  uint8_t colorIndex = (i * 255 / NUM_LEDS + millis() / 10) % 255;
  leds[i] = ColorFromPalette(currentPalette, colorIndex);
  }

  // Random twinkles for added psychedelic effect
  if (random8() < 20) {
    leds[random16(NUM_LEDS)] = CRGB::White;  // Random flash of white
  }

  // Smooth fade effect
  fadeToBlackBy(leds, NUM_LEDS, 15);
  
  // Slight delay to make the effect feel more dynamic
  FastLED.delay(30);

 // fill_solid(leds, NUM_LEDS, CRGB::Black);  // Turn all LEDs off for a pause
 // FastLED.show();  // Show blackout
 // FastLED.delay(128);  // Pause before next flash
}


void fireworks() {
  // Added 25/9/24 - J.S
  // LEDs light up like fireworks, starting from a central point and exploding outward.
  // Key Functions: random16() for random explosion points, fadeToBlackBy() for the trailing effect.
  // Improved fireworks simulation with multiple explosions and velocity
  fadeToBlackBy(leds, NUM_LEDS, 15);  // Fade the entire strip slowly for trailing effect
  
  static unsigned long previousMillis = 0;  
  const long interval = 200;  // Minimum time between each new firework
  
  // Check if enough time has passed to launch a new firework
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Choose a random center for the explosion
    int center = random16(NUM_LEDS);
    uint8_t explosionColor = random8();  // Random hue for the explosion color
    
    // Set the center to full brightness
    leds[center] = CHSV(explosionColor, 255, 255);
    
    // Number of fragments per firework (you can tweak this for size)
    int numFragments = random8(5, 15);  // Randomize number of explosion fragments

    // Set velocity and decay for each fragment
    for (int i = 1; i <= numFragments; i++) {
      // Calculate the position of each fragment, expanding from the center
      int fragmentPosForward = (center + i) % NUM_LEDS;
      int fragmentPosBackward = (center - i + NUM_LEDS) % NUM_LEDS;
      
      // Use diminishing brightness for further fragments, simulating a fading explosion
      uint8_t brightness = 255 - (i * (255 / numFragments));  // Fades out with distance
      
      // Set the colors of fragments moving outward from the center
      leds[fragmentPosForward] += CHSV(explosionColor, 255, brightness);  // Fragment moving right
      leds[fragmentPosBackward] += CHSV(explosionColor, 255, brightness); // Fragment moving left
    }
  }
  
  // Twinkling effect on trailing firework fragments (random glitter)
  if (random8() < 20) {
    leds[random16(NUM_LEDS)] += CRGB::White;  // Add a bright twinkle randomly
  }
}

void colorComet() {
  // Added 25/9/24 - J.S
  // Fade the entire strip to create comet's trail
  fadeToBlackBy(leds, NUM_LEDS, 15);  // Faster fading for a smoother trail
  
  // Comet position moves with time, creating the effect of motion
  static uint16_t cometPos = 0;
  //static int cometSpeed = 5;  // Speed of comet (larger value means slower)
  cometPos = (cometPos + 1) % NUM_LEDS;  // Move comet position
  
  // Random color shift with palette or CHSV
  static uint8_t colorOffset = 0;
  colorOffset += random8(2, 5);  // Vary color speed slightly for more randomness
  leds[cometPos] = CHSV(colorOffset, 255, 255);  // Color of the comet's head
  
  // Create a trailing tail with brightness decay
  for (int i = 1; i <= 20; i++) {  // Adjust tail length here
    int pos = (cometPos - i + NUM_LEDS) % NUM_LEDS;  // Ensure the position wraps around
    uint8_t brightness = 255 - (i * (255 / 20));     // Gradual brightness fade
    leds[pos] = CHSV(colorOffset + i * 8, 255, brightness);  // Gradually shift the color in the tail
  }

  // Add sparkles to the trail for more visual interest
  if (random8() < 40) {
    int sparklePos = (cometPos - random8(1, 10) + NUM_LEDS) % NUM_LEDS;  // Position for sparkle
    leds[sparklePos] = CRGB::White;  // Bright white sparkle
  }
  FastLED.delay(10);
}

void pulse() {
  // Added 25/9/24 - J.S
  // LEDs light up from the center outwards, then back inward, like a pulse.
  static int pulseWidth = 0;
  static int direction = 1;
  static uint8_t currentPaletteIndex = 0;



  // Clear the strip
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  // Calculate the center
  int center = NUM_LEDS / 2;

  // Create the pulse effect using the current palette
  for (int i = 0; i < pulseWidth; i++) {
    // Get color from palette
    uint8_t paletteIndex = map(i, 0, NUM_LEDS / 2, 0, 255);  // Map to palette range
    CRGB color = ColorFromPalette(currentPalette, paletteIndex);  // Retrieve color from palette

    if (center - i >= 0) leds[center - i] = color;  // Pulse to the left
    if (center + i < NUM_LEDS) leds[center + i] = color;  // Pulse to the right
  }

  // Increase or decrease the pulse width
  pulseWidth += direction;
  if (pulseWidth == NUM_LEDS / 2 || pulseWidth == 0) {
    direction = -direction;  // Reverse direction when the pulse reaches the edges
  }

  // Change to the next palette when the pulse is fully reset (at the edges)
  if (pulseWidth == 0) {
    currentPaletteIndex = (currentPaletteIndex + 1) % 18;  // Cycle through 10 palettes
  }
  FastLED.delay(5);  // Adjust delay for pulse speed
}


void snake() {
  // Added 25/9/24 - J.S
  //  "snake" of light moves across the strip, growing longer as it moves.
  unsigned long previousMillis = 0;  // Stores the last time the snake was updated
  const long interval = 30;          // Speed of the snake (30ms between updates)

  static int snakeLength = 1;   // Start with snake length of 1
  static int pos = 0;           // Position of the snake's head
  static int direction = 1;     // 1 for forward, -1 for reverse (bouncing effect)

  // Check if enough time has passed since the last update
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the current time for the next interval

    fill_solid(leds, NUM_LEDS, CRGB::Black);  // Clear the strip

    // Draw the snake with the current length and color
    for (int i = 0; i < snakeLength; i++) {
      int currentPos = (pos - i + NUM_LEDS) % NUM_LEDS;  // Ensure the snake wraps around the strip
      uint8_t hue = map(i, 0, 299, 0, 255);  // Spread colors evenly across the snake's length
      leds[currentPos] = CHSV(hue, 255, 255);  // Assign color to each segment of the snake
    }

    // Move the snake in the current direction
    pos += direction;

    // Bounce the snake when it reaches either end
    if (pos >= NUM_LEDS || pos < 0) {
      direction = -direction;  // Reverse direction when snake hits the end
      pos += direction;  // Ensure the snake stays within bounds after bouncing
    }

    // Increase snake length until it reaches 200
    if (snakeLength < 299) {
      snakeLength++;  // Add a new segment with each full pass
    }
  }
}

void snakeCyclePalettes() {
  // Added 29/9/24 - J.S

// Snake effect variables
static int minSnakeLength = 1;
static int maxSnakeLength = 299;
static int snakeLength = random(minSnakeLength, maxSnakeLength);  // Random Length of the snake
static int snakeSpeed = 25;        // Delay between updates (speed of the snake. Lower values make it faster, and higher values make it slower.)
static int snakeHeadPos = 0;  // Position of the snake's head
//static int direction = 1;     // 1 for right, -1 for left

int currentPaletteIndex = 0;  // Index for custom palette array
static uint8_t startIndex = 0;  // Palette index within the palette
    
// Get the current palette
CRGBPalette16 currentPalette = *(palettes[currentPaletteIndex]);

// Clear the LEDs before drawing the snake
//FastLED.clear();
// Fade the entire strip to create the snake's trail
  fadeToBlackBy(leds, NUM_LEDS, 15);  // Faster fading for a smoother trail
  
    // Draw the snake using the current palette
    for (int i = 0; i < snakeLength; i++) {
        int pos = (snakeHeadPos - i + NUM_LEDS) % NUM_LEDS;  // Wrap the snake's position around the LED strip
        if (pos >= 0 && pos < NUM_LEDS) {  // Ensure position is within the LED strip bounds
            // Get a color from the palette, and use the snake's head position to control the color index
            // Pulsing effect by dynamically adjusting the brightness based on a sine wave
            uint8_t brightness = sin8(millis() / 5);  // Use sine wave for brightness pulsing
            leds[pos] = ColorFromPalette(currentPalette, startIndex + (i * 2), brightness, LINEARBLEND);
        }
    }

    // Update the snake head position (wrap around the LED strip using modulo)
    snakeHeadPos = (snakeHeadPos + 1) % NUM_LEDS;

    // Gradually increment the palette index for smooth color transition
    startIndex += 1;  // Increase for faster palette transitions

    // Show the LEDs
    FastLED.show();

    // Add a small delay to control speed
    delay(snakeSpeed);  // Adjust for speed of the snake movement

    // Change the palette and randomize snake length after a full pass
    if (snakeHeadPos == 0) {
        currentPaletteIndex = (currentPaletteIndex + 1) % (sizeof(palettes) / sizeof(palettes[0])); // Switch palette

        // Randomize snake length between minSnakeLength and maxSnakeLength
        snakeLength = random(minSnakeLength, maxSnakeLength);
    }
}

void snakeComet() {
  //Added 29/9/24 - J.S

  static int snakeLength = 1;   // Start with snake length of 1
  static int pos = 0;           // Position of the snake's head
  
  // Fade the entire strip to create the snake's trail
  fadeToBlackBy(leds, NUM_LEDS, 15);  // Faster fading for a smoother trail
  
  // Random color shift for comet-like behavior
  static uint8_t colorOffset = 0;
  colorOffset += random8(2, 5);  // Vary color speed slightly for more randomness
  
  // Draw the snake with the current length and comet effect
  for (int i = 0; i < snakeLength; i++) {
    int currentPos = (pos - i + NUM_LEDS) % NUM_LEDS;  // Ensure the snake wraps around the strip
    uint8_t hue = map(i, 0, snakeLength - 1, 0, 255);  // Spread colors evenly across the snake's length
    
    // Add a flickering comet-like effect to each segment of the snake
    uint8_t brightness = 255 - (i * (255 / snakeLength));  // Gradual brightness fade for the trail
    leds[currentPos] = CHSV(colorOffset + hue, 255, brightness);  // Assign color to each segment of the snake
  }

  // Move the snake by updating the head position
  pos++;
  if (pos >= NUM_LEDS) {
    pos = 0;  // Wrap around when reaching the end of the strip
    
    // Increase snake length until it reaches 299
    if (snakeLength < 299) {
      snakeLength++;  // Add a new segment with each full pass
    }
  }

  // Add comet-like sparkles to random positions in the snake's tail
  if (random8() < 40) {  // 40% chance for a sparkle
    int sparklePos = (pos - random8(1, snakeLength) + NUM_LEDS) % NUM_LEDS;  // Randomize sparkle position within the snake's body
    leds[sparklePos] = CRGB::White;  // Bright white sparkle for the flickering effect
  }
  FastLED.delay(10);  // Adjust delay for snake speed
}

void trippysnake() {
  // Added 25/9/24 - J.S
  // "Snake" of light moves across the strip, growing longer as it moves.
  static unsigned long previousMillis = 0;  // Stores the last time the snake was updated
  const long interval = 5;  // Speed of the snake (30ms between updates)

  static int snakeLength = 1;   // Start with snake length of 1
  static int pos = 0;           // Position of the snake's head
  static int direction = -1;    // 1 for forward, -1 for reverse (bouncing effect)

  // Check if enough time has passed since the last update
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the current time for the next interval

    fill_solid(leds, NUM_LEDS, CRGB::Black);  // Clear the strip

  // Draw the snake with the current length and palette
    for (int i = 0; i < snakeLength; i++) {
      int currentPos = (pos - i + NUM_LEDS) % NUM_LEDS;  // Ensure the snake wraps around the strip
      uint8_t colorIndex = map(i, 0, 299, 0, 255);       // Spread colors evenly across the snake's length
      leds[currentPos] = ColorFromPalette(currentPalette, colorIndex);  // Assign color from the palette
    }

    // Move the snake in the current direction
    pos += direction;

    // Bounce the snake when it reaches either end
    if (pos >= NUM_LEDS || pos < 0) {
      direction = -direction;  // Reverse direction when snake hits the end
      pos += direction;        // Ensure the snake stays within bounds after bouncing
    }

    // Increase snake length until it reaches 300
    if (snakeLength < 300 && pos == 0) {
      snakeLength++;  // Add a new segment with each full pass
    }

    // Switch palette when snake reaches full size
    if (snakeLength == 300) {
      currentPaletteIndex = (currentPaletteIndex + 1) % 10;  // Cycle through the 10 palettes
      snakeLength = 1;  // Reset snake length after reaching the full size
    }
  }
}

void palettesSplits() {
  // Key Features:
  // Three Waves: We'll divide the LED strip into three sections, each showing a palette pattern.
  // Different Frequencies: Each wave will have a different speed or frequency, which makes them move at varying rates.
  // Bouncing Effect: Each section will "bounce" back when it reaches the edge of the strip, creating a reflective, back-and-forth motion.

  int pos1 = 0, pos2 = 0, pos3 = 0;
  int direction1 = 1, direction2 = 1, direction3 = 1;  // Direction for bouncing (1 for forward, -1 for reverse)
  unsigned long previousMillis1 = 0, previousMillis2 = 0, previousMillis3 = 0;  // Timing variables for each wave
  const long interval1 = 15;  // Speed of wave 1
  const long interval2 = 50;  // Speed of wave 2
  const long interval3 = 15;  // Speed of wave 3

  // Clear the strip
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  // Get the current time
  unsigned long currentMillis = millis();

  // Update wave 1 (left section)
  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;  // Save the last update time
    pos1 += direction1;  // Move the wave

    if (pos1 >= NUM_LEDS / 3 || pos1 <= 0) {
      direction1 = -direction1;  // Reverse direction when it hits the boundaries of its section
    }

    // Apply the palette to the first third of the strip
    for (int i = 0; i < NUM_LEDS / 3; i++) {
      // Get a color from palette1 and map it to the LED position
      leds[(pos1 + i) % NUM_LEDS] = ColorFromPalette(neonParadise, i * 255 / (NUM_LEDS / 3));
    }
  }

  // Update wave 2 (middle section)
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;
    pos2 += direction2;

    if (pos2 >= 2 * NUM_LEDS / 3 || pos2 <= NUM_LEDS / 3) {
      direction2 = -direction2;
    }

    // Apply the palette to the second third of the strip
    for (size_t i = NUM_LEDS / 3; i < 2 * NUM_LEDS / 3; i++) {
      // Get a color from palette2 and map it to the LED position
      leds[(pos2 + i) % NUM_LEDS] = ColorFromPalette(neonVibes, (i - NUM_LEDS / 3) * 255 / (NUM_LEDS / 3));
    }
  }

  // Update wave 3 (right section)
  if (currentMillis - previousMillis3 >= interval3) {
    previousMillis3 = currentMillis;
    pos3 += direction3;

    if (pos3 >= NUM_LEDS || pos3 <= 2 * NUM_LEDS / 3) {
      direction3 = -direction3;
    }

    // Apply the palette to the last third of the strip
    for (int i = 2 * NUM_LEDS / 3; i < NUM_LEDS; i++) {
      // Get a color from palette3 and map it to the LED position
      leds[(pos3 + i) % NUM_LEDS] = ColorFromPalette(ultravioletDreams, (i - 2 * NUM_LEDS / 3) * 255 / (NUM_LEDS / 3));
    }
  }
}

void UV() {
  // Define the colors for the UV effect
  CRGB deepPurple = CRGB(75, 0, 130);   // Simulated UV purple
  CRGB deepBlue = CRGB(0, 0, 255);      // Deep blue for stronger effect
  CRGB vibrantPink = CRGB(255, 0, 100); // Subtle pink accents

  // Randomly dim the brightness of the entire strip to simulate a UV flicker
  uint8_t flicker = random8(230, 255);  // Flicker between 90% and 100% brightness

  // Apply a gradient pattern across the LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    // Create a subtle gradient between deep purple, blue, and pink
    if (i % 3 == 0) {
      leds[i] = deepPurple;
    } else if (i % 3 == 1) {
      leds[i] = deepBlue;
    } else {
      leds[i] = vibrantPink;
    }
    // Apply flicker effect to simulate UV's dim pulse
    leds[i].fadeLightBy(flicker);
  }

  // Add a slow pulsing effect (similar to UV lights warming up)
  static uint8_t brightnessPulse = 0;
  brightnessPulse += 3;  // Increase pulse for each loop
  FastLED.setBrightness(sin8(brightnessPulse));  // Use sine wave for smooth pulse effect

  FastLED.delay(25);  // Delay to smooth out the pulse
}

void fireflyEffect() {
    for (int i = 0; i < NUM_LEDS; i++) {
        if (random8() < 20) { // Random chance for a firefly
            leds[i] = ColorFromPalette(neonVibes, random8(), 255, LINEARBLEND);
        } else {
            leds[i].fadeToBlackBy(20); // Gradual fade out
        }
    }
    FastLED.delay(30);
}

void paletteStrobe() {
    fill_solid(leds, NUM_LEDS, CRGB::Black); // Turn all LEDs off
    FastLED.show();
    delay(25); // Control strobe speed

    fill_palette(leds, NUM_LEDS, 0, 255 / NUM_LEDS, *(palettes[currentPaletteIndex]), 255, LINEARBLEND);
    FastLED.show();
    delay(75);
}

void solidUV() {
    fill_solid( leds, NUM_LEDS, CRGB::Blue);
  FastLED.delay(100); 
}

void solidWhite() {
  fill_solid( leds, NUM_LEDS, CRGB::White );
  FastLED.delay(100); 
}

void off() {
  FastLED.clear();
  FastLED.delay(100); 
}