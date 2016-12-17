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

#define VERBOSE(x, f, l) x; std::cout << f << ":" << l << " --> "  \
                            << #x << std::endl;
#define PRINT(x) std::cout << #x << "==" << x
#define PRINT_HDR(x) std::cout << std::endl << "==== " << x << " ====" << std::endl;

void SimplestUseCase() {
    PRINT_HDR(__FUNCTION__);
    
    class PropertyWrapper {
    private:
        int m_var;

    public:
        PropertyWrapper(const int& val) : m_var(val), property(m_var) {};

        Property<int> property;
        
        const int getVal() const { return m_var; }
        void setVal(int val) { m_var = val; }
    };

    PropertyWrapper obj(100);
    PRINT(obj.property) << "; ";
    PRINT(obj.getVal()) << std::endl;
    obj.property = 200;
    PRINT(obj.property) << "; ";
    PRINT(obj.getVal()) << std::endl;
    obj.setVal(300);
    PRINT(obj.property) << "; ";
    PRINT(obj.getVal()) << std::endl;
}

void PropertyInConstObject() {
    PRINT_HDR(__FUNCTION__);
    
    class PropertyWrapper {
    private:
        int m_var;

    public:
        PropertyWrapper(const int& val) : m_var(val), property(m_var) {};

        Property<int> property;
        
        const int getVal() const { return m_var; }
        void setVal(int val) { m_var = val; }
    };

    const PropertyWrapper obj(100);
    PRINT(obj.property) << "; ";
    PRINT(obj.getVal()) << std::endl;
//     obj.property = 200; //- compile error
//     obj.setVal(300); //- compile error
}

void ExplicitReadonlyProperty() {
    PRINT_HDR(__FUNCTION__);
    
    class PropertyWrapper {
    private:
        int m_var;

    public:
        PropertyWrapper(const int& val) : m_var(val), property(m_var) {};

        const Property<int> property; // readonly property
        
        const int getVal() const { return m_var; }
        void setVal(int val) { m_var = val; }
    };

    PropertyWrapper obj(100);
    PRINT(obj.property) << "; ";
    PRINT(obj.getVal()) << std::endl;

    // obj.property = 200; - compile error
    obj.setVal(200);
    PRINT(obj.property) << "; ";
    PRINT(obj.getVal()) << std::endl;
}

void AutoProperties() {
    PRINT_HDR(__FUNCTION__);
    
    std::cout << "---- typical use ----" << std::endl;
    Property<int> prop1;
    prop1 = 1234;
    PRINT(prop1) << std::endl << std::endl;
    
    std::cout << "---- Assign / Move of Auto-properties ----" << std::endl;
    auto prop2 = std::move(prop1); prop1 = 9876;
    PRINT(prop1) << "; ";
    PRINT(prop2) << std::endl;
    
    auto prop3 = prop1;
    PRINT(prop3) << std::endl;
}

void PropertiesWithCustomChecker() {
    PRINT_HDR(__FUNCTION__);
    
    Property<int> prop1([](const int& val) { return val % 2 == 0; });
        // only even numbers can be assigned to this auto-property.
    PRINT((prop1 = 2).IsAssigned) << "; "; PRINT(prop1) << std::endl;
    PRINT((prop1 = 3).IsAssigned) << "; "; PRINT(prop1) << std::endl;
    PRINT((prop1 = 4).IsAssigned) << "; "; PRINT(prop1) << std::endl;

    class PropertyWrapper {
    private:
        int m_var;

    public:
        PropertyWrapper()
            : evenOnly(m_var, [](const int& val) { return val%2 == 0; })
        {}
        Property<int> evenOnly;
        
        const int getVal() const { return m_var; }
        void setVal(int val) { m_var = val; }
    };

    PropertyWrapper obj; obj.setVal(0);
    PRINT((obj.evenOnly = 2).IsAssigned) << "; "; PRINT(obj.evenOnly) << std::endl;
    PRINT((obj.evenOnly = 3).IsAssigned) << "; "; PRINT(obj.evenOnly) << std::endl;
    PRINT((obj.evenOnly = 4).IsAssigned) << "; "; PRINT(obj.evenOnly) << std::endl;
}

int main(int argc, char** argv) {
    SimplestUseCase();
    PropertyInConstObject();
    ExplicitReadonlyProperty();
    AutoProperties();
    PropertiesWithCustomChecker();
    
    return 0;
}

