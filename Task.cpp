#include "Task.h"

#include <string>
#include <utility>

Task::Task(int id, std::string title) : id(id), title(std::move(title)), status(TaskStatus::Todo) {}

int Task::getId() const
{
    return id;
}

const std::string& Task::getTitle() const
{
    return title;
}

TaskStatus Task::getStatus() const
{
    return status;
}

void Task::setTitle(std::string newTitle)
{
    title = std::move(newTitle);
}

void Task::setStatus(TaskStatus newStatus)
{
    status = newStatus;
}

std::string taskStatusToString(TaskStatus status)
{
    switch (status)
    {
    case TaskStatus::Done:
        return "Done";
    case TaskStatus::Todo:
        return "Todo";
    case TaskStatus::InProgress:
        return "InProgress";
    }

    return "Unknown";
}
