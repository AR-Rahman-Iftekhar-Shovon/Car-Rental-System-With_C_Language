#ifndef VIEW_RENTAL_HISTORY_H
#define VIEW_RENTAL_HISTORY_H

typedef struct {
    char carBrand[50];
    char carModel[50];
    char renterEmail[100];
    char ownerID[50];
    char rentalDate[50];
    char returnDate[50];
    float price;
} RentalHistory;

void view_rental_history(const char *email);
void view_owner_rental_history(const char *ownerID);
void add_rental_record(const RentalHistory *history);

#endif
