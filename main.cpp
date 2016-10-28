/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: srivathsan
 *
 * Created on 27 October, 2016, 4:30 PM
 */

#include <iostream>

template <typename T>
class Property {
public:
    Property(T& var) : m_data(var) {};
    Property(const T& var) : m_data(var) {};
    Property(const Property<T>& prop) : m_data(prop.m_data) {};
    
    const T operator= (const T& value) {
        m_data = value;
        return value;
    }
    const T operator*() const {
        return m_data;
    }

private:
    T& m_data;
};

class Dummy {
private:
    int m_var;
public:
    Property<int> p;
    Dummy(int val) : m_var(val), p(m_var) {};
    
    int getVal() { return m_var; }
};

int main(int argc, char** argv) {
    Dummy d(100);
    
    std::cout << *d.p << std::endl;
    d.p = 111;
    std::cout << *d.p << std::endl;
    return 0;
}

