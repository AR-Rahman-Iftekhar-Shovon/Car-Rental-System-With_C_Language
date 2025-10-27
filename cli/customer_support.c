#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "customer_support.h"
#include "customer_login.h"
#include "view_rental_history.h"

void customer_support() {
    system("cls");

    printf("\n\t\t\t\t\t***********************************************\n");
    printf("\t\t\t\t\t*               [Customer Support]            *\n");
    printf("\t\t\t\t\t***********************************************\n");

    printf("\n\t\t\t\t\tHow can we assist you today?\n");
    printf("\t\t\t\t\t1. Technical Issues\n");
    printf("\t\t\t\t\t2. Car Availability\n");
    printf("\t\t\t\t\t3. Payment Issues\n");
    printf("\t\t\t\t\t4. Rental History Inquiry\n");
    printf("\t\t\t\t\tEnter your issue choice: ");

    int issue_choice;
    char name[20], number[20], email[100];

    scanf("%d", &issue_choice);


    switch (issue_choice) {
        case 1:
            printf("\n\t\t\t\t\t***********************************************\n");
            printf("\t\t\t\t\t*       Technical Issue Assistance            *\n");
            printf("\t\t\t\t\t***********************************************\n");
            printf("\n\t\t\t\t\tPlease Enter Your Name: ");
            scanf("%s", name);
            printf("\t\t\t\t\tPlease Enter Your Number: ");
            scanf("%s", number);
            printf("\n\n\t\t\t\t\t***********************************************\n");
            printf("\t\t\t\t\t* Our team will get back to you regarding the *\n");
            printf("\t\t\t\t\t* technical issues.                           *\n");
            printf("\t\t\t\t\t***********************************************\n");
            break;
        case 2:
            printf("\n\t\t\t\t\t***********************************************\n");
            printf("\t\t\t\t\t*         Car Availability Assistance         *\n");
            printf("\t\t\t\t\t***********************************************\n");
            printf("\n\t\t\t\t\tPlease Enter Your Name: ");
            scanf("%s", name);
            printf("\t\t\t\t\tPlease Enter Your Number: ");
            scanf("%s", number);
            printf("\n\n\t\t\t\t\t***********************************************\n");
            printf("\t\t\t\t\t* We will provide information on car         *\n");
            printf("\t\t\t\t\t* availability shortly.                      *\n");
            printf("\t\t\t\t\t***********************************************\n");
            break;
        case 3:
            printf("\n\t\t\t\t\t***********************************************\n");
            printf("\t\t\t\t\t*         Payment Issue Assistance            *\n");
            printf("\t\t\t\t\t***********************************************\n");
            printf("\nPlease Enter Your Name: ");
            scanf("%s", name);
            printf("Please Enter Your Number: ");
            scanf("%s", number);
            printf("\n\n\t\t\t\t\t***********************************************\n");
            printf("\t\t\t\t\t* Payment issues will be addressed within     *\n");
            printf("\t\t\t\t\t* 24 hours.                                   *\n");
            printf("\t\t\t\t\t***********************************************\n");
            break;
        case 4:
            printf("\n\t\t\t\t\t***********************************************\n");
            printf("\t\t\t\t\t*         Rental History Inquiry              *\n");
            printf("\t\t\t\t\t***********************************************\n");
            printf("\n\t\t\t\t\tPlease Enter Your Email: ");
            scanf("%s", email);
            view_rental_history(email);
            break;
        default:
            printf("\n\t\t\t\t\t***********************************************\n");
            printf("\t\t\t\t\t*       Invalid choice. Please select a valid *\n");
            printf("\t\t\t\t\t*       option.                             *\n");
            printf("\t\t\t\t\t***********************************************\n");
    }
}
