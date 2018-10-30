#include <stdexcept>
#include "Value.h"

Value::Value(int value) : m_type(DATA_TYPE::INT), m_ptr(new int(value)) {}

Value::Value(const string &value) : m_type(DATA_TYPE::STRING), m_ptr(new string(value)) {}

Value::DATA_TYPE Value::type() {
    return m_type;
}

void *Value::val() {
    return m_ptr;
}

int Value::compare(Value v1, Value v2) {
    Value::DATA_TYPE type1 = v1.type();
    Value::DATA_TYPE type2 = v2.type();
    if (type1 != type2)
        throw runtime_error("Values no coinciden");

    switch (type1) {
        case Value::DATA_TYPE::INT:
            if (*(int *)v1.m_ptr > *(int *)v2.m_ptr)
                return 1;
            else if (*(int *)v1.m_ptr == *(int *)v2.m_ptr)
                return 0;
            else
                return -1;
        case Value::DATA_TYPE::STRING:
            return (*(string *)v1.m_ptr).compare(*(string *)v2.m_ptr);
    }
}
