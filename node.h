#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

template <typename T>
class Node {

    typedef Node<T> node;

    unsigned int tamaño;
    unsigned int capacidad;
    vector<unsigned int> llaves;
    vector<Node<T>*> hijos;
    bool isLeaf;

    public: 
        Node(unsigned int capacidad, bool isLeaf = true) : capacidad(capacidad), isLeaf(isLeaf) {
            tamaño = 0;
            llaves.resize(capacidad - 1);
            hijos.resize(capacidad);
        }

        bool Buscar(int nodito){
            int i = 0;
            while(i < tamaño && nodito > llaves[i]){
                i++;
            }
            if (llaves[i] != nodito) {
                if (isLeaf) { return false; }
                return hijos[i]->buscar(nodito);
            } else { return true; }
        }
        void Insertar(unsigned int nodito, T data){
            int variable = tamaño;
            if (isLeaf) {
                while (variable > 0 && nodito < llaves[variable - 1]) {
                    llaves[variable] = llaves[variable - 1];
                    variable--;
                }
                llaves[variable] = nodito;
                tamaño++;
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
            
        }




    friend class BTree; 
};

#endif