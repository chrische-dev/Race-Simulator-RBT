/******************************************************
 * File: node.cpp
 * Author: Chris Chen
 * Program: CS302 Program #3 – Race Simulator
 *
 * Purpose:
 *    Implements the RBT node functions, including
 *    constructors, setters/getters, and color/parent
 *    manipulation used during tree balancing.
 ******************************************************/

#include "node.h"

node::node() : class_ptr(nullptr), left(nullptr), right(nullptr), parent(nullptr), color(RED){}

node::node(racer * ptr_to_add) : class_ptr(ptr_to_add), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}

node::~node()
{
    class_ptr = nullptr;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

int node::setLeft(node *& left)
{
    this->left = left;
    return 0;
}

int node::setRight(node *& right)
{
    this->right = right;
    return 0;
}

int node::setParent(node * parent)
{
    this->parent = parent;
    return 0;
}

int node::setColor(Color color)
{
    this->color = color;
    return 0;
}

node*& node::getLeft()
{
    return left;
}

node*& node::getRight()
{
    return right;
}

node*& node::getParent()
{
    return parent;
}

Color node::getColor() const
{
    return color;
}

racer*& node::get_class_ptr()
{
    return class_ptr;
}

node & node::operator=(node * source)
{
    if(this == source)
        return *this;

    if(class_ptr != nullptr)
        delete class_ptr;

    if(source->class_ptr != nullptr)
        class_ptr = source->get_class_ptr()->clone();

    return *this;
}
