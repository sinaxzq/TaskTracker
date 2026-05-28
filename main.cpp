#include "Task.h"
#include "TaskManager.h"
#include "TaskStorage.h"

#include <cctype>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>

namespace
{
const std::string StorageFile = "tasks.txt";

void printTask(const Task& task)
{
    std::cout << task.getId() << " | " << task.getTitle() << " | "
              << taskStatusToString(task.getStatus()) << "\n";
}

void printAllTasks(const TaskManager& manager)
{
    if (manager.getTasks().empty())
    {
        std::cout << "No tasks\n";
        return;
    }

    for (const Task& task : manager.getTasks())
    {
        printTask(task);
    }
}

void printUsage()
{
    std::cout << "Usage:\n";
    std::cout << "  TaskTrackerApp list\n";
    std::cout << "  TaskTrackerApp add \"Task title\"\n";
    std::cout << "  TaskTrackerApp done <id>\n";
    std::cout << "  TaskTrackerApp remove <id>\n";
    std::cout << "  TaskTrackerApp rename <id> \"New title\"\n";
    std::cout << "  TaskTrackerApp status <id> <todo|progress|done>\n";
}

bool loadExistingTasks(TaskManager& manager)
{
    if (!std::filesystem::exists(StorageFile))
    {
        return true;
    }

    return loadTasksFromFile(manager, StorageFile);
}

bool saveTasks(const TaskManager& manager)
{
    return saveTasksToFile(manager, StorageFile);
}

std::optional<int> parseId(const std::string& text)
{
    if (text.empty())
    {
        return std::nullopt;
    }

    for (char ch : text)
    {
        if (ch < '0' || ch > '9')
        {
            return std::nullopt;
        }
    }

    try
    {
        int id = std::stoi(text);

        if (id <= 0)
        {
            return std::nullopt;
        }

        return id;
    }
    catch (...)
    {
        return std::nullopt;
    }
}

std::optional<TaskStatus> parseStatus(const std::string& text)
{
    if (text == "todo")
    {
        return TaskStatus::Todo;
    }

    if (text == "progress")
    {
        return TaskStatus::InProgress;
    }

    if (text == "done")
    {
        return TaskStatus::Done;
    }

    return std::nullopt;
}
} // namespace

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printUsage();
        return 1;
    }

    TaskManager manager;

    if (!loadExistingTasks(manager))
    {
        std::cout << "Failed to load tasks\n";
        return 1;
    }

    const std::string command = argv[1];

    if (command == "list")
    {
        printAllTasks(manager);
        return 0;
    }

    if (command == "add")
    {
        if (argc < 3)
        {
            std::cout << "Missing task title\n";
            return 1;
        }

        Task& task = manager.addTask(argv[2]);

        if (!saveTasks(manager))
        {
            std::cout << "Failed to save tasks\n";
            return 1;
        }

        std::cout << "Added task with id " << task.getId() << "\n";
        return 0;
    }

    if (command == "done")
    {
        if (argc < 3)
        {
            std::cout << "Missing task id\n";
            return 1;
        }

        std::optional<int> id = parseId(argv[2]);

        if (!id)
        {
            std::cout << "Invalid task id\n";
            return 1;
        }

        if (!manager.changeStatus(*id, TaskStatus::Done))
        {
            std::cout << "Task not found\n";
            return 1;
        }

        if (!saveTasks(manager))
        {
            std::cout << "Failed to save tasks\n";
            return 1;
        }

        std::cout << "Task marked as done\n";
        return 0;
    }

    if (command == "remove")
    {
        if (argc < 3)
        {
            std::cout << "Missing task id\n";
            return 1;
        }

        std::optional<int> id = parseId(argv[2]);

        if (!id)
        {
            std::cout << "Invalid task id\n";
            return 1;
        }

        if (!manager.removeTask(*id))
        {
            std::cout << "Task not found\n";
            return 1;
        }

        if (!saveTasks(manager))
        {
            std::cout << "Failed to save tasks\n";
            return 1;
        }

        std::cout << "Task removed\n";
        return 0;
    }

    if (command == "rename")
    {
        if (argc < 4)
        {
            std::cout << "Missing task new title\n";
            return 1;
        }

        std::optional<int> id = parseId(argv[2]);

        if (!id)
        {
            std::cout << "Invalid task id\n";
            return 1;
        }

        if (!manager.renameTask(*id, argv[3]))
        {
            std::cout << "Task not found\n";
            return 1;
        }
        
        if (!saveTasks(manager))
        {
            std::cout << "Failed to save tasks\n";
            return 1;
        }

        std::cout << "Task renamed\n";
        return 0;
    }

    if (command == "status")
    {
        if (argc < 4)
        {
            std::cout << "Missing task id or status\n";
            return 1;
        }

        std::optional<int> id = parseId(argv[2]);

        if (!id)
        {
            std::cout << "Invalid task id\n";
            return 1;
        }

        std::optional<TaskStatus> status = parseStatus(argv[3]);

        if (!status)
        {
            std::cout << "Invalid status\n";
            return 1;
        }

        if (!manager.changeStatus(*id, *status))
        {
            std::cout << "Task not found\n";
            return 1;
        }

        if (!saveTasks(manager))
        {
            std::cout << "Failed to save tasks\n";
            return 1;
        }

        std::cout << "Task status changed\n";
        return 0;
    }

    std::cout << "Unknown command\n";
    printUsage();
    return 1;
}