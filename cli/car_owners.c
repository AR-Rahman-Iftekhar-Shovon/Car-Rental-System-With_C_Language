#include <stdio.h>
#include <stdlib.h> // For system("cls")
#include <string.h>
#include "car_owners.h"
#include "car.h"

void display_car_owners() {
    system("cls"); // Clear screen (works in Code::Blocks on Windows)

    printf("\t\t\t\t=====================================================================\n");
    printf("\t\t\t\t|                           CAR OWNERS LIST                         |\n");
    printf("\t\t\t\t=====================================================================\n");

    printf("\t\t\t\t| 1. AR Rahman Iftekhar Shovon                                      |\n");
    printf("\t\t\t\t|     [Lamborghini] [Toyota]                                        |\n");
    printf("\t\t\t\t---------------------------------------------------------------------\n");

    printf("\t\t\t\t| 2. Naimun Hasan Narju                                             |\n");
    printf("\t\t\t\t|     [BMW] [Pajero]                                                |\n");
    printf("\t\t\t\t---------------------------------------------------------------------\n");

    printf("\t\t\t\t| 3. Ruku Hasan Zim                                                 |\n");
    printf("\t\t\t\t|     [Mercedes]                                                    |\n");
    printf("\t\t\t\t---------------------------------------------------------------------\n");

    printf("\t\t\t\t| 4. Shanzida Sanzu                                                 |\n");
    printf("\t\t\t\t|     [Ferrari] [Honda]                                             |\n");
    printf("\t\t\t\t---------------------------------------------------------------------\n");

    printf("\t\t\t\t| 5. Mohammad Shahriar Shaown                                       |\n");
    printf("\t\t\t\t|     [Audi] [Premio]                                               |\n");
    printf("\t\t\t\t=====================================================================\n");
}
