#include <iostream>

#include "Nodo.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc == 3)
        const unsigned long long M = stoull(argv[2]);
    else
        const unsigned long long M = 100000;
    string keys[] = {"id", "rut", "puntosAcumulados"};
    Value myvals[] = {Value((int) 1), Value("19136938-6"), Value((int) 1000)};
    Nodo *mynodo = new Nodo(keys, myvals, 3);
    bool is_in_map = (bool) mynodo->mymap().count("rut");
    string nodoline = mynodo->como_linea();
    cout << "el resultado de la llave es " << is_in_map << endl;
    cout << "el resultado de la linea es " << nodoline << endl;
    return 0;

}