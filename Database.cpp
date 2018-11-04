#include "Database.h"

Database::Database(Estructura *estructura) : estructura(estructura), size(0) {}

void Database::add_nodo(Nodo *nodo) {
    estructura->add_nodo(nodo);
    size++;
}

void merge(const string &atributo, long long l, long long m, long long r, long long M) {

}

void Database::ordenar(const string &atributo) {
    estructura->ordenar(atributo, size);
}

long long Database::getSize() {
    return size;
}
