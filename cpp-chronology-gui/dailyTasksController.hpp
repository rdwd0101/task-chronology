#pragma once
#include <gtkmm.h>

#include "columns.hpp"
#include "../cpp-chronology-lib/database/DatabaseWrapper.h"
#include "../cpp-chronology-lib/database/WorklogDb.h"

#include <iostream>

namespace chronology
{
    namespace controllers
    {
        class DailyTasksController
        {
        private:
            std::unique_ptr<chronology::WorklogDb> _db;
            Glib::RefPtr<Gtk::ListStore> m_dailyTasksTreeModel;
            ui::TodayTaskListColumns m_columns;

            std::string _dbName = "worklog.db";
        
        public:
            DailyTasksController()
            {
                _db = std::make_unique<chronology::WorklogDb>();
                _db->load(_dbName);
            }

            void SetModel(const Glib::RefPtr<Gtk::ListStore>& model)
            {
                m_dailyTasksTreeModel = model;
            }

            void Load()
            {
                _db->requestAllItems();

                while (true)
                {
                    chronology::types::DailyRecord item;
                    
                    if (!_db->getItemStep(item))
                    {
                        break;
                    }
                    AddRecordToUI(item);
                }
            }

            void AddRecordToUI(const chronology::types::DailyRecord& record)
            {
                // add record to model
                Gtk::TreeModel::Row row = *(m_dailyTasksTreeModel->append());
                row[m_columns.m_uuid] = record.uuid;
                row[m_columns.m_task_name] = record.task_name; //nameEntryPtr->get_text();
                row[m_columns.m_task_description] = record.description; //descEntryPtr->get_text();
                row[m_columns.m_hours] = record.hours; //std::stof(timeEntryPtr->get_text().c_str());
                
                Glib::Date date;
                date.set_time(record.date);
                row[m_columns.m_date] = date.format_string("%F");
            }

            void AddRecord(const chronology::types::DailyRecord& record)
            {
                // add record to DB
                _db->add(record);

                // update ui
                m_dailyTasksTreeModel->clear();
                Load();
            }

            void RemoveRecord(const std::string& uuid)
            {
                // remove record from DB
                _db->remove(uuid);

                // update ui
                m_dailyTasksTreeModel->clear();
                Load();
            }
        };
    }
}