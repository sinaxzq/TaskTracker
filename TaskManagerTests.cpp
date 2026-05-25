#include "TaskManagerTests.h"
#include "TaskManager.h"

#include <cassert>

void testAddTask()
{
	TaskManager manager;

	int id = manager.addTask("First").getId();

	assert(id == 1);
	assert(manager.getTasks().size() == 1);
	assert(manager.getTasks()[0].getTitle() == "First");
	assert(manager.getTasks()[0].getStatus() == TaskStatus::Todo);
}

void testChangeStatus()
{
	TaskManager manager;

	int id = manager.addTask("First").getId();

	bool changed = manager.changeStatus(id , TaskStatus::Done);

	assert(changed);
	assert(manager.findTask(id)->getStatus() == TaskStatus::Done);
}

void testChangeStatusInvalidId()
{
	TaskManager manager;

	bool changed = manager.changeStatus(999, TaskStatus::Done);

	assert(!changed);
}

void testRemoveTask()
{
	TaskManager manager;

	int firstId = manager.addTask("First").getId();
	int secondId = manager.addTask("Second").getId();

	bool removed = manager.removeTask(firstId);

	assert(removed);
	assert(manager.getTasks().size() == 1);
	assert(manager.findTask(firstId) == nullptr);
	assert(manager.findTask(secondId) != nullptr);
}

void testRemoveTaskInvalidId()
{
	TaskManager manager;

	int firstId = manager.addTask("First").getId();

	bool removed = manager.removeTask(999);

	assert(!removed);
	assert(manager.getTasks().size() == 1);
}

void runTaskManagerTests()
{
	testAddTask();
	testChangeStatus();
	testChangeStatusInvalidId();
	testRemoveTask();
	testRemoveTaskInvalidId();
}