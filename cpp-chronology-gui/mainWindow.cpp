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
        Gtk::TreeView* treePtr = nullptr;
        m_builder->get_widget("TaskTreeView", treePtr);
        m_TasksList.reset(treePtr);
    }
    
    Gtk::Label* item = new Gtk::Label();
    item->set_text("Hello, world!");
    m_TasksList->add(*item);
    item->show();
}