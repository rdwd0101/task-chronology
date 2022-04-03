#include "mainWindow.hpp"

ui::MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
    : Gtk::Window(cobject)
    , m_builder(builder)
{
    Gtk::Button* buttonPtr = nullptr;
    m_builder->get_widget("AddTaskButton", buttonPtr);
    m_AddTaskButton.reset(buttonPtr);
    m_AddTaskButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::AddTaskButton_clicked_cb));
}

ui::MainWindow::~MainWindow() {}

void ui::MainWindow::StartInInitState()
{
    if (m_TasksListView.get() == nullptr)
    {
        Gtk::TreeView* treePtr = nullptr;
        m_builder->get_widget("TaskTreeView", treePtr);
        m_TasksListView.reset(treePtr);
    }
    m_treeModel = Gtk::ListStore::create(m_columns);
    m_TasksListView->set_model(m_treeModel);
    m_TasksListView->append_column("ID", m_columns.m_col_id);
    m_TasksListView->append_column("Name", m_columns.m_col_name);
    m_TasksListView->append_column("Number", m_columns.m_col_number);
    m_TasksListView->append_column("Percentage", m_columns.m_col_percentage);
    show_all_children();
}


void ui::MainWindow::AddTaskButton_clicked_cb()
{
    LOG(INFO) << "Found cookies";
    Gtk::TreeModel::Row row = *(m_treeModel->append());
    row[m_columns.m_col_id] = 1;
    row[m_columns.m_col_name] = "The Name";
    row[m_columns.m_col_number] = 10;
    row[m_columns.m_col_percentage] = 15;
}