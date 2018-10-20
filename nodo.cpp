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
    Value(std::string& value)
        : m_type(DATA_TYPE::STRING), m_ptr(new std::string(value)){}
  
};

/* clase nodo, esta es la clase del enunciado,
tiene como unico atributo un diccionario,
en el constructor recibe como input dos listas una de llaves de 
columnas y otra de valores */
class Nodo {
public:
    map<string, Value> fila;

    Nodo(list<int> column, list<Value> value) {

        int len = column.size();
        for(int i=0; i< len; i++){
            string key= column.front();
            column.pop_front();
            Value::DATA_TYPE type = value.front().type();
            switch (type) {
                case Value::DATA_TYPE::INT:
                fila.insert(std::make_pair<string,int>(key, value.front()));
                break;

                case Value::DATA_TYPE::STRING:
                fila.insert(std::make_pair<string,string>(key, value.front()));
                break;
            }
            value.pop_front();

        
    }
    }
}