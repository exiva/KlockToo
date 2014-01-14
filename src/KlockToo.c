#include <pebble.h>

static Window *window;
static Layer *grid_layer;
static Layer *brand_layer;
static Layer *window_layer;
static Layer *precision_layer;

static TextLayer *it_text_layer;
static TextLayer *is_text_layer;
static TextLayer *am_text_layer;
static TextLayer *pm_text_layer;
static TextLayer *a_text_layer;
static TextLayer *quarter_text_layer;
static TextLayer *half_text_layer;
static TextLayer *mten_text_layer;
static TextLayer *hnine_text_layer;
static TextLayer *hone_text_layer;
static TextLayer *hsix_text_layer;
static TextLayer *hthree_text_layer;
static TextLayer *hfour_text_layer;
static TextLayer *hfive_text_layer;
static TextLayer *htwo_text_layer;
static TextLayer *height_text_layer;
static TextLayer *heleven_text_layer;
static TextLayer *htwelve_text_layer;
static TextLayer *hseven_text_layer;
static TextLayer *hten_text_layer;
static TextLayer *to_text_layer;
static TextLayer *past_text_layer;
static TextLayer *twenty_text_layer;
static TextLayer *mfive_text_layer;
static TextLayer *random_text_layer;
static TextLayer *oclock_text_layer;

static TextLayer *brand_text;

static const char* _IT = "I T";
static const char* _IS = "I S";
static const char* _A = "A";

//hours
static const char* _HONE = "O N E";
static const char* _HTWO = "T W O";
static const char* _HTHREE = "T H R E E";
static const char* _HFOUR = "F O U R";
static const char* _HFIVE = "F I V E";
static const char* _HSIX = "S I X";
static const char* _HSEVEN = "S E V E N";
static const char* _HEIGHT = "E I G H T";
static const char* _HNINE = "N I N E";
static const char* _HTEN = "T E N";
static const char* _HELEVEN = "E L E V E N";
static const char* _HTWELVE = "T W E L V E";

//minutes
static const char* _MFIVE = "F I V E";
static const char* _MTEN = "T E N";
static const char* _MQUARTER = "Q U A R T E R";
static const char* _MTWENTY = "T W E N T Y";
static const char* _MHALF = "H A L F";

//misc
static const char* _PAST = "P A S T";
static const char* _TO = "T O";
static const char* _OCLOCK = "O' C L O C K";
static const char* _AM = "A M";
static const char* _PM = "P M";

int started = 0;

static const int lineheight = 14;
static const int lineleft = 8;

static void deinit(void) {
  window_destroy(window);
}

void draw_minute(GContext* ctx, struct tm *t) {
  int minute = t->tm_min;

  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_draw_circle(ctx, GPoint(10, 148), 5);
  graphics_draw_circle(ctx, GPoint(25, 148), 5);
  graphics_draw_circle(ctx, GPoint(40, 148), 5);
  graphics_draw_circle(ctx, GPoint(55, 148), 5);

  if (minute % 10 == 1 || minute % 10 == 6) {
    graphics_fill_circle(ctx, GPoint(10, 148), 4);
  } else if (minute % 10 == 2 || minute % 10 == 7) {
    graphics_fill_circle(ctx, GPoint(10, 148), 4);
    graphics_fill_circle(ctx, GPoint(25, 148), 4);
  } else if (minute % 10 == 3 || minute % 10 == 8) {
    graphics_fill_circle(ctx, GPoint(10, 148), 4);
    graphics_fill_circle(ctx, GPoint(25, 148), 4);
    graphics_fill_circle(ctx, GPoint(40, 148), 4);
  } else if (minute % 10 == 4 || minute % 10 == 9) {
    graphics_fill_circle(ctx, GPoint(10, 148), 4);
    graphics_fill_circle(ctx, GPoint(25, 148), 4);
    graphics_fill_circle(ctx, GPoint(40, 148), 4);
    graphics_fill_circle(ctx, GPoint(55, 148), 4);
  }
}


