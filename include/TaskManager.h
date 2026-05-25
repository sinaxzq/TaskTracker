#pragma once

#include "Task.h"

#include <string>
#include <vector>

class TaskManager
{
	std::vector<Task> tasks;
	int nextId = 1;

public:
	Task& addTask(std::string title);

	bool removeTask(int id);

	Task* findTask(int id);
	const Task* findTask (int id) const;

	bool changeStatus(int id , TaskStatus newStatus);

	const std::vector<Task>& getTasks() const;

	bool renameTask(int id , std::string newTitle);

	int removeTasksByStatus(TaskStatus status);
};