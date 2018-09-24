#ifndef _RBTREE_
#define _RBTREE_
#include <iostream>
#include <stack>

namespace rdtree {
using namespace std;


enum COLOR {
    BLACK = 0,
    RED = 1,
};


template <typename T>
class node {
public:
    node() { l = nullptr, r = nullptr, cl = BLACK; }
    node(const T& a): val(a) { l = nullptr, r = nullptr, cl = BLACK; }
    node(const T&& a): val(a) { l = nullptr, r = nullptr, cl = BLACK; }

    node<T>* left() { return l; }
    node<T>* right() { return r; }
    node<T>* parent() { return p; }
    COLOR color() { return cl; }

    void set_left(node<T>* ptr) { l = ptr; }
    void set_right(node<T>* ptr) { r = ptr; }
    void set_parent(node<T>* ptr) { p = ptr; }
    void set_color(const COLOR c) { cl = c; }
    void set_value(const T& val) { this -> val = val; }
    T value(){ return val; }
private:
    node<T>* l; 
    node<T>* r;
    node<T>* p;
    COLOR cl;
    T val;
};


template <typename T>
class rdtree {
public:
    rdtree() { 
        nil = new node<T>; 
        nil -> set_left(nil);
        nil -> set_right(nil);
        nil -> set_parent(nil);
        root = nil;
    }

    ~rdtree();
    void add(const T &val);
    //node<T>* root() { return root; }

    void test();

private:
    void insert_fixup(node<T>* x);
    void left_rotate(node<T>* const x);
    void right_rotate(node<T>* const x);

    node<T> * root;
    node<T> * nil;
};


template <typename T>
rdtree<T>::~rdtree() {
    stack<node<T> *> stk;
    if (root != nil) stk.push(root);

    while(!stk.empty()) {
        node <T> * ptr = stk.top();
        stk.pop();
        while ( ptr != nil ) {
            node <T> * left = ptr -> left();
            node <T> * right = ptr -> right();

            if (right != nil)
                stk.push(right);

            ptr -> set_left(nullptr);
            ptr -> set_right(nullptr);

            delete ptr;
            ptr = left;
        }
    }

    delete nil;
    nil = nullptr;
    root = nullptr;
}


template <typename T>
void rdtree<T>::add(const T &val) {
    node<T>* parent = nil;
    node<T>* ptr = root;

    while( ptr != nil ) {
        parent = ptr;
        if ( val < ptr -> value()) ptr = ptr -> left();
        else ptr = ptr -> right();
    }

    node<T>* z = new node<T>( val );

    if (root == nil) 
        root = z;
    else {
        if ( val < parent -> value() ) parent -> set_left(z);
        else parent -> set_right(z);
    }

    z -> set_parent( parent );
    z -> set_left(nil);
    z -> set_right(nil);
    z -> set_color(RED);

    insert_fixup(z);
}


template <typename T>
void rdtree<T>::insert_fixup(node<T>* x) {
    while (x -> parent() -> color() == RED) {
        if ( x -> parent() == x -> parent() -> parent() -> left()) {
            node <T> * y = x -> parent() -> parent() -> right();
            if (y -> color() == RED) {
                x -> parent() -> set_color(BLACK);
                y -> set_color(BLACK);
                x -> parent() -> parent() -> set_color(RED);
                x = x -> parent() -> parent();
            }
            else {
                if (x == x -> parent() -> right()) {
                    x = x -> parent();
                    left_rotate(x);
                }
                x -> parent() -> set_color(BLACK);
                x -> parent() -> parent() -> set_color(RED);
                right_rotate(x -> parent() -> parent());
            }
        }
        else {
            node <T> * y = x -> parent() -> parent() -> left();
            if (y -> color() == RED) {
                x -> parent() -> set_color(BLACK);
                y -> set_color(BLACK);
                x -> parent() -> parent() -> set_color(RED);
                x = x -> parent() -> parent();
            }
            else {
                if (x == x -> parent() -> left()) {
                    x = x -> parent();
                    right_rotate(x);
                }
                x -> parent() -> set_color(BLACK);
                x -> parent() -> parent() -> set_color(RED);
                left_rotate(x -> parent() -> parent());
            }
        }
    }
    root -> set_color(BLACK);
}


template <typename T>
void rdtree<T>::left_rotate(node<T>* const x) {
    node<T> * const right = x -> right();
    if( x == root ) {
        root = right;
    }
    else {
        if (x == x -> parent() -> left()) {
            x -> parent() -> set_left(right);
        }
        else {
            x -> parent() -> set_right(right);
        }
    }
    right -> set_parent(x -> parent());

    x -> set_parent(right);
    x -> set_right(right -> left());

    if (right -> left() != nil) {
        right -> left() -> set_parent(x);
    }
    right -> set_left(x);
}


template <typename T>
void rdtree<T>::right_rotate(node<T>* const x) {
    node<T> * const left = x -> left();
    if (x == root) {
        root = left;
    }
    else {
        if (x == x -> parent() -> left()) {
            x -> parent() -> set_left(left);
        }
        else {
            x -> parent() -> set_right(left);
        }
    }
    left -> set_parent(x -> parent());

    x -> set_parent(left);
    x -> set_left(left -> right());

    if (left -> right() != nil) {
        left -> right() -> set_parent(x);
    }
    left -> set_right(x);
}


template <typename T>
void rdtree<T>::test() {
    add('w');
    //add('u');
    add('y');
    //add('x');
    add('z');
    //add('v');
    //add('a');

    left_rotate(root);
    right_rotate(root);
    cout << root -> value() << endl;
    cout << root -> left() -> value() << endl;
    cout << root -> right() -> value() << endl;
}


};

#endif
