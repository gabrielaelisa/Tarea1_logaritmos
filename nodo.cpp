// tarea logaritmos p1 
#include <map>
#include <iostream>
#include <string>
#include <list>
#include <fstream>

using namespace std;

class Estructura {
public:
    virtual void add_nodo(Nodo *nodo);
    virtual void ordenar(string &atributo, long long l, long long r);
};

class EstructuraArchivo: public Estructura {
public:
    void add_nodo(Nodo *nodo) {

    }

private:
    ofstream file;
};

//clase que contiene un atributo o string, o int
class Value {
public:
    enum DATA_TYPE {
        STRING,
        INT
    };

    // existen dos constructores, uno para el type string,
    // otro para el type int
    Value(int value)
            : m_type(DATA_TYPE::INT), m_ptr(new int(value)) {}

    Value(const string &value)
            : m_type(DATA_TYPE::STRING), m_ptr(new string(value)) {}

    DATA_TYPE type() {
        return m_type;
    }

    void *val() {
        return (void *) m_ptr;
    }

private:
    DATA_TYPE m_type;
    void *m_ptr;
};

/* clase nodo, esta es la clase del enunciado,
tiene como unico atributo un diccionario,
en el constructor recibe como input dos arreglos una de llaves de 
columnas y otra de valores */
class Nodo {
public:
    map<string, Value> fila;
    int mylen;

    Nodo(string column[], Value value[], int len) {
        for (int i = 0; i < len; i++) {
            string key = column[i];
            Value val = value[i];
            fila.insert(make_pair(key, val));

        }
        mylen=len;
    }

    map<string, Value> mymap() {
        return fila;
    }

    // esta es la funcion que serializa Nodo a una linea
    // se utiliza en la implementacion de la clase database
    string como_linea() {
        map<string, Value>::iterator it;
        string mystr;

        for (it = fila.begin(); it != fila.end(); it++) {
            if (it != fila.begin()) {
                mystr.append(", ");
            }
            mystr.append(it->first);
            mystr.append(": ");
            Value::DATA_TYPE type = it->second.type();
            switch (type) {
                case Value::DATA_TYPE::INT:
                    mystr.append(to_string(*(int *) it->second.val()));
                    break;
                case Value::DATA_TYPE::STRING:
                    mystr.append(*(string *) (it->second.val()));
                    break;
            }
        }
        return mystr;
    }

};

/* clase database, permite agregar nodos
primera implementacion es solamente un archivo de texto*/
class Database {
    ofstream myfile;
    Estructura * estructura;

    // constructor de database, solo inicializa un archivo vacío
    Database() {
        estructura = new Estructura();
        /*
        myfile.open("p1.txt");
        myfile.close();
         */
    }

    // escribe una linea en el archivo
    void add_nodo(Nodo *nodo) {
        estructura->add_nodo(nodo);
        /*
        string new_line = nodo->como_linea();
        myfile.open("p1.txt");
        myfile << new_line.append("\n");
        myfile.close();
         */
    }

    // recibe la llave de la columna a ordenar
    // y el tamaño de la memoria principal
    void ordenar(string & atributo, long long l, long long r, unsigned long long M) {
        if (r - l >= M) {
            // Same as (l+r)/2, but avoids overflow for
            // large l and h
            int m = l + (r - l) / 2;

            // Sort first and second halves
            ordenar(estructura, l, m);
            ordenar(estructura, m + 1, r);

            merge(arr, l, m, r);
        } else {
            estructura.ordenar(atributo, l, r);
        }
    }


};

int main(int argc, char *argv[]) {
    if (argc == 3)
        const unsigned long long M = stoll(argv[2]);
    else
        const unsigned long long M = 100000;
    string keys[] = {"id", "rut", "puntosAcumulados"};
    Value myvals[] = {Value((int) 1), Value("19136938-6"), Value((int) 1000)};
    Nodo *mynodo = new Nodo(keys, myvals, 3);
    bool is_in_map = mynodo->mymap().count("rut");
    string nodoline = mynodo->como_linea();
    cout << "el resultado de la llave es " << is_in_map;
    cout << "\n el resultado de la linea es " << nodoline << endl;
    return 0;

}