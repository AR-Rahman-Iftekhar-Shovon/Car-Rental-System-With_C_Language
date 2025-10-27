#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "car.h"
#include "rent_a_car.h"
#include "view_rental_history.h"
#include "customer_login.h"

#define MAX_CARS 9

void rent_a_car() {
    system("cls");

    char company[][20] = {"Lamborghini", "BMW", "Audi", "Mercedes", "Ferrari", "Toyota", "Pajero", "Premio", "Honda"};
    char model[][20] = {"Countach", "Bmw i5", "Audi R8", "Benz S", "Ferrari SF", "2016", "Maxultra", "GX34", "CD40"};
    char color[][20] = {"Green", "Gray", "Metalic Blue", "Black", "Red", "White", "Silver", "Blue", "Yellow"};
    char max_speed[][20] = {"335 km/h", "193 km/h", "316 km/h", "155 km/h", "340 km/h", "180 km/h", "220 km/h", "200 km/h", "180 km/h"};
    int price[] = {5000, 2100, 4245, 11890, 5900, 3000, 5000, 4000, 2500};
    char plate_no[][100] = {"dh-123","V-2433","rm-69","S-325","m-35","t-423","ch-56","lh-23","kh-1323"};
    char owners[][20] = {"Shovon", "Narju", "Shuvo", "Shaown", "Shanzida", "Shovon", "Narju", "Shaown", "Shuvo"};
    int booked[MAX_CARS] = {0};


    FILE *file = fopen("booked_cars.txt", "r");
    if (file != NULL) {
        for (int i = 0; i < MAX_CARS; i++) {
            fscanf(file, "%d", &booked[i]);
        }
        fclose(file);
    }

    char inputemail[100] = {0};
    char contact[100] = {0};
    char customer_name[100] = {0};

    printf("\n\t\t\t\t\t*********************************************************\n");
    printf("\t\t\t\t\t*                     [Rent A Car]                      *\n");
    printf("\t\t\t\t\t*********************************************************\n\n");


    if (strlen(loggedInUserEmail) > 0) {
        strcpy(inputemail, loggedInUserEmail);
        printf("\t\t\t\t\tLogged in as: %s\n", inputemail);


        FILE *customer_file = fopen("customers.txt", "r");
        if (customer_file != NULL) {
            char name[100], contact_num[100], email[100], password[100];
            while (fscanf(customer_file, "Name: %s\nContact: %s\nEmail: %s\nPassword: %s\n\n",
                         name, contact_num, email, password) == 4) {
                if (strcmp(email, loggedInUserEmail) == 0) {
                    strcpy(customer_name, name);
                    strcpy(contact, contact_num);
                    break;
                }
            }
            fclose(customer_file);
        }
    } else {
        printf("\t\t\t\t\tEnter your name              : ");
        scanf("%s", customer_name);
        printf("\t\t\t\t\tEnter your contact number    : ");
        scanf("%s", contact);
        printf("\t\t\t\t\tEnter email                  : ");
        scanf("%s", inputemail);
    }

    sleep(1);
    printf("\n\n\t\t\t\t\t\t    Please wait while we process your request...\n");
    sleep(2);

    printf("\n\t\t\t\t\t-------------------------------------------------------------\n");
    printf("\t\t\t\t\tWelcome! You are now registered in our rental system.\n");
    printf("\t\t\t\t\t-------------------------------------------------------------\n");

    int choose = 0;
    int car_owner = -1;

    while (1) {
        printf("\n\n\t\t\t\t\t==================== AVAILABLE CARS ====================\n");
        for (int i = 0; i < MAX_CARS; i++) {
            printf("\t\t\t\t\t%d. %-12s | Model: %-10s | Status: %s\n",
                i + 1, company[i], model[i], booked[i] ? "Booked" : "Available");
        }
        printf("\t\t\t\t\t========================================================\n");

        printf("\n\t\t\t\t\tEnter your choice (1-%d): ", MAX_CARS);
        scanf("%d", &choose);

        if (choose < 1 || choose > MAX_CARS) {
            printf("\n\t\t\t\t\t!!! Invalid choice. Please select a valid car. !!!\n");
            continue;
        }

        car_owner = choose - 1;

        if (booked[car_owner]) {
            printf("\n\t\t\t\t\t*** This car is already booked. Please choose another. ***\n");
            continue;
        } else {
            break;
        }
    }

    printf("\n\t\t\t\t\t-------------------- Car Details ----------------------\n");
    printf("\t\t\t\t\tCompany      : %s\n", company[car_owner]);
    printf("\t\t\t\t\tModel        : %s\n", model[car_owner]);
    printf("\t\t\t\t\tColor        : %s\n", color[car_owner]);
    printf("\t\t\t\t\tMax Speed    : %s\n", max_speed[car_owner]);
    printf("\t\t\t\t\tPrice        : $%d\n", price[car_owner]);
    printf("\t\t\t\t\tPlate Number : %s\n", plate_no[car_owner]);
    printf("\t\t\t\t\tOwner        : %s\n", owners[car_owner]);
    printf("\t\t\t\t\t--------------------------------------------------------\n");

    struct tm start_date = {0};
    struct tm end_date = {0};
    char buffer[50];

    printf("\n\t\t\t\t\tEnter the rental start date (YYYY-MM-DD): ");
    scanf("%s", buffer);
    sscanf(buffer, "%4d-%2d-%2d", &start_date.tm_year, &start_date.tm_mon, &start_date.tm_mday);
    start_date.tm_year -= 1900;
    start_date.tm_mon -= 1;

    printf("\t\t\t\t\tEnter the rental end date (YYYY-MM-DD): ");
    scanf("%s", buffer);
    sscanf(buffer, "%4d-%2d-%2d", &end_date.tm_year, &end_date.tm_mon, &end_date.tm_mday);
    end_date.tm_year -= 1900;
    end_date.tm_mon -= 1;

    time_t start_time = mktime(&start_date);
    time_t end_time = mktime(&end_date);
    double rental_duration = difftime(end_time, start_time) / (60 * 60 * 24);

    printf("\n\t\t\t\t\tDo you want to book this car? (1 for Yes, 0 for No): ");
    int confirm;
    scanf("%d", &confirm);

    if (confirm == 1) {
        booked[car_owner] = 1;
        int original_price = price[car_owner];
        float discounted_price = original_price * 0.8;

        float total_price = rental_duration * original_price;
        float total_discount = rental_duration * discounted_price;

        printf("\n\t\t\t\t\t==================== CASH MEMO ====================\n");
        printf("\t\t\t\t\tCustomer Name     : %s\n", customer_name);
        printf("\t\t\t\t\tEmail            : %s\n", inputemail);
        printf("\t\t\t\t\tContact          : %s\n", contact);
        printf("\t\t\t\t\tCar Booked       : %s %s\n", company[car_owner], model[car_owner]);
        printf("\t\t\t\t\tRental Duration  : %.0f days\n", rental_duration);
        printf("\t\t\t\t\tRental Dates     : %04d-%02d-%02d to %04d-%02d-%02d\n",
            start_date.tm_year + 1900, start_date.tm_mon + 1, start_date.tm_mday,
            end_date.tm_year + 1900, end_date.tm_mon + 1, end_date.tm_mday);
        printf("\t\t\t\t\tOriginal Price   : $%.2f\n", total_price);
        printf("\t\t\t\t\tDiscounted Price : $%.2f (20%% off)\n", total_discount);
        printf("\t\t\t\t\t====================================================\n");


        RentalHistory history;
        strcpy(history.carBrand, company[car_owner]);
        strcpy(history.carModel, model[car_owner]);
        strcpy(history.renterEmail, inputemail);
        strcpy(history.ownerID, owners[car_owner]);
        sprintf(history.rentalDate, "%04d-%02d-%02d",
            start_date.tm_year + 1900, start_date.tm_mon + 1, start_date.tm_mday);
        sprintf(history.returnDate, "%04d-%02d-%02d",
            end_date.tm_year + 1900, end_date.tm_mon + 1, end_date.tm_mday);
        history.price = total_discount;

        add_rental_record(&history);

        printf("\n\t\t\t\t\tThank you, %s! The car has been successfully booked.\n", customer_name);
        sleep(3);


        file = fopen("booked_cars.txt", "w");
        for (int i = 0; i < MAX_CARS; i++) {
            fprintf(file, "%d ", booked[i]);
        }
        fclose(file);
    } else {
        printf("\n\t\t\t\t\t*** Booking cancelled. ***\n");
    }
}

