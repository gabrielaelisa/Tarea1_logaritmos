#include <iostream>
#include <math.h>
#include <random>
#include <chrono>
#include <ctime>
#include "Nodo.h"
#include "Database.h"


using namespace std;


/*
 * Pobla una Database dummy para la parte c)
 * Se basa en la estructura de la tabla Consumidor
 */
void agregarNodosADatabase(Database &D, long N) {
    long rutBase = 999000;
    long rutStep = 11;
    long puntajeMaximo = 50000;
    long cantidadDeElementos = N;
    vector<long> ids;
    vector<long> ruts;
    ids.resize(cantidadDeElementos);
    ruts.resize(cantidadDeElementos);
    for (long i = 0; i < cantidadDeElementos; ++i) {
        ruts[i] = rutBase + i * rutStep;
        ids[i] = i;
    }
    string keys[] = {"id", "rut", "puntosAcumulados"};
    default_random_engine generator;
    uniform_int_distribution<long> genCodVerRut(0, 9);
    uniform_int_distribution<long> genPuntaje(0, puntajeMaximo);
    for (long i = cantidadDeElementos - 1; i >= 0; i--) {
        uniform_int_distribution<long> distribution(0, i);
        long indiceRut = distribution(generator);
        long indiceId = distribution(generator);
        long rut = ruts[indiceRut];
        long id = ids[indiceId];
        ruts[indiceRut] = ruts[i];
        ids[indiceId] = ids[i];
        Value myvals[] = {Value(id), Value(to_string(rut) + "-" + to_string(genCodVerRut(generator))), Value(genPuntaje(generator))};
        Nodo nuevoNodo(keys, myvals, 3);
        D.add_nodo(&nuevoNodo);
    }
}


/*
 * Ejecuta el ordenamiento en la Database
 */
void ordenarDatabase(Database &D, const string &atributo) {
    auto begin = std::chrono::high_resolution_clock::now();
    D.ordenar(atributo);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << "ns" << std::endl;
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
    int N = static_cast<int>(pow(10, stoi(argv[1])));
    long long M = 100000;
    int pruebas = 10;
    if (argc == 3) {
        M = stoull(argv[2]);
    }
    /*
     * Primero, se hacen las pruebas de insercion
     */
    cout << "Insertando " << to_string(N) << " elementos, en " << to_string(pruebas) << " pruebas" << endl;
    for (int i = 0; i < pruebas; ++i) {
        auto begin = std::chrono::high_resolution_clock::now();
        EstructuraArchivo testEstructura("test_p1_c", M);
        Database testDatabase(&testEstructura);
        agregarNodosADatabase(testDatabase, N);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << "ns" << std::endl;
    }

    /*
     * A continuacion, se hacen los pruebas de ordenamiento
     */
    int pruebas2 = 10;
    cout << "Ordenando " << to_string(N) << " elementos, en " << to_string(pruebas2) << " pruebas" << endl;
    for (int i = 0; i < pruebas2; ++i) {
        EstructuraArchivo testEstructura("test_p1_c", M);
        Database testDatabase(&testEstructura);
        agregarNodosADatabase(testDatabase, N);
        ordenarDatabase(testDatabase, "id");
    }
}
