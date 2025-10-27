#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>  // For getch() function
#include <windows.h>  // For Sleep function
#include "admin_dashboard.h"
#include "owner_login.h"

#define MAX_OWNERS 5


static const char *owners[MAX_OWNERS] = {"Shovon", "Narju", "Shuvo", "Shaown", "Shanzida"};
static const char *ownerPasswords[MAX_OWNERS] = {"123shovon", "123narju", "123shuvo", "123shaown", "123shanzida"};

void print_login_header() {
    system("cls");
    printf("\n\n");
    printf("\t\t\t\t\t==============================================\n");
    printf("\t\t\t\t\t|              OWNER LOGIN PORTAL            |\n");
    printf("\t\t\t\t\t==============================================\n\n");
}

void print_success_message(const char *username) {
    printf("\n\t\t\t\t\t==============================================\n");
    printf("\t\t\t\t\t|           LOGIN SUCCESSFUL!                |\n");
    printf("\t\t\t\t\t|                                            |\n");
    printf("\t\t\t\t\t|  Welcome back, %-25s   |\n", username);
    printf("\t\t\t\t\t==============================================\n");
    Sleep(1500);
}

void print_error_message() {
    printf("\n\t\t\t\t\t==============================================\n");
    printf("\t\t\t\t\t|           LOGIN FAILED!                    |\n");
    printf("\t\t\t\t\t|                                            |\n");
    printf("\t\t\t\t\t|  Invalid username or password.             |\n");
    printf("\t\t\t\t\t|  Please try again.                         |\n");
    printf("\t\t\t\t\t==============================================\n");
    Sleep(2000);
}

int owner_login(char loggedInUser[]) {
    char inputUsername[50], inputPassword[50];
    int success = 0;
    char ch;
    int i = 0;

    print_login_header();


    printf("\t\t\t\t\tUsername: ");
    fgets(inputUsername, sizeof(inputUsername), stdin);
    inputUsername[strcspn(inputUsername, "\n")] = 0;


    printf("\t\t\t\t\tPassword: ");
    while (1) {
        ch = getch();
        if (ch == 13) {
            inputPassword[i] = '\0';
            break;
        } else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < sizeof(inputPassword) - 1) {
            inputPassword[i++] = ch;
            printf("*");
        }
    }
    printf("\n");


    for (int i = 0; i < MAX_OWNERS; i++) {
        if (strcmp(owners[i], inputUsername) == 0 &&
            strcmp(ownerPasswords[i], inputPassword) == 0) {
            success = 1;
            strcpy(loggedInUser, owners[i]);
            break;
        }
    }

    if (success) {
        print_success_message(loggedInUser);
        admin_dashboard(loggedInUser);
        return 1;
    } else {
        print_error_message();
        return 0;
    }
}
