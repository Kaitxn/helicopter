#include <stdio.h>
#include <string.h>

int main(void) {

    char colors[20];
    char pluralNoun[20];
    char celebrityf[20];
    char celebrityl[20];

    printf("Enter a color: "); // Added missing semicolon
    scanf("%s", colors);        // Removed unnecessary comma and variable name

    printf("Enter a plural noun: "); // Added missing semicolon
    scanf("%s", pluralNoun);         // Removed unnecessary comma and variable name

    printf("Enter a celebrity's first name: "); // Added missing semicolon and more descriptive prompt
    scanf("%s", celebrityf);                    // Removed unnecessary comma and variable name

    printf("Enter a celebrity's last name: "); // Added missing semicolon and more descriptive prompt
    scanf("%s", celebrityl);                   // Removed unnecessary comma and variable name

    printf("Roses are %s\n", colors);
    printf("%s are blue\n", pluralNoun);
    printf("I love %s %s\n", celebrityf, celebrityl); // Corrected the format specifier for the last printf

    return 0;
}
