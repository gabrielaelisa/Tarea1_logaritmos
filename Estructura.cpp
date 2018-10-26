#include <utility>

#include "Estructura.h"

EstructuraArchivo::EstructuraArchivo(string filename) : filename(std::move(filename)), open(false) {}

void EstructuraArchivo::add_nodo(Nodo *nodo) {
    string new_line = nodo->como_linea();
    outfile.open(filename);
    outfile << new_line << endl;
    outfile.close();
}

void EstructuraArchivo::ordenar(string atributo, long long M) {
    if (!open) {
        infile.open(filename);
    }
    long long i = 0;
    string line;
    map<Value, Nodo> nodos;
    while (i < M) {
        getline(infile, line);
        // deserializar la linea para obtener un nodo
        string column;
        Nodo *n;
        n = new Nodo(&column, new Value(0), 10);
        nodos[n->mymap()[atributo]] = *n;
        i++;
    }
}

/* implementacion del constructor de btree*/
/* por razones de implementacion ausmimos que B cabe 10000 en M*/
EstructuraBtree::EstructuraBtree( long long M, string atr): B(M/ 10000), atributo(atr) {}
