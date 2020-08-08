#include <gtkmm.h>
#include "mainWindow.hpp"

namespace constants {
    static const std::string s_uiFileName = "ui.glade";
}

int main (int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.cpp.chronology");
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(constants::s_uiFileName.c_str());
    ui::MainWindow* mainWindow = nullptr;
    builder->get_widget_derived("MainWindow", mainWindow);
    std::unique_ptr<Gtk::Window> mainWindowGuard(mainWindow);
    app->run(*mainWindowGuard);
    return 0;
}