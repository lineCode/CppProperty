# CppProperty
One other independent implementation of C#-like properties in C++11

## Why This Project
> `TODO:`

## Objectives
1. Must be a header-only component
2. Simple to use
3. Usage must be as close to C#/.Net Property as possible
4. Must provide for **`readonly`** and **`auto`** properties
5. C++ exceptions must be avoided, to the extent possible

## The Main Files
- **`property.h`**: the main (and the only) header-only component containing the
source of the **`Property`** template-class definition
- **`main.cpp`**: illustrative; contains examples of typical usage of the
**`Property`** class

## Typical Usages
It's easier to start from how the **`Property`** class could be used.  The file **`main.cpp`** has the following functions:
- **`SimplestUseCase()`**
- **`PropertyInConstObject()`**
- **`ExplicitReadonlyProperty()`**
- **`AutoProperties()`**

The functions' names are self-explanatory and indicate the nature of use. Apart from the usages in the illustrative functions above, I haven't envisaged any other.

## The Gory Details - `property.h`

### The 'Wrapping' Property - the most-likely usage
The primary usage I envisaged was to use the **`Property`** class to wrap the fields / member-variables within a user-defined class. The function **`SimplestUseCase()`** illustrates this usage.  The constructor
> `Property(T& var, Checker check = nullptr) noexcept`

helps in creating such a "wrapping" Property around an existing variable / field.

### 'Auto' Property
Unlike the "wrapping" Property, the Property object doesn't wrap / reference an existing variable / field.  It internally has a field that would contain the value.  The constructor
> `Property(Checker check = nullptr) noexcept`

helps in creating this auto-property.

### The `Checker` function object
Both the above 2 CTORs provide for supplying a user-defined function to check / validate the value being assigned to the property.  If the value being assigned is *illegal*, then this function must return fa **`false`**.  If unspecified, the default Checker function simply returns a **`true`** always, meaning that any value could be assigned to the Property object.

