#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I²C OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Center of the atom on the 128×64 screen
const int centerX = SCREEN_WIDTH / 2;   // 64
const int centerY = SCREEN_HEIGHT / 2;  // 32

// Nucleus (three nucleons) configuration
const int nucleusRadius = 4;  // radius of each proton/neutron dot
const int offset = 5;         // offset between nucleus dots

// Electron orbit configuration
const int orbitRadius = 26;    // how far the electron orbits from center
const int electronRadius = 2;  // radius of the electron dot

// Animation timing
const int totalFrames = 30;
const float angleIncrement = 360.0 / totalFrames;  // degrees per frame
const int frameDelay = 33;   // ~30 FPS (33ms per frame)

void setup() {
  // Initialize I²C and OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  static float angleDeg = 0.0;

  // Clear the OLED buffer
  display.clearDisplay();

  // 1) Draw the electron's circular orbit (wireframe)
  display.drawCircle(centerX, centerY, orbitRadius, SSD1306_WHITE);

  // 2) Draw the nucleus (three filled circles clustered around center)
  //    - One proton/neutron in the middle
  display.fillCircle(centerX, centerY, nucleusRadius, SSD1306_WHITE);
  //    - Two others positioned diagonally below
  display.fillCircle(centerX - offset, centerY + offset, nucleusRadius, SSD1306_WHITE);
  display.fillCircle(centerX + offset, centerY + offset, nucleusRadius, SSD1306_WHITE);

  // 3) Compute electron position along its orbit
  float theta = angleDeg * (PI / 180.0f);
  int electronX = centerX + round(orbitRadius * cos(theta) );
  int electronY = centerY + round(orbitRadius * sin(theta) );

  // 4) Draw the electron as a filled circle
  display.fillCircle(electronX, electronY, electronRadius, SSD1306_WHITE);

  // 5) Send the buffer to the OLED
  display.display();

  // 6) Advance the angle for the next frame
  angleDeg += angleIncrement;
  if (angleDeg >= 360.0) {
    angleDeg -= 360.0;
  }

  // 7) Delay to achieve ~30 FPS
  delay(frameDelay);
}