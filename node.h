#ifndef NODE_H
#define NODE_H

#include <vector>
#include <queue>

using namespace std;
template<typename T> class BTree; //Se agrego generaba error
template <typename T>
class Node {
    typedef Node<T> node;

    unsigned int capacity;
    unsigned int tamano;
    vector<unsigned int> llaves;
    vector<Node<T>*> hijos;
    bool isLeaf;
public:
    Node(unsigned int capacity, bool isLeaf = true) : capacity(capacity), isLeaf(isLeaf) {
        tamano = 0;
        // puse el resize en el código base, pero no es una buena idea usarlo
        llaves.resize(capacity - 1);
        hijos.resize(capacity);
    }

    bool search(int k){
        int i = 0;
        while(i < tamano && k > llaves[i])
            i++;

        if (llaves[i] != k) {
            if (isLeaf)
                return false;
            return hijos[i]->search(k);
        } else return true;
    }
    void insert(unsigned int k, T data){
        int variable = tamano;
        if (!isLeaf) {
            while (variable > 0 && k < llaves[variable - 1]) {
                variable--;
            }

            if (hijos[variable]->tamano == capacity - 1) {
                splitChild(variable, hijos[variable]);
                if (k > llaves[variable]) {
                    variable++;
                }
            }
            hijos[variable]->insert(k, data);
        } else {
            while (variable > 0 && k < llaves[variable - 1]) {
                llaves[variable] = llaves[variable - 1];
                variable--;
            }
            llaves[variable] = k;
            tamano++;
        }
    }
    void splitChild(int variable, node* toSplit){
        node* nuevoNode = new node(capacity, toSplit->isLeaf);
        int m = (capacity - 1)/2;
        nuevoNode->tamano = m - (capacity%2);
        for(int i = 0; i < nuevoNode->tamano; i++){
            nuevoNode->llaves[i] = toSplit->llaves[m + 1 + i];
        }
        if (toSplit->isLeaf) {}
        else {
            for (int i = 0; i <= nuevoNode->tamano; i++) {
                nuevoNode->hijos[i] = toSplit->hijos[m + 1 + i];
            }
        }
        toSplit->tamano = m;
        for(int i = tamano + 1; i > variable + 1; i--){
            hijos[i] = hijos[i-1];
        }
        hijos[variable + 1] = nuevoNode;
        for(int i = tamano; i > variable; i--){
            llaves[i] = llaves[i-1];
        }
        llaves[variable] = toSplit->llaves[m];
        tamano++;
    }
    void remove(int k){
        int variable = 0;
        while(variable < tamano && k > llaves[variable]){
            variable++;
        }
        if (variable >= tamano || llaves[variable] != k) {
            if (hijos[variable]->tamano < (capacity + 1) / 2) {
                fillNode(variable);
            }

            if (variable > tamano) {
                hijos[variable - 1]->remove(k);
            } else {
                hijos[variable]->remove(k);
            }
        } else {
            if (isLeaf) {
                for (int i = variable; i < tamano - 1; i++) {
                    llaves[i] = llaves[i + 1];
                }
                tamano--;
            } else {
                if (hijos[variable]->tamano >= (capacity + 1) / 2) {
                    int newKey = getPreviousKey(variable);
                    llaves[variable] = newKey;
                    hijos[variable]->remove(newKey);
                } else if (hijos[variable + 1]->tamano >= (capacity + 1) / 2) {
                    int newKey = getNextKey(variable);
                    llaves[variable] = newKey;
                    hijos[variable + 1]->remove(newKey);
                } else {
                    mergeNodes(variable);
                    hijos[variable]->remove(k);
                }
            }

        }
    }
    int getPreviousKey(int variable){
        node* pase = hijos[variable];
        while(!pase->isLeaf){
            pase = pase->hijos[0];
        }
        return pase->llaves[0];
    }
    int getNextKey(int variable){
        node* pase = hijos[variable + 1];
        while(!pase->isLeaf){
            pase = pase->hijos[pase->tamano];
        }
        return pase->llaves[pase->tamano - 1];
    }
    void fillNode(int variable){
        int m = (capacity - 1)/2;
        if (!variable || hijos[variable - 1]->tamano <= m) {
            if (variable != tamano && hijos[variable + 1]->tamano > m) {
                borrowNext(variable);
            } else {
                if (variable == tamano) {
                    mergeNodes(variable - 1);
                } else {
                    mergeNodes(variable);
                }
            }
        } else {
            borrowPrev(variable);
        }
    }

