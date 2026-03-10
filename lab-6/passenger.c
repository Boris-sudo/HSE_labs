#include "../libs/input.h"
#include "passenger.h"
#include "math.h"

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

int check_string(const char *str) {
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == '\0' || (str[i] == '.') || (str[i] >= 'a' && str[i] <= 'z') ||
            (str[i] >= 'A' && str[i] <= 'Z'))
            continue;
        return 0;
    }
    return 1;
}

int name_validator(const char *name) {
    if (strlen(name) > 19) return 0;
    char *dup_name = strdup(name);
    char *token = strtok(dup_name, " ");
    while (token != NULL) {
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

void print_header() {
    printf("\n========================================================================================");
    printf("\n| %-5s | %-12s | %-12s | %-20s | %-10s | %-10s |\n",
           "N", "Number", "Date", "FCs", "Seat", "Baggage");
}

void print_passenger(Passenger p, int index) {
    printf("| %-5d | %-12d | %02d/%02d/%04d   | %-20s | %-10s | %-10.2f |\n",
           index, p.flight_number,
           p.flight_date.day, p.flight_date.month, p.flight_date.year,
           p.name, p.seat, p.baggage_weight);
}

void print_table(const Passenger *arr, int page, int count) {
    int pages = count / 10;
    print_header();
    for (int i = 0; i < 10 && page * 10 + i + 1 <= count; ++i)
        print_passenger(arr[i], page * 10 + i + 1);
    char page_index[16] = "=====0 \\ \0";

    page++;
    pages++;

    int index = 0;
    while (page > 0) {
        page_index[5 - index++] = (page % 10) + '0';
        page /= 10;
    }
    page_index[5 - index] = ' ';

    char s2[6] = "";
    index = 0;
    while (pages > 0) {
        s2[index++] = (pages % 10) + '0';
        pages /= 10;
    }
    index = 9;
    for (int i = strlen(s2) - 1; i >= 0; i--)
        page_index[index++] = s2[i];
    page_index[index] = ' ';

    while (strlen(page_index) < 15)
        strcat(page_index, "=");

    printf("= 1. Back =========================%s============================ 2. Next =\n0. Exit\n3. Choose page\n",
           page_index);
}

// Вспомогательная функция сравнения (возвращает -1, 0, 1)
// ascending = 1 для сортировки по возрастанию, 0 для убывания
int comparator(const Passenger *a, const Passenger *b, int ascending) {
    int cmp = 0;

    if (a->flight_number != b->flight_number)
        cmp = (a->flight_number > b->flight_number ? 1 : -1);
    else {
        if (a->flight_date.year != b->flight_date.year)
            cmp = (a->flight_date.year > b->flight_date.year ? 1 : -1);
        else if (a->flight_date.month != b->flight_date.month)
            cmp = (a->flight_date.month > b->flight_date.month ? 1 : -1);
        else if (a->flight_date.day != b->flight_date.day)
            cmp = (a->flight_date.day > b->flight_date.day ? 1 : -1);
        else {
            cmp = strcmp(a->name, b->name);
            if (cmp == 0) {
                cmp = strcmp(a->seat, b->seat);
                if (cmp == 0) {
                    if (fabs(a->baggage_weight - b->baggage_weight) > 1e-9)
                        cmp = (a->baggage_weight > b->baggage_weight ? 1 : -1);
                } else cmp = cmp / abs(cmp);
            } else cmp = cmp / abs(cmp);
        }
    }

    if (!ascending) cmp = -cmp;
    return cmp;
}

int cmp_asc(const Passenger *a, const Passenger *b) {
    return comparator(a, b, 1);
}

int cmp_desc(const Passenger *a, const Passenger *b) {
    return comparator(a, b, 0);
}

Passenger generate_random_passenger() {
    Passenger p;
    p.flight_number = rand() % 1000;
    p.flight_date.year = 2020 + rand() % 6;
    p.flight_date.month = 1 + rand() % 12;
    p.flight_date.day = 1 + rand() % 28;

    int name_len = 5 + rand() % 16;
    for (int i = 0; i < name_len; i++)
        p.name[i] = 'A' + (rand() % 26);
    p.name[name_len] = '\0';

    p.seat[0] = rand() % 10 + '0';
    p.seat[1] = rand() % 10 + '0';
    p.seat[2] = rand() % 26 + 'A';

    p.baggage_weight = (double) (rand() % 5001) / 100.0;

    return p;
}

void generate_array(Passenger *arr, int n) {
    for (int i = 0; i < n; ++i)
        arr[i] = generate_random_passenger();
}

void shaker_sort(Passenger *arr, int n, passenger_cmp cmp) {
    int left = 0;
    int right = n - 1;
    int swapped = 1;
    while (left < right && swapped) {
        swapped = 0;
        for (int i = left; i < right; i++) {
            if (cmp(&arr[i + 1], &arr[i]) < 0) {
                Passenger temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
        right--;

        swapped = 0;
        for (int i = right; i > left; i--) {
            if (cmp(&arr[i], &arr[i - 1]) < 0) {
                Passenger temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                swapped = 1;
            }
        }
        left++;
    }
}

void merge(Passenger *arr, int left, int mid, int right, Passenger *temp, passenger_cmp cmp) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (cmp(&arr[i], &arr[j]) <= 0)
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = left; i <= right; ++i) arr[i] = temp[i];
}

void merge_sort_rec(Passenger *arr, int left, int right, Passenger *temp, passenger_cmp cmp) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_rec(arr, left, mid, temp, cmp);
    merge_sort_rec(arr, mid + 1, right, temp, cmp);
    merge(arr, left, mid, right, temp, cmp);
}

void merge_sort(Passenger *arr, int n, passenger_cmp cmp) {
    Passenger *temp = (Passenger *) malloc(sizeof(Passenger) * n);
    if (temp) {
        merge_sort_rec(arr, 0, n - 1, temp, cmp);
        free(temp);
    }
}

void quick_sort_rec(Passenger *arr, int left, int right, passenger_cmp cmp) {
    while (left < right) {
        int i = left, j = right;
        Passenger pivot = arr[left + (right - left) / 2];

        while (i <= j) {
            while (cmp(&arr[i], &pivot) < 0) i++;
            while (cmp(&arr[j], &pivot) > 0) j--;
            if (i <= j) {
                Passenger temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }

        if (j - left < right - i) {
            quick_sort_rec(arr, left, j, cmp);
            left = i;
        } else {
            quick_sort_rec(arr, i, right, cmp);
            right = j;
        }
    }
}

void quick_sort(Passenger *arr, int n, passenger_cmp cmp) {
    quick_sort_rec(arr, 0, n - 1, cmp);
}

void shuffle_arr(Passenger *arr, int n) {
    Passenger temp;
    for (int i = 0; i < n; ++i) {
        int index = rand() % n;
        temp = arr[i];
        arr[index] = arr[i];
        arr[i] = temp;
    }
}
