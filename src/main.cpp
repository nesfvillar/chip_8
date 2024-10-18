#include "emulator.hpp"

#include <adwaita.h>
#include <string_view>

using namespace chip_8;

std::string_view constexpr APP_TITLE = "Chip 8 Emulator";
std::string_view constexpr APP_ID = "org.nesfvillar.Chip_8";
size_t constexpr APP_WIDTH = 800;
size_t constexpr APP_HEIGHT = 600;

void activate_cb(GtkApplication *app) {
  GtkWidget *window = gtk_application_window_new(app);

  gtk_window_set_title(GTK_WINDOW(window), APP_TITLE.data());
  gtk_window_set_default_size(GTK_WINDOW(window), APP_WIDTH, APP_HEIGHT);

  GtkWidget *drawing_area = gtk_drawing_area_new();
  gtk_window_set_child(GTK_WINDOW(window), drawing_area);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
  auto app = adw_application_new(APP_ID.data(), G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "activate", G_CALLBACK(activate_cb), NULL);

  return g_application_run(G_APPLICATION(app), argc, argv);
}
