#include <iostream>
#include <fstream>

using namespace std;

long long int sqrt(long long int x)
{
    for (long long int i = 1; i < x; i++)
    {
        if ((i * i) >= x)
        {
            return i;
        }
    }
    return 0;
}

int main()
{
    long int n;
    cin >> n;
    long long int summa = (n + 1) * n / 4;

    ofstream file("output.txt");

    if (n % 4 == 0 || n % 4 == 3)
    {
        file << "YES" << endl;

        long int i = (2 + sqrt(1 + 2 * n + 2 * n * n)) / 2, l = n + 1 - i, extension = 0;

        if (((i + n) * (n + 1 - i) / 2) != summa)
        {
            l += 1;
            extension = summa - ((i + n) * (n + 1 - i) / 2);
        }

        file << l << endl;

        if (extension != 0)
        {
            file << extension << " ";
        }

        for (long long int j = i; j <= n; j++)
        {
            file << j << " ";
        }

        file << endl;
        file << n - l << endl;

        for(long long int k = 1; k < i; k ++)
        {
            if(k != extension)
            {
                file << k << " ";
            }
        }

        file << endl;

    }
    else
    {
        file << "NO" << endl;
    }
    file.close();
    return 0;
}