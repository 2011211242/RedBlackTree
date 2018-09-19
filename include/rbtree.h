#ifndef _RBTREE_
#define _RBTREE_

#include <iostream>
#include <stack>

namespace rdtree {

using namespace std;


enum color {
    black = 0,
    red = 1,
};


template <typename T>
class node {
public:
    node(){ l = nullptr, r = nullptr, cl = black; }
    node(T a): val(a) { l = nullptr, r = nullptr, cl = black; }

    node<T>* left() { return l; }
    node<T>* right() { return r; }

    void set_left(node<T>* ptr) { l = ptr; }
    void set_right(node<T>* ptr) { r = ptr; }

    ~node() { 
        if ( l ) l -> ~node(); 
        if ( r ) r -> ~node(); 
        delete l;
        delete r;
        l = r = nullptr;
        val.~T();
    }

private:
    node<T>* l; 
    node<T>* r;
    color cl;
    T val;
};


template <typename T>
class rdtree {
public:
    rdtree() { root = nullptr; }
    ~rdtree();
private:
    node<T> * root;
};


template <class T>
rdtree<T>::~rdtree(){
    if ( root ) root -> ~node();
    root = nullptr;
}


};

#endif
