// SALANATIN, NATHALY PEARL | ACTIVITY 1 | PROGRAMMING LANGUANGE

#include <stdio.h>
#include <stdlib.h>

// Function to write data to a text file
void write_file() {
    char data[100];
    printf("Enter data to write to the text file: ");
    fflush(stdin);
    gets(data);

    // Open file
    FILE *file = fopen("example.txt", "w");
    if (file == NULL) {
        printf("Failed to open file.\n");
        exit(1);
    }

    // Write data to the text file
    fprintf(file, "%s", data);
    fclose(file);
    printf("Data written successfully!\n");
}

// Function to read data from a text file
void read_file() {
    char data[100];

    // Open file in read mode
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Failed to open.\n");
        exit(1);
    }

    // Read data from the text file
    printf("Data read from file:\n");
    while (fgets(data, sizeof(data), file) != NULL) {
        printf("%s", data);
    }
    fclose(file);
}

int main() {
    int choice;
    while (1) {
        printf("\nFile Handling Program\n");
        printf("1. Write to File\n");
        printf("2. Read from File\n");
        printf("3. Exit\n");
        printf("Enter your choice (1/2/3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                write_file();
                break;
            case 2:
                read_file();
                break;
            case 3:
                printf("Thank you for!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
