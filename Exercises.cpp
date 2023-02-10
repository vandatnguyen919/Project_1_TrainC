#include <stdio.h>
#include <stdlib.h> 
#include "LoginSystem.h"

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
