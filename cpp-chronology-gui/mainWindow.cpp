#include <memory>
#include "mainWindow.hpp"

ui::MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
    : Gtk::Window(cobject)
    , m_builder(builder)
{
    Gtk::Button* buttonPtr = nullptr;
    m_builder->get_widget("AddTaskButton", buttonPtr);
    m_AddTaskButton.reset(buttonPtr);
    m_AddTaskButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::AddTaskButton_clicked_cb));
    
    Gtk::Button* buttonPtr2 = nullptr;
    m_builder->get_widget("NewWorklogDialogOkButton", buttonPtr2);
    buttonPtr2->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::NewWorklogDialogOkButton_clicked_cb));
}

ui::MainWindow::~MainWindow() {}

void ui::MainWindow::StartInInitState()
{
    if (m_dailyTasksListView.get() == nullptr)
    {
        Gtk::TreeView* treePtr = nullptr;
        m_builder->get_widget("TaskTreeView", treePtr);
        m_dailyTasksListView.reset(treePtr);
    }
    // model arrangement
    m_dailyTasksTreeModel = Gtk::ListStore::create(m_columns);
    
    // view arrangement
    m_dailyTasksListView->set_model(m_dailyTasksTreeModel);
    m_dailyTasksListView->append_column_editable("Name", m_columns.m_task_name);
    m_dailyTasksListView->append_column_editable("Hours", m_columns.m_hours);
    m_dailyTasksListView->append_column_editable("Description", m_columns.m_task_description);
    
    show_all_children();

    //auto ptr = new chronology::providers::YamlDatabaseProvider();
    //std::make_shared<chronology::providers::YamlDatabaseProvider>();
    //m_worklogDbManager = std::make_unique<chronology::managers::WorklogDBManager>(ptr);
    //m_worklogDbManager->Load("./worklog.yaml");
}


void ui::MainWindow::AddTaskButton_clicked_cb()
{
    // adds daily record
    // LOG(INFO) << "Found cookies";
    //m_dailyTasksListView->get_cursor(path, column);
    Gtk::Dialog *dialogPtr = nullptr;
    m_builder->get_widget("NewWorklogDialog", dialogPtr);
    int buttonClicked = dialogPtr->run();
    dialogPtr->hide();

    if (buttonClicked != 1)
    {
        return;
    }

    Gtk::Entry *nameEntryPtr = nullptr;
    m_builder->get_widget("NewWorklogDialogNameEntryText", nameEntryPtr);

    Gtk::Entry *timeEntryPtr = nullptr;
    m_builder->get_widget("NewWorklogDialogTimeEntryText", timeEntryPtr);

    Gtk::Entry *descEntryPtr = nullptr;
    m_builder->get_widget("NewWorklogDialogDescriptionEntryText", descEntryPtr);
    
    if (nameEntryPtr == nullptr || timeEntryPtr == nullptr || descEntryPtr == nullptr)
    {
        return;
    }
    // assume that all error checking was performed in dialog button callback
    Gtk::TreeModel::Row row = *(m_dailyTasksTreeModel->append());
    row[m_columns.m_task_name] = nameEntryPtr->get_text();
    row[m_columns.m_task_description] = descEntryPtr->get_text();
    row[m_columns.m_hours] = std::stof(timeEntryPtr->get_text().c_str());
}

void ui::MainWindow::NewWorklogDialogOkButton_clicked_cb()
{
    Gtk::Entry *nameEntryPtr = nullptr;
    m_builder->get_widget("NewWorklogDialogNameEntryText", nameEntryPtr);

    Gtk::Entry *timeEntryPtr = nullptr;
    m_builder->get_widget("NewWorklogDialogTimeEntryText", timeEntryPtr);

    Gtk::Entry *descEntryPtr = nullptr;
    m_builder->get_widget("NewWorklogDialogDescriptionEntryText", descEntryPtr);
    
    if (nameEntryPtr == nullptr || timeEntryPtr == nullptr || descEntryPtr == nullptr)
    {
        return;
    }

    if (nameEntryPtr->get_text().empty())
    {
        LOG(INFO) << "Name entry was empty";
        return;
    }

    if (timeEntryPtr->get_text().empty())
    {
        LOG(INFO) << "Time entry was empty";
        return;
    }

    if (descEntryPtr->get_text().empty())
    {
        LOG(INFO) << "Desc entry was empty";
        return;
    }
    // TODO: add error checking:
    //row[m_columns.m_hours] = std::stof(timeEntryPtr->get_text().c_str());
}