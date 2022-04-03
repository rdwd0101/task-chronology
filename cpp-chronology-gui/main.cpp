#include <gtkmm.h>
#include <glog/logging.h>
#include "mainWindow.hpp"

namespace constants {
    static const std::string s_uiFileName = "gui.glade";
}

int main (int argc, char *argv[]) {
    // setup logging
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::INFO, "./cpp-chronology-gui-"); // comment this line to write logs to /tmp

    auto app = Gtk::Application::create(argc, argv, "org.cpp.chronology");
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(constants::s_uiFileName.c_str());
    ui::MainWindow* mainWindow = nullptr;
    builder->get_widget_derived("MainWindow", mainWindow);
    std::unique_ptr<ui::MainWindow> mainWindowGuard(mainWindow);
    mainWindowGuard->StartInInitState();
    app->run(*mainWindowGuard);
    return 0;
}