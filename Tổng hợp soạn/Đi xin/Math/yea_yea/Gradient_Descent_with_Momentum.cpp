#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

double fastpow(double n, ll m) {
    if (m == 0)
        return 1;
    double tmp = fastpow(n, m/2);
    if (m & 1)
        return tmp*tmp*n;
    else
        return tmp*tmp;
}

double function1(double x) {
    return 2 * exp(fastpow(x, 5) - fastpow(x, 3)) - 5 * fastpow(x, 3) - x + log(x + 45) + 20;
}

double gradient1(double x) {
    return 2 * exp(fastpow(x, 5) - fastpow(x, 3)) * fastpow(x, 2) * (5 * fastpow(x, 2) - 3) - 15 * x * x - 1 + 1 / (x + 45);
}

double function2(double x) {
    return 3*exp(fastpow(x, 5) - fastpow(x, 4)) + fastpow(x, 2) - 20*x + log(x + 25) - 10;
}

double gradient2(double x) { // derivative of loss function
    return 3*exp(fastpow(x, 5) - fastpow(x, 4))*(5*fastpow(x, 4) - 4*fastpow(x, 3)) + 2*x - 20 + 1/(x+25);
}


double gradientDescentWithMomentum(double (*function)(double), double (*gradient)(double), double learning_rate, double momentum, int N, double epsilon, double velocity = 0.0, double x = 0.0) {
    int i = 0;
    
    while (i < N) {
        double x_old = x;
        double grad = gradient(x_old);
        velocity = momentum * velocity - learning_rate * grad;
        x = x_old + velocity;
        if (fabs(x - x_old) < epsilon)
            break;
        i++;
    }
    return x;
}

int main() {
    double learning_rate = 0.001;
    double momentum = 0.9;
    int N = 1000000;
    double epsilon = 1e-7;

    // f(x) = 2e^(x^5 - x^3) - 5x^3 - x + ln(x + 45) + 20
    // f'(x) = 2e^(x^5 - x^3)*(5x^4 - 3x^2) - 15x^2 + 1 + 1/(x+45)

    // g(x) = 3e^(x^5 - x^4) + x^2 - 20x + ln(x + 25) - 10
    // g'(x) = 3e^(x^5 - x^4)*(5x^4 - 4x^3) + 2x - 20 + 1/(x+25)

    cout << "Minimum value of the function f(x): " << function1(gradientDescentWithMomentum(function1, gradient1, learning_rate, momentum, N, epsilon)) << endl;
    cout << "Minimum value of the function g(x): " << function2(gradientDescentWithMomentum(function2, gradient2, learning_rate, momentum, N, epsilon)) << endl;

    return 0;
}
