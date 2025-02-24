#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME "example.txt"
#define BUFFER_SIZE 100

int main() {
    int fd;
    char buffer[BUFFER_SIZE];

    fd = open(FILENAME, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error creating file");
        exit(1);
    }

    write(fd, "Hello, this is a demonstration of UNIX file system calls.\n", 54);
    close(fd);

    fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(1);
    }

    read(fd, buffer, BUFFER_SIZE);
    printf("File Contents:\n%s", buffer);

    lseek(fd, 0, SEEK_SET);
    read(fd, buffer, BUFFER_SIZE);
    printf("\nRe-read File Contents:\n%s", buffer);

    close(fd);
    unlink(FILENAME);
    printf("\nFile deleted successfully.\n");

    return 0;
}