void draw_grid() {
  // Line One
  it_text_layer = text_layer_create((GRect){ .origin = { lineleft, 1 }, .size = {22, lineheight} });
  text_layer_set_text(it_text_layer, _IT);
  text_layer_set_font(it_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(it_text_layer, GColorWhite);
  text_layer_set_background_color(it_text_layer, GColorBlack);
  text_layer_set_text_alignment(it_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(it_text_layer));

  random_text_layer = text_layer_create((GRect){ .origin = { 27+5, 1 }, .size = {9, lineheight} });
  text_layer_set_text(random_text_layer, "L");
  text_layer_set_font(random_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(random_text_layer, GColorBlack);
  text_layer_set_background_color(random_text_layer, GColorWhite);
  text_layer_set_text_alignment(random_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(random_text_layer));

  is_text_layer = text_layer_create((GRect){ .origin = { 39+5, 1 }, .size = {22, lineheight} });
  text_layer_set_text(is_text_layer, _IS);
  text_layer_set_font(is_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(is_text_layer, GColorWhite);
  text_layer_set_background_color(is_text_layer, GColorBlack);
  text_layer_set_text_alignment(is_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(is_text_layer));

  random_text_layer = text_layer_create((GRect){ .origin = { 63+5, 1 }, .size = {22, lineheight} });
  text_layer_set_text(random_text_layer, "A S");
  text_layer_set_font(random_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(random_text_layer, GColorBlack);
  text_layer_set_background_color(random_text_layer, GColorWhite);
  text_layer_set_text_alignment(random_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(random_text_layer));

  am_text_layer = text_layer_create((GRect){ .origin = { 87+5, 1 }, .size = {22, lineheight} });
  text_layer_set_text(am_text_layer, _AM);
  text_layer_set_font(am_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(am_text_layer, GColorBlack);
  text_layer_set_background_color(am_text_layer, GColorWhite);
  text_layer_set_text_alignment(am_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(am_text_layer));

  pm_text_layer = text_layer_create((GRect){ .origin = { 111+5, 1 }, .size = {22, lineheight} });
  text_layer_set_text(pm_text_layer, _PM);
  text_layer_set_font(pm_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(pm_text_layer, GColorBlack);
  text_layer_set_background_color(pm_text_layer, GColorWhite);
  text_layer_set_text_alignment(pm_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(pm_text_layer));

  // Line 2
  a_text_layer = text_layer_create((GRect){ .origin = { lineleft, lineheight }, .size = {9, lineheight} });
  text_layer_set_text(a_text_layer, _A);
  text_layer_set_font(a_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(a_text_layer, GColorBlack);
  text_layer_set_background_color(a_text_layer, GColorWhite);
  text_layer_set_text_alignment(a_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(a_text_layer));

  random_text_layer = text_layer_create((GRect){ .origin = { 15+5, lineheight }, .size = {9, lineheight} });
  text_layer_set_text(random_text_layer, "C");
  text_layer_set_font(random_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(random_text_layer, GColorBlack);
  text_layer_set_background_color(random_text_layer, GColorWhite);
  text_layer_set_text_alignment(random_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(random_text_layer));

  quarter_text_layer = text_layer_create((GRect){ .origin = { 27+5, lineheight }, .size = {87, lineheight} });
  text_layer_set_text(quarter_text_layer, _MQUARTER);
  text_layer_set_font(quarter_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(quarter_text_layer, GColorBlack);
  text_layer_set_background_color(quarter_text_layer, GColorWhite);
  text_layer_set_text_alignment(quarter_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(quarter_text_layer));

  random_text_layer = text_layer_create((GRect){ .origin = { 111+5, lineheight }, .size = {22, lineheight} });
  text_layer_set_text(random_text_layer, "D C");
  text_layer_set_font(random_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(random_text_layer, GColorBlack);
  text_layer_set_background_color(random_text_layer, GColorWhite);
  text_layer_set_text_alignment(random_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(random_text_layer));

  // Line 3
  twenty_text_layer = text_layer_create((GRect){ .origin = { lineleft, lineheight*2 }, .size = {74, lineheight} });
  text_layer_set_text(twenty_text_layer, _MTWENTY);
  text_layer_set_font(twenty_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(twenty_text_layer, GColorBlack);
  text_layer_set_background_color(twenty_text_layer, GColorWhite);
  text_layer_set_text_alignment(twenty_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(twenty_text_layer));

  mfive_text_layer = text_layer_create((GRect){ .origin = { 75+5, lineheight*2 }, .size = {48, lineheight} });
  text_layer_set_text(mfive_text_layer, _MFIVE);
  text_layer_set_font(mfive_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(mfive_text_layer, GColorBlack);
  text_layer_set_background_color(mfive_text_layer, GColorWhite);
  text_layer_set_text_alignment(mfive_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(mfive_text_layer));

  random_text_layer = text_layer_create((GRect){ .origin = { 123+5, lineheight*2 }, .size = {9, lineheight} });
  text_layer_set_text(random_text_layer, "X");
  text_layer_set_font(random_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(random_text_layer, GColorBlack);
  text_layer_set_background_color(random_text_layer, GColorWhite);
  text_layer_set_text_alignment(random_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(random_text_layer));

  // Line 4
  half_text_layer = text_layer_create((GRect){ .origin = { lineleft, lineheight*3 }, .size = {48, lineheight} });
  text_layer_set_text(half_text_layer, _MHALF);
  text_layer_set_font(half_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(half_text_layer, GColorBlack);
  text_layer_set_background_color(half_text_layer, GColorWhite);
  text_layer_set_text_alignment(half_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(half_text_layer));

  random_text_layer = text_layer_create((GRect){ .origin = { 51+5, lineheight*3 }, .size = {9, lineheight} });
  text_layer_set_text(random_text_layer, "B");
  text_layer_set_font(random_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(random_text_layer, GColorBlack);
  text_layer_set_background_color(random_text_layer, GColorWhite);
  text_layer_set_text_alignment(random_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(random_text_layer));

  mten_text_layer = text_layer_create((GRect){ .origin = { 63+5, lineheight*3 }, .size = {35, lineheight} });
  text_layer_set_text(mten_text_layer, _MTEN);
  text_layer_set_font(mten_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(mten_text_layer, GColorBlack);
  text_layer_set_background_color(mten_text_layer, GColorWhite);
  text_layer_set_text_alignment(mten_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(mten_text_layer));

  random_text_layer = text_layer_create((GRect){ .origin = { 100+5, lineheight*3 }, .size = {9, lineheight} });
  text_layer_set_text(random_text_layer, "F");
  text_layer_set_font(random_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(random_text_layer, GColorBlack);
  text_layer_set_background_color(random_text_layer, GColorWhite);
  text_layer_set_text_alignment(random_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(random_text_layer));

  to_text_layer = text_layer_create((GRect){ .origin = { 111+5, lineheight*3 }, .size = {22, lineheight} });
  text_layer_set_text(to_text_layer, _TO);
  text_layer_set_font(to_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(to_text_layer, GColorBlack);
  text_layer_set_background_color(to_text_layer, GColorWhite);
  text_layer_set_text_alignment(to_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(to_text_layer));

  // Line 5
  past_text_layer = text_layer_create((GRect){ .origin = { lineleft, lineheight*4 }, .size = {48, lineheight} });
  text_layer_set_text(past_text_layer, _PAST);
  text_layer_set_font(past_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(past_text_layer, GColorBlack);
  text_layer_set_background_color(past_text_layer, GColorWhite);
  text_layer_set_text_alignment(past_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(past_text_layer));

  random_text_layer = text_layer_create((GRect){ .origin = { 51+5, lineheight*4 }, .size = {35, lineheight} });
  text_layer_set_text(random_text_layer, "E R U");
  text_layer_set_font(random_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(random_text_layer, GColorBlack);
  text_layer_set_background_color(random_text_layer, GColorWhite);
  text_layer_set_text_alignment(random_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(random_text_layer));

  hnine_text_layer = text_layer_create((GRect){ .origin = { 87+5, lineheight*4 }, .size = {48, lineheight} });
  text_layer_set_text(hnine_text_layer, _HNINE);
  text_layer_set_font(hnine_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(hnine_text_layer, GColorBlack);
  text_layer_set_background_color(hnine_text_layer, GColorWhite);
  text_layer_set_text_alignment(hnine_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(hnine_text_layer));

  // Line 6
  hone_text_layer = text_layer_create((GRect){ .origin = { lineleft, lineheight*5 }, .size = {35, lineheight} });
  text_layer_set_text(hone_text_layer, _HONE);
  text_layer_set_font(hone_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(hone_text_layer, GColorBlack);
  text_layer_set_background_color(hone_text_layer, GColorWhite);
  text_layer_set_text_alignment(hone_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(hone_text_layer));

  hsix_text_layer = text_layer_create((GRect){ .origin = { 39+5, lineheight*5 }, .size = {35, lineheight} });
  text_layer_set_text(hsix_text_layer, _HSIX);
  text_layer_set_font(hsix_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(hsix_text_layer, GColorBlack);
  text_layer_set_background_color(hsix_text_layer, GColorWhite);
  text_layer_set_text_alignment(hsix_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(hsix_text_layer));

  hthree_text_layer = text_layer_create((GRect){ .origin = { 75+5, lineheight*5 }, .size = {61, lineheight} });
  text_layer_set_text(hthree_text_layer, _HTHREE);
  text_layer_set_font(hthree_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(hthree_text_layer, GColorBlack);
  text_layer_set_background_color(hthree_text_layer, GColorWhite);
  text_layer_set_text_alignment(hthree_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(hthree_text_layer));

  // Line 7
  hfour_text_layer = text_layer_create((GRect){ .origin = { lineleft, lineheight*6 }, .size = {57, lineheight} });
  text_layer_set_text(hfour_text_layer, _HFOUR);
  text_layer_set_font(hfour_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(hfour_text_layer, GColorBlack);
  text_layer_set_background_color(hfour_text_layer, GColorWhite);
  text_layer_set_text_alignment(hfour_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(hfour_text_layer));

  hfive_text_layer = text_layer_create((GRect){ .origin = { 51+5, lineheight*6 }, .size = {57, lineheight} });
  text_layer_set_text(hfive_text_layer, _HFIVE);
  text_layer_set_font(hfive_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(hfive_text_layer, GColorBlack);
  text_layer_set_background_color(hfive_text_layer, GColorWhite);
  text_layer_set_text_alignment(hfive_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(hfive_text_layer));

  htwo_text_layer = text_layer_create((GRect){ .origin = { 99+5, lineheight*6 }, .size = {35, lineheight} });
  text_layer_set_text(htwo_text_layer, _HTWO);
  text_layer_set_font(htwo_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(htwo_text_layer, GColorBlack);
  text_layer_set_background_color(htwo_text_layer, GColorWhite);
  text_layer_set_text_alignment(htwo_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(htwo_text_layer));

  // Line 8
  height_text_layer = text_layer_create((GRect){ .origin = { lineleft, lineheight*7 }, .size = {61, lineheight} });
  text_layer_set_text(height_text_layer, _HEIGHT);
  text_layer_set_font(height_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(height_text_layer, GColorBlack);
  text_layer_set_background_color(height_text_layer, GColorWhite);
  text_layer_set_text_alignment(height_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(height_text_layer));

  heleven_text_layer = text_layer_create((GRect){ .origin = { 63+5, lineheight*7 }, .size = {74, lineheight} });
  text_layer_set_text(heleven_text_layer, _HELEVEN);
  text_layer_set_font(heleven_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(heleven_text_layer, GColorBlack);
  text_layer_set_background_color(heleven_text_layer, GColorWhite);
  text_layer_set_text_alignment(heleven_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(heleven_text_layer));

  // Line 9
  hseven_text_layer = text_layer_create((GRect){ .origin = { lineleft, lineheight*8 }, .size = {61, lineheight} });
  text_layer_set_text(hseven_text_layer, _HSEVEN);
  text_layer_set_font(hseven_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(hseven_text_layer, GColorBlack);
  text_layer_set_background_color(hseven_text_layer, GColorWhite);
  text_layer_set_text_alignment(hseven_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(hseven_text_layer));

  htwelve_text_layer = text_layer_create((GRect){ .origin = { 63+5, lineheight*8 }, .size = {74, lineheight} });
  text_layer_set_text(htwelve_text_layer, _HTWELVE);
  text_layer_set_font(htwelve_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(htwelve_text_layer, GColorBlack);
  text_layer_set_background_color(htwelve_text_layer, GColorWhite);
  text_layer_set_text_alignment(htwelve_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(htwelve_text_layer));

  // Line 10
  hten_text_layer = text_layer_create((GRect){ .origin = { lineleft, lineheight*9 }, .size = {35, lineheight} });
  text_layer_set_text(hten_text_layer, _HTEN);
  text_layer_set_font(hten_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(hten_text_layer, GColorBlack);
  text_layer_set_background_color(hten_text_layer, GColorWhite);
  text_layer_set_text_alignment(hten_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(hten_text_layer));

  random_text_layer = text_layer_create((GRect){ .origin = { 39+5, lineheight*9 }, .size = {22, lineheight} });
  text_layer_set_text(random_text_layer, "S E");
  text_layer_set_font(random_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(random_text_layer, GColorBlack);
  text_layer_set_background_color(random_text_layer, GColorWhite);
  text_layer_set_text_alignment(random_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(random_text_layer));

  oclock_text_layer = text_layer_create((GRect){ .origin = { 61+5, lineheight*9 }, .size = {74, lineheight} });
  text_layer_set_text(oclock_text_layer, _OCLOCK);
  text_layer_set_font(oclock_text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_12)));
  text_layer_set_text_color(oclock_text_layer, GColorBlack);
  text_layer_set_background_color(oclock_text_layer, GColorWhite);
  text_layer_set_text_alignment(oclock_text_layer, GTextAlignmentLeft);
  layer_add_child(grid_layer, text_layer_get_layer(oclock_text_layer));
}

void draw_branding() {
  brand_text = text_layer_create((GRect){ .origin = { 0, 158 }, .size = {144, lineheight} });
  text_layer_set_text(brand_text, "GALET&RAINURE");
  text_layer_set_font(brand_text, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXEL_7)));
  text_layer_set_text_color(brand_text, GColorBlack);
  text_layer_set_background_color(brand_text, GColorWhite);
  text_layer_set_text_alignment(brand_text, GTextAlignmentCenter);
  layer_add_child(brand_layer, text_layer_get_layer(brand_text));
}

static void reset_hour_layer(int hr) {

    text_layer_set_text_color(hone_text_layer, GColorBlack);
    text_layer_set_background_color(hone_text_layer, GColorWhite);

    text_layer_set_text_color(htwo_text_layer, GColorBlack);
    text_layer_set_background_color(htwo_text_layer, GColorWhite);

    text_layer_set_text_color(hthree_text_layer, GColorBlack);
    text_layer_set_background_color(hthree_text_layer, GColorWhite);

    text_layer_set_text_color(hfour_text_layer, GColorBlack);
    text_layer_set_background_color(hfour_text_layer, GColorWhite);

    text_layer_set_text_color(hfive_text_layer, GColorBlack);
    text_layer_set_background_color(hfive_text_layer, GColorWhite);

    text_layer_set_text_color(hsix_text_layer, GColorBlack);
    text_layer_set_background_color(hsix_text_layer, GColorWhite);

    text_layer_set_text_color(hseven_text_layer, GColorBlack);
    text_layer_set_background_color(hseven_text_layer, GColorWhite);

    text_layer_set_text_color(height_text_layer, GColorBlack);
    text_layer_set_background_color(height_text_layer, GColorWhite);

    text_layer_set_text_color(hnine_text_layer, GColorBlack);
    text_layer_set_background_color(hnine_text_layer, GColorWhite);

    text_layer_set_text_color(hten_text_layer, GColorBlack);
    text_layer_set_background_color(hten_text_layer, GColorWhite);

    text_layer_set_text_color(heleven_text_layer, GColorBlack);
    text_layer_set_background_color(heleven_text_layer, GColorWhite);

    text_layer_set_text_color(htwelve_text_layer, GColorBlack);
    text_layer_set_background_color(htwelve_text_layer, GColorWhite);
}

static void set_ampm(struct tm* t) {
  int hour = t->tm_hour;

  if (hour >= 00 && hour <= 11) {
      text_layer_set_text_color(am_text_layer, GColorWhite);
      text_layer_set_background_color(am_text_layer, GColorBlack);
      text_layer_set_text_color(pm_text_layer, GColorBlack);
      text_layer_set_background_color(pm_text_layer, GColorWhite);
  } else if (hour >= 12 && hour <= 23) {
      text_layer_set_text_color(pm_text_layer, GColorWhite);
      text_layer_set_background_color(pm_text_layer, GColorBlack);
      text_layer_set_text_color(am_text_layer, GColorBlack);
      text_layer_set_background_color(am_text_layer, GColorWhite);
  }
}

static void hour2text(struct tm* t) {
  int hour = t->tm_hour % 12;

  if (t->tm_min >= 35) { 
    hour = hour+1;
  }

  layer_mark_dirty(window_layer);
  reset_hour_layer(hour);

  if (hour == 1) {
    text_layer_set_text_color(hone_text_layer, GColorWhite);
    text_layer_set_background_color(hone_text_layer, GColorBlack);
  } else if (hour == 2) {
    text_layer_set_text_color(htwo_text_layer, GColorWhite);
    text_layer_set_background_color(htwo_text_layer, GColorBlack);
  } else if (hour == 3) {
    text_layer_set_text_color(hthree_text_layer, GColorWhite);
    text_layer_set_background_color(hthree_text_layer, GColorBlack);
  } else if (hour == 4) {
    text_layer_set_text_color(hfour_text_layer, GColorWhite);
    text_layer_set_background_color(hfour_text_layer, GColorBlack);
  } else if (hour == 5) {
    text_layer_set_text_color(hfive_text_layer, GColorWhite);
    text_layer_set_background_color(hfive_text_layer, GColorBlack);
  } else if (hour == 6) {
    text_layer_set_text_color(hsix_text_layer, GColorWhite);
    text_layer_set_background_color(hsix_text_layer, GColorBlack);
  } else if (hour == 7) {
    text_layer_set_text_color(hseven_text_layer, GColorWhite);
    text_layer_set_background_color(hseven_text_layer, GColorBlack);
  } else if (hour == 8) {
    text_layer_set_text_color(height_text_layer, GColorWhite);
    text_layer_set_background_color(height_text_layer, GColorBlack);
  } else if (hour == 9) {
    text_layer_set_text_color(hnine_text_layer, GColorWhite);
    text_layer_set_background_color(hnine_text_layer, GColorBlack);
  } else if (hour == 10) {
    text_layer_set_text_color(hten_text_layer, GColorWhite);
    text_layer_set_background_color(hten_text_layer, GColorBlack);
  } else if (hour == 11) {
    text_layer_set_text_color(heleven_text_layer, GColorWhite);
    text_layer_set_background_color(heleven_text_layer, GColorBlack);
  } else {
    text_layer_set_text_color(htwelve_text_layer, GColorWhite);
    text_layer_set_background_color(htwelve_text_layer, GColorBlack);
    set_ampm(t);
  }
}

static void reset_minute_layer(int min) {
  int l_min = min-1;
  if (l_min <= 4) {
    text_layer_set_text_color(oclock_text_layer, GColorBlack);
    text_layer_set_background_color(oclock_text_layer, GColorWhite);
    text_layer_set_text_color(mfive_text_layer, GColorBlack);
    text_layer_set_background_color(mfive_text_layer, GColorWhite);
  } else if (l_min >= 5 && l_min <= 9) {
    text_layer_set_text_color(mfive_text_layer, GColorBlack);
    text_layer_set_background_color(mfive_text_layer, GColorWhite);
  } else if (l_min >= 10 && l_min <= 14) {
    text_layer_set_text_color(mten_text_layer, GColorBlack);
    text_layer_set_background_color(mten_text_layer, GColorWhite);
  } else if (l_min >= 15 && l_min <= 19) {
    text_layer_set_text_color(a_text_layer, GColorBlack);
    text_layer_set_background_color(a_text_layer, GColorWhite);
    text_layer_set_text_color(quarter_text_layer, GColorBlack);
    text_layer_set_background_color(quarter_text_layer, GColorWhite);
  } else if (l_min >= 20 && l_min <= 24) {
    text_layer_set_text_color(twenty_text_layer, GColorBlack);
    text_layer_set_background_color(twenty_text_layer, GColorWhite);
  } else if (l_min >= 25 && l_min <= 29) {
    text_layer_set_text_color(twenty_text_layer, GColorBlack);
    text_layer_set_background_color(twenty_text_layer, GColorWhite);
    text_layer_set_text_color(mfive_text_layer, GColorBlack);
    text_layer_set_background_color(mfive_text_layer, GColorWhite);
  } else if (l_min >= 30 && l_min <= 34) {
    text_layer_set_text_color(half_text_layer, GColorBlack);
    text_layer_set_background_color(half_text_layer, GColorWhite);
  } else if (l_min >= 35 && l_min <= 39) {
    text_layer_set_text_color(twenty_text_layer, GColorBlack);
    text_layer_set_background_color(twenty_text_layer, GColorWhite);
    text_layer_set_text_color(mfive_text_layer, GColorBlack);
    text_layer_set_background_color(mfive_text_layer, GColorWhite);
  } else if (l_min >= 40 && l_min <= 44) {
    text_layer_set_text_color(twenty_text_layer, GColorBlack);
    text_layer_set_background_color(twenty_text_layer, GColorWhite);
  } else if (l_min >= 45 && l_min <= 49) {
    text_layer_set_text_color(quarter_text_layer, GColorBlack);
    text_layer_set_background_color(quarter_text_layer, GColorWhite);
  } else if (l_min >= 50 && l_min <= 54) {
    text_layer_set_text_color(mten_text_layer, GColorBlack);
    text_layer_set_background_color(mten_text_layer, GColorWhite);
  } else if (l_min >= 55) {
    text_layer_set_text_color(mfive_text_layer, GColorBlack);
    text_layer_set_background_color(mfive_text_layer, GColorWhite);
  }
}

static void minute2text(struct tm* t) {
  int minute = t->tm_min;
  int lastmin = minute % 10;

  if (started == 0 || lastmin == 0 || lastmin == 5) {
    started = 1; // use for first run, never again.
    //mark the screen dirty when it changes.
    layer_mark_dirty(window_layer);
    reset_minute_layer(minute);
    if (minute >= 0 && minute <= 4) {
      text_layer_set_text_color(oclock_text_layer, GColorWhite);
      text_layer_set_background_color(oclock_text_layer, GColorBlack);
    } else if (minute >= 5 && minute <= 9) {
      text_layer_set_text_color(mfive_text_layer, GColorWhite);
      text_layer_set_background_color(mfive_text_layer, GColorBlack);
    } else if (minute >= 10 && minute <= 14) {
      text_layer_set_text_color(mten_text_layer, GColorWhite);
      text_layer_set_background_color(mten_text_layer, GColorBlack);
    } else if (minute >= 15 && minute <= 19) {
      text_layer_set_text_color(a_text_layer, GColorWhite);
      text_layer_set_background_color(a_text_layer, GColorBlack);
      text_layer_set_text_color(quarter_text_layer, GColorWhite);
      text_layer_set_background_color(quarter_text_layer, GColorBlack);
    } else if (minute >= 20 && minute <= 24) {
      text_layer_set_text_color(twenty_text_layer, GColorWhite);
      text_layer_set_background_color(twenty_text_layer, GColorBlack);
    } else if (minute >= 25 && minute <= 29) {
      text_layer_set_text_color(twenty_text_layer, GColorWhite);
      text_layer_set_background_color(twenty_text_layer, GColorBlack);
      text_layer_set_text_color(mfive_text_layer, GColorWhite);
      text_layer_set_background_color(mfive_text_layer, GColorBlack);
    } else if (minute >= 30 && minute <= 34) {
      text_layer_set_text_color(half_text_layer, GColorWhite);
      text_layer_set_background_color(half_text_layer, GColorBlack);
    } else if (minute >= 35 && minute <= 39) {
      text_layer_set_text_color(twenty_text_layer, GColorWhite);
      text_layer_set_background_color(twenty_text_layer, GColorBlack);
      text_layer_set_text_color(mfive_text_layer, GColorWhite);
      text_layer_set_background_color(mfive_text_layer, GColorBlack);
    } else if (minute >= 40 && minute <= 44) {
      text_layer_set_text_color(twenty_text_layer, GColorWhite);
      text_layer_set_background_color(twenty_text_layer, GColorBlack);
    } else if (minute >= 45 && minute <= 49) {
      text_layer_set_text_color(a_text_layer, GColorWhite);
      text_layer_set_background_color(a_text_layer, GColorBlack);
      text_layer_set_text_color(quarter_text_layer, GColorWhite);
      text_layer_set_background_color(quarter_text_layer, GColorBlack);
    } else if (minute >= 50 && minute <= 54) {
      text_layer_set_text_color(mten_text_layer, GColorWhite);
      text_layer_set_background_color(mten_text_layer, GColorBlack);
    } else if (minute >= 55) {
      text_layer_set_text_color(mfive_text_layer, GColorWhite);
      text_layer_set_background_color(mfive_text_layer, GColorBlack);
    }
    if (minute >= 5 && minute <= 34) { // handle tense
      text_layer_set_text_color(past_text_layer, GColorWhite);
      text_layer_set_background_color(past_text_layer, GColorBlack);
      text_layer_set_text_color(to_text_layer, GColorBlack);
      text_layer_set_background_color(to_text_layer, GColorWhite);
    } if (minute >= 35) {
      text_layer_set_text_color(to_text_layer, GColorWhite);
      text_layer_set_background_color(to_text_layer, GColorBlack);
      text_layer_set_text_color(past_text_layer, GColorBlack);
      text_layer_set_background_color(past_text_layer, GColorWhite);
    } else if(minute < 5) {
      text_layer_set_text_color(to_text_layer, GColorBlack);
      text_layer_set_background_color(to_text_layer, GColorWhite);
      text_layer_set_text_color(past_text_layer, GColorBlack);
      text_layer_set_background_color(past_text_layer, GColorWhite);
    }
    if (minute == 35) { //hour changes on 35 past. Save updates.
      hour2text(t);
    }
  }
}

static void handle_tick(struct tm *tick_time, TimeUnits units_changed) {
    layer_mark_dirty(precision_layer);
    minute2text(tick_time);
}

void minutelayer_update_callback(Layer *me, GContext* ctx) {
  //get current time.
  time_t now = time(NULL);
  struct tm *tick_time = localtime(&now);

  draw_minute(ctx, tick_time);
}

static void init(void) {
  window = window_create();
  window_stack_push(window, false);

  window_set_background_color(window, GColorWhite);

  //draw text grid
  window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  grid_layer = layer_create(bounds);
  layer_add_child(window_layer, grid_layer);
  draw_grid();

  brand_layer = layer_create(bounds);
  layer_add_child(window_layer, brand_layer);
  draw_branding();

  precision_layer = layer_create(bounds);
  layer_set_update_proc(precision_layer, &minutelayer_update_callback);
  layer_add_child(window_layer, precision_layer);

  //subscribe to tick and update display for first rendering
  tick_timer_service_subscribe(MINUTE_UNIT, &handle_tick);
  time_t now = time(NULL);
  struct tm *tick_time = localtime(&now);
  //init the screen
  minute2text(tick_time);
  hour2text(tick_time);
  set_ampm(tick_time);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}