#ifndef PROJECT_NODO_H
#define PROJECT_NODO_H

#include <map>
#include <string>

#include "Value.h"

using namespace std;

/* clase nodo, esta es la clase del enunciado,
tiene como unico atributo un diccionario,
en el constructor recibe como input dos arreglos una de llaves de
columnas y otra de valores */
class Nodo {

public:
    Nodo(string column[], Value value[], int len);

    map<string, Value> mymap();

    // esta es la funcion que serializa Nodo a una linea
    // se utiliza en la implementacion de la clase database
    string como_linea();

    // funcion para deserializar una linea y obtener un nodo
    static Nodo como_nodo(string s);

private:
    map<string, Value> fila;
    int mylen;
};


#endif //PROJECT_NODO_H
