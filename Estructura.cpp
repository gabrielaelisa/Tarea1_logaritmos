#include "Estructura.h"

EstructuraArchivo::EstructuraArchivo(string filename) : file(filename), open(false) {}

void EstructuraArchivo::add_nodo(Nodo *nodo) {
    ofstream f;
    string new_line = nodo->como_linea();
    f.open(file);
    f << new_line << endl;
    f.close();
}

void EstructuraArchivo::ordenar(string atributo, long long l, long long r) {
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
