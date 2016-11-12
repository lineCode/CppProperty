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

#include <utility>
#include <functional>

template <typename T>
class Property {
public:
    typedef std::function<bool (const T&)> Handler;

    Property(const T& var) = delete;
    Property(Property<T>&& prop) = delete;
    Property(
            T& var, Handler onSet = DEFAULT, Handler onGet = DEFAULT
        ) : m_data(var), OnSet(onSet), OnGet(onGet) {};
    Property(const Property<T>& prop)
        : m_data(prop.m_data), OnSet(prop.OnSet), OnGet(prop.OnGet) {};
    
    const T operator=(const T& val) {
        if (!OnSet(val)) throw nullptr;
        return (m_data = val);
    }
    operator const T() const{
        if (!OnGet(m_data)) throw nullptr;
        return m_data;
    }
    
private:
    static bool DEFAULT(const T&) { return true; };
    Handler OnSet, OnGet;
    T& m_data;
};

#endif /* PROPERTY_H */

