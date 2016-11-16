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
#include "property.h"

class Dummy {
private:
    int m_var;
    
    bool OnSet(const int val) { return val != 0; }
    bool OnGet(const int val) { return val != 0; }
public:
    Property<int> p1, p2;
    const Property<int> p3;
    Dummy(const int& val) : m_var(val),
        p1(m_var,
            [this](const int val) { return OnSet(val); },
            [this](const int val) { return OnGet(val); }
        ), p2(m_var), p3(m_var) {};
    
    int getVal() { return m_var; }
};

int main(int argc, char** argv) {
    Dummy d1(100);
    const Dummy d2(999);
    
    d1.p1 = 222;
    std::cout << d1.p3 << std::endl;
    std::cout << d2.p3 << std::endl;
    std::cout << (d1.p1 = -1) << std::endl;
    std::cout << d1.p3 << std::endl;
    std::cout << d2.p2 << std::endl;
    return 0;
}

