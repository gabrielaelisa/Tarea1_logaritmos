#include "Nodo.h"

Nodo::Nodo(string *column, Value *value, int len) {
    for (int i = 0; i < len; i++) {
        string key = column[i];
        Value val = value[i];
        fila.insert(make_pair(key, val));

    }
    mylen=len;
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
