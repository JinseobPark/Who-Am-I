/**
\file        EditLevel2.cpp
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM250
\date        06/14/2018
\brief       editor.
All content (c) 2018 DigiPen (USA) Corporation, all rights reserved.
*/
#include "EditLevel2.h"
#include "CameraSystem.h"
#include "Data.h"
#include "EditHelper.h"
#include "Engine.h"
#include "GameList.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Headers_Controllers.h"
#include "JsonWriter.h"
#include "Minimap.h"
#include "ObjectFactory.h"
#include "ObjectGenerator.h"
#include "Physics.h"
#include "PhysicsLogic.h"
#include "SoundManager.h"
#include "jsonReader.h"
#include <glm/glm.hpp>
#include <memory>

#ifdef _WIN32
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif

using namespace std;
using namespace glm;
namespace FindersEngine
{
    namespace
    {
        GameData* GameObject = new GameData;
        MinimapObject Minimap;
    }
    void EditLevel2StateLoad(void)
    {
        ENGINE->isEdit = true;
        ENGINE->isPause = true;

        GameObject->CurrentLevel = 2;
    }

    void EditLevel2StateInit(void)
    {
        SOUNDMANAGER->stop("MENU_SOUND.mp3");
        SOUNDMANAGER->play("BACKGROUND_SOUND.mp3");
        SOUNDMANAGER->play("THUNDER_SOUND.mp3");
        GRAPHICS->BackgroundColor(1, 1, 1, 1);
        JSONREADER->ReadJsonLevel(*GameObject);

        InitPlayer(*GameObject);
        InitFinalDoor(*GameObject);
        InitWall(*GameObject);
        InitDoor(*GameObject);
        InitAmmo(*GameObject);
        InitZombie(*GameObject);
        InitPistol(*GameObject);
        InitArmor(*GameObject);
        InitCamera(*GameObject);
        InitWASDWall(*GameObject);
        Minimap.MiniMap_InitBase();
        Minimap.MiniMap_InitObject(*GameObject);

        GRAPHICS->TurnOnLights();
    }

