#include "emulator.hpp"

#include <adwaita.h>
#include <string_view>

using namespace chip_8;

std::string_view constexpr APP_TITLE = "Chip 8 Emulator";
std::string_view constexpr APP_ID = "org.nesfvillar.chip_8";
size_t constexpr APP_WIDTH = 800;
size_t constexpr APP_HEIGHT = 600;

void draw(GtkDrawingArea *area, cairo_t *cr, int width, int height,
          gpointer data) {
  auto screen = static_cast<
      std::array<std::array<bool, Screen::WIDTH>, Screen::HEIGHT> *>(data);

  GdkRGBA color;
  gtk_widget_get_color(GTK_WIDGET(area), &color);
  gdk_cairo_set_source_rgba(cr, &color);

  int pixel_height = height / Screen::HEIGHT;
  int pixel_width = width / Screen::WIDTH;
  for (auto y = 0; y < Screen::HEIGHT; y++) {
    for (auto x = 0; x < Screen::WIDTH; x++) {
      if ((*screen)[y][x]) {
        cairo_rectangle(cr, x * pixel_width, y * pixel_height, pixel_width,
                        pixel_height);
      }
    }
  }
  cairo_fill(cr);
}

void activate_cb(GtkApplication *app) {
  auto window = gtk_application_window_new(app);

  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE.data());
  gtk_window_set_default_size(GTK_WINDOW(window), APP_WIDTH, APP_HEIGHT);

  auto drawing_area = gtk_drawing_area_new();
  gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(drawing_area),
                                      APP_HEIGHT);
  gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(drawing_area), APP_WIDTH);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), draw, nullptr,
                                 nullptr);

  gtk_window_set_child(GTK_WINDOW(window), drawing_area);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
  auto app = adw_application_new(APP_ID.data(), G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "activate", G_CALLBACK(activate_cb), nullptr);

  return g_application_run(G_APPLICATION(app), argc, argv);
}
