#include <iostream>
#include <ctime>
#include <fstream>

using std::cout;
using std::cin;
using std::string;

class Pizzeria {
    public:
    long unsigned int ID;
    private:
    string name;
    float rating;
    public:
    Pizzeria(long unsigned int ID, string name, float rating) {
        this->ID = ID;
        this->name = name;
        this->rating = rating;
    }
};
class Menu {
    public:
    long unsigned int ID;
    private:
    long unsigned int Pizzeria_ID;
    string Pizza_Name;
    float Price;
    public:
    Menu(long unsigned int ID, long unsigned int Pizzeria_ID, string Pizza_Name, float Price) {
        this->ID = ID;
        this->Pizzeria_ID = Pizzeria_ID;
        this->Pizza_Name = Pizza_Name;
        this->Price = Price;
    }
};
class Person {
    public:
    long unsigned int ID;
    private:
    string name;
    int age;
    bool gender; // true - Man, false - Woman
    string address;
    public:
    Person(long unsigned int ID, string name, int age, bool gender, string address) {
        this->ID = ID;
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->address = address;
    }
};
class Person_Visits {
    public:
    long unsigned int ID;
    private:
    long unsigned int Person_ID;
    long unsigned int Pizzeria_ID;
    tm Visit_Date;
    public:
    Person_Visits(long unsigned int ID, long unsigned int Person_ID, long unsigned int Pizzeria_ID, tm Visit_Date) {
        this->ID = ID;
        this->Person_ID = Person_ID;
        this->Pizzeria_ID = Pizzeria_ID;
        this->Visit_Date = Visit_Date;
    }
};
class Person_Order {
    public:
    long unsigned int ID;
    private:
    long unsigned int Person_ID;
    long unsigned int Menu_ID;
    tm Order_Date;
    public:
    Person_Order(long unsigned int ID, long unsigned int Person_ID, long unsigned int Menu_ID, tm Order_Date) {
        this->ID = ID;
        this->Person_ID = Person_ID;
        this->Menu_ID = Menu_ID;
        this->Order_Date = Order_Date;
    }
};

int main() {
    Pizzeria Dodo = Pizzeria(3859231283972471, "Dodo pizza", 4.7);
    return 0;
}
