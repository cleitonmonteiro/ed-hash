#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include "_hash.h"

void _print_arr(int *arr, int start, int size)
{
  printf("[ ");
  for (int c = start; c < start + size; c++)
  {
    printf("%i ", arr[c]);
  }
  printf("]");
}

void _print_arr_f(double *arr, int start, int size)
{
  printf("[ ");
  for (int c = start; c < start + size; c++)
  {
    printf("%.3f ", arr[c]);
  }
  printf("]");
}

int hash_div(int key, int table_size)
{
  int result = key % table_size;
  // printf("LOG: hash_div(%i, %i) = %i\n", key, table_size, result);
  return result;
}

int *int_to_arr(int number, int number_digits)
{
  int *arr = calloc(number_digits, sizeof(int));
  int temp_number = number;

  for (int c = number_digits - 1; c >= 0; c--)
  {
    arr[c] = temp_number % 10;
    temp_number /= 10;
  }

  // printf("LOG: int_to_arr(%i, %i) = ", number, number_digits);
  // _print_arr(arr, 0, number_digits);
  // printf("\n");
  return arr;
}

int arr_to_int(int *arr, int arr_size, int last_count)
{
  int number = 0;
  int last_count_temp = last_count;
  int index = arr_size - 1;
  int expo = 0;

  while (last_count >= 1)
  {
    number += arr[index] * pow(10, expo);
    index--;
    last_count--;
    expo++;
  }

  // printf("LOG: arr_to_int(");
  // _print_arr(arr, 0, arr_size);
  // printf(", %i, %i) = %i\n", arr_size, last_count_temp, number);
  return number;
}

int _or(int a, int b)
{
  int result = a | b;
  // printf("LOG: _or(%i, %i) = %i\n", a, b, result);
  return result;
}

int _and(int a, int b)
{
  int result = a & b;
  // printf("LOG: _and(%i, %i) = %i\n", a, b, result);
  return result;
}

int _xor(int a, int b)
{
  int result = a ^ b;
  // printf("LOG: _xor(%i, %i) = %i\n", a, b, result);
  return result;
}

int _add(int a, int b)
{
  int result = (a + b) % 10;
  // printf("LOG: _add(%i, %i) = %i\n", a, b, result);
  return result;
}

int hash_fold_method(int bin_key, int table_size, int (*operation)(int, int))
{
  int number_digits_key = log10(bin_key) + 1;
  int *arr_key = int_to_arr(bin_key, number_digits_key);
  int count = (number_digits_key / table_size) - 1;

  if (count < 0)
    return bin_key;

  int base_index = table_size;

  for (int c = 0; c < count; c++)
  {
    arr_key[base_index] = operation(arr_key[base_index], arr_key[base_index - 1]);
    arr_key[base_index + 1] = operation(arr_key[base_index + 1], arr_key[base_index - table_size]);
    base_index += table_size;
  }

  int result = arr_to_int(arr_key, number_digits_key, table_size);

  // printf("LOG: hash_fold_method(%i, %i) = %i\n", bin_key, table_size, result);
  return result;
}

int hash_half_square(int key, int table_size)
{
  int key_double = key * key;
  int number_digits_result = log10(table_size);
  int number_digits_key = log10(key_double) + 1;

  // printf("LOG: hash_half_square: key_double %i\n", key_double);
  // printf("LOG: hash_half_square: number_digits_key %i\n", number_digits_key);
  // printf("LOG: hash_half_square: number_digits_result %i\n", number_digits_result);

  if (number_digits_key <= number_digits_result) {
    // printf("LOG: hash_half_square(%i, %i) = %i\n", key, table_size, key);
    return key;
  }

  int difference = number_digits_key - number_digits_result;
  int excess = difference / 2;

  int result = 0;
  int pot = 10;
  while (number_digits_result > 0)
  {
    excess--;
    if (excess > 0)
      continue;
    int number = (key_double % 10) * pot;
    result += number;
    key_double /= 10;
    number_digits_result--;
  }

  // printf("LOG: hash_half_square(%i, %i) = %i\n", key, table_size, result);
  return result;
}

double deviation_v1(int *arr_freq, int number_keys)
{
  double result = 0;

  for (int c = 0; c < 10; c++)
  {
    double partial = pow((double)arr_freq[c] - (double)number_keys / 10, 2);
    result += partial;
  }

  // printf("LOG: deviation_v1(");
  // _print_arr(arr_freq, 0, 10);
  // printf(", %i) = %f\n", number_keys, result);
  return result;
}

double deviation_v2(int *arr_freq, int number_keys)
{
  double result = 0;

  for (int c = 0; c < 10; c++)
  {
    double partial = fabs((double)arr_freq[c] - (double)number_keys / 10);
    result += partial;
  }

  // printf("LOG: deviation_v2(");
  // _print_arr(arr_freq, 0, 10);
  // printf(", %i) = %f\n", number_keys, result);
  return result;
}

