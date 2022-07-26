#pragma once
#include <gtkmm.h>
#include <glog/logging.h>

#include "../cpp-chronology-lib/providers/IDatabaseProvider.h"
#include "../cpp-chronology-lib/providers/YamlDatabaseProvider.h"
#include "../cpp-chronology-lib/managers/worklogDBManager.h"
#include "columns.hpp"

namespace ui {
    class MainWindow : public Gtk::Window {
    private:
        std::unique_ptr<chronology::providers::YamlDatabaseProvider> m_dbProvider;
        std::unique_ptr<chronology::managers::WorklogDBManager> m_worklogDbManager;

    public:
        MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
        virtual ~MainWindow();
        void StartInInitState();

    protected: // callbacks
        void AddTaskButton_clicked_cb();
        void NewWorklogDialogOkButton_clicked_cb();

    protected: // member widgets
        std::unique_ptr<Gtk::Button> m_AddTaskButton;
        
        Glib::RefPtr<Gtk::Builder> m_builder;
        TodayTaskListColumns m_columns;
        
        Glib::RefPtr<Gtk::ListStore> m_dailyTasksTreeModel;
        std::unique_ptr<Gtk::TreeView> m_dailyTasksListView;
    };
}