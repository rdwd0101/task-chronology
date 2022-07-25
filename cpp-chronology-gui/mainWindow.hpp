#pragma once
#include <gtkmm.h>
#include <glog/logging.h>

#include "columns.hpp"

namespace ui {
    class MainWindow : public Gtk::Window {
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