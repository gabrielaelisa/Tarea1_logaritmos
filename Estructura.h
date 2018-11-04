#ifndef TAREA1_LOGARITMOS_ESTRUCTURA_H
#define TAREA1_LOGARITMOS_ESTRUCTURA_H


#include <fstream>
#include "Nodo.h"

class Estructura {
public:
    virtual void add_nodo(Nodo *nodo) = 0;
    virtual void ordenar(const string &atributo, long long size) = 0;

};

class EstructuraArchivo: public Estructura {

public:

    explicit EstructuraArchivo(string filename, long long M);

    void add_nodo(Nodo *nodo) override;

    // size es la cantidad de nodos
    void ordenar(const string &atributo, long long size) override;

    // algoritmo mergesort, el parametro first indica si es el primer paso de la recursion
    void mergeSort(const string &atributo, long long l, long long r, bool first);

    // merge de mergesort
    void merge(long long l, long long m, long long r);

    // ordena un trozo de tamano menor que M
    void ordenarTrozo(const string &atributo);

private:
    ofstream outfile;
    ifstream infile;
    string filename;
    long long M;
};

class EstructuraBtree: public Estructura {

public:
    
    //constructor recibe el atributo por el cual se ordenara al insertar
    explicit EstructuraBtree(long long M, string atributo);

    void add_nodo(Nodo *nodo);
    
    /* buscaremos una valor perteneciente a la llave
     * ej id, Value(506)
     */
    void buscar(string key, Value* val);

    /* no hace nada, el btree ya esta ordenado
     * por el atributo que le pasamos en el constructor
     */
    void ordenar(const string &atributo , long long M);

private:
    //tamaño del bloque
    long long B;
    string atributo;
    

};
#endif //TAREA1_LOGARITMOS_ESTRUCTURA_H
