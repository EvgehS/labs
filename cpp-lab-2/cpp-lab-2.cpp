#include <iostream>
#include <iomanip>

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

long double t(long double x)
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

long double f(long double y)
{
    return (7 * t(0.25) + 2 * t(1 + y)) / (6 - t(in_degree(y, 2) - 1));
}
int main()
{
    long double y;
    int x = 32;
    cin >> y;
    cout.width(4);
    cout << x << endl;
    cout << x << endl;
    cout << x << endl;
    cout << fixed << setprecision(13)  << f(y) << endl;
    cout << f(y) << endl;
    return 0;

}
