/******************************************************
 * File: racer.h
 * Author: Chris Chen
 * Program: CS302 Program #3 – Race Simulator
 *
 * Purpose:
 *    Declares the abstract base class 'racer' and the
 *    derived classes (human, dog, monster). Provides
 *    the virtual interface used for dynamic binding
 *    and RTTI across all racer types.
 ******************************************************/

#ifndef RACER_H
#define RACER_H

#include <iostream>
#include <string>
using namespace std;

// Chris Chen, chrische@pdx.edu, CS302 Program #3

class racer
{
    public:
    racer();
    racer(const string & name_input, const int & stamina_input, const int & speed_input);
    virtual ~racer();
    virtual racer * clone() const = 0;
    virtual int move(int & distance) = 0;              //virtual = 0 means this is a pure virtual function //that can be overriden by dervied class
    virtual bool rest() = 0;             //functions and  = 0 means there is no body
    virtual bool special_ability() = 0; 
    virtual bool display() = 0;
    string & get_name();
                                        
                                        //even if we had only one pure virtual function this class still cannot be made into a 
                                        //object in main because it will be considered a abstract class so no racer obj; in main()
                                        
    protected:
    string name;
    int stamina;
    int speed;

};

class human : public racer
{
    public:
    human();
    human(const string & name_input, const int & stamina_input, const int & speed_input, const int & hydration_input, const string & snack_input);
    ~human();
    racer * clone() const override;
    int move(int & distance) override;             //these functions will overide the pure virtual ones in the base class
    bool rest() override;
    bool special_ability() override;
    bool display() override;
    bool taunt();
    


    private:
    int hydration_level;
    string snack;
};

class dog : public racer
{
    public:
    dog();
    dog(const string & name_input, const int & stamina_input, const int & speed_input, const int & hunger_input, const string & treat_input);
    ~dog();
    racer * clone() const override;
    int move(int & distance) override;
    bool rest() override;
    bool special_ability() override;
    bool display() override;

    private:
    int hunger_level;
    string treat;


};

class monster : public racer
{
    public: 
    monster();
    monster(const string & name_input, const int & stamina_input, const int & speed_input, const int & destroyed_input, const int & threat_input);
    ~monster();
    racer * clone() const override;
    int move(int & distance) override;
    bool rest() override;
    bool special_ability() override;
    bool display() override;

    private:
    int destroyed_objects;
    int threat_level;


};
    
#endif


