#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "LoginSystem.h"
#include "App.h"

int main () {
	
	LoginInterface:
	system("cls");
		
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(console, &consoleInfo);
	int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
	char text1[] = "-----Login Interface-----"; 
	char text2[] = "1. Login";
	char text3[] = "2. Register";
	char text4[] = "3. Forgot your password?";
	char text5[] = "0. Exit";
	char text6[] = "Choice: ";
	char text7[] = "-------------------------"; 
	
	int padding = (consoleWidth - sizeof(text1)) / 2;
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("%*s%s%*s\n",padding, "", text1, padding, "");
	printf("%*s%s%*s\n",padding, "", text2, padding, "");
	printf("%*s%s%*s\n",padding, "", text3, padding, "");
	printf("%*s%s%*s\n",padding, "", text4, padding, "");
	printf("%*s%s%*s\n",padding, "", text5, padding, "");
	printf("%*s%s",padding, "", text6);

	int choice; scanf("%d",&choice);
	printf("%*s%s%*s\n",padding, "", text7, padding, "");
	switch (choice) {
		case 0:
			break;
		case 1: 
			int n;
			n = Login();
			if (n == 1) {
				printf("Login succeed!\n");
				StudentMenu();
				break;
			}
			else if (n == 2) {
				printf("Login succeed!\n");
				AdminMenu();
				break;
			}
			else {
				printf("Login failed!\n");
				if (BacktoLogin()) {
					goto LoginInterface;
				} else break;
			}
		case 2: 
			Register();
			if (BacktoLogin()) {
				goto LoginInterface;
			} else break;
			
		case 3:
			ForgotPas();
			if (BacktoLogin()) {
				goto LoginInterface;
			} else break;
			
		default: 
			printf("Invalid number!\n");
			if (BacktoLogin()) {
				goto LoginInterface;
			} else break;
	}
	
	return 0;	
}
