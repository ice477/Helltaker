//
// Created by Chucolate on 2025/3/14.
//

#ifndef CHAR_PLAYER_HPP
#define CHAR_PLAYER_HPP

//#include "UI_Subject.hpp"
#include "Animation.hpp"
#include "Position.hpp"
#include "KeyInput.hpp"
//#include ""

class Char_PL {
    private:
        size=3;
        Pos_X=0;
        Pos_Y=0;
    public:
        void Move(int a,int b){
            Pos_X+=a;
            Pos_Y+=b;
        }
}
#endif //CHAR_PLAYER_HPP
