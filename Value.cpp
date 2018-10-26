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

int Value::compare(Value v) {
    Value::DATA_TYPE type = v.type();
    if (m_type != type)
        throw runtime_error("Values no coinciden");

    switch (type) {
        case Value::DATA_TYPE::INT:
            if (*(int *)m_ptr > *(int *)v.m_ptr)
                return 1;
            else if (*(int *)m_ptr == *(int *)v.m_ptr)
                return 0;
            else
                return -1;
        case Value::DATA_TYPE::STRING:
            return (*(string *)m_ptr).compare(*(string *)v.m_ptr);
    }
}
