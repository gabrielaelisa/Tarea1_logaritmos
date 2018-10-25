// tarea logaritmos p1 
#include <map>
#include <iostream>
#include <string>
#include <list>
#include <fstream>

using namespace std;

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

    // constructor de database, solo inicializa un archivo vacío
    Database() {
        myfile.open("p1.txt");
        myfile.close();
    }

    // escribe una linea en el archivo
    void add_nodo(Nodo *nodo) {
        string new_line = nodo->como_linea();
        myfile.open("p1.txt");
        myfile << new_line.append("\n");
        myfile.close();
    }

    // recibe la llave de la columna a ordenar
    // y el tamaño de la memoria principal
    void ordenar(string & s, unsigned long long M){
    }


};

int main() {
    string keys[] = {"id", "rut", "puntosAcumulados"};
    Value myvals[] = {Value((int) 1), Value("19136938-6"), Value((int) 1000)};
    Nodo *mynodo = new Nodo(keys, myvals, 3);
    bool is_in_map = mynodo->mymap().count("rut");
    string nodoline = mynodo->como_linea();
    cout << "el resultado de la llave es " << is_in_map;
    cout << "\n el resultado de la linea es " << nodoline;
    return 0;

}