/*
Scheduler implementation
Ben Rimedio - 11/17/2021
CS202 - Fall 2021
Instructor: Karla Fant
This is the implementation of the Scheduler client class.
*/

#include "scheduler.h"

//Default constructor:
Scheduler::Scheduler() {}

//Copy constructor:
Scheduler::Scheduler(const Scheduler& source)
{
    distances = source.distances;
    pettables = source.pettables;
    aquatics = source.aquatics;
}

//Destructor:
Scheduler::~Scheduler() {}

//Assignment operator:
Scheduler& Scheduler::operator= (const Scheduler& to_copy)
{
    if(this != &to_copy)
    {
        distances = to_copy.distances;
        pettables = to_copy.pettables;
        aquatics = to_copy.aquatics;
    }
    return *this;
}

//Input and insert distance:
void Scheduler::insert_distance(void)
{
    distances.insert();
}

//Input and insert aquatic:
void Scheduler::insert_aquatic(void)
{
    aquatics.insert();
}

//Input and insert pettable:
void Scheduler::insert_pettable(void)
{
    pettables.insert();
}

//Input and remove aquatic:
bool Scheduler::remove_aquatic(void)
{
    return aquatics.remove();
}

//Input and remove pettable:
bool Scheduler::remove_pettable(void)
{
    return pettables.remove();
}

//Input and remove aquatic by index:
bool Scheduler::remove_index_aquatic(void)
{
    size_t to_remove;
    try
    {
        std::cout << "Which index would you like to remove?: ";
        std::cin >> to_remove;
        if(!std::cin)
            throw false;
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');
        return aquatics.remove(to_remove, aquatics[to_remove]);
    }
    catch(bool err)
    {
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');
        return err;
    }
}

//Input and remove pettable by index:
bool Scheduler::remove_index_pettable(void)
{
    size_t to_remove;
    try
    {
        std::cout << "Which index would you like to remove?: ";
        std::cin >> to_remove;
        if(!std::cin)
            throw false;
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');
        return pettables.remove(to_remove, pettables[to_remove]);
    }
    catch(bool err)
    {
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');
        return err;
    }

}

//Display distances:
void Scheduler::display_distance(void)
{
    distances.display();
}

//Display aquatics:
void Scheduler::display_aquatic(void)
{
    aquatics.display();
}

//Display pettables:
void Scheduler::display_pettable(void)
{
    pettables.display();
}
