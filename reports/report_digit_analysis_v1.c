#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../lib/_hash.h"

void random_keys(int *arr_keys, int size, int limit)
{
  time_t t;
  srand((unsigned)time(&t));
  for (int c = 0; c < size; c++)
  {
    arr_keys[c] = abs((rand() + rand()) % limit);
  }
}

int main(int argc, char const *argv[])
{

  int index;
  int limit = 2000000000;
  int table_size = 100000;
  int *table, *keys;
  int collisions = 0;

  int ns[] = {200000, 400000, 600000, 800000, 1000000};
  int ns_size = 5;
  for (int i = 0; i < ns_size; i++)
  {
    int n = ns[i];
    table = calloc(table_size, sizeof(int));
    if (table == NULL)
    {
      printf("CANNOT ALLOC MEMORY: table\n");
    }

    keys = calloc(n, sizeof(int));
    if (keys == NULL)
    {
      printf("CANNOT ALLOC MEMORY: keys\n");
    }

    random_keys(keys, n, limit);
    for (int index_key = 0; index_key < n; index_key++)
    {
      index = hash_digit_analysis(keys[index_key], table_size, 5, keys, n, deviation_v1);
      if (table[index])
      {
        collisions++;
      }
      else
      {
        table[index] = keys[index_key];
      }
    }
    printf("DIGIT_ANALYSIS_V1,%d,%d\n", n, collisions);
    free(keys);
    free(table);
  }

  return 0;
}