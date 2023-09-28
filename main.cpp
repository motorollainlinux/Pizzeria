#include <ctime>
#include <fstream>
#include <iostream>
#include <math.h>
#include <map>

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
        gender = StrGender == "true" || StrGender == "1";
        File_person >> address;
        Person person(ID, name, age, gender, address);
        MapPerson.emplace(i, person);
    }
    File_person.close();
    return i;
}
Person_Order OrderGenerate(map<int, Menu> MapMenu, map<int, Person> MapPerson, tm day, int MaxMenuMap, int MaxPersonMap) {
    int Random;
    //srand(time(NULL));
    int ID;
    Random = rand() % (MaxPersonMap);
    Person person = MapPerson.at(Random);
    Random = rand() % (MaxMenuMap);
    Menu menu = MapMenu.at(Random);
    ID = rand() % (4294967292);
    Person_Order personorder(ID, person.ID, menu.ID, day);
    return personorder;
}
Person_Visits VisitsGenerate(map<int, Pizzeria> MapPizzeria, map<int, Person> MapPerson, tm day, int MaxPersonMap, int MaxPizzeriaMap) {
    int Random;
    //srand(time(NULL));
    int ID;
    Random = rand() % (MaxPersonMap);
    Person person = MapPerson.at(Random);
    Random = rand() % (MaxPizzeriaMap);
    Pizzeria pizzeria = MapPizzeria.at(Random);
    ID = rand() % (4294967292);
    Person_Visits personvisits(ID, person.ID, pizzeria.ID, day);
    return personvisits; 
}
int searchMenu(map<int, Menu> MapMenu, long unsigned int ID) {
    for (int i = 0;i < MapMenu.size(); i++) {
        Menu menu = MapMenu.at(i);
        if(menu.ID == ID) {
            return i;
        }
    }
    return MapMenu.size()-1;
}
int searchPizzeria(map<int, Pizzeria> MapPizzeria, long unsigned int ID) {
    for (int i = 0;i < MapPizzeria.size(); i++) {
        Pizzeria pizzeria = MapPizzeria.at(i);
        if(pizzeria.ID == ID) {
            return i;
        }
    }
    return MapPizzeria.size()-1;
}
int searchPerson(map<int, Person> MapPerson, long unsigned int ID) {
    for (int i = 0;i < MapPerson.size(); i++) {
        Person person = MapPerson.at(i);
        if(person.ID == ID) {
            return i;
        }
    }
    return MapPerson.size()-1;
}
void WeekTimer(map<int, Pizzeria> MapPizzeria, map<int, Menu> MapMenu, map<int, Person> MapPerson, int MaxPizzeriaMap, int MaxMenuMap, int MaxPersonMap, map<int, Person_Order> &MapPersonOrder, map<int, Person_Visits> &MapPersonVisits) {
    int Random, MenuIterrator = 0;
    //srand(Random);
    tm day;
    day.tm_year = 2023;
    day.tm_mon = 9;
    day.tm_mday = 26;
    int k = 0, l = 0;
    for(int i = 0; i < 15; i++) {
        Random = (rand() % (20-3))+1;
        for(int j = 0; j < Random; j++) {
            Person_Visits personvisits = VisitsGenerate(MapPizzeria, MapPerson, day, MaxPersonMap, MaxPizzeriaMap);
            //cout << "V: " << personvisits.ID << " " << personvisits.Person_ID << " " << searchPizzeria(MapPizzeria, personvisits.Pizzeria_ID) << "\n";
            MapPersonVisits.emplace(k, personvisits);
            k++;
            }
        Random = (rand() % (20-3))+1;
        for(int j = 0; j < Random; j++) {
            Person_Order personorder = OrderGenerate(MapMenu, MapPerson, day, MaxMenuMap, MaxPersonMap);
            int indexMenu = searchMenu(MapMenu, personorder.Menu_ID);
            Menu menu = MapMenu.at(indexMenu);
            //cout << "O: " << personorder.ID << " " << personorder.Person_ID << " " << searchPizzeria(MapPizzeria, menu.Pizzeria_ID) << "\n";
            MapPersonOrder.emplace(l, personorder);
            l++;
            }
        day.tm_mday++;
        if(day.tm_mday > 30) {
            day.tm_mday = 1;
            day.tm_mon++;
        }
    }
}
void Results(map<int, Person_Order> MapPersonOrder,map<int, Person_Visits> MapPersonVisits, map<int, Pizzeria> MapPizzeria, map<int, Menu> MapMenu, map<int, Person> MapPerson) {
    map<string, int> VisitsAndOrdersCount;
    map<int, int> IvestinsMoney;
    int AveragePrice;
    int best = 0;
    string IsBest = "";
    for(int i = 0; i < MapMenu.size(); i++) {
        Menu menu = MapMenu.at(i);
        AveragePrice += menu.Price;
    }
    AveragePrice /= 30;
    for(int i = 0; i < MapPersonVisits.size(); i++) {
        Person_Visits personvisits = MapPersonVisits.at(i);
        int indexPizzeria = searchPizzeria(MapPizzeria, personvisits.Pizzeria_ID);
        // cout << searchPizzeria(MapPizzeria, personvisits.Pizzeria_ID) << "\n";
        Pizzeria pizzeria = MapPizzeria.at(indexPizzeria);
        VisitsAndOrdersCount[pizzeria.name]++;
    }
    for(int i = 0; i < MapPersonOrder.size(); i++) {
        Person_Order personorder = MapPersonOrder.at(i);
        int indexPizza = searchMenu(MapMenu, personorder.Menu_ID);
        Menu menu = MapMenu.at(indexPizza);
        int indexPizzeria = searchPizzeria(MapPizzeria, menu.Pizzeria_ID);
        Pizzeria pizzeria = MapPizzeria.at(indexPizzeria);
        VisitsAndOrdersCount[pizzeria.name]++;
    }
    for(int i = 0; i < MapPizzeria.size();i++) {
        Pizzeria pizzeria = MapPizzeria.at(i);
        if(VisitsAndOrdersCount[pizzeria.name] > best) {
            best = VisitsAndOrdersCount[pizzeria.name];
            IsBest = pizzeria.name;
        }
    }
    cout << "Best Pizzeria of this 2 weeks is: " << IsBest << " whis " << best << " visits and orders!\n";
    best = 0;
    IsBest = "";
    for(int i = 0; i < MapPersonVisits.size(); i++) {
        Person_Visits personvisits = MapPersonVisits.at(i);
        int indexPerson = searchPerson(MapPerson, personvisits.Person_ID);
        IvestinsMoney[indexPerson] += AveragePrice;
    }
    for(int i = 0; i < MapPersonOrder.size(); i++) {
        Person_Order personorder = MapPersonOrder.at(i);
        int indexPerson = searchPerson(MapPerson, personorder.Person_ID);
        int indexPizza = searchMenu(MapMenu, personorder.Menu_ID);
        Menu menu = MapMenu.at(indexPizza);
        IvestinsMoney[indexPerson] += menu.Price;
    }
    for(int i = 0; i < MapPerson.size(); i++) {
        if(IvestinsMoney[i] > best) {
            best = IvestinsMoney[i];
            Person person = MapPerson.at(i);
            IsBest = person.name;
        }
        if (IsBest == "") {
            Person person = MapPerson.at(0);
            IsBest = person.name;
        }
    }
    cout << "most active buyer in 2 weeks is: " << IsBest << " spent: " << best << " rub\n";
}
int main() {
    srand(time(NULL));
    map<int, Pizzeria> MapPizzeria;
    map<int, Menu> MapMenu;
    map<int, Person> MapPerson;
    map<int, Person_Order> MapPersonOrder;
    map<int, Person_Visits> MapPersonVisits;
    int MaxPizzeriaMap, MaxMenuMap, MaxPersonMap;
    MaxPizzeriaMap = PizzeriaFilling(MapPizzeria);
    MaxMenuMap = MenuFilling(MapMenu);
    MaxPersonMap = PersonFilling(MapPerson);
    WeekTimer(MapPizzeria, MapMenu, MapPerson, MaxPizzeriaMap, MaxMenuMap, MaxPersonMap, MapPersonOrder, MapPersonVisits);
    Results(MapPersonOrder, MapPersonVisits, MapPizzeria, MapMenu, MapPerson);
    return 0;
}
