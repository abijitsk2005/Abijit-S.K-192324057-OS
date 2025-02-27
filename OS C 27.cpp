#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char fn[50], pat[50], temp[200];
    FILE *fp;

    // Get file name
    printf("\nEnter file name: ");
    scanf("%s", fn);

    // Get pattern to search
    printf("Enter the pattern: ");
    scanf("%s", pat);

    // Open file in read mode
    fp = fopen(fn, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file '%s'.\n", fn);
        return 1;
    }

    // Read file line by line and check for pattern
    while (fgets(temp, sizeof(temp), fp) != NULL) {
        if (strstr(temp, pat) != NULL) { // Use strstr() to check if pattern exists
            printf("%s", temp);
        }
    }

    // Close file
    fclose(fp);
    return 0;
}
