#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>
#include <cstring>
#include "inject.hpp"

DWORD find_process(const std::string& name)
{
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE)
        return 0;

    if (Process32First(snap, &pe))
    {
        do
        {
            if (strcmp(pe.szExeFile, name.c_str()) == 0)
            {
                CloseHandle(snap);
                return pe.th32ProcessID;
            }

        } while (Process32Next(snap, &pe));
    }

    CloseHandle(snap);
    return 0;
}

std::string get_module_path()
{
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    std::string full = path;
    size_t pos = full.find_last_of("\\/");

    return full.substr(0, pos + 1) + "Module.dll";
}

int main()
{
    DWORD pid = find_process("Notepad.exe");

    if (!pid)
    {
        std::cout << "Notepad not found\n";
		system("pause");    
        return 0;
    }

    std::string dll = get_module_path();

    std::cout << "Notepad PID: " << pid << "\n";
    std::cout << "DLL: " << dll << "\n";

    if (inject(pid, dll))
        std::cout << "Injected\n";
    else
        std::cout << "Injection failed\n";

    return 0;
}