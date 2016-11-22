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

public:
    Dummy(const int& val) : m_var(val), Value(m_var), ConstValue(m_var) {
        autoValue = 999;
    };

    Property<int> autoValue;
    Property<int> Value;
    const Property<int> ConstValue;
    int getVal() const { return m_var; }
};

int main(int argc, char** argv) {
    Dummy dummy(100);
    std::cout << dummy.Value << " " << dummy.getVal() << std::endl;

    dummy.Value = 200;
    std::cout << dummy.ConstValue << " " << dummy.getVal() << std::endl;
    
    std::cout << dummy.autoValue << " " << std::endl;
    dummy.autoValue = 666;
    std::cout << dummy.autoValue << " " << std::endl;
    return 0;
}

