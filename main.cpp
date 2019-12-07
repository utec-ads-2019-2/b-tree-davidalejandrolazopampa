#include <iostream>

#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
    BTree<int> btree(2);
    for(int i = 0; i < 100; i++)
        btree.insert(i, i);

    btree.print();
    cout<<"Pum"<<endl;

    btree.remove(78);

    btree.print();
    cout<<"Pum"<<endl;
    btree.insert(12,1);

    btree.print();
    return EXIT_SUCCESS;
}