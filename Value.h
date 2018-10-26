#ifndef TAREA1_LOGARITMOS_VALUE_H
#define TAREA1_LOGARITMOS_VALUE_H

#include <string>

using namespace std;

//clase que contiene un atributo o string, o int
class Value {
public:
    enum DATA_TYPE {
        STRING,
        INT
    };

    // existen dos constructores, uno para el type string,
    // otro para el type int
    explicit Value(int value);

    explicit Value(const string &value);

    DATA_TYPE type();

    void *val();

    /* Compara con otro valor del mismo tipo, retorna 1 si el valor con el cual se compara es menor, 0 si son iguales
     * y -1 si es mayor
     */
    int compare(Value v);

private:
    DATA_TYPE m_type;
    void *m_ptr;
};


#endif //TAREA1_LOGARITMOS_VALUE_H
