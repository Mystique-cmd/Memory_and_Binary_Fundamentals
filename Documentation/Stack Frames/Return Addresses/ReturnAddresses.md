# Return Addresses

A return address is the value that tells the CPU where to resume execution after a function finishes.

On x86/x86-64, a near `CALL` instruction does two things:

1. It pushes the address of the next instruction onto the stack as the return address.
2. It jumps to the function's entry point.

When the function ends, `RET` pops that address from the stack and jumps back to it. Other architectures may use different instructions or a link register.

## Where it lives on the stack

With a conventional frame-pointer prologue on x86-64, the return address is at a higher address than the saved `%rbp`, while local variables are commonly at lower addresses. This layout is not guaranteed: compilers may omit the frame pointer, optimize locals into registers, or eliminate a frame entirely.

If a buffer overflow overwrites local data, it can also overwrite the return address. Once that value is corrupted, the CPU can jump to an attacker-controlled location. This is the basis for both classic buffer-overflow exploits and ROP chains.

## Why it matters

Return addresses are central to exploitation because they determine control flow after a function returns. If an attacker can influence them, they can redirect execution to arbitrary code or re-used gadgets.
