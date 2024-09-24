#include <iostream>
#include <chrono>

using namespace std;

long double in_degree(long double digit, int degree)
{
    long double ans = 1;
    for(int i = 0; i < degree; i++)
    {
        ans *= digit;
    }
    return ans;
}

long int double_factorial(int digit)
{
    long int ans = 1;
    for(digit; digit > 0; digit -= 2)
    {
        ans *= digit;
    }
    return ans;
}

long double t(double x)
{
    int k;
    long double sum_1 = 0, sum_2 = 0;
    for(k = 0; k <= 10; k++)
    {
        sum_2 += in_degree(x, 2 * k) / double_factorial(2 * k);
        sum_1 += in_degree(x, 2 * k + 1) / double_factorial(2 * k + 1);
    }
    return sum_1 / sum_2;
}

double function(double y)
{
    return (7 * t(0.25) + 2 * t(1 + y)) / (6 - t(in_degree(y, 2) - 1));
}

void test(long double digit, double answer)
{
    auto start = chrono::high_resolution_clock::now();
    long double result = function(digit);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    if (abs(result - answer) < 3e-5)
    {
        cout << "Тест пройден за " << duration.count() << " миллисекунды" << endl;
    }
    else
    {
        cout << "Тест не пройден, ожидаемый ответ: " << answer << ", ваш ответ: " << result << endl;
    };
}
int main()
{
    test(5, -10.3181);
    test(5, -10.456);
    test(6, -1.62495);
    test(6, -2.62495);
    test(-100, 0.0192057);
    test(1000, -0.00200846);
    test(100000000000000000, -2e-17);
    return 0;
}
