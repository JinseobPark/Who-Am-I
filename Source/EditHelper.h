/**
 \file        EditHelper.h
 \author      jinseob.park
 \par         email: 0814owl@gmail.com
 \par         course: GAM200
 \date        12/15/2017
 \brief       MapEdit stage.
 
 */
#pragma once
#ifndef EDITHELPER_H
#define EDITHELPER_H
#include "Data.h"
#include "glm/glm.hpp"
#include <vector>


namespace FindersEngine
{
    class Object;
    class Transform;

    struct EditInfo
    {
        EditMode Mode = NONE;
        bool IsSelect = false;
        bool WorldSelect = false;
        glm::vec2 Location = {0, 0};
        int TargetObject = 0;
        int TargetType = 0;
    };

    static EditInfo editdata;
    void InitPlayer(GameData& data);
    void InitFinalDoor(GameData& data);
    void InitWall(GameData& data);
    void InitWASDWall(GameData& data);
    void InitDoor(GameData& data);
    void InitAmmo(GameData& data);
    void InitZombie(GameData& data);
    void InitPistol(GameData& data);
    void InitArmor(GameData& data);
    void InitCamera(GameData& data);


    void EditZombie(GameData& data);
    void EditDoor(GameData& data);
    void EditWall(GameData& data);
    void EditAmmo(GameData& data);
    void EditPistol(GameData& data);
    void EditUDLRWall(GameData& data);
    void EditCamera();

    void NotPause(void);
    void ModeHelper(void);
    int RoundInt(float value);
}
#endif
