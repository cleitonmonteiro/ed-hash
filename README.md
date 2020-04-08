# Hash functions implementation in C

## Running simple tests
```sh
gcc -o hash.o -c ./lib/_hash.c && gcc -o main main.c hash.o && ./main
```

## Generating reports
```sh
cd reports
gcc -o hash.o -c ../lib/_hash.c && gcc -o report report_div.c hash.o && ./report
gcc -o hash.o -c ../lib/_hash.c && gcc -o report report_fold_method.c hash.o && ./report
gcc -o hash.o -c ../lib/_hash.c && gcc -o report report_half_square.c hash.o && ./report
gcc -o hash.o -c ../lib/_hash.c && gcc -o report report_digit_analysis_v1.c hash.o && ./report
gcc -o hash.o -c ../lib/_hash.c && gcc -o report report_digit_analysis_v2.c hash.o && ./report
```

## Results with table size = 100000

| Hash Method | Number of keys | Collisions |
| :-------------     |:-------------:| -----:|
| Division          | 200000  | 145173 |
| Fold Method       | 200000  | 145211 |
| Half Square       | 200000  | 185966 |
| Digit Analysis v1 | 200000  | ? |
| Digit Analysis v2 | 200000  | ? |
| Division          | 400000  | 484977 |
| Fold Method       | 400000  | 485081 |
| Half Square       | 400000  | 569422 |
| Digit Analysis v1 | 400000  | ? |
| Digit Analysis v2 | 400000  | ? |
| Division          | 600000  | 1023040 |
| Fold Method       | 600000  | 1023122 |
| Half Square       | 600000  | 1151969 |
| Digit Analysis v1 | 600000  | ? |
| Digit Analysis v2 | 600000  | ? |
| Division          | 800000  | 1760201 |
| Fold Method       | 800000  | 1760277 |
| Half Square       | 800000  | 1934064 |
| Digit Analysis v1 | 800000  | ? |
| Digit Analysis v2 | 800000  | ? |
| Division          | 1000000  | 2696847 |
| Fold Method       | 1000000  | 2696921 |
| Half Square       | 1000000  | 2915873 |
| Digit Analysis v1 | 1000000  | ? |
| Digit Analysis v2 | 1000000  | ? |

