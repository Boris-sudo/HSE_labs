#include <stdio.h>
#include "file_operations.h"
#include "../libs/input.h"

#define FILENAME "C:\\Users\\boris\\ClionProjects\\HSE_labs\\lab-6\\passengers.dat"

typedef void (*MenuFunction)(const char*);

int choice_validator(int choice) {
    return choice >= 0 && choice <= 6;
}

int main() {
    setbuf(stdout, NULL);

    MenuFunction menu[] = {
            add_record,
            delete_record,
            search_records,
            edit_record,
            print_all,
            initialize_file
    };
    int choice;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Add an entry\n");
        printf("2. Delete an entry by number\n");
        printf("3. Record Search\n");
        printf("4. Edit an entry\n");
        printf("5. Output all entries\n");
        printf("6. Initialize file\n");
        printf("0. Exit\n");
        input_int(&choice, "Your choice: ", "Error, please try again.", choice_validator);

        if (choice >= 1 && choice <= 6)
            menu[choice-1](FILENAME);

        int x=1;
        while(x<1e5){x+=1;}
    } while (choice != 0);

    return 0;
}