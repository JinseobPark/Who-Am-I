/**
\file        RandomGeneratorLogic.h
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM250
\date        06/14/2018
\brief       the header of Random Generator logic.
All content (c) 2018 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#ifndef RANDOMGENERATORLOGIC_H
#define RANDOMGENERATORLOGIC_H

#include "Data.h"
namespace FindersEngine
{
    bool CirRectCollisionCheck(Object* pA, Object* pB, Game_Random_Data& data);
    void OpenTheDoor(Game_Random_Data& data);
    LastDoor PickOneDoor(LastDoor first, LastDoor second, LastDoor third);
    void JudgeMakeDoor(Game_Random_Data& data);
	void JudgeMakeDoorBoss(Game_Random_Data& data);
    void SetIsLastDoor(Game_Random_Data& data);

}

#endif
