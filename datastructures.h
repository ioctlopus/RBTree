/*
Data structures for Program 3
Ben Rimedio - 11/10/2021
CS202 - Fall 2021
Instructor: Karla Fant
This is the interface for the data structures (clients) for Program 3.
The tree has a root d_node and supports insert, remove, display, and retrieve.
*/

#ifndef DATA_H
#define DATA_H

#include <vector>

#include "animals.h"

#define RED 0
#define BLACK 1
#define LEFT 0
#define RIGHT 1
#define NUM_CHILDREN 2

//Node for Tree:
class d_node : public Distance
{
public:
    d_node();
    d_node(const d_node& source);
    d_node(d_node* source, d_node* l_ptr, d_node* r_ptr);
    ~d_node();
    d_node*& go_left(void);
    d_node*& go_right(void);
    d_node*& go(bool dir);
    unsigned short get_color(void);
    void set_left(d_node* a_d_node);
    void set_right(d_node* a_d_node);
    void set(bool dir, d_node* a_d_node);
    void set_color(char a_color);
    bool is_red(void);
    void change_color(void);
    void copy_data(d_node*& a_node);
protected:
    d_node** children;

    unsigned short color;
};

//Tree class:
class Tree
{
public:
    Tree();
    Tree(const Tree& source);
    ~Tree();
    void destroy_tree(d_node*& curr_root);
    void insert(d_node*& to_add);
    void insert(void);
    d_node* copy(d_node* a_root);
    void display(void) const;
    
    Tree& operator= (const Tree& to_copy);
    Tree& operator+= (d_node*& to_add);
protected:
    d_node* root;

    d_node* r_retrieve(d_node*& a_root, char*& a_name);
    void r_display(d_node* a_root) const;
    d_node* insert_help(d_node* a_root, d_node* to_insert);
    d_node* retrieve(char* a_name);
    d_node* rotate(d_node*& a_node, bool dir);
    d_node* double_rotate(d_node*& a_node, bool dir);
    d_node* insert_fix(d_node* a_root, bool dir);
};

class a_vect
{
public:
    a_vect();
    a_vect(const a_vect& source);
    ~a_vect();
    void insert(void);
    bool remove(void);
    bool remove(char* a_name);
    bool remove(size_t ind, Aquatic* rem);
    void display(void);

    a_vect& operator= (const a_vect& to_copy);
    Aquatic*& operator[] (long unsigned int ind);
protected:
    std::vector<Aquatic*> data;
};

class p_vect
{
public:
    p_vect();
    p_vect(const p_vect& source);
    ~p_vect();
    void insert(void);
    bool remove(void);
    bool remove(char* a_name);
    bool remove(size_t ind, Pettable* rem);
    void display(void);

    p_vect& operator= (const p_vect& to_copy);
    Pettable*& operator[] (long unsigned int ind);
protected:
    std::vector<Pettable*> data;
};

#endif
