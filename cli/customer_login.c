#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "customer_login.h"
#include "view_rental_history.h"
#include "customer_support.h"
#include "rent_a_car.h"

#define MAX_ATTEMPTS 3


char loggedInUserEmail[100];

void show_customer_menu() {
    printf("\n\t\t\t\t\t==============================================\n");
    printf("\t\t\t\t\t|              CUSTOMER MENU                  |\n");
    printf("\t\t\t\t\t==============================================\n");
    printf("\t\t\t\t\t| 1. View Rental History                      |\n");
    printf("\t\t\t\t\t| 2. Rent a Car                               |\n");
    printf("\t\t\t\t\t| 3. Logout                                   |\n");
    printf("\t\t\t\t\t==============================================\n");
    printf("\t\t\t\t\tEnter your choice: ");
}

int customer_login() {
    system("cls");

    char inputEmail[100], inputPassword[100], ch;
    int attempt = 0;

    while (attempt < MAX_ATTEMPTS) {
        printf("\n\n\t\t\t\t\t==============================================\n");
        printf("\t\t\t\t\t|               [ Login Menu ]              |\n");
        printf("\t\t\t\t\t==============================================\n\n");

        printf("\t\t\t\t\tEnter Email    : ");
        scanf("%s", inputEmail);

        printf("\t\t\t\t\tEnter Password : ");
        int i = 0;
        while (1) {
            ch = getch();
            if (ch == 13) {
                inputPassword[i] = '\0';
                break;
            } else if (ch == 8 && i > 0) {
                printf("\b \b");
                i--;
            } else if (i < sizeof(inputPassword) - 1) {
                inputPassword[i++] = ch;
                printf("*");
            }
        }

        FILE *file = fopen("customers.txt", "r");
        if (file == NULL) {
            printf("\n\t\t\t\t\tError opening file! Make sure customers.txt exists.\n");
            return 0;
        }

        char name[100], contact[100], email[100], password[100];
        int found = 0;

        while (fscanf(file, "Name: %s\nContact: %s\nEmail: %s\nPassword: %s\n\n",
                      name, contact, email, password) == 4) {
            if (strcmp(email, inputEmail) == 0 && strcmp(password, inputPassword) == 0) {
                found = 1;
                strcpy(loggedInUserEmail, email);
            }
        }

        fclose(file);

        if (found) {
            printf("\n\n\t\t\t\t\t----------------------------------------------\n");
            printf("\t\t\t\t\t  Login Successful! Welcome, %s.\n", name);
            printf("\t\t\t\t\t----------------------------------------------\n");

            int choice;
            do {
                show_customer_menu();
                scanf("%d", &choice);
                getchar();

                switch (choice) {
                    case 1:
                        view_rental_history(loggedInUserEmail);
                        break;
                    case 2:
                        rent_a_car();
                        break;
                    case 3:
                        printf("\n\t\t\t\t\tLogging out...\n");
                        return 1;
                    default:
                        printf("\n\t\t\t\t\tInvalid choice! Please try again.\n");
                }
            } while (choice != 3);

            return 1;
        } else {
            printf("\n\n\t\t\t\t\tIncorrect Email or Password. Attempts left: %d\n", MAX_ATTEMPTS - attempt - 1);
            attempt++;
        }
    }

    printf("\n\t\t\t\t\t==============================================\n");
    printf("\t\t\t\t\t  Too many failed attempts. Access Denied!\n");
    printf("\t\t\t\t\t==============================================\n");
    return 0;
}
