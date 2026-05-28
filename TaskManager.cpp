#include "TaskManager.h"
#include "Task.h"

#include <string>
#include <utility>
#include <vector>

Task& TaskManager::addTask(std::string title)
{
    tasks.emplace_back(nextId, std::move(title));
    nextId++;
    return tasks.back();
}

bool TaskManager::removeTask(int id)
{
    for (auto it = tasks.begin(); it != tasks.end(); it++)
    {
        if (it->getId() == id)
        {
            tasks.erase(it);
            return true;
        }
    }
    return false;
}

Task* TaskManager::findTask(int id)
{
    for (auto& task : tasks)
    {
        if (task.getId() == id)
            return &task;
    }
    return nullptr;
}
const Task* TaskManager::findTask(int id) const
{
    for (auto& task : tasks)
    {
        if (task.getId() == id)
            return &task;
    }
    return nullptr;
}

bool TaskManager::changeStatus(int id, TaskStatus newStatus)
{
    auto t = findTask(id);
    if (t)
    {
        t->setStatus(newStatus);
        return true;
    }
    return false;
}

const std::vector<Task>& TaskManager::getTasks() const
{
    return tasks;
}

bool TaskManager::renameTask(int id, std::string newTitle)
{
    auto ptr = findTask(id);

    if (ptr)
    {
        ptr->setTitle(std::move(newTitle));
        return true;
    }

    return false;
}

int TaskManager::removeTasksByStatus(TaskStatus status)
{
    int removedCount = 0;

    for (std::vector<Task>::iterator it = tasks.begin(); it != tasks.end();)
    {
        if (it->getStatus() == status)
        {
            it = tasks.erase(it);
            removedCount++;
        }
        else
        {
            it++;
        }
    }

    return removedCount;
}

void TaskManager::clear()
{
    tasks.clear();
    nextId = 1;
}

bool TaskManager::addTaskWithId(int id, std::string title, TaskStatus status)
{

    if (id <= 0 || findTask(id) != nullptr)
        return false;

    Task& task = tasks.emplace_back(Task(id, std::move(title)));
    task.setStatus(status);

    if (id >= nextId)
    {
        nextId = id + 1;
    }

    return true;
}