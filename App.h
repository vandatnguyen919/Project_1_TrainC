
#define MAX 100
#define BOOK_FILE "book.txt"
#define BOOK_TEMP "booktemp.txt"
#define BOOK_BRW "bookborrow.txt"

void AddBook();
void BorrowBook();
void ListBook();
void ListBorrowedBook();
void SearchBook();
void SearchMember();
void ReturnBook();
bool BacktoMenu();

struct Book{
	char BookName[MAX];
} typedef Book;

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

void StudentMenu() {
	
	Menu:
	system("cls");
	Logo();
	
	int choice;
	printf("Hi! :D\n");
	printf("1.Search a book\n2.List all books\n3.Borrow a book\n4.Return the book\n0.Exit\nChoice: ");
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
			BorrowBook();
			if (BacktoMenu()) {
				goto Menu;
			} else break;
		case 4:
			ReturnBook();
			if (BacktoMenu()) {
				goto Menu;
			} else break;	
	}
 }

void AdminMenu() {

	Menu:
	system("cls");
	Logo();
	
	int choice;
	printf("Hi, admin :D\n");
	printf("1.Add a book\n2.Search a book\n3.Search members\n4.List all books\n5.List all borrowed books\n6.Borrow a book\n7.Return the book\n0.Exit\nChoice: ");
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
			BorrowBook();
			if (BacktoMenu()) {
				goto Menu;
			} else break;	
		case 7:
			ReturnBook();
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

void BorrowBook() {
	
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
	char line[MAX];
	int lineNum = 1, choice; 
	printf("Choose a book to borrow: "); scanf("%d", &choice);
	while (fgets(line, sizeof(line), f) != NULL) {
		if (lineNum != choice) {
			fprintf(f_temp, "%s", line);
		} else {
			fprintf(f_borrow, "%s", line);
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
	printf("Successful!\n");
} 

void ListBook() {
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

void ReturnBook() {
	
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
	char line[MAX];
	int lineNum = 1, choice; 
	printf("Choose a book to return: "); scanf("%d", &choice);
	while (fgets(line, sizeof(line), f_borrow) != NULL) {
		if (lineNum == choice) {
			fprintf(f, "%s", line);
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
	printf("Successful!\n");
} 

void Update() {
	
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










