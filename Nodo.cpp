#include <iostream>
#include <vector>
#include <algorithm>
#include "Nodo.h"

Nodo::Nodo(string *column, Value *value, int len) {
    for (int i = 0; i < len; i++) {
        string key = column[i];
        Value val = value[i];
        fila[key] = val;

    }
    mylen = len;
}

bool is_number(const string &s) {
    return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

Nodo::Nodo(string line) {
    string delimiter = ", ";
    string atributo_delimeter = ": ";
    size_t pos = 0;
    size_t pos_token = 0;
    string token;
    string atributo;
    vector<string> atributos;
    vector<Value> valores;
    int len = 0;
    while (true) {
        pos = line.find(delimiter);
        token = line.substr(0, pos); // token es de la forma "atributo: valor"
        pos_token = token.find(atributo_delimeter); // se separa el token en atributo y valor

        // se obtiene el atributo y se guarda
        atributo = token.substr(0, pos_token);
        atributos.push_back(atributo);

        token.erase(0, pos_token + atributo_delimeter.length()); // ahora token es solo el valor

        // se genera un value, el cual puede ser numerico o un string, y se guarda
        Value val = Value(token);
        if (is_number(token))
            val = Value(stoi(token));
        valores.push_back(val);

        // se avanza en el string
        line.erase(0, pos + delimiter.length());

        // se aumenta el largo
        len++;

        // si se llega al final termina el ciclo
        if (pos == string::npos)
            break;
    }

    for (int i = 0; i < len; i++) {
        string key = atributos[i];
        Value val = valores[i];
        fila[key] = val;

    }

    mylen = len;
}

map<string, Value> Nodo::mymap() {
    return fila;
}

string Nodo::como_linea() {
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

bool Nodo::equal(Nodo * otro_nodo){
    // otro map
    map<string, Value> om= otro_nodo->mymap();
    // this map
    map<string, Value> tm= fila;
    //tamaños diferentes
    if(tm.size() != om.size()){return false;} 

    typename map<string, Value>::iterator i, j;
    for(i = tm.begin(), j = om.begin(); j != om.end(); i++, j++)
    {
        Value v1 = i->second;
        Value v2 = j->second;
        if(Value::compare(v1,v2)!=0){return false;}
        
    }
    return true;
}
