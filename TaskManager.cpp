#include "TaskManager.h"
#include "Task.h"

#include <vector>
#include <string>
#include <utility>

Task& TaskManager::addTask(std::string title)
{
	tasks.emplace_back(nextId, std::move(title));
	nextId++;
	return tasks.back();
}

bool TaskManager::removeTask(int id)
{
	for (auto it = tasks.begin(); it!=tasks.end(); it++)
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
		if (task.getId() == id) return &task;
	}
	return nullptr;
}
const Task* TaskManager::findTask(int id) const
{
	for (auto& task : tasks)
	{
		if (task.getId() == id) return &task;
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

bool TaskManager::renameTask(int id , std::string newTitle)
{
	auto ptr = findTask(id);

	if (ptr)
	{
		ptr->setTitle(std::move(newTitle));
		return true;
	}

	return false;
}

