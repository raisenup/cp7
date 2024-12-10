#include "common.h"
#include <stdio.h>
#include <math.h>

#define STEP 1e-6
#define MAX_ITER 1e9

double f1(const double x, const double y) {
    return cos(y/x)-2.0*sin(1.0/x)+1.0/x;
}

double f1_derivative(const double x, const double y) {
    return (y*sin(y/x)+2*cos(1/x)-1)/(x*x);
}

double f2(const double x, const double y) {
    return sin(log(x))-cos(log(x))+y*log(x);
}

double f2_derivative(const double x, const double y) {
    return (cos(log(x))+sin(log(x))+y)/x;
}

double bisection(double (*f)(double, double), double a, double b, const double y, const double eps) {
    double fa = f(a,y);
    double mid = 0;
    do {
        mid = (a + b) / 2.0;
        double fmid = f(mid,y);

        if (fa * fmid < 0) {
            b = mid;
        } else {
            a = mid;
            fa = fmid;
        }
    } while (fabs(b - a) > eps);
    return mid;
}

double newton(double (*f)(double, double), double (*df)(double, double), const double x0, const double y, const double eps) {
    double x = x0;
    for (int iter = 0; iter < MAX_ITER; iter++) {
        const double fx = f(x, y);
        const double fx_prime = df(x, y);
        const double x_new = x - fx / fx_prime;
        if (fabs(x_new - x) < eps) {
            return x_new;
        }
        x = x_new;
    }
    printf("Newton's method did not converge for x0 = %.15lf\n", x0);
    return NAN;
}

void solve_equation(const ushort method_num, double (*f)(double, double), double (*df)(double, double),
                      const double a, const double b, const double y, const double epsilon) {
    const ushort precision = (int)-log10(epsilon);
    switch (method_num) {
        case 1: {
            double x1 = a;
            double x2 = a + STEP;
            printf(CYAN"\nRoots found in [%.*lf, %.*lf] :\n"RESET, precision, a, precision, b);
            ushort i = 1;
            printf(YELLOW);
            while (x2 <= b) {
                const double fa = f(x1, y);
                const double fb = f(x2, y);

                if (fa * fb < 0) {
                    double root = bisection(f, x1, x2, y, epsilon);
                    if (!isnan(root)) {
                        printf("x%d = %.*lf\n", i++, precision, root);
                    }
                }
                x1 = x2;
                x2 += STEP;
            }
            printf(RESET);
        } break;
        case 2: {
            double roots[100];
            ushort root_count = 0;
            printf(CYAN"\nRoot found in [%.*lf, %.*lf] :\n"RESET, precision, a, precision, b);
            ushort i = 1;
            for (double x = a; x < b; x += STEP) {
                const double x1 = x, x2 = x + STEP;
                if (f(x1, y) * f(x2, y) < 0) {
                    const double x0 = (x1 + x2) / 2.0;
                    double root = newton(f, df, x0, y, epsilon);
                    if (!isnan(root)) {
                        ushort duplicate = 0;
                        for (int j = 0; j < root_count; j++) {
                            if (fabs(root - roots[j]) < epsilon) {
                                duplicate = 1;
                                break;
                            }
                        }
                        if (!duplicate) {
                            roots[root_count++] = root;
                            printf(YELLOW"x%d = %.*lf\n"RESET, i++, precision, root);
                        }
                    }
                }
            }
        } break;
        default: {
            printf("Invalid method number: %d\n", method_num);
        } break;
    }
}