#pragma once
#include <gtkmm.h>

namespace ui {
    class MainWindow : public Gtk::Window {
    public:
        MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
        virtual ~MainWindow();

    protected: // signals
        void AddTaskButton_clicked_cb();

    protected: // member widgets
        std::unique_ptr<Gtk::Button> m_AddTaskButton;
        std::unique_ptr<Gtk::ListBox> m_TasksList;
        Glib::RefPtr<Gtk::Builder> m_builder;
    };
}