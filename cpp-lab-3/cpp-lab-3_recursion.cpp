#include <iostream>

using namespace std;

int n;
long long int target;

long int maximum(long int num_1, long int num_2)
{
    if(num_1 > num_2)
    {
        return num_1;
    }
    return num_2;
}

long int find_diff(long int sum, long long int array[], int index)
{
    if(sum <= target)
    {
        long int res = sum;
        if(index == n - 1)
        {
            return res;
        }
        for(int index_1 = index; index_1 < n; index_1++)
        {

            res = maximum(res, find_diff(sum + array[index_1], array, index_1 + 1));
        }
        return res;
    }
    return 0;
}

int main()
{
    long long int summa = 0;
    cin >> n;

    long long int arr[n] = {};
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        summa += arr[i];
    }
    target = summa / 2;

    cout << "start" << endl;
    cout << 2 * (target - find_diff(0, arr, 0)) + summa % 2 << endl;
    return 0;
}

