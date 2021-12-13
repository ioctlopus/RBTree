/*
Main driver for Program 3.
Ben Rimedio - 11/11/2021
CS202 - Fall 2021
Instructor: Karla Fant
This is the main driver file for Program 3. There is a simple menu implemented.
From this menu, the user can create and schedule animal viewing activities.
*/

#include <cstdlib>
#include "scheduler.h"

int main(void)
{
    int ret = EXIT_SUCCESS;
    char choice = '\0';
    Scheduler schedules, copied;

    std::cout << "\nWelcome!\n" << std::endl;

    while(toupper(choice) != 'Q')
    {
        std::cout << "Schedule:\n (P)ettable animal viewing\n (A)quatic animal viewing\n (D)istance animal viewing\n"
                  << "Remove:\n P(e)ttable viewing\n Aq(u)atic viewing\n"
                  << "Display:\n (1) Pettable viewings\n (2) Aquatic viewings\n (3) Distance viewings\n"
                  << "Remove by index:\n (4) Aquatic viewing\n (5) Pettable viewing\n(C)opy schedules and display test.\n"
                  << "(Q)uit\n>>> ";
        try
        {
            std::cin >> choice;
            if(!std::cin)
                throw EXIT_FAILURE;
        }
        catch(int err)
        {
            std::cin.clear();
            std::cin.ignore(MAX_STREAM, '\n');
            std::cerr << "\n\nStandard input stream ended unexpectedly. Exiting...\n" << std::endl;
            exit(err);
        }
        std::cin.clear();
        std::cin.ignore(MAX_STREAM, '\n');

        switch(toupper(choice))
        {
            case 'P':
                schedules.insert_pettable();
                std::cout << std::endl;
                break;
            case 'D':
                schedules.insert_distance();
                std::cout << std::endl;
                break;
            case 'A':
                schedules.insert_aquatic();
                std::cout << std::endl;
                break;
            case 'E':
                try
                {
                    if(!schedules.remove_pettable())
                        throw false;
                    std::cout << "\nRemoval successful.\n";
                }
                catch(bool err)
                {
                    std::cerr << "\nName not found. Nothing removed.\n";
                }
                std::cout << std::endl;
                break;
            case 'U':
                try
                {
                    if(!schedules.remove_aquatic())
                        throw false;
                    std::cout << "Removal successful.\n";
                }
                catch(bool err)
                {
                    std::cerr << "\nName not found. Nothing removed.\n";
                }
                std::cout << std::endl;
                break;
            case '1':
                std::cout << std::endl << "===================================================================\n";
                std::cout << "               Pettable viewing activities\n";
                std::cout << "===================================================================" << std::endl;
                schedules.display_pettable();
                std::cout << "===================================================================\n" << std::endl;
                break;
            case '2':
                std::cout << std::endl << "===================================================================\n";
                std::cout << "               Aquatic viewing activities\n";
                std::cout << "===================================================================" << std::endl;
                schedules.display_aquatic();
                std::cout << "===================================================================\n" << std::endl;
                break;
            case '3':
                std::cout << std::endl << "===================================================================\n";
                std::cout << "               Distance viewing activities\n";
                std::cout << "===================================================================" << std::endl;
                schedules.display_distance();
                std::cout << "===================================================================\n" << std::endl;
                break;
            case '4':
                try
                {
                    if(!schedules.remove_index_aquatic())
                        throw false;
                    std::cout << "Removal successful";
                }
                catch(bool err)
                {
                    std::cerr << "\nIndex not found. Nothing removed.\n";
                }
                std::cout << std::endl;
                break;
            case '5':
                try
                {
                    if(!schedules.remove_index_pettable())
                        throw false;
                    std::cout << "Removal successful";
                }
                catch(bool err)
                {
                    std::cerr << "\nIndex not found. Nothing removed.\n";
                }
                std::cout << std::endl;
                break;
            case 'C':
                copied = schedules;
                std::cout << std::endl << "Pettables:\n";
                copied.display_pettable();
                std::cout << std::endl << "Aquatics:\n";
                copied.display_aquatic();
                std::cout << std::endl << "Distances:\n";
                copied.display_distance();
                std::cout << std::endl;
                break;
            case 'Q':
                std::cout << "\nGoodbye!\n" << std::endl;
                break;
            default:
                std::cout << "\nInvalid choice.\n" << std::endl;
                break;
        }
    }

    return ret;
}
