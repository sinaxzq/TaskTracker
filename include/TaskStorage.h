#pragma once

#include "TaskManager.h"

#include <string>

bool saveTasksToFile(const TaskManager& manager, const std::string& filename);