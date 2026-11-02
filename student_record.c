#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char regNo[20];
    char name[50];
    float marks;
    struct Student *next;
};
struct Student *head = NULL;

void clearInput(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

void addStudent(void) {
    struct Student *node, *temp;
    node = (struct Student *)malloc(sizeof(struct Student));
    if (node == NULL) { printf("Memory allocation failed!\n"); return; }

    printf("Enter registration number: ");
    if (scanf("%19s", node->regNo) != 1) {
        printf("Invalid registration number!\n");
        free(node); clearInput(); return;
    }
    clearInput();

    for (temp = head; temp != NULL; temp = temp->next) {
        if (strcmp(temp->regNo, node->regNo) == 0) {
            printf("Registration number already exists!\n");
            free(node); return;
        }
    }

    printf("Enter student name: ");
    if (fgets(node->name, sizeof(node->name), stdin) == NULL) {
        printf("Could not read student name.\n");
        free(node); return;
    }
    node->name[strcspn(node->name, "\r\n")] = '\0';
    if (node->name[0] == '\0') {
        printf("Name cannot be empty!\n");
        free(node); return;
    }

    printf("Enter marks (0-100): ");
    if (scanf("%f", &node->marks) != 1 ||
        node->marks < 0.0f || node->marks > 100.0f) {
        printf("Invalid marks. Enter a value from 0 to 100.\n");
        free(node); clearInput(); return;
    }
    clearInput();

    node->next = NULL;
    if (head == NULL) head = node;
    else {
        temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = node;
    }
    printf("Student record added successfully!\n");
}

void searchStudent(void) {
    char reg[20];
    struct Student *temp = head;
    printf("Enter registration number to search: ");
    if (scanf("%19s", reg) != 1) {
        printf("Invalid input!\n"); clearInput(); return;
    }
    clearInput();
    while (temp != NULL) {
        if (strcmp(temp->regNo, reg) == 0) {
            printf("\nStudent Found!\n");
            printf("Registration Number: %s\n", temp->regNo);
            printf("Name: %s\n", temp->name);
            printf("Marks: %.2f\n", temp->marks);
            return;
        }
        temp = temp->next;
    }
    printf("Student record not found!\n");
}

void deleteStudent(void) {
    char reg[20];
    struct Student *temp = head, *prev = NULL;
    printf("Enter registration number to delete: ");
    if (scanf("%19s", reg) != 1) {
        printf("Invalid input!\n"); clearInput(); return;
    }
    clearInput();
    while (temp != NULL && strcmp(temp->regNo, reg) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) { printf("Student record not found!\n"); return; }
    if (prev == NULL) head = temp->next;
    else prev->next = temp->next;
    free(temp);
    printf("Student record deleted successfully!\n");
}

void displayStudents(void) {
    struct Student *temp = head;
    if (temp == NULL) { printf("No student records available.\n"); return; }
    printf("\n--- Student Records ---\n");
    while (temp != NULL) {
        printf("Registration Number: %s\n", temp->regNo);
        printf("Name: %s\n", temp->name);
        printf("Marks: %.2f\n", temp->marks);
        printf("-----------------------\n");
        temp = temp->next;
    }
}

void freeAllStudents(void) {
    struct Student *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    int choice;
    while (1) {
        printf("\n=== Student Record Management System ===\n");
        printf("1. Add Student\n2. Search Student\n3. Delete Student\n");
        printf("4. Display All Students\n5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid menu choice. Enter a number from 1 to 5.\n");
            clearInput(); continue;
        }
        clearInput();
        switch (choice) {
            case 1: addStudent(); break;
            case 2: searchStudent(); break;
            case 3: deleteStudent(); break;
            case 4: displayStudents(); break;
            case 5:
                freeAllStudents();
                printf("Exiting application. Goodbye!\n");
                return 0;
            default: printf("Invalid choice! Select 1 to 5.\n");
        }
    }
}
