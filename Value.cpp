#include "Value.h"

Value::Value(int value) : m_type(DATA_TYPE::INT), m_ptr(new int(value)) {}

Value::Value(const string &value) : m_type(DATA_TYPE::STRING), m_ptr(new string(value)) {}

Value::DATA_TYPE Value::type() {
    return m_type;
}

void *Value::val() {
    return (void *) m_ptr;
}
