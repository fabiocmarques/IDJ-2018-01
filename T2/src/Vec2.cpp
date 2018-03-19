//
// Created by fabio on 16/03/18.
//

#include "Vec2.h"

Vec2::Vec2() {
    x = 0;
    y = 0;
}

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2 Vec2::Sum(Vec2 v, bool sum) {
    Vec2 ret;

    if(sum){
        ret.x += v.x;
        ret.y += v.y;
    } else{
        ret.x -= v.x;
        ret.y -= v.y;
    }

    return ret;
}

Vec2 Vec2::MultEsc(int esc) {
    Vec2 ret;

    ret.x = this->x * esc;
    ret.y = this->y * esc;

    return ret;
}

float Vec2::Mag() {
    return (float)sqrtf(((this->x * this->x) + (this->y * this->y)));
}

Vec2 Vec2::Norm() {
    float mag = this->Mag();
    return Vec2(this->x / mag, this->y / mag);
}

float Vec2::Dist(Vec2 v) {
    Vec2 ret = this->Sum(v, false);
    return (float)ret.Mag();
}

float Vec2::IncX() {
    return (float)atan2(this->x, this->y);
}

float Vec2::Incl(Vec2 v) {
    Vec2 ret = this->Sum(v, false);
    return ret.IncX();
}

Vec2 Vec2::GetRotated(float ang) {
    return Vec2(x*cos(ang) - y*sin(ang), y*cos(ang) + x*sin(ang));
}

Vec2 Vec2::operator+(const Vec2& v) {
    return Vec2(x + v.x, y + v.y );
}


