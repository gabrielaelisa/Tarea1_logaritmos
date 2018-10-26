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
    
    //constructor
    explicit EstructuraBtree();

    void add_nodo(Nodo *nodo);

    void ordenar();
}
#endif //TAREA1_LOGARITMOS_ESTRUCTURA_H
