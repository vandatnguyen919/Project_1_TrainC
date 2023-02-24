#include <time.h>

#define MAX 100
#define BOOK_FILE "book.txt"
#define BOOK_TEMP "booktemp.txt"
#define BOOK_BRW "bookborrow.txt"

struct Book{
	char BookName[MAX];
} typedef Book;

void AddBook();
void AddUpdate(Book *book);
void BorrowBook(Account *person);
void BorrowUpdate(Account *person, Book *book);
void ReturnBook(Account *person);
void ReturnUpdate(Account *person, Book *book);
void ReturnDate();
void ListBook();
void ListBorrowedBook();
void SearchBook();
void SearchMember();
void Update();
bool BacktoMenu();

void Logo() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(console, &consoleInfo);
	int consoleWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
	
	char line1[] = "##    ## ####  ####   ###  ####  ## ##";
	char line2[] = "##    ## ## ## ## ## ##### ## ## ## ##"; 
	char line3[] = "##    ## ####  ####  ## ## ####   ### "; 
	char line4[] = "##### ## ## ## ## ## ##### ## ##   ## "; 
	char line5[] = "##### ## ####  ## ## ## ## ## ##  ##  ";
	char line6[] = "--------------------------------------";
	char line7[] = "    ---WELCOME TO FCODE LIBRARY---    ";
	int padding = (consoleWidth - sizeof(line1)) / 2;
	printf("%*s%s%*s\n",padding, "", line1, padding, "");
	printf("%*s%s%*s\n",padding, "", line2, padding, "");
	printf("%*s%s%*s\n",padding, "", line3, padding, "");
	printf("%*s%s%*s\n",padding, "", line4, padding, "");
	printf("%*s%s%*s\n",padding, "", line5, padding, "");
	printf("%*s%s%*s\n",padding, "", line6, padding, "");
	printf("%*s%s%*s\n",padding, "", line7, padding, "");

} 

void StudentMenu(Account *person) {
	
	Menu:
	system("cls");
	Logo();
	
	int choice;
	printf("Hi, %s :D (student)\n", person->username);
	printf("1.Search a book\n2.List all books\n3.Borrow a book\n4.Return a book\n0.Exit\nChoice: ");
	scanf("%d", &choice);
	
	switch (choice) {
		case 1:
			SearchBook();
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 2:
			ListBook();
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 3:
			BorrowBook(person);
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 4:
			ReturnBook(person);
			if (BacktoMenu()) {
				goto Menu;
			} else break;	
	}
 }

