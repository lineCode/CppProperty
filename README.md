# CppProperty
One other independent implementation of C#-like properties in C++11

## Why This Project

To hone my C++ skills, I wanted to take swing at implementing C#/.Net-like Property in C++11.  While I independently conceived the implementation, I later discovered that there are quite a few virtually identical implementations out in the open.  While I am not disheartened by that, I just want to emphasize that this project is honestly my own independent creation.

## Self-imposed Technical Objectives
1. Must be a header-only component
2. Simple to use
3. Usage must be as close to C#/.Net Property as possible
4. Must provide for **`readonly`** and **`auto`** properties
5. C++ exceptions must be avoided, to the extent possible

## The Main Files
- **`property.h`**: the main (and the only) header-only component containing the source of the **`Property`** template-class definition
- **`main.cpp`**: illustrative; contains examples of typical usages of the **`Property`** class

## Typical Usages
It's easier to start from how the `Property<T>` class could be used.  The file **`main.cpp`** has the following functions:
- `SimplestUseCase()`
- `PropertyInConstObject()`
- `ExplicitReadonlyProperty()`
- `AutoProperties()`
- `PropertiesWithCustomChecker()`

The functions' names are self-explanatory and indicate the nature of use. Apart from the usages in the illustrative functions above, I haven't envisaged any other.

## The Gory Details - `property.h`

### The 'Wrapping' Property - the most-likely usage
The primary usage I envisaged was to use the `Property<T>` class to wrap / reference the fields / member-variables within a user-defined class. The function `SimplestUseCase()` illustrates this usage.  The constructor
> `Property(T& var, Checker check = nullptr) noexcept`

helps in creating such a "wrapping / referencing" Property around an existing variable / field.

### 'Auto' Property
Unlike the "wrapping" Property, the Property object doesn't wrap / reference another variable / field.  It internally has a field that would contain the value.  The constructor
> `Property(Checker check = nullptr) noexcept`

helps in creating this auto-property. The function `AutoProperties()` is an example for defining and using auto-properties.

### The `Checker` function object
Both the above 2 CTORs provide for supplying a custom function to check / validate the value being assigned to the property.  If the value being assigned is *illegal / invalid*, then this function must return **`false`**.  If unspecified, the default `Checker` function simply returns a **`true`** always, meaning that any value could be assigned to the `Property<T>` object.

The function `PropertiesWithCustomChecker()` illustrates the use of custom / user-defined `Checker` function while defining a `Property<T>`object.

### The `IsAssigned` field

Since the `Property<T>` class doesn't throw any exception of its own, this field is useful to check if the immediately preceding assignment was successful or not.  The corrollary is, the value in this field is relevant / useful only when it is used (or read) immediately after an assignmentto the `Property<T>` object.

The function `PropertiesWithCustomChecker()` is a good example illustrating its use

### A Note on copying / moving of `Property<T>` objects

- In the case of move-assignemnt / move-construction, The `Property<T>` object on the RHS must be an auto-property otherwise the behaviour would be unpredictable.  It is recommended that the calling function checks the `IsAssigned` value immeidately after such operation.
- Whether it is an auto-property or not, only the value contained / wrapped by that `Property<T>` object on the RHS is moved / assigned.  The RHS might have a different (custom) Checker function and might even refererence another variable / field yet only the value contained in `Property<T>::m_val` is moved / assigned.
- In case of a copy/move-constructed `Property<T>` object (LHS), the default Checker function is internally initialized, irrespective of the RHS' Checker function.

<p align="center">-x-x-x-x-</p>

