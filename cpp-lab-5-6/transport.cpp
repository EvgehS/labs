#include "transport.hpp"
#include <fstream>
#include <exception>

User::User() : name(""), email(""), passwd("") {};

void User::log_in(const std::string &input_name, const std::string &input_email, const std::string &input_passwd)
{
    std::ifstream in("users.txt");
    std::string tmp_name, tmp_email, tmp_passwd, tmp_balance;

    while (in >> tmp_name >> tmp_email >> tmp_passwd >> tmp_balance)
    {
        if (tmp_email == input_email)
            throw std::invalid_argument("This email is already registered");
    }
    in.close();

    name = input_name;
    email = input_email;
    passwd = input_passwd;
    balance = "0";


    save();
}

void User::sign_up(const std::string &input_email, const std::string &input_passwd)
{
    std::ifstream file("users.txt");
    std::string tmp_email, tmp_name, tmp_passwd, tmp_balance;

    while (file >> tmp_name >> tmp_email >> tmp_passwd >> tmp_balance)
    {
        if (tmp_email == input_email)
        {
            if (input_passwd != tmp_passwd)
                throw std::invalid_argument("Incorrect passwd");

            else
            {
                email = tmp_email;
                name = tmp_name;
                passwd = tmp_passwd;
                balance = tmp_balance;

                file.close();
                return;
            }
        }
    }
    file.close();
    throw std::invalid_argument("No such user");
}

void User::save()
{
    std::ofstream file("users.txt", std::ios::app);

    file << name << " " << email << " " << passwd << " " << balance << std::endl;;

    file.close();
}

void User::change_password(const std::string &new_password)
{
    delete_line("users.txt", name + " " + email + " " +  passwd + " " + balance);
    passwd = new_password;
    save();
    
}

void User::show_rent_history()
{
    std::ifstream file("renthistory.txt");
    std::string email, number, type;
    int flag = 1;
    std::cout << "Транспорт, арендованный ранее" << std::endl;
    std::cout << "Номер\tТип" << std::endl;
    while(file >> email >> number >> type)
    {
        if(email == this->email)
        {
            std::cout << number << "\t" << type << std::endl;
            flag = 0;
        }
    }
    if(flag)
        throw std::invalid_argument("No rent before");
    file.close();
}

void User::operator+=(Vehicle* vehicle)
{
    std::ofstream file("renthistory.txt", std::ios::app);
    file << email << "\t" << (*vehicle).number << "\t" << (*vehicle).get_type() << std::endl;;
    file.close();
}

void User::rent(Vehicle* vehicle)
{
    if(vehicle->is_rentable == "нет")
        throw std::invalid_argument("Vehilce has been rented");

    long long balance = std::stoll(this->balance), rent_price = std::stoll(vehicle->rent_price);

    if(rent_price > balance) 
        throw std::invalid_argument("Not enough money");
    balance -= rent_price;
    delete_line("users.txt", name + " " + email + " " +  passwd + " " + this->balance);
    this->balance = std::to_string(balance);

    save();
    (*vehicle).rent(this->email);
}

void User::return_rent(Vehicle* vehicle)
{
    if(vehicle->is_rentable == "да")
        throw std::invalid_argument("Vehicle hasn't been rented");

    (*vehicle).return_rent(email);
}

void User::add_money(std::string& money)
{
    delete_line("users.txt", name + " " + email + " " +  passwd + " " + balance);
    balance = std::to_string(std::stoll(money) + std::stoll(balance));
    save();
}

std::string& User::show_balance()
{
    return balance;
}

Vehicle::Vehicle()
{
    number = model = brand = year = rent_price = "";
}

Vehicle::Vehicle(const std::string &number, const std::string &model, const std::string &brand, const std::string &year, const std::string &rent_price, const std::string &is_rentable)
{
    this->number = number;
    this->model = model;
    this->brand = brand;
    this->year = year;
    this->rent_price = rent_price;
    this->is_rentable = is_rentable;
}

void Vehicle::get_info()
{
     std::cout << "Номер: " << number << "\n"
                  << "Модель: " << model << "\n"
                  << "Марка: " << brand << "\n"
                  << "Год выпуска: " << year << "\n"
                  << "Цена аренды: " << rent_price << "\n"
                  << "Возможно ли арендовать: " << is_rentable << "\n";
}

Car::Car() : Vehicle()
{
    gearbox_type = speed_limit = "";
}

Car::Car(const std::string &number, const std::string &model, const std::string &brand, const std::string &year, const std::string &rent_price, const std::string &is_rentable, const std::string &gearbox_type, const std::string &speed_limit)
    : Vehicle(number, model, brand, year, rent_price, is_rentable)
{
    this->speed_limit = speed_limit;
    this->gearbox_type = gearbox_type;
}

