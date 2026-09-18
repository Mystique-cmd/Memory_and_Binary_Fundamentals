# ROP Chains

ROP stands for Return-Oriented Programming. A ROP chain is a sequence of existing instruction fragments, called gadgets, arranged so that execution flows from one gadget to the next by abusing the stack and the `RET` instruction.

This technique exists because stack frames contain return addresses. If an attacker can overwrite a return address, they can redirect execution without injecting new code.

## Why ROP exists

Modern mitigations such as DEP/NX prevent execution from writable memory, but they do not prevent the processor from executing code that already exists in the binary or shared libraries. ROP reuses harmless-looking instruction sequences that already exist in memory.

A ROP chain is not shellcode injection. It is code reuse.

![](./images/image1.png)

## What is a gadget?

A gadget is a short instruction sequence that ends with a `RET` instruction.

Example gadgets:

```asm
pop rdi; ret
add rax, rdi; ret
mov [rdi], rsi; ret
```

These gadgets are found naturally in binaries and libraries, especially in `libc`.

Useful tools for finding them include:

- ROPgadget
- `radare2`
- `objdump -d`

## Why ROP chains matter

ROP chains allow attackers to:

- set registers using `pop` gadgets
- call functions such as `system("/bin/sh")`
- write memory
- read memory
- pivot the stack
- bypass DEP/NX
- bypass ASLR with memory leaks
- achieve arbitrary code execution

## Why they are effective

Modern systems often block:

- executable stacks
- executable heaps
- writable code segments

But they still need to execute ordinary instructions from the program or libraries. ROP exploits this fact by chaining existing instructions in a controlled order.

## Practical workflow

1. Compile the vulnerable program without stack protections.
2. Find the address of `system` and the string `"/bin/sh"`.
3. Locate a `pop rdi; ret` gadget.
4. Build a payload that redirects execution through the gadgets in the desired order.

Example commands:

```bash
nm -D vuln | grep system
strings -a -t x /lib/x86_64-linux-gnu/libc.so.6 | grep "/bin/sh"
```

![](./images/image2.png)

## Summary

ROP chains demonstrate that the system can still be abused even when code injection is blocked. By reusing existing instructions and controlling the return-address flow, attackers can build arbitrary execution paths without writing new executable code into memory.
