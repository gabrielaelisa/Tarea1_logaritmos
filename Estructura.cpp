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
EstructuraBtree::EstructuraBtree(string atr): root(NULL),atributo(atr) {}

 
NodoBtree::NodoBtree(int _B, bool _hoja, string atributo) 
{ 
    // Copy the given minimum degree and leaf property 
    B=_B;
    hoja = _hoja; 
    llaves = (Nodo **)malloc(sizeof(Nodo*)*(((B-1)/2)+1)); 
    hijos = new NodoBtree *[((B-1)/2)+1]; 
    n = 0; 
} 

void EstructuraBtree::add_nodo(Nodo* nodo) 
{ 
    // si el arbol esta vacío 
    if (root == NULL) 
    { 
        root = new NodoBtree(B, true, atributo); 
        root->llaves[0] = nodo;  // inserta llave
        root->n = 1;  // hay 1 llave
    } 
    // el arbol no esta vacio
    else 
    {   
        // la raiz esta llena tiene B-1/2 llaves
        if (root->n == (B-1)/2) 
        { 
            NodoBtree *s = new NodoBtree(B, false, atributo); 
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
            root = s; // se cambia la raiz
        } 
        else 
            root->insertNonFull(nodo); 
    } 
} 
  
//se inserta una nueva llave en este nodo, que no esta lleno
void NodoBtree::insertNonFull(Nodo * nodo) 
{ 
    Value newval= nodo->mymap.Find(atributo)->second;
    int i = n-1; 
    if (hoja) 
    { 
        //encuentra la posicion de la nueva llave y realoca a los mayores
        while (i >= 0) 
        {   
            Value thisval= llaves[i]->mymap.Find(atributo)->second;
            if(!thisval.compare(thisval, newval))
                break;
            llaves[i+1] = llaves[i]; 
            i--; 
        } 
        //se inserta la nueva llave en la posicion encontrada
        llaves[i+1] = nodo; 
        n = n+1; 
    } 
    else 
    { 
        // Find the child which is going to have the new key 
        while (i >= 0)
        {
            Value thisval= llaves[i]->mymap.Find(atributo)->second;
            if(!thisval.compare(thisval, newval))
                break;
            i--;
        }
        // verificar si el hijo está lleno
        if (hijos[i+1]->n == (B-1)/2) 
        { 
            splitChild(i+1, hijos[i+1]); 
            Value thisval= llaves[i+1]->mymap.Find(atributo)->second;
            if (!thisval.compare(thisval,newval)) 
                i++; 
        } 
        hijos[i+1]->insertNonFull(nodo); 
    } 
} 
  
void NodoBtree::splitChild(int i, NodoBtree *y) 
{ 
    //un nuevo nodo guarda la mitad-1 de las llaves
    NodoBtree *z = new NodoBtree(y->B, y->hoja, atributo); 
    z->n = (B -2)/4; 
  
    // Copy the last (t-1) keys of y to z 
    for (int j = 0; j < (B -2)/4; j++) 
        z->llaves[j] = y->llaves[j+(B /4)]; 
  
    // Copy the last t children of y to z 
    if (!y->hoja) 
    { 
        for (int j = 0; j < (B/4); j++) 
            z->hijos[j] = y->hijos[j+(B/4)]; 
    } 
  
    // Reduce the number of keys in y 
    y->n = (B -2)/4; 
  
    // se crea espacio para el nuevo hijo
    for (int j = n; j >= i+1; j--) 
        hijos[j+1] = hijos[j]; 
  
    hijos[i+1] = z; 
  
    // A key of y will move to this node. Find location of 
    // new key and move all greater keys one space ahead 
    for (int j = n-1; j >= i; j--) 
        llaves[j+1] = llaves[j]; 
  
    // Copy the middle key of y to this node 
    llaves[i] = y->llaves[(B -2)/4]; 
  
    n = n + 1; 
} 