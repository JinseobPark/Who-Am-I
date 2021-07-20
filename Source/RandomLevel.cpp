/**
\file        RandomLevel.cpp
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM250
\date        06/14/2018
\brief       random level.
All content (c) 2018 DigiPen (USA) Corporation, all rights reserved.
*/
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
#include "PlayerController.h" // player_health
#include "PlayerLogic.h"
#include "RandomGenerator.h"
#include "RandomGeneratorLogic.h"
#include "RandomLevel.h"
#include "SoundManager.h"
#include "SpotLight.h"
#include "SpriteText.hpp"
#include "jsonReader.h"
#include <ctime>
#include <glm/glm.hpp>
#include <memory>

#include <glm/gtc/epsilon.hpp>
//#include <glm/gtc/epsilon.inl>


#ifdef _WIN32
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif
#define WIDTH 1280
#define HEIGHT_TEMP 640 //720


using namespace std;
using namespace glm;

namespace FindersEngine
{
    std::vector<unsigned> Game_Random_Data::player_hint_order_1;
    std::vector<unsigned> Game_Random_Data::player_hint_1;

    static std::vector<Object*> number_objects_1;
    Object* randomLevel::rotate_hint_hud1 = nullptr;
    Transform* randomLevel::rotate_hint_hud1_trans = nullptr;

    namespace
    {
        Game_Random_Data* GameObject;
        PublicData* p_data;
        MinimapObject Minimap;

        float elapsed_time = 0.f;

        bool isgetAmmo = false;
        bool isgetPistol = false;
        bool isGrande = false;

        bool isDieAnimationEnd = false;

        Object* hintbox_1 = nullptr;
        Object* hintbox_2 = nullptr;
        Object* hintbox_3 = nullptr;
        Object* hintbox_4 = nullptr;
        Object* GatePass = nullptr;
        Object* rand1_mouse_object = nullptr;
        Transform* rand1_mouse_trans = nullptr;
        Object* game_life1 = nullptr;
        Object* game_life2 = nullptr;
        Object* game_life3 = nullptr;
        Transform* game_life1_trans = nullptr;
        Transform* game_life2_trans = nullptr;
        Transform* game_life3_trans = nullptr;
        Timer temp;
        float radian = 0.f;
        float rot = 0;
        char rand_secret_num[3] = {0};
    }

    void RandomLevelStateLoad(void)
    {
        GameObject = new Game_Random_Data();
        p_data = new PublicData();

        isgetPistol = false;
        isgetAmmo = false;
        isGrande = false;

        RandomEventNumbersLevel1(*GameObject);

        GRAPHICS->BackgroundColor(0, 0, 0, 0);
        GameObject->Room_Number = 1;
        GameObject->Is_Get_Pistol = false;
        GameObject->curr_ammo_ = 0;
        GameObject->curr_grenade = 0;
        GameObject->player_hint_1.clear();
        GameObject->currLevel = 1;
        PlayerController::player_health = 300;

        srand((unsigned int)time(nullptr));
        JSONREADER->read_rand_item_data();

        for (auto i = 0; i < 4; ++i)
        {
            rand_secret_num[i] = RandomIntNumber(49, 58);
        }
        GAMELOGIC->SetSecretNumber(rand_secret_num[0], rand_secret_num[1], rand_secret_num[2], rand_secret_num[3]);
    }

