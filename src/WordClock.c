#include <pebble.h>

static Window *window;
static TextLayer *its_text_layer;
static TextLayer *min_text_layer;
static TextLayer *tense_text_layer;
static TextLayer *hour_text_layer;
static TextLayer *minutebubble_text_layer;

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
static const char* _BLANK = "";
static const char* _OCLOCK = "o'clock";
static const char* _AM = "AM";
static const char* _PM = "PM";

const char* tminute = NULL;
const char* thour = NULL;
int tense = 0;
int minutebubble = 0;
int timeofday = 0;

static void window_load(Window *window) {
}

static void window_unload(Window *window) {
  text_layer_destroy(min_text_layer);
}

static void deinit(void) {
  window_destroy(window);
}

static void render_screen(void) {
  Layer *window_layer = window_get_root_layer(window);

  GRect bounds = layer_get_frame(window_layer);

  its_text_layer = text_layer_create((GRect){ .origin = { 0, 0 }, .size = bounds.size });
  text_layer_set_font(its_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_color(its_text_layer, GColorWhite);
  text_layer_set_background_color(its_text_layer, GColorClear);
  text_layer_set_text_alignment(its_text_layer, GTextAlignmentLeft);
  layer_add_child(window_layer, text_layer_get_layer(its_text_layer));

  min_text_layer = text_layer_create((GRect){ .origin = { 0, 20 }, .size = bounds.size });
  text_layer_set_font(min_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_color(min_text_layer, GColorWhite);
  text_layer_set_background_color(min_text_layer, GColorClear);
  text_layer_set_text_alignment(min_text_layer, GTextAlignmentLeft);
  layer_add_child(window_layer, text_layer_get_layer(min_text_layer));
  
  tense_text_layer = text_layer_create((GRect){ .origin = { 0, 40 }, .size = bounds.size });
  text_layer_set_font(tense_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_color(tense_text_layer, GColorWhite);
  text_layer_set_background_color(tense_text_layer, GColorClear);
  text_layer_set_text_alignment(tense_text_layer, GTextAlignmentLeft);
  layer_add_child(window_layer, text_layer_get_layer(tense_text_layer));
      
  hour_text_layer = text_layer_create((GRect){ .origin = { 0, 60 }, .size = bounds.size });
  text_layer_set_font(hour_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_color(hour_text_layer, GColorWhite);
  text_layer_set_background_color(hour_text_layer, GColorClear);
  text_layer_set_text_alignment(hour_text_layer, GTextAlignmentLeft);
  layer_add_child(window_layer, text_layer_get_layer(hour_text_layer));

  minutebubble_text_layer = text_layer_create((GRect){ .origin = { 0, 80 }, .size = bounds.size });
  text_layer_set_font(minutebubble_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_color(minutebubble_text_layer, GColorWhite);
  text_layer_set_background_color(minutebubble_text_layer, GColorClear);
  text_layer_set_text_alignment(minutebubble_text_layer, GTextAlignmentLeft);
  layer_add_child(window_layer, text_layer_get_layer(minutebubble_text_layer));

}

static void update_text(const char* t_minute, const char* t_hour, int t_tense, int t_minutes, int t_timeofday) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Debug: %s text minute: %s text hour: %s tense: %i minutes: %i timeofday: %i", _ITIS, t_minute, t_hour, t_tense, t_minutes, t_timeofday);
  text_layer_set_text(its_text_layer, _ITIS);

  text_layer_set_text(min_text_layer, t_minute);

    switch(t_tense) {
    case 0:
      text_layer_destroy(tense_text_layer);
    break;
    case 1:
      text_layer_set_text(tense_text_layer, _PAST);
    break;
    case 2:
      text_layer_set_text(tense_text_layer, _TO);
    break;
  }

  text_layer_set_text(hour_text_layer, t_hour);

    switch(t_minutes) {
    case 0:
      text_layer_set_text(minutebubble_text_layer, "x x x x");
      break;
    case 1:
      text_layer_set_text(minutebubble_text_layer, "o x x x");
      break;
    case 2:
      text_layer_set_text(minutebubble_text_layer, "o o x x");
      break;
    case 3:
      text_layer_set_text(minutebubble_text_layer, "o o o x");
      break;
    case 4:
      text_layer_set_text(minutebubble_text_layer, "o o o o");
      break;
  }
}

static void time2text(struct tm* t) {
  int hour = t->tm_hour % 12;
  int minute = t->tm_min;

  if (minute >= 0 && minute <= 4) {
    tminute = _OCLOCK;
  } else if (minute >= 5 && minute <= 9) {
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
  
  if (minute >=0 && minute <= 4) {
    tense = 0;
  } else if (minute >= 5 && minute <= 34) {
    tense = 1;
  } else {
    tense = 2;
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
  } else {
    thour = _HTWELVE;
  }

  if (t->tm_hour >= 0 && t->tm_hour <=11) {
    timeofday = 1;
  } else {
    timeofday = 2;
  }

  if (minute % 10 == 0 || minute % 10 == 5) {
    minutebubble = 0;
  } else if (minute % 10 == 1 || minute % 10 == 6) {
    minutebubble = 1;
  } else if (minute % 10 == 2 || minute % 10 == 7) {
    minutebubble = 2;
  } else if (minute % 10 == 3 || minute % 10 == 8) {
    minutebubble = 3;
  } else if (minute % 10 == 4 || minute % 10 == 9) {
    minutebubble = 4;
  }

  //return shit.
  // APP_LOG(APP_LOG_LEVEL_DEBUG, "Debug: struct: %i hour: %i thour: %s minute: %i", t->tm_hour, hour, thour, minute);
  // APP_LOG(APP_LOG_LEVEL_DEBUG, "Debug: %s text minute: %s text hour: %s tense: %i minutes: %i timeofday: %i", _ITIS, tminute, thour, tense, minutebubble, timeofday);
  update_text(tminute, thour, tense, minutebubble, timeofday);
}



static void handle_tick(struct tm *tick_time, TimeUnits units_changed) {
  time2text(tick_time);
}

static void init(void) {
  window = window_create();
  window_stack_push(window, true);
  window_set_background_color(window, GColorBlack);
  render_screen(); //init screen

  tick_timer_service_subscribe(MINUTE_UNIT, &handle_tick  );
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}