#include "emulator.hpp"

#include <string_view>

#include <adwaita.h>
#include <gtkmm.h>

using namespace chip_8;

std::string_view constexpr APP_ID = "org.nesfvillar.chip_8";
std::string_view constexpr UI_PATH = "../src/builder.ui";
std::string_view constexpr PROGRAM_PATH = "../br8kout.ch8";
size_t constexpr INSTRUCTIONS_PER_FRAME = 10;

bool on_key_pressed(guint keyval, guint, Gdk::ModifierType, Cpu *cpu) {
  auto &&keyboard = cpu->keyboard;

  switch (gdk_keyval_to_lower(keyval)) {
  case GDK_KEY_1:
    keyboard[0x1] = true;
    break;
  case GDK_KEY_2:
    keyboard[0x2] = true;
    break;
  case GDK_KEY_3:
    keyboard[0x3] = true;
    break;
  case GDK_KEY_4:
    keyboard[0xC] = true;
    break;
  case GDK_KEY_q:
    keyboard[0x4] = true;
    break;
  case GDK_KEY_w:
    keyboard[0x5] = true;
    break;
  case GDK_KEY_e:
    keyboard[0x6] = true;
    break;
  case GDK_KEY_r:
    keyboard[0xD] = true;
    break;
  case GDK_KEY_a:
    keyboard[0x7] = true;
    break;
  case GDK_KEY_s:
    keyboard[0x8] = true;
    break;
  case GDK_KEY_d:
    keyboard[0x9] = true;
    break;
  case GDK_KEY_f:
    keyboard[0xE] = true;
    break;
  case GDK_KEY_z:
    keyboard[0xA] = true;
    break;
  case GDK_KEY_x:
    keyboard[0x0] = true;
    break;
  case GDK_KEY_c:
    keyboard[0xB] = true;
    break;
  case GDK_KEY_v:
    keyboard[0xF] = true;
    break;
  }

  return true;
}

void on_key_released(guint keyval, guint, Gdk::ModifierType, Cpu *cpu) {
  auto &&keyboard = cpu->keyboard;

  switch (gdk_keyval_to_lower(keyval)) {
  case GDK_KEY_1:
    keyboard[0x1] = false;
    break;
  case GDK_KEY_2:
    keyboard[0x2] = false;
    break;
  case GDK_KEY_3:
    keyboard[0x3] = false;
    break;
  case GDK_KEY_4:
    keyboard[0xC] = false;
    break;
  case GDK_KEY_q:
    keyboard[0x4] = false;
    break;
  case GDK_KEY_w:
    keyboard[0x5] = false;
    break;
  case GDK_KEY_e:
    keyboard[0x6] = false;
    break;
  case GDK_KEY_r:
    keyboard[0xD] = false;
    break;
  case GDK_KEY_a:
    keyboard[0x7] = false;
    break;
  case GDK_KEY_s:
    keyboard[0x8] = false;
    break;
  case GDK_KEY_d:
    keyboard[0x9] = false;
    break;
  case GDK_KEY_f:
    keyboard[0xE] = false;
    break;
  case GDK_KEY_z:
    keyboard[0xA] = false;
    break;
  case GDK_KEY_x:
    keyboard[0x0] = false;
    break;
  case GDK_KEY_c:
    keyboard[0xB] = false;
    break;
  case GDK_KEY_v:
    keyboard[0xF] = false;
    break;
  }
}
void on_draw(Cairo::RefPtr<Cairo::Context> const &cr, int width, int height,
             Gtk::Widget const *widget, Emulator const *emulator) {
  auto screen = emulator->cpu.screen;

  int pixel_height = height / screen.HEIGHT;
  int pixel_width = width / screen.WIDTH;

  for (size_t y = 0; y < screen.HEIGHT; y++) {
    for (size_t x = 0; x < screen.WIDTH; x++) {

      if (screen[x, y]) {
        cr->rectangle(x * pixel_width, y * pixel_height, pixel_width,
                      pixel_height);
      }
    }
  }

  auto color = widget->get_color();
  cr->set_source_rgba(color.get_red(), color.get_green(), color.get_blue(),
                      color.get_alpha());

  cr->fill();
}

bool on_tick(Glib::RefPtr<Gdk::FrameClock> const &, Gtk::Widget *widget,
             Emulator *emulator) {
  bool should_draw = false;
  for (size_t i = 0; i < INSTRUCTIONS_PER_FRAME; i++) {
    should_draw |= emulator->step();
  }

  if (should_draw) {
    widget->queue_draw();
  }

  emulator->decrease_timers();
  // if (emulator->state().cpu.timers[Timer::SOUND]) {
  // }

  return G_SOURCE_CONTINUE;
}

void on_app_activate(Glib::RefPtr<Gtk::Application> app, Emulator *emulator) {

  auto builder = Gtk::Builder::create_from_file(UI_PATH.data());

  auto window = builder->get_object<Gtk::ApplicationWindow>("window");
  window->set_application(app);

  auto drawing_area = builder->get_object<Gtk::DrawingArea>("drawing_area");
  drawing_area->set_draw_func(
      sigc::bind(&on_draw, drawing_area.get(), emulator));
  drawing_area->add_tick_callback(
      sigc::bind(&on_tick, drawing_area.get(), emulator));

  auto key_controller = Gtk::EventControllerKey::create();
  key_controller->signal_key_pressed().connect(
      sigc::bind(&on_key_pressed, &emulator->cpu), true);
  key_controller->signal_key_released().connect(
      sigc::bind(&on_key_released, &emulator->cpu), false);
  window->add_controller(key_controller);

  window->present();
}

int main(int argc, char *argv[]) {
  adw_init();
  auto app = Gtk::Application::create(APP_ID.data());

  auto program = read_binary(PROGRAM_PATH.data());
  Emulator emulator{std::move(program)};

  app->signal_activate().connect(sigc::bind(&on_app_activate, app, &emulator));

  return app->run(argc, argv);
}
