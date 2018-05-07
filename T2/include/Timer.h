//
// Created by fabio on 06/05/18.
//

#ifndef T2_TIMER_H
#define T2_TIMER_H


class Timer {
    float time;

public:
    Timer();
    
    void Update(float dt);
    void Restart();
    float Get();

};


#endif //T2_TIMER_H
