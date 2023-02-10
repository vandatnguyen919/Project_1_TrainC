#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define MAX 100

struct Account{
	char email[MAX];
	char username[MAX];
	char password[MAX];
}; 

void Register();
bool Login();
void ForgotPas();

void LoginInterface() {
	
}

int main () {
	
	LoginInterface:
	printf("\n***MENU***\n1.Login\n2.Register\n3.Forgot your password?\n0.Exit\nChoice: ");
	int choice; scanf("%d",&choice);
	switch (choice) {
		case 0:
			break;
		case 1: 
			if (Login()) {
				printf("Login succeed!\n");
				goto LoginInterface;
			}
			else {
				printf("Login failed!\n");
				goto LoginInterface;
			}
		case 2: 
			Register();
			goto LoginInterface;
		case 3:
			ForgotPas();
			goto LoginInterface;
	}
	
	return 0;	
}

void Register() {
	
	FILE *f;
	
	// Open/Create and read the file
	f = fopen("account.txt","a+");
	if (f == NULL) {
		printf("Cannot open/create a file.");
		exit(1);
	}
	Account p,p2;
	char confirmPas[MAX];
	//Enter email and username
	printf("Enter your email: "); scanf("%s", &p.email);
	printf("Enter your username: "); scanf("%s", &p.username);
	
	// Scan and check email and username the in file
	rewind(f);
	while (!feof(f)) {
		fscanf(f, "%s %s %s",&p2.email,&p2.username,&p2.password);
		if (!strcmp(p.email,p2.email) || !strcmp(p.username,p2.username)) {
			printf("This email/username is already taken.\n");
			fclose(f);
			return;
		} 
		else {
			break;
		}
	}
	fclose(f);
	// Enter and confirm password
	printf("Enter your password: "); scanf("%s", &p.password);
	do {
		printf("Confirm your password: "); scanf("%s", &confirmPas);
		if (strcmp(p.password,confirmPas)) printf("Try again! ") ;
	} while (strcmp(p.password,confirmPas));
	f = fopen("account.txt","a");
	// Print and save account in file 
	fprintf(f,"%s %s %s\n",p.email,p.username,p.password);
	printf("Your registration is successful.\n");
	fclose(f);
}
bool Login() {
	
	FILE *f;
	
	// Open and read the file
	f = fopen("account.txt","r");
	if (f == NULL) {
		printf("Cannot open/create a file.");
		exit(1);
	}
	Account p, p2;
	
	//Enter username and password
	printf("Enter your username: "); scanf("%s",&p.username);
	printf("Enter your password: "); scanf("%s",&p.password);
	
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
	f = fopen("account.txt","r");
	Account p,p2;
	
	//Enter email and username
	printf("Enter your email: "); scanf("%s",&p.email);
	printf("Enter your username: "); scanf("%s",&p.username);
	
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
	}
	else {
		printf("Sorry :( Cannot find your account.\n");
	}
	fclose(f);
}

//Iu Dung





















