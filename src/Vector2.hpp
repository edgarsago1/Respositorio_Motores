#pragma once 
#include <cmath>

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
    Vector2 operator+(const Vector2 &other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    // Operadores de resta entre vectores, que devuelve un nuevo vector.
    Vector2 operator-(const Vector2 &other) const
    {
        return Vector2(x - other.x, y - other.y);
    }
    
    // Operador de multiplicación entre un vector y un escalar, que devuelve un nuevo vector.
    Vector2 operator*(float scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }

    // Operador de magnitud al cuadrado del vector, que devuelve un float.
    float length_squared() const
    {
        return x * x + y * y;
    }

    // Operador de magnitud del vector, que devuelve su valor absoluto en un tipo float.
    float length() const
    {
        return std::sqrt(length_squared());
    }

    // Operador de normalización del vector, que devuelve un nuevo vector con magnitud 1.
    Vector2 normalized() const
    {
        float len = length();
        if (len > 0.0001f)
        {
            return Vector2(x / len, y / len);
        }
        return {0.0f, 0.0f};
    }
};