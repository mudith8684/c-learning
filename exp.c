#include <stdio.h>

typedef long long real_t;

real_t power (real_t base, real_t n);

int main (void) {
    real_t base, n, p;
    printf("Enter base: ");
    scanf("%lld", &base);
    printf("Enter exponent: ");
    scanf("%lld", &n);
    p = power (base, n);
    printf("The result is: %lld\n", p);
    return 0;
}

real_t power (real_t base, real_t n) {
    real_t p = 1;
    for (int i = 1; i <= n; i++) {
        p *= base;
    }
    return p;
}
