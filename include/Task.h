#pragma once

#include <string>
#include <optional>

enum class TaskStatus
{
    Todo,
    InProgress,
    Done
};

std::string taskStatusToString(TaskStatus status);

std::optional<TaskStatus> taskStatusFromInt(int value);

class Task
{
    int id;
    std::string title;
    TaskStatus status;

  public:
    Task(int id, std::string title);

    int getId() const;
    const std::string& getTitle() const;
    TaskStatus getStatus() const;

    void setTitle(std::string newTitle);
    void setStatus(TaskStatus newStatus);
};
