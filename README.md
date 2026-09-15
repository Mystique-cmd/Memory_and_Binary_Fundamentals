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
![](images/image1.png)
From the output we can see that it indicates the memory addresses to the different section of the executable. It also indicates the absolute path of the executable and the file type of the file.

Then disassemble the executable with the following command.
`dissasemble vuln `
The expectation is to get an assembly program code.
This command writes the code in assembly language
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

The tool i decided to use to look into the binary file was radare2 a tool that i was not that much familiar with so i had to first learn it and as i was playing around with it i fell into the disassembly section where i saw it was possible to understand how the program worked with the registers and at what memory addresses and with that i could be able to utiiize that to exploit the overflow presence put forth by the presence of the insecure functions
`r2 vuln`
`v`
![](images/image7.png)
Under the functions section there was also the presence of the `puts()` function which i had not explicitly used on the code in the vulnerablefile.c to me it appears like underneath that function though it was removed from the standard library seems to be still used under the hood. 
To start with i would want to do the allocator bookkeepinid overwrite since it is the most basic one
