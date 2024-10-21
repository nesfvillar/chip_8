#include "emulator.hpp"

#include <adwaita.h>
#include <string_view>

using namespace chip_8;

std::string_view constexpr APP_TITLE = "Chip 8 Emulator";
std::string_view constexpr APP_ID = "org.nesfvillar.chip_8";
size_t constexpr APP_WIDTH = 800;
size_t constexpr APP_HEIGHT = 600;
size_t constexpr INSTRUCTIONS_PER_FRAME = 10;

void draw_cb(GtkDrawingArea *area, cairo_t *cr, int width, int height,
             gpointer data) {
  auto const &screen_buffer = static_cast<Screen const *>(data)->buffer();

  int pixel_height = height / Screen::HEIGHT;
  int pixel_width = width / Screen::WIDTH;
  for (size_t y = 0; y < Screen::HEIGHT; y++) {
    for (size_t x = 0; x < Screen::WIDTH; x++) {
      if (screen_buffer[y][x]) {
        cairo_rectangle(cr, x * pixel_width, y * pixel_height, pixel_width,
                        pixel_height);
      }
    }
  }
  GdkRGBA color;
  gtk_widget_get_color(GTK_WIDGET(area), &color);
  gdk_cairo_set_source_rgba(cr, &color);

  cairo_fill(cr);
}

gboolean tick_cb(GtkWidget *widget, GdkFrameClock *frame_clock, gpointer data) {
  auto &emulator = *static_cast<Emulator *>(data);

  bool should_draw = false;
  for (size_t i = 0; i < INSTRUCTIONS_PER_FRAME; i++) {
    should_draw |= emulator.step();
  }

  if (should_draw) {
    gtk_widget_queue_draw(widget);
  }

  return G_SOURCE_CONTINUE;
}

void key_pressed_cb(GtkEventController *controller, guint keyval, guint keycode,
                    GdkModifierType state, Keyboard *keyboard) {
  switch (gdk_keyval_to_lower(keyval)) {
  case GDK_KEY_1:
    (*keyboard)[0x1] = true;
    break;
  case GDK_KEY_2:
    (*keyboard)[0x2] = true;
    break;
  case GDK_KEY_3:
    (*keyboard)[0x3] = true;
    break;
  case GDK_KEY_4:
    (*keyboard)[0xC] = true;
    break;
  case GDK_KEY_q:
    (*keyboard)[0x4] = true;
    break;
  case GDK_KEY_w:
    (*keyboard)[0x5] = true;
    break;
  case GDK_KEY_e:
    (*keyboard)[0x6] = true;
    break;
  case GDK_KEY_r:
    (*keyboard)[0xD] = true;
    break;
  case GDK_KEY_a:
    (*keyboard)[0x7] = true;
    break;
  case GDK_KEY_s:
    (*keyboard)[0x8] = true;
    break;
  case GDK_KEY_d:
    (*keyboard)[0x9] = true;
    break;
  case GDK_KEY_f:
    (*keyboard)[0xE] = true;
    break;
  case GDK_KEY_z:
    (*keyboard)[0xA] = true;
    break;
  case GDK_KEY_x:
    (*keyboard)[0x0] = true;
    break;
  case GDK_KEY_c:
    (*keyboard)[0xB] = true;
    break;
  case GDK_KEY_v:
    (*keyboard)[0xF] = true;
    break;
  }
}

void key_released_cb(GtkEventController *controller, guint keyval,
                     guint keycode, GdkModifierType state, Keyboard *keyboard) {
  switch (gdk_keyval_to_lower(keyval)) {
  case GDK_KEY_1:
    (*keyboard)[0x1] = false;
    break;
  case GDK_KEY_2:
    (*keyboard)[0x2] = false;
    break;
  case GDK_KEY_3:
    (*keyboard)[0x3] = false;
    break;
  case GDK_KEY_4:
    (*keyboard)[0xC] = false;
    break;
  case GDK_KEY_q:
    (*keyboard)[0x4] = false;
    break;
  case GDK_KEY_w:
    (*keyboard)[0x5] = false;
    break;
  case GDK_KEY_e:
    (*keyboard)[0x6] = false;
    break;
  case GDK_KEY_r:
    (*keyboard)[0xD] = false;
    break;
  case GDK_KEY_a:
    (*keyboard)[0x7] = false;
    break;
  case GDK_KEY_s:
    (*keyboard)[0x8] = false;
    break;
  case GDK_KEY_d:
    (*keyboard)[0x9] = false;
    break;
  case GDK_KEY_f:
    (*keyboard)[0xE] = false;
    break;
  case GDK_KEY_z:
    (*keyboard)[0xA] = false;
    break;
  case GDK_KEY_x:
    (*keyboard)[0x0] = false;
    break;
  case GDK_KEY_c:
    (*keyboard)[0xB] = false;
    break;
  case GDK_KEY_v:
    (*keyboard)[0xF] = false;
    break;
  }
}

void activate_cb(GtkApplication *app, Emulator *emulator) {
  auto window = adw_application_window_new(app);
  auto toolbar = adw_toolbar_view_new();
  auto header = adw_header_bar_new();
  auto title = adw_window_title_new(APP_TITLE.data(), nullptr);
  auto key_controller = gtk_event_controller_key_new();
  auto drawing_area = gtk_drawing_area_new();

  adw_application_window_set_content(ADW_APPLICATION_WINDOW(window), toolbar);

  adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(toolbar), header);

  adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(toolbar), drawing_area);

  adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), title);

  g_signal_connect_data(GTK_EVENT_CONTROLLER_KEY(key_controller), "key-pressed",
                        G_CALLBACK(key_pressed_cb),
                        const_cast<Keyboard *>(&emulator->state().keyboard),
                        nullptr, G_CONNECT_DEFAULT);
  g_signal_connect_data(key_controller, "key-released",
                        G_CALLBACK(key_released_cb),
                        const_cast<Keyboard *>(&emulator->state().keyboard),
                        nullptr, G_CONNECT_DEFAULT);

  gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(drawing_area), APP_WIDTH);
  gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(drawing_area),
                                      APP_HEIGHT);
  gtk_drawing_area_set_draw_func(
      GTK_DRAWING_AREA(drawing_area), draw_cb,
      const_cast<Screen *>(&emulator->state().screen), nullptr);

  gtk_widget_add_tick_callback(drawing_area, tick_cb, emulator, nullptr);

  gtk_widget_set_focusable(GTK_WIDGET(drawing_area), TRUE);
  gtk_widget_add_controller(GTK_WIDGET(drawing_area),
                            GTK_EVENT_CONTROLLER(key_controller));

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
  auto app = adw_application_new(APP_ID.data(), G_APPLICATION_DEFAULT_FLAGS);

  Emulator emulator;

  g_signal_connect(app, "activate", G_CALLBACK(activate_cb), &emulator);

  return g_application_run(G_APPLICATION(app), argc, argv);
}
