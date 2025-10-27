// car.h
#ifndef CAR_H
#define CAR_H

typedef struct {
    char ownerID[50];
    char carBrand[50];
    char carModel[50];
    int year;
    float ratePerDay;
    int isAvailable;
} Car;

#endif

