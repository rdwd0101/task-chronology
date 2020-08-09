#include "mainWindow.hpp"

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
    if (m_TasksList.get() == nullptr)
    {
        Gtk::ListBox* listPtr = nullptr;
        m_builder->get_widget("TasksList", listPtr);
        m_TasksList.reset(listPtr);
    }
    
    Gtk::Label* item = new Gtk::Label();
    item->set_text("Hello, world!");
    m_TasksList->insert(*item, m_TasksList->get_children().size());
    item->show();
}