#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_AUTHOR 50
#define MAX_BOOKS 100

typedef struct {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int year;
} Book;

Book library[MAX_BOOKS];
int bookCount = 0;

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full! Cannot add more books.\n");
        return;
    }

    Book newBook;
    newBook.id = bookCount + 1;
    printf("Enter book title: ");
    scanf(" %[^"]", newBook.title);
    printf("Enter author name: ");
    scanf(" %[^"]", newBook.author);
    printf("Enter publication year: ");
    scanf("%d", &newBook.year);

    library[bookCount++] = newBook;
    printf("Book added successfully!\n");
}

void viewBooks() {
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\n%-5s%-30s%-20s%-10s\n", "ID", "Title", "Author", "Year");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%-5d%-30s%-20s%-10d\n", library[i].id, library[i].title, library[i].author, library[i].year);
    }
}

void searchBook() {
    char searchTitle[MAX_TITLE];
    printf("Enter the title of the book to search: ");
    scanf(" %[^"]", searchTitle);

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcasecmp(library[i].title, searchTitle) == 0) {
            printf("\nBook found:\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\n", library[i].id, library[i].title, library[i].author, library[i].year);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found in the library.\n");
    }
}

void deleteBook() {
    int id;
    printf("Enter the ID of the book to delete: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            found = 1;
            for (int j = i; j < bookCount - 1; j++) {
                library[j] = library[j + 1];
            }
            bookCount--;
            printf("Book with ID %d deleted successfully!\n", id);
            break;
        }
    }

    if (!found) {
        printf("Book with ID %d not found.\n", id);
    }
}

void saveToFile(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(&bookCount, sizeof(int), 1, file);
    fwrite(library, sizeof(Book), bookCount, file);
    fclose(file);
    printf("Library data saved to %s\n", filename);
}

void loadFromFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }

    fread(&bookCount, sizeof(int), 1, file);
    fread(library, sizeof(Book), bookCount, file);
    fclose(file);
    printf("Library data loaded from %s\n", filename);
}

void menu() {
    printf("\nLibrary Management System\n");
    printf("1. Add Book\n");
    printf("2. View Books\n");
    printf("3. Search Book\n");
    printf("4. Delete Book\n");
    printf("5. Save to File\n");
    printf("6. Load from File\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    const char *filename = "library.dat";

    while (1) {
        menu();
        int choice;
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addBook();
            break;
        case 2:
            viewBooks();
            break;
        case 3:
            searchBook();
            break;
        case 4:
            deleteBook();
            break;
        case 5:
            saveToFile(filename);
            break;
        case 6:
            loadFromFile(filename);
            break;
        case 7:
            printf("Exiting program. Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}
