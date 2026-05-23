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

    Gtk::Button* buttonPtr3 = nullptr;
    m_builder->get_widget("RemoveTaskButton", buttonPtr3);
    buttonPtr3->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::RemoveTaskButton_clicked_cb));
}

ui::MainWindow::~MainWindow() {}

void ui::MainWindow::StartInInitState()
{
    LOG(INFO) << "on StartInInitState";
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
    m_dailyTasksListView->append_column("Date", m_columns.m_date);
    
    show_all_children();

    m_dailyTasksController.SetModel(m_dailyTasksTreeModel);
    m_dailyTasksController.Load();
    LOG(INFO) << "StartInInitState finish";
}


void ui::MainWindow::AddTaskButton_clicked_cb()
{
    // adds daily record
    Gtk::Dialog *dialogPtr = nullptr;
    m_builder->get_widget("NewWorklogDialog", dialogPtr);
    int buttonClicked = dialogPtr->run();
    dialogPtr->hide();

    if (buttonClicked != 1)
    {
        return;
    }
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
    chronology::types::DailyRecord record;
    record.uuid = chronology::utils::GenerateUUID();
    record.description = descEntryPtr->get_text();
    try
    {
        record.hours = std::stod(timeEntryPtr->get_text().c_str());
    }
    catch (const std::exception& ex)
    {
        LOG(INFO) << "Invalid hours input: " << timeEntryPtr->get_text() << " (" << ex.what() << ")";
        return;
    }
    record.task_name = nameEntryPtr->get_text();
    record.date = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    m_dailyTasksController.AddRecord(record);

}

void ui::MainWindow::RemoveTaskButton_clicked_cb()
{
    // removes daily record

    Glib::RefPtr<Gtk::TreeSelection> sel = m_dailyTasksListView->get_selection();
    
    Gtk::TreeModel::iterator selectedRow = sel->get_selected();
    Gtk::TreeModel::Row row = *selectedRow;
    Glib::ustring uuid = row.get_value(m_columns.m_uuid);
    
    m_dailyTasksController.RemoveRecord(uuid);
}
