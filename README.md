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