    void borrowPrev(int variable){
        int nuevo = (capacity - 1)/2;
        node* pase = hijos[variable];
        node* toBorrow = hijos[variable - 1];
        for(int i = pase->tamano; i > 0; i--){
            pase->llaves[i] = pase->llaves[i - 1];
        }
        if (pase->isLeaf) {}
        else {
            for (int i = pase->tamano + 1; i > 0; i--) {
                pase->hijos[i] = pase->hijos[i - 1];
            }
        }
        pase->llaves[0] = llaves[variable - 1];
        if (toBorrow->isLeaf) {}
        else {
            pase->hijos[0] = toBorrow->hijos[toBorrow->tamano];
        }

        llaves[variable - 1] = toBorrow->llaves[toBorrow->tamano - 1];

        pase->tamano++;
        toBorrow->tamano--;
    }
    void borrowNext(int variable){
        int nuevo = (capacity - 1)/2;

        node* pase = hijos[variable];
        node* toBorrow = hijos[variable + 1];

        pase->llaves[pase->tamano] = llaves[variable];

        if(!toBorrow->isLeaf){
            pase->hijos[pase->tamano + 1] = toBorrow->hijos[0];
        }
        llaves[variable] = toBorrow->llaves[0];

        for(int i = 1; i < toBorrow->tamano; i++){
            toBorrow->llaves[i - 1] = toBorrow->llaves[i];
        }
        if(!pase->isLeaf){
            for(int i = 1; i < toBorrow->tamano + 1; i++){
                toBorrow->hijos[i - 1] = toBorrow->hijos[i];
            }
        }
        pase->tamano++;
        toBorrow->tamano--;
    }
    void mergeNodes(int variable){
        int nuevo = (capacity - 1)/2;
        node* pase = hijos[variable];
        node* toMerge = hijos[variable + 1];
        pase->llaves[nuevo] = llaves[variable];
        for(int i = 0; i < toMerge->tamano; i++){
            pase->llaves[nuevo + 1 + i] = toMerge->llaves[i];
        }
        if (toMerge->isLeaf) {}
        else {
            for (int i = 0; i <= toMerge->tamano; i++) {
                pase->hijos[nuevo + 1 + i] = toMerge->hijos[i];
            }
        }
        for(int i = variable; i < tamano - 1; i++){
            llaves[i] = llaves[i + 1];
        }
        for(int i = variable + 1; i < tamano; i++){
            hijos[i] = hijos[i + 1];
        }
        pase->tamano += 1 + toMerge->tamano;
        tamano--;
        delete toMerge;
    }
    void print(){
        if(isLeaf){
            for(int i = 0; i < tamano; i++){
                cout<<llaves[i]<<" "<<endl;;
            }
        }
        else{
            for(int i = 0; i < tamano; i++){
                hijos[i]->print();
                cout<<llaves[i]<<" ";
            }
            hijos[tamano]->print();
        }
    }
    void KillSelf(){
        for(auto now : this->hijos) {
            if (!now) // Así  no se debería controlar
                continue;
            now->KillSelf();
        }
        delete this;
    }

    void recorrerNodes() {
            queue<pair<Node<T>*, int>> next;
            next.push(pair<Node<T>*, int>(this, 0));

            while (!next.empty()) {
                auto temp = next.front();
                next.pop();

                temp.first->printIndexes(temp.second);

                for (int i = 0; i < temp.first->hijos.size(); i++) {
                    next.push(pair<Node<T>*, int>(temp.first->hijos[i], temp.second + 1));
                }

                cout << endl;
            }  
    }

    void printIndexes(int level) {
        cout << level << ": ";
        for (int i = 0; i < llaves.size(); i++) {
            cout << llaves[i] << " ";
        }
    }

    ~Node() {
        this->hijos.clear();
        this->llaves.clear();
    }
    friend class BTree<T>;
};

#endif