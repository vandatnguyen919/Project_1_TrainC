#include <string.h>

#define MAX 100
#define ACC_FILE "account.txt" 

struct Account{
	char email[MAX];
	char username[MAX];
	char password[MAX];
} typedef Account; 
 
void Register() {
	
	FILE *f;
	
	// Open/Create and read the file
	f = fopen(ACC_FILE,"a+");
	if (f == NULL) {
		printf("Cannot open/create a file.");
		exit(1);
	}

	Account p,p2;
	char confirmPas[MAX];
	//Enter email and username
	printf("Enter your email: "); scanf("%s", &p.email);
	Beep(432, 300);
	printf("Enter your username: "); scanf("%s", &p.username);
	Beep(432, 300);

	// Scan and check email and username the in file
	rewind(f);
	while (!feof(f)) {
		fscanf(f, "%s %s %s",&p2.email,&p2.username,&p2.password);
		if (!strcmp(p.email,p2.email) || !strcmp(p.username,p2.username)) {
			printf("This email/username is already taken.\n");
			Beep(432, 300);
			fclose(f);
			return;
		} 
	}
	fclose(f);
	// Enter and confirm password
	printf("Enter your password: "); scanf("%s", &p.password);
	Beep(432, 300);
	do {
		printf("Confirm your password: "); scanf("%s", &confirmPas);
		Beep(432, 300);
		if (strcmp(p.password,confirmPas)) printf("Try again! ") ;
	} while (strcmp(p.password,confirmPas));
	f = fopen(ACC_FILE,"a");
	// Print and save account in file 
	fprintf(f,"%s %s %s\n",p.email,p.username,p.password);
	printf("Your registration is successful.\n");
	Beep(432, 300);
	fclose(f);
}
bool Login() {
	
	FILE *f;
	
	// Open and read the file
	f = fopen(ACC_FILE,"r");
	if (f == NULL) {
		printf("Cannot open/create a file.");
		exit(1);
	}
	Account p, p2;
	
	//Enter username and password
	printf("Enter your username: "); scanf("%s",&p.username);
	Beep(432, 300);
	printf("Enter your password: "); scanf("%s",&p.password);
	Beep(432, 300);
	
	// Scan username and password in file 
	while (!feof(f)) {
		fscanf(f, "%s %s %s",&p2.email,&p2.username,&p2.password);
		if (!strcmp(p.username,p2.username) && !strcmp(p.password,p2.password)) {
			fclose(f);
			return true;
		} 
	}
	fclose(f);
	return false;	
}
void ForgotPas() {
	
	FILE *f;
	
	// Open and read the file
	f = fopen(ACC_FILE,"r");
	Account p,p2;
	
	//Enter email and username
	printf("Enter your email: "); scanf("%s",&p.email);
	Beep(432, 300);
	printf("Enter your username: "); scanf("%s",&p.username);
	Beep(432, 300);
	
	// Scan email and username in the file
	bool found = false;
	while (!feof(f)) {
		fscanf(f, "%s %s %s",&p2.email,&p2.username,&p2.password);
		if (!strcmp(p.email,p2.email) && !strcmp(p.username,p2.username)) {
			found = true;
			break;
		}
	}
	// Check
	if (found) {
		printf("Found! Here is your password: %s\n",p2.password);
		Beep(432, 300);
	}
	else {
		printf("Sorry :( Cannot find your account.\n");
		Beep(432, 300);
	}
	fclose(f);
}
bool BacktoLogin() {
	int n;
	printf("Enter \"0\" to return to Login Interface "); scanf("%d", &n);
	Beep(432, 300);
	return n == 0;
}
