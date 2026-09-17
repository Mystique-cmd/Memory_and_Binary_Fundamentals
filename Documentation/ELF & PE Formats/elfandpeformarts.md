They are formats that turn compiled code into something an OS can load, map into memory , link, execute and sometimes inpect or modify.
ELF stands for Executable and Linkable Format - Linux
PE stands for Portable Executatbel - Windows
### ELF
It is commond in 
i) BSD
ii) Linux
iii) Unix-like systems
iv) Embedded systems
v) Android
It is made of the following structure ( simplified)
ELF File
ELF Header
Program Header Table
Sections
	(i) .text - executable machine code
	(ii) .rodata - read only data
	(iii) .data - initialized writable global / static variables
	(iv) .bss - uninitialised or zero initialized global / static data
	(v) .symtab
	(vii) .strtab ...
Section Header Table
There are two different ways of looking at an ELF file
a) Linking view - It is used heavily by compiler, linker , debugger and binary analysis tools and the view revolves around sections
b) Execution view - it is used by the OS loader and the view revolves around segments
### ELF Header
It is essentially the files ID and it can be inspected using:
` readelf -h program`
It contains information such as:
a) Magic number - it is the no at the beginning of an elf file and can be inspected using `xdd program | head `
b) Architecture
c) 32-bit / 64-bit
d) Endianness
e) Entry point
f) Program header location
g) Section header location
h) Number of sections
i) Numer of program headers
### Section vs  Segments
Sections primarily describe the executable to compiler, linker, debugger and binary-analysis tools
Segments describe wha the OS loader needs to map into memory. Here the permissions matter enormously
### ELF Program Headers
They are inspected using `readelf -l program `
You will see things such as "
(i) LOAD
(ii) INTERP
(iii) DYNAMIC 
(iv) GNU_STACK
(v) GNU_RELRO
### ELF Entry Point
Given the entry point as 0x0493892 does not mean that main() starts from there main is simply a C abstraction to the actual entry point since the CPU does not know what main is. The actual path is more like:
ELF entry >> _start >> runtime initialization >> __libc_start_main >> main()
### Dynamic Linking
Modern Linux programs frequently depend on shared libraries and ELF contains information describing these dependencies.
It can be checked by either of the following commands:
```
	ldd program 
	readelf -d program
```
You will encounter concepts like 
(i) DT_NEEDED
(ii) PLT
(iii) GOT
(iv) .dynamic
This ones are important for binary exploitation
## PE
It is used for things such as 
(i) .exe
(ii) .dll
(iii) .sys
Traditionaly they begin with MZ ( ASCII ) or 4D 5A . Also checked with a similar command to the ELF
` xdd program.exe | head ` This is the DOS header. 
This header contains information including a pointer to the PE header
## PE Signature
Denoted by `PE\0\0 ` it is found within the location specified by <el_ifanew> which is the pointer being refered to up here
### PE Optional Header
Despite the name it is extremely important for executable images
It contatins information such as:
(i) Entry point
(ii) Image Base
(iii) Section Alignment
(iv) File Alignment
(v) Image Size
(vi) Subsystem
(vii) DLL Characteristics
(viii) Data Directories
The actual entry address can conceptually be : Image Base + Address of Entry Point
### PE Sections
You will see sections such as:
(i) .text - executable code
(ii) .rdata - read-only data: strings , constants , read only tables
(iii) .data - writable initialized data
(iv) .rsrc - resources such as : icons, dialogs, version information, embedded resources
(v) .reloc - relocation information
This becomes important when the executable is not loaded at its preferred address.
### PE Data Directories
It points to structures such as:
(i) Export Table*
(ii) Import Table*
(iii) Resource Table
(iv) Exception Table*
(v) Certificate Table
(vi) Base Relocation Table*
(vii) Debug Information
(viii) TLS Information*
### PE Imports
When a Windows program calls a function `CreateFile()` the function is implemented in a Windows DLL rather than necessarily inside your executable. The PE contains import information describing its dependencies
This is roughly analogous to ELF's dynamic linking world
### PE Exports
DLLs can expose functions to ther programs and then another program can import those functions
Using the code in the file "hello.c" investigate:
` file hello`
![](images/image1.png)
`readelf -h hello`
[](images/image2.png)
`readelf -S hello`
[](images/image3.png)
`readelf -l hello`
[](images/image4.png)
`readelf -d hello`
[](images/image5.png)
`readelf -s hello`
[](images/image6.png)
`objdump -d hello`
[](images/image7.png)
The goal is not to understand every line but to answer:
a) What architecture is the  binary?
b) What is the entry point?
c) Where is .text?
d) Where is .data?
e) Which regions are executable?
f) What shared libraries does it depend on?
g) What is the relationship between the file layout and the process memory layout?


























