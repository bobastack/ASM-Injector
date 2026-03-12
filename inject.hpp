#pragma once
#include <Windows.h>
#include <string>

bool inject(DWORD pid, const std::string& dllPath);