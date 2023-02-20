 void StudentMenu() {
	int choice;
	
	system("cls");
	printf("---------------Hello Student, WELCOME TO eFCode\n");
	printf("1.Search a book\n2.Borrow a book\n3.Return the book\nChoice: ");
	scanf("%d", &choice);
	
	switch (choice) {
		case 1:
			printf("First choice.\n");
			StudentMenu();
			break;
		case 2:
			printf("Second choice.\n");
			StudentMenu();
			break;
		case 3:
			printf("Third choice.\n");
			StudentMenu();
			break;	
	}
 }
void AdminMenu() {
	int choice;
	
	system("cls");
	printf("---------------Hello Admin, WELCOME TO eFCode\n");
	printf("1.Add a book\n2.Update\n3.Search a book\n4.Search a member\n5.Return the book\nChoice: ");
	scanf("%d", &choice);
	
	switch (choice) {
		case 1:
			printf("First choice.\n");
			AdminMenu();
			break;
		case 2:
			printf("Second choice.\n");
			AdminMenu();
			break;
		case 3:
			printf("Third choice.\n");
			AdminMenu();
			break;
		case 4:
			printf("Fourth choice.\n");
			AdminMenu();
			break;
		case 5:
			printf("Fifth choice.\n");
			AdminMenu();
			break;	
	}
}
