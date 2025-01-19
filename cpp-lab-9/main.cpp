#include <iostream>


bool is_positive(int value) {
    return value > 0;
}

bool is_even(int value) {
    return value % 2 == 0;
}


template<typename T, typename condition_type>
size_t count_if(const T* array, size_t size, condition_type condition)
{
    size_t count = 0;
    for(size_t i = 0; i < size; ++i)
    {
        if(condition(array[i]))
        {
            count ++;
        }
    }
    return count;
}

int main() {

    int int_array[] = {1, -2, 3, 4, -5, 6};
    size_t int_size = 6;

    size_t positive_count = count_if(int_array, int_size, is_positive);
    std::cout << "Count of positive numbers: " << positive_count << std::endl;

    size_t even_count = count_if(int_array, int_size, is_even);
    std::cout << "Count of even numbers: " << even_count << std::endl;

    double double_array[] = {1.5, -2.3, 3.0, 4.7, -5.1};
    size_t double_size = 5;

    size_t greater_than_two = count_if(double_array, double_size, [](double value) {
        return value > 2.0;
    });
    std::cout << "Count of numbers greater than 2: " << greater_than_two << std::endl;

    return 0;
}