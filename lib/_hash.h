#ifndef _HASH_H_
#define _HASH_H_

int *int_to_arr(int number, int number_digits);
int _or(int a, int b);
int _and(int a, int b);
int _xor(int a, int b);
int _add(int a, int b);

void _print_arr(int *arr, int start, int size);

double deviation_v1(int *arr_freq, int number_keys);
double deviation_v2(int *arr_freq, int number_keys);

int hash_div(int key, int table_size);
int hash_fold_method(int bin_key, int table_size, int (*operation)(int, int));
int hash_half_square(int key, int table_size);
int hash_digit_analysis(int key, int table_size, int number_digits_key, int *arr, int arr_size, double(*deviation_func)(int*, int));

#endif
