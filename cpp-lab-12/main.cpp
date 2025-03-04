#include <iostream>
#include <list>

template <typename Iterator, typename func>
class transform_iterator
{
private:
    Iterator current;
    func transform;

public:
    transform_iterator(Iterator p, func function)
        : current(p), transform(function) {}

    auto operator*()
    {
        return transform(*current);
    }

    transform_iterator &operator++()
    {
        ++current;
        return *this;
    }

    bool operator!=(const transform_iterator &other) const
    {
        return current != other.current;
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

int main()
{
    double rubles[] = {100, 500, 1000, 5000};
    size_t size_1 = sizeof(rubles) / sizeof(rubles[0]);

    std::list<std::string> dates = {"01.02.2025", "05.07.2007", "09.02.2006"};

    transform_iterator<double*, double (*)(double)> begin(rubles, rub_to_usd);
    transform_iterator<double*, double (*)(double)> end(rubles + size_1, rub_to_usd);

    std::cout << "Конвертированные суммы (RUB -> USD):\n";
    for (auto it = begin; it != end; ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    transform_iterator<std::list<std::string>::iterator, std::string (*)(const std::string&)> begin_1(dates.begin(), transform_date);
    transform_iterator<std::list<std::string>::iterator, std::string (*)(const std::string&)> end_1(dates.end(), transform_date);

    std::cout << "Конвертированные даты:\n";
    for (auto it = begin_1; it != end_1; ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}