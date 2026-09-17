They tell you how functions communicate at machine code level.
It answers questions like:
(i) Where do function arguments go?
(ii) Where is the return address placed?
(iii) Which registers must be preserved?
(iv) Who cleans up the stack?
(v) How is the stack aligned?
(vi) How does the function know where its local variables are?
A calling convention defines several things:
### Arguments
Where are arguments placed?
Example: On modern x86-64 Linux the first integer arguments go to:
a) rdi
b) rsi
c) rdx
e) rcx
f) r8
g) r9
### Return Value
Where does the function put its result?
For normal integer/pointer returns on x86-64:
rax
### Registers
They have different roles given by the calling convention.
For the commong x86-64 System V ABI used by Linux
a) rdi - 1st integer/pointer argument
b) rsi - 2nd
c) rdx - 3rd
d) rcx - 4th
r8 - 5th
r9 - 6th
rax - return value
rsp - stack pointer
rbp -frame/ base pointer when used
rip - instruction pointer
There are also registers classified according to whether a function must preserve them
### Caller-saved vs Callee-saved
In caller-saved registers the caller must assume that the following registers can be destroyed by the called functions
rax, rcx, rdx, rdi, rsi, r8, r9, r10, r11
### Callee saved registers
The callee must preserve this registers
For system Vx86-64:
rbx, rbp, r12, r13, r14, r15
When modified they have to be restored before returning. 
The distincition becomes very important when reading assembly and understandign ROP chains, register contrl and function calls

The calling convention differ from one OS to another. 
For example for Windows  x64
a) rcx - 1st argument
b) rdx - 2nd argument
c) r8 - 3rd 
d) r9 - 4th
e) rax - return
When there are more than 6 arguments in the System V x86-64 the remaining arguments are passed through the stack 
### Floating Point Arguments
On x86-64 System V they generally use XMM registers, rather than the general purpose.
The return value generally comes back in XMM0
### Variadic Functions
These are functions that do not have a fixed number of arguments and understaing ABI is useful when analyzing such functions including:
`printf()`, `scanf()`, `sprintf`
