#include <iostream>

class Vehicle
{
public:
    Vehicle();
    Vehicle(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
    virtual void get_info();
    virtual void save() {};
    virtual ~Vehicle() {};
    virtual void rent(std::string&) {};
    virtual void return_rent(std::string&) {};


protected:
    std::string number, model, brand, year, rent_price, is_rentable;
    virtual std::string get_type() {return "none";};
    friend class User;
    friend class Maintenance_Record;
};

class Car: public Vehicle
{
public:
    Car();
    Car(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
    Car(const std::string&);
    void get_info();
private:
    std::string gearbox_type, speed_limit;
    void save();
    void rent(std::string&);
    void return_rent(std::string&);
    std::string get_type();
};

class Moto: public Vehicle
{
public:
    Moto();
    Moto(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
    Moto(const std::string&);
    void get_info();
private:
    std::string type, wheel_cnt;
    void save();
    void rent(std::string&);
    void return_rent(std::string&);
    std::string get_type();
};

class Truck: public Vehicle
{
public:
    Truck();
    Truck(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
    Truck(const std::string&);
    void get_info();
private:
    std::string weight_limit, transmission;
    void save();
    void rent(std::string& );
    void return_rent(std::string&);
    std::string get_type();
};

class User
{
public:
    User();
    void log_in(const std::string&, const std::string&, const std::string&);
    void sign_up(const std::string&, const std::string&);
    void change_password(const std::string&);
    void show_rent_history();
    void operator+=(Vehicle*);
    void rent(Vehicle*); 
    void return_rent(Vehicle*);
    void add_money(std::string& money);
    std::string& show_balance();

private:
    std::string name, email, passwd, balance;
    void save();
};

class Maintenance_Record
{
public:
    Maintenance_Record(Vehicle*, std::string&);
private:
    void save();
    std::string vehicle_type, vehicle_number, maintenance_type;
};

void show_transport(const std::string& filename);

void delete_line(const std::string& filename, const std::string& line_to_delete);