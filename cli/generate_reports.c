#include <stdio.h>
#include <stdlib.h>
#include "generate_reports.h"

void generate_reports() {
    FILE *file = fopen("rental_history.txt", "r");
    if (!file) {
        printf("Error opening rental history file.\n");
        return;
    }

    printf("\nRental Report:\n");
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}
