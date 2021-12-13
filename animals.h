/*
Program 3 Hierarchy
Ben Rimedio - 11/09/2021
CS202 - Fall 2021
Instructor: Karla Fant
This is the core hierarchy of animal scheduling classes.
There is a base class and three derived classes:
Pettable, Aquatic, and Distance.
*/

#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <string>

#define MAX_STREAM 1024

enum cmp_price {FIRST, EQUAL, SECOND};

class Animal_scheduling
{
public:
    Animal_scheduling();
    Animal_scheduling(const Animal_scheduling& source);
    ~Animal_scheduling();
    void set_name(char* a_name);
    void set_time(std::string& a_time);
    bool compare_name(char* a_name);
protected:
    char* name;
    std::string time;
};

class Pettable : public Animal_scheduling
{
public:
    Pettable();
    Pettable(const Pettable& source);
    ~Pettable();
    void display(void) const;
    void input(void);
    void set_price(float a_price);

    friend std::ostream& operator<< (std::ostream& out, const Pettable& to_display);
    Pettable& operator= (const Pettable& to_copy);
protected:
    float price;
};

class Aquatic : public Animal_scheduling
{
public:
    Aquatic();
    Aquatic(const Aquatic& source);
    ~Aquatic();
    void display(void) const;
    void input(void);
    void set_price(float a_price);

    friend std::ostream& operator<< (std::ostream& out, const Aquatic& in);
    Aquatic& operator= (const Aquatic& to_copy);
protected:
    float price;
};

class Distance : public Animal_scheduling
{
public:
    Distance();
    Distance(const Distance& source);
    ~Distance();
    void display(void) const;
    void input(void);
    void set_rate(float a_rate);
    void set_hours(unsigned int amt);

    friend std::ostream& operator<< (std::ostream& out, const Distance& in);
    Distance& operator= (const Distance& to_copy);
    friend bool operator< (const Distance& first, const Distance& second);
    friend bool operator> (const Distance& first, const Distance& second);
    friend bool operator>= (const Distance& first, const Distance& second);
    friend bool operator<= (const Distance& first, const Distance& second);
    friend bool operator== (const Distance& first, const Distance& second);
    friend bool operator!= (const Distance& first, const Distance& second);
    friend bool operator< (const Distance& first, const char* a_name);
    friend bool operator> (const Distance& first, const char* a_name);
    friend bool operator>= (const Distance& first, const char* a_name);
    friend bool operator<= (const Distance& first, const char* a_name);
    friend bool operator== (const Distance& first, const char* a_name);
    friend bool operator!= (const Distance& first, const char* a_name);

protected:
    float rate_hr;
    unsigned short hours;
};

#endif
