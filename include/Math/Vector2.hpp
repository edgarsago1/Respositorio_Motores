#pragma once 

struct Vector2
{
    // Elemento x y y del vector
    float x{0.0f};
    float y{0.0f};

    // Constructor que devuelve un vector default (0, 0)
    constexpr Vector2() = default;
    // Constructor que devuelve un vector con valores x e y dados.
    constexpr Vector2(float x, float y) : x(x), y(y) {}
    
    // Operadores de suma entre vectores, que devuelve un nuevo vector.
    Vector2 operator+(const Vector2 &other) const;

    // Operadores de resta entre vectores, que devuelve un nuevo vector.
    Vector2 operator-(const Vector2 &other) const;
    
    // Operador de multiplicación entre un vector y un escalar, que devuelve un nuevo vector.
    Vector2 operator*(float scalar) const;

    // Operador de magnitud al cuadrado del vector, que devuelve un float.
    float length_squared() const;

    // Operador de magnitud del vector, que devuelve su valor absoluto en un tipo float.
    float length() const; 

    // Operador de normalización del vector, que devuelve un nuevo vector con magnitud 1.
    Vector2 normalized() const;

    // Versión propia de clamp, guardamos los límites en un vector llamado boundaries, si el vector a revisar 
    // es mayor al límite de X o Y de Boundaries, se devuelve el valor de boundaries que se sobrepasó.
    Vector2 clamp(Vector2 boundaries_down, Vector2 boundaries_up) const;
};