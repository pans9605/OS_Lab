#include <stdio.h>
#include <string.h> // Include string.h for strcspn()

// Define a structure for Process information
struct Process {
    int process_id;         // Process ID
    char arrival_time[5];  // Arrival Time as a string
    char completion_time[5];
    char execution_time[10];
    char process_name[30]; // Departure Time as a string
};

void input_process_info(struct Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter process_id for process %d: ", i + 1);
        scanf("%d", &processes[i].process_id);
        printf("Enter process name %d:", i + 1);
        scanf("%s", processes[i].process_name);
        printf("Enter arrival_time in 24-hour format for process %d: ", i + 1);
        scanf("%s", processes[i].arrival_time);
        printf("Enter completion time in 24-hour format for process %d: ", i + 1);
        scanf("%s", processes[i].completion_time);
        printf("Enter execution time in 24-hour format for process %d: ", i + 1);
        scanf("%s", processes[i].execution_time);
    }
}

// Function to output process information
void output_process_info(struct Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nProcess Information for Process %d:\n", i + 1);
        printf("Process ID: %d\n", processes[i].process_id);
        printf("Process Name: %s\n", processes[i].process_name);
        printf("Arrival Time: %s\n", processes[i].arrival_time);
        printf("Completion Time: %s\n", processes[i].completion_time);
        printf("Execution Time: %s\n", processes[i].execution_time);
    }
}

void search_process_by_id(struct Process processes[], int n, int search_id)
{
    int found = 0;
    for (int i = 0; i < n; i++)
    {
        if (processes[i].process_id == search_id)
        {
            printf("\nProcess found!\n");
            printf("Process ID: %d\n", processes[i].process_id);
            printf("Process Name: %s\n", processes[i].process_name);
            printf("Arrival Time: %s\n", processes[i].arrival_time);
            printf("Completion Time: %s\n", processes[i].completion_time);
            printf("Execution Time: %s\n", processes[i].execution_time);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nProcess with ID %d not found!\n", search_id);
    }
}

int main() {
    int n, search_id;
    int choice;

    // Initial menu prompt
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n]; // Array to hold processes

    do
    {
        // Menu display
        printf("\nMenu:\n");
        printf("1. Input Process Information\n");
        printf("2. Output All Process Information\n");
        printf("3. Search Process by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Input process information
            input_process_info(processes, n);
            break;

        case 2:
            // Output all processes information
            output_process_info(processes, n);
            break;

        case 3:
            // Search process by ID
            printf("\nEnter the process ID to search: ");
            scanf("%d", &search_id);
            search_process_by_id(processes, n, search_id);
            break;

        case 4:
            // Exit program
            printf("\nExiting program.\n");
            break;

        default:
            // Invalid option
            printf("\nInvalid choice! Please enter a valid option.\n");
            break;
        }
    } while (choice != 4); // Repeat until the user chooses to exit

    return 0;
}
