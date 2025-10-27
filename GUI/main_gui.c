#include <gtk/gtk.h>
#include "gui.h"
#include "style.h"
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
#include <string.h>
#include <ctype.h>
#include <windows.h>

// Function declarations for console mode
void print_header();
void display_menu();
void print_design();
void to_lowercase(char *str);
void handle_invalid_input();
void car_animation();
void clearScreen();
void setColor(int, int);
void resetColor();
void gotoxy(int, int);
void drawTitle(const char*, int, int);
void drawBox(int, int, int, int, int, int);
void printCentered(const char*, int);

// Console-mode login
int console_customer_login(char *loggedInUser);

// Car animation function
void car_animation() {
    int pos = 0;
    int direction = 1;
    int max_position = 50;

    for (int frame = 0; frame < 120; frame++) {
        clearScreen();
        setColor(13, 0); // Magenta on black

        for (int i = 0; i < pos; i++) printf(" ");
        printf("\t\t\t\t\t    ______\n");

        for (int i = 0; i < pos; i++) printf(" ");
        printf("\t\t\t\t\t __/[] [] \\__\n");

        for (int i = 0; i < pos; i++) printf(" ");
        printf("\t\t\t\t\t|_         _|\n");

        for (int i = 0; i < pos; i++) printf(" ");
        printf("\t\t\t\t\t  O       O\n");

        resetColor();
        Sleep(20);

        pos += direction;
        if (pos >= max_position || pos <= 0)
            direction *= -1;
    }
}

void print_header() {
    clearScreen();
    setColor(9, 0); // Blue on black
    drawTitle("AUTOMOBILE RENTAL SYSTEM", 9, 0);
    Sleep(1000);

    setColor(11, 0); // Cyan
    printCentered("Project Managed by: CODE GEEKS", 6);
    Sleep(1000);

    setColor(10, 0); // Green
    printCentered("Thanks for choosing our car rental service! Ready to hit the road.", 8);
    resetColor();
    Sleep(1000);

    setColor(13, 0); // Magenta
    printCentered("[Car Owners]  [Rent A Car]  [Drivers]  [Customer Support]", 10);
    resetColor();
    Sleep(1000);

    car_animation();
}

void display_menu() {
    drawBox(20, 12, 40, 11, 9, 0);
    gotoxy(30, 13);
    setColor(9, 0);
    printf("[MENU BAR]");
    resetColor();

    setColor(11, 0);
    gotoxy(22, 15); printf("1. Owner Login");
    gotoxy(22, 16); printf("2. New Customer Sign Up");
    gotoxy(22, 17); printf("3. Existing Customer Login");
    gotoxy(22, 18); printf("4. Driver Management");
    gotoxy(22, 19); printf("5. Customer Support");
    gotoxy(22, 20); printf("6. Rent A Car");
    gotoxy(22, 21); printf("7. Car Owners");
    resetColor();
}

void print_design() {
    drawBox(20, 24, 40, 3, 10, 0);
    gotoxy(30, 25);
    setColor(10, 0);
    printf("ACTION COMPLETED");
    resetColor();
}

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void handle_invalid_input() {
    while (getchar() != '\n');
    setColor(12, 0);
    printCentered("Invalid input. Please enter a valid option.", 26);
    resetColor();
    Sleep(1000);
}

int console_customer_login(char *loggedInUser) {
    FILE *file = fopen("customers.txt", "r");
    if (!file) {
        printf("Error: could not open customers.txt\n");
        return 0;
    }

    char name[100], contact[100], email[100], password[100];
    char input_email[100], input_password[100];

    printf("\nEnter Email: ");
    fgets(input_email, sizeof(input_email), stdin);
    input_email[strcspn(input_email, "\n")] = 0;

    printf("Enter Password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = 0;

    while (fscanf(file, "Name: %s\nContact: %s\nEmail: %s\nPassword: %s\n\n",
                  name, contact, email, password) == 4) {
        if (strcmp(email, input_email) == 0 && strcmp(password, input_password) == 0) {
            strcpy(loggedInUser, email);
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void run_console_mode() {
    char input[100];
    int found;
    char loggedInUser[100] = "";

    print_header();
    display_menu();

    while (1) {
        setColor(14, 0);
        gotoxy(30, 23);
        printf("SEARCH :  ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        to_lowercase(input);
        found = 0;

        if (strcmp(input, "1") == 0 || strstr(input, "owner login") != NULL) {
            owner_login();
            found = 1;
        } else if (strcmp(input, "2") == 0 || strstr(input, "customer sign up") != NULL) {
            new_customer_registration();
            found = 1;
        } else if (strcmp(input, "3") == 0 || strstr(input, "existing customer login") != NULL) {
            if (console_customer_login(loggedInUser)) {
                printf("Login successful!\n");
            } else {
                printf("Invalid credentials.\n");
            }
            found = 1;
        } else if (strcmp(input, "4") == 0 || strstr(input, "driver management") != NULL) {
            driver_management();
            found = 1;
        } else if (strcmp(input, "5") == 0 || strstr(input, "customer support") != NULL) {
            customer_support();
            found = 1;
        } else if (strcmp(input, "6") == 0 || strstr(input, "rent a car") != NULL) {
            if (strlen(loggedInUser) > 0) {
                rent_a_car(loggedInUser);
            } else {
                printf("Please login first to rent a car.\n");
            }
            found = 1;
        } else if (strcmp(input, "7") == 0 || strstr(input, "car owners") != NULL) {
            display_car_owners();
            found = 1;
        }

        if (!found) {
            handle_invalid_input();
        } else {
            print_design();
            Sleep(1000);
            clearScreen();
            display_menu();
        }
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    load_css();

    GtkWidget* window = create_main_window();
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
