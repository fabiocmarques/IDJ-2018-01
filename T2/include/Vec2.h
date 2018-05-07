//
// Created by fabio on 16/03/18.
//

#ifndef T1_VEC2_H
#define T1_VEC2_H

#include <cmath>

class Vec2 {

public:
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);

    // Soma de dois vetores. Se 'sum' == true, acontece uma soma, se 'sum' == false, uma subtracao.
    Vec2 Sum(Vec2 v, bool sum);
    // Multiplicacao por escalar.
    Vec2 MultEsc(int esc);
    // Magnitude do vetor.
    float Mag();
    // Vetor normalizado.
    Vec2 Norm();
    //Distancia entre 2 vetores.
    float Dist(Vec2 v);
    // Inclinacao em relacao ao eixo X.
    float IncX();
    // Inclinacao entre 2 vetores.
    float Incl(Vec2 v);
    // Rotaciona o vetor pelo angulo 'ang'.
    Vec2 GetRotated(float ang);

    Vec2 operator+(const Vec2& v) const;

    Vec2 operator-(const Vec2& rhs) const;

    Vec2 operator*(float rhs) const;
};


#endif //T1_VEC2_H
