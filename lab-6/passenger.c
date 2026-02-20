#include "../libs/input.h"
#include "passenger.h"

int flight_number_validator(const int number) {
    return number > 0 & number < 1000;
}

int day_validator(const int day) {
    return day > 0 && day <= 31;
}

int month_validator(const int month) {
    return month > 0 && month <= 12;
}

int year_validator(const int year) {
    return year >= 2000 && year <= 2026;
}

int check_string(const char* str) {
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == '\0' || (str[i] == '.') || (str[i] >= 'a' && str[i] <= 'z') || (str[i]>='A' && str[i]<='Z')) continue;
        return 0;
    }
    return 1;
}

int name_validator(const char* name) {
    char *dup_name = strdup(name);
    char *token = strtok(dup_name, " ");
    while(token != NULL) {
        if (check_string(token) == 0) return 0;
        token = strtok(NULL, " ");
    }
    return 1;
}

int seat_validator(const char *seat) {
    if (strlen(seat) > 3) return 0;
    for (int i = 0; i < strlen(seat); ++i) {
        if (('0' <= seat[i] && seat[i] <= '9') || ('A' <= seat[i] && seat[i] <= 'Z')) continue;
        return 0;
    }
    return 1;
}

int baggage_weight_validator(const double weight) {
    return weight >= 0 && weight <= 100;
}