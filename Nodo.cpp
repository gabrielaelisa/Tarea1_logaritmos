#include <iostream>
#include <vector>
#include <algorithm>
#include "Nodo.h"

Nodo::Nodo(string *column, Value *value, int len) {
    for (int i = 0; i < len; i++) {
        string key = column[i];
        Value val = value[i];
        fila.insert(make_pair(key, val));

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

bool is_number(const string &s) {
    return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

Nodo Nodo::como_nodo(string s) {
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
        pos = s.find(delimiter);
        token = s.substr(0, pos); // token es de la forma "atributo: valor"
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
        s.erase(0, pos + delimiter.length());

        // se aumenta el largo
        len++;

        // si se llega al final termina el ciclo
        if (pos == string::npos)
            break;
    }

    //los vectores se deben transformar a arreglos
    string* array_atributos = &atributos[0];
    Value* array_valores = &valores[0];
    
    return Nodo(array_atributos, array_valores, len);
}
