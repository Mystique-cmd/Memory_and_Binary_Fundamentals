# Return Addresses

A return address is the value that tells the CPU where to resume execution after a function finishes.

When a function is called, the CPU executes a `CALL` instruction. This does two things:

1. It pushes the address of the next instruction onto the stack as the return address.
2. It jumps to the function's entry point.

When the function ends, the `RET` instruction pops that address from the stack and jumps back to it.

## Where it lives on the stack

The return address usually sits just above the saved base pointer (`%rbp`) and below local variables in the stack frame. This makes it a critical target in memory corruption.

If a buffer overflow overwrites local data, it can also overwrite the return address. Once that value is corrupted, the CPU can jump to an attacker-controlled location. This is the basis for both classic buffer-overflow exploits and ROP chains.

## Why it matters

Return addresses are central to exploitation because they determine control flow after a function returns. If an attacker can influence them, they can redirect execution to arbitrary code or re-used gadgets.
