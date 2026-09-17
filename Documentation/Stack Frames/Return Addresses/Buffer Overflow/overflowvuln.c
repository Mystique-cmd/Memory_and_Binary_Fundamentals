void vuln() {
	char buf[16];
	gets(buf); //no bound checking
}

int main(){
	vuln();
}