Car::Car(const std::string& number_to_find)
{
    std::string number, model, brand, year, rent_price, gearbox_type, speed_limit, rentable;
    std::ifstream file("cars.txt");
    while(file >> number >> model >> brand >> year >> rent_price >> rentable >> speed_limit >> gearbox_type)
    {
        if((number == number_to_find))
        {
            this->number = number;
            this->model = model;
            this->brand = brand;
            this->year = year;
            this->rent_price = rent_price;
            this->gearbox_type = gearbox_type;
            this->speed_limit = speed_limit; 
            this->is_rentable = rentable;
            file.close();
            return;
        }
    }
    file.close();
    throw std::invalid_argument("No vehicle with such number");
}
void Car::get_info()
{
    Vehicle::get_info();
    std::cout << "Максимальная скорость: " << speed_limit << "\n" 
                "Тип коробки передач: " << gearbox_type << std::endl;
}

void Car::save()
{
    std::ofstream file("cars.txt", std::ios::app);

    file << number << "\t" << model << "\t" << brand 
        << "\t" << year << "\t" << rent_price << "\t" << is_rentable << "\t" << speed_limit << "\t" << gearbox_type << std::endl ;

    file.close();
}

void Car::rent(std::string& email)
{
    delete_line("cars.txt", number + "\t" + model  + "\t" + brand  + "\t" + year
                         + "\t" + rent_price + "\t" + is_rentable + "\t" + speed_limit + "\t" + gearbox_type);
    is_rentable = "нет";

    std::ofstream file("rented_cars.txt", std::ios::app);
    file << email << "\t" << number << std::endl;
    save();
}

void Car::return_rent(std::string& email)
{
    std::ifstream file("rented_cars.txt");
    std::string mail, number;
    while(file >> mail >> number)
    {
        if((number == this->number) && (mail != email))
            throw  std::invalid_argument("Another user");
    }
    file.close();

    delete_line("rented_cars.txt", email + "\t" + this->number);

    delete_line("cars.txt", this->number + "\t" + model  + "\t" + brand  + "\t" + year
                         + "\t" + rent_price + "\t" + is_rentable + "\t" + speed_limit + "\t" + gearbox_type);
    
    is_rentable = "да";

    save();
}

std::string Car::get_type()
{
    return "машина";
}

Truck::Truck() : Vehicle()
{
    weight_limit = transmission = "";
}

Truck::Truck(const std::string &number, const std::string &model, const std::string &brand, const std::string &year, const std::string &rent_price, const std::string &is_rentable, const std::string &transmission, const std::string &weight_limit)
    : Vehicle(number, model, brand, year, rent_price, is_rentable)
{
    this->weight_limit = weight_limit;
    this->transmission = transmission;
}

void Truck::get_info()
{
    Vehicle::get_info();
    std::cout << "Максимальный вес: " << weight_limit << "\n" 
                "Тип коробки: "<< transmission << std::endl;
}

void Truck::save()
{
    std::ofstream file("trucks.txt", std::ios::app);

    file << number << "\t" << model << "\t" << brand 
        << "\t" << year << "\t" << rent_price << "\t" << is_rentable << "\t" << weight_limit << "\t" << transmission << std::endl;

    file.close();
}

Truck::Truck(const std::string& number_to_find)
{
    std::string filename = "trucks.txt", number, model, brand, year, rent_price, transmission, weight_limit, rentable;
    std::ifstream file(filename);
    while(file >> number >> model >> brand >> year >> rent_price >> rentable >> weight_limit >> transmission)
    {
        if((number == number_to_find))
        {
            this->number = number;
            this->model = model;
            this->brand = brand;
            this->year = year;
            this->rent_price = rent_price;
            this->transmission = transmission;
            this->weight_limit = weight_limit;
            this->is_rentable = rentable;
            file.close();
            return;
        }
    }
    file.close();
    throw std::invalid_argument("No vehicle with such number");
}

void Truck::rent(std::string& email)
{
    delete_line("trucks.txt", number + "\t" + model  + "\t" + brand  + "\t" + year
                         + "\t" + rent_price + "\t" + is_rentable + "\t" + weight_limit + "\t" + transmission);
    is_rentable = "нет";

    std::ofstream file("rented_trucks.txt", std::ios::app);
    file << email << "\t" << number << std::endl;
    save();
}

void Truck::return_rent(std::string& email)
{
    std::ifstream file("rented_trucks.txt");
    std::string mail, number;
    while(file >> mail >> number)
    {
        if((number == this->number) && (mail != email))
            throw  std::invalid_argument("Another user");
    }
    file.close();

    delete_line("rented_trucks.txt", email + "\t" + this->number);

    delete_line("trucks.txt", this->number + "\t" + model  + "\t" + brand  + "\t" + year
                         + "\t" + rent_price + "\t" + is_rentable + "\t" + weight_limit + "\t" + transmission);
    
    is_rentable = "да";

    save();
}

