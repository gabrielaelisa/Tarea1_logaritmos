#include <utility>
#include <iostream>
#include <limits>

#include "Estructura.h"

/*
 * Implementacion de constructor de EstructuraArchivo
 */
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

void EstructuraArchivo::merge(const string &atributo, long long l, long long m, long long r) {

    long long i, j;

    // se obtiene la cantidad de elementos por lado
    long long n1 = m - l + 1;
    long long n2 =  r - m;

    // archivos que representan el arreglo de la izquierda y derecha
    fstream L(filename);
    fstream R(filename);

    // archivo de resultado
    ofstream K("tempResult");

    i = 0; // indice inicial del arreglo de la izquierda
    j = 0; // indice inicial del arreglo de la derecha

    // se posiciona en los lugares correspondientes del archivo
    GoToLine(L, l);
    GoToLine(R, m + 1);

    string inputL, inputR;


    // merge
    while (i < n1 && j < n2) {

        // se guarda posicion actual
        streampos oldposL = L.tellg();
        streampos oldposR = R.tellg();

        // se leen las lineas
        getline(L, inputL);
        getline(R, inputR);

        // se crean nodos
        Nodo nodoL(inputL);
        Nodo nodoR(inputR);

        // se obtienen valores
        Value valL = nodoL.mymap()[atributo];
        Value valR = nodoR.mymap()[atributo];

        if (Value::compare(valL, valR) <= 0) { // L[i] <= R[j]
            K << inputL << endl; // arr[k] = L[i];
            R.seekg(oldposR); // como R no avanza vuelve una linea
            i++;
        }
        else {
            K << inputR << endl; // arr[k] = R[j];
            L.seekg(oldposL); // como L no avanza vuelve una linea
            j++;
        }
    }

    // se copian los elementos restantes en L si quedan
    while (i < n1) {
        getline(L, inputL);
        K << inputL << endl;
        i++;
    }

    // se copian los elementos restantes en R si quedan
    while (j < n2) {
        getline(R, inputR);
        K << inputR << endl;
        j++;
    }


    // se copia el resultado en el archivo original
    string output;
    fstream file(filename);
    ifstream res("tempResult");
    GoToLine(file, l);
    getline(res, output);
    while (!output.empty()) {
        file << output << endl;
        getline(res, output);
    }


    // se borra el archivo temporal
    remove("tempResult");
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

    if (r - l > M) { // si el pedazo a ordenar es mayor a M

        long long m = (l + (r - l) / 2);

        // se ordenan ambas mitades
        mergeSort(atributo, l, m, false);
        mergeSort(atributo, m + 1, r, false);

        merge(atributo, l, m, r);
    } else {
        ordenarTrozo(atributo);
    }
}

void EstructuraArchivo::ordenar(const string &atributo, long long size) {
    mergeSort(atributo, 0, size - 1, true);
}

fstream &EstructuraArchivo::GoToLine(fstream &file, long long num) {
    file.seekg(ios::beg);
    for (int i = 0; i < num; ++i) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return file;
}


EstructuraBtree::EstructuraBtree(string atr): root(NULL),atributo(atr) {}

void EstructuraBtree::ordenar(const string &atributo , long long M){}

Nodo * EstructuraBtree::buscar(Nodo* nodo){
    return (root == NULL)? NULL : root->buscar(nodo);
}

 
NodoBtree::NodoBtree(int _B, bool _hoja, string _atributo) 
{ 
    // Copy the given minimum degree and leaf property 
    B=_B;
    hoja = _hoja; 
    llaves = (Nodo **)malloc(sizeof(Nodo*)*((B-1)/2)); 
    hijos = new NodoBtree *[((B-1)/2)+1]; 
    n = 0; 
    atributo= _atributo;
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

            Value newval= (nodo->mymap()).find(atributo)->second;
            Value thisval= (s->llaves[0])->mymap().find(atributo)->second;
            int i = 0; 
            //thisval < newval
            if (thisval.compare(thisval,newval)!=1) 
                i++; 
            s->hijos[i]->insertar(nodo); 
            root = s; // se cambia la raiz
        } 
        else 
            root->insertar(nodo); 
    } 
} 
  
//se inserta una nueva llave en este nodo, que no esta lleno
void NodoBtree::insertar(Nodo * nodo) 
{ 
    Value newval= nodo->mymap().find(atributo)->second;
    int i = n-1; 
    if (hoja) 
    { 
        //encuentra la posicion de la nueva llave y realoca a los mayores
        while (i >= 0) 
        {   
            Value thisval= llaves[i]->mymap().find(atributo)->second;
            if(thisval.compare(thisval, newval)!=1)
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
            Value thisval= llaves[i]->mymap().find(atributo)->second;
            if(thisval.compare(thisval, newval)!=1)
                break;
            i--;
        }
        // verificar si el hijo está lleno
        if (hijos[i+1]->n == (B-1)/2) 
        { 
            splitChild(i+1, hijos[i+1]); 
            Value thisval= llaves[i+1]->mymap().find(atributo)->second;
            if (thisval.compare(thisval,newval)!=1) 
                i++; 
        } 
        hijos[i+1]->insertar(nodo); 
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

Nodo* NodoBtree::buscar(Nodo * nodo) 
{ 
    Value newval= nodo->mymap().find(atributo)->second; 
    //buscar la primera llave mayor o igual al nodo
    int i = 0;
    while (i < n){
        Value thisval= llaves[i]->mymap().find(atributo)->second; 
        //newval>thisval
        if(Value::compare(newval,thisval)!=1){
            break;
        }
        i++; 
    }
    
    
    if ((llaves[i]->equal(nodo))==true){
        return llaves[i]; 
        }
  
    else if (hoja == true){
        return NULL; }
  
    return hijos[i]->buscar(nodo); 
} 
