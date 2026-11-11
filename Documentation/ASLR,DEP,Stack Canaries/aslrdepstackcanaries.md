# ASLR, DEP, and Stack Canaries

These three mechanisms are the foundation of modern memory-corruption defenses. A memory-corruption bug, such as a buffer overflow, can allow an attacker to overwrite data or redirect execution. Modern operating systems add protections to make such attacks harder to perform reliably.

## 1. ASLR (Address Space Layout Randomization)

ASLR randomizes the location of key memory regions, such as the stack, heap, and shared libraries. A position-independent executable (PIE) can also be relocated; a traditional non-PIE main executable may retain fixed code addresses. Exact behavior depends on the operating system and its configuration.

Why it matters:
- It reduces the reliability of direct code or data pointer attacks.
- It increases the difficulty of targeting fixed addresses.
- It creates an information problem: if the attacker can leak memory addresses, exploitation becomes much easier.

This is why information-disclosure vulnerabilities are so valuable in memory-corruption exploitation.

## 2. DEP / NX (Data Execution Prevention / No-eXecute)

DEP/NX uses page permissions to prevent execution from memory regions marked non-executable. It blocks direct execution from such data pages, but does not by itself prevent memory corruption or code reuse.

In practice:
- The NX bit marks pages as non-executable.
- Attackers cannot simply inject machine code into a stack or heap buffer and execute it.
- Code-reuse techniques can still execute instructions from pages that are already executable, including:
  - ret2libc
  - ROP (Return-Oriented Programming)
  - JOP (Jump-Oriented Programming)

## 3. Stack Canaries

A stack canary is a guard value placed in a protected stack frame between some local data and control data. Compiler-generated checks compare it before returning from the function.

If the canary value is changed, the check normally terminates the process before the function returns. Canaries do not protect every object or detect every kind of memory corruption.

## Important Note

These are not perfect security mechanisms. They are mitigations, not guarantees. Vulnerabilities can still exist, and attackers may bypass them through leaks, reuse techniques, or unsafe assumptions in the program logic.
