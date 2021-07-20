/**
\file        Minimap.cpp
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM250
\date        06/14/2018
\brief       Minimap of game..
All content (c) 2018 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Minimap.h"
#include "CameraSystem.h"
#include "Graphics.h"
#include "ObjectGenerator.h"

#define WIDTH 1280
#define HEIGHT 720
namespace FindersEngine
{
    MinimapObject::MinimapObject()
    {
        MiniWall = new std::vector<Object*>;
    }
    MinimapObject::~MinimapObject()
    {
        MiniWall->clear();
        UMiniWall.clear();
        DMiniWall.clear();
        LMiniWall.clear();
        RMiniWall.clear();
    }

    void MinimapObject::MiniMap_InitBase(void)
    {
        MiniBase = OBJECT_GEN->CreateHud(glm::vec3(WIDTH - 90, 90, 0) + glm::vec3(GRAPHICS->camera_system->m_position.x, GRAPHICS->camera_system->m_position.y, 0.f), glm::vec3(180, 180, 1.f), 9100, "PIN_BACKGROUND_OF_HINT.png");
    }
    void MinimapObject::MiniMap_InitObject(GameData& data)
    {
        MiniWall->clear();

        MiniPlayer = OBJECT_GEN->CreateHud(MiniBase->GetPosition() + glm::vec3(data.Player->GetPosition().x * 15, -data.Player->GetPosition().y * 15, 0), glm::vec3(25, 25, 1.f), 9101, "PIN_PLAYER.png");

        for (unsigned int i = 0; i < data.Wall_Count; ++i)
        {
            (*MiniWall).push_back(OBJECT_GEN->CreateHud(MiniBase->GetPosition() + glm::vec3(data.Wall[i]->GetPosition().x * 15, -data.Wall[i]->GetPosition().y * 15, 0), glm::vec3(data.Wall[i]->GetScale().x / 160.f * 3.f, data.Wall[i]->GetScale().y / 160.f * 3.f, 1.f), 9400 + i, "PIN_MINIWALL.png"));
        }
    }
    void MinimapObject::MiniMap_InitObject_Random(Game_Random_Data& data)
    {
        UMiniWall.clear();
        DMiniWall.clear();
        LMiniWall.clear();
        RMiniWall.clear();

        MiniPlayer = OBJECT_GEN->CreateHud(MiniBase->GetPosition() + glm::vec3(data.Player->GetPosition().x * 15, -data.Player->GetPosition().y * 15, 0), glm::vec3(25, 25, 1.f), 9101, "PIN_PLAYER.png");
        MiniPlayer_hud = reinterpret_cast<Hud*>(MiniPlayer->GetComponent(CT_HUD));
        MiniPlayer_hud->setBlendAlpha(0.3f, true, true);

        for (unsigned int i = 0; i < data.Walls.UWall_Count; ++i)
        {
            (UMiniWall).push_back(OBJECT_GEN->CreateHud(MiniBase->GetPosition() + glm::vec3(data.Walls.UWall[i]->GetPosition().x * 15, -data.Walls.UWall[i]->GetPosition().y * 15, 0), glm::vec3(data.Walls.UWall[i]->GetScale().x / 145.f * 3.f, data.Walls.UWall[i]->GetScale().y / 150.f * 3.f, 1.f), 9400 + i, "PIN_MINIWALL.png"));
        }
        for (unsigned int i = 0; i < data.Walls.DWall_Count; ++i)
        {
            (DMiniWall).push_back(OBJECT_GEN->CreateHud(MiniBase->GetPosition() + glm::vec3(data.Walls.DWall[i]->GetPosition().x * 15, -data.Walls.DWall[i]->GetPosition().y * 15, 0), glm::vec3(data.Walls.DWall[i]->GetScale().x / 145.f * 3.f, data.Walls.DWall[i]->GetScale().y / 150.f * 3.f, 1.f), 9400 + i, "PIN_MINIWALL.png"));
        }
        for (unsigned int i = 0; i < data.Walls.LWall_Count; ++i)
        {
            (LMiniWall).push_back(OBJECT_GEN->CreateHud(MiniBase->GetPosition() + glm::vec3(data.Walls.LWall[i]->GetPosition().x * 15, -data.Walls.LWall[i]->GetPosition().y * 15, 0), glm::vec3(data.Walls.LWall[i]->GetScale().x / 150.f * 3.f, data.Walls.LWall[i]->GetScale().y / 150.f * 3.f, 1.f), 9400 + i, "PIN_MINIWALL.png"));
        }
        for (unsigned int i = 0; i < data.Walls.RWall_Count; ++i)
        {
            (RMiniWall).push_back(OBJECT_GEN->CreateHud(MiniBase->GetPosition() + glm::vec3(data.Walls.RWall[i]->GetPosition().x * 15, -data.Walls.RWall[i]->GetPosition().y * 15, 0), glm::vec3(data.Walls.RWall[i]->GetScale().x / 150.f * 3.f, data.Walls.RWall[i]->GetScale().y / 150.f * 3.f, 1.f), 9400 + i, "PIN_MINIWALL.png"));
        }
    }


    void MinimapObject::MiniMap_Update(GameData& data)
    {
        MiniBase->SetPosition(WIDTH - 90 + GRAPHICS->camera_system->m_position.x, 90 + GRAPHICS->camera_system->m_position.y);
        MiniPlayer->SetPosition(MiniBase->GetPosition().x + data.Player->GetPosition().x * 15, MiniBase->GetPosition().y - data.Player->GetPosition().y * 15);

        for (unsigned int i = 0; i < data.Wall_Count; ++i)
        {
            (*MiniWall)[i]->SetPosition(MiniBase->GetPosition().x + data.Wall[i]->GetPosition().x * 15, MiniBase->GetPosition().y - data.Wall[i]->GetPosition().y * 15);
        }
    }
    void MinimapObject::MiniMap_Update_Random(Game_Random_Data& data)
    {
        MiniBase->SetPosition(WIDTH - 90 + GRAPHICS->camera_system->m_position.x, 90 + GRAPHICS->camera_system->m_position.y);
        MiniPlayer->SetPosition(MiniBase->GetPosition().x + data.Player->GetPosition().x * 15, MiniBase->GetPosition().y - data.Player->GetPosition().y * 15);

        for (unsigned int i = 0; i < data.Walls.UWall_Count; ++i)
        {
            (UMiniWall)[i]->SetPosition(MiniBase->GetPosition().x + data.Walls.UWall[i]->GetPosition().x * 15, MiniBase->GetPosition().y - data.Walls.UWall[i]->GetPosition().y * 15);
        }
        for (unsigned int i = 0; i < data.Walls.DWall_Count; ++i)
        {
            (DMiniWall)[i]->SetPosition(MiniBase->GetPosition().x + data.Walls.DWall[i]->GetPosition().x * 15, MiniBase->GetPosition().y - data.Walls.DWall[i]->GetPosition().y * 15);
        }
        for (unsigned int i = 0; i < data.Walls.LWall_Count; ++i)
        {
            (LMiniWall)[i]->SetPosition(MiniBase->GetPosition().x + data.Walls.LWall[i]->GetPosition().x * 15, MiniBase->GetPosition().y - data.Walls.LWall[i]->GetPosition().y * 15);
        }
        for (unsigned int i = 0; i < data.Walls.RWall_Count; ++i)
        {
            (RMiniWall)[i]->SetPosition(MiniBase->GetPosition().x + data.Walls.RWall[i]->GetPosition().x * 15, MiniBase->GetPosition().y - data.Walls.RWall[i]->GetPosition().y * 15);
        }
    }

}
