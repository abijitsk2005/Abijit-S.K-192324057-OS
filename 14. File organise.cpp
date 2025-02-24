#include <stdio.h>
#include <string.h>

#define MAX_FILES 100
#define NAME_LENGTH 50

struct File {
    char name[NAME_LENGTH];
};

struct File directory[MAX_FILES];
int file_count = 0;

void createFile() {
    if (file_count >= MAX_FILES) {
        printf("Directory is full. Cannot create more files.\n");
        return;
    }

    char filename[NAME_LENGTH];
    printf("Enter file name to create: ");
    scanf("%s", filename);

    for (int i = 0; i < file_count; i++) {
        if (strcmp(directory[i].name, filename) == 0) {
            printf("File already exists.\n");
            return;
        }
    }

    strcpy(directory[file_count].name, filename);
    file_count++;
    printf("File '%s' created successfully.\n", filename);
}

void deleteFile() {
    char filename[NAME_LENGTH];
    printf("Enter file name to delete: ");
    scanf("%s", filename);

    for (int i = 0; i < file_count; i++) {
        if (strcmp(directory[i].name, filename) == 0) {
            for (int j = i; j < file_count - 1; j++) {
                strcpy(directory[j].name, directory[j + 1].name);
            }
            file_count--;
            printf("File '%s' deleted successfully.\n", filename);
            return;
        }
    }
    printf("File not found.\n");
}

void searchFile() {
    char filename[NAME_LENGTH];
    printf("Enter file name to search: ");
    scanf("%s", filename);

    for (int i = 0; i < file_count; i++) {
        if (strcmp(directory[i].name, filename) == 0) {
            printf("File '%s' found in directory.\n", filename);
            return;
        }
    }
    printf("File not found.\n");
}

void displayFiles() {
    if (file_count == 0) {
        printf("Directory is empty.\n");
        return;
    }

    printf("Files in directory:\n");
    for (int i = 0; i < file_count; i++) {
        printf("%s\n", directory[i].name);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nSingle-Level Directory System:\n");
        printf("1. Create File\n2. Delete File\n3. Search File\n4. Display Files\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createFile(); break;
            case 2: deleteFile(); break;
            case 3: searchFile(); break;
            case 4: displayFiles(); break;
            case 5: return 0;
            default: printf("Invalid choice. Try again.\n");
        }
    }
}
