#include "Task.h"
#include "TaskManager.h"

#include <iostream>
#include <string>

using std::cout;

void printTask(const Task& task);
void printAllTasks(const TaskManager& manager);

int main()
{
    std::cout << "main\n";

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