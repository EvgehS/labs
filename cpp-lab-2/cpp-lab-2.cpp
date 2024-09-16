#include <iostream>

using namespace std;

double in_degree(double digit, int degree)
{
    double ans = 1;
    for(int i = 0; i < degree; i++)
    {
        ans *= digit;
    }
    return ans;
}

double double_factorial(int digit)
{
    long long int ans = 1;
    for(digit; digit > 0; digit -= 2)
    {
        ans *= digit;
    }
    return ans;
}

double t(double x)
{
    int k;
    double sum_1 = 0, sum_2 = 0;
    for(k = 0; k <= 10; k++)
    {
        sum_1 += in_degree(x, 2 * k + 1) / double_factorial(2 * k + 1);
    }
    cout << sum_1 << endl;
    for(k = 0; k <= 10; k++)
    {
        sum_2 += in_degree(x, 2 * k) / double_factorial(2 * k);
    }
    cout << sum_2 << endl;
    return sum_1 / sum_2;
}

double f(double y)
{
    return (7 * t(0.25) + 2 * t(1 + y)) / (6 - t(in_degree(y, 2) - 1));
}
int main()
{
    double y;
    cin >> y;
    cout << f(y) << endl;
    return 0;

}
