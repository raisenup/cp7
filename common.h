#pragma once

typedef unsigned short ushort;

#define RESET       "\033[0m"
#define YELLOW      "\033[33m"
#define CYAN        "\033[36m"

double f1(const double x, const double y);

double f1_derivative(const double x, const double y);

double f2(const double x, const double y);

double f2_derivative(const double x, const double y);

double bisection(double (*f)(double, double), double a, double b, const double y, const double eps);

double newton(double (*f)(double, double), double (*df)(double, double), const double x0, const double y, const double eps);

void solve_equation(const ushort method_num, double (*f)(double, double), double (*df)(double, double),
                      const double a, const double b, const double y, const double epsilon);
