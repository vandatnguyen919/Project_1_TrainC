void Menu() {
	
	int choice;
	
	system("cls");
	printf("---------------WELCOME TO eFCode---------------\n");
	printf("1.Purchase\n2.Add to cart\n0.Exit\nChoice: ");
	scanf("%d", &choice);
	
	switch (choice) {
		case 1:
			printf("First choice.\n");
			Menu();
			break;
		case 2:
			printf("Second choice.\n");
			Menu();
			break;
	}
}

