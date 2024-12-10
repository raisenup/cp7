#include <stdio.h>
#include <conio.h>

#include "common.h"

#define MAX_E 1e-2
#define MIN_E 1e-15

int main(void) {

    printf("This program calculates roots of nonlinear equations on a given interval.\n");

    do {
        ushort eq_num = 0;
        printf(CYAN"Equations:\n1. cos(y/x)-2*sin(1/x)+(1/x) = 0\n2. sin(ln(x))-cos(ln(x))+y*ln(x) = 0\n"RESET);
        do {
            printf("Enter number of the equation: ");
            if(scanf("%hu", &eq_num) != 1 || eq_num != 1 && eq_num != 2) {
                printf("Error: wrong input.\n");
            }
            fflush(stdin);
        } while (eq_num != 1 && eq_num != 2);

        double a = 0, b = 0;
        do {
            printf("Enter the interval [a,b]: ");
            if(scanf("%lf %lf", &a, &b) != 2) {
                printf("Error: wrong input.\n");
            } else if (a >= b) {
                printf("Error: a is greater or equal to b.\n");
            } else if (a == 0) {
                printf("Error: a cannot be equal to 0.\n");
            }
            fflush(stdin);
        } while (a >= b || a == 0);

        double y = 0;
        ushort y_input = 0;
        do {
            printf("Enter the value of parameter y: ");
            y_input = scanf("%lf", &y);
            if(y_input != 1) {
                printf("Error: wrong input.\n");
            }
            fflush(stdin);
        } while (y_input != 1);

        ushort method_num = 0;
        printf(CYAN"Methods:\n1. Bisection Method\n2. Newton's Method\n"RESET);
        do {
            printf("Enter number of the method: ");
            if(scanf("%hu", &method_num) != 1 || method_num != 1 && method_num != 2) {
                printf("Error: wrong input.\n");
            }
            fflush(stdin);
        } while (method_num != 1 && method_num != 2);

        double epsilon = 0.0;
        do {
            printf("Enter precision in exponential form [%.0e, %.0e]: ", MIN_E, MAX_E);
            if(scanf("%lf", &epsilon) != 1) {
                printf("Error: wrong input.\n");
            } else if (epsilon > MAX_E || epsilon < MIN_E) {
                printf("Error: precision is not in range.\n");
            }
            fflush(stdin);
        } while (epsilon > MAX_E || epsilon < MIN_E);

        switch (eq_num) {
            case 1:
                solve_equation(method_num, f1, f1_derivative, a, b, y, epsilon);
                break;
            case 2:
                solve_equation(method_num, f2, f2_derivative, a, b, y, epsilon);
                break;
            default:
                printf("Error: there is not such equation.\n");
                break;
        }

        printf("\nPress ENTER to restart, or any other key to exit.\n");
    } while (getch() == 13);

    return 0;
}
