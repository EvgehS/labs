#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;

void merge(long long *arr, long long left, long long mid, long long right)
{
    long long n1 = mid - left + 1;
    long long n2 = right - mid;

    long long *L = new long long[n1];
    long long *R = new long long[n2];

    for (long long i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (long long j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    long long i = 0;
    long long j = 0;
    long long k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(long long *arr, long long left, long long right)
{
    if (left < right)
    {
        long long mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}
void fill_sums_array(long long int *arr, long long int size, long long int *weights_array)
{
    for (long long int mask = 0; mask < (1 << size); ++mask)
    {
        long long sum = 0;
        for (long long int i = 0; i < size; ++i)
        {
            if (mask & (1 << i))
            {
                sum += weights_array[i];
            }
        }
        arr[mask] = sum;
    }
}

long long binarySearch(long long int *arr, long long int size, long long int target)
{
    int left = 0, right = size - 1;
    int result = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] <= target)
        {
            result = arr[mid];
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return target - result;
}

long long solve(int n, long long int *values)
{
    long long total_sum = 0;
    long long left[n / 2], right[n/2 + n % 2];

        for (int i = 0; i < n / 2; ++i)
    {
        left[i] = values[i];
        total_sum += left[i];
    }

    for (int i = 0; i < (n / 2 + n % 2); ++i)
    {
        right[i] = values[n / 2 + i];
        total_sum += right[i];
    }

    long long int leftSums[1 << n / 2], rightSums[1 << (n / 2 + n % 2)];
    long long min_diff = total_sum;
    long long target = total_sum / 2;

    fill_sums_array(leftSums, n / 2, left);
    fill_sums_array(rightSums, n / 2 + n % 2, right);

    mergeSort(rightSums, 0, (1 << n / 2 + n % 2) - 1);

    for (long long left_sum : leftSums)
    {
        if (left_sum <= target)
            min_diff = min(min_diff, 2 * binarySearch(rightSums, 1 << (n / 2 + n % 2), target - left_sum) + total_sum % 2);
    }

    return min_diff;
}

void test(int n, long long *values, long long answer)
{
    auto start = chrono::high_resolution_clock::now();
    
    long long result = solve(n, values);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    if (result == answer)
    {
        cout << "Тест пройден за " << duration.count() << " секунды" << endl;
    }
    else
    {
        cout << "Тест не пройден, верный ответ: " << answer << ", ответ программы: " << result << endl;
    }
}

int main()
{
    ifstream file("testcases.txt");

    int n;
    while (file >> n)
    {
        long long *values = new long long[n];
        for (int i = 0; i < n; ++i)
            file >> values[i];

        long long expected_answer;
        file >> expected_answer;

        test(n, values, expected_answer);

        delete[] values;
    }

    file.close();
    return 0;
}