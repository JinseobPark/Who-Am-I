/**
\file        RandomGenerator.h
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM250
\date        06/14/2018
\brief       Random Generator.
All content (c) 2018 DigiPen (USA) Corporation, all rights reserved.
*/

#pragma once
#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H
#include "Data.h"
#include "glm/glm.hpp"
#include <vector>

namespace FindersEngine
{
    class Object;
    class Transform;

    void RandomInitPlayer(Game_Random_Data& data);
    void RandomInitWall(Game_Random_Data& data);
	void RandomInitDoor(Game_Random_Data& data);
    void RandomInitDoorBoss(Game_Random_Data& data);

    void RandomInitZombie(Game_Random_Data& data);
	void RandomInitZombie2(Game_Random_Data& data);

    void RandomInitCamera(Game_Random_Data& data);
    void RandomCabinet(Game_Random_Data& data);

	void RandomInitTrap(Game_Random_Data& data);
	void RandomInitTrap2(Game_Random_Data& data);

	void RandomInitBoss(Game_Random_Data& data);

	void RandomGatePass(Game_Random_Data& data);
	void RandomGatePass2(Game_Random_Data& data);

	void RandomInitHint(Game_Random_Data& data);
	void RandomInitAmmo(Game_Random_Data& data);

    void RandomLoadLastHint(Game_Random_Data& data);
    void RandomSaveLastHint(Game_Random_Data& data);

	void RandomEventNumbersLevel1(Game_Random_Data& data);
	void RandomEventNumbersLevel2(Game_Random_Data& data);
    void BeforeWall(Game_Random_Data& data);
    void BeforeDoor(Game_Random_Data& data);
    void BeforeZombie(Game_Random_Data& data);
    void BeforePistol(Game_Random_Data& data);
    void BeforePlayer(Game_Random_Data& data);

	void SavePlayerStatus(Game_Random_Data& data);
	void LoadPlayerStatus(Game_Random_Data& data);

    void SetRoomStyle(Game_Random_Data& data);

	void CheatCode(Game_Random_Data& data);

	glm::vec3 SetObjectPos(float size, Game_Random_Data& data);
	glm::vec3 SetObjectPosWithoutPlayer(float size, Game_Random_Data& data);
    int RandomIntNumber(int min_num, int max_num);
    bool RandomChanceBool(int chance);
    float RandomFloatNumber(float min_num, float max_num);
}
#endif