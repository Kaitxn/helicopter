#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_HABITS 10000

char **str_split(char *a_str, const char a_delim)
{
    char **result = 0;
    size_t count = 0;
    char *tmp = a_str;
    char *last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char *) * count);

    if (result)
    {
        size_t idx = 0;
        char *token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

typedef struct
{
    char *name;
    int interval_day;
} Habit;

int main(int argc, char *argv[])
{
    FILE *fptr;

    // Open a file for reading habits
    fptr = fopen("db.csv", "r");

    // This is to handle if there is error opening the file
    if (fptr == NULL)
    {
        fprintf(stderr, "Failed to open file at db.csv");
        return 1;
    }

    // Read from the file to take existing habits
    Habit habits[MAX_HABITS];
    int i = 0;
    int read;
    int len;
    char *line;

    // Read line by line for the file
    while ((read = getline(&line, &len, fptr)) != -1)
    {
        char **tokens = str_split(line, ',');
        if (tokens == NULL)
            continue;

        habits[i] = (Habit){.name = tokens[0], .interval_day = atoi(tokens[1])};
        i++;

        free(tokens);
    }

    fclose(fptr);

    if (argc == 2 && strcmp(argv[1], "add") == 0)
    {
        // Open a file for storing habits
        fptr = fopen("db.csv", "a");

        // This is to handle if there is error opening the file
        if (fptr == NULL)
        {
            fprintf(stderr, "Failed to open file at db.csv");
            return 1;
        }

        Habit habit = {.name = (char *)malloc(100 * sizeof(char)), .interval_day = 0};

        printf("What habit do you want to add?: ");
        scanf("%s", habit.name);

        printf("What is the interval of the habit?: ");
        scanf("%d", &habit.interval_day);

        fprintf(fptr, "%s,%d\n", habit.name, habit.interval_day);

        printf("Habit %s added.", habit.name);

        fclose(fptr);

        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "remove") == 0)
    {
        char remove_habit_name[100];

        printf("What habit do you want to remove?: ");
        scanf("%s", remove_habit_name);

        int habit_index_to_remove = -1;

        for (int i = 0; i < MAX_HABITS; i++)
        {
            if (habits[i].name == NULL)
                break;
            if (strcmp(habits[i].name, remove_habit_name) == 0)
            {
                habit_index_to_remove = i;
                break;
            }
        }
        if (habit_index_to_remove != -1)
        {
            // Shift the array elements to remove the habit
            for (int j = habit_index_to_remove; j < MAX_HABITS - 1; j++)
            {
                habits[j] = habits[j + 1];
            }

            // Clear the last element in the array
            habits[MAX_HABITS - 1].name = NULL;
            habits[MAX_HABITS - 1].interval_day = 0;

            // Open the file to rewrite the habits
            fptr = fopen("db.csv", "w");

            // Write the habits back to the file
            for (int i = 0; habits[i].name != NULL; i++)
            {
                fprintf(fptr, "%s,%d\n", habits[i].name, habits[i].interval_day);
            }

            printf("Habit %s removed.", remove_habit_name);

            fclose(fptr);
        }
        else
        {
            printf("Habit %s not found.", remove_habit_name);
        }

        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "list") == 0)
    {
        for (int i = 0; i < MAX_HABITS; i++)
        {
            if (habits[i].name == NULL)
                break;
            printf("Habit %d: %s (%d days)\n", i + 1, habits[i].name, habits[i].interval_day);
        }

        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        printf("Usage: helicopter [command]\n");
        printf("  command:\n");
        printf("    add                  Adding a habit\n");
        printf("    remove               Removing a habit\n");
        printf("    list                 Lists your habits\n");

        return 0;
    }

    fclose(fptr);

    return 0;
}
