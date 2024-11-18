// bisection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include <optional>
#include <functional>

inline bool diff_sign(double x, double y) {
    return x > 0 ? y < 0 : y > 0;
}

std::optional<double> bisection(std::function<double(double)> f, double x0 = 0, double x1 = 1, double tol = 1e-5) {
    double f0 = f(x0), f1 = f(x1);
    double av, f_av;
    if (!diff_sign(f0, f1)) return {};

    while (x1 - x0 > tol) {
        av = (x1 + x0) / 2;
        f_av = f(av);
        if (diff_sign(f0, f_av)) {
            x1 = av;
            f1 = f_av;
        }
        else {
            x0 = av;
            f0 = f_av;
        }
    }

    return (x1 + x0)/2;
}

double sin_exp(double x) {
    return sin(exp(x));
}

int main()
{
    std::cout << "f(x) = sin(e^x)\nLooking for zero in (a, b)\n";
    std::cout << std::setprecision(8) << std::scientific;

    std::cout << "a = 0, b = 1, tol = 1e-5\n";
    if (auto x = bisection(sin_exp))
        std::cout << x.value() << "\n";
    else
        std::cout << "Error! Can't find zero of the function\n";
    
    std::cout << "a = 1, b = 1.5, tol = 1e-5\n";
    if (auto x = bisection(sin_exp, 1, 1.5))
        std::cout << x.value() << "\n";
    else
        std::cout << "Error! Can't find zero of the function\n";
    
    std::cout << "a = 1, b = 1.5, tol = 1e-8\n";
    if (auto x = bisection(sin_exp, 1, 1.5, 1e-8))
        std::cout << x.value() << "\n";
    else
        std::cout << "Error! Can't find zero of the function\n";
}
