#include <utility>

#include "Estructura.h"

EstructuraArchivo::EstructuraArchivo(string filename) : filename(std::move(filename)), open(false) {}

void EstructuraArchivo::add_nodo(Nodo *nodo) {
    string new_line = nodo->como_linea();
    outfile.open(filename);
    outfile << new_line << endl;
    f.close();
}

void EstructuraArchivo::ordenar(string atributo, long long M) {
    if (!open) {
        f.open(file);
    }
    long long i = 0;
    string line;
    while (i < M) {
        getline(f, line);
        i++;
    }
}

/* implementacion del constructor de btree*/
/* por razones de implementacion ausmimos que B cabe 10000 en M*/
EstructuraBtree::EstructuraBtree( long long M, string atr): B(M/ 10000), atributo(atr) {}
