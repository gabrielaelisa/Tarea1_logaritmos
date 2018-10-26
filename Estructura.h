#ifndef TAREA1_LOGARITMOS_ESTRUCTURA_H
#define TAREA1_LOGARITMOS_ESTRUCTURA_H


#include <fstream>
#include "Nodo.h"

class Estructura {
public:
    virtual void add_nodo(Nodo *nodo) = 0;
    virtual void ordenar(string &atributo, long long M) = 0;
};

class EstructuraArchivo: public Estructura {

public:

    explicit EstructuraArchivo(string filename);

    void add_nodo(Nodo *nodo);

    void ordenar(string atributo, long long M);

private:
    ofstream outfile;
    ifstream infile;
    string filename;
    bool open;
};

class EstructuraBtree: public Estructura {

public:
    
    //constructor recibe el atributo por el cual se ordenara al insertar
    explicit EstructuraBtree(long long M, string atributo);

    void add_nodo(Nodo *nodo);
    
    /* buscaremos una valor perteneciente a la llave
    ej id, Value(506)*/
    void buscar(string key, Value* val);

    /* no hace nada, el btree ya esta ordenado 
    por el atributo que le pasamos en el constructor*/
    void ordenar(string atributo , long long M);

private:
    //tamaño del bloque
    long long B;
    string atributo;
    

}
#endif //TAREA1_LOGARITMOS_ESTRUCTURA_H
