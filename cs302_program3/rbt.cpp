/******************************************************
 * File: rbt.cpp
 * Author: Chris Chen
 * Program: CS302 Program #3 – Race Simulator
 *
 * Purpose:
 *    Implements the Red-Black Tree used to store all
 *    racers. Includes constructors, copy operations,
 *    recursive insert/remove/display, and balancing
 *    logic for rotations and color changes.
 ******************************************************/

#include "rbt.h"

rbt::rbt()
{
    NIL = new node;
    NIL->setColor(BLACK);
    NIL->setLeft(NIL);
    NIL->setRight(NIL);
    NIL->setParent(NIL);

    root = NIL;
}

rbt::rbt(node * source)
{
    copybst(root, source);
}

rbt::~rbt()
{
    remove_all();
    root = nullptr;
    NIL = nullptr;
}

int rbt::copybst(node *& root, node * source)
{
    if(source == nullptr)
        return 0;

    racer * copy_ptr = root->get_class_ptr()->clone(); //copies the object root is pointing at and now copy_ptr * is point at a new copy of the same
    root = new node(copy_ptr); // root is now pointing at a new node that copied what the copy_ptr was pointing at ex. human object

    copybst(root->getLeft(), source);

    copybst(root->getRight(), source);

    return 1;
}


bool rbt::insert(racer * ptr_to_add)
{
    //The REAL root should always be black!!
    if(!root)
    {
        root = new node(ptr_to_add);
        root->setColor(BLACK);
        root->setParent(NIL);
        root->setRight(NIL);
        root->setLeft(NIL);
        return true;
    }
    bool flag = insert(root, ptr_to_add, NIL);
    //This ensures that no matter what happend with recoloring, the
    //root always stays black!!
    root->setColor(BLACK);

    return flag;
}


bool rbt::insert(node *& root, racer * ptr_to_add, node *& parent)
{
    // If we have reached a NIL leaf, this is where the new node belongs
    if(root == NIL)
    {
        root = new node(ptr_to_add);
        root->setParent(parent);
        root->setLeft(NIL);
        root->setRight(NIL);
        return true;
    }

    // Walk down the tree using standard BST ordering
    if(root->get_class_ptr()->get_name() > ptr_to_add->get_name())
    {
        insert(root->getLeft(), ptr_to_add, root);
    }

    else
    {
        insert(root->getRight(), ptr_to_add, root);
    }

    // Case 1: both children under 'root' are red
    // This creates a local imbalance in the color distribution,
    // so we recolor the parent red and push black down to the kids.
    // The wrapper will ensure the real root is forced back to black.
    if(root->getLeft()->getColor() == RED && root->getRight()->getColor() == RED)
    {
        root->setColor(RED);
        root->getRight()->setColor(BLACK);
        root->getLeft()->setColor(BLACK);
    }

    // Case 2: Red violation on the left side
    // These occur when a red child has another red child below it.
    // Depending on the shape (LL or LR), we perform either
    // a single or a double rotation.
    if(root->getLeft()->getColor() == RED)
    {

        // LL pattern → single right rotation repairs it
        if(root->getLeft()->getLeft()->getColor() == RED)
        {
 //           cout << "red - red straight violation! Performing right rotation!" << endl;
            rightRotation(root);
        }

        // LR pattern → requires left rotation on child, then right rotation
        if(root->getLeft()->getRight()->getColor() == RED) 
        {
            //Double rotation: rotate left then right to fix issue
//            cout << "Performing a Double rotation" << endl;
            leftRotation(root);
            rightRotation(root);
        }
    }
    // Case 3: Red violation on the right side
    // Symmetric cases to those above (RR or RL).
    if(root->getRight()->getColor() == RED)
    {
        // RR pattern → single left rotation repairs it	 
        if(root->getRight()->getRight()->getColor() == RED)
        {
            //cout << "Performing left Rotation!" << endl;
            leftRotation(root);
        }
        // RL pattern → requires right rotation on child, then left rotation
        if(root->getRight()->getLeft()->getColor() == RED) 
        {
            //cout << "Performing a Double rotation" << endl;
            rightRotation(root);
            leftRotation(root);
        }
    }
    return true;
}



bool rbt::leftRotation(node * x)
{
    // y will move up to replace x (y is x’s right child)
    node * y = x->getRight();

    // x adopts y’s left subtree on its right side
    x->setRight(y->getLeft());

    // y will move up to replace x (y is x’s right child)
    if(y->getLeft() != NIL)
    {
        y->getLeft()->setParent(x);
    }

    // y should now connect to the parent that originally pointed to x
    y->setParent(x->getParent());

    // case 1: x was the true root of the tree
    if(x->getParent() == NIL)
    {
        this->root = y;
    }

    // case 2: x was a left child → y replaces x on the left
    else if (x == x->getParent()->getLeft()) 
    {
        x->getParent()->setLeft(y);
    }
    // case 3: x was a right child → y replaces x on the right
    else 
    {
        x->getParent()->setRight(y);
    }

    // x drops down and becomes y’s new left child
    y->setLeft(x);

    // and x now reports to y
    x->setParent(y);

    return true;
}


bool rbt::rightRotation(node * y)
{
    // x will take y's place in the tree (x is y's left child)
    node * x = y->getLeft();
    // Move x’s right subtree into y’s left position
    y->setLeft(x->getRight());

    // If x had a right child, that child now reports y as its parent
    if(x->getRight() != NIL)
    {
        x->getRight()->setParent(y);
    }

    // x should now have the same parent that y used to have
    x->setParent(y->getParent());

    // Case: y was the tree’s actual root → update the root pointer
    if (y->getParent() == NIL) 
    {
        this->root = x;
    }

    // Case: y was a left child → x replaces y on the left side
    else if (y == y->getParent()->getLeft()) 
    {
        y->getParent()->setLeft(x);
    }
    // Case: y was a right child → x replaces y on the right side
    else {
        y->getParent()->setRight(x);
    }

    // y now becomes the right child of x
    x->setRight(y);

    // And y’s new parent is x
    y->setParent(x);

    return true;
}



