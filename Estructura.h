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


// Nodo del Btree
class NodoBtree 
{ 
    Nodo ** llaves;  // arreglo de llaves
    int B; //rango de claves
    NodoBtree ** hijos; // arreglo de punteros a hijos
    int n;     // numero de llaves
    bool hoja; //es verdadero si el nodo es una hoja 
    string atributo;

public: 
    NodoBtree(int _B, bool _hoja, string _atributo);   // Constructor 
    
    NodoBtree * buscar(string key, Value* val);

    void insertNonFull(Nodo * nodo); 
  
    void splitChild(int i, NodoBtree *y);  
  
// con esto se puede acceder a campos privados del Btree
friend class EstructuraBtree; 
};

class EstructuraBtree: public Estructura 
{

public:
    
    //constructor recibe el atributo por el cual se ordenara al insertar
    explicit EstructuraBtree(string atributo);

    void add_nodo(Nodo *nodo);
    
    /* buscaremos una valor perteneciente a la llave
     * ej id, Value(506)
     */
    NodoBtree * buscar(string key, Value* val);

    /* no hace nada, el btree ya esta ordenado
     * por el atributo que le pasamos en el constructor
     */
    void ordenar(const string &atributo , long long M);

private:
    //tamaño del bloque
    int B= 1024; // 1 kbyte
    string atributo;
    NodoBtree *root; // puntero al root node
    

};


#endif //TAREA1_LOGARITMOS_ESTRUCTURA_H
