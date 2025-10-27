#include <stdio.h>
#include <stdlib.h>
#include "admin_car_management.h"

#define MAX_CARS 9

void update_car_status() {
    char car_status[MAX_CARS][20] = {"Available", "Available", "Booked", "Available", "Available", "Booked", "Available", "Available", "Booked"};
    int choice;
    printf("Enter the car number to update its status (1 to %d): ", MAX_CARS);
    scanf("%d", &choice);

    if (choice < 1 || choice > MAX_CARS) {
        printf("Invalid car number.\n");
        return;
    }

    printf("Current Status of Car %d: %s\n", choice, car_status[choice - 1]);
   printf("Enter new status for Car %d (Available/Booked): ", choice);
scanf("%19s", car_status[choice - 1]);

    printf("Car %d status updated to: %s\n", choice, car_status[choice - 1]);
}
