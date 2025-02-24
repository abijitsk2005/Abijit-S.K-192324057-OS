#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_FILES 10
#define NAME_LENGTH 50

struct File {
    char name[NAME_LENGTH];
};

struct User {
    char name[NAME_LENGTH];
    struct File files[MAX_FILES];
    int file_count;
};

struct User users[MAX_USERS];
int user_count = 0;

void createUser() {
    if (user_count >= MAX_USERS) {
        printf("Maximum users reached. Cannot add more users.\n");
        return;
    }

    char username[NAME_LENGTH];
    printf("Enter new user name: ");
    scanf("%s", username);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].name, username) == 0) {
            printf("User already exists.\n");
            return;
        }
    }

    strcpy(users[user_count].name, username);
    users[user_count].file_count = 0;
    user_count++;
    printf("User '%s' created successfully.\n", username);
}

int findUser(char username[]) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].name, username) == 0)
            return i;
    }
    return -1;
}

void createFile() {
    char username[NAME_LENGTH], filename[NAME_LENGTH];
    printf("Enter user name: ");
    scanf("%s", username);

    int user_index = findUser(username);
    if (user_index == -1) {
        printf("User not found.\n");
        return;
    }

    if (users[user_index].file_count >= MAX_FILES) {
        printf("User directory is full.\n");
        return;
    }

    printf("Enter file name to create: ");
    scanf("%s", filename);

    for (int i = 0; i < users[user_index].file_count; i++) {
        if (strcmp(users[user_index].files[i].name, filename) == 0) {
            printf("File already exists.\n");
            return;
        }
    }

    strcpy(users[user_index].files[users[user_index].file_count].name, filename);
    users[user_index].file_count++;
    printf("File '%s' created successfully under user '%s'.\n", filename, username);
}

void deleteFile() {
    char username[NAME_LENGTH], filename[NAME_LENGTH];
    printf("Enter user name: ");
    scanf("%s", username);

    int user_index = findUser(username);
    if (user_index == -1) {
        printf("User not found.\n");
        return;
    }

    printf("Enter file name to delete: ");
    scanf("%s", filename);

    for (int i = 0; i < users[user_index].file_count; i++) {
        if (strcmp(users[user_index].files[i].name, filename) == 0) {
            for (int j = i; j < users[user_index].file_count - 1; j++) {
                strcpy(users[user_index].files[j].name, users[user_index].files[j + 1].name);
            }
            users[user_index].file_count--;
            printf("File '%s' deleted successfully from user '%s'.\n", filename, username);
            return;
        }
    }
    printf("File not found.\n");
}

void searchFile() {
    char username[NAME_LENGTH], filename[NAME_LENGTH];
    printf("Enter user name: ");
    scanf("%s", username);

    int user_index = findUser(username);
    if (user_index == -1) {
        printf("User not found.\n");
        return;
    }

    printf("Enter file name to search: ");
    scanf("%s", filename);

    for (int i = 0; i < users[user_index].file_count; i++) {
        if (strcmp(users[user_index].files[i].name, filename) == 0) {
            printf("File '%s' found under user '%s'.\n", filename, username);
            return;
        }
    }
    printf("File not found.\n");
}

void displayFiles() {
    char username[NAME_LENGTH];
    printf("Enter user name: ");
    scanf("%s", username);

    int user_index = findUser(username);
    if (user_index == -1) {
        printf("User not found.\n");
        return;
    }

    if (users[user_index].file_count == 0) {
        printf("No files found under user '%s'.\n", username);
        return;
    }

    printf("Files under user '%s':\n", username);
    for (int i = 0; i < users[user_index].file_count; i++) {
        printf("%s\n", users[user_index].files[i].name);
    }
}

int main() {
    int choice;
    while (1) {
        printf("\nTwo-Level Directory System:\n");
        printf("1. Create User Directory\n");
        printf("2. Create File\n");
        printf("3. Delete File\n");
        printf("4. Search File\n");
        printf("5. Display Files\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createUser(); break;
            case 2: createFile(); break;
            case 3: deleteFile(); break;
            case 4: searchFile(); break;
            case 5: displayFiles(); break;
            case 6: return 0;
            default: printf("Invalid choice. Try again.\n");
        }
    }
}