    void EditLevel2StateUpdate(float dt)
    {
        if (GameObject->initiate)
        {
            ENGINE->isEdit = true;
            ENGINE->isPause = true;
            GameObject->initiate = false;
        }
        if (ENGINE->isEdit)
        {
            GRAPHICS->BackgroundColor(1, 1, 1, 1);
            float Camera_Z = GRAPHICS->camera_system->m_position.z;

            //Mouse
            int mouse_x;
            int mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);

            glm::vec2 world_mouse(mouse_x, mouse_y);

            EditZombie(*GameObject);
            EditWall(*GameObject);
            EditDoor(*GameObject);
            EditAmmo(*GameObject);
            EditPistol(*GameObject);
            EditCamera();
            EditUDLRWall(*GameObject);
            ModeHelper();
            //add
            std::string Wall_num = std::to_string((*GameObject).Wall_Count);
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_Z))
            {
                (*GameObject).Zombie.push_back(OBJECT_GEN->CreateZombie(glm::vec3(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + GRAPHICS->camera_system->m_position.x, Camera_Z * (-(float)mouse_y + 360.f) / 840.f + GRAPHICS->camera_system->m_position.y, 0), ZombieId + (*GameObject).Zombie_Count, Z_NORMAL));
                (*GameObject).Zombie_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_D))
            {
                (*GameObject).Door.push_back(OBJECT_GEN->CreateObject("PIN_HDOOR.png", glm::vec3(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + GRAPHICS->camera_system->m_position.x, RoundInt(Camera_Z * (-(float)mouse_y + 360.f) / 840.f + GRAPHICS->camera_system->m_position.y), 0), glm::vec3(400, 150, 0), ObjectType(8), ST_RECTANGLE, DoorId + (*GameObject).Door_Count));
                (*GameObject).Door_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_F))
            {
                (*GameObject).Door.push_back(OBJECT_GEN->CreateObject("PIN_VDOOR.png", glm::vec3(RoundInt(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + GRAPHICS->camera_system->m_position.x), Camera_Z * (-(float)mouse_y + 360.f) / 840.f + GRAPHICS->camera_system->m_position.y, 0), glm::vec3(150, 400, 0), ObjectType(9), ST_RECTANGLE, DoorId + (*GameObject).Door_Count));
                (*GameObject).Door_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_C))
            {
                (*GameObject).Wall.push_back(OBJECT_GEN->CreateWall(glm::vec3(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + GRAPHICS->camera_system->m_position.x, RoundInt(Camera_Z * (-(float)mouse_y + 360.f) / 840.f + GRAPHICS->camera_system->m_position.y), 0), glm::vec3(2500, 200, 0), WallId + (*GameObject).Wall_Count, "Wall" + Wall_num, "PIN_UWALL.png"));
                (*GameObject).Wall_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_V))
            {
                (*GameObject).Wall.push_back(OBJECT_GEN->CreateWall(glm::vec3(RoundInt(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + GRAPHICS->camera_system->m_position.x), Camera_Z * (-(float)mouse_y + 360.f) / 840.f + GRAPHICS->camera_system->m_position.y, 0), glm::vec3(200, 2500, 0), WallId + (*GameObject).Wall_Count, "Wall" + Wall_num, "PIN_RWALL.png"));
                (*GameObject).Wall_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_B))
            {
                (*GameObject).Wall.push_back(OBJECT_GEN->CreateWall(glm::vec3(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + GRAPHICS->camera_system->m_position.x, Camera_Z * (-(float)mouse_y + 360.f) / 840.f + GRAPHICS->camera_system->m_position.y, 0), glm::vec3(200, 200, 0), WallId + (*GameObject).Wall_Count, "Wall" + Wall_num, "PIN_RWALL.png"));
                (*GameObject).Wall_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_A))
            {
                (*GameObject).Ammo.push_back(OBJECT_GEN->CreateObject("PIN_AMMO.png", glm::vec3(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + GRAPHICS->camera_system->m_position.x, Camera_Z * (-(float)mouse_y + 360.f) / 840.f + GRAPHICS->camera_system->m_position.y, 0), glm::vec3(90, 90, 0), OT_AMMO, ST_CIRCLE, AmmoId + (*GameObject).Ammo_Count));
                (*GameObject).Ammo_Count++;
                //Minimap.AddAmmo(*GameObject);
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_X))
            {
                (*GameObject).Pistol->SetPosition(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + GRAPHICS->camera_system->m_position.x, Camera_Z * (-(float)mouse_y + 360.f) / 840.f + GRAPHICS->camera_system->m_position.y);
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_T))
            {
                (*GameObject).Player->SetPosition(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + GRAPHICS->camera_system->m_position.x, Camera_Z * (-(float)mouse_y + 360.f) / 840.f + GRAPHICS->camera_system->m_position.y);
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_U))
            {
                (*GameObject).Walls.UWall.push_back(OBJECT_GEN->CreateWall(glm::vec3(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + GRAPHICS->camera_system->m_position.x, Camera_Z * (-(float)mouse_y + 360.f) / 840.f + GRAPHICS->camera_system->m_position.y, 0), glm::vec3(2500, 200, 0), WallId + (*GameObject).Wall_Count, "Wall" + Wall_num, "PIN_UWALL.png"));
                (*GameObject).Walls.UWall_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_J))
            {
                (*GameObject).Walls.DWall.push_back(OBJECT_GEN->CreateWall(glm::vec3(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + GRAPHICS->camera_system->m_position.x, Camera_Z * (-(float)mouse_y + 360.f) / 840.f + GRAPHICS->camera_system->m_position.y, 0), glm::vec3(2500, 200, 0), WallId + (*GameObject).Wall_Count, "Wall" + Wall_num, "PIN_DWALL.png"));
                (*GameObject).Walls.DWall_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_H))
            {
                (*GameObject).Walls.LWall.push_back(OBJECT_GEN->CreateWall(glm::vec3(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + GRAPHICS->camera_system->m_position.x, Camera_Z * (-(float)mouse_y + 360.f) / 840.f + GRAPHICS->camera_system->m_position.y, 0), glm::vec3(200, 2500, 0), WallId + (*GameObject).Wall_Count, "Wall" + Wall_num, "PIN_LWALL.png"));
                (*GameObject).Walls.LWall_Count++;
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_K))
            {
                (*GameObject).Walls.RWall.push_back(OBJECT_GEN->CreateWall(glm::vec3(Camera_Z * (((float)mouse_x - 640.f) / 840.f) + GRAPHICS->camera_system->m_position.x, Camera_Z * (-(float)mouse_y + 360.f) / 840.f + GRAPHICS->camera_system->m_position.y, 0), glm::vec3(200, 2500, 0), WallId + (*GameObject).Wall_Count, "Wall" + Wall_num, "PIN_RWALL.png"));
                (*GameObject).Walls.RWall_Count++;
            }
            if (Input::IsPressed(SDL_SCANCODE_UP))
            {
                GRAPHICS->camera_system->m_position.y += 0.1f;
            }
            if (Input::IsPressed(SDL_SCANCODE_DOWN))
            {
                GRAPHICS->camera_system->m_position.y -= 0.1f;
            }
            if (Input::IsPressed(SDL_SCANCODE_RIGHT))
            {
                GRAPHICS->camera_system->m_position.x += 0.1f;
            }
            if (Input::IsPressed(SDL_SCANCODE_LEFT))
            {
                GRAPHICS->camera_system->m_position.x -= 0.1f;
            }

            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_F2))
            {
                JSONWRITER->jsonWriterEdit((*GameObject));
                GameObject->CurrentLevel = 2;
                GAME_STATE->Restart();
            }
            if (Input::GetInstance().IsTriggered(SDL_SCANCODE_F3))
            {
                JSONWRITER->jsonWriterEdit((*GameObject));
                GameObject->CurrentLevel = 3;
                GAME_STATE->Restart();
            }
        } //can edit
        else
        {
            GRAPHICS->BackgroundColor(0, 0, 0, 1);
        }

        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_ESCAPE))
        {
            if (ENGINE->isEdit == false)
            {
                ENGINE->isEdit = true;
                ENGINE->isPause = true;
                GAME_STATE->Restart();
            }
            else
            {
                ENGINE->isEdit = false;
                ENGINE->isPause = false;
                GAME_STATE->SetNextState(SL_MENU);
            }
        }
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_F5))
        {
            JSONWRITER->jsonWriterEdit((*GameObject));
            ENGINE->isEdit = false;
            ENGINE->isPause = false;
            GAME_STATE->Restart();
        }
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_P))
        {
            if (ENGINE->isEdit == false)
            {
                ENGINE->isEdit = true;
                ENGINE->isPause = true;
                GAME_STATE->Restart();
            }
            else
            {
                JSONWRITER->jsonWriterEdit(*GameObject);
                ENGINE->isEdit = false;
                ENGINE->isPause = false;
                GAME_STATE->Restart();
            }
        }

    }

    void EditLevel2StateExit(void)
    {
        PHYSICS->walls_and_zombies.clear();
        PHYSICS->walls.clear();
        OBJECT_FACTORY->DestroyAllObjects();
        SOUNDMANAGER->stop("BACKGROUND_SOUND.mp3");
        SOUNDMANAGER->stop("THUNDER_SOUND.mp3");
        JSONREADER->jsonReaderUnload();
    }

    void EditLevel2StateUnload(void)
    {
    }
}
