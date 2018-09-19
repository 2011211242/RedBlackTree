#include <iostream>

namespace rdtree {

enum color {
    black = 0,
    red = 1,
};

template <class T>
struct node {
    struct node *left; 
    struct node *right;
    color cl;
    T a;
    node() {left = nullptr, right=nullptr, cl=black;}
};

template <class T>
class rdtree {
public:
    rdtree() {root = nullptr;}
    ~rdtree();
private:
    node<T> * root;
};

template <class T>
rdtree<T>::~rdtree(){
}


};
