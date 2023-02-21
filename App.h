//#include "LoginSystem.h"

#define MAX 100
#define BOOK_FILE "book.txt"

void AddBook();
void SearchBook();
void SearchMember();
bool BacktoMenu();

struct Book{
	char BookName[MAX];
} typedef Book;

void StudentMenu() {
	
	Menu:
	int choice;
	
	system("cls");
	printf("---------------------------------Hello, WELCOME TO eFCode\n");
	printf("1.Search books\n2.Borrow a book\n3.Return the book\nChoice: ");
	scanf("%d", &choice);
	
	switch (choice) {
		case 1:
			SearchBook();
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 2:
			printf("Second choice.\n");
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 3:
			printf("Third choice.\n");
			if (BacktoMenu()) {
				goto Menu;
			} else break;	
	}
 }

void AdminMenu() {

	Menu:
	int choice;
	
	system("cls");
	printf("---------------------------Hello Admin, WELCOME TO eFCode\n");
	printf("1.Add a book\n2.Update\n3.Search books\n4.Search members\n5.Return the book\nChoice: ");
	scanf("%d", &choice);
	
	switch (choice) {
		case 1:
			AddBook();
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 2:
			printf("Second choice.\n");
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 3:
			SearchBook();
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 4:
			SearchMember();
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 5:
			printf("Fifth choice.\n");
			if (BacktoMenu()) {
				goto Menu;
			} else break;	
	}
}

void AddBook() {
	
	char line[MAX];
	FILE *f;
	
	Book b;
	f = fopen(BOOK_FILE, "a");
	if (f == NULL) {
		printf("Cannot open/create a file.\n");
		exit(1);
	}
	printf("Add a book: "); 
	getchar();
	fgets(b.BookName, sizeof(line), stdin);
	
	fprintf(f, "%s", b.BookName);
	printf("The book is added.\n");
	fclose(f);
}

void Update() {
	
} 

void SearchBook() {
	
	char line[MAX];
	int countBook = 0;
	FILE *f;
	
	Book b;
	f = fopen(BOOK_FILE, "r");
	if (f == NULL) {
		printf("Cannot open/create a file.\n");
		exit(1);
	}
	printf("Books:\n");
	while (fgets(line, sizeof(line), f) != NULL) {
		countBook++;
		printf("%d. %s", countBook, line);
	}
	fclose(f);
}

void SearchMember() {
	
	char line[MAX];
	int countStudent = 0;
	FILE *f;
	
	Account p;
	f = fopen(STU_FILE, "r");
	if (f == NULL) {
		printf("Cannot open/create a file.\n");
		exit(1);
	}
	printf("Members:\n");
	while (fgets(line, sizeof(line), f) != NULL) {
		countStudent++;
	}
	fseek(f, 0, SEEK_SET);
	for (int i = 1; i <= countStudent; i++) {
		fscanf(f, "%s %s %s", &p.email, &p.username, &p.password);
		printf("%d. %s\n", i, p.username);
	}
	printf("TOTAL: %d\n", countStudent);
	fclose(f);
}

bool BacktoMenu() {
	int n;
	printf("Enter \"0\" to return to Menu: "); scanf("%d", &n);
	return n == 0;
}










