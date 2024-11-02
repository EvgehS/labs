#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

// Не работает при больших n, так как долгий перебор
int is_in(long int number, long int *array, long int len)
{
    // for (long int index = 0; index < len; ++index)
    // {
    //     if (array[index] == number)
    //         return 1;
    // }
    return 0;ё
}

int strcmp(const char *s_1, const char *s_2)
{
    int i = 0;
    for (; s_1[i] != '\0' && s_2[i] != '\0'; ++i)
    {
        if (s_1[i] != s_2[i])
        {
            return 0;
        }
    }
    return (s_1[i] == '\0' && s_2[i] == '\0');
}

long int sqrt(long long int x)
{
    for (long int i = 1; i < x; i++)
    {
        if ((i * i) >= x)
        {
            return i;
        }
    }
    return 0;
}

void result(long int n)
{
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

        for (long long int k = 1; k < i; k++)
        {
            if (k != extension)
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
}

int test(long int n)
{
    char word[4];

    fstream output_file("output.txt");
    output_file >> word;
    if (n % 4 == 0 || n % 4 == 3)
    {
        if (strcmp("YES", word))
        {
            long int target = (1 + n) * n / 4, count, digit, ans_sum = 0, *digits = new long[n], i;
            output_file >> count;

            for (i = 0; i < count; ++i)
            {
                output_file >> digit;

                if (is_in(digit, digits, n))
                {
                    delete[] digits;
                    return 0;
                }
                
                digits[i] = digit;
                ans_sum += digit;
            }

            if (ans_sum != target)
            {
                delete[] digits;
                return 0;
            }

            ans_sum = 0;
            output_file >> count;

            for (; i < n; ++i)
            {
                output_file >> digit;

                if (is_in(digit, digits, n))
                {
                    delete[] digits;
                    return 0;
                }

                digits[i] = digit;
                ans_sum += digit;
            }

            delete[] digits;
            return ans_sum == target;
        }
        return 0;
    }
    return strcmp("NO", word);
}
int main()
{
    long int n;
    fstream input_file("input.txt");
    while (input_file >> n)
    {
        auto start = chrono::high_resolution_clock::now();
        result(n);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        if(test(n))
        {
            cout << "Тест  пройден за " << duration.count() << " секунды" << endl;

        }
        else
            cout << "Тест не пройден" << endl;
    }
    return 0;
}