#include <iostream>
#include <math.h>
#include <random>

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
    int rutBase = 999000;
    int rutStep = 11;
    int puntajeMaximo = 50000;
    int cantidadDeElementos = static_cast<int>(pow(10, N));
    int ruts[cantidadDeElementos];
    int ids[cantidadDeElementos];
    for (int i = 0; i < cantidadDeElementos; ++i) {
        ids[i] = i + 1;
        ruts[i] = rutBase + i * rutStep;
    }
    string keys[] = {"id", "rut", "puntosAcumulados"};
    default_random_engine generator;
    uniform_int_distribution<int> genCodVerRut(0, 9);
    uniform_int_distribution<int> genPuntaje(0, puntajeMaximo);
    for (int i = cantidadDeElementos - 1; i >= 0; i--) {
        uniform_int_distribution<int> distribution(0, i);
        int indiceRut = distribution(generator);
        int indiceId = distribution(generator);
        int rut = ruts[indiceRut];
        int id = ids[indiceId];
        ruts[indiceRut] = ruts[i];
        ids[indiceId] = ids[i];
        Value myvals[] = {Value(id), Value(to_string(rut) + "-" + to_string(genCodVerRut(generator))), Value(genPuntaje(generator))};
        Nodo nuevoNodo(keys, myvals, 3);
        D.add_nodo(&nuevoNodo);
    }
}

// TODO: esto deberia hacer mas que solo llamar a ordenar, como guardar el tiempo por ejemplo
/*
 * Ejecuta el ordenamiento en la Database
 */
void ordenarDatabase(Database &D, const string &atributo) {
    D.ordenar(atributo);
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

    EstructuraArchivo testEstructura("test_p1_c", M);
    Database testDatabase(&testEstructura);

    agregarNodosADatabase(testDatabase, N);

    ordenarDatabase(testDatabase, "id");

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