#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <winbase.h>

#define BUFFER_SIZE 100

int main() {
    HANDLE hFile;
    DWORD bytesRead, bytesWritten;
    char buffer[BUFFER_SIZE];

    hFile = CreateFile("test.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        perror("Error creating file");
        exit(1);
    }

    WriteFile(hFile, "Sample text for demonstration.\n", 32, &bytesWritten, NULL);
    CloseHandle(hFile);

    hFile = CreateFile("test.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        perror("Error opening file");
        exit(1);
    }

    SetFilePointer(hFile, 10, NULL, FILE_BEGIN);
    ReadFile(hFile, buffer, 20, &bytesRead, NULL);
    buffer[bytesRead] = '\0';
    printf("Read from offset: %s\n", buffer);
    CloseHandle(hFile);

    WIN32_FIND_DATA fileData;
    HANDLE hFind = FindFirstFile("test.txt", &fileData);
    if (hFind != INVALID_HANDLE_VALUE) {
        printf("File Size: %lld bytes\n", (long long)fileData.nFileSizeLow);
        FindClose(hFind);
    }

    printf("Directory Contents:\n");
    WIN32_FIND_DATA findFileData;
    HANDLE hDir = FindFirstFile("*.*", &findFileData);
    if (hDir != INVALID_HANDLE_VALUE) {
        do {
            printf("%s\n", findFileData.cFileName);
        } while (FindNextFile(hDir, &findFileData) != 0);
        FindClose(hDir);
    }

    return 0;
}
