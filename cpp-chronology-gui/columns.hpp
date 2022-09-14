#pragma once
#include <gtkmm.h>

namespace ui
{
    class TodayTaskListColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:
        TodayTaskListColumns()
        {
            add(m_uuid);
            add(m_task_name);
            add(m_task_description);
            add(m_hours);
            add(m_date);
        }
    public:
        Gtk::TreeModelColumn<Glib::ustring> m_uuid;
        Gtk::TreeModelColumn<Glib::ustring> m_task_name;
        Gtk::TreeModelColumn<Glib::ustring> m_task_description;
        Gtk::TreeModelColumn<double> m_hours;
        Gtk::TreeModelColumn<Glib::ustring> m_date;
    };
}