std::string Truck::get_type()
{
    return "грузовик";
}

Moto::Moto() : Vehicle()
{
    type = wheel_cnt = "";
}

Moto::Moto(const std::string &number, const std::string &model, const std::string &brand, const std::string &year, const std::string &rent_price, const std::string &is_rentable, const std::string &wheel_cnt, const std::string &type)
    : Vehicle(number, model, brand, year, rent_price, is_rentable)
{
    this->type = type;
    this->wheel_cnt = wheel_cnt;
}

void Moto::get_info()
{
    Vehicle::get_info();
    std::cout <<  "Тип: " << type << "\n" 
                "Количество колёс: "<< wheel_cnt << std::endl;
}

void Moto::save()
{
    std::ofstream file("motos.txt", std::ios::app);

    file << number << "\t" << model << "\t" << brand 
        << "\t" << year << "\t" << rent_price << "\t" << is_rentable << "\t" << type << "\t" << wheel_cnt << std::endl;

    file.close();
}

Moto::Moto(const std::string& number_to_find)
{
    std::string filename = "trucks.txt", number, model, brand, year, rent_price, wheel_cnt, type, rentable;
    std::ifstream file(filename);
    while(file >> number >> model >> brand >> year >> rent_price >> rentable >> type >> wheel_cnt)
    {
        if((number == number_to_find))
        {
            this->number = number;
            this->model = model;
            this->brand = brand;
            this->year = year;
            this->rent_price = rent_price;
            this->type = type;
            this->wheel_cnt = wheel_cnt;
            this->is_rentable = rentable;
            file.close();
            return;
        }
    }
    file.close();
    throw std::invalid_argument("No vehicle with such number");
}

void Moto::rent(std::string& email)
{
    delete_line("cars.txt", number + "\t" + model  + "\t" + brand  + "\t" + year
                         + "\t" + rent_price + "\t" + is_rentable + "\t" + type + "\t" + wheel_cnt);
    is_rentable = "нет";

    std::ofstream file("rented_motos.txt", std::ios::app);
    file << email << "\t" << number << std::endl;
    save();
}

void Moto::return_rent(std::string& email)
{
    std::ifstream file("rented_motos.txt");
    std::string mail, number;
    while(file >> mail >> number)
    {
        if((number == this->number) && (mail != email))
            throw  std::invalid_argument("Another user");
    }
    file.close();

    delete_line("rented_motos.txt", email + "\t" + this->number);

    delete_line("motos.txt", this->number + "\t" + model  + "\t" + brand  + "\t" + year
                         + "\t" + rent_price + "\t" + is_rentable + "\t" + type + "\t" + wheel_cnt);
    
    is_rentable = "да";

    save();
}

std::string Moto::get_type()
{
    return "мотоцикл";
}

void show_transport(const std::string& filename)
{
    std::ifstream file(filename);
    std::string str;
    bool flag = true;
    std::cout << "Номер\t" << "Модель\t" << "Марка\t" << "Год выпуска\t" << "Цена аренды\t" << "Возможно ли арендовать\t";
    std::cout << ((filename == "cars.txt") ? "Максимальная скорость\tТип коробки":((filename == "motos.txt") ? "Тип\tКол-во колёс":"Максимальный вес\tПривод")) << std::endl;;
    while(getline(file, str))
    {
        if(str.find("да") != std::string::npos)
        {
            std::cout << str << std::endl;
            flag = false;
        }
    }
    file.close();
    if(flag)
    {
        std::cout << "\t\t\tНет доступного транспорта" << std::endl;
    }
}

void delete_line(const std::string& filename, const std::string& line_to_delete) {
    std::ifstream inputFile(filename);
    std::ofstream tempFile("temp.txt"); 

    std::string line;

    while (std::getline(inputFile, line)) {
        if (line != line_to_delete) {
            tempFile << line << '\n';
        }
    }

    inputFile.close();
    tempFile.close();

    std::remove(filename.c_str());
    std::rename("temp.txt", filename.c_str());
}

Maintenance_Record::Maintenance_Record(Vehicle* vehicle, std::string& type)
{
    vehicle_type = (*vehicle).get_type();
    vehicle_number = vehicle->number;
    maintenance_type = type;
    save();
}

void Maintenance_Record::save()
{
    std::ofstream file("maintenance.txt", std::ios::app);

    file << vehicle_type << "\t" << vehicle_number << "\t" << maintenance_type << std::endl;

    file.close();
}