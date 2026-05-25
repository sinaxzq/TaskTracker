#include "Task.h"
#include "TaskManager.h"
#include "TaskManagerTests.h"

#include <iostream>
#include <string>

using std::cout;


void printTask(const Task& task);
void printAllTasks(const TaskManager& manager);

int main()
{
	runTaskManagerTests();

	std::cout << "All tests passed\n";

	return 0;
}

void printTask(const Task& task)
{
	std::cout
		<< task.getId() << " | "
		<< task.getTitle() << " | "
		<< taskStatusToString(task.getStatus())
		<< "\n";
}

void printAllTasks(const TaskManager& manager)
{
	for (const Task& task : manager.getTasks())
	{
		printTask(task);
	}
}