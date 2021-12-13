/*
Data structure methods for Program 3
Ben Rimedio - 11/10/2021
CS202 - Fall 2021
Instructor: Karla Fant
These are the implementations of the methods for the data structures (clients) in
Program 3. There are methods for both the d_node class and the Tree class. The tree is organized by name.
This implementation is a red-black tree using one color flag per node.
Color and direction are represented as 0 and 1 in order to easily perform boolean
and arithmetic operations on them. Nodes contain an array of two pointers, representing
the left and right child. The tree is used to store Distance animal viewing activities.
Additionally, two small classes are used to encapsulate and simplify operations on 
the vector-centered classes representing Pettable and Aquatic activities.
*/

#include "datastructures.h"

//------------------------------------------d_node-------------------------------------------------------
//Default constructor:
d_node::d_node() : Distance()
{
    children = new d_node*[NUM_CHILDREN];
    children[LEFT] = nullptr;
    children[RIGHT] = nullptr;
    color = BLACK;
}

//Copy constructor:
d_node::d_node(const d_node& source) : Distance(source)
{
    children = new d_node*[NUM_CHILDREN];
    children[LEFT] = nullptr;
    children[RIGHT] = nullptr;
    color = BLACK;
}

//Constructor with children arguments:
d_node::d_node(d_node* source, d_node* l_ptr, d_node* r_ptr) : Distance(*source)
{
    children = new d_node*[NUM_CHILDREN];
    children[LEFT] = l_ptr;
    children[RIGHT] = r_ptr;
    color = source->get_color();
}

//Destructor:
d_node::~d_node()
{
    delete [] children;
    children = nullptr;
    color = BLACK;
}

//Return reference to left:
d_node*& d_node::go_left(void)
{
    return children[LEFT];
}

//Return reference to right:
d_node*& d_node::go_right(void)
{
    return children[RIGHT];
}

//Return reference to arbitrary child based on direction argument:
d_node*& d_node::go(bool dir)
{
    return children[dir];
}

//Copy data only into new node:
void d_node::copy_data(d_node*& a_node)
{
    time = a_node->time;
    rate_hr = a_node->rate_hr;
    hours = a_node->hours;
    if(a_node->name)
        set_name(a_node->name);
}

//Get color:
unsigned short d_node::get_color(void)
{
    return color;
}

//Check if node is red:
bool d_node::is_red(void)
{
    return color == RED;
}

//Flip color:
void d_node::change_color(void)
{
    color = color ^ 1;
    if(go_left())
        go_left()->set_color(go_left()->get_color() ^ 1);
    if(go_right())
        go_right()->set_color(go_right()->get_color() ^ 1);
}

//Set left d_node:
void d_node::set_left(d_node* a_d_node)
{
    children[LEFT] = a_d_node;
}

//Set right d_node:
void d_node::set_right(d_node* a_d_node)
{
    children[RIGHT] = a_d_node;
}

//Set arbitrary child based on direction argument:
void d_node::set(bool dir, d_node* a_d_node)
{
    try
    {
        if(dir != LEFT && dir != RIGHT)
            throw false;
        if(dir == LEFT)
            set_left(a_d_node);
        else if(dir == RIGHT)
            set_right(a_d_node);
    }
    catch(bool err)
    {
        std::cerr << "\n\nInvalid direction...\n" << std::endl;
        return;
    }
}

//Set color:
void d_node::set_color(char a_color)
{
    color = a_color;
}

//--------------------------------------------Tree-----------------------------------------------------
//Default constructor:
Tree::Tree()
{
    root = nullptr;
}

//Assignment operator:
Tree& Tree::operator= (const Tree& to_copy)
{
    if(this != &to_copy)
    {
        destroy_tree(root);
        root = copy(to_copy.root);
    }
    return *this;
}

//Copy constructor. Note that this takes advantage of the assignment operator:
Tree::Tree(const Tree& source)
{
    d_node* start = source.root;
    root = copy(start);
}

//Destructor:
Tree::~Tree()
{
    destroy_tree(root);
    root = nullptr;
}

//+= operator:
Tree& Tree::operator+= (d_node*& to_add)
{
    insert(to_add);
    return *this;
}

//Deep copy:
d_node* Tree::copy(d_node* a_root)
{
    if(!a_root)
        return nullptr;
    return new d_node(a_root, copy(a_root->go_left()), copy(a_root->go_right()));
}

