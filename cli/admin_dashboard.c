#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "admin_dashboard.h"
#include "view_rental_history.h"
#include "car.h"

void print_dashboard_header(const char *ownerID) {
    system("cls");
    printf("\n\t\t\t\t================================================================\n");
    printf("\t\t\t\t|                     ADMIN DASHBOARD                          |\n");
    printf("\t\t\t\t================================================================\n");
    printf("\t\t\t\t|  Welcome, %-51s|\n", ownerID);
    printf("\t\t\t\t================================================================\n\n");
}

void print_menu() {
    printf("\n\t\t\t\t+------------------[ Menu Options ]--------------------------+\n");
    printf("\t\t\t\t|                                                            |\n");
    printf("\t\t\t\t|    [1] View My Cars                                        |\n");
    printf("\t\t\t\t|    [2] Add New Car                                         |\n");
    printf("\t\t\t\t|    [3] Remove Car                                          |\n");
    printf("\t\t\t\t|    [4] View Rental History                                 |\n");
    printf("\t\t\t\t|    [5] Logout                                              |\n");
    printf("\t\t\t\t|                                                            |\n");
    printf("\t\t\t\t+------------------------------------------------------------+\n");
}

// Function to display the owner dashboard
void admin_dashboard(char *ownerID) {
    int choice;
    do {
        print_dashboard_header(ownerID);
        print_menu();

        printf("\n\t\t\t\tEnter your choice (1-5): ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        printf("\n");
        switch (choice) {
            case 1:
                printf("\t\t\t\t+------------------[ My Cars ]-------------------------------+\n");
                view_my_cars(ownerID);
                printf("\t\t\t\t+------------------------------------------------------------+\n");
                break;
            case 2:
                printf("\t\t\t\t+------------------[ Add New Car ]---------------------------+\n");
                add_new_car(ownerID);
                printf("\t\t\t\t+------------------------------------------------------------+\n");
                break;
            case 3:
                printf("\t\t\t\t+------------------[ Remove Car ]----------------------------+\n");
                remove_car(ownerID);
                printf("\t\t\t\t+------------------------------------------------------------+\n");
                break;
            case 4:
                printf("\t\t\t\t+------------------[ Rental History ]------------------------+\n");
                view_owner_rental_history(ownerID);
                printf("\t\t\t\t+------------------------------------------------------------+\n");
                break;
            case 5:
                printf("\t\t\t\t+------------------------------------------------------------+\n");
                printf("\t\t\t\t|                    Logging out...                          |\n");
                printf("\t\t\t\t+------------------------------------------------------------+\n");
                sleep(1);
                break;
            default:
                printf("\t\t\t\t+------------------------------------------------------------+\n");
                printf("\t\t\t\t|              Invalid choice. Please try again.             |\n");
                printf("\t\t\t\t+------------------------------------------------------------+\n");
                sleep(1);
        }

        if (choice != 5) {
            printf("\n\t\t\t\tPress Enter to continue...");
            getchar();
        }
    } while (choice != 5);
}

// Function to view cars owned by the user
void view_my_cars(char *ownerID) {
    int found = 0;
    // Show hardcoded default cars for each owner
    if (strcmp(ownerID, "Shovon") == 0) {
        printf("\t\t\t\t| Lamborghini Countach (2021) - $5000/day                   |\n");
        printf("\t\t\t\t| Toyota 2016 (2016) - $3000/day                            |\n");
        found = 1;
    } else if (strcmp(ownerID, "Narju") == 0) {
        printf("\t\t\t\t| BMW i5 (2020) - $2100/day                                 |\n");
        printf("\t\t\t\t| Mercedes Benz S (2021) - $11890/day                       |\n");
        found = 1;
    } else if (strcmp(ownerID, "Shuvo") == 0) {
        printf("\t\t\t\t| Audi R8 (2022) - $4245/day                                |\n");
        printf("\t\t\t\t| Honda CD40 (2021) - $2500/day                             |\n");
        found = 1;
    } else if (strcmp(ownerID, "Shaown") == 0) {
        printf("\t\t\t\t| Ferrari SF (2021) - $5900/day                             |\n");
        printf("\t\t\t\t| Pajero Maxultra (2020) - $5000/day                        |\n");
        found = 1;
    } else if (strcmp(ownerID, "Shanzida") == 0) {
        printf("\t\t\t\t| Premio GX34 (2019) - $4000/day                            |\n");
        found = 1;
    }
    // Show dynamic cars from cars.txt
    FILE *file = fopen("cars.txt", "r");
    if (file) {
        Car car;
        int any = 0;
        while (fscanf(file, "%49s %49s %d %f %d %49s", car.carBrand, car.carModel, &car.year, &car.ratePerDay, &car.isAvailable, car.ownerID) == 6) {
            if (strcmp(car.ownerID, ownerID) == 0) {
                printf("\t\t\t\t| %s %s (%d) - $%.2f/day                                    |\n", car.carBrand, car.carModel, car.year, car.ratePerDay);
                any = 1;
            }
        }
        if (!found && !any) {
            printf("\t\t\t\t| No cars found for this owner.                              |\n");
        }
        fclose(file);
    } else if (!found) {
        printf("\t\t\t\t| No cars found for this owner.                              |\n");
    }
}

// Function to add a new car
void add_new_car(char *ownerID) {
    Car newCar;
    printf("\t\t\t\t| Enter car details:                                         |\n");
    printf("\t\t\t\t|------------------------------------------------------------|\n");
    printf("\t\t\t\t| Brand: ");
    scanf("%s", newCar.carBrand);
    printf("\t\t\t\t| Model: ");
    scanf("%s", newCar.carModel);
    printf("\t\t\t\t| Year: ");
    scanf("%d", &newCar.year);
    printf("\t\t\t\t| Rate per day: $");
    scanf("%f", &newCar.ratePerDay);
    newCar.isAvailable = 1;
    strcpy(newCar.ownerID, ownerID);
    FILE *file = fopen("cars.txt", "a");
    if (file) {
        fprintf(file, "%s %s %d %.2f %d %s\n", newCar.carBrand, newCar.carModel, newCar.year, newCar.ratePerDay, newCar.isAvailable, newCar.ownerID);
        fclose(file);
    }
    printf("\t\t\t\t|------------------------------------------------------------|\n");
    printf("\t\t\t\t| New car added successfully:                                |\n");
    printf("\t\t\t\t| %s %s (%d) - $%.2f/day                                    |\n", newCar.carBrand, newCar.carModel, newCar.year, newCar.ratePerDay);
}

// Function to remove a car
void remove_car(char *ownerID) {
    char carBrand[50];
    printf("\t\t\t\t| Enter car brand to remove: ");
    scanf("%s", carBrand);
    FILE *file = fopen("cars.txt", "r");
    FILE *temp = fopen("cars_temp.txt", "w");
    if (!file || !temp) {
        printf("\t\t\t\t| Error opening file.                                        |\n");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }
    Car car;
    int removed = 0;
    while (fscanf(file, "%49s %49s %d %f %d %49s", car.carBrand, car.carModel, &car.year, &car.ratePerDay, &car.isAvailable, car.ownerID) == 6) {
        if (strcmp(car.ownerID, ownerID) == 0 && strcmp(car.carBrand, carBrand) == 0) {
            removed = 1;
            continue; // skip writing this car
        }
        fprintf(temp, "%s %s %d %.2f %d %s\n", car.carBrand, car.carModel, car.year, car.ratePerDay, car.isAvailable, car.ownerID);
    }
    fclose(file);
    fclose(temp);
    remove("cars.txt");
    rename("cars_temp.txt", "cars.txt");
    printf("\t\t\t\t|------------------------------------------------------------|\n");
    if (removed) {
        printf("\t\t\t\t| Car %s has been removed from your list.                    |\n", carBrand);
    } else {
        printf("\t\t\t\t| Car %s not found in your list.                             |\n", carBrand);
    }
}
