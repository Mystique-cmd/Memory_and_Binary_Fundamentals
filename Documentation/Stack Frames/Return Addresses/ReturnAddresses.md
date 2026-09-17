Return address is the value that tells the CPU where to resume execution after a function finishes.
When a function is called the CPU executes a CALL instruction. This instruction does two things:
a) Pushes the address of the next instruction ( the return address ) onto the stack
b) Jumps to the function's entry point
When the function ends the RET instruction pops that return address off the stack and jumps back to it.
On the stack the return address sits just above the saved base pointer ( %rbp) and local variables. This make it vulnerable is a buffer overflow overwrites local variables, it can also overwrite the return address. Once corrupted the CPU will jump to whatever address you've injected - which is the basis of buffer overflow exploits and ROP chains
