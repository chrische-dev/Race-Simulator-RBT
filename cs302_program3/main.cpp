/******************************************************
 * File: main.cpp
 * Author: Chris Chen
 * Program: CS302 Program #3 – Race Simulator
 *
 * Purpose:
 *    Driver for the race application. Creates the
 *    Red-Black Tree of racers, lets the user select a
 *    racer, and manages menu input with exception
 *    handling. Demonstrates dynamic binding by using
 *    base-class pointers for all racer types.
 ******************************************************/
#include "racer.h"
#include "rbt.h"
#include <cstdlib>  
#include <ctime>

int main()
{  
    //let user create their own character possibly
    //display all the racers to choose from
    //ask who the user want to play as and let them make choices such as move, rest, and use their super
    //we will use random num generator 1-3 for the choice of the other racer bots

    rbt list;

    int distance = 100;

    //may make 3 different distance traveled for human, dog, and monster and pass in the move function

    racer * ptr = new human("chris", 100, 10, 100, "puff bar");
    racer * ptr2 = new dog("rico", 150, 15, 100, "Chicken chips");
    racer * ptr3 = new monster("godzilla", 100, 5, 0, 0);
    list.insert(ptr);
    list.insert(ptr2);
    list.insert(ptr3);

    int choice = 0;

    while(choice != 4)
    {
        srand(time(0));           
        int bot = rand() % 3 + 1;

        try
        {
            cout << "1. human" <<endl;
            cout << "2. dog" <<endl;
            cout << "3. monster" <<endl;
            cout << "4. quit" <<endl;
            cout << "choose your racer: ";
            cin >> choice;
            cout << endl;

            if (!cin || choice < 1 || choice > 4)
            {
                cin.clear();
                cin.ignore(100, '\n');
                throw invalid_argument("Input must be a number between 1 and 4");
            }
        }

            catch(const invalid_argument &e)
            {
                cout << "Error: " << e.what() << endl;
                choice = 0;
            }


            if(choice == 1)
            {
                int h_choice = 0;

                while(h_choice != 4)
                {

                    try
                    {
                        cout << "Below are you moves you can do choose wisely to win the race!" <<endl;
                        cout << "1. move forward" <<endl;
                        cout << "2. rest" <<endl;
                        cout << "3. use your special ability Sprint Burst" <<endl;
                        cout << "4. quit the race :(" <<endl;
                        cout << "what move will you make: ";
                        cin >> h_choice;
                        cout << endl;

                        if (!cin || h_choice < 1 || h_choice > 4)
                        {
                            cin.clear();
                            cin.ignore (100,'\n');
                            throw invalid_argument("Input must be a number between 1 and 4");
                        }
                    }

                    catch(const invalid_argument &e)
                    {
                        cout << "Error: " << e.what() << endl;
                        cin.clear();
                        cin.ignore(100, '\n');
                        h_choice = 0;
                        continue;
                    }


                    if(h_choice == 1)
                    {
                        int distance_traveled = list.move_forward("chris", distance);

                        if(distance_traveled >= distance)
                        {
                            cout << "You won the race!" <<endl <<endl;

                            human * h_ptr = dynamic_cast<human*>(ptr); //if ptr is pointing at human obj then change its racer * type to human * type
                                                                       // if ptr is not pointing ata human obj then h_ptr is pointing at null
                            if(h_ptr != nullptr)
                            {
                                h_ptr->taunt();
                            }
                            else
                            {
                                cout << "taunt failed!" << endl;
                            }
                            choice = 4;
                            break;
                        }

                    }

                    if(h_choice == 2)
                    {
                        list.rest_break("chris");
                    }

                    if(h_choice ==3)
                    {
                        list.sig_ability("chris");
                    }

                    int dog_move = rand() % 3 + 1;
                    int monster_move = rand() % 3 + 1;

                    if(dog_move == 1)
                    {
                        int d_traveled = list.move_forward("rico", distance);

                        if(d_traveled >= distance)
                        {
                            cout <<" You lost!" <<endl;
                            cout << "dog won the race!" <<endl <<endl;
                            choice = 4;
                            break;
                        }
                    }


                    else if(dog_move == 2)
                        list.rest_break("rico");

                    else
                        list.sig_ability("rico");

                    if(monster_move == 1)
                    {
                        int m_traveled = list.move_forward("godzilla", distance);

                        if(m_traveled >= distance)
                        {
                            cout << "You lost!" <<endl;
                            cout << "monster won the race!" <<endl <<endl;
                            choice = 4;
                            break;
                        }
                    }

                    else if(monster_move == 2)
                        list.rest_break("godzilla");

                    else
                        list.sig_ability("godzilla");

                }

            }

            if(choice == 2)
            {

                int d_choice = 0;

                while(d_choice != 4)
                {

                    try
                    {

                        cout << "Below are you moves you can do choose wisely to win the race!" <<endl;
                        cout << "1. move forward" <<endl;
                        cout << "2. rest" <<endl;
                        cout << "3. use your special ability Air Leap" <<endl;
                        cout << "4. quit the race :(" <<endl;
                        cout << "what move will you make: ";
                        cin >> d_choice;
                        cout <<endl;

                    
                        if (!cin || d_choice < 1 || d_choice > 4)
                        {
                            cin.clear();
                            cin.ignore (100,'\n');
                            throw invalid_argument("Input must be a number between 1 and 4");
                        }
                    }

                    catch(const invalid_argument &e)
                    {
                        cout << "Error: " << e.what() << endl;
                        cin.clear();
                        cin.ignore(100, '\n');
                        d_choice = 0;
                        continue;
                    }


                    if(d_choice == 1)
                    {
                        int distance_traveled = list.move_forward("rico", distance);

                        if(distance_traveled >= distance)
                        {
                            cout << "You won the race!" <<endl <<endl;
                            choice = 4;
                            break;
                        }
                    }

                    if(d_choice == 2)
                    {
                        list.rest_break("rico");
                    }

                    if(d_choice == 3)
                    {
                        list.sig_ability("rico");
                    }

                    int human_move = rand() % 3 + 1;
                    int monster_move = rand() % 3 + 1;

                    if(human_move == 1)
                    {
                        int h_traveled = list.move_forward("chris", distance);

                        if(h_traveled >= distance)
                        {
                            cout <<"You lost!" <<endl;
                            cout << "Human won the race!" <<endl <<endl;
                            choice = 4;
                            break;
                        }
                    }

                    else if(human_move == 2)
                        list.rest_break("chris");

                    else
                        list.sig_ability("chris");

                    if(monster_move == 1)
                    {
                        int m_traveled = list.move_forward("godzilla", distance);

                        if(m_traveled >= distance)
                        {
                            cout << "You lost!" <<endl;
                            cout << "Monster won the race!" <<endl <<endl;
                            choice = 4;
                            break;
                        }
                    }

                    else if(monster_move == 2)
                        list.rest_break("godzilla");

                    else
                        list.sig_ability("godzilla");
                }

            }

            if(choice == 3)
            {

                int m_choice = 0;

                while(m_choice != 4)
                {

                    try
                    {

                        cout << "Below are you moves you can do choose wisely to win the race!" <<endl;
                        cout << "1. move forward" <<endl;
                        cout << "2. rest" <<endl;
                        cout << "3. use your special ability Angry Rampage " <<endl;
                        cout << "4. quit the race :(" <<endl;
                        cout << "what move will you make: ";
                        cin >> m_choice;
                        cout <<endl;

                        
                        if (!cin || m_choice < 1 || m_choice > 4)
                        {
                            cin.clear();
                            cin.ignore (100,'\n');
                            throw invalid_argument("Input must be a number between 1 and 4");
                        }
                    }

                    catch(const invalid_argument &e)
                    {
                        cout << "Error: " << e.what() << endl;
                        cin.clear();
                        cin.ignore(100, '\n');
                        m_choice = 0;
                        continue;
                    }



                    if(m_choice == 1)
                    {
                        int distance_traveled = list.move_forward("godzilla", distance);

                        if(distance_traveled >= distance)
                        {
                            cout << "You won the race!" <<endl <<endl;
                            choice = 4;
                            break;
                        }
                    }

                    if(m_choice == 2)
                    {
                        list.rest_break("godzilla");
                    }

                    if(m_choice == 3)
                    {
                        list.sig_ability("godzilla");
                    }

                    int human_move = rand() % 3 + 1;
                    int dog_move = rand() % 3 + 1;

                    if(human_move == 1)
                    {   
                        int h_traveled = list.move_forward("chris", distance);

                        if(h_traveled >= distance)
                        {
                            cout <<"You lost!" <<endl;
                            cout << "Human won the race!" <<endl <<endl;
                            choice = 4;
                            break;
                        }
                    }

                    else if(human_move == 2)
                        list.rest_break("chris");

                    else
                        list.sig_ability("chris");

                    if(dog_move == 1)
                    {
                        int d_traveled = list.move_forward("rico", distance);

                        if(d_traveled >= distance)
                        {
                            cout <<"You lost!" <<endl;
                            cout << "dog won the race!" <<endl <<endl;
                            choice = 4;
                            break;
                        }
                    }

                    else if(dog_move == 2)
                        list.rest_break("rico");

                    else
                        list.sig_ability("rico");
                }
            }
        }


        /*
           list.display_all();

           list.remove("chris");

           cout << "---------------------";
           list.display_all();
         */



        return 0;
    }
