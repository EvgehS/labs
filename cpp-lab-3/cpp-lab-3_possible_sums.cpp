#include <iostream>

using namespace std;

int main()
{
    int n;
    long long int summa = 0, target, digit, res = 0;
    cin >> n;

    long long int arr[n] = {};
    
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
        summa += arr[i];
    }
    target = summa / 2;

    long long int possible_sums[target + 1] = {};
    for(int i = 0; i < n; i++)
    {
        digit = arr[i];
        for(int index = target - digit; index >= 0; index--)
        {
            if(possible_sums[index] == 1)
            {
                possible_sums[index + digit] = 1;
                res = max(res, index + digit);
            }
        }
        if(digit <= target){
            possible_sums[digit] = 1;
            res = max(res, digit);
        }
    }
    cout << 2 * (target - res) + summa % 2 << endl;
    return 0;
}