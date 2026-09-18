# ASLR, DEP, and Stack Canaries

These three mechanisms are the foundation of modern memory-corruption defenses. A memory-corruption bug, such as a buffer overflow, can allow an attacker to overwrite data or redirect execution. Modern operating systems add protections to make such attacks harder to perform reliably.

## 1. ASLR (Address Space Layout Randomization)

ASLR randomizes the location of key memory regions, such as the stack, heap, libraries, and executable image. This makes it difficult for an attacker to predict addresses ahead of time.

Why it matters:
- It reduces the reliability of direct code or data pointer attacks.
- It increases the difficulty of targeting fixed addresses.
- It creates an information problem: if the attacker can leak memory addresses, exploitation becomes much easier.

This is why information-disclosure vulnerabilities are so valuable in memory-corruption exploitation.

## 2. DEP / NX (Data Execution Prevention / No-eXecute)

DEP prevents code from being executed from memory regions marked as data. This blocks classic shellcode injection attacks.

In practice:
- The NX bit marks pages as non-executable.
- Attackers cannot simply inject machine code into a stack or heap buffer and execute it.
- Instead, attackers often reuse existing code already present in memory, leading to techniques such as:
  - ret2libc
  - ROP (Return-Oriented Programming)
  - JOP (Jump-Oriented Programming)

## 3. Stack Canaries

A stack canary is a secret value placed between a local buffer and control data on the stack. When the function returns, the program checks whether the canary was modified.

If the canary value is changed, the program detects stack corruption and aborts before execution can continue. This helps prevent classic stack-based buffer-overflow exploitation.

## Important Note

These are not perfect security mechanisms. They are mitigations, not guarantees. Vulnerabilities can still exist, and attackers may bypass them through leaks, reuse techniques, or unsafe assumptions in the program logic.
