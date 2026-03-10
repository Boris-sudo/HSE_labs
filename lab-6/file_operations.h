#ifndef HSE_FILE_OPERATIONS_H
#define HSE_FILE_OPERATIONS_H

void add_record(const char *filename);
void delete_record(const char *filename);
void search_records(const char *filename);
void edit_record(const char *filename);
void print_all(const char *filename);
void print_max(const char *filename);
void initialize_file(const char *filename);
void sort_file(const char *filename);
void add_random_records(const char *filename);
void print_size(const char *filename);

#endif
