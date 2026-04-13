/******************************************************
 * File: rbt.h
 * Author: Chris Chen
 * Program: CS302 Program #3 – Race Simulator
 *
 * Purpose:
 *    Declares the Red-Black Tree used to store all
 *    racer objects. Supports recursive insert, display,
 *    removal, and operations that trigger racer actions
 *    through dynamic binding.
 ******************************************************/

#include "node.h"

class rbt
{
    public:
    rbt();
    rbt(node * source);
    ~rbt();
    bool insert(racer * ptr_to_add);
    int display_all();
    int remove(const string & name_input);
    int remove_all();
    


    int move_forward(const string & name_input, int & distance);
    bool rest_break(const string & name_input);
    bool sig_ability(const string & name_input);

    private:
    node * root;
    node * NIL;

    int copybst(node *& root, node * source);
    bool insert(node *& root, racer * ptr_to_add, node *& parent);
    int display_all(node * root);
    int remove(node *& root, const string & name_input);
    int remove_all(node *& root);
    node * ios(node *& root);
    bool leftRotation(node * x);
    bool rightRotation(node * y);


    int move_forward(node * root, const string & name_input, int & distance);
    bool rest_break(node * root, const string & name_input);
    bool sig_ability(node * root, const string & name_input);

};
