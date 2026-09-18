Goal: Do a buffer overflow exploitation.
I started off by writing a program vulnerable to this kind of exploit. For an overflow exploit the program must have implemented a function that does not have limit bounds on the input being taken in from the user. In my case i wrote a program that uses the functions `scanf()` and `printf()` to do the following:
(i) Take a user's name as the input using the `scanf()` function
(ii) Display the function code and the input prompt on STDOUT using the `printf()` function.
These creates two attack surfaces for the exploit.
Took me a minute to write the program compile it and then see that it satisfies the functionality as intended.
### (a) Compiling the Code
The compilarion needs to be with the protections disabled thus the use of the command below:
`gcc -g -O0 -fno-stack-protector -no-pie -z execstack vulnerablefile.c -o vuln`

### (b) Running the code
This is for typically trying to understand what it is that I am trying to overwrite. For this task I will be using the GNU gdb (Debian 17.1-4) 17.1

The first step is to run the compiled file inside the gdb using the following command to lauch the debugger on the terminal:
`gdb `
 
Load the executable into the debugger with the following command:
`file ./vuln`

You can preview the file information with :
`info files`
![](/images/image1.png)
From the output we can see that it indicates the memory addresses to the different section of the executable. It also indicates the absolute path of the executable and the file type of the file.

Then disassemble the executable with the following command. The argument after the keyword is a function name.
`dissasemble greet `
![](/images/image2.png)
We can see that the tool performs an assembly dump of the  vulnerable function greet. It shows the memory addresses the syscalls made the registers use and the symbols used.

### (c) Finding the overflow offset.
The overflow offset is the number of bytes that i would need to put into an overflowing input before i reach a specific piece of data that i want to overwrite
For the generation of the overflow input we can use pwntools. It is a python framework for binary exploitation and Capture The Flag ( CTF) work. It provides convinient fucntions for interacting with programs, manipulating binary data , debugging and building exploit experiments. To generate the input I used the following steps.
(i) Create a virtual environemnt with :
`python -m venv venv`
(ii) Activated the virtual environment
`source venv/bin/venv`
(iii) Installed the pwn module
`pip install pwn`
(iv) Ran the following command to get the overflow input. For a 64bit X86-64 system then the best approach is to use the 8-byte cyclic pattern where we specify n=8 otherwise pwntools would use its default n=4
`python3 -c 'from pwn import *; print(cyclic(200, n=8).decode())`

The next step is now to run the executable and feed the input data. Inside gdb:
`run`
![](images/image3.png)
As expected the program crashed signaled by the segmentation fault error output.
After this I inspected the registers with:
`info registers rbp rsi rip`
The focus being on the following registers: rip , rbp and rsp . This is so that i can be able to determing which part of the cyclic pattern reached the saved return address.
![](images/image4.png)
I observed that the patterns for the rbp register looked like a ASCII pattern data instead of a normal stack address but the rip seems to have remained intact and rbp got overwritten.. Now from here I can find the rbp offset by using the pwntools still and we also have to specify the use of 8 bytes pattern
`python3 -c 'from pwn import *; print(cyclic_find(0x6261616162616161, n=8))`

![](images/image5.png)
The value 1 in this case is not the offset buffer to the RIP as we expected it is the offset of the byte sequence inside the generated pattern because of this we need to do some more digging. To see the value of the saved rip 
`info frame`
![](images/image6.png)
It is evident that the value of the current rbp and that of the saved rip are different. This means the rip was actually overwritten but also suggest that the program is taking in the supplied pattern input in a different way than I thought earlier calling for a need to do the inspection of the stack frame.
`disassemble main`
![](images/image7.png)
`disassemble greet`
![](images/image8.png)
`x/40gx 0x7fffffffdbe0`
![](images/image9.png)
Looking at the disassembly the instructions such as `sub    $0x10,%rsp` tell how much stack space was allocated while instructions such as `lea    -0x1(%rbp),%rax` tell where the input buffer sits relative to the rbp. From the disassembly we can also confirm that the compiler placed the input object at an unusual place thus the output 1, it was placed at rbp-1 indicated by the instruction `lea -0x1(%rbp),%rax`
To now get the rip offset we expect it to be at 9 from the command note we are using the value of the saved rip ( from info frame:
`python3 -c 'from pwn import*; print(cyclic_find(0x6361616161616161))'`
Given that our offset is 9bytes then the basic payload structure would be: [payload syntax](payload.py)

### (d) Creating the exploit
[exploit code](exploit.py)
Run the exploit
`python exploit.py`
The exploit above is one to simply confirm the overwritting of the offset buffer.

