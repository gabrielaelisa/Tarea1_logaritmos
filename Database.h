#ifndef TAREA1_LOGARITMOS_DATABASE_H
#define TAREA1_LOGARITMOS_DATABASE_H


#include "Estructura.h"

class Database {

public:
    explicit Database(Estructura *estructura);
    
    void add_nodo(Nodo *nodo);

    /* recibe el atributo segun el cual se ordena, los limites entre los cuales se ordena,
     * y la constante M de la memoria
     */
    void ordenar(const string &atributo, long long l, long long r, long long M);

private:
    Estructura *estructura;
};


#endif //TAREA1_LOGARITMOS_DATABASE_H
