#pragma once
#include <gtkmm.h>

#include "columns.hpp"
#include "../cpp-chronology-lib/providers/IDatabaseProvider.h"
#include "../cpp-chronology-lib/providers/YamlDatabaseProvider.h"
#include "../cpp-chronology-lib/managers/worklogDBManager.h"

namespace chronology
{
    namespace controllers
    {
        class DailyTasksController
        {
        private:
            std::unique_ptr<chronology::managers::WorklogDBManager> m_dbManager;
            std::shared_ptr<chronology::providers::YamlDatabaseProvider> m_dbProvider;
            Glib::RefPtr<Gtk::ListStore> m_dailyTasksTreeModel;
            ui::TodayTaskListColumns m_columns;
        
        public:
            DailyTasksController(const Glib::RefPtr<Gtk::ListStore>& model)
             : m_dbProvider(std::make_shared<chronology::providers::YamlDatabaseProvider>())
             , m_dailyTasksTreeModel(model)
            {
                m_dbManager = std::make_unique<chronology::managers::WorklogDBManager>(m_dbProvider);
            }

            void Load()
            {
                // TODO: return data:
                return;
                m_dbManager->Load("worklog_database.yaml");
                std::vector<chronology::types::DailyRecord> list;

                for (const auto& item : list)
                {
                    AddRecordToUI(item);
                }
            }

            void AddRecordToUI(const chronology::types::DailyRecord& record)
            {
                Gtk::TreeModel::Row row = *(m_dailyTasksTreeModel->append());
                row[m_columns.m_task_name] = record.task_name; //nameEntryPtr->get_text();
                row[m_columns.m_task_description] = record.description; //descEntryPtr->get_text();
                row[m_columns.m_hours] = record.hours; //std::stof(timeEntryPtr->get_text().c_str());
            }

            void AddRecord(const chronology::types::DailyRecord& record)
            {
                // add record to DB

                // update ui
                AddRecordToUI(record);
            }
        };
    }
}