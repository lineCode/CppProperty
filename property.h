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
#include <utility>

template <typename T> // T is a trivially copy-able/assignable/move-able type
class Property {
public:
    typedef std::function<void (const T&)> Setter;
    typedef std::function<const T ()> Getter;

    Property(const Property<T>& prop) : m_ref(m_val), m_val(prop.m_val) {
        if (&prop.m_ref != &prop.m_val) {
            throw "Only auto-properties can be copy-constructed";
        }
    }
    Property(Property<T>&& prop) : m_ref(m_val), m_val(std::move(prop.m_val)) {
        if (&prop.m_ref != &prop.m_val) {
            throw "Only auto-properties can be move-constructed";
        }
    }
    Property(
            T& var, Setter onSet = nullptr, Getter onGet = nullptr
        ) : m_ref(var)
    {
        InitHandlers(onSet, onGet);
    };
    Property(
            const T& var, Setter onSet = nullptr, Getter onGet = nullptr
        ) : m_ref(var)
    {
        InitHandlers(onSet, onGet);
    };
    Property(Setter onSet = nullptr) : m_ref(m_val) { // ctor for auto-property
        Getter onGet = nullptr;
        InitHandlers(onSet, onGet);
    }
    
    const T operator=(const T& val) { Set(val); }
    operator const T() const        { return Get(); }
    
private:
    mutable Setter Set;
    mutable Getter Get;
    T& m_ref;
    T  m_val;
    
    void InitHandlers(const Setter& set, const Getter& get) {
        Set = set; Get = get;
        if (Set == nullptr) {
            Set = [this](const T& val) {
                this->m_ref = val;
            };
        }
        if (Get == nullptr) {
            Get = [this]() -> const T {
                return this->m_ref;
            };
        }
    }
};

#endif /* PROPERTY_H */

