/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   property.h
 * Author: srivathsan
 *
 * Created on 12 November, 2016, 8:03 PM
 */

#ifndef PROPERTY_H
#define PROPERTY_H

#include <functional>

template <typename T> // T is a trivially copy-able / assignable type
class Property {
public:
    typedef std::function<bool (const T&)> Handler;

    Property(const Property<T>& prop) = delete;
    Property(Property<T>&& prop)      = delete;
    Property(
            const T& var, Handler onSet = DEFAULT, Handler onGet = DEFAULT
        ) : m_data(var), OnSet(onSet), OnGet(onGet) {};
    Property(
            T& var, Handler onSet = DEFAULT, Handler onGet = DEFAULT
        ) : m_data(var), OnSet(onSet), OnGet(onGet) {};
    
    const T operator=(const T& val) {
        if (!OnSet(val)) throw "OnSet() validation failed";
        return (m_data = val); 
    }
    operator const T() const{
        if (!OnGet(m_data)) throw "OnGet() validation failed";
        return m_data;
    }
    
protected: // to support derived implementations
    static bool DEFAULT(const T&) { return true; };
    Handler OnSet, OnGet;
    T& m_data;
};

#endif /* PROPERTY_H */

