#pragma once
#include <gtkmm.h>
#include <glog/logging.h>

#include "../cpp-chronology-lib/types/dailyrecord.h"
#include "../cpp-chronology-lib/utils/utils.h"

#include "columns.hpp"
#include "dailyTasksController.hpp"

namespace ui {
    class MainWindow : public Gtk::Window {
    public:
        MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
        virtual ~MainWindow();
        void StartInInitState();

    protected: // callbacks
        void AddTaskButton_clicked_cb();
        void NewWorklogDialogOkButton_clicked_cb();
        void RemoveTaskButton_clicked_cb();

    protected: // member widgets
        std::unique_ptr<Gtk::Button> m_AddTaskButton;
        
        Glib::RefPtr<Gtk::Builder> m_builder;
        TodayTaskListColumns m_columns;
        Glib::RefPtr<Gtk::ListStore> m_dailyTasksTreeModel;
        std::unique_ptr<Gtk::TreeView> m_dailyTasksListView;

        chronology::controllers::DailyTasksController m_dailyTasksController;
    };
}