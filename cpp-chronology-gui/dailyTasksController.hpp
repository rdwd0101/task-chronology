#pragma once
#include <gtkmm.h>

#include "columns.hpp"
#include "../cpp-chronology-lib/providers/YamlDatabaseProvider.h"
#include "../cpp-chronology-lib/providers/YamlDatabaseProvider.h"
#include "../cpp-chronology-lib/managers/worklogDBManager.h"
#include <iostream>

namespace chronology
{
    namespace controllers
    {
        class DailyTasksController
        {
        private:
            std::unique_ptr<chronology::managers::WorklogDBManager> m_dbManager;
            Glib::RefPtr<Gtk::ListStore> m_dailyTasksTreeModel;
            ui::TodayTaskListColumns m_columns;
        
        public:
            DailyTasksController()
             : m_dbManager(std::make_unique<managers::WorklogDBManager>("worklogs.yaml"))
            {
            }

            void SetModel(const Glib::RefPtr<Gtk::ListStore>& model)
            {
                m_dailyTasksTreeModel = model;
            }

            void Load()
            {
                m_dbManager->Load();

                for (const auto& item : m_dbManager->records)
                {
                    AddRecordToUI(item);
                }
            }

            void AddRecordToUI(const chronology::types::DailyRecord& record)
            {
                std::cout << std::endl;
                std::cout << record.task_name << "\n";
                std::cout << record.description << "\n";
                std::cout << record.hours << "\n";
                
                
                Gtk::TreeModel::Row row = *(m_dailyTasksTreeModel->append());
                row[m_columns.m_task_name] = record.task_name; //nameEntryPtr->get_text();
                row[m_columns.m_task_description] = record.description; //descEntryPtr->get_text();
                row[m_columns.m_hours] = record.hours; //std::stof(timeEntryPtr->get_text().c_str());
            }

            void AddRecord(const chronology::types::DailyRecord& record)
            {
                // add record to DB
                m_dbManager->AddRecord(record);

                // update ui
                AddRecordToUI(record);
            }
        };
    }
}