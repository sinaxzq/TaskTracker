#include "TaskManagerTests.h"
#include "Task.h"
#include "TaskManager.h"
#include "TaskStorage.h"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <string>

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

    bool changed = manager.changeStatus(id, TaskStatus::Done);

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

    manager.addTask("First").getId();

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

    manager.addTask("First").getId();

    bool renamed = manager.renameTask(999, "FirstChanged");

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

    manager.changeStatus(secondId, TaskStatus::Done);
    manager.changeStatus(fourthId, TaskStatus::Done);

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

void testSaveAndLoadTasks()
{
    const std::string filename = "task_storage_test.txt";

    std::remove(filename.c_str());

    TaskManager original;

    int firstId = original.addTask("First").getId();
    int secondId = original.addTask("Second").getId();

    original.changeStatus(firstId, TaskStatus::InProgress);
    original.changeStatus(secondId, TaskStatus::Done);

    bool saved = saveTasksToFile(original, filename);
    assert(saved);

    TaskManager loaded;

    bool loadedSuccessfully = loadTasksFromFile(loaded, filename);
    assert(loadedSuccessfully);

    assert(loaded.getTasks().size() == 2);

    const Task* first = loaded.findTask(firstId);
    const Task* second = loaded.findTask(secondId);

    assert(first != nullptr);
    assert(second != nullptr);

    assert(first->getTitle() == "First");
    assert(first->getStatus() == TaskStatus::InProgress);

    assert(second->getTitle() == "Second");
    assert(second->getStatus() == TaskStatus::Done);

    std::remove(filename.c_str());
}

void testMissingFile()
{
    const std::string filename = "missing_tasks_file.txt";

    std::remove(filename.c_str());

    TaskManager manager;

    int existingId = manager.addTask("Existing").getId();
    bool loaded = loadTasksFromFile(manager, filename);

    assert(!loaded);

    Task* existing = manager.findTask(existingId);

    assert(existing != nullptr);
    assert(existing->getTitle() == "Existing");
}

void testLoadTasksFromInvalidStatusDoesNotOverwriteManager()
{
    const std::string filename = "invalid_status_tasks.txt";

    {
        std::ofstream file(filename);
        file << "1;Bad task;99\n";
    }

    TaskManager manager;
    int existingId = manager.addTask("Existing").getId();

    bool loaded = loadTasksFromFile(manager, filename);

    assert(!loaded);
    assert(manager.getTasks().size() == 1);

    const Task* existing = manager.findTask(existingId);

    assert(existing != nullptr);
    assert(existing->getTitle() == "Existing");

    std::remove(filename.c_str());
}

void testLoadTasksFromDuplicateIdFails()
{
    const std::string filename = "duplicate_id_tasks.txt";

    {
        std::ofstream file(filename);
        file << "1;First;0\n";
        file << "1;Duplicate;2\n";
    }

    TaskManager manager;
    int existingId = manager.addTask("Existing").getId();

    bool loaded = loadTasksFromFile(manager, filename);

    assert(!loaded);
    assert(manager.getTasks().size() == 1);

    const Task* existing = manager.findTask(existingId);

    assert(existing != nullptr);
    assert(existing->getTitle() == "Existing");

    std::remove(filename.c_str());
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
    testSaveAndLoadTasks();
    testMissingFile();
    testLoadTasksFromInvalidStatusDoesNotOverwriteManager();
    testLoadTasksFromDuplicateIdFails();
}
