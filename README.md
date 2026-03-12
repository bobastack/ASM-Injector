# ASM-Injector

A simple educational project showing how **x64 assembly shellcode** can be executed from a **C++ injector**.
# Payload
- The shellcode is small and only performs one task: calling `LoadLibraryA`.

```
BITS 64
default rel

payload_start:

    sub rsp, 28h        

    mov rax, 0x0000000000000000
                          ; we store LoadLibraryA address here

    call rax              ; call LoadLibraryA

    add rsp, 28h          ; restore stack

    ret
```

# Usage

1. run Notepad
2. Run the injector.
3. injector will inject the Module into notepad

If successful, the DLL will be loaded into the target process.

# Disclaimer

> This project is provided **for educational and research purposes only**.

⭐ If you found this useful, consider giving the repository a star.
