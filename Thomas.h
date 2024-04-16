#pragma once
#include "PlayableCharacter.h"

class Thomas : public PlayableCharacter
{
    public:
        Thomas::Thomas(); // constructor
        bool virtual handleInput(); // override input handler
};