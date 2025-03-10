#include <vector>
#include <iostream>
#include <algorithm>

template <typename Iterator, typename func>
class transform_iterator
{
private:
    Iterator current;
    func transform;

public:
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using pointer = typename std::iterator_traits<Iterator>::pointer;
    using reference = decltype(transform(*current));

    transform_iterator(Iterator p, func function)
        : current(p), transform(function) {}

    reference operator*() const
    {
        return transform(*current);
    }

    transform_iterator& operator++()
    {
        ++current;
        return *this;
    }

    transform_iterator operator++(int)
    {
        transform_iterator tmp = *this;
        ++current;
        return tmp;
    }

    difference_type operator-(const transform_iterator &other) const
    {
        return current - other.current;
    }

    bool operator!=(const transform_iterator &other) const
    {
        return current != other.current;
    }

    bool operator==(const transform_iterator &other) const
    {
        return current == other.current;
    }

};

double rub_to_usd(double rub)
{
    return rub / 100;
};

std::string transform_date(const std::string& str)
{
    int day = std::stoi(str.substr(0, 2));
    int month = std::stoi(str.substr(3, 2));
    int year = std::stoi(str.substr(8, 2));
    return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
}

int main() {
    std::vector<int> v = {400, 100, 300, 200};
    auto start = transform_iterator(v.begin(), rub_to_usd);
    auto end = transform_iterator(v.end(), rub_to_usd);

    auto result = std::find(start, end, 3.0);

    if (result != end) {
        std::cout << "Found: " << *result << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    return 0;
}