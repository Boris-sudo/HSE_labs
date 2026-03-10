#include <stdio.h>
#include <string.h>
#include <math.h>
#include <io.h>
#include <time.h>

#include "passenger.h"
#include "file_operations.h"
#include "../libs/input.h"
#include "../libs/utils.h"

int SINGLE_PRINT = 0;

int print_operation_validator(int operation) {
    return operation >= 0 && operation <= 3;
}

int index_validator(int index) {
    return index > 0;
}

int records_count_validator(int count) {
    return count > 0 && count < 1e7;
}

int count_validator(int count) {
    return count >= 0 && count < 10;
}

int sort_type_validator(int mode) {
    return mode >= 1 && mode <= 4;
}

int sort_mode_validator(int mode) {
    return mode >= 1 && mode <= 2;
}

int search_index_validator(int index) {
    return index > 0 && index < 6;
}

void input_passenger(Passenger *p) {
    for (int i = 0; i < 30; ++i) p->name[i] = '\0';
    for (int i = 0; i < 4; ++i) p->seat[i] = '\0';

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

    printf("\nSearch with parament: \n");
    printf("1. Flight number\n");
    printf("2. Flight date\n");
    printf("3. Passenger name\n");
    printf("4. Seat\n");
    printf("5. Baggage weight\n");

    int field;
    input_int(&field, "Input value: ", "Error, wrong format.", search_index_validator);

    Passenger search;
    for (int i = 0; i < 50; ++i) search.name[i] = '\0';
    for (int i = 0; i < 4; ++i) search.seat[i] = '\0';
    char *str;
    switch (field) {
        case 1:
            input_int(&search.flight_number, "Enter flight number: ", "Incorrect flight number. Please try again.",
                      flight_number_validator);
            break;
        case 2:
            input_int(&search.flight_date.day, "Enter flight day (number): ", "Incorrect flight day. Please try again.",
                      day_validator);
            input_int(&search.flight_date.month, "Enter flight month (number): ",
                      "Incorrect flight month. Please try again.", month_validator);
            input_int(&search.flight_date.year, "Enter flight year (number): ",
                      "Incorrect flight year. Please try again.", year_validator);
            break;
        case 3:
            input_string(&str, "Enter passenger's first name: ",
                         "Incorrect format. Please try again.", name_validator);
            for (int i = 0; i < strlen(str); ++i) search.name[i] = str[i];
            break;
        case 4:
            input_string(&str, "Enter passenger's seat number (12A): ", "Incorrect format. Please try again.",
                         seat_validator);
            for (int i = 0; i < strlen(str); ++i) search.seat[i] = str[i];
            break;
        case 5:
            input_double(&search.baggage_weight, "Enter baggage weight: ", "Incorrect number. Please try again.",
                         baggage_weight_validator);
            break;
        default:
            printf("Incorrect choice.\n");
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
                if (p.flight_date.day == search.flight_date.day && p.flight_date.month == search.flight_date.month &&
                    p.flight_date.year == search.flight_date.year)
                    match = 1;
                break;
            case 3:
                if (strstr(p.name, search.name) != NULL) match = 1;
                break;
            case 4:
                if (strcmp(p.seat, search.seat) == 0) match = 1;
                break;
            case 5:
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

    Passenger p;
    int page = 0;
    int pages = (records_count + 9) / 10 - 1;
    Passenger arr[10];
    while (1) {
        fseek(fp, 10 * page * rec_size, SEEK_SET);
        fread(arr, rec_size, 10, fp);
        print_table(arr, page, records_count);

        if (SINGLE_PRINT) break;

        int operation;
        input_int(&operation, "Enter operation: ", "Error, please try again.", print_operation_validator);
        if (operation == 0) break;
        else if (operation == 1 && page > 0) page--;
        else if (operation == 2 && page < pages) page++;
        else if (operation == 3) {
            int page_index;
            input_int(&page_index, "Enter page index: ", "Error, please try again", index_validator);
            page_index--;
            page_index = page_index > pages ? pages : page_index;
        }
    }
    fclose(fp);
}

void print_max(const char *filename) {
    SINGLE_PRINT = 1;
    print_all(filename);
    SINGLE_PRINT = 0;
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
            { 101, { 15, 3, 2025 }, "Ivanov I.I.",  "12A", 15.5 },
            { 101, { 15, 3, 2025 }, "Petrov P.P.",  "12B", 20.0 },
            { 102, { 16, 3, 2025 }, "Sidorov S.S.", "5C",  10.2 }
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

void sort_file(const char *filename) {
    FILE *fp = fopen(filename, "rb+");
    if (fp == NULL) {
        perror("File doesnt exists.");
        return;
    }

    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    int rec_size = sizeof(Passenger);
    if (file_size % rec_size != 0) {
        printf("Error with data");
        return;
    }

    int count = file_size / rec_size;
    Passenger *arr = (Passenger *) malloc(count * rec_size);
    rewind(fp);
    fread(arr, rec_size, count, fp);

    int type;
    printf("\nSorting type:\n");
    printf("1. Shaker sort\n");
    printf("2. Merge sort\n");
    printf("3. Fast sort\n");
    printf("4. Random shuffle\n");
    input_int(&type, "Enter soring type: ", "Error, please try again.", sort_type_validator);

    int mode;
    if (type != 4) {
        printf("\nSorting mode:\n");
        printf("1. ascending order\n");
        printf("2. decreasing order\n");
        input_int(&mode, "Enter soring mode: ", "Error, please try again.", sort_mode_validator);
    }

    printf("\nInput array (first 10):");
    int print_count = count < 10 ? count : 10;
    print_header();
    for (int i = 0; i < print_count; ++i)
        print_passenger(arr[i], i + 1);

    passenger_cmp cmp = (mode == 1 ? cmp_asc : cmp_desc);

    clock_t start = clock();
    if (type == 1) shaker_sort(arr, count, cmp);
    else if (type == 2) merge_sort(arr, count, cmp);
    else if (type == 3) quick_sort(arr, count, cmp);
    else if (type == 4) shuffle_arr(arr, count);

    clock_t finish = clock();

    double elapsed = (double) (finish - start) / CLOCKS_PER_SEC;
    printf("\nSorting time: %lf\n", elapsed);
    printf("Sorted array (first 10):");
    print_header();
    for (int i = 0; i < print_count; ++i)
        print_passenger(arr[i], i + 1);

    rewind(fp);
    fwrite(arr, rec_size, count, fp);
    fclose(fp);
}

void add_random_records(const char *filename) {
    FILE *fp = fopen(filename, "wb+");
    if (fp == NULL) {
        perror("File error");
        return;
    }

    int count;
    input_int(&count, "Enter count of records: ", "Error, please try again.", records_count_validator);

    Passenger *arr = (Passenger *) malloc(count * sizeof(Passenger));
    generate_array(arr, count);

    fwrite(arr, sizeof(Passenger), count, fp);
    fclose(fp);
    printf("Records successfully generated");
    print_max(filename);
}

void print_size(const char *filename) {
    FILE *fp = fopen(filename, "rb+");
    if (fp == NULL) {
        perror("File doesn't exist");
        return;
    }

    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    int rec_size = sizeof(Passenger);

    if (file_size % rec_size != 0) {
        printf("unexpected error!");
        return;
    }

    int count = file_size / rec_size;
    printf("\nEntities count: %d\n", count);

    fclose(fp);
}