#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "driver_management.h"

#define MAX_DRIVERS 100

typedef struct {
    int id;
    char name[50];
    char car_assigned[20];
    char schedule[50];
} Driver;

Driver drivers[MAX_DRIVERS];
int driverCount = 0;
const char *FILENAME = "drivers.dat";

void saveDriversToFile() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Error saving driver data.\n");
        return;
    }
    fwrite(&driverCount, sizeof(int), 1, file);
    fwrite(drivers, sizeof(Driver), driverCount, file);
    fclose(file);
}

void loadDriversFromFile() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) return;
    fread(&driverCount, sizeof(int), 1, file);
    fread(drivers, sizeof(Driver), driverCount, file);
    fclose(file);
}

void addDriver() {
    if (driverCount >= MAX_DRIVERS) {
        printf("\n\t\t\t\t\t= =============================================\n");
        printf("\t\t\t\t\t|         Driver list is full!                |\n");
        printf("\t\t\t\t\t==============================================\n");
        return;
    }

    printf("\n\t\t\t\t\t==============================================\n");
    printf("\t\t\t\t\t|                 Add New Driver              |\n");
    printf("\t\t\t\t\t==============================================\n");

    printf("\nEnter Driver ID: ");
    scanf("%d", &drivers[driverCount].id);
    getchar();

    printf("Enter Driver Name: ");
    fgets(drivers[driverCount].name, 50, stdin);
    drivers[driverCount].name[strcspn(drivers[driverCount].name, "\n")] = 0;

    printf("Enter Assigned Car: ");
    fgets(drivers[driverCount].car_assigned, 20, stdin);
    drivers[driverCount].car_assigned[strcspn(drivers[driverCount].car_assigned, "\n")] = 0;

    printf("Enter Schedule (e.g., 9AM-5PM): ");
    fgets(drivers[driverCount].schedule, 50, stdin);
    drivers[driverCount].schedule[strcspn(drivers[driverCount].schedule, "\n")] = 0;

    driverCount++;
    saveDriversToFile();

    printf("\n\t\t\t\t\t----------------------------------------------\n");
    printf("\t\t\t\t\t         Driver added successfully!\n");
    printf("\t\t\t\t\t----------------------------------------------\n");
}

void displayDrivers() {
    loadDriversFromFile();
    if (driverCount == 0) {
        printf("\n\t\t\t\t\t==============================================\n");
        printf("\t\t\t\t\t|          No drivers scheduled yet!         |\n");
        printf("\t\t\t\t\t==============================================\n");
        return;
    }

    printf("\n\t\t\t\t\t==============================================\n");
    printf("\t\t\t\t\t|               Driver Schedules             |\n");
    printf("\t\t\t\t\t==============================================\n\n");

    for (int i = 0; i < driverCount; i++) {
        printf("ID: %d | Name: %s | Car: %s | Schedule: %s\n",
               drivers[i].id, drivers[i].name, drivers[i].car_assigned, drivers[i].schedule);
    }
    printf("\n\t\t\t\t\t----------------------------------------------\n");
}

void searchDriver() {
    system("cls");
    loadDriversFromFile();
    int id;

    printf("\nEnter Driver ID to search: ");
    scanf("%d", &id);
    for (int i = 0; i < driverCount; i++) {
        if (drivers[i].id == id) {
            printf("\n\t\t\t\t\t==============================================\n");
            printf("\t\t\t\t\t|               Driver Found                  |\n");
            printf("\t\t\t\t\t==============================================\n");
            printf("ID: %d | Name: %s | Car: %s | Schedule: %s\n",
                   drivers[i].id, drivers[i].name, drivers[i].car_assigned, drivers[i].schedule);
            return;
        }
    }
    printf("\n\t\t\t\t\t==============================================\n");
    printf("\t\t\t\t\t|       Driver with ID %d not found!         |\n", id);
    printf("\t\t\t\t\t==============================================\n");
}

void driver_management() {
    system("cls");
    loadDriversFromFile();

    printf("\n\n\t\t\t\t\t==============================================\n");
    printf("\t\t\t\t\t|                Driver Management           |\n");
    printf("\t\t\t\t\t==============================================\n");

    int choice;
    do {
        printf("\n\n\t\t\t\t\t----------------------------------------------\n");
        printf("\t\t\t\t\t       Driver Schedule Management Menu\n");
        printf("\t\t\t\t\t----------------------------------------------\n");
        printf("\t\t\t\t\t  1. Add Driver\n");
        printf("\t\t\t\t\t  2. Display Drivers\n");
        printf("\t\t\t\t\t  3. Search Driver\n");
        printf("\t\t\t\t\t  4. Exit\n");
        printf("\t\t\t\t\t----------------------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addDriver();
                break;
            case 2:
                displayDrivers();
                break;
            case 3:
                searchDriver();
                break;
            case 4:
                printf("\n\t\t\t\t\tThank you for using Driver Management System!\n");
                break;
            default:
                printf("\n\t\t\t\t\tInvalid choice! Please try again.\n");
        }
    } while (choice != 4);
}
