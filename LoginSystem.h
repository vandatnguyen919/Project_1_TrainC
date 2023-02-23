#include <string.h>

#define MAX 100
#define STU_FILE "student.txt" 
#define ADM_FILE "admin.txt"


struct Account{
	char email[MAX];
	char username[MAX];
	char password[MAX];
} typedef Account; 
 
void Register() {
	
	FILE *f;

	//Align text to the center
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(console, &consoleInfo);
	int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
	char text1[] = "-------------------------";
	char text2[] = "REGISTER                 "; 
	
	int padding = (consoleWidth - sizeof(text1)) / 2;
	printf("%*s%s%*s\n",padding, "", text1, padding, "");
	printf("%*s%s%*s\n",padding, "", text2, padding, "");
	
	// Open/Create and read the file
	f = fopen(STU_FILE,"a+");
	if (f == NULL) {
		printf("Cannot open/create a file.");
		exit(1);
	}

	Account p,p2;
	char confirmPas[MAX];
	//Enter email and username
	char text3[] = "Enter your email: "; 
	char text4[] = "Enter your username: ";
	printf("%*s%s",padding, "", text3); scanf("%s", &p.email);
	printf("%*s%s",padding, "", text4); scanf("%s", &p.username);

	// Scan and check email and username the in file
	rewind(f);
	while (!feof(f)) {
		fscanf(f, "%s %s %s",&p2.email,&p2.username,&p2.password);
		if (!strcmp(p.email,p2.email) || !strcmp(p.username,p2.username)) {
			printf("This email/username is already taken.\n");
			fclose(f);
			return;
		} 
	}
	fclose(f);
	
	// Enter and confirm password
	char text5[] = "Enter your password: ";
	char text6[] = "Confirm your password: ";
	printf("%*s%s",padding, "", text5); scanf("%s", &p.password);
	getchar();
	do {
		printf("%*s%s",padding, "", text6); scanf("%s", &confirmPas);
		if (strcmp(p.password,confirmPas)) printf("Try again!\n") ;
	} while (strcmp(p.password,confirmPas));
	
	f = fopen(STU_FILE,"a");
	// Print and save account in file 
	fprintf(f,"%s %s %s\n",p.email,p.username,p.password);
	printf("Your registration is successful.\n");
	fclose(f);
}

int Login(Account *person) {

	FILE *f;
	
	//Align text to the center	
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(console, &consoleInfo);
	int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
	char text1[] = "-------------------------"; 
	char text2[] = "LOGIN                    ";
	char text3[] = "1. Student               "; 
	char text4[] = "2. Admin                 "; 
	char text5[] = "Choice: "; 

	int padding = (consoleWidth - sizeof(text1)) / 2;
	printf("%*s%s%*s\n",padding, "", text1, padding, "");
	printf("%*s%s%*s\n",padding, "", text2, padding, "");
	printf("%*s%s%*s\n",padding, "", text3, padding, "");
	printf("%*s%s%*s\n",padding, "", text4, padding, "");
	printf("%*s%s",padding, "", text5);

	int n; scanf("%d", &n);
	switch (n) {
		case 1: 
			// Open and read the student file
			f = fopen(STU_FILE,"r");
			break;
		case 2:
			// Open and read the admin file
			f = fopen(ADM_FILE,"r");
			break;
		default:
			return 0;
	}
	if (f == NULL) {
		printf("Cannot open/create a file.");
		exit(1);
	}
	
	Account p, p2;
	
	//Enter username and password
	char text6[] = "Enter your username: "; 
	char text7[] = "Enter your password: "; 
	printf("%*s%s",padding, "", text6); scanf("%s",&p.username);
	printf("%*s%s",padding, "", text7); scanf("%s",&p.password);

	// Scan username and password in file 
	while (!feof(f)) {
		fscanf(f, "%s %s %s",&p2.email,&p2.username,&p2.password);
		if (!strcmp(p.username,p2.username) && !strcmp(p.password,p2.password)) {
			fclose(f);
			strcpy(person->username, p.username);
			return n;
		} 
	}
	fclose(f);
	return 0;	
}

void ForgotPas() {
	
	FILE *f;
	
	//Align text to the center
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(console, &consoleInfo);
	int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
	char text1[] = "-------------------------"; 
	char text2[] = "FORGOT PASSWORD?         "; 
	
	int padding = (consoleWidth - sizeof(text1)) / 2;
	printf("%*s%s%*s\n",padding, "", text1, padding, "");
	printf("%*s%s%*s\n",padding, "", text2, padding, "");
	
	// Open and read the file
	f = fopen(STU_FILE,"r");
	Account p,p2;
	
	//Enter email and username
	char text3[] = "Enter your email: ";
	char text4[] = "Enter your username: ";
	printf("%*s%s",padding, "", text3); scanf("%s",&p.email);
	printf("%*s%s",padding, "", text4); scanf("%s",&p.username);
	
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
		printf("Found :D Here is your password: %s\n",p2.password);
	}
	else {
		printf("Sorry :( Cannot find your account.\n");
	}
	fclose(f);
}

bool BacktoLogin() {
	int n;
	printf("Enter \"0\" to return to Login Interface: "); scanf("%d", &n);
	Beep(432, 300);
	return n == 0;
}
