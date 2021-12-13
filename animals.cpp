/*
Animal_scheduling methods for Program 3
Ben Rimedio - 11/10/2021
CS202 - Fall 2021
Instructor: Karla Fant
These are the implementations of the methods for the base class and
its three derived types. Operator overloading is implemented for the pertinent operators.
*/

#include <iomanip>
#include <cstring>
#include "animals.h"


//--------------------------------Animal_scheduling (Base Class)----------------------------------------------------
//Default constructor:
Animal_scheduling::Animal_scheduling()
{
    name = nullptr;
}

//Copy constructor:
Animal_scheduling::Animal_scheduling(const Animal_scheduling& source)
{
    set_name(source.name);
    time = source.time;
}

//Destructor:
Animal_scheduling::~Animal_scheduling()
{
    if(name)
        delete [] name;
}

//Set name to char* arg:
void Animal_scheduling::set_name(char* a_name)
{
    if(!a_name)
    {
        name = nullptr;
        return;
    }
    if(name)
        delete [] name;
    name = new char[strlen(a_name) + 1];
    strcpy(name, a_name);
}

//Set new time:
void Animal_scheduling::set_time(std::string& a_time)
{
    time = a_time;
}

//Compare name to char* argument:
bool Animal_scheduling::compare_name(char* a_name)
{
    return !(strcmp(name, a_name));
}
//----------------------------------Pettable-----------------------------------------------------------------------
//Default constructor:
Pettable::Pettable() : Animal_scheduling()
{
    price = 0.0;
}

//Copy constructor:
Pettable::Pettable(const Pettable& source) : Animal_scheduling(source)
{
    price = source.price;
}

//Destructor:
Pettable::~Pettable()
{
    price = 0.0;
}

//Set price:
void Pettable::set_price(float a_price)
{
    price = a_price;
}

//Prompt user to input fields:
void Pettable::input(void)
{
    char* new_name = new char[MAX_STREAM + 1];
    float new_price = 0.0;
    std::string new_time;
    
    std::cout << "\nEnter the name of the petting activity: ";
    std::cin.get(new_name, MAX_STREAM, '\n');
    std::cin.clear();
    std::cin.ignore(MAX_STREAM, '\n');
    std::cout << "Enter the time of the petting: ";
    std::getline(std::cin, new_time);
    set_time(new_time);
    std::cout << "Enter the price of the petting activity: ";
    while(!(std::cin >> new_price) || new_price < 0.0)
    {
        std::cout << "Invalid price. Enter valid price: ";
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');
    }
    std::cin.clear();
    std::cin.ignore(MAX_STREAM, '\n');

    set_price(new_price);
    set_name(new_name);

    delete [] new_name;
}

//Assignment operator copies source and returns reference to Pettable:
Pettable& Pettable::operator= (const Pettable& to_copy)
{
    if(this != &to_copy)
    {
        if(name)
        {
            delete [] name;
        }
        if(to_copy.name)
        {
            name = new char[strlen(to_copy.name) + 1];
            strcpy(name, to_copy.name);
        }
        price = to_copy.price;
    }
    return *this;
}

//Insertion operator. Returns ostream reference:
std::ostream& operator<< (std::ostream& out, const Pettable& in)
{
    out << "Name: " << in.name << "\t\tTime: " << in.time << "\tPrice: $" << std::fixed << std::setprecision(2) << in.price;
    return out;
}

//Display:
void Pettable::display(void) const
{
    std::cout << *this << std::endl;
}
//------------------------------------Distance--------------------------------------------------------------------
//Default constructor:
Distance::Distance()
{
    rate_hr = 0.0;
    hours = 0;
}

//Copy constructor:
Distance::Distance(const Distance& source) : Animal_scheduling(source)
{
    rate_hr = source.rate_hr;
    hours = source.hours;
}

//Destructor:
Distance::~Distance()
{
    rate_hr = 0.0;
    hours = 0;
}

//Assignment operator. Copies source and returns a Distance reference:
Distance& Distance::operator= (const Distance& to_copy)
{
    if(this != &to_copy)
    {
        if(name)
        {
            delete [] name;
        }
        if(to_copy.name)
        {
            name = new char[strlen(to_copy.name) + 1];
            strcpy(name, to_copy.name);
        }
        time = to_copy.time;
        rate_hr = to_copy.rate_hr;
        hours = to_copy.hours;
    }
    return *this;
}

//Set rate_hr:
void Distance::set_rate(float a_rate)
{
    rate_hr = a_rate;
}

//Set number of hours:
void Distance::set_hours(unsigned int amt)
{
    hours = amt;
}

