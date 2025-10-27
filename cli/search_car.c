#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "search_car.h"

#define MAX_CARS 9


void search_car() {

    char company[][20] = {"Lamborghini", "BMW", "Audi", "Mercedes", "Ferrari", "Toyota", "Pajero", "Premio", "Honda"};
    char model[][20] = {"Countach", "Bmw i5", "Audi R8", "Benz S", "Ferrari SF", "2016", "Maxultra", "GX34", "CD40"};
    int price[] = {5000, 2100, 4245, 11890, 5900, 3000, 5000, 4000, 2500};  // Prices for the cars

    char search_term[20];
    printf("Enter car brand or model to search: ");
    scanf("%s", search_term);
    printf("\nSearch Results:\n");
    for (int i = 0; i < MAX_CARS; i++) {

        if (strstr(company[i], search_term) != NULL || strstr(model[i], search_term) != NULL) {

            printf("Car %d: %s %s | Price: $%d\n", i + 1, company[i], model[i], price[i]);
        }
    }
}
