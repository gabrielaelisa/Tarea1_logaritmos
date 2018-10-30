#include <iostream>
#include <math.h>

#include "Nodo.h"
#include "Database.h"


using namespace std;


// TODO: Adaptar esto cuando las Database existan de verdad
/*
 * Pobla una Database dummy para la parte c)
 * Se basa en la estructura de la tabla Consumidor
 * Ingresa 10^N datos
 */
void agregarNodosADatabase(Database &D, int N) {
    int rut = 9900000;
    string keys[] = {"id", "rut", "puntosAcumulados"};
    int upperBound = pow(10,N);
    for (int i = 1; i <= upperBound; i++){
        int codigoVerificador = rand() % 10;
        Value myvals[] = {Value(i),Value(to_string(rut++)+"-"+to_string(codigoVerificador)),Value(rand() % 10000)};
        Nodo nuevoNodo(keys,myvals,3);
        D.add_nodo(&nuevoNodo);
    }
}

/*
 * Main recibira:
 * argv[1] = N , cantidad de datos a insertar
 * argv[2] = M , memoria
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Falta ingresar N";
        return -1;
    }
    int N = stoi(argv[1]);
    long long M = 100000;
    if (argc == 3) {
        M = stoull(argv[2]);
    }

    EstructuraArchivo testEstructura("test_p1_c");
    Database testDatabase(&testEstructura);

    agregarNodosADatabase(testDatabase,N);

    /*
    string keys[] = {"id", "rut", "puntosAcumulados"};
    Value myvals[] = {Value((int) 1), Value("19136938-6"), Value((int) 1000)};
    Nodo *mynodo = new Nodo(keys, myvals, 3);
    bool is_in_map = (bool) mynodo->mymap().count("rut");
    string nodoline = mynodo->como_linea();
    cout << "el resultado de la llave es " << is_in_map << endl;
    cout << "el resultado de la linea es " << nodoline << endl;
    return 0;
     */

}