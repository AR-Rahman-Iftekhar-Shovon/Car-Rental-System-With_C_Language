#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>  // For Sleep function
#include "owner_login.h"
#include "customer_registration.h"
#include "driver_management.h"
#include "customer_support.h"
#include "rent_a_car.h"
#include "car_owners.h"
#include "customer_login.h"
#include "admin_dashboard.h"
#include "admin_car_management.h"
#include "generate_reports.h"
#include "search_car.h"
#include "view_rental_history.h"

void car_animation() {
    int pos = 0;
    int direction = 1;
    int max_position = 50;

    for (int frame = 0; frame < 120; frame++) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        for (int i = 0; i < pos; i++) printf(" ");
        printf("\t\t\t\t\t    ______\n");

        for (int i = 0; i < pos; i++) printf(" ");
        printf("\t\t\t\t\t __/[] [] \\__\n");

        for (int i = 0; i < pos; i++) printf(" ");
        printf("\t\t\t\t\t|_         _|\n");

        for (int i = 0; i < pos; i++) printf(" ");
        printf("\t\t\t\t\t  O       O\n");

        usleep(10); // 20ms delay

        pos += direction;
        if (pos >= max_position || pos <= 0)
            direction *= -1;
    }
}

void print_header() {
    printf("\n\n\t\t\t\t\t\t   AUTOMOBILE RENTAL SYSTEM \n\n\n");
    sleep(1);
    printf("\t\t\t\t\t\tProject Managed by: CODE GEEKS\n");
    sleep(1);
    printf("\t\t\t\tThanks for choosing our car rental service! Ready to hit the road.\n");
    sleep(1);
    printf("\n\n  [Car Owners]\t\t\t\t[Rent A Car]\t\t\t\t[Drivers]\t\t[Customer Support]\n\n\n");
    sleep(1);
}

void display_menu() {
    printf("\n\t\t\t\t\t\t ------------------------------\n");
    printf("\t\t\t\t\t\t|         [MENU BAR]          |\n");
    printf("\t\t\t\t\t\t ------------------------------\n");
    printf("\t\t\t\t\t\t|   1. Owner Login            |\n");
    printf("\t\t\t\t\t\t|   2. New Customer Sign Up   |\n");
    printf("\t\t\t\t\t\t|   3. Existing Customer Login|\n");
    printf("\t\t\t\t\t\t|   4. Driver Management      |\n");
    printf("\t\t\t\t\t\t|   5. Customer Support       |\n");
    printf("\t\t\t\t\t\t|   6. Rent A Car             |\n");
    printf("\t\t\t\t\t\t|   7. Car Owners             |\n");
    printf("\t\t\t\t\t\t------------------------------\n");
}

void print_design() {
    printf("\n\t\t\t\t\t\t-------------------------------\n");
    printf("\t\t\t\t\t\t        ACTION COMPLETED \n");
    printf("\t\t\t\t\t\t-------------------------------\n\n");
}

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void handle_invalid_input() {
    while (getchar() != '\n');
    printf("Invalid input. Please enter a valid option.\n");
}

int main() {
    char input[100];
    int found;
    car_animation();

    // Show header and first menu
//#ifdef _WIN32
//    system("cls");
//#else
//    system("clear");
//#endif
    print_header();
    display_menu();

    while (1) {
        printf("\nSEARCH :  ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        to_lowercase(input);
        found = 0;

        char loggedInUser[100];

        if (strcmp(input, "1") == 0 || strstr(input, "owner login") != NULL) {
            owner_login(loggedInUser);
            found = 1;
        }
        else if (strcmp(input, "2") == 0 || strstr(input, "customer sign up") != NULL) {
            new_customer_registration();
            found = 1;
        }
        else if (strcmp(input, "3") == 0 || strstr(input, "existing customer login") != NULL) {
            customer_login();
            found = 1;
        }
        else if (strcmp(input, "4") == 0 || strstr(input, "driver management") != NULL) {
            driver_management();
            found = 1;
        }
        else if (strcmp(input, "5") == 0 || strstr(input, "customer support") != NULL) {
            customer_support();
            found = 1;
        }
        else if (strcmp(input, "6") == 0 || strstr(input, "rent a car") != NULL) {
            rent_a_car();
            found = 1;
        }
        else if (strcmp(input, "7") == 0 || strstr(input, "car owners") != NULL) {
            display_car_owners();
            found = 1;
        }

        if (!found) {
            handle_invalid_input();
        } else {
            print_design();
            sleep(1);

            // Clear screen and show fresh menu again
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            display_menu();
        }
    }

    return 0;
}
