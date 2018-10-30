#include <utility>

#include "Estructura.h"

EstructuraArchivo::EstructuraArchivo(string filename) : filename(std::move(filename)), open(false) {}

void EstructuraArchivo::add_nodo(Nodo *nodo) {
    string new_line = nodo->como_linea();
    outfile.open(filename);
    outfile << new_line << endl;
    outfile.close();
}


// Comparador que se basa en el metodo compare de Value
struct cmpByValueCompare {
    bool operator()(const Value &a, const Value &b) const {
        return Value::compare(a, b) == -1;
    }
};

void EstructuraArchivo::ordenar(const string &atributo, long long M) {
    if (!open) { // si no se han abierto los archivos se abren
        infile.open(filename);
        outfile.open(filename);
    }

    long long i = 0;
    string line;

    // mapa con los nodos, el cual se ordena cada vez que se inserta un elemento
    map<Value, Nodo, cmpByValueCompare> nodos;

    while (i < M) {
        getline(infile, line);
        Nodo n = Nodo::como_nodo(line);
        nodos[n.mymap()[atributo]] = n; // la llave es el atributo por el cual se ordena
        i++;
    }

    // se escriben los nodos en el archivo
    for (auto &nodo : nodos) {
        outfile << nodo.second.como_linea() << endl;
    }
}

/* implementacion del constructor de btree
 * por razones de implementacion ausmimos que B cabe 10000 en M
 */
EstructuraBtree::EstructuraBtree( long long M, string atr): B(M/ 10000), atributo(atr) {}
