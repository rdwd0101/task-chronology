#include "mainWindow.hpp"
#include <iostream>

ui::MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
    : Gtk::Window(cobject)
    , m_builder(builder) {
    Gtk::Button* buttonPtr = nullptr;
    m_builder->get_widget("AddTaskButton", buttonPtr);
    m_AddTaskButton.reset(buttonPtr);
    m_AddTaskButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::AddTaskButton_clicked_cb));
}

ui::MainWindow::~MainWindow() {}

void ui::MainWindow::AddTaskButton_clicked_cb()
{
    std::cout << "Hello World" << std::endl;
}