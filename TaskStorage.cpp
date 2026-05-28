#include "TaskManager.h"
#include "TaskStorage.h"
#include "Task.h"

#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <optional>


bool saveTasksToFile(const TaskManager& manager , const std::string& filename)
{
    std::ofstream file(filename);

    if (!file)
        return false;
    
    
    for (auto& task : manager.getTasks())
    {
        file << task.getId() << ';' 
            << task.getTitle() 
            << ';' << static_cast<int>(task.getStatus())
             << '\n';
    }

    return true;
};

bool loadTasksFromFile(TaskManager& manager, const std::string& filename)
{
    TaskManager loadedManager;
    std::ifstream stream(filename);

    if (!stream)
        return false;

    std::string line;

    while (std::getline(stream, line))
    {
        std::string idText;
        std::string title;
        std::string statusIdText;
        std::istringstream isstream(line);

        if (!std::getline(isstream, idText, ';') || !std::getline(isstream, title, ';') ||
            !std::getline(isstream, statusIdText))
            return false;
        
        int id;
        std::optional<TaskStatus> status;

        try
        {
            id = std::stoi(idText);
            status = taskStatusFromInt(std::stoi(statusIdText));
        }
        catch (...)
        {
            return false;
        }

        if (!status)
            return false;

        if (!loadedManager.addTaskWithId(id, title, *status))
            return false;
    }

    manager = loadedManager;

    return true;
}
