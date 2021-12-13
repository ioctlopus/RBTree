/*
Scheduler wrapper class
Ben Rimedio - 11/17/2021
CS202 - Fall 2021
Instructor: Karla Fant
This is the wrapper client for the data structures. This class is meant to
generalize the three viewing activities for use in main().
*/

#ifndef SCHED_H
#define SCHED_H

#include "datastructures.h"

class Scheduler
{
public:
    Scheduler();
    Scheduler(const Scheduler& source);
    ~Scheduler();
    void insert_distance(void);
    void insert_aquatic(void);
    void insert_pettable(void);
    bool remove_aquatic(void);
    bool remove_pettable(void);
    bool remove_index_aquatic(void);
    bool remove_index_pettable(void);
    void display_distance(void);
    void display_aquatic(void);
    void display_pettable(void);

    Scheduler& operator= (const Scheduler& to_copy);
private:
    Tree distances;
    a_vect aquatics;
    p_vect pettables;
};

#endif
