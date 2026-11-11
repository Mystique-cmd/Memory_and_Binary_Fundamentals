# Calling Conventions

Calling conventions define how functions communicate at the machine-code level. They answer questions such as:

- Where are function arguments placed?
- Where is the return address stored?
- Which registers must be preserved?
- Who cleans up the stack?
- How is the stack aligned?
- How does a function locate its local variables?

A calling convention specifies the rules that both the caller and callee must follow when interacting.

## Function Arguments

Where are arguments placed?

On modern x86-64 Linux (System V ABI), the first integer or pointer arguments are passed in registers:

1. `rdi`
2. `rsi`
3. `rdx`
4. `rcx`
5. `r8`
6. `r9`

If more arguments are needed, the remaining values are passed in a stack argument area. The caller need not implement this as a series of individual `push` instructions.

## Return Value

Where does the function place its result?

For normal integer or pointer return values on x86-64, the result is typically placed in:

- `rax`

## Register Roles

Registers serve different purposes depending on the ABI.

For the common x86-64 System V ABI used on Linux:

- `rdi` - 1st integer/pointer argument
- `rsi` - 2nd argument
- `rdx` - 3rd argument
- `rcx` - 4th argument
- `r8` - 5th argument
- `r9` - 6th argument
- `rax` - return value
- `rsp` - stack pointer
- `rbp` - callee-saved register; it may be used as a frame pointer, but optimized code often uses it for general purposes
- `rip` - instruction pointer

## Caller-saved vs Callee-saved Registers

Registers are classified by whether the caller or callee must preserve them.

### Caller-saved registers

The caller must assume that the following registers may be clobbered by the callee:

- `rax`, `rcx`, `rdx`, `rdi`, `rsi`, `r8`, `r9`, `r10`, `r11`

### Callee-saved registers

The callee must preserve the following registers and restore them before returning:

- `rbx`, `rbp`, `r12`, `r13`, `r14`, `r15`

This distinction is especially important when reading assembly, understanding ROP chains, and analyzing function calls.

## Differences Between Platforms

Calling conventions differ between operating systems.

For Windows x64:

1. `rcx` - 1st argument
2. `rdx` - 2nd argument
3. `r8` - 3rd argument
4. `r9` - 4th argument
5. `rax` - return value

On System V x86-64, integer/pointer arguments beyond the first six use the stack argument area. Windows x64 passes the first four integer/pointer arguments in `rcx`, `rdx`, `r8`, and `r9`, and reserves caller-provided shadow space; later arguments use the stack.

## Floating-Point Arguments

On x86-64 System V, floating-point arguments use XMM registers according to the ABI's separate argument classification. Their return values typically come back in `xmm0`.

## Variadic Functions

Variadic functions are functions that accept a variable number of arguments. Understanding the ABI is crucial for analyzing functions such as:

- `printf()`
- `scanf()`
- `sprintf()`

These functions rely on calling convention rules to access arguments correctly.
