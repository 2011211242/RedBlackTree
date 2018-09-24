#include <rbtree.h>
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

//using namespace rdtree;

int main() {
    const int SIZE = 10000;
    srand(time(nullptr));

    rdtree::rdtree<int> tree;
    for(int i = 0; i < SIZE; i ++) {
        tree.add(rand() % (10 * SIZE));
        if ( false == tree.test_bh() ) {
            cout << "bh wrong" << endl;
        }
    }

    //tree.test();
}
