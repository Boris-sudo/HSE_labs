#ifndef HSE_PASSENGER_H
#define HSE_PASSENGER_H

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int flight_number;
    Date flight_date;
    char name[50];
    char seat[3]; // example, "12A"
    double baggage_weight;
} Passenger;

int flight_number_validator(int number);
int day_validator(int day);
int month_validator(int month);
int year_validator(int year);
int name_validator(const char* name);
int seat_validator(const char* seat);
int baggage_weight_validator(double weight);

#endif
