#include <iostream>

#include "Nodo.h"

using namespace std;

/*
 *
 */


// TODO: Adaptar esto cuando las Database existan de verdad
/*
 * Pobla una Database dummy para la parte c)
 * Se basa en la estructura de la tabla Consumidor
 */
void agregarNodosADatabase(const Database &D, int M) {
    int rut = 9900000;
    string keys[] = {"id", "rut", "puntosAcumulados"};
    for (int i = 1; i <= M; i++){
        int codigoVerificador = rand() % 10;
        Value myvals[] = {Value(i),Value(to_string(rut++)+"-"+to_string(codigoVerificador))};
        Nodo nuevoNodo(keys,myvals,3);
        Database.addNodo(nuevoNodo);
    }
}

/*
 * Main recibira:
 * argv[1] = N , cantidad de datos a insertar
 * argv[2] = M , memoria
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Faltan ingresar N";
        return -1;
    }
    int N = stoi(argv[1]);
    long long M = 100000;
    if (argc == 3) {
        M = stoull(argv[2]);
    }


    string keys[] = {"id", "rut", "puntosAcumulados"};
    Value myvals[] = {Value((int) 1), Value("19136938-6"), Value((int) 1000)};
    Nodo *mynodo = new Nodo(keys, myvals, 3);
    bool is_in_map = (bool) mynodo->mymap().count("rut");
    string nodoline = mynodo->como_linea();
    cout << "el resultado de la llave es " << is_in_map << endl;
    cout << "el resultado de la linea es " << nodoline << endl;
    return 0;

}