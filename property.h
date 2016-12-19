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

template <typename T> // T is a trivially copy-able/assignable/movable type
class Property {
public:
    typedef std::function<bool (const T&)> Checker;

    //---- Constructors ----
    Property(T& var, Checker check = nullptr) noexcept // CTOR for "wrapping" property
            : m_ref(var), IsAuto(false), IsAssigned(false)
        { Init(check); }
    Property(Checker check = nullptr) noexcept // CTOR for auto-property
            : m_ref(m_val), IsAuto(true), IsAssigned(false)
        { Init(check); }
    
    Property(const Property<T>& prop) noexcept // copy-CTOR; creates auto-property
            : m_ref(m_val), IsAuto(true), IsAssigned(false)
        { Init(nullptr); *this = prop; }
    Property(Property<T>&& prop) noexcept // move-CTOR; creates auto-property
            : m_ref(m_val), IsAuto(true), IsAssigned(false)
        { Init(nullptr); *this = std::move(prop); }
    
    //---- typecast overload ----
    operator const T() const noexcept { return m_ref; }
    
    //---- Assignment operator-overload ----
    Property<T>& operator=(T&& val) noexcept {
        if ((IsAssigned = Check(val)))
            m_ref = std::move(val);
        return *this;
    }
    Property<T>& operator=(const T& val) noexcept {
        if ((IsAssigned = Check(val)))
            m_ref = val;
        return *this;
    }
    Property<T>& operator=(const Property<T>& prop) noexcept {
        return (*this = prop.m_ref);
    }
    Property<T>& operator=(Property<T>&& prop) noexcept {
        return (*this = std::move(prop.m_val));
    }
    
    mutable bool IsAssigned = false;
    const bool& IsAuto; // Whether this object is an AutoProperty or not

private:
    T& m_ref;
    T  m_val;
    mutable Checker Check;
    
    void Init(const Checker& check) {
        if ((Check = check) == nullptr)
            Check = [](const T&) { return true; };
    }
};

#endif /* PROPERTY_H */