//Remove all:
void Tree::destroy_tree(d_node*& curr_root)
{
    if(!curr_root)
        return;
    destroy_tree(curr_root->go_left());
    destroy_tree(curr_root->go_right());
    delete curr_root;
    curr_root = nullptr;
}

//Rotate based on direction argument. Return node:
d_node* Tree::rotate(d_node*& a_node,  bool dir)
{
    d_node* result = a_node->go(!dir);
    a_node->set(!dir, result->go(dir));
    result->set(dir, a_node);
    result->set_color(a_node->get_color());
    a_node->set_color(RED);
    return result;
}

//Double rotation:
d_node* Tree::double_rotate(d_node*& a_node, bool dir)
{
    a_node->set(!dir, rotate(a_node->go(!dir), !dir));
    return rotate(a_node, dir);
}

//Insert new:
void Tree::insert(void)
{
    std::cout << std::endl;
    d_node* new_node = new d_node;
    new_node->input();
    *this += new_node;
}

//Insert by node:
void Tree::insert(d_node*& a_node)
{
    try
    {
        if(!a_node)
            throw nullptr;
        if(!root)
            root = a_node;
        else
            root = insert_help(root, a_node);
        root->set_color(BLACK);
    }
    catch(d_node* err)
    {
        std::cerr << "\n\nEmpty node error...\n" << std::endl;
        return;
    }
}

//Helper for insert. Returns node:
d_node* Tree::insert_help(d_node* a_root, d_node* to_insert)
{
    if(!a_root)
        return to_insert;
    bool direction = (*to_insert >= *a_root);
    a_root->set(direction, insert_help(a_root->go(direction), to_insert));
    return insert_fix(a_root, direction);
}

//Fix coloring and balance after an insertion:
d_node* Tree::insert_fix(d_node* a_root, bool dir)
{
    if(a_root && a_root->go(dir) && a_root->go(dir)->is_red())
    {
        //Both children red:
        if(a_root->go(!dir) && a_root->go(!dir)->is_red())
        {
            if(a_root->go(dir)->go(dir)->is_red() || a_root->go(dir)->go(!dir)->is_red())
                a_root->change_color();
        }
        //Both children black:
        else
        {
            if(a_root->go(dir)->go(dir) && a_root->go(dir)->go(dir)->is_red())
            {
                a_root = rotate(a_root, !dir);
            }
            //Child has two reds together:
            else if(a_root->go(dir)->go(!dir) && a_root->go(dir)->go(!dir)->is_red())
            {
                a_root = double_rotate(a_root, !dir);
            }
        }

    }
    return a_root;
}


//Return node based on name argument:
d_node* Tree::retrieve(char* a_name)
{
    d_node* ret = nullptr;
    if(!a_name)
        return ret;
    ret = r_retrieve(root, a_name);
    return ret;
}

//Wrapper for recursive display:
void Tree::display(void) const
{
    r_display(root);
}

//Recursive display:
void Tree::r_display(d_node* a_root) const
{
    if(!a_root)
        return;
    r_display(a_root->go_left());
    std::cout << *a_root << std::endl;
    r_display(a_root->go_right());
}

//Recursive retrieval:
d_node* Tree::r_retrieve(d_node*& a_root, char*& a_name)
{
    if(!a_root)
    {
        return nullptr;
    }
    else if(*a_root == a_name)
    {
        return a_root;
    }
    else if(*a_root < a_name)
    {
        return a_root->go_right();
    }
    else
    {
        return a_root->go_left();
    }
}

//----------------------------------------------------a_vect---------------------------------------------------------
//Default constructor:
a_vect::a_vect()
{
    data.clear();
}

//Copy constructor:
a_vect::a_vect(const a_vect& source)
{
    for(size_t i = 0; i < source.data.size(); ++i)
    {
        Aquatic* new_aq = new Aquatic(*(source.data[i]));
        data.push_back(new_aq);
    }
}

//Destructor:
a_vect::~a_vect()
{
    for(size_t i = 0; i < data.size(); ++i)
        delete data[i];
    data.clear();
}

//Assignment operator:
a_vect& a_vect::operator= (const a_vect& to_copy)
{
    if(this != &to_copy)
    {
        for(size_t i = 0; i < to_copy.data.size(); ++i)
        {
            Aquatic* new_aq = new Aquatic(*(to_copy.data[i]));
            data.push_back(new_aq);
        }
    }
    return *this;
}

