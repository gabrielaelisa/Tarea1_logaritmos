#include <utility>
#include <iostream>

#include "Estructura.h"

EstructuraArchivo::EstructuraArchivo(string filename) : filename(std::move(filename)) {}

void EstructuraArchivo::add_nodo(Nodo *nodo) {
    string new_line = nodo->como_linea();
    if(!outfile.is_open()){
        outfile.open(filename);
    }
    outfile << new_line << endl;
}


// Comparador que se basa en el metodo compare de Value
struct cmpByValueCompare {
    bool operator()(const Value &a, const Value &b) const {
        return Value::compare(a, b) == -1;
    }
};

void EstructuraArchivo::ordenar(const string &atributo, long long M) {
    // si no se han abierto los archivos se abren
    if (!infile.is_open())
        infile.open(filename);
    if (!outfile.is_open())
        outfile.open(filename);

    long long i = 0;
    string line;

    // mapa con los nodos, el cual se ordena cada vez que se inserta un elemento
    map<Value, Nodo*, cmpByValueCompare> nodos;

    while (i < M) {
        getline(infile, line);
        if (line.empty()) break;
        Nodo *n = new Nodo(line);
        map<string, Value> mapa = n->mymap();
        Value v;
        v = mapa[atributo];
        nodos[v] = n; // la llave es el atributo por el cual se ordena
        i++;
    }

    // se escriben los nodos en el archivo
    for (auto &nodo : nodos) {
        outfile << nodo.second->como_linea() << endl;
    }
}

void EstructuraArchivo::startOrdenar() {
    outfile.seekp(0, std::ofstream::beg);
    //outfile.close();
}

void EstructuraArchivo::endOrdenar() {}

/* implementacion del constructor de btree
 * por razones de implementacion ausmimos que B cabe 10000 en M
 */
//EstructuraBtree::EstructuraBtree( long long M, string atr): B(M/ 10000), atributo(atr) {}
