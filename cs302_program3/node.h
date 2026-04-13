/******************************************************
 * File: node.h
 * Author: Chris Chen
 * Program: CS302 Program #3 – Race Simulator
 *
 * Purpose:
 *    Defines the RBT node class used to store pointers
 *    to racer objects. Each node keeps track of its
    left, right, parent links and color for balancing.
 ******************************************************/

 #include "racer.h"

enum Color
{
    BLACK,
    RED
};


class node
{
    public:
        node();
        node(racer * ptr_to_add); //ex. racer * new_racer = new dog(), we create a object in main and then we pass the ptr* to the constructor 
                                  //so the new node we create is pointing at a dog object, and we can access its public using ->
                                  //now we have a node that has a pointer inside of it that points to the dog object
        ~node();
        int setLeft(node *& left);
        int setRight(node *& right);
        int setColor(Color color);
        int setParent(node * parent);
        node*& getParent();
        Color getColor() const;
        node & operator=(node * source);
        node *& getLeft();
        node *& getRight();
        racer *& get_class_ptr();

    private:
        racer * class_ptr; //racer * ptr will be able to point at any derived class since they are all inherited racers, racer * ptr = new dog
        node * left; // in main we use ptr->function() to call any function in the class we are pointing at
        node * right;
        node * parent; //parent pointer
        Color color;

};


