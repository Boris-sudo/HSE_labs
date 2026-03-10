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
    char seat[4]; // example, "12A"
    double baggage_weight;
} Passenger;

typedef int (*passenger_cmp)(const Passenger*, const Passenger*);

int flight_number_validator(int number);
int day_validator(int day);
int month_validator(int month);
int year_validator(int year);
int name_validator(const char* name);
int seat_validator(const char* seat);
int baggage_weight_validator(double weight);

void print_header();
void print_passenger(Passenger p, int index);
void print_table(const Passenger *arr, int page, int pages);

// lab-7
int comparator(const Passenger* a, const Passenger* b, int ascending);
int cmp_asc(const Passenger *a, const Passenger *b); // по возрастанию
int cmp_desc(const Passenger *a, const Passenger *b); // по убыванию

Passenger generate_random_passenger();
void generate_array(Passenger *arr, int n);

void shaker_sort(Passenger *arr, int n, passenger_cmp cmp);
void merge_sort(Passenger *arr, int n, passenger_cmp cmp);
void quick_sort(Passenger *arr, int n, passenger_cmp cmp);
void shuffle_arr(Passenger *arr, int n);

#endif
