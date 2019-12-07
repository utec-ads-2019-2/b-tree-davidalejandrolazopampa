#ifndef BTREE_H
#define BTREE_H
#include "node.h"
template <typename T>
class BTree {//No cambiar a btree xq deja de funcionar
private:
    typedef Node<T> node;
    node* root;
    unsigned int degree;
public:
    BTree(unsigned int degree) : degree(degree), root(nullptr) {};

    T search(int k) {
        if(root)
            return root->search(k);
        return false;
    }

    bool insert(int k, T data) {
        if(search(k))
            return false;
        if(!root){
            root = new node(degree);
            root->llaves[0] = k;
            root->tamano = 1;
        }
        else if(root->tamano == degree - 1){
            node *newRoot = new node(degree, false);
            newRoot->hijos[0] = root;
            newRoot->splitChild(0, root);

            if (k >= newRoot->llaves[0]) {
                newRoot->hijos[1]->insert(k, data);
            } else {
                newRoot->hijos[0]->insert(k, data);
            }
            root = newRoot;
        }
        else{
            root->insert(k, data);
        }
        return true;
    }
    bool remove(int k) {
        if(!search(k)){
            return false;
        }
        root->remove(k);
        if(root->tamano == 0){
            node* oldRoot = root;
            if(root->isLeaf){
                root = nullptr;
            }
            else{
                root = root->hijos[0];
            }
            delete oldRoot;
        }
        return true;
    }
    void print() {
        if(root){
            root->print();
        }
        cout<<" "<<endl;
    }
    ~BTree(){
        if(root){
            root -> KillSelf();
        }

    };
};

#endif