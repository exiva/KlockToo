#include <pebble.h>

static Window *window;
static TextLayer *text_layer;

static const char* _ITIS = "it is";
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
static const char* _MFIVE = "five";
static const char* _MTEN = "ten";
static const char* _MQUARTER = "quarter";
static const char* _MTWENTY = "twenty";
static const char* _MTWENTYFIVE = "twenty five";
static const char* _MHALF = "half";

//misc
static const char* _PAST = "past";
static const char* _TO = "to";
static const char* _OCLOCK = "o'clock";

const char* tminute = NULL;
const char* thour = NULL;
const char* tense = NULL;

static void window_load(Window *window) {
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void deinit(void) {
  window_destroy(window);
}


static void test(struct tm* t) {
  int hour = t->tm_hour % 12;
  int minute = t->tm_min;

  if (minute >= 5 && minute <= 9) {
    tminute = _MFIVE;
  } else if (minute >= 10 && minute <= 14) {
    tminute = _MTEN;
  } else if (minute >= 15 && minute <= 19) {
    tminute = _MQUARTER;
  } else if (minute >= 20 && minute <= 24) {
    tminute = _MTWENTY;
  } else if (minute >= 25 && minute <= 29) {
    tminute = _MTWENTYFIVE;
  } else if (minute >= 30 && minute <= 34) {
    tminute = _MHALF;
  } else if (minute >= 35 && minute <= 39) {
    tminute = _MTWENTYFIVE;
    hour=hour+1;
  } else if (minute >= 40 && minute <= 44) {
    tminute = _MTWENTY;
    hour=hour+1;
  } else if (minute >= 45 && minute <= 49) {
    tminute = _MQUARTER;
    hour=hour+1;
  } else if (minute >= 50 && minute <= 54) {
    tminute = _MTEN;
    hour=hour+1;
  } else if (minute >= 55) {
    tminute = _MFIVE;
    hour=hour+1;
  }
  
  // if (minute == 0) {
  //   APP_LOG(APP_LOG_LEVEL_DEBUG, "%s",  _OCLOCK);
  // } else {

  // }

  if (minute >= 1 && minute <= 34) {
    tense = _PAST;
  } else {
    tense = _TO;
  }

  if (hour == 1) {
    thour = _HONE;
  } else if (hour == 2) {
    thour = _HTWO;
  } else if (hour == 3) {
    thour = _HTHREE;
  } else if (hour == 4) {
    thour = _HFOUR;
  } else if (hour == 5) {
    thour = _HFIVE;
  } else if (hour == 6) {
    thour = _HSIX;
  } else if (hour == 7) {
    thour = _HSEVEN;
  } else if (hour == 8) {
    thour = _HEIGHT;
  } else if (hour == 9) {
    thour = _HNINE;
  } else if (hour == 10) {
    thour = _HTEN;
  } else if (hour == 11) {
    thour = _HELEVEN;
  } else if (hour == 12) {
    thour = _HTWELVE;
  }

  APP_LOG(APP_LOG_LEVEL_DEBUG, "%s %s %s %s", _ITIS, tminute, tense, thour );

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