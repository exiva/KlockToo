#include <pebble.h>

static Window *window;
static TextLayer *text_layer;

//hours
static const char* _HONE = "one";
static const char* _HTWO = "two";
static const char* _HTHREE = "three";
static const char* _HFOUR = "four";
static const char* _HFIVE = "five";
static const char* _HSIX = "six";
static const char* _HSEVEN = "seven";
static const char* _HEIGHT = "eight";
static const char* _HNINE = "nine";
static const char* _HTEN = "ten";
static const char* _HELEVEN = "eleven";
static const char* _HTWELVE = "twelve";

//minutes
static char* _MFIVE = "five";
static const char* _MTEN = "ten";
static const char* _MQUARTER = "quarter";
static const char* _MTWENTY = "twenty";
static const char* _MTWENTYFIVE = "twenty five";
static const char* _MHALF = "half";

// //misc
static const char* _PAST = "past";
static const char* _TO = "to";
static const char* _OCLOCK = "o'clock";

static void window_load(Window *window) {
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void deinit(void) {
  window_destroy(window);
}


static void test(struct tm* t) {
  int hour = t->tm_hour;
  int minute = t->tm_min;

  // char* tminute;
  // char* thour;

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Minute: %i", minute);

  if (minute >= 5 && minute <= 9) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", _MFIVE);
  } else if (minute >= 10 && minute <= 14) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", _MTEN);
  } else if (minute >= 15 && minute <= 19) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", _MQUARTER);
  } else if (minute >= 20 && minute <= 24) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", _MTWENTY);
  } else if (minute >= 25 && minute <= 29) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", _MTWENTYFIVE);
  } else if (minute >= 30 && minute <= 34) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", _MHALF);
  } else if (minute >= 35 && minute <= 39) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", _MTWENTYFIVE);
    hour=hour+1;
  } else if (minute >= 40 && minute <= 44) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", _MTWENTY);
    hour=hour+1;
  } else if (minute >= 45 && minute <= 49) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", _MQUARTER);
    hour=hour+1;
  } else if (minute >= 50 && minute <= 54) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", _MTEN);
    hour=hour+1;
  } else if (minute >= 55) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", _MFIVE);
    hour=hour+1;
  }
  
  if (minute == 0) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s",  _OCLOCK);
  }
  if (minute >= 1 && minute <= 30) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s",  _PAST);
  } else {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s",  _TO);
  }

  switch(hour % 12){
    case 1:
     APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", _HONE);
      break;
    case 2:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "%s",  _HTWO);
      break;
    case 3:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "%s",  _HTHREE);
      break;
    case 4:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", _HFOUR);
      break;
    case 5:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", _HFIVE);
      break;
    case 6:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "%s",  _HSIX);
      break;
    case 7:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "%s",  _HSEVEN);
      break;
    case 8:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "%s",  _HEIGHT);
      break;
    case 9:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "%s",  _HNINE);
      break;
    case 10:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "%s",  _HTEN);
      break;
    case 11:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "%s",  _HELEVEN);
      break;
    case 12:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "%s",  _HTWELVE);
      break;
  }

  if (minute % 10 == 0 || minute % 10 == 5) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "x x x x");
  } else if (minute % 10 == 1 || minute % 10 == 6) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "o x x x");
  } else if (minute % 10 == 2 || minute % 10 == 7) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "o o x x");
  } else if (minute % 10 == 3 || minute % 10 == 8) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "o o o x");
  } else if (minute % 10 == 4 || minute % 10 == 9) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "o o o o");
  }
}

static void handle_tick(struct tm *tick_time, TimeUnits units_changed) {
  test(tick_time);

}

static void init(void) {
  window = window_create();
  const bool animated = true;
  window_stack_push(window, animated);
  tick_timer_service_subscribe(MINUTE_UNIT, &handle_tick  );
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}