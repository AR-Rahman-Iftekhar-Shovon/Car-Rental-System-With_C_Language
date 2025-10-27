#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // For sleep()
#include "customer_registration.h"

void new_customer_registration() {
    char New_customers[100];
    char inputemail[100], inputPassword[100];
    char contact[100];

    system("cls"); // Clears the console in Windows (for Code::Blocks)

    printf("\t\t\t\t=============================================================\n");
    printf("\t\t\t\t|                 NEW CUSTOMER REGISTRATION                 |\n");
    printf("\t\t\t\t=============================================================\n");

    printf("\t\t\t\t| Enter your name           : ");
    scanf("%99s", New_customers);

    printf("\t\t\t\t| Enter your contact number : ");
    scanf("%99s", contact);

    printf("\t\t\t\t| Enter your email          : ");
    scanf("%99s", inputemail);

    printf("\t\t\t\t| Enter your password       : ");
    scanf("%99s", inputPassword);

    // Save user details to file
    FILE *file = fopen("customers.txt", "a");  // "a" to append new customers
    if (file == NULL) {
        printf("\t\t\t\tError saving registration details!\n");
        return;
    }

    fprintf(file, "Name: %s\nContact: %s\nEmail: %s\nPassword: %s\n\n",
            New_customers, contact, inputemail, inputPassword);
    fclose(file);

    printf("\t\t\t\t=============================================================\n");

    sleep(1);
    printf("\n\t\t\t\t\tPlease wait while we process your registration");
    sleep(2);

    printf("\n\n\t\t\t\t=============================================================\n");
    printf("\t\t\t\t\t\t Thank you for registering, %s!\n", New_customers);
    printf("\t\t\t\t\t\t Welcome to our community.\n");
    printf("\t\t\t\t=============================================================\n");
}
