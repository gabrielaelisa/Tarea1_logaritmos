#include <iostream>
#include <math.h>
#include <random>
#include <fstream>
#include <chrono>
#include <ctime>
#include "Nodo.h"
#include "Database.h"
using namespace std;

Nodo ** crear_nodos(int N){
    Nodo ** nodos = (Nodo **)malloc(sizeof(Nodo*)*N); 
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
        Nodo* n=  new Nodo(keys, myvals, 3);
        nodos[i]= n;
    
    }
    return nodos;


}

int main(int argc, char *argv[]) 
{ 
     if (argc < 3) {
        cout << "Falta ingresar N y nombre de columna por la cual ordenar";
        return -1;
    }
    int N = static_cast<int>(pow(10, stoi(argv[1])));
    string col = static_cast<string>(argv[2]);
    EstructuraBtree t(col); // arbol B que inserta nodos segun el campo id
    Nodo ** nodos = crear_nodos(N);
    auto begin = std::chrono::high_resolution_clock::now();
    for(int i=0; i< N; i++){
        t.add_nodo(nodos[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << "ns" << std::endl;

    /*
    string keys[] = {"id", "rut", "puntosAcumulados"};
    Value myvals[] = {Value((int) 1), Value("19136938-6"), Value((int) 1000)};
    Value myvals2[] = {Value((int) 2), Value("19136938-6"), Value((int) 1000)};
    Nodo nodo(keys, myvals, 3);
    Nodo nodo2(keys, myvals2, 3);
    t.add_nodo(&nodo);
    t.add_nodo(&nodo2);
    Nodo * result=t.buscar(&nodo2);
    string s=result->como_linea();
    cout << "\n el resultado de la linea es " << s << endl;
    */
}