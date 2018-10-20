// tarea logaritmos p1 
#include <map>
#include <iostream>
#include <string>
#include <list>


using namespace std;
//clase que contiene un atributo o string, o int
class Value {
public:
    enum DATA_TYPE
    {
        STRING,
        INT
    };
    
    // existen dos constructores, uno para el type string,
    // otro para el type int
    Value(int value)
        : m_type(DATA_TYPE::INT), m_ptr(new int(value)){}
    Value(const string & value)
        : m_type(DATA_TYPE::STRING), m_ptr(new string(value)){}

     DATA_TYPE type()
    {
        return m_type;
    }
    private:
        DATA_TYPE m_type;
        void *m_ptr;
};

/* clase nodo, esta es la clase del enunciado,
tiene como unico atributo un diccionario,
en el constructor recibe como input dos listas una de llaves de 
columnas y otra de valores */
class Nodo {
public:
    map<string, Value> fila;
    
    Nodo(string column[], Value value[], int len){
        for (int i=0; i< len; i++){
            string key= column[i];
            Value val= value[i];
            fila.insert(make_pair(key, val));

        }
    }
     map<string, Value> mymap(){
        return fila;
    }

};

int main()

{
    string keys[]={"id", "rut", "puntosAcumulados"};
    Value myvals[]= {Value((int) 1), Value("19136938-6"), Value((int)1000)};
    Nodo * mynodo= new Nodo(keys, myvals, 3);
    bool is_in_map = mynodo->mymap().count("rut");
    cout<<"el resultado de la llave es " << is_in_map;
    return 0;

}