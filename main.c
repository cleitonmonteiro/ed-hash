#include <stdio.h>
#include <stdlib.h>
#include "./lib/_hash.h"

int main(int argc, char const *argv[])
{
  
  hash_div(90, 7); // 6

  hash_fold_method(101000, 2, _or); // 11
  hash_fold_method(101000, 2, _and); // 0
  hash_fold_method(111111, 2, _and); // 11
  hash_fold_method(111111, 2, _xor); // 11
  
  hash_fold_method(813459, 2, _add); // 11


  int arr[] = {44, 46, 49, 68, 71, 97};
  hash_digit_analysis(44, 100, 2, arr, 6, deviation_v2); // 44
  hash_digit_analysis(71, 100, 2, arr, 6, deviation_v2); // 17
  hash_digit_analysis(97, 100, 2, arr, 6, deviation_v2); // 97

  return 0;
}

// H(16) = 0000 0001 0000 0000 = 256 0001 0000 = 16 
// H(12) = 0000 0000 0110 0100 = 100 0000 1100 = 6