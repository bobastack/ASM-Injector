#include "inject.hpp"
#include "payload.hpp"
#include <iostream>
#include <cstring>

bool inject(DWORD pid, const std::string& Module)
{
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!process)
        return false;

    // patch shellcode with LoadLibraryA
    void* load = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    memcpy(&payload[6], &load, 8);

    SIZE_T size = Module.size() + 1;

    LPVOID String = VirtualAllocEx(
        process,
        nullptr,
        size,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_READWRITE
    );

    WriteProcessMemory(
        process,
        String,
        Module.c_str(),
        size,
        nullptr
    );

    LPVOID code = VirtualAllocEx(
        process,
        nullptr,
        Psize,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE
    );

    WriteProcessMemory(
        process,
        code,
        payload,
        Psize,
        nullptr
    );

    HANDLE thread = CreateRemoteThread(
        process,
        nullptr,
        0,
        (LPTHREAD_START_ROUTINE)code,
        String,
        0,
        nullptr
    );

    if (!thread)
        return false;

    CloseHandle(thread);
    CloseHandle(process);

    return true;
}