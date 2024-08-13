#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 1000

void view_file_content(char content[][MAX_LINE_LENGTH], int num_lines) {
    printf("\nContents of the file:\n");
    for (int i = 0; i < num_lines; i++) {
        printf("%d: %s", i + 1, content[i]);
    }
    printf("\n");
}

void edit_file_content(char content[][MAX_LINE_LENGTH], int num_lines) {
    int line_number;
    char new_line[MAX_LINE_LENGTH];

    while (1) {
        view_file_content(content, num_lines);
        printf("Enter the line number you want to edit (0 to stop editing): ");
        scanf("%d", &line_number);

        if (line_number == 0) {
            break;
        }

        if (line_number < 1 || line_number > num_lines) {
            printf("Invalid line number! Please try again.\n");
            continue;
        }

        printf("Enter the new content for line %d: ", line_number);
        getchar();
        fgets(new_line, MAX_LINE_LENGTH, stdin);


        strcpy(content[line_number - 1], new_line);
    }
}

int main() {
    FILE *file;
    char filename[100];
    char content[MAX_LINES][MAX_LINE_LENGTH];
    int num_lines = 0;
    int choice;

    printf("Enter the name of the file to open: ");
    scanf("%s", filename);

    printf("Choose an operation:\n");
    printf("1. View file\n");
    printf("2. Edit file\n");
    printf("3. Exit\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
        case 2:
            file = fopen(filename, "r");
            if (file == NULL) {
                printf("Error opening file!\n");
                return 1;
            }

            while (fgets(content[num_lines], MAX_LINE_LENGTH, file) != NULL) {
                num_lines++;
                if (num_lines >= MAX_LINES) {
                    printf("File is too large!\n");
                    fclose(file);
                    return 1;
                }
            }

            fclose(file);

            if (choice == 1) {
                view_file_content(content, num_lines);
            } else {
                edit_file_content(content, num_lines);

                file = fopen(filename, "w");
                if (file == NULL) {
                    printf("Error saving file!\n");
                    return 1;
                }

                for (int i = 0; i < num_lines; i++) {
                    fputs(content[i], file);
                }

                fclose(file);
                printf("Changes saved to the file '%s'.\n", filename);
            }
            break;

        case 3:
            printf("Exiting the program.\n");
            exit(0);

        default:
            printf("Invalid choice! Exiting.\n");
            exit(1);
    }

    return 0;
}