int rbt::display_all()
{
    if(root == NIL)
    {
        return 0;
    }

    return display_all(root);
}


int rbt::display_all(node * root)
{
    if(root == NIL)
        return 1;

    root->get_class_ptr()->display();

    display_all(root->getLeft());

    display_all(root->getRight());

    return 1;
} 

int rbt::remove(const string & name_input)
{
    if(!root) return 0;

    return remove(root, name_input);
}

int rbt::remove(node *& root, const string & name_input)
{
    if(!root) return 0;

    if(root->get_class_ptr()->get_name() == name_input)
    {
        if(!root->getLeft() && !root->getRight())
        {
            delete root;
            root = nullptr;
            return 1;
        }

        if(root->getLeft() != nullptr && root->getRight() == nullptr)
        {
            node * hold = root->getLeft();
            delete root;
            root = hold;
            return 1;
        }

        if(root->getLeft() == nullptr && root->getRight() != nullptr)
        {
            node * hold = root->getRight();
            delete root;
            root = hold;
            return 1;
        }

        else
        { 
            node * retrieve = ios(root->getRight()); //have retrieve hold the node we will return
            delete root->get_class_ptr(); // deallocate the class ptr of the node we want change what it points to
            root->get_class_ptr() = retrieve->get_class_ptr()->clone();  // derefrence what obj retrieve is pointing at and now
                                                                         //  root is pointing at it
            delete retrieve; //delete the retrieve node, it wasnt part of the tree we just used it to store ios data;

        }
    }

    if(root->get_class_ptr()->get_name() > name_input)
    {
        remove(root->getLeft(), name_input);
    }

    else if(root->get_class_ptr()->get_name() < name_input)
    {
        remove(root->getRight(), name_input);
    }
    return 1;
}

node * rbt::ios(node *& root)
{
    if(root->getLeft() == nullptr)
    { 
        racer * copyClass = root->get_class_ptr()->clone(); 
        // = racer * copyclass = new human(*root)           

        // clone creates memory for what root is pointing at and also copies roots class data
        // inside of it so now copyClass is pointing at a new object with everything 
        // root's class pointer is pointing at

        node * copyNode = new node(copyClass); // now we make a new node and send in the copy class ptr we made so now we have a node pointing to it
        delete root; //we delete the smallest node in the right sub tree, since we copied its data we dont need it anymore
        root = nullptr;
        return copyNode; //return the node we copied
    }

    return ios(root->getLeft()); //will traverse left until we reach the end
}


int rbt::remove_all()
{
    if(root == NIL)
        return 0;

    if(!root->getLeft() && !root->getRight())
    {
        delete root;
        root = nullptr;
        return 1;
    }

    return remove_all(root);
}


int rbt::remove_all(node *& root)
{
    if(root == NIL) return 1;

    remove_all(root->getLeft());

    remove_all(root->getRight());

    delete root;
    root = nullptr;

    return 1;
}






int  rbt::move_forward(const string & name_input, int & distance)  //move getter function if name name from user == root->name then we call move function 
{
    if(!root)
    { 
        return 0;
    }

    if(root->get_class_ptr()->get_name() == name_input)
    {
        int distance_traveled = root->get_class_ptr()->move(distance);
        return distance_traveled;
    }

    return move_forward(root, name_input, distance);
}

int rbt::move_forward(node * root, const string & name_input, int & distance)
{
    if(!root) return 0;

    if(root->get_class_ptr()->get_name() == name_input)
    {
        int distance_traveled = root->get_class_ptr()->move(distance);
        return distance_traveled;
    }

    if(root->get_class_ptr()->get_name() > name_input)
    {
        return move_forward(root->getLeft(), name_input, distance);
    }

    else if(root->get_class_ptr()->get_name() < name_input)
    {
        return move_forward(root->getRight(), name_input, distance);
    }

    return 0;

}

bool rbt::rest_break(const string & name_input)
{
    if(!root)
        return false;

    if(root->get_class_ptr()->get_name() == name_input)
    {
        root->get_class_ptr()->rest();
        return true;
    }

    return rest_break(root, name_input);
}

bool rbt::rest_break(node * root, const string & name_input)
{
    if(!root) return false;

    if(root->get_class_ptr()->get_name() == name_input)
    {
        root->get_class_ptr()->rest();
        return true;
    }

    if(root->get_class_ptr()->get_name() > name_input)
    {
        rest_break(root->getLeft(), name_input);
    }

    else if(root->get_class_ptr()->get_name() < name_input)
    {
        rest_break(root->getRight(), name_input);
    }

    return true;
}

bool rbt::sig_ability(const string & name_input)
{
    if(!root) return false;

    if(root->get_class_ptr()->get_name() == name_input)
    {
        root->get_class_ptr()->special_ability();
        return true;
    }

    return sig_ability(root, name_input);
}

bool rbt::sig_ability(node * root, const string & name_input)
{
    if(!root) return false;

    if(root->get_class_ptr()->get_name() == name_input)
    {
        root->get_class_ptr()->special_ability();
        return true;
    }

    if(root->get_class_ptr()->get_name() > name_input)
    {
        sig_ability(root->getLeft(), name_input);
    }

    else if(root->get_class_ptr()->get_name() < name_input)
    {
        sig_ability(root->getRight(), name_input);
    }

    return true;
}











