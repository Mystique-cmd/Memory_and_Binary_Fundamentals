These are the three core memory-corruption defenses.
A memory corruption bug -such as buffer overflow - can potentially let an attacker corrupt data or redirect execution.
Modern OSes add defenses to make that harder
(i) ASLR ( Address Space Layout Randomization ) - randomizes memory addresses thus protecting form predictable addresses. This creates an information problem and taht is why information disclosure vulnerabilities are extremelly valuable in memory corruption exploitation
(ii) DEP ( Data Execution Prevention )/ NX ( No-eXecute) - do not execute code from data memory thus protecting from injected shellcode. This is implemented using the NX bit thus because of that execution restriction attacker developed techniques that reuse code already present in executable memory introducing concepts like ret2libc, ROP( Return Oriented Programming ) JOP( Jump Oriented Programming )
(iiI) Stack Canary - delete stack corruption thus preventing stack based buffer overflows. It uses the canary which the compiler places between the buffer and control data and the program knows what its value should be and if it defers during return then it means the canary was corrupted.
These are not perfect security mechanism but mitigations and vulnerabilities can still exist
