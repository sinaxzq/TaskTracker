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
    int secondId = manager.addTask("Add file saving").getId();
    int thirdId = manager.addTask("Add file loading").getId();

    manager.changeStatus(firstId, TaskStatus::InProgress);
    manager.changeStatus(secondId, TaskStatus::Done);
    manager.changeStatus(thirdId, TaskStatus::Todo);

    std::cout << "Original tasks:\n";
    printAllTasks(manager);

    bool saved = saveTasksToFile(manager, "tasks.txt");

    if (!saved)
    {
        std::cout << "Failed to save tasks\n";
        return 1;
    }

    TaskManager loadedManager;

    bool loaded = loadTasksFromFile(loadedManager, "tasks.txt");

    if (!loaded)
    {
        std::cout << "Failed to load tasks\n";
        return 1;
    }

    std::cout << "\nLoaded tasks:\n";
    printAllTasks(loadedManager);

    int fourthId = loadedManager.addTask("Task after loading").getId();

    std::cout << "\nAdded task after loading:\n";
    std::cout << "New task id: " << fourthId << "\n";

    std::cout << "\nFinal loaded manager state:\n";
    printAllTasks(loadedManager);

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