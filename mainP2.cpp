#include <iostream>
#include <math.h>
#include <random>

#include "Nodo.h"
#include "Database.h"
using namespace std;

int main() 
{ 
    EstructuraBtree t("id"); // arbol B que inserta nodos segun el campo id
    string keys[] = {"id", "rut", "puntosAcumulados"};
    Value myvals[] = {Value((int) 1), Value("19136938-6"), Value((int) 1000)};
    Nodo nodo(keys, myvals, 3);
    t.add_nodo(&nodo);
}