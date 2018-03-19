//
// Created by fabio on 16/03/18.
//

#ifndef T1_RECT_H
#define T1_RECT_H


#include "Vec2.h"

class Rect {

public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float w, float h);

    Rect SumVec2(Vec2 v);
    Vec2 CenterRec();
    float DistRecs(Rect r);
    bool Contains(Vec2 v);


};


#endif //T1_RECT_H
