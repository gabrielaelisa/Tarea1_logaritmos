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

/* implementacion del constructor de btree
 * por razones de implementacion ausmimos que B cabe 10000 en M
 */
EstructuraBtree::EstructuraBtree( long long M, string atr): atributo(atr) {}

void EstructuraBtree::add_nodo(Nodo* nodo) 
{ 
    // si el arbol esta vacío 
    if (root == NULL) 
    { 
        root = new BtreeNode(B, true); 
        root->llaves[0] = nodo;  // inserta llave
        root->n = 1;  // hay 1 llave
    } 
    // el arbol no esta vacio
    else 
    {   
        // la raiz esta llena tiene B-1/2 llaves
        if (root->n == (B-1)/2) 
        { 
            BtreeNode *s = new BtreeNode(B, false); 
            // la raiz antigua es hija de la nueva 
            s->hijos[0] = root; 
            s->splitChild(0, root); 

            Value newval= nodo->mymap.Find(atributo)->second;
            Value thisval= (s->llaves[0])->mymap.Find(atributo)->second;
            int i = 0; 
            //thisval < newval
            if (!thisval.compare(thisval,newval)) 
                i++; 
            s->hijos[i]->insertNonFull(nodo); 
  
            // Change root 
            root = s; 
        } 
        else  // If root is not full, call insertNonFull for root 
            root->insertNonFull(nodo); 
    } 
} 
  
//se inserta una nueva llave en este nodo, que no esta lleno
void BtreeNode::insertNonFull(Nodo * nodo) 
{ 
    // Initialize index as index of rightmost element 
    int i = n-1; 

    if (hoja) 
    { 
        // The following loop does two things 
        // a) Finds the location of new key to be inserted 
        // b) Moves all greater keys to one place ahead 
        while (i >= 0 && llaves[i] > k) 
        { 
            llaves[i+1] = llaves[i]; 
            i--; 
        } 
  
        // Insert the new key at found location 
        llaves[i+1] = k; 
        n = n+1; 
    } 
    else // If this node is not leaf 
    { 
        // Find the child which is going to have the new key 
        while (i >= 0 && llaves[i] > k) 
            i--; 
  
        // See if the found child is full 
        if (C[i+1]->n == 2*t-1) 
        { 
            // If the child is full, then split it 
            splitChild(i+1, C[i+1]); 
  
            // After split, the middle key of C[i] goes up and 
            // C[i] is splitted into two.  See which of the two 
            // is going to have the new key 
            if (keys[i+1] < k) 
                i++; 
        } 
        C[i+1]->insertNonFull(k); 
    } 
} 
  
void BtreeNode::splitChild(int i, BtreeNode *y) 
{ 
    // Create a new node which is going to store (t-1) keys 
    // of y 
    BtreeNode *z = new BtreeNode(y->t, y->leaf); 
    z->n = t - 1; 
  
    // Copy the last (t-1) keys of y to z 
    for (int j = 0; j < t-1; j++) 
        z->keys[j] = y->keys[j+t]; 
  
    // Copy the last t children of y to z 
    if (y->leaf == false) 
    { 
        for (int j = 0; j < t; j++) 
            z->C[j] = y->C[j+t]; 
    } 
  
    // Reduce the number of keys in y 
    y->n = t - 1; 
  
    // Since this node is going to have a new child, 
    // create space of new child 
    for (int j = n; j >= i+1; j--) 
        C[j+1] = C[j]; 
  
    // Link the new child to this node 
    C[i+1] = z; 
  
    // A key of y will move to this node. Find location of 
    // new key and move all greater keys one space ahead 
    for (int j = n-1; j >= i; j--) 
        keys[j+1] = keys[j]; 
  
    // Copy the middle key of y to this node 
    keys[i] = y->keys[t-1]; 
  
    // Increment count of keys in this node 
    n = n + 1; 
} 