    void RandomLevelStateInit(void)
    {
        GameObject->player_pos_check.Init();
        temp.Init();
        SOUNDMANAGER->AllStop();
        SOUNDMANAGER->init();
        SOUNDMANAGER->play("DOOR_SOUND.wav");
        SOUNDMANAGER->play("BACKGROUND_SOUND.mp3");
        SOUNDMANAGER->play("THUNDER_SOUND.mp3");
        const auto height = 720.f;
        PlayerController::die_animation_end = false;
        GAMELOGIC->Make_PauseMenu();

        rand1_mouse_object = OBJECT_GEN->CreateMouseCursor(vec3(0, 0, 0), "PIN_CURSOR.png");
        rand1_mouse_trans = dynamic_cast<Transform*>(rand1_mouse_object->GetComponent(CT_TRANSFORM));
        SetRoomStyle(*GameObject);
        PLAYERLOGIC->Init();
        OBJECT_GEN->CreateBase(vec3(-4, -4, 0), vec3(3200, 3200, 0), 5001);
        OBJECT_GEN->CreateBase(vec3(-4, 0, 0), vec3(3200, 3200, 0), 5002);
        OBJECT_GEN->CreateBase(vec3(-4, 4, 0), vec3(3200, 3200, 0), 5003);
        OBJECT_GEN->CreateBase(vec3(0, 4, 0), vec3(3200, 3200, 0), 5004);
        OBJECT_GEN->CreateBase(vec3(0, 0, 0), vec3(3200, 3200, 0), 5005);
        OBJECT_GEN->CreateBase(vec3(0, -4, 0), vec3(3200, 3200, 0), 5006);
        OBJECT_GEN->CreateBase(vec3(4, -4, 0), vec3(3200, 3200, 0), 5007);
        OBJECT_GEN->CreateBase(vec3(4, 0, 0), vec3(3200, 3200, 0), 5008);
        OBJECT_GEN->CreateBase(vec3(4, 4, 0), vec3(3200, 3200, 0), 5009);

        game_life1 = OBJECT_GEN->CreateHud(vec3(WIDTH / 6 - 30, HEIGHT_TEMP / 8, 0), vec3(25.f, 25.f, 1.f), 3070,
                                           "PIN_LIFE.png");
        game_life2 = OBJECT_GEN->CreateHud(vec3(WIDTH / 6, HEIGHT_TEMP / 8, 0), vec3(25.f, 25.f, 1.f), 3071,
                                           "PIN_LIFE.png");
        game_life3 = OBJECT_GEN->CreateHud(vec3(WIDTH / 6 + 30, HEIGHT_TEMP / 8, 0), vec3(25.f, 25.f, 1.f), 3072,
                                           "PIN_LIFE.png");

        game_life1_trans = static_cast<Transform*>(game_life1->GetComponent(CT_TRANSFORM));
        game_life2_trans = static_cast<Transform*>(game_life2->GetComponent(CT_TRANSFORM));
        game_life3_trans = static_cast<Transform*>(game_life3->GetComponent(CT_TRANSFORM));

        GameObject->Weapon_Hud = OBJECT_GEN->CreateHud(vec3(WIDTH / 6 - 150, height / 8, 0), vec3(120, 80, 0),
                                                       3701, "PIN_WEAPON_HUD.png");
        GameObject->Life_Hud = OBJECT_GEN->CreateHud(vec3(WIDTH / 6, height / 8, 0), vec3(120, 80, 0), 3701,
                                                     "PIN_LIFE_HUD.png");

        p_data->Danger_sign = OBJECT_GEN->CreateHud(vec3(WIDTH / 2, HEIGHT_TEMP / 2 - 100, 0), vec3(0, 0, 0),
                                                    9601, "PIN_DANGER.png", LO_1);

        p_data->number_trans.clear();
        for (auto i : p_data->number_objects)
        {
            p_data->number_trans.push_back(dynamic_cast<Transform*>(i->GetComponent(CT_TRANSFORM)));
        }

        p_data->Danger_sign_Transform = dynamic_cast<Transform*>(p_data->Danger_sign->GetComponent(CT_TRANSFORM));
        p_data->Danger_sign_Hud = dynamic_cast<Hud*>(p_data->Danger_sign->GetComponent(CT_HUD));

        JSONREADER->ReadItemData();

        GatePass = OBJECT_GEN->CreateGatePass(vec3(-1.5f, -1.5f, 0), vec3(0, 0, 0), 9900, "PIN_GATEPASS.png");

        if (GameObject->Door_Stat == RG_BEFORE)
        {
            JSONREADER->ReadJsonRandomLevel(*GameObject);
            BeforeWall(*GameObject);
            BeforeDoor(*GameObject);
            BeforePlayer(*GameObject);
            BeforePistol(*GameObject);
            BeforeZombie(*GameObject);
        }
        else
        {
            JSONREADER->ReadJwonRandomLevelWall(GameObject->Room_Style);
            RandomInitWall(*GameObject);
            RandomInitDoor(*GameObject);

            RandomInitTrap(*GameObject);
            RandomInitPlayer(*GameObject);
            RandomInitZombie(*GameObject);
            RandomInitCamera(*GameObject);
            RandomGatePass(*GameObject);
            RandomInitAmmo(*GameObject);
            RandomCabinet(*GameObject);
            RandomLoadLastHint(*GameObject);
            RandomInitHint(*GameObject);
        }
        int j = 0;
        for (auto i : GameObject->Door)
        {
            GameObject->rotate_light.push_back(OBJECT_GEN->CreateRotateLight(i->GetPosition(), 12.f, 24.f));
            GameObject->rotate_light_trans.push_back(
                reinterpret_cast<Transform*>(GameObject->rotate_light[j]->GetComponent(CT_TRANSFORM)));
            GameObject->rotate_light_cont.push_back(
                reinterpret_cast<SpotLight*>(GameObject->rotate_light[j]->GetComponent(CT_SPOT_LIGHT)));
            ++j;
        }

        if (isgetAmmo)
        {
            OBJECT_GEN->CreateHud(vec3(WIDTH / 6 - 50, HEIGHT_TEMP / 8, 0), vec3(50, 50, 0), 3700,
                                  "PIN_AMMO.png");
        }

        Minimap.MiniMap_InitBase();
        Minimap.MiniMap_InitObject_Random(*GameObject);

        GameObject->Door_Stat = RG_CURRENT;

        GRAPHICS->TurnOnLights();

        LoadPlayerStatus(*GameObject);
        PLAYERLOGIC->Init();
        p_data->player = OBJECT_FACTORY->FindObject("player");
        p_data->m_collision = static_cast<Collision*>(p_data->player->GetComponent(CT_COLLISION));
        p_data->player_rigidbody = static_cast<RigidBody*>(p_data->player->GetComponent(CT_RIGID_BODY));

        if (GameObject->Room_Number == 1)
        {
            SOUNDMANAGER->play("01.mp3");
        }

        if ((GameObject->Room_Number == (*GameObject).EventNumbers[1] - 1)
            || (GameObject->Room_Number == (*GameObject).EventNumbers[2] - 1))
        {
            SOUNDMANAGER->play("03.mp3");
        }

        if ((GameObject->Room_Number == (*GameObject).EventNumbers[1]) || (GameObject->Room_Number == (*GameObject).
            EventNumbers[2]))
        {
            SOUNDMANAGER->play("04.mp3");
        }
    }

