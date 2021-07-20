/**
\file        Minimap.h
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM250
\date        06/14/2018
\brief       the header of minimap.
All content (c) 2018 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#ifndef MINIMAP_H
#define MINIMAP_H
#include "Data.h"
#include "Object.h"
#include <vector>

namespace FindersEngine
{

    class MinimapObject
    {
    public:
        MinimapObject();
        ~MinimapObject();
        void MiniMap_InitBase(void);
        void MiniMap_InitObject(GameData& data);
        void MiniMap_InitObject_Random(Game_Random_Data& data);

        void MiniMap_Update(GameData& data);
        void MiniMap_Update_Random(Game_Random_Data& data);

    private:
        Object* MiniBase;
        Object* MiniPlayer;
        Hud* MiniPlayer_hud;

        std::vector<Object*>* MiniWall;
        std::vector<Object*> UMiniWall;
        std::vector<Object*> DMiniWall;
        std::vector<Object*> LMiniWall;
        std::vector<Object*> RMiniWall;
    };
}

#endif
