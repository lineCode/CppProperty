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
#define PRINT(x) #x << "==" << x
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

    VERBOSE(PropertyWrapper obj(100);, __FILE__, __LINE__);
    std::cout << PRINT(obj.property)
            << "; " << PRINT(obj.getVal()) << std::endl;
    VERBOSE(obj.property = 200;, __FILE__, __LINE__);
    std::cout << PRINT(obj.property)
            << "; " << PRINT(obj.getVal()) << std::endl;
    VERBOSE(obj.setVal(300);, __FILE__, __LINE__);
    std::cout << PRINT(obj.property)
            << "; " << PRINT(obj.getVal()) << std::endl;
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

    VERBOSE(const PropertyWrapper obj(100);, __FILE__, __LINE__);
    std::cout << PRINT(obj.property)
            << "; " << PRINT(obj.getVal()) << std::endl;
    // obj.property = 200; - compile error
    // obj.setVal(300); - compile error
}

void ExplicitReadonlyProperty() {
    PRINT_HDR(__FUNCTION__);
    
    class PropertyWrapper {
    private:
        int m_var;

    public:
        PropertyWrapper(const int& val) : m_var(val), property(m_var) {};

        const Property<int> property;
        
        const int getVal() const { return m_var; }
        void setVal(int val) { m_var = val; }
    };

    VERBOSE(PropertyWrapper obj(100);, __FILE__, __LINE__);
    std::cout << PRINT(obj.property)
            << "; " << PRINT(obj.getVal()) << std::endl;

    // obj.property = 200; - compile error
    VERBOSE(obj.setVal(200);, __FILE__, __LINE__);
    std::cout << PRINT(obj.property)
            << "; " << PRINT(obj.getVal()) << std::endl;
}

void AutoProperties() {
    PRINT_HDR(__FUNCTION__);
    
    std::cout << "---- typical use ----" << std::endl;
    VERBOSE(Property<int> prop;, __FILE__, __LINE__);
    VERBOSE(prop = 1234;, __FILE__, __LINE__);
    std::cout << PRINT(prop) << std::endl << std::endl;
    
    std::cout << "---- Use of Move Semantics with Auto-Property ----" << std::endl;
    VERBOSE(Property<int> prop2;, __FILE__, __LINE__);
    VERBOSE(prop2 = 9999;, __FILE__, __LINE__);
    VERBOSE(auto prop3 = std::move(prop2);, __FILE__, __LINE__);
    std::cout << PRINT(prop3) << std::endl << std::endl;
    
    try {
        std::cout << "---- Try using the 'moved-out' property ----" << std::endl;
        std::cout << __FILE__ << ":" << __LINE__ << " prop2==";
        std::cout << prop2 << std::endl;
    } catch(const std::exception &e) {
        std::cout << " >>>> EXCEPTION occurred; " << e.what() << ". "
                << __FILE__ << ":" << __LINE__
                << " <<<<" << std::endl;
    } catch(...) {
        std::cout << " >>>> UNKNOWN EXCEPTION occurred; "
                << __FILE__ << ":" << __LINE__
                << " <<<<" << std::endl;
    }
    std::cout << std::endl;

    try {
        std::cout << "---- Typical Referencing / Wrapping Property ----" << std::endl;
        VERBOSE(int dummy = 6666;, __FILE__, __LINE__);
        VERBOSE(Property<int> prop4(dummy);, __FILE__, __LINE__);
        std::cout << PRINT(prop4) << std::endl << std::endl;
        
        std::cout << "---- Try moving out the above Property ----" << std::endl;
        VERBOSE(auto prop5 = std::move(prop4);, __FILE__, __LINE__);
    } catch(const std::exception &e) {
        std::cout << " >>>> EXCEPTION occurred; " << e.what() << ". "
                << __FILE__ << ":" << __LINE__
                << " <<<<" << std::endl;
    } catch(...) {
        std::cout << " >>>> UNKNOWN EXCEPTION occurred; "
                << __FILE__ << ":" << __LINE__
                << " <<<<" << std::endl;
    }
}

int main(int argc, char** argv) {
//    SimplestUseCase();
//    PropertyInConstObject();
//    ExplicitReadonlyProperty();
    AutoProperties();
    return 0;
}

