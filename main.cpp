#include <iostream>

#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
    BTree<int> btree(3);
    for(int i = 70; i < 80; i++)
        btree.insert(i, i);


    // Da segmentation fault, probablemente algunos punteros no se estén liberando de la manera correcta, o al insertar no se esté asignando bien
    // No está insertando bien los elementos
    //btree.print();
    cout<<"Pum"<<endl;

    // El remover no está funcionando correctamente, desaparece todo un nodo, y el árbol no está balanceado
    btree.remove(78);

    //btree.print();
    cout<<"Pum"<<endl;
    btree.insert(12,1);

    btree.print();
    return EXIT_SUCCESS;
}