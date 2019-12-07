#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

template <typename T>
class Node {

    typedef Node<T> node;

    unsigned int tamano;
    unsigned int capacidad;
    vector<unsigned int> llaves;
    vector<Node<T>*> hijos;
    bool isLeaf;

    public: 
        Node(unsigned int capacidad, bool isLeaf = true) : capacidad(capacidad), isLeaf(isLeaf) {
            tamano = 0;
            llaves.resize(capacidad - 1);
            hijos.resize(capacidad);
        }

        bool Buscar(int nodito){
            int i = 0;
            while(i < tamano && nodito > llaves[i]){
                i++;
            }
            if (llaves[i] != nodito) {
                if (isLeaf) { return false; }
                return hijos[i]->buscar(nodito);
            } else { return true; }
        }
        void Insertar(unsigned int nodito, T data){
            int variable = tamano;
            if (isLeaf) {
                while (variable > 0 && nodito < llaves[variable - 1]) {
                    llaves[variable] = llaves[variable - 1];
                    variable--;
                }
                llaves[variable] = nodito;
                tamano++;
            } else {
                while (variable > 0 && nodito < llaves[variable - 1]) {
                    variable--;
                }
                if (!(hijos[variable]->size == capacidad - 1)) {}
                else {
                    splitChild(variable, hijos[variable]);
                    if (nodito <= llaves[variable]) {}
                    else {
                        variable++;
                    }
                }

                hijos[variable]->Insertar(nodito, data);
            }
        }

        void SplitNino(int variable, node* NinoDividido){
            //aqui debo de partir en 2
            node* newNode = new node(capacidad, NinoDividido->isLeaf);
            int nuevo = (capacidad - 1)/2;
            //Paso
            newNode->size = nuevo - (capacidad%2);
            for(int i = 0; i < newNode->size; i++){
                newNode->keys[i] = NinoDividido->keys[nuevo + 1 + i];
            }

            if (NinoDividido->isLeaf) {}
            else {
                for (int i = 0; i <= newNode->size; i++) {
                    newNode->children[i] = NinoDividido->children[nuevo + 1 + i];
                }
            }
            NinoDividido->size = nuevo;
            for(int i = tamano + 1; i > variable + 1; i--){
                hijos[i] = hijos[i-1];
            }
            hijos[variable + 1] = newNode;
            for(int i = tamano; i > variable; i--){
                llaves[i] = llaves[i-1];
            }
            llaves[variable] = NinoDividido->keys[nuevo];
            tamano++;
        }
        void Elimina(int nodito){
        int variable = 0;
        while(variable < tamano && nodito > llaves[variable]){
            variable++;
        }
        if (variable >= tamano || llaves[variable] != nodito) {
            if (!(hijos[variable]->size < (capacidad + 1) / 2)) {}
            else {
                llenar(variable);
            }

            if (variable <= tamano) {
                hijos[variable]->remove(nodito);
            } else {
                hijos[variable - 1]->remove(nodito);
            }
        } else {
            if (isLeaf) {
                for (int i = variable; i < tamano - 1; i++) {
                    llaves[i] = llaves[i + 1];
                }
                tamano--;
            } else {
                if (hijos[variable]->size >= (capacidad + 1) / 2) {
                    int newKey = getLlaveanterior(variable);
                    llaves[variable] = newKey;
                    hijos[variable]->remove(newKey);
                } else if (!(hijos[variable + 1]->size >= (capacidad + 1) / 2)) {
                    merge(variable);
                    hijos[variable]->remove(nodito);
                } else {
                    int newKey = getLlavesiguiente(variable);
                    llaves[variable] = newKey;
                    hijos[variable + 1]->remove(newKey);
                }
            }

        }
    }
        void llenar(int variable){

        }
        void merge(int variable){

        }
        void getLlaveanterior(int variable){

        }
        void getLlavesiguiente(int variable){

    }



    friend class BTree; 
};

#endif