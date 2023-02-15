#ifndef App 
#define App

#include <stdio.h>
#include <stdlib.h>
 
void Menu() {
	int a = 0;
	int *choice;
	choice = &a;
	
	system("cls");
	printf("---WELCOME TO eFCode---\n");
	printf("1.Purchase\n2.Add to cart\n0.Exit\nChoice: ");
	scanf("%d", choice);
	
	switch (*choice) {
		case 1:
			break;
		case 2:
			break;
	}
	
}

#endif
