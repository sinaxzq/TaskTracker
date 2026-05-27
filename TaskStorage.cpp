#include "TaskManager.h"
#include "TaskStorage.h"

#include <string>
#include <fstream>

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