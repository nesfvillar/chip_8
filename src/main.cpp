#include "emulator.hpp"

#include <adwaita.h>
#include <string_view>

using namespace chip_8;

std::string_view constexpr APP_TITLE = "Chip 8 Emulator";
std::string_view constexpr APP_ID = "org.nesfvillar.chip_8";
size_t constexpr APP_WIDTH = 800;
size_t constexpr APP_HEIGHT = 600;

void draw_cb(GtkDrawingArea *area, cairo_t *cr, int width, int height,
             gpointer data) {
  auto screen_buffer = static_cast<Screen *>(data)->buffer();

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
  auto &&e = *static_cast<Emulator *>(data);

  bool should_draw = false;
  for (auto i = 0; i < 11; i++) {
    should_draw |= e.step();
  }

  if (should_draw) {
    gtk_widget_queue_draw(widget);
  }

  return G_SOURCE_CONTINUE;
}

void activate_cb(GtkApplication *app, Emulator *emulator) {
  auto &&state = const_cast<State &>(emulator->state());

  auto window = adw_application_window_new(app);
  auto toolbar = adw_toolbar_view_new();
  auto header = adw_header_bar_new();
  auto title = adw_window_title_new(APP_TITLE.data(), nullptr);
  auto drawing_area = gtk_drawing_area_new();

  adw_application_window_set_content(ADW_APPLICATION_WINDOW(window), toolbar);

  adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(toolbar), header);

  adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(toolbar), drawing_area);

  adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), title);

  gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(drawing_area), APP_WIDTH);
  gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(drawing_area),
                                      APP_HEIGHT);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), draw_cb,
                                 &state.screen, nullptr);
  gtk_widget_add_tick_callback(drawing_area, tick_cb, emulator, nullptr);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
  auto app = adw_application_new(APP_ID.data(), G_APPLICATION_DEFAULT_FLAGS);

  Emulator emulator;

  g_signal_connect(app, "activate", G_CALLBACK(activate_cb), &emulator);

  return g_application_run(G_APPLICATION(app), argc, argv);
}
