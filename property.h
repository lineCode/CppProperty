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
#include <stdexcept>

template <typename T> // T is a trivially copy-able/assignable/movable type
class Property {
public:
    typedef std::function<void (const T&)> Setter;
    typedef std::function<const T ()> Getter;

    //---- Constructors ----
    Property(const Property<T>& prop) noexcept(false) // copy-CTOR
        : m_ref(m_val), m_val(prop.m_val)
    {
        if (&prop.m_ref != &prop.m_val) {
            throw std::logic_error("Only auto-properties can be copy-constructed");
        }
        Set = prop.Set; Get = prop.Get;
    }
    Property(Property<T>&& prop) noexcept(false) // move-CTOR
        : m_ref(m_val), m_val(std::move(prop.m_val))
    {
        if (&prop.m_ref != &prop.m_val) {
            throw std::logic_error("Only auto-properties can be move-constructed");
        }
        Set = std::move(prop.Set); Get = std::move(prop.Get);
    }
    Property(T& var, Setter onSet = nullptr, Getter onGet = nullptr) noexcept
        : m_ref(var)
    {
        InitHandlers(onSet, onGet);
    };
    Property(const T& var, Setter onSet = nullptr, Getter onGet = nullptr) noexcept
        : m_ref(var)
    {
        InitHandlers(onSet, onGet);
    };
    Property(Setter onSet = nullptr) noexcept // CTOR for auto-property
        : m_ref(m_val)
    {
        Getter onGet = nullptr;
        InitHandlers(onSet, onGet);
    }
    
    //---- Assignment operator-overload ----
    Property<T>& operator=(const Property<T>& prop) noexcept(false) {
        if (&prop.m_ref != &prop.m_val || &m_ref != &m_val) {
            throw std::logic_error("Only auto-properties are assignable");
        }
        m_val = prop.m_val;
        Set = prop.Set; Get = prop.Get;
        return *this;
    }
    Property<T>& operator=(Property<T>&& prop) noexcept(false) {
        if (&prop.m_ref != &prop.m_val || &m_ref != &m_val) {
            throw std::logic_error("Only auto-properties are movable");
        }
        m_val = std::move(prop.m_val);
        Set = std::move(prop.Set); Get = std::move(prop.Get);
        return *this;
    }
    Property<T>& operator=(const T& val) noexcept(false) { Set(val); return *this; }
    
    //---- typecast overload ----
    operator const T() const { return Get(); }
    
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

