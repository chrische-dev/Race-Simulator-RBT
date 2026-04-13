/******************************************************
 * File: racer.cpp
 * Author: Chris Chen
 * Program: CS302 Program #3 – Race Simulator
 *
 * Purpose:
 *    Implements the racer base class and all derived
 *    class behaviors (human, dog, monster). Includes
 *    constructors, overridden racing actions, and the
 *    clone function used for dynamic binding.
 ******************************************************/

#include "racer.h"

racer::racer() : name(""), stamina(0), speed(0){}

racer::racer(const string & name_input, const int & stamina_input, const int & speed_input) : name(name_input), stamina(stamina_input), speed(speed_input){}

racer::~racer(){}


string & racer::get_name()
{
    return name;
}


human::human() : hydration_level(0), snack(""){}

human::human(const string & name_input, const int & stamina_input, const int & speed_input, const int & hydration_input, const string & snack_input) : racer(name_input, stamina_input, speed_input), hydration_level(hydration_input), snack(snack_input){}

racer * human::clone() const
{
    return new human(*this); //returns a new created human object and copies the data that the pointer is pointing at inside of it
}

int human::move(int & distance)
{

    if(stamina == 0)
    {
        cout << name <<" must rest first you are too tired" <<endl;
    }
    else
    {
        speed +=1; //changed this
        cout << name <<" is moving at a speed of " << speed <<endl;
        stamina -= 10;
    }
        int distance_traveled = 0;
        distance_traveled += speed;  //changed this
        cout << name <<" has traveled " <<distance_traveled << " out of " << distance <<endl <<endl;
        return distance_traveled;

}

bool human::rest()
{   
    cout << name <<" ate a " << snack <<endl;
    stamina += 10; 
    cout << name <<" stamina is now at " << stamina <<endl;
    hydration_level += 20;
    cout << name <<" hydration level is now at " << hydration_level <<endl <<endl;
    return true;
    
}

bool human::special_ability() //we move faster with this so we need to limit how much we can let the user use it
{
    if(hydration_level >= 70)
    {
        cout <<  name << " special ability SPRINT BURST has activated!" <<endl;
        speed += 5;
        cout << name << " speed has been increased by 5!" <<endl <<endl;
        cout <<endl;
        hydration_level -= 30; //changed this
        return true;
    }

    else if(hydration_level < 70)
    {
        cout << name << " can't use special ability " << name << " is not hydrated enough" <<endl <<endl;
        return false;
    }


    return false;

}

bool human::display()
{
    cout << "The name of the human is " <<name <<endl;
    cout << "The stamina of the human is " <<stamina <<endl;
    cout << "The speed of the human is " <<speed <<endl;
    cout << "The hydration level of the human is " << hydration_level <<endl;
    cout << "The snack is " <<snack <<endl;
    return true;
}

bool human::taunt()
{
    cout << "Brains and legs beats barks and roars!" <<endl <<endl;
    return true;
}
    


human::~human(){}

dog::dog() : hunger_level(0), treat(""){}

dog::dog(const string & name_input, const int & stamina_input, const int & speed_input, const int & hunger_input, const string & treat_input) : racer(name_input, stamina_input, speed_input), hunger_level(hunger_input), treat(treat_input){}

racer * dog::clone() const
{
    return new dog(*this);
}

int dog::move(int & distance)
{

    if(stamina == 0)
    {
        cout << name << " must rest first you are too tired" <<endl;
    }
    else
    {
        speed += 2;
        cout << name <<" is moving at a speed of " << speed <<endl;
        stamina -= 10;
    }
        int distance_traveled = 0;
        distance_traveled += speed;

        cout << name <<" has traveled " << distance_traveled << " out of " << distance <<endl <<endl;
        return distance_traveled;
}

bool dog::rest()
{
    cout << "your owner fed you a " << treat <<endl;
    hunger_level += 10;
    stamina += 10; 
    cout << name <<" stamina is now at " << stamina <<endl <<endl;
    return true;
}

bool dog::special_ability()
{
    if(hunger_level >= 50)
    {
        cout << name <<" special ability AIR LEAP has activated!" <<endl;
        cout << name <<" your speed has been increased by 10!" <<endl;
        speed += 10;
        hunger_level -= 20;
        cout <<endl;
        return true;

    }
    else if(hunger_level < 50)
    {
        cout << name << " can't use special ability " << name <<" are too hungry" <<endl <<endl;
        return false;
    }
    return false;

}

bool dog::display()
{
    cout << "The name of the dog is " <<name <<endl;
    cout << "The stamina of the dog is " <<stamina <<endl;
    cout << "The speed of the dog is " <<speed <<endl;
    cout << "The hunger level of the dog is " << hunger_level <<endl;
    cout << "The treat is " <<treat <<endl;
    return true;
}

dog::~dog(){}

monster::monster() : destroyed_objects(0), threat_level(0) {}

monster::monster(const string & name_input, const int & stamina_input, const int & speed_input, const int & destroyed_input, const int & threat_input) : racer(name_input, stamina_input, speed_input), destroyed_objects(destroyed_input), threat_level(threat_input){}

racer * monster::clone() const
{
    return new monster(*this);
}

int monster::move(int & distance)
{

    if(stamina == 0)
    {
        cout << "You must rest first you are too tired" <<endl;
    }
    else
    {
        speed += 3;
        destroyed_objects += 2;
        threat_level += 2;
        stamina -= 5;
        
        cout << name << " has destroyed " << destroyed_objects << " building" <<endl;
        cout << "The monster's threat level is " << threat_level <<endl;
        cout << name <<" is moving at a speed of " << speed <<endl;
    }
        int distance_traveled = 0;
        distance_traveled += speed;
    
        cout << "you have traveled " << distance_traveled << " out of " << distance <<endl <<endl;
        return distance_traveled;
}

bool monster::rest()
{
    threat_level -= 1;
    stamina += 5;
    cout << "Monster stamina is now at " << stamina <<endl <<endl;
    return true;
}

bool monster::special_ability()
{
    if(threat_level > 2)
    {
        cout << name << " special ability ANGRY RAMPAGE has activated!" <<endl;
        cout << name << " speed has been increased by 15!" <<endl <<endl;
        threat_level -= 1;
        speed += 15;
        cout <<endl;
        return true;
    }

    else if(threat_level <= 2)
    {
        cout << name << " can't use special ability " <<name <<" haven't caused enough destruction" <<endl <<endl;
        return false;
    }
    return false;

}

bool monster::display()
{

    cout << "The name of the monster is " <<name <<endl;
    cout << "The stamina of the monster is " <<stamina <<endl;
    cout << "The speed of the monster is " <<speed <<endl;
    cout << "The amount of objects the monster has destroyed is " <<destroyed_objects <<endl;
    cout << "The threat level of the monster is " <<threat_level <<endl;
    return true;
}

monster::~monster(){}

