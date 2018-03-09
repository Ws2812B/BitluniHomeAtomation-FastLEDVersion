/*
Released under Creative Commons Attribution 4.0
by bitluni 2016
https://creativecommons.org/licenses/by/4.0/
Attribution means you can use it however you like as long you
mention that it's base on my stuff.
I'll be pleased if you'd do it by sharing http://youtube.com/bitlunislab
*/

#include <ESP8266WebServer.h>
#include "LedFunction.h"

const int MAX_LED_COUNT = 300;

class LedStates
{
  public:
  uint8_t values[MAX_LED_COUNT][3] = {{0}};
  int count = 0;
  bool dirty = false;
  LedFunction *function = 0;
	CRGB *leds;

  LedStates(CRGB *ledss, int numLeds)
  {
    count = numLeds;
		leds = ledss;
  }

  void setFunction(LedFunction *newFunction)
  {
    if(function)
      delete function;
    function = newFunction;
    if(!function)
      return;
    function->state = this;
  }

  void setRgb(int i, uint8_t r, uint8_t g, uint8_t b)
  {
    values[i][0] = r;
    values[i][1] = g;
    values[i][2] = b;
    dirty = true;
  }

  virtual void render()
  {
    if(function)
      function->render();
  }

  void setValues(LedStates &to)
  {
    for(int i = 0; i < count; i++)
      for(int j = 0; j < 3; j++)
        values[i][j] = to.values[i][j];
    setFunction(to.function);
    to.function = 0;
    dirty = true;
  }

  void commit()
  {
    if(!dirty)
      return;
    for(int i = 0; i < count; i++) {
      leds[i].r = values[i][0];
			leds[i].g = values[i][1];
			leds[i].b = values[i][2];
    }
		FastLED.show();
    dirty = false;
  }

  void fade(LedStates &to, long f0, long f1)
  {
		for (int i = 0; i < count; i++) {
			leds[i].r = values[i][0];
			leds[i].g = values[i][1];
			leds[i].b = values[i][2];
		}
    FastLED.show();
    dirty = true;
  }
};