//Return indexed Aquatic pointer:
Aquatic*& a_vect::operator[] (long unsigned int ind)
{
    try{
        if(!data[ind])
            throw data[ind];
        return data[ind];
    }
    catch(Aquatic*& err)
    {
        std::cerr << "\nEmpty member.\n" << std::endl;
        return err;
    }
}

//Insert based on user input:
void a_vect::insert(void)
{
    Aquatic* to_add = new Aquatic;
    to_add->input();
    data.push_back(to_add);
}

//Remove based on user input. Returns true if removal is successful:
bool a_vect::remove(void)
{
    char* rem_name = new char[MAX_STREAM + 1];
    bool ret = false;

    std::cout << "\nWhat aquatic activity would you like to remove?: ";
    std::cin.get(rem_name, MAX_STREAM, '\n');
    ret = remove(rem_name);

    delete [] rem_name;
    return ret;
}

//Remove based on name. Returns true if removal is successful:
bool a_vect::remove(char* a_name)
{
    for(size_t i = 0; i < data.size(); ++i)
    {
        if(data[i]->compare_name(a_name))
        {
            delete data[i];
            data.erase(data.begin() + i);
            return true;
        }
    }
    return false;
}

//Remove by index:
bool a_vect::remove(size_t ind, Aquatic* rem)
{
    try{
        if(ind >= data.size())
            throw false;
        delete rem;
        data.erase(data.begin() + ind);
        return true;
    }
    catch(bool err)
    {
        return err;
    }
}

//Display:
void a_vect::display(void)
{
    for(size_t i = 0; i < data.size(); ++i)
        std::cout << *(data[i]) << std::endl;
}
//----------------------------------------------------p_vect---------------------------------------------------------
//Default constructor:
p_vect::p_vect()
{
    data.clear();
}

//Copy constructor:
p_vect::p_vect(const p_vect& source)
{
    for(size_t i = 0; i < source.data.size(); ++i)
    {
        Pettable* new_pet = new Pettable(*(source.data[i]));
        data.push_back(new_pet);
    }
}

//Destructor:
p_vect::~p_vect()
{
    for(size_t i = 0; i < data.size(); ++i)
        delete data[i];
    data.clear();
}

//Assignment operator:
p_vect& p_vect::operator= (const p_vect& to_copy)
{
    if(this != &to_copy)
    {
        for(size_t i = 0; i < to_copy.data.size(); ++i)
        {
            Pettable* new_pet = new Pettable(*(to_copy.data[i]));
            data.push_back(new_pet);
        }
    }
    return *this;
}

//Return indexed Pettable pointer:
Pettable*& p_vect::operator[] (long unsigned int ind)
{
    try
    {
        if(!data[ind])
            throw data[ind];
        return data[ind];
    }
    catch(Pettable*& err)
    {
        std::cerr << "\nEmpty member.\n" << std::endl;
        return err;
    }
}

//Insert by prompting user:
void p_vect::insert(void)
{
    Pettable* to_add = new Pettable;
    to_add->input();
    data.push_back(to_add);
}

//Remove based on user input. Returns true if removal is successful:
bool p_vect::remove(void)
{
    char* rem_name = new char[MAX_STREAM + 1];
    bool ret = false;

    std::cout << "\nWhat petting activity would you like to remove?: ";
    std::cin.get(rem_name, MAX_STREAM, '\n');
    ret = remove(rem_name);

    delete [] rem_name;
    return ret;
}

//Remove by index:
bool p_vect::remove(size_t ind, Pettable* rem)
{
    try{
        if(ind >= data.size())
            throw false;
        delete rem;
        data.erase(data.begin() + ind);
        return true;
    }
    catch(bool err)
    {
        return err;
    }
}

//Remove based on name. Returns true if removal is successful:
bool p_vect::remove(char* a_name)
{
    for(size_t i = 0; i < data.size(); ++i)
    {
        if(data[i]->compare_name(a_name))
        {
            delete data[i];
            data.erase(data.begin() + i);
            return true;
        }
    }
    return false;
}

//Display:
void p_vect::display(void)
{
    for(size_t i = 0; i < data.size(); ++i)
        std::cout << *(data[i]) << std::endl;
}
