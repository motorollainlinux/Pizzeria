#include <map>
#include <ctime>
#include <fstream>
#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::map;
using std::ifstream;
using std::fstream;

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
int PizzeriaFilling(map<int, Pizzeria> &MapPizzeria) {
    fstream File_pizzeria("Pizzeria.txt");
    long unsigned int ID;
    string name;
    float rating;
    int i = 0
    for(;!File_pizzeria.eof(); i++) {
        File_pizzeria >> name;
        File_pizzeria >> ID;
        File_pizzeria >> rating;
        Pizzeria pizzeria(ID, name, rating);
        MapPizzeria.emplace(i, pizzeria);
    }
    return i;
}
int MenuFilling(map<int, Pizzeria> &MapMenu) {
    fstream File_menu("Menu.txt");
    long unsigned int ID;
    long unsigned int Pizzeria_ID;
    string Name_pizza;
    int Price;
    int i = 0
    for(;!File_menu.eof(); i++) {
        File_menu >> ID;
        File_menu >> Pizzeria_ID;
        File_menu >> Name_pizza;
        File_menu >> Price;
        Menu menu(ID, Pizzeria_ID, Name_pizza, Price);
        MapMenu.emplace(i, menu);
    }
    return i;
}
int PersonFilling(map<int, Pizzeria> &MapPerson) {
    fstream File_person("Persons.txt");
    long unsigned int ID;
    string name, address;
    int age;
    bool gender;
    int i = 0
    for(;!File_pizzeria.eof(); i++) {
        File_person >> ID;
        File_person >> name;
        File_person >> age;
        File_person >> gender;
        File_person >> address;
        Person person(ID, name, age, gender, address);
        MapPerson.emplace(i, person);
    }
    return i;
}
int main() {
    map<int, Pizzeria> MapPizzeria;
    map<int, Menu> MapMenu;
    map<int, Person> MapPerson;
    int MaxPizzeriaMap, MaxMenuMap, MaxPersonMap;
    MaxPizzeriaMap = PizzeriaFilling(MapPizzeria);
    MaxMenuMap = MenuFilling(MapMenu);
    MaxPersonMap = PersonFilling(MapPerson);
    
    return 0;
}

