Function Arguments in stack frames are the first layer of data that gets placed when a function is called.
They define how values are passed into the function, and depending on the architecture and calling convention, they may live in registers or spill inot the stack

## How Function Arguments Are Stored
i) Registers first - On System V AMD64 the first six integer/ pointer arguments go into registers : %rdi, %rsi, %rdx, %rcx, %r8, %r9.
On Windows x64, the first four go into %rcx, %rdx, %r8, %r9
ii) Stack Spill - If there are more arguments than the registers can hold, the extras are pushed onto the stack
(iii) Alignment - The stack pointer %rsp is aligned to 16bytes before a call. Arguments are padded if necessary to maintain alignement

## Why this matters in Exploitation
i) Buffer Overflows - if arguments spill onto the stack, they sit right next to local variables and saved registers and these are prime targets for corruption
ii) ROP Chains - Understanding which arguments are in registers vs stack lets you craft payloads correctly
iii) Reverse Engineering - Recognizing argument placement helps reconstruct function prototypes from disassembly

In the file "funcarg.c"
- a -> %rdi
- b -> %rsi
- c -> %rdx
- d -> %rcx
- e -> %r8
- f -> %r9
- g -> pushed onto the stack

## Reading the Stack 
# Compile With Debug Symbols
``` gcc -O0 -g -fno-stack-protector funcarg.c -o funcarg 
	#-O0 no optimization ( keeps stack frames readable)
	# -g includes debug symbols
	# -fno-stack-protector  disables stack canaries so you can see raw memory
```

# Launch gdb
 
 ` gdb ./funcarg `
	
# Set Breakpoint at Sum

``` 
	break sum
	run 
```
This will stop the execution right when sum is called.
# Inspect Register

` info registers `

Notice the first six arguments in the registers

# Inspect the Stack
Dumping memory at the stack pointer
``` 
	x/16gx $rsp
	# x - examine memory
	#/16 - show 16 entries
	# g - each entry is a "giant word" (8 bytes )
	# x - display in hexadecimal
	# $rsp - start at the current stack pointer register
```
![](./images/image1.png)
0x0000000000000007 - represents the 7th argument. The other entries represent return addresses, frame pointers and runtime library addresses.

![](./images/image2.png)

