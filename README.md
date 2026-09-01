Goal: Do a buffer overflow exploitation without use of any tutorial
I started off by writing a program vulnerable to this kind of exploit. For an overflow exploit the program must have implemented a function that does not have limit bounds on the input being taken in from the user. In my case i wrote a program that uses the functions `scanf()` and `printf()` to do the following:
(i) Take a user's name as the input using the `scanf()` function
(ii) Display the function code and the input prompt on STDOUT using the `printf()` function.
These creates two attack surfaces for the exploit.
Took me a minute to write the program compile it and then see that it satisfies the functionality as intended.
### (a) Compiling the Code
`gcc -o vuln vulnerablefile.c`
![](/images/image1.png)

### (b) Running the code
`./vuln`
![](/images/image2.png)

Decided to first overflow the `scanf()` and then observe how it affects the stack.
I overflowed it by inputting a very long string for the input. But before overflowing it we need to first check the status of the stack  before the `scan()` function is called in order to identify the memory addresses that would be overwritten by the overflowed data. For this activity I would be using <GNU gdb >debugger
### (a) Running gdb on the compiled ELF 
`gdb ./vuln`
![](/images/image3.png)
### (b) Setting a break point before the scanf() function
`break  greet`
The syntax for setting the breaking points is the keyword break followed by the name of a defined function within the program.
![](/images/image4.png)
### (c) Run the program inside GNU gdb
`run`
The expectation is for the program to pause the running after hitting the greet() so we can inspect the stack first.
### (d) Inspect the registers and their contents
`infor all-regisers`
![](/images/image4.png)
### (e) Continue the execution of program
`continue`
This would continue the program from the breaking point.
![](/images/image5.png)
Note: The scanf() functions seems to be taking input upto a whitespace and a null terminator so if one is to overflow the input buffer the name should not be having anywhitespaces else the function would cut the input at that point.
The gbd returned a SIGSEGV, segmentation fault signal - this seems to be a good sign that the overflow has occured since it failed to fit into the memory space of the input buffer.
### Reinspect the registers to see if there are any changes
The expectation is for the first registers to be the ones that get overwritten
![](/images/image6.png)
This are the characteristics that i looked for to determine if there was an actual overflow in the registers:
a) The return of the Segmentation fault signal
b) Different values on the registers information
Since I have been able to determine that there is an overflow now the next step is to  get a way to exploit the overflow as an attack surface of the program. This are what i could come up with.
(i) Heap exploitation
(ii) Redirecting the instruction pointer
I will try performing the two on the program and see how they work.
## Heap Exploitation
For this i would have to further understand the program intricacies for this i decided to use Radare for the disassembly of the binary so that i would understand how the  program interacts with the registers.
