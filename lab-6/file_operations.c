#include <stdio.h>
#include <string.h>
#include <math.h>
#include <io.h>

#include "passenger.h"
#include "file_operations.h"
#include "../libs/input.h"
#include "../libs/utils.h"

int index_validator(int index) {
    return index > 0;
}

int count_validator(int count) {
    return count >= 0 && count < 10;
}

int search_index_validator(int index) {
    return index > 0 && index < 10;
}

void print_header() {
    printf("\n%-5s %-12s %-12s %-20s %-10s %-10s\n",
           "N", "Number", "Date", "FCs", "Seat", "Baggage");
}

void print_passenger(Passenger p, int index) {
    printf("%-5d %-12d %02d/%02d/%04d   %-20s %-10s %-10.2f\n",
           index, p.flight_number,
           p.flight_date.day, p.flight_date.month, p.flight_date.year,
           p.name, p.seat, p.baggage_weight);
}

void input_passenger(Passenger *p) {
    for (int i = 0; i < 30; ++i) p->name[i] = '\0';
    for (int i = 0; i < 3; ++i) p->seat[i] = '\0';

    input_int(&p->flight_number, "Enter flight number: ", "Incorrect flight number. Please try again.",
              flight_number_validator);
    input_int(&p->flight_date.day, "Enter flight day (number): ", "Incorrect flight day. Please try again.",
              day_validator);
    input_int(&p->flight_date.month, "Enter flight month (number): ", "Incorrect flight month. Please try again.",
              month_validator);
    input_int(&p->flight_date.year, "Enter flight year (number): ", "Incorrect flight year. Please try again.",
              year_validator);
    char *name;
    input_string(&name, "Enter passenger's name: ", "Incorrect format. Please try again.",
                 name_validator);
    for (int i = 0; i < strlen(name); ++i) p->name[i] = name[i];
    char *seat;
    input_string(&seat, "Enter passenger's seat number (12A): ", "Incorrect format. Please try again.",
                 seat_validator);
    for (int i = 0; i < strlen(seat); ++i) p->seat[i] = seat[i];
    input_double(&p->baggage_weight, "Enter baggage weight: ", "Incorrect number. Please try again.",
                 baggage_weight_validator);
}

void add_record(const char *filename) {
    FILE *fp = fopen(filename, "ab");

    Passenger p;
    input_passenger(&p);

    fwrite(&p, sizeof(Passenger), 1, fp);
    fclose(fp);
    printf("Record addition done.\n");
}

void delete_record(const char *filename) {
    FILE *fp = fopen(filename, "rb+");
    if (fp == NULL) {
        perror("Error, file not exists.");
        fclose(fp);
        return;
    }

    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    int rec_size = sizeof(Passenger);
    if (file_size % rec_size != 0) {
        perror("Error, file size doesn't match with size of Passenger.");
        return;
    }

    int records_count = file_size / rec_size;
    if (records_count == 0) {
        printf("File is empty.");
    }

    int index;
    input_int(&index, "Enter index of the record to delete: ", "Please try again.", index_validator);
    if (index > records_count) {
        printf("Index is larger than records count. Please try again.");
        fclose(fp);
        return;
    }

    for (int i = index; i < records_count; i++) {
        Passenger p;
        fseek(fp, i * rec_size, SEEK_SET);
        fread(&p, rec_size, 1, fp);
        fseek(fp, (i - 1) * rec_size, SEEK_SET);
        fwrite(&p, rec_size, 1, fp);
    }

    fflush(fp);
    _chsize(_fileno(fp), file_size - rec_size);
    fclose(fp);
}