typedef struct node
{
  int index;
  double value;
} node_t;

typedef struct node node_t;

node_t *make_nodes(int size)
{
  node_t *nodes;
  nodes = calloc(size, sizeof(node_t));
  return nodes;
}

node_t *make_nodes_from_arr(double *arr, int size)
{
  node_t *nodes;
  nodes = calloc(size, sizeof(node_t));
  // printf("LOG: make_nodes_from_arr(");
  // _print_arr_f(arr, 0, size);
  // printf(", %i) = [ ", size);
  for (int c = 0; c < size; c++)
  {
    nodes[c].index = c;
    nodes[c].value = arr[c];
    // printf("(%i, %f), ", c, arr[c]);
  }
  // printf("]\n");
  return nodes;
}

void _print_nodes(node_t *nodes, int start, int size)
{
  printf("[ ");
  for (int c = start; c < start + size; c++)
  {
    printf("(%i, %.3f) ", nodes[c].index, nodes[c].value);
  }
  printf("]");
}

void merge(node_t *nodes, int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  /* create temp arrays */
  node_t *L = make_nodes(n1);
  node_t *R = make_nodes(n2);

  /* Copy data to temp arrays L[] and R[] */
  for (i = 0; i < n1; i++)
    L[i] = nodes[l + i];
  for (j = 0; j < n2; j++)
    R[j] = nodes[m + 1 + j];

  /* Merge the temp arrays back into arr[l..r]*/
  i = 0; // Initial index of first subarray
  j = 0; // Initial index of second subarray
  k = l; // Initial index of merged subarray
  while (i < n1 && j < n2)
  {
    if (L[i].value <= R[j].value)
    {
      nodes[k] = L[i];
      i++;
    }
    else
    {
      nodes[k] = R[j];
      j++;
    }
    k++;
  }

  /* Copy the remaining elements of L[], if there 
       are any */
  while (i < n1)
  {
    nodes[k] = L[i];
    i++;
    k++;
  }

  /* Copy the remaining elements of R[], if there 
       are any */
  while (j < n2)
  {
    nodes[k] = R[j];
    j++;
    k++;
  }
}

/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void merge_sort(node_t *nodes, int l, int r, int root)
{
  if (root)
  {
    // printf("LOG: merge_sort( ");
    // _print_nodes(nodes, 0, r + 1);
  }

  if (l < r)
  {
    // Same as (l+r)/2, but avoids overflow for
    // large l and h
    int m = l + (r - l) / 2;

    // Sort first and second halves
    merge_sort(nodes, l, m, 0);
    merge_sort(nodes, m + 1, r, 0);

    merge(nodes, l, m, r);
  }

  if (root)
  {
    // printf(" ) = ");
    // _print_nodes(nodes, 0, r + 1);
    // printf("\n");
  }
}

int get_key_from_sorted_deviatons(node_t *nodes, int size, int key, int qtd)
{
  int *arr = calloc(qtd, sizeof(int));
  for (int c = 0; c < qtd; c++)
  {
    int digit_index = nodes[c].index;
    int digit = key / (int)pow(10, digit_index) % 10;
    arr[c] = digit;
  }
  int result = arr_to_int(arr, qtd, qtd);

  // printf("LOG: get_key_from_sorted_deviatons(");
  // _print_nodes(nodes, 0, size);
  // printf(", %i, %i, %i) = %i\n", size, key, qtd, result);
  return result;
}

int hash_digit_analysis(int key, int table_size, int number_digits_key, int *arr, int arr_size, double (*deviation_func)(int *, int))
{
  // printf("LOG: hash_digit_analysis(%i, %i, %i\n", key, table_size, number_digits_key);
  int max_number_digits = log10(table_size);
  double *deviation_arr = calloc(max_number_digits, sizeof(double));
  int *digit_freq;

  for (int digit_index = 0; digit_index < max_number_digits; digit_index++)
  {
    digit_freq = calloc(10, sizeof(int));
    for (int c = 0; c < arr_size; c++)
    {
      int digit = arr[c] / (int)pow(10, digit_index) % 10;
      digit_freq[digit]++;
    }
    deviation_arr[digit_index] = deviation_func(digit_freq, arr_size);
    free(digit_freq);
  }

  node_t *nodes = make_nodes_from_arr(deviation_arr, max_number_digits);

  merge_sort(nodes, 0, max_number_digits - 1, 1);

  int result = get_key_from_sorted_deviatons(nodes, max_number_digits, key, number_digits_key);
  // printf("LOG: hash_digit_analysis(%i, %i, ", key, number_digits_key);
  // _print_arr(arr, 0, arr_size);
  // printf(", %i) = %i\n", arr_size, result);

  // free(digit_freq);
  // free(deviation_arr);
  return result;
}
