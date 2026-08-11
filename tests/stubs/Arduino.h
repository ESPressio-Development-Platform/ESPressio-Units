#pragma once

#include <string>

class String {
    private:
        std::string _value;

    public:
        String(const char* value = "") : _value(value) { }

        String& operator+=(const char* value) {
            _value += value;
            return *this;
        }

        const char* c_str() const {
            return _value.c_str();
        }
};
