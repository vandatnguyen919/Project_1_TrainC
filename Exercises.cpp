#include <stdio.h>
#include <stdlib.h> 
#include "LoginSystem.h"
#include "App.h"

int main () {
	
	LoginInterface:
	system("cls");
	printf("***MENU***\n1.Login\n2.Register\n3.Forgot your password?\n0.Exit\nChoice: ");
	int choice; scanf("%d",&choice);
	switch (choice) {
		case 0:
			break;
		case 1: 
			if (Login()) {
				printf("Login succeed!\n");
				Menu();
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
