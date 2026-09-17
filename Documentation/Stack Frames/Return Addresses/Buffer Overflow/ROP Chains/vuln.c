#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern void *system(const char *); // dummy referene to allow for nm -D to return output

void vuln() {
	char buf[64];
	gets(buf);
}

int main(){
	system("echo hi");
	vuln();
	return 0;
}


