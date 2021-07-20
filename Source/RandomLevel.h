/**
\file        RandomLevel.cpp
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM250
\date        06/14/2018
\brief       random level header.
All content (c) 2018 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once

#ifndef RANDOMLEVEL_H
#define RANDOMLEVEL_H
#include "Collision.h"
#include "Timer.hpp"
#include <vector>

namespace FindersEngine
{
    void RandomLevelStateLoad(void);
    void RandomLevelStateInit(void);
    void RandomLevelStateUpdate(float dt);
    void RandomLevelStateExit(void);
    void RandomLevelStateUnload(void);
    
    class randomLevel
    {
    public:
        static void random_light1(float dt);
        static void poision_responce();
        static void gatepass_confirm();
        static void create_gathered_hint();
        static void rotate_gathered_hint(float dt);
        static void create_rotate_gathered_hint();
        static void create_before_hint();
        static void check_password();
        static void create_numpad();
        static void destroy_numpad();

        static Object* rotate_hint_hud1;
        static Transform* rotate_hint_hud1_trans;
    };
}

#endif // !RANDOMLEVEL_H
