#include "Task.h"
#include "TaskManager.h"
#include "TaskStorage.h"

#include <iostream>
#include <string>

using std::cout;

void printTask(const Task& task);
void printAllTasks(const TaskManager& manager);

int main()
{
    TaskManager manager;

    int firstId = manager.addTask("Learn C++ architecture").getId();
    int secondId = manager.addTask("Add CMake later").getId();
    int thirdId = manager.addTask("Write tests later").getId();

    manager.changeStatus(firstId, TaskStatus::InProgress);
    manager.changeStatus(thirdId, TaskStatus::Done);

    manager.removeTask(secondId);

    printAllTasks(manager);

    bool saved = saveTasksToFile(manager, "tasks.txt");

    if (!saved)
    {
        std::cout << "Failed to save tasks\n";
    }

    return 0;
}

void printTask(const Task& task)
{
    std::cout << task.getId() << " | " << task.getTitle() << " | "
              << taskStatusToString(task.getStatus()) << "\n";
}

void printAllTasks(const TaskManager& manager)
{
    for (const Task& task : manager.getTasks())
    {
        printTask(task);
    }
}