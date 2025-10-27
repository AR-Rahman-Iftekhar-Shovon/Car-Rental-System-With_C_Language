#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "view_rental_history.h"
#include "rent_a_car.h"

void create_file_if_not_exists() {
    FILE *file = fopen("rental_history.txt", "r");
    if (!file) {
        file = fopen("rental_history.txt", "w");
        if (file) {
            fclose(file);
            printf("File 'rental_history.txt' was created.\n");
        } else {
            printf("Error creating rental_history.txt.\n");
        }
    } else {
        fclose(file);
    }
}

void view_rental_history(const char *email) {
    system("cls");
    printf("\n\t\t\t\t\t==============================================\n");
    printf("\t\t\t\t\t|              RENTAL HISTORY                 |\n");
    printf("\t\t\t\t\t==============================================\n\n");

    FILE *file = fopen("rental_history.txt", "r");
    if (file == NULL) {
        printf("\t\t\t\t\tNo rental history found.\n");
        return;
    }

    char line[256];
    int found = 0, record_count = 0;
    char owner[100], car[100], renter[100], dates[100], price[100];

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Owner: ", 7) == 0) {
            strcpy(owner, line + 7);
            owner[strcspn(owner, "\n")] = '\0';

            fgets(line, sizeof(line), file);
            strcpy(car, line + 5);
            car[strcspn(car, "\n")] = '\0';

            fgets(line, sizeof(line), file);
            strcpy(renter, line + 11);
            renter[strcspn(renter, "\n")] = '\0';

            fgets(line, sizeof(line), file);
            strcpy(dates, line + 7);
            dates[strcspn(dates, "\n")] = '\0';

            fgets(line, sizeof(line), file);
            strcpy(price, line + 7);
            price[strcspn(price, "\n")] = '\0';

            fgets(line, sizeof(line), file); // blank line

            if (strcmp(renter, email) == 0) {
                found = 1;
                record_count++;

                printf("\t\t\t\t\t----------------------------------------------\n");
                printf("\t\t\t\t\t| Rental Record #%d                           |\n", record_count);
                printf("\t\t\t\t\t----------------------------------------------\n");
                printf("\t\t\t\t\t| Car Owner    : %-30s |\n", owner);
                printf("\t\t\t\t\t| Car Details  : %-30s |\n", car);
                printf("\t\t\t\t\t| Rental Dates : %-30s |\n", dates);
                printf("\t\t\t\t\t| Total Price  : %-30s |\n", price);
                printf("\t\t\t\t\t----------------------------------------------\n");
                Sleep(4000);
            }
        }
    }

    if (!found) {
        printf("\t\t\t\t\t| No rental history found for this email.    |\n");
    } else {
        printf("\n\t\t\t\t\tTotal Rentals: %d\n", record_count);
    }

    fclose(file);
    printf("\n\t\t\t\t\tPress Enter to continue...");
    getchar();
}

void view_owner_rental_history(const char *ownerID) {
    system("cls");
    printf("\n\t\t\t\t\t==============================================\n");
    printf("\t\t\t\t\t|           OWNER RENTAL HISTORY             |\n");
    printf("\t\t\t\t\t==============================================\n\n");

    FILE *file = fopen("rental_history.txt", "r");
    if (file == NULL) {
        printf("\t\t\t\t\tNo rental history found.\n");
        return;
    }

    char line[256];
    int found = 0;
    char owner[100], car[100], renter[100], dates[100], price[100];

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Owner: ", 7) == 0) {
            strcpy(owner, line + 7);
            owner[strcspn(owner, "\n")] = '\0';

            fgets(line, sizeof(line), file);
            strcpy(car, line + 5);
            car[strcspn(car, "\n")] = '\0';

            fgets(line, sizeof(line), file);
            strcpy(renter, line + 11);
            renter[strcspn(renter, "\n")] = '\0';

            fgets(line, sizeof(line), file);
            strcpy(dates, line + 7);
            dates[strcspn(dates, "\n")] = '\0';

            fgets(line, sizeof(line), file);
            strcpy(price, line + 7);
            price[strcspn(price, "\n")] = '\0';

            fgets(line, sizeof(line), file); // blank line

            if (strcmp(owner, ownerID) == 0) {
                found = 1;

                printf("\t\t\t\t\t----------------------------------------------\n");
                printf("\t\t\t\t\t| Car         : %-30s |\n", car);
                printf("\t\t\t\t\t| Rented by   : %-30s |\n", renter);
                printf("\t\t\t\t\t| Dates       : %-30s |\n", dates);
                printf("\t\t\t\t\t| Price       : %-30s |\n", price);
                printf("\t\t\t\t\t----------------------------------------------\n");
                Sleep(4000);
            }
        }
    }

    if (!found) {
        printf("\t\t\t\t\tNo rental history found for this owner.\n");
    }

    fclose(file);
    printf("\n\t\t\t\t\tPress Enter to continue...");
    getchar();
}

void add_rental_record(const RentalHistory *history) {
    FILE *file = fopen("rental_history.txt", "a");
    if (!file) {
        printf("Error opening rental history file.\n");
        return;
    }

    fprintf(file, "Owner: %s\n", history->ownerID);
    fprintf(file, "Car: %s %s\n", history->carBrand, history->carModel);
    fprintf(file, "Rented by: %s\n", history->renterEmail);
    fprintf(file, "Dates: %s to %s\n", history->rentalDate, history->returnDate);
    fprintf(file, "Price: $%.2f\n\n", history->price);

    fclose(file);
}
