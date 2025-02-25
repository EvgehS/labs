#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main() 
{
    std::vector<std::string> inventory;
    std::string item;
    int command;

    while (true) {
        std::cout << "Выберите команду:\n\t1. add\n\t2. remove\n\t3. list\n\t4. exit" << std::endl;
        std::cin >> command;

        if (command == 1) {
            std::cout << "Введите название предмета: ";
            std::cin >> item;
            std::back_insert_iterator<std::vector<std::string>> back = std::back_inserter(inventory);
            *back = item;
            std::cout << item << " добавлен в инвентарь.\n";
        }
        else if (command == 2) {
            std::cout << "Введите название предмета: ";
            std::cin >> item;
            std::vector<std::string>::iterator new_end = std::remove(inventory.begin(), inventory.end(), item);
            if (new_end != inventory.end()) {
                inventory.erase(new_end, inventory.end());
                std::cout << item << " удалён из инвентаря.\n";
            } else {
                std::cout << item << " не найден в инвентаре.\n";
            }
        }
        else if (command == 3) {
            std::cout << "Инвентарь: ";
            for (std::vector<std::string>::iterator i = inventory.begin(); i != inventory.end(); ++i)
                std::cout << *i << "; ";
            std::cout << "\n";
        }
        else if (command == 4) {
            break;
        }
        else {
            std::cout << "Неизвестная команда.\n";
        }
    }

    return 0;
}
