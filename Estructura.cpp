#include <utility>
#include <iostream>

#include "Estructura.h"

EstructuraArchivo::EstructuraArchivo(string filename, long long M) : filename(std::move(filename)), M(M) {}

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

void EstructuraArchivo::merge(long long l, long long m, long long r) {

    // TODO: este es como el esqueleto del merge tipico, hay que adaptarlo a este caso

//    long long i, j, k;
//    long long n1 = m - l + 1;
//    long long n2 =  r - m;
//
//    /* create temp arrays */
//    int L[n1], R[n2];
//
//    /* Copy data to temp arrays L[] and R[] */
//    for (i = 0; i < n1; i++)
//        L[i] = arr[l + i];
//    for (j = 0; j < n2; j++)
//        R[j] = arr[m + 1+ j];
//
//    /* Merge the temp arrays back into arr[l..r]*/
//    i = 0; // Initial index of first subarray
//    j = 0; // Initial index of second subarray
//    k = l; // Initial index of merged subarray
//    while (i < n1 && j < n2)
//    {
//        if (L[i] <= R[j])
//        {
//            arr[k] = L[i];
//            i++;
//        }
//        else
//        {
//            arr[k] = R[j];
//            j++;
//        }
//        k++;
//    }
//
//    /* Copy the remaining elements of L[], if there
//       are any */
//    while (i < n1)
//    {
//        arr[k] = L[i];
//        i++;
//        k++;
//    }
//
//    /* Copy the remaining elements of R[], if there
//       are any */
//    while (j < n2)
//    {
//        arr[k] = R[j];
//        j++;
//        k++;
//    }
}

void EstructuraArchivo::ordenarTrozo(const string &atributo) {
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

void EstructuraArchivo::mergeSort(const string &atributo, long long l, long long r, bool first) {

    if (first)
        this->outfile.seekp(0, std::ofstream::beg);

    if (r - l >= M) { // si el pedazo a ordenar es mayor o igual a M

        long long m = l + (r - l) / 2;

        // se ordenan ambas mitades
        mergeSort(atributo, l, m, false);
        mergeSort(atributo, m + 1, r, false);

        merge(l, m, r);
    } else {
        ordenarTrozo(atributo);
    }
}

void EstructuraArchivo::ordenar(const string &atributo, long long size) {
    mergeSort(atributo, 0, size - 1, true);
}


/* implementacion del constructor de btree
 * por razones de implementacion ausmimos que B cabe 10000 en M
 */
//EstructuraBtree::EstructuraBtree( long long M, string atr): B(M/ 10000), atributo(atr) {}
