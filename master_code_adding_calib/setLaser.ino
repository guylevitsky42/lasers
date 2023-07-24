void setLaser(int index, int brigthness) {
  int expenderIndex = index / 3;
  int modulePin = (index % 3) ;

  CRGB color = laserExpander[expenderIndex];

  laserExpander[expenderIndex] = CRGB(modulePin == 0 ? brigthness : color.red, modulePin == 1 ? brigthness : color.green, modulePin == 2 ? brigthness : color.blue);

  FastLED.show();
}
