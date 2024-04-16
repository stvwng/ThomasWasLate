#pragma once
#include "PlayableCharacter.h"

class Bob : public PlayableCharacter
{
    public:
        Bob::Bob();
        bool virtual handleInput();
};