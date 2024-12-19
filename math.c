#include <stdio.h>
#include <stdlib.h>

// Function for exponentiation (integer and float)
long double power(long double base, long double exp) {
    long double result = 1.0;
    while (exp > 0) {
        result *= base;
        exp--;
    }
    return result;
}

void print_usage() {
    printf("Usage: math [FLAGS]... <num1> <num2>\n");
    printf("Flags:\n");
    printf("  -a: add\n");
    printf("  -s: subtract\n");
    printf("  -m: multiply\n");
    printf("  -d: divide\n");
    printf("  -r: remainder\n");
    printf("  -f: enable float\n");
    printf("  -A: bitwise and\n");
    printf("  -O: bitwise or\n");
    printf("  -N: bitwise not\n");
    printf("  -X: bitwise xor\n");
    printf("  -e: exponentiation\n");
}

long double remainder_double(long double x, long double y) {
    return x - (long long int)(x / y) * y;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        print_usage();
        return 1;
    }

    int enable_float = 0;
    long long int num1_int, num2_int;
    long double num1, num2;
    int flags = 0;  // AONXfdrmas flags
    char *endptr;

    // Parse flags
    int i = 1;
    while (i < argc && argv[i][0] == '-') {
        for (int j = 1; argv[i][j] != '\0'; j++) {
            switch (argv[i][j]) {
                case 'f': enable_float = 1; break;
                case 'a': flags |= 1 << 0; break;
                case 's': flags |= 1 << 1; break;
                case 'm': flags |= 1 << 2; break;
                case 'd': flags |= 1 << 3; break;
                case 'r': flags |= 1 << 4; break;
                case 'A': flags |= 1 << 5; break;
                case 'O': flags |= 1 << 6; break;
                case 'N': flags |= 1 << 7; break;
                case 'X': flags |= 1 << 8; break;
                case 'e': flags |= 1 << 9; break;
                default:
                    print_usage();
                    return 1;
            }
        }
        i++;
    }

    // Get numbers
    if (enable_float) {
        num1 = strtold(argv[i], &endptr);  // Use strtold for long double
        if (*endptr != '\0') {
            print_usage();
            return 1;
        }
        num2 = strtold(argv[i + 1], &endptr);
        if (*endptr != '\0') {
            print_usage();
            return 1;
        }
    } else {
        num1_int = strtoll(argv[i], &endptr, 10);  // Provide a base (10 for decimal) to strtoll
        if (*endptr != '\0') {
            print_usage();
            return 1;
        }
        num2_int = strtoll(argv[i + 1], &endptr, 10);  // Provide a base (10 for decimal) to strtoll
        if (*endptr != '\0') {
            print_usage();
            return 1;
        }
    }

    // Apply flags in the order they appear
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j] != '\0'; j++) {
                switch (argv[i][j]) {
                    case 'a': // -a: add
                        if (enable_float) {
                            printf("%Lf\n", num1 + num2);
                        } else {
                            printf("%lld\n", num1_int + num2_int);
                        }
                        break;
                    case 's': // -s: subtract
                        if (enable_float) {
                            printf("%Lf\n", num1 - num2);
                        } else {
                            printf("%lld\n", num1_int - num2_int);
                        }
                        break;
                    case 'm': // -m: multiply
                        if (enable_float) {
                            printf("%Lf\n", num1 * num2);
                        } else {
                            printf("%lld\n", num1_int * num2_int);
                        }
                        break;
                    case 'd': // -d: divide
                        if (num2 != 0) {
                            if (enable_float) {
                                printf("%Lf\n", num1 / num2);
                            } else {
                                printf("%lld\n", num1_int / num2_int);
                            }
                        } else {
                            printf("Error: Division by zero\n");
                        }
                        break;
                    case 'r': // -r: remainder
                        if (num2 != 0) {
                            if (enable_float) {
                                printf("%Lf\n", remainder_double(num1, num2));
                            } else {
                                printf("%lld\n", num1_int % num2_int);
                            }
                        } else {
                            printf("Error: Division by zero\n");
                        }
                        break;
                    case 'A': // -A: bitwise and
                        if (!enable_float) {
                            printf("%lld\n", num1_int & num2_int);
                        }
                        break;
                    case 'O': // -O: bitwise or
                        if (!enable_float) {
                            printf("%lld\n", num1_int | num2_int);
                        }
                        break;
                    case 'N': // -N: bitwise not
                        if (!enable_float) {
                            printf("%lld\n", ~num1_int);
                            printf("%lld\n", ~num2_int);
                        }
                        break;
                    case 'X': // -X: bitwise xor
                        if (!enable_float) {
                            printf("%lld\n", num1_int ^ num2_int);
                        }
                        break;
                    case 'e': // -e: exponentiation
                        if (enable_float) {
                            printf("%Lf\n", power(num1, num2));
                        } else {
                            printf("%lld\n", (long long int)power(num1_int, num2_int));
                        }
                        break;
                    default:
                        print_usage();
                        return 1;
                }
            }
        }
    }

    return 0;
}
