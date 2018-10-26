#ifndef TAREA1_LOGARITMOS_ESTRUCTURA_H
#define TAREA1_LOGARITMOS_ESTRUCTURA_H


#include <fstream>
#include "Nodo.h"

class Estructura {
public:
    virtual void add_nodo(Nodo *nodo) = 0;
    virtual void ordenar(string &atributo, long long l, long long r) = 0;
};

class EstructuraArchivo: public Estructura {

public:

    explicit EstructuraArchivo(string filename);

    void add_nodo(Nodo *nodo);

    void ordenar(string atributo, long long l, long long r);

private:
    string file;
    bool open;
};


#endif //TAREA1_LOGARITMOS_ESTRUCTURA_H
