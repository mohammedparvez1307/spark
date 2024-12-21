#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

void addStudent(Student **students, int *count) {
    Student newStudent;
    printf("Enter ID: ");
    scanf("%d", &newStudent.id);
    printf("Enter Name: ");
    scanf(" %49[^"]", newStudent.name);
    printf("Enter Age: ");
    scanf("%d", &newStudent.age);
    printf("Enter GPA: ");
    scanf("%f", &newStudent.gpa);

    (*count)++;
    *students = realloc(*students, (*count) * sizeof(Student));
    if (!(*students)) {
        printf("Memory allocation failed. Exiting.\n");
        exit(1);
    }
    (*students)[*count - 1] = newStudent;
    printf("Student added successfully!\n");
}

void viewStudents(Student *students, int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\n%-10s%-30s%-10s%-10s\n", "ID", "Name", "Age", "GPA");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-10d%-30s%-10d%-10.2f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
}

int findStudentIndex(Student *students, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id)
            return i;
    }
    return -1;
}

void updateStudent(Student *students, int count) {
    int id;
    printf("Enter the ID of the student to update: ");
    scanf("%d", &id);

    int index = findStudentIndex(students, count, id);
    if (index == -1) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    printf("Enter new details:\n");
    printf("Enter Name: ");
    scanf(" %49[^"]", students[index].name);
    printf("Enter Age: ");
    scanf("%d", &students[index].age);
    printf("Enter GPA: ");
    scanf("%f", &students[index].gpa);

    printf("Student updated successfully!\n");
}

void deleteStudent(Student **students, int *count) {
    int id;
    printf("Enter the ID of the student to delete: ");
    scanf("%d", &id);

    int index = findStudentIndex(*students, *count, id);
    if (index == -1) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    for (int i = index; i < (*count) - 1; i++) {
        (*students)[i] = (*students)[i + 1];
    }
    (*count)--;
    *students = realloc(*students, (*count) * sizeof(Student));

    if (*count > 0 && !(*students)) {
        printf("Memory reallocation failed. Exiting.\n");
        exit(1);
    }
    printf("Student deleted successfully!\n");
}

void saveToFile(Student *students, int count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), count, file);

    fclose(file);
    printf("Data saved successfully to %s!\n", filename);
}

void loadFromFile(Student **students, int *count, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }

    fread(count, sizeof(int), 1, file);
    *students = malloc((*count) * sizeof(Student));
    if (!(*students)) {
        printf("Memory allocation failed. Exiting.\n");
        exit(1);
    }
    fread(*students, sizeof(Student), *count, file);

    fclose(file);
    printf("Data loaded successfully from %s!\n", filename);
}

void menu() {
    printf("\nStudent Management System\n");
    printf("1. Add Student\n");
    printf("2. View Students\n");
    printf("3. Update Student\n");
    printf("4. Delete Student\n");
    printf("5. Save to File\n");
    printf("6. Load from File\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Student *students = NULL;
    int count = 0;
    const char *filename = "students.dat";

    while (1) {
        menu();
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(&students, &count);
                break;
            case 2:
                viewStudents(students, count);
                break;
            case 3:
                updateStudent(students, count);
                break;
            case 4:
                deleteStudent(&students, &count);
                break;
            case 5:
                saveToFile(students, count, filename);
                break;
            case 6:
                loadFromFile(&students, &count, filename);
                break;
            case 7:
                free(students);
                printf("Exiting program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
