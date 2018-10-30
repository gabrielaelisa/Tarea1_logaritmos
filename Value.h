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

    /* Compara 2 valores, retorna 1 si el primer valor es mayor, 0 si son iguales
     * y -1 si el segundo es mayor
     */
    static int compare(Value v1, Value v2);

private:
    DATA_TYPE m_type;
    void *m_ptr;
};


#endif //TAREA1_LOGARITMOS_VALUE_H