void AdminMenu(Account *person) {

	Menu:
	system("cls");
	Logo();
	
	int choice;
	printf("Hi, %s :D (admin)\n", person->username);
	printf("1.Add a book\n2.Search a book\n3.Search members\n4.List all books\n5.List all borrowed books\n6.Borrow a book\n7.Return a book\n8.Check updated information\n9.Check return date\n0.Exit\nChoice: ");
	scanf("%d", &choice);
	
	switch (choice) {
		case 1:
			AddBook();
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 2:
			SearchBook();
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 3:
			SearchMember();
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 4:
			ListBook();
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 5:
			ListBorrowedBook();
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 6:
			BorrowBook(person);
			if (BacktoMenu()) {
				goto Menu;
			} else break;	
		case 7:
			ReturnBook(person);
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 8:
			Update();
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 9:
			ReturnDate();
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
	AddUpdate(&b);
	fclose(f);
}

void AddUpdate(Book *book) {
	
	time_t current_time;
	
	//Obtain current time
	current_time = time(NULL);
			
	FILE *f = fopen("updateInformation.txt", "a");
	if (f == NULL) {
		printf("Cannot open the file.\n");
		exit(1);
	}
	fprintf(f, "%s", ctime(&current_time));
	fprintf(f, "%s-->is added\n", book->BookName);
	fclose(f);
	printf("\nYour book is added on %s\n", ctime(&current_time));
} 

void BorrowBook(Account *person) {
	
	ListBook();
	
	//Open files
    FILE *f = fopen(BOOK_FILE, "r");
	if (f == NULL) {
		printf("Cannot open the file.\n");
		exit(1);
	} 
    FILE *f_temp = fopen(BOOK_TEMP, "w");
    if (f_temp == NULL) {
		printf("Cannot open the file.\n");
		fclose(f);
		exit(1);
	} 
	FILE *f_borrow = fopen(BOOK_BRW, "a");
	if (f_borrow == NULL) {
		printf("Cannot open the file.\n");
		fclose(f);
		fclose(f_temp);
		exit(1);
	} 
	//Read lines from original file and write them to temp file
	Book b;
	char line[MAX];
	int lineNum = 1, choice; 
	printf("Choose a book to borrow: "); scanf("%d", &choice);
	while (fgets(line, sizeof(line), f) != NULL) {
		if (lineNum != choice) {
			fprintf(f_temp, "%s", line);
		} else {
			fprintf(f_borrow, "%s", line);
			strcpy(b.BookName, line);
		}
		lineNum++;
	}
	
	fclose(f);
	fclose(f_temp);
	fclose(f_borrow);
	
	//Remove the old file
	if (remove(BOOK_FILE) != 0) {
		printf("Cannot remove the orignal file.\n");
		exit(1);
	}
	//Rename the temp file's name to the original file's name
	if (rename(BOOK_TEMP, BOOK_FILE) != 0) {
		printf("Cannot remane the temporary file.\n");
		exit(1);
	}
	BorrowUpdate(person, &b);
} 

void BorrowUpdate(Account *person, Book *book) {
	
	time_t current_time, future_time;
	
	//Obtain current time
	current_time = time(NULL);
	
	//Add 7 days
	future_time = current_time + (7 *24 * 60 * 60);
	
	FILE *f = fopen("updateInformation.txt", "a");
	if (f == NULL) {
		printf("Cannot open the file.\n");
		exit(1);
	}
	FILE *f2 = fopen("returnDate.txt", "a");
	if (f2 == NULL) {
		printf("Cannot open the file.\n");
		exit(1);
	}
	//Save in updateInformation file
	fprintf(f, "%s", ctime(&current_time));
	fprintf(f, "%s-->is borrowed by %s\n", book->BookName, person->username);
	
	//Save in returnDate file
	fprintf(f2, "%s", ctime(&future_time));
	fprintf(f2, "-->%s should return the book's name: %s", person->username, book->BookName);
	
	fclose(f);
	fclose(f2);
	
	printf("\nYou borrowed the book on %s", ctime(&current_time));
	printf("You have to return the book to the library on %s\n", ctime(&future_time));
} 

void ReturnDate() {
	
	FILE *f = fopen("returnDate.txt", "r");
	if (f == NULL) {
		printf("Cannot open the file.\n");
		exit(1);
	}
	char line[MAX];
	while (fgets(line, sizeof(line), f) != NULL) {
		printf("%s", line);
	}
	fclose(f);
}

void ListBook() {
	char line[MAX];
	int countBook = 0;
	FILE *f;
	
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
	printf("TOTAL: %d\n", countBook);
	fclose(f);
}

void ListMember() {
	
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

void ListBorrowedBook() {
	
	char line[MAX];
	int countBook = 0;
	FILE *f;
	
	Book b;
	f = fopen(BOOK_BRW, "r");
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

void ReturnBook(Account *person) {
	
	ListBorrowedBook();
	
	//Open files
    FILE *f = fopen(BOOK_FILE, "a");
	if (f == NULL) {
		printf("Cannot open the file.\n");
		exit(1);
	} 
    FILE *f_temp = fopen(BOOK_TEMP, "w");
    if (f_temp == NULL) {
		printf("Cannot open the file.\n");
		fclose(f);
		exit(1);
	} 
	FILE *f_borrow = fopen(BOOK_BRW, "r");
	if (f_borrow == NULL) {
		printf("Cannot open the file.\n");
		fclose(f);
		fclose(f_temp);
		exit(1);
	} 
	//Read lines from original file and write them to temp file
	Book b;
	char line[MAX];
	int lineNum = 1, choice; 
	printf("Choose a book to return: "); scanf("%d", &choice);
	while (fgets(line, sizeof(line), f_borrow) != NULL) {
		if (lineNum == choice) {
			fprintf(f, "%s", line);
			strcpy(b.BookName, line);
		} else {
			fprintf(f_temp, "%s", line);
		}
		lineNum++;
	}
	
	fclose(f);
	fclose(f_temp);
	fclose(f_borrow);
	
	//Remove the old file
	if (remove(BOOK_BRW) != 0) {
		printf("Cannot remove the orignal file.\n");
		exit(1);
	}
	//Rename the temp file's name to the original file's name
	if (rename(BOOK_TEMP, BOOK_BRW) != 0) {
		printf("Cannot rename the temporary file.\n");
		exit(1);
	}
	ReturnUpdate(person, &b);
	printf("Successful!\n");
} 

void ReturnUpdate(Account *person, Book *book) {
	
	time_t current_time;
	
	//Obtain current time
	current_time = time(NULL);
			
	FILE *f = fopen("updateInformation.txt", "a");
	if (f == NULL) {
		printf("Cannot open the file.\n");
		exit(1);
	}
	fprintf(f, "%s", ctime(&current_time));
	fprintf(f, "-->%s returned %s",person->username, book->BookName);
	fclose(f);
	printf("\nYour book is returned on %s\n", ctime(&current_time));
}

void Update() {
	
	FILE *f = fopen("updateInformation.txt", "r");
	if (f == NULL) {
		printf("Cannot open the file.\n");
		exit(1);
	}
	char line[MAX];
	while (fgets(line, sizeof(line), f) != NULL) {
		printf("%s", line);
	}
	fclose(f);
}

void SearchBook() {
	
	ListBook();
	
	FILE *f = fopen(BOOK_FILE, "r");
	if (f == NULL) {
		printf("Cannot open the file.\n");
		exit(1);
	}
	
	printf("Enter the name of a book: ");
	Book b;
	getchar();
	fgets(b.BookName, sizeof(b.BookName), stdin);
	char line[MAX];
	int lineNum = 1;
	bool found = false;
	while (fgets(line, sizeof(line), f)) {
		if (!strcmp(b.BookName,line)) {
			found = true;
			break;
		}
		lineNum++;
	}
	fclose(f);
	if (found) {
		printf("Found! Your book is on line: %d\n", lineNum);
	} 
	else {
		printf("Sorry. We could not find your book.\n");
	}
	
}

void SearchMember() {
	
	ListMember();
	
	FILE *f = fopen(STU_FILE, "r");
	Account p, file;
	bool found = false;
	int lineNum = 1;
	printf("Enter member's username: "); scanf("%s", &p.username);
	while(!feof(f)) {
		fscanf(f, "%s %s %s", &file.email, &file.username, &file.password);
		if (!strcmp(p.username, file.username)) {
			found = true;
			break;
		}
		lineNum++;
	}
	fclose(f);
	if (found) {
		printf("Found! the member's name is on line: %d\n", lineNum);
	}
	else {
		printf("Sorry. We could not find that member's name.\n");
	}
	
}

bool BacktoMenu() {
	int n;
	printf("\nEnter \"0\" to return to Menu: "); scanf("%d", &n);
	return n == 0;
}










