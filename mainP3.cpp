#include <iostream>
#include <math.h>
#include <random>
#include <chrono>
#include <ctime>
#include "Nodo.h"
#include "Database.h"


using namespace std;


/*
 * Pobla la tabla consumidor
 */
void poblarConsumidor(Database &D, long N) {
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
 * Pobla la tabla producto
 */
void poblarProducto(Database &D, long N) {
    long precioMaximo = 10000000;
    long puntosNecMaximo = 50000;
    long puntosRecMaximo = 50000;
    long cantidadDeElementos = N;
    vector<long> ids;
    ids.resize(cantidadDeElementos);
    for (long i = 0; i < cantidadDeElementos; ++i) {
        ids[i] = i;
    }
    string keys[] = {"id", "precio", "puntosNec", "puntosRec"};
    default_random_engine generator;
    uniform_int_distribution<long> genPrecio(0, precioMaximo);
    uniform_int_distribution<long> genPuntosNec(0, puntosNecMaximo);
    uniform_int_distribution<long> genPuntosRec(0, puntosRecMaximo);
    for (long i = cantidadDeElementos - 1; i >= 0; i--) {
        uniform_int_distribution<long> distribution(0, i);
        long indiceId = distribution(generator);
        long id = ids[indiceId];
        ids[indiceId] = ids[i];
        Value myvals[] = {Value(id), Value(genPrecio(generator)), Value(genPuntosNec(generator)), Value(genPuntosRec(generator))};
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
        cout << "Falta ingresar C y P";
        return -1;
    }
    if (argc < 3) {
        cout << "Falta ingresar P";
        return -1;
    }
    int C = static_cast<int>(pow(10, stoi(argv[1])));
    int P = static_cast<int>(pow(10, stoi(argv[2])));
    long long M = 100000;
    if (argc == 4) {
        M = stoull(argv[2]);
    }

    /*
     * Parte a)
     */
    //TODO

    /*
     * Parte b)
     */
    EstructuraArchivo testEstructuraConsumidor("test_p3_b_consumidor", C);
    Database testDatabaseConsumidor(&testEstructuraConsumidor);
    poblarConsumidor(testDatabaseConsumidor, C);

    EstructuraArchivo testEstructuraProducto("test_p3_b_producto", P);
    Database testDatabaseProducto(&testEstructuraProducto);
    poblarProducto(testDatabaseProducto, P);

    testDatabaseConsumidor.ordenar("puntosAcumulados");
    testDatabaseProducto.ordenar("puntosNec");

    ifstream tabla_consumidor("test_p3_b_consumidor");
    ifstream tabla_producto("test_p3_b_producto");
    ofstream query("test_p3_b_query");

    long long i, cursor = 0;
    string consumidor, producto;
    getline(tabla_consumidor, consumidor);
    while (!consumidor.empty()) {
        Nodo nodo_consumidor(consumidor);
        size_t index_id_consumidor = consumidor.find("id");
        consumidor.replace(index_id_consumidor, 2, "id_consumidor");
        tabla_producto.clear();
        tabla_producto.seekg(0, ios::beg);
        for (i = 0; i < cursor; i++) {
            getline(tabla_producto, producto);
            size_t index_id_producto = producto.find("id");
            producto.replace(index_id_producto, 2, "id_producto");
            query << consumidor << " " << producto << endl;
        }

        Value puntosAcumulados = nodo_consumidor.mymap()["puntosAcumulados"];

        getline(tabla_producto, producto);
        if (producto.empty()) break;

        Nodo nodo_producto(producto);
        Value puntosNec = nodo_producto.mymap()["puntosNec"];

        while (Value::compare(puntosNec, puntosAcumulados) <= 0) {
            size_t index_id_producto = producto.find("id");
            producto.replace(index_id_producto, 2, "id_producto");
            query << consumidor << " " << producto << endl;

            getline(tabla_producto, producto);
            if (producto.empty()) break;

            Nodo new_nodo_producto(producto);
            puntosNec = new_nodo_producto.mymap()["puntosNec"];

            cursor++;
        }

        getline(tabla_consumidor, consumidor);
    }

}


