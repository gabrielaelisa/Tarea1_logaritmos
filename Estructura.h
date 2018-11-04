#ifndef TAREA1_LOGARITMOS_ESTRUCTURA_H
#define TAREA1_LOGARITMOS_ESTRUCTURA_H


#include <fstream>
#include "Nodo.h"

class Estructura {
public:
    virtual void add_nodo(Nodo *nodo) = 0;
    virtual void ordenar(const string &atributo, long long M) = 0;
};

class EstructuraArchivo: public Estructura {

public:

    explicit EstructuraArchivo(string filename);

    void add_nodo(Nodo *nodo) override;

    void ordenar(const string &atributo, long long M) override;

private:
    ofstream outfile;
    ifstream infile;
    string filename;
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
    NodoBtree(int _B, bool _leaf, string atributo);   // Constructor 
    
    NodoBtree *buscar(int k);

    void insertNonFull(Nodo * nodo); 
  
    void splitChild(int i, NodoBtree *y);  
  
// con esto se puede acceder a campos privados del Btree
friend class EstructuraBtree; 
};
#endif //TAREA1_LOGARITMOS_ESTRUCTURA_H
