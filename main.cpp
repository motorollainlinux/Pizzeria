#include <map>
#include <ctime>
#include <fstream>
#include <iostream>
#include <math.h>

using std::cout;
using std::cin;
using std::string;
using std::map;
using std::ifstream;
using std::ofstream;
using std::fstream;

class Pizzeria {
    public:
    long unsigned int ID;
    string name;
    float rating;
    Pizzeria(long unsigned int ID, string name, float rating) {
        this->ID = ID;
        this->name = name;
        this->rating = rating;
    }
};
class Menu {
    public:
    long unsigned int ID;
    long unsigned int Pizzeria_ID;
    string Pizza_Name;
    float Price;
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
    string name;
    int age;
    bool gender; // true - Man, false - Woman
    string address;
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
    long unsigned int Person_ID;
    long unsigned int Pizzeria_ID;
    tm Visit_Date;
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
    long unsigned int Person_ID;
    long unsigned int Menu_ID;
    tm Order_Date;
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
    int i = 0;
    for(;!File_pizzeria.eof(); i++) {
        File_pizzeria >> name;
        File_pizzeria >> ID;
        File_pizzeria >> rating;
        Pizzeria pizzeria(ID, name, rating);
        MapPizzeria.emplace(i, pizzeria);
    }
    File_pizzeria.close();
    return i;
}
int MenuFilling(map<int, Menu> &MapMenu) {
    fstream File_menu("Menu.txt");
    long unsigned int ID;
    long unsigned int Pizzeria_ID;
    string Name_pizza;
    int Price;
    int i = 0;
    for(;!File_menu.eof(); i++) {
        File_menu >> ID;
        File_menu >> Pizzeria_ID;
        File_menu >> Name_pizza;
        File_menu >> Price;
        Menu menu(ID, Pizzeria_ID, Name_pizza, Price);
        MapMenu.emplace(i, menu);
    }
    File_menu.close();
    return i;
}
int PersonFilling(map<int, Person> &MapPerson) {
    fstream File_person("Persons.txt");
    long unsigned int ID;
    string name, address, StrGender;
    int age;
    bool gender;
    int i = 0;
    for(;!File_person.eof(); i++) {
        File_person >> ID;
        File_person >> name;
        File_person >> age;
        File_person >> StrGender;
        gender = std::stoi(StrGender);
        File_person >> address;
        Person person(ID, name, age, gender, address);
        MapPerson.emplace(i, person);
    }
    File_person.close();
    return i;
}
Person_Order OrderGenerate(map<int, Menu> MapMenu, map<int, Person> MapPerson, tm day, int MaxMenuMap, int MaxPersonMap) {
    srand(time(NULL));
    int Random = rand();
    srand(Random);
    int ID;
    Random = rand() % (MaxPersonMap+1);
    Person person = MapPerson.at(Random);
    Random = rand() % (MaxMenuMap+1);
    Menu menu = MapMenu.at(Random);
    ID = rand() % (4294967292+1);
    Person_Order personorder(ID, person.ID, menu.ID, day);
    return personorder;
}
Person_Visits VisitsGenerate(map<int, Pizzeria> MapPizzeria, map<int, Person> MapPerson, tm day, int MaxPersonMap, int MaxPizzeriaMap) {
    srand(time(NULL));
    int Random = rand();
    srand(Random);
    int ID;
    Random = rand() % (MaxPersonMap+1);
    Person person = MapPerson.at(Random);
    Random = rand() % (MaxPizzeriaMap+1);
    Pizzeria pizzeria = MapPizzeria.at(Random);
    ID = rand() % (4294967292+1);
    Person_Visits personvisits(ID, person.ID, pizzeria.ID, day);
    return personvisits; 
}
int searchMenu(map<int, Menu> MapMenu, long unsigned int ID, int MaxMenuMap) {
    for (int i = 0;i < MaxMenuMap; i++) {
        cout << "work " << ID << "\n";
        Menu menu = MapMenu.at(i);
        if(menu.ID == ID) {
            return i;
        }
    }
    return MaxMenuMap;
}
void WeekTimer(map<int, Pizzeria> MapPizzeria, map<int, Menu> MapMenu, map<int, Person> MapPerson, int MaxPizzeriaMap, int MaxMenuMap, int MaxPersonMap) {
    srand(time(NULL));
    
    fstream LOG("log.txt");
    tm day;
    day.tm_year = 2023;
    day.tm_mon = 9;
    day.tm_mday = 26;
    int Random;
    for(int i = 0; i < 15; i++) {
        Random = rand() % (20-3+1);
        for(int j = 0; j < Random; j++) {
            Person_Visits personvisits = VisitsGenerate(MapPizzeria, MapPerson, day, MaxPersonMap, MaxPizzeriaMap);
            LOG << "Person:" << personvisits.Person_ID << " Visit Pizzeria: " << personvisits.Pizzeria_ID << "at: " << personvisits.Visit_Date.tm_mday << "\n";
        }
        Random = rand() % (20-3+1);
        for(int j = 0; j < Random; j++) {
            Person_Order personorder = OrderGenerate(MapMenu, MapPerson, day, MaxMenuMap, MaxPersonMap);
            cout << "test:" << searchMenu(MapMenu, personorder.Menu_ID, MaxMenuMap) << " tess: " << MaxMenuMap << "\n";
            LOG << "Person:" << personorder.Person_ID << " Order Pizza: " << personorder.Menu_ID << "at: " << personorder.Order_Date.tm_mday << "for:" << MapMenu.at(searchMenu(MapMenu, personorder.Menu_ID, MaxMenuMap)).Price << "₽\n";
        }
        day.tm_mday++;
    }
    LOG.close();
}
int main() {
    map<int, Pizzeria> MapPizzeria;
    map<int, Menu> MapMenu;
    map<int, Person> MapPerson;
    map<int, Person_Order> MapPersonOrder;
    map<int, Person_Visits> MapPersonVisits;
    int MaxPizzeriaMap, MaxMenuMap, MaxPersonMap;
    MaxPizzeriaMap = PizzeriaFilling(MapPizzeria);
    MaxMenuMap = MenuFilling(MapMenu);
    MaxPersonMap = PersonFilling(MapPerson);
    WeekTimer(MapPizzeria, MapMenu, MapPerson, MaxPizzeriaMap, MaxMenuMap, MaxPersonMap);
    return 0;
}