void search_records(const char *filename) {
    FILE *fp = fopen(filename, "rb+");
    if (fp == NULL) {
        perror("File doesnt exists.");
        return;
    }

    printf("Search with parament: \n");
    printf("1. Flight number\n");
    printf("2. Flight day\n");
    printf("3. Flight month\n");
    printf("4. Flight year\n");
    printf("5. Passenger name\n");
    printf("6. seat\n");
    printf("7. baggage weight\n");

    int field;
    input_int(&field, "", "", search_index_validator);

    Passenger search;
    switch (field) {
        case 1:
            input_int(&search.flight_number, "Enter flight number: ", "Incorrect flight number. Please try again.",
                      flight_number_validator);
            break;
        case 2:
            input_int(&search.flight_date.day, "Enter flight day (number): ", "Incorrect flight day. Please try again.",
                      day_validator);
            break;
        case 3:
            input_int(&search.flight_date.month, "Enter flight month (number): ",
                      "Incorrect flight month. Please try again.", month_validator);
            break;
        case 4:
            input_int(&search.flight_date.year, "Enter flight year (number): ",
                      "Incorrect flight year. Please try again.", year_validator);
            break;
        case 5:
            input_string(&search.name, "Enter passenger's first name: ",
                         "Incorrect format. Please try again.", name_validator);
            break;
        case 6:
            input_string(&search.seat, "Enter passenger's seat number (12A): ", "Incorrect format. Please try again.",
                         seat_validator);
            break;
        case 7:
            input_double(&search.baggage_weight, "Enter baggage weight: ", "Incorrect number. Please try again.",
                         baggage_weight_validator);
            break;
        default:
            printf("Неверный выбор.\n");
            fclose(fp);
            return;
    }

    Passenger p;
    int found = 0;
    int count = 0;
    while (fread(&p, sizeof(Passenger), 1, fp) == 1) {
        count++;
        int match = 0;
        switch (field) {
            case 1:
                if (p.flight_number == search.flight_number) match = 1;
                break;
            case 2:
                if (p.flight_date.day == search.flight_date.day) match = 1;
                break;
            case 3:
                if (p.flight_date.month == search.flight_date.month) match = 1;
                break;
            case 4:
                if (p.flight_date.year == search.flight_date.year) match = 1;
                break;
            case 5:
                if (strstr(p.name, search.name) != NULL) match = 1;
                break;
            case 6:
                if (strcmp(p.seat, search.seat) == 0) match = 1;
                break;
            case 7:
                if (fabs(p.baggage_weight - search.baggage_weight) < EPS) match = 1;
                break;
            default:
                break;
        }
        if (match) {
            if (!found) print_header();
            print_passenger(p, count);
            found = 1;
        }
    }

    if (!found)
        printf("No matches found.\n");
    fclose(fp);
}

void edit_record(const char *filename) {
    FILE *fp = fopen(filename, "rb+");
    if (fp == NULL) {
        perror("File doesnt exists.");
        return;
    }

    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    int rec_size = sizeof(Passenger);
    if (file_size % rec_size != 0) {
        perror("Error, file size doesn't match with size of Passenger.");
        return;
    }

    int records_count = file_size / rec_size;
    if (records_count == 0) {
        printf("File is empty.");
    }

    int index;
    input_int(&index, "Enter index of the record to delete: ", "Please try again.", index_validator);
    if (index > records_count) {
        printf("Index is larger than records count. Please try again.");
        fclose(fp);
        return;
    }

    Passenger p;
    fseek(fp, (index - 1) * rec_size, SEEK_SET);
    fread(&p, rec_size, 1, fp);

    print_header();
    print_passenger(p, 1);

    printf("Write new passenger information.\n");
    Passenger new;
    input_passenger(&p);

    fseek(fp, (index - 1) * rec_size, SEEK_SET);
    fwrite(&p, rec_size, 1, fp);
    fclose(fp);
    printf("New record saved");
}

void print_all(const char *filename) {
    FILE *fp = fopen(filename, "rb+");
    if (fp == NULL) {
        perror("File doesnt exists.");
        return;
    }

    Passenger p;
    int rec_num = 0;
    print_header();
    while (fread(&p, sizeof(Passenger), 1, fp) == 1) {
        rec_num++;
        print_passenger(p, rec_num);
    }
    if (rec_num == 0)
        printf("No matches found.\n");
    fclose(fp);
}

void initialize_file(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp) {
        fclose(fp);
        return;
    }

#ifdef AUTO_INITIALIZER
    printf("The file will be initialized automatically.\n");
    Passenger initial_data[] = {
            {101, {15, 3, 2025}, "Ivanov I.I.",  "12A", 15.5},
            {101, {15, 3, 2025}, "Petrov P.P.",  "12B", 20.0},
            {102, {16, 3, 2025}, "Sidorov S.S.", "5C",  10.2}
    };
    int count = sizeof(initial_data) / sizeof(initial_data[0]);
    fp = fopen(filename, "wb");
    if (!fp) {
        perror("File creation error.");
        return;
    }
    fwrite(initial_data, sizeof(Passenger), count, fp);
    fclose(fp);
    printf("The file is initialized from an array (%d records).\n", count);
#else
    printf("Initialize the initial file data manually. To change it, add definition -AUTO_INITIALIZER.\n\n");
    int count;
    input_int(&count, "Enter the number of new entries: ", "Error, please try again.", count_validator);
    for (int i = 0; i < count; ++i) {
        add_record(filename);
        printf("\n");
    }
#endif

}