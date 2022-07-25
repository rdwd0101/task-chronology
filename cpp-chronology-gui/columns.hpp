#pragma once
#include <gtkmm.h>

namespace ui
{
    class TodayTaskListColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:
        TodayTaskListColumns()
        {
            add(m_task_name);
            add(m_task_description);
            add(m_hours);
        }
    public:
        Gtk::TreeModelColumn<Glib::ustring> m_task_name;
        Gtk::TreeModelColumn<Glib::ustring> m_task_description;
        Gtk::TreeModelColumn<float> m_hours;
    };
}