#ifndef INPUT
#define INPUT

typedef int (*double_validator_func)(const double);
typedef int (*int_validator_func)(const int);
typedef int (*char_validator_func)(const char);

int isWhiteSpace(int c);

int isInputValid();

void clearInputBuffer();

void input_double(double *value, const char* mes, const char* error, double_validator_func validator);

void input_int(int *value, const char* mes, const char* error, int_validator_func validator);

void input_char(char *value, const char* mes, const char* error, char_validator_func validator);

#endif