    float test = 0.f;

    void RandomLevelStateUpdate(float dt)
    {
        if (GameObject->player_pos_check.GetTime() < 0.2f)
        {
            if ((GameObject->Player->GetPosition().x <= 0.3f && GameObject->Player->GetPosition().x >= -0.3f)
                && (GameObject->Player->GetPosition().y <= 0.3f && GameObject->Player->GetPosition().y >= -0.3f))
            {
                GAME_STATE->Restart();
            }
        }
        GAMELOGIC->Set_PauseMenu();

        if (PlayerController::player_health <= 0.f)
        {
            if (GAMELOGIC->GameLife == 1)
            {
                GAME_STATE->SetNextState(SL_LOSE);
            }
            else
            {
                PlayerController::die_animation_end = true;
                GAMELOGIC->die_timer.Init();
            }
        }
        if (GAMELOGIC->GameLife == 2)
        {
            game_life3_trans->scale = vec3(0.f, 0.f, 0.f);
        }
        else if (GAMELOGIC->GameLife == 1)
        {
            game_life3_trans->scale = vec3(0.f, 0.f, 0.f);
            game_life2_trans->scale = vec3(0.f, 0.f, 0.f);
        }
        if (PlayerController::die_animation_end && GAMELOGIC->die_timer.GetTime() < 2.f)
        {
            GAMELOGIC->AniamtionMode();
        }
        if (PlayerController::die_animation_end && GAMELOGIC->die_timer.GetTime() > 2.5f)
        {
            SDL_HapticRumblePlay(APPLICATION->gControllerHaptic, 10.f, 500);
            SOUNDMANAGER->play("PLAYER_DIED_SOUND.wav");
            GameObject->Room_Number = 1;
            GAMELOGIC->GameLife--;
            PlayerController::player_health = 300.f;
            GRAPHICS->reset_cam_zoom();
            PlayerController::die_animation_end = false;
            GAME_STATE->Restart();
        }
        rot += 0.05f;
        if (rot > 360)
            rot = 0;

        vec3 rotDir(cos(rot), sin(rot), 0);

        for (auto& i : GameObject->rotate_light_cont)
            i->direction = rotDir;

        if (!APPLICATION->isUsingGamepad)
        {
            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            rand1_mouse_trans->setPosition(vec3(mouse_x, mouse_y, 0));
        }

        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_3))
        {
            GAME_STATE->SetNextState(SL_RANDOMLEVEL3);
        }


        if (isgetAmmo)
        {
            if (p_data->player->curr_ammo > 0)
            {
                OBJECT_GEN->CreateHud(vec3(WIDTH / 6 - 50, HEIGHT_TEMP / 8, 0), vec3(50, 50, 0), 3700,
                                      "PIN_AMMO.png");
                isgetAmmo = true;
            }
        }

        if (!isgetPistol)
        {
            if (p_data->player->is_get_pistol)
            {
                isgetPistol = true;
            }
        }

        if ((*GameObject).Room_Number == (*GameObject).EventNumbers[1] || (*GameObject).Room_Number == (*GameObject).
            EventNumbers[2])
        {
            PLAYERLOGIC->GetDamage_poison();
        }
        if ((*GameObject).Room_Number == (*GameObject).EventNumbers[0])
        {
            randomLevel::gatepass_confirm();
        }
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_F3))
        {
            GAME_STATE->Restart();
        }
        if (Input::GetInstance().IsPressed(SDL_SCANCODE_V))
        {
            GRAPHICS->camera_system->m_position.z = 20.f;
        }
        CheatCode((*GameObject));
        // Some cheat code

        Minimap.MiniMap_Update_Random(*GameObject);

        OpenTheDoor(*GameObject);
        std::string roomname = ToString((*GameObject).Room_Style);

        if (p_data->player->isHasHint)
            randomLevel::create_gathered_hint();

        if (p_data->player->has_rotate_hint)
        {
            randomLevel::create_rotate_gathered_hint();
        }
        if (p_data->player->isRotate)
            randomLevel::rotate_gathered_hint(dt);

        if ((*GameObject).Room_Number == (*GameObject).EventNumbers[1])
        {
            elapsed_time++;
            if (elapsed_time > 10.f)
            {
                PlayerController::player_health -= 1.f;
                elapsed_time = 0.f;
            }
        }

        if (p_data->player->is_in_Final)
        {
            randomLevel::create_numpad();
            APPLICATION->enterthecode = true;
        }

        //Hud Update
        game_life1->SetPosition(WIDTH / 6.f - 30 + GRAPHICS->camera_system->m_position.x,
                                HEIGHT_TEMP / 8.f + GRAPHICS->camera_system->m_position.y);
        game_life2->SetPosition(WIDTH / 6.f + GRAPHICS->camera_system->m_position.x,
                                HEIGHT_TEMP / 8.f + GRAPHICS->camera_system->m_position.y);
        game_life3->SetPosition(WIDTH / 6.f + 30 + GRAPHICS->camera_system->m_position.x,
                                HEIGHT_TEMP / 8.f + GRAPHICS->camera_system->m_position.y);
        GameObject->Weapon_Hud->SetPosition(WIDTH / 6.f - 150 + GRAPHICS->camera_system->m_position.x,
                                            720.f / 8.f + GRAPHICS->camera_system->m_position.y);
        GameObject->Life_Hud->SetPosition(WIDTH / 6.f + GRAPHICS->camera_system->m_position.x,
                                          720.f / 8.f + GRAPHICS->camera_system->m_position.y);

        GAMELOGIC->CheckingPassword();
    }

    void RandomLevelStateExit(void)
    {
        SavePlayerStatus(*GameObject);
        RandomSaveLastHint(*GameObject);
        PHYSICS->walls_and_zombies.clear();
        PHYSICS->walls.clear();
        OBJECT_FACTORY->DestroyAllObjects();
        JSONREADER->jsonReaderUnload();

        GameObject->rotate_light.clear();
        GameObject->rotate_light_trans.clear();
        GameObject->rotate_light_cont.clear();
    }

    void randomLevel::gatepass_confirm()
    {
        if (p_data->m_collision->CircleCircleCollisionCheck((*GameObject).Player, GatePass))
        {
            GatePass->SetScale_x(0);
            GatePass->SetScale_y(0);
            p_data->player->isGetPass = true;
        }
    }


    void randomLevel::create_gathered_hint()
    {
        if (!p_data->player->gathered_hint_order.empty())
        {
            switch (p_data->player->gathered_hint_order[0])
            {
            case 1:
                {
                    OBJECT_GEN->CreateHud(vec3(50.0f, HEIGHT_TEMP, 0), vec3(50.f, 50.f, 0.f),
                                          3052, "PIN_NUM" + std::to_string(GAMELOGIC->WhatIsSecretNumber(0) - 48) +
                                          ".png");
                    (*GameObject).IsGetHint[0] = true;
                    break;
                }
            case 2:
                {
                    OBJECT_GEN->CreateHud(vec3(100.0f, HEIGHT_TEMP, 0), vec3(50.f, 50.f, 0.f),
                                          3052, "PIN_NUM" + std::to_string(GAMELOGIC->WhatIsSecretNumber(1) - 48) +
                                          ".png");
                    (*GameObject).IsGetHint[1] = true;
                    break;
                }
            case 3:
                {
                    OBJECT_GEN->CreateHud(vec3(150.0f, HEIGHT_TEMP, 0), vec3(50.f, 50.f, 0.f),
                                          3052, "PIN_NUM" + std::to_string(GAMELOGIC->WhatIsSecretNumber(2) - 48) +
                                          ".png");
                    (*GameObject).IsGetHint[2] = true;
                    break;
                }
            case 4:
                {
                    OBJECT_GEN->CreateHud(vec3(200.0f, HEIGHT_TEMP, 0), vec3(50.f, 50.f, 0.f),
                                          3052, "PIN_NUM" + std::to_string(GAMELOGIC->WhatIsSecretNumber(3) - 48) +
                                          ".png");
                    (*GameObject).IsGetHint[3] = true;
                    break;
                }
            default:
                break;
            }
        }
        p_data->player->isHasHint = false;
    }

    void randomLevel::create_rotate_gathered_hint()
    {
        switch ((*GameObject).Room_Number)
        {
        case 1:
            rotate_hint_hud1 = OBJECT_GEN->CreateHud(vec3(WIDTH / 2.f, HEIGHT_TEMP / 2.f, 0),
                                                     vec3(80.f, 80.f, 0.f),
                                                     3052, "PIN_NUM" + std::to_string(
                                                         GAMELOGIC->WhatIsSecretNumber(0) - 48) + ".png");
            SOUNDMANAGER->play("ITEM_GRAB.wav");
            break;
        case 3:
            rotate_hint_hud1 = OBJECT_GEN->CreateHud(vec3(WIDTH / 2.f, HEIGHT_TEMP / 2.f, 0),
                                                     vec3(80.f, 80.f, 0.f),
                                                     3052, "PIN_NUM" + std::to_string(
                                                         GAMELOGIC->WhatIsSecretNumber(1) - 48) + ".png");
            SOUNDMANAGER->play("ITEM_GRAB.wav");
            break;
        case 5:
            rotate_hint_hud1 = OBJECT_GEN->CreateHud(vec3(WIDTH / 2.f, HEIGHT_TEMP / 2.f, 0),
                                                     vec3(80.f, 80.f, 0.f),
                                                     3052, "PIN_NUM" + std::to_string(
                                                         GAMELOGIC->WhatIsSecretNumber(2) - 48) + ".png");
            SOUNDMANAGER->play("ITEM_GRAB.wav");
            break;
        case 7:
            rotate_hint_hud1 = OBJECT_GEN->CreateHud(vec3(WIDTH / 2.f, HEIGHT_TEMP / 2.f, 0),
                                                     vec3(80.f, 80.f, 0.f),
                                                     3052, "PIN_NUM" + std::to_string(
                                                         GAMELOGIC->WhatIsSecretNumber(3) - 48) + ".png");
            SOUNDMANAGER->play("ITEM_GRAB.wav");
            break;
        default:
            break;
        }
        p_data->player->has_rotate_hint = false;
        p_data->player->isRotate = true;
    }

    void randomLevel::rotate_gathered_hint(float dt)
    {
        Object* a = rotate_hint_hud1;
        if (rotate_hint_hud1 != nullptr)
        {
            rotate_hint_hud1_trans = dynamic_cast<Transform*>(rotate_hint_hud1->GetComponent(CT_TRANSFORM));
            radian += 15.f;
            rotate_hint_hud1_trans->setRotation(vec3(0, radians(radian), 0));
            Transform* temp = rotate_hint_hud1_trans;
            if (radian > 720.f)
            {
                rotate_hint_hud1_trans->setScale(vec3(0, 0, 0));
                radian = 0.f;
                p_data->player->isRotate = false;
            }
        }
    }

    void randomLevel::create_before_hint()
    {
        for (auto i : Game_Random_Data::player_hint_order_1)
        {
            switch (i)
            {
            case 1:
                (*p_data).hint_hud1 = OBJECT_GEN->CreateHud(vec3(50.0f, HEIGHT_TEMP, 0),
                                                            vec3(50.f, 50.f, 0.f),
                                                            3052, "PIN_NUM" + std::to_string(
                                                                GAMELOGIC->WhatIsSecretNumber(0) - 48) + ".png");
                break;
            case 2:
                (*p_data).hint_hud2 = OBJECT_GEN->CreateHud(vec3(100.0f, HEIGHT_TEMP, 0),
                                                            vec3(50.f, 50.f, 0.f),
                                                            3052, "PIN_NUM" + std::to_string(
                                                                GAMELOGIC->WhatIsSecretNumber(1) - 48) + ".png");
                break;
            case 3:
                (*p_data).hint_hud3 = OBJECT_GEN->CreateHud(vec3(150.0f, HEIGHT_TEMP, 0),
                                                            vec3(50.f, 50.f, 0.f),
                                                            3052, "PIN_NUM" + std::to_string(
                                                                GAMELOGIC->WhatIsSecretNumber(2) - 48) + ".png");
                break;
            case 4:
                (*p_data).hint_hud4 = OBJECT_GEN->CreateHud(vec3(200.0f, HEIGHT_TEMP, 0),
                                                            vec3(50.f, 50.f, 0.f),
                                                            3052, "PIN_NUM" + std::to_string(
                                                                GAMELOGIC->WhatIsSecretNumber(3) - 48) + ".png");
            default:
                break;
            }
        }
    }

    void randomLevel::check_password()
    {
        std::string print;
        if (p_data->PrintFontCondition != GAMELOGIC->INDEX - 1)
        {
            switch (GAMELOGIC->INDEX - 1)
            {
            case 0:
                print = GAMELOGIC->WhatIsSecretNumber(0);
                p_data->FirstNumber = OBJECT_GEN->CreateAFont(vec3(460.f, 610.f, 0.f), 1.5f, print,
                                                              vec3(0.9f, 0.7f, 0.0f), 6101, 0.f, FT_HOLD);
                p_data->FirstNumberText = dynamic_cast<SpriteText*>(p_data->FirstNumber->GetComponent(CT_SPRITE_TEXT));
                p_data->PrintFontCondition = (GAMELOGIC->INDEX) - 1;
                break;
            case 1:
                print = GAMELOGIC->WhatIsSecretNumber(1);
                p_data->SecondNumber = OBJECT_GEN->CreateAFont(vec3(560.f, 610.f, 0.f), 1.5f, print,
                                                               vec3(0.9f, 0.7f, 0.0f), 6102, 0.f, FT_HOLD);
                p_data->SecondNumberText = dynamic_cast<SpriteText*>(p_data->SecondNumber->GetComponent(CT_SPRITE_TEXT)
                );
                p_data->PrintFontCondition = (GAMELOGIC->INDEX) - 1;
                break;
            case 2:
                print = GAMELOGIC->WhatIsSecretNumber(2);
                p_data->ThirdNumber = OBJECT_GEN->CreateAFont(vec3(660.f, 610.f, 0.f), 1.5f, print,
                                                              vec3(0.9f, 0.7f, 0.0f), 6103, 0.f, FT_HOLD);
                p_data->ThirdNumberText = dynamic_cast<SpriteText*>(p_data->ThirdNumber->GetComponent(CT_SPRITE_TEXT));
                p_data->PrintFontCondition = (GAMELOGIC->INDEX) - 1;
                break;
            case -1:
                print = GAMELOGIC->WhatIsSecretNumber(3);
                p_data->ForthNumber = OBJECT_GEN->CreateAFont(vec3(780.f, 610.f, 0.f), 1.5f, print,
                                                              vec3(0.9f, 0.7f, 0.0f), 6104, 0.f, FT_HOLD);
                p_data->ForthNumberText = dynamic_cast<SpriteText*>(p_data->ForthNumber->GetComponent(CT_SPRITE_TEXT));
                p_data->PrintFontCondition = (GAMELOGIC->INDEX) - 1;

                if (GAMELOGIC->CheckSecretNumber())
                {
                    SDL_HapticRumblePlay(APPLICATION->gControllerHaptic, 10.f, 500);
                    GAMELOGIC->ClearGetSecretNumber();
                    SDL_HapticRumblePlay(APPLICATION->gControllerHaptic, 0.7f, 100);
                    ENGINE->isPause = false;
                    GAME_STATE->SetNextState(SL_RANDOMLEVEL3);
                }
                else
                {
                }
                break;
            default:
                break;
            }
        }
        if (p_data->LoseFont != nullptr)
        {
            p_data->Font_timer += 1;
            if (p_data->Font_timer >= 60)
            {
                p_data->LoseFontText->setScale(0.f);
                p_data->Font_timer = 0;
            }
        }
    }

    void randomLevel::create_numpad()
    {
        PLAYERLOGIC->CreateNumpad();
        p_data->player->is_in_Final = false;
    }

    void randomLevel::destroy_numpad()
    {
        PLAYERLOGIC->DestroyNumpad();
    }


    void RandomLevelStateUnload(void)
    {
        randomLevel::rotate_hint_hud1 = nullptr;
        randomLevel::rotate_hint_hud1_trans = nullptr;
        GAMELOGIC->GameLife = 3;
        delete GameObject;
        delete p_data;

        for (int i = 0; i < 4; i++)
            (*GameObject).IsGetHint[i] = false;
    }

    void randomLevel::random_light1(float dt)
    {
        p_data->light_timer += 1;
        if (p_data->light_timer == 70)

            GRAPHICS->TurnOnLights();
        else if (p_data->light_timer == 90)

            GRAPHICS->TurnOffLights();
        else if (p_data->light_timer == 100)

            GRAPHICS->TurnOnLights();
        else if (p_data->light_timer == 110)

            GRAPHICS->TurnOffLights();
        else if (p_data->light_timer == 125)

            GRAPHICS->TurnOnLights();
        else if (p_data->light_timer >= 400)
            p_data->light_timer = 0;
    }
}
