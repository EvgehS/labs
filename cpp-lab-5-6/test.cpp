#include "transport.hpp"
#include <termios.h>
#include <unistd.h>
#include <typeinfo>

int main()
{
    std::cout << "          Аренда транспорта" << std::endl;
    std::cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
              << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠟⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠻⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
              << "⣿⣿⣿⣿⣿⣿⣿⣿⡿⢣⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡙⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
              << "⣿⣿⣿⣿⣿⣿⣿⡿⢡⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡘⣿⣿⣿⣿⣿⣿⣿⣿\n"
              << "⣿⣿⣿⠟⠉⠙⠿⢣⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡘⡟⠋⠉⢻⣿⣿⣿\n"
              << "⣿⣿⣿⣦⣤⣤⠄⠘⠛⠛⠛⠛⠛⠛⠛⠫⢭⣭⣭⣭⣭⣭⣭⠭⠝⠛⠛⠛⠛⠛⠛⠛⠃⠄⣤⣤⣾⣿⣿⣿\n"
              << "⣿⣿⣿⣿⡿⠃⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠸⣿⣿⣿⣿⣿\n"
              << "⣿⣿⣿⢻⢀⠄⣾⣿⣿⣶⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢠⣾⣿⣿⣦⢀⠈⠻⣿⣿⣿\n"
              << "⣿⣿⣿⢸⠸⠇⠻⣿⣿⣿⠇⠄⢰⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄⠄⠻⣿⣿⣿⠏⠸⠄⠄⣿⣿⣿\n"
              << "⣿⣿⣿⢸⠄⠄⣀⣀⣀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢀⣀⣀⣀⠄⠄⠄⣿⣿⣿\n"
              << "⣿⣿⣿⢸⠄⠰⡏⠄⠄⢳⠄⠄⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠄⠄⡏⠄⠄⢹⠄⠄⠄⣿⣿⣿\n"
              << "⣿⣿⡟⢸⠄⠄⠳⠤⠴⠟⠄⠄⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⠄⠄⠳⠤⠤⠞⠄⠄⠄⣿⣿⣿\n"
              << "⣿⣿⣿⣾⣤⣤⣌⣁⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣈⣡⣤⣴⣶⣿⣿⣿" << std::endl;
    User current_user;
    bool logged_in = false;
    int choice;

    while (true)
    {
        if (!logged_in)
        {
            std::cout << "\n--- Главное меню ---\n";
            std::cout << "1. Войти\n";
            std::cout << "2. Зарегистрироваться\n";
            std::cout << "3. Выйти\n";
            std::cout << "Выберите опцию: ";
            std::cin >> choice;

            switch (choice)
            {
            case 1:
            {
                std::string login, password;
                std::cout << "\nВведите почту: ";
                std::cin >> login;
                std::cout << "Введите пароль: ";

                struct termios oldt, newt;
                tcgetattr(STDIN_FILENO, &oldt);
                newt = oldt;
                newt.c_lflag &= ~ECHO;
                tcsetattr(STDIN_FILENO, TCSANOW, &newt);
                std::cin >> password;
                std::cout << std::endl;
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

                try
                {
                    current_user.sign_up(login, password);
                    logged_in = true;
                    std::cout << "Вы успешно вошли!\n";
                }
                catch (const std::invalid_argument &e)
                {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }

            case 2:
            {
                std::string login, password, name;
                std::cout << "\nВведите почту: ";
                std::cin >> login;
                std::cout << "Введите пароль: ";

                struct termios oldt, newt;
                tcgetattr(STDIN_FILENO, &oldt);
                newt = oldt;
                newt.c_lflag &= ~ECHO;
                tcsetattr(STDIN_FILENO, TCSANOW, &newt);
                std::cin >> password;
                std::cout << std::endl;
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

                std::cout << "Введите имя: ";
                std::cin >> name;

                try
                {
                    current_user.log_in(name, login, password);
                    logged_in = true;
                    std::cout << "Вы успешно зарегистрированы и вошли в аккаунт!\n";
                }
                catch (const std::invalid_argument &e)
                {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }

            case 3:
                std::cout << "\nДо свидания!" << std::endl;
                return 0;

            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
            }
        }
        else
        {
            std::cout << "\n--- Меню аккаунта ---\n";
            std::cout << "1. Сменить пароль\n";
            std::cout << "2. Посмотреть историю аренды\n";
            std::cout << "3. Посмотреть список доступного транспорта\n";
            std::cout << "4. Взять транспорт в аренду\n";
            std::cout << "5. Вернуть арендованный транспорт\n";
            std::cout << "6. Пополнить баланс\n";
            std::cout << "7. Узнать баланс\n";
            std::cout << "8. Провести тех.обслуживание\n";
            std::cout << "9. Выйти из аккаунта\n";
            std::cout << "Выберите опцию: ";
            std::cin >> choice;

            switch (choice)
            {
            case 1:
            {
                std::string new_password;
                std::cout << "\nВведите новый пароль: ";
                std::cin >> new_password;
                current_user.change_password(new_password);
                std::cout << "Пароль успешно изменен.\n";
                break;
            }

            case 2:
            {
                try
                {
                    current_user.show_rent_history();
                }
                catch (const std::exception &e)
                {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }

            case 3:
            {
                std::cout << "\n--- Доступные транспортные средства ---\n";
                std::cout << "1. Машины\n";
                std::cout << "2. Грузовики\n";
                std::cout << "3. Мотоциклы\n";
                std::cout << "4. Назад\n";
                std::cout << "Выберите опцию: ";
                std::cin >> choice;

                switch (choice)
                {
                case 1:
                case 2:
                case 3:
                {
                    std::string vehicle_type = (choice == 1) ? "cars.txt" : (choice == 2) ? "trucks.txt"
                                                                                          : "motos.txt";
                    show_transport(vehicle_type);
                    break;
                }

                case 4:
                    break;

                default:
                    std::cout << "Неверный выбор.\n";
                }
                break;
            }
            case 4:
            {
                while (true)
                {
                    std::cout << "\n--- Взять транспорт в аренду ---\n";
                    std::cout << "1. Машины\n";
                    std::cout << "2. Грузовики\n";
                    std::cout << "3. Мотоциклы\n";
                    std::cout << "4. Назад\n";
                    std::cout << "Выберите опцию: ";
                    std::cin >> choice;

                    if (choice == 4)
                        break;

                    std::string vehicle_type = (choice == 1)   ? "cars.txt"
                                               : (choice == 2) ? "trucks.txt"
                                               : (choice == 3) ? "motos.txt"
                                                               : "";

                    if (vehicle_type.empty())
                    {
                        std::cout << "Неверный выбор. Попробуйте снова.\n";
                        continue;
                    }

                    while (true)
                    {
                        std::cout << "\n--- Действия ---\n";
                        std::cout << "1. Показать доступный транспорт\n";
                        std::cout << "2. Ввести номер транспорта\n";
                        std::cout << "3. Назад\n";
                        std::cout << "Выберите опцию: ";
                        std::cin >> choice;

                        if (choice == 3)
                            break;

                        try
                        {
                            if (choice == 1)
                            {
                                show_transport(vehicle_type);
                            }
                            else if (choice == 2)
                            {
                                std::string transport_id;
                                std::cout << "Введите номер транспорта: ";
                                std::cin >> transport_id;

                                if (vehicle_type == "cars.txt")
                                {
                                    Car car(transport_id);
                                    current_user.rent(&car);
                                    current_user += &car;
                                }

                                if (vehicle_type == "trucks.txt")
                                {
                                    Truck truck(transport_id);
                                    current_user.rent(&truck);
                                    current_user += &truck;
                                }

                                if (vehicle_type == "motos.txt")
                                {
                                    Moto moto(transport_id);
                                    current_user.rent(&moto);
                                    current_user += &moto;
                                }
                                std::cout << "Транспорт успешно взят в аренду!\n";
                                break;
                            }
                            else
                            {
                                std::cout << "Неверный выбор. Попробуйте снова.\n";
                            }
                        }
                        catch (const std::exception &e)
                        {
                            std::cout << "Ошибка: " << e.what() << "\n";
                            std::cout << "Попробуйте снова.\n";
                        }
                    }
                }
                break;
            }
            case 5:
            {
                while (true)
                {
                    std::cout << "\n--- Вернуть транспорт в аренду ---\n";
                    std::cout << "1. Машины\n";
                    std::cout << "2. Грузовики\n";
                    std::cout << "3. Мотоциклы\n";
                    std::cout << "4. Назад\n";
                    std::cout << "Выберите опцию: ";
                    std::cin >> choice;

                    if (choice == 4)
                        break;

                    std::string vehicle_type = (choice == 1)   ? "cars.txt"
                                               : (choice == 2) ? "trucks.txt"
                                               : (choice == 3) ? "motos.txt"
                                                               : "";

                    if (vehicle_type.empty())
                    {
                        std::cout << "Неверный выбор. Попробуйте снова.\n";
                        continue;
                    }

                    while (true)
                    {
                        std::cout << "\n--- Действия ---\n";
                        std::cout << "1. Ввести номер транспорта\n";
                        std::cout << "2. Назад\n";
                        std::cout << "Выберите опцию: ";
                        std::cin >> choice;

                        if (choice == 2)
                            break;

                        try
                        {
                            if (choice == 1)
                            {
                                std::string transport_id;
                                std::cout << "Введите номер транспорта: ";
                                std::cin >> transport_id;

                                if (vehicle_type == "cars.txt")
                                {
                                    Car car(transport_id);
                                    current_user.return_rent(&car);
                                }

                                if (vehicle_type == "trucks.txt")
                                {
                                    Truck truck(transport_id);
                                    current_user.return_rent(&truck);
                                }

                                if (vehicle_type == "motos.txt")
                                {
                                    Moto moto(transport_id);
                                    current_user.return_rent(&moto);
                                }
                                std::cout << "Транспорт успешно возвращен в аренду!\n";
                                break;
                            }
                            else
                            {
                                std::cout << "Неверный выбор. Попробуйте снова.\n";
                            }
                        }
                        catch (const std::exception &e)
                        {
                            std::cout << "Ошибка: " << e.what() << "\n";
                            std::cout << "Попробуйте снова.\n";
                        }
                    }
                }
                break;
            }
            case 6:
            {
                std::string sum;
                std::cout << std::endl
                          << "Введите сумму пополнения (желательно перечислить эти деньги по номеру +79252827006): ";
                std::cin >> sum;
                current_user.add_money(sum);
                std::cout << "Баланс пополнен" << std::endl;
                break;
            }
            case 7:
            {
                std::cout << std::endl
                          << "Ваш баланс: " << current_user.show_balance() << std::endl;
                break;
            }

            case 8:
            {
                while (true)
                {
                        int case_1;
                        std::cout << "\n--- Выберите тип транспорта ---\n";
                        std::cout << "1. Машина\n";
                        std::cout << "2. Грузовик\n";
                        std::cout << "3. Мотоцикл\n";
                        std::cout << "4. Назад\n";
                        std::cin >> case_1;
                        if(case_1 == 4) break;
                        if(case_1 == 1)
                        {
                            try
                            {
                                std::cout << "Введите номер транспорта: " << std::endl;
                                std::string number, type;
                                std::cin >> number;
                                std::cout << "Введите тип обслуживания: " << std::endl;
                                std::cin >> type;
                                Car car(number);
                                Maintenance_Record maintenance(&car, type);
                                break;
                            }
                            catch (const std::exception& e) {
                                std::cout << "Ошибка: " << e.what() << "\n";
                                std::cout << "Попробуйте снова.\n";
                            }

                        }
                        if(case_1 == 2)
                        {
                            try
                            {
                                std::cout << "Введите номер транспорта: " << std::endl;
                                std::string number, type;
                                std::cin >> number;
                                std::cout << "Введите тип обслуживания: " << std::endl;
                                std::cin >> type;
                                Truck truck(number);
                                Maintenance_Record maintenance(&truck, type);
                                break;
                            }
                            catch (const std::exception& e) {
                                std::cout << "Ошибка: " << e.what() << "\n";
                                std::cout << "Попробуйте снова.\n";
                            }

                        }
                        if(case_1 == 3)
                        {
                            try
                            {
                                std::cout << "Введите номер транспорта: " << std::endl;
                                std::string number, type;
                                std::cin >> number;
                                std::cout << "Введите тип обслуживания: " << std::endl;
                                std::cin >> type;
                                Moto moto(number);
                                Maintenance_Record maintenance(&moto, type);
                                break;
                            }
                            catch (const std::exception& e) {
                                std::cout << "Ошибка: " << e.what() << "\n";
                                std::cout << "Попробуйте снова.\n";
                            }

                        }
                    }
                    break;
                }
                case 9:
                            logged_in = false;
                            std::cout << "\nВыход из аккаунта.\n";
                            break;

                        default:
                            std::cout << "Неверный выбор.\n";
                        }
            }
            }

            return 0;
        }