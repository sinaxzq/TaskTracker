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

void testRenameTask()
{
	TaskManager manager;

	int firstId = manager.addTask("First").getId();
	
	bool renamed = manager.renameTask(firstId, "FirstChanged");

	assert(renamed);
	assert(manager.findTask(firstId)->getTitle() == "FirstChanged");
}

void testRenameTaskInvalidId()
{
	TaskManager manager;

	int firstId = manager.addTask("First").getId();

	bool renamed = manager.renameTask(999 , "FirstChanged");

	assert(!renamed);
	assert(manager.getTasks()[0].getTitle() == "First");
}

void testRemoveTasksByStatus()
{
	TaskManager manager;
	int firstId = manager.addTask("First").getId();
	int secondId = manager.addTask("Second").getId();
	int thirdId = manager.addTask("Third").getId();
	int fourthId = manager.addTask("Fourth").getId();

	manager.changeStatus(secondId , TaskStatus::Done);
	manager.changeStatus(fourthId , TaskStatus::Done);

	int count = manager.removeTasksByStatus(TaskStatus::Done);

	assert(count == 2);
	assert(manager.getTasks().size() == 2);

	assert(manager.findTask(firstId) != nullptr);
	assert(manager.findTask(secondId) == nullptr);
	assert(manager.findTask(thirdId) != nullptr);
	assert(manager.findTask(fourthId) == nullptr);
}

void testRemoveTasksByStatusNoMatches()
{
	TaskManager manager;
	int firstId = manager.addTask("First").getId();

	int count = manager.removeTasksByStatus(TaskStatus::Done);

	assert(count == 0);
	assert(manager.getTasks().size() == 1);
	assert(manager.findTask(firstId) != nullptr);
}

void runTaskManagerTests()
{
	testAddTask();
	testChangeStatus();
	testChangeStatusInvalidId();
	testRemoveTask();
	testRemoveTaskInvalidId();
	testRenameTask();
	testRenameTaskInvalidId();
	testRemoveTasksByStatus();
	testRemoveTasksByStatusNoMatches();
}

