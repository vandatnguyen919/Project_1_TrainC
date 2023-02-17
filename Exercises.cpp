#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "LoginSystem.h"
#include "App.h"

int main () {
	
	LoginInterface:
	system("cls");
	system("COLOR 0F");
	printf("----------------Login Interface-----------------\n1.Login\n2.Register\n3.Forgot your password?\n0.Exit\nChoice: ");
	
	int choice; scanf("%d",&choice);
	Beep (432, 300);
	switch (choice) {
		case 0:
			break;
		case 1: 
			if (Login()) {
				printf("Login succeed!\n");
				Beep (432, 300);
				Menu();
				break;
			}
			else {
				printf("Login failed!\n");
				Beep (432, 300);
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
