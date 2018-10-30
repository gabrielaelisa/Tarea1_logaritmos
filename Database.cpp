//
// Created by pedro on 29-10-18.
//

#include "Database.h"

Database::Database(Estructura *estructura) : estructura(estructura) {}

void Database::add_nodo(Nodo *nodo) {
    estructura->add_nodo(nodo);
}

void merge(const string &atributo, long long l, long long m, long long r, long long M) {

}

void Database::ordenar(const string &atributo, long long l, long long r, long long M) {
    if (r - l >= M) { // si el pedazo a ordenar es mayor o igual a M

        long long m = l + (r - l) / 2;

        // se ordenan ambas mitades
        ordenar(atributo, l, m, M);
        ordenar(atributo, m + 1, r, M);

        merge(atributo, l, m, r, M);
    } else {
        estructura.ordenar(atributo, M);
    }
}
