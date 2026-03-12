BITS 64
default rel

payload_start:

    sub rsp, 28h        

    mov rax, 0x0000000000000000
                          ; we store LoadLibraryA address here

    call rax              ; call LoadLibraryA

    add rsp, 28h          ; restore stack

    ret