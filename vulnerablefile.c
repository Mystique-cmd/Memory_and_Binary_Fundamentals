/*
The program can become vulnerable the moment it uses a function that does not have any bounds on the input from the user
For this case i will use a simple function that uses the scanf() function and printf() function
*/
#include <stdio.h>
void greet (char *name)
{
    printf("What is your name?\n");
    scanf("%s",name);
    printf("Good Morning %s\n", name);
}
int main()
{
    char name;
    greet(&name);
}