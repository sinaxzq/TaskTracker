#include "Task.h"

#include <string>
#include <utility>
#include <optional>

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

std::optional<TaskStatus> taskStatusFromInt(int value)
{
    switch (value)
    {
    case 0:
        return TaskStatus::Todo;
    case 1:
        return TaskStatus::InProgress;
    case 2:
        return TaskStatus::Done;
    default:
        return std::nullopt;
    }
}