//Input fields from user:
void Distance::input(void)
{
    std::string new_time;
    char* new_name = new char[MAX_STREAM + 1];
    float new_rate = 0.0;
    unsigned int new_hours = 0;
    
    std::cout << "\nEnter the name of the distance viewing activity: ";
    std::cin.get(new_name, MAX_STREAM, '\n');
    std::cin.clear();
    std::cin.ignore(MAX_STREAM, '\n');
    std::cout << "Enter the start time of the viewing: ";
    std::getline(std::cin, new_time);
    set_time(new_time);
    std::cout << "Enter the rate per hour of the activity: ";
    while(!(std::cin >> new_rate) || new_rate < 0.0)
    {
        std::cout << "Invalid rate. Enter valid rate: ";
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');
    }
    std::cout << "How many hours would you like to pay for?: ";
    while(!(std::cin >> new_hours) || new_hours >= 8)
    {
        std::cout << "Must pay for 1 to 8 hours. Enter valid amount of time: ";
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');
    }
    std::cin.clear();
    std::cin.ignore(MAX_STREAM, '\n');

    set_rate(new_rate);
    set_hours(new_hours);
    set_name(new_name);

    delete [] new_name;
}

//Insertion operator. Returns a reference to an ostream object:
std::ostream& operator<< (std::ostream& out, const Distance& in)
{
    out << "Name: " << in.name << "\t\tTime: " << in.time << "\tRate: $" << std::fixed << std::setprecision(2) << in.rate_hr << "/hr.";
    return out;
}

//Less than:
bool operator< (const Distance& first, const Distance& second)
{
    return strcmp(first.name, second.name) < 0;
}

//Greater than:
bool operator> (const Distance& first, const Distance& second)
{
    return strcmp(first.name, second.name) > 0;
}

//Less or equal:
bool operator<= (const Distance& first, const Distance& second)
{
    return strcmp(first.name, second.name) <= 0;
}

//Greater or equal:
bool operator>= (const Distance& first, const Distance& second)
{
    return strcmp(first.name, second.name) >= 0;
}

//Equal:
bool operator== (const Distance& first, const Distance& second)
{
    return !(strcmp(first.name, second.name));
}

//Not equal:
bool operator!= (const Distance& first, const Distance& second)
{
    return strcmp(first.name, second.name);
}

//Less than:
bool operator< (const Distance& first, const char* a_name)
{
    return strcmp(first.name, a_name) < 0;
}

//Greater than:
bool operator> (const Distance& first, const char* a_name)
{
    return strcmp(first.name, a_name) > 0;
}

//Less or equal:
bool operator<= (const Distance& first, const char* a_name)
{
    return strcmp(first.name, a_name) <= 0;
}

//Greater or equal:
bool operator>= (const Distance& first, const char* a_name)
{
    return strcmp(first.name, a_name) >= 0;
}

//Equal:
bool operator== (const Distance& first, const char* a_name)
{
    return !(strcmp(first.name, a_name));
}

//Not equal:
bool operator!= (const Distance& first, const char* a_name)
{
    return strcmp(first.name, a_name);
}

//Display:
void Distance::display(void) const
{
    std::cout << *this << std::endl;
}

//-----------------------------------Aquatic--------------------------------------------------------------
//Default constructor:
Aquatic::Aquatic() : Animal_scheduling()
{
    price = 0.0;
}

//Copy constructor:
Aquatic::Aquatic(const Aquatic& source) : Animal_scheduling(source)
{
    price = source.price;
}

//Destructor:
Aquatic::~Aquatic()
{
    price = 0.0;
}

//Set price:
void Aquatic::set_price(float a_price)
{
    price = a_price;
}

void Aquatic::input(void)
{
    char* new_name = new char[MAX_STREAM + 1];
    float new_price = 0.0;
    
    std::cout << "\nEnter the name of the aquatic animal activity: ";
    std::cin.get(new_name, MAX_STREAM, '\n');
    std::cin.clear();
    std::cin.ignore(MAX_STREAM, '\n');
    std::cout << "Enter the time of the aquatic viewing: ";
    std::getline(std::cin, time);
    std::cout << "Enter the price of the aquatic activity: ";
    while(!(std::cin >> new_price) || new_price < 0.0)
    {
        std::cout << "Invalid price. Enter valid price: ";
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');
    }
    std::cin.clear();
    std::cin.ignore(MAX_STREAM, '\n');

    set_price(new_price);
    set_name(new_name);

    delete [] new_name;
     
}

//Assignment operator. Copies source and returns reference to Aquatic:
Aquatic& Aquatic::operator= (const Aquatic& to_copy)
{
    if(this != &to_copy)
    {
        if(name)
        {
            delete [] name;
        }
        if(to_copy.name)
        {
            name = new char[strlen(to_copy.name) + 1];
            strcpy(name, to_copy.name);
        }
        time = to_copy.time;
        price = to_copy.price;
    }
    return *this;
}

//Insertion operator. Returns reference to ostream:
std::ostream& operator<< (std::ostream& out, const Aquatic& in)
{
    out << "Name: " << in.name << "\t\tTime: " << in.time << "\tPrice: " << std::fixed << std::setprecision(2) << in.price;
    return out;
}

//Display:
void Aquatic::display(void) const
{
    std::cout << *this << std::endl;
}
