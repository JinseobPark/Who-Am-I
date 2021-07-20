/**
\file        Data.h
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM250
\date        06/14/2018
\brief       store game data.
All content (c) 2018 DigiPen (USA) Corporation, all rights reserved.
*/
#ifndef DATA_H
#define DATA_H
#include "glm/glm.hpp"
#include <vector>
#include "RandomStruct.h"
#include <string>
#include "Collision.h"
#include "Timer.hpp"

namespace FindersEngine
{
    class Object;
    class Transform;

    enum Game_Mode
    {
        PLAY,
        EDIT
    };

	struct WayWalls
	{
		std::vector<Object*> UWall;
		std::vector<Object*> DWall;
		std::vector<Object*> LWall;
		std::vector<Object*> RWall;
		std::vector<Object*> CornerWall;

		unsigned int UWall_Count;
		unsigned int DWall_Count;
		unsigned int LWall_Count;
		unsigned int RWall_Count;
		unsigned int CornerWall_Count;
	};

    struct Game_Random_Data
    {
        int currLevel;
		Timer player_pos_check;
        static std::vector<unsigned> player_hint_1;
        static std::vector<unsigned> player_hint_order_1;

		static std::vector<unsigned> player_hint_2;
		static std::vector<unsigned> player_hint_order_2;

		static std::vector<Object*> number_objects_1;

        RoomStyle Room_Style;
        DoorStat Door_Stat;
        LastDoor Last_Door = LAST_RIGHT;
        CurrentDoor Current_Door = CURRENT_NONE;
        SureIsDoor IsDoorWay{false, false, false, false};
        SureIsCabinet IsCabinetWay{ false, false, false, false };
        WayWalls Walls;
        Object* Player;
		Object* Poison1;
		Object* PoisonDrum;
		Object* Boss;
		Object* gatepass;

		Object* Itembox1;
		Object* Itembox2;

        std::vector<Object*> rotate_light;
        std::vector<Transform*> rotate_light_trans;
        std::vector<SpotLight*> rotate_light_cont;

		Object* pistolhud;
		Object* ammohud;
		Object* ammo1;
		Object* ammo2;
		Object* ammo3;
		Object* ammo4;
		Object* pistol;

		Object* Weapon_Hud;
		Object* Life_Hud;

		Object* Item_Zombie;

		Transform* Poison1_transform;
		Transform* player_transform;
		static unsigned maxItemBoxCount;
		static unsigned getRandItemBoxCount() { return maxItemBoxCount; }

        std::vector<Object*> Ammo;
        std::vector<Object*> Zombie;
        std::vector<Object*> Door;
        std::vector<Object*> Cabinet;
		std::vector<int> EventNumbers;
        
        unsigned int Zombie_Count = 0;
        unsigned int Door_Count = 0;
        unsigned int Ammo_Count = 0;
        unsigned int PlayerHealth = 300;

        unsigned int Room_Number;
        unsigned int curr_ammo_;
        unsigned curr_grenade;
        bool Is_Get_Pistol;

        bool is_before = false;

		bool IsGetHint[4] = { false, false, false, false };
    };
    struct ObjectList
    {
        std::string List_Name;
        Object* List_Object = nullptr;
    };

    enum EditMode
    {
        TRANS,
        SCALE_X,
        SCALE_Y,
        ROTATION,
        NONE
    };

    struct GameData
    {
        Object* Player = nullptr;
        Object* FinalDoor = nullptr;

        std::vector<Object*> Wall;
        std::vector<Object*> Door;
        std::vector<Object*> Bullet;
        std::vector<Object*> Ammo;
        std::vector<Object*> Zombie;
        WayWalls Walls;
        Object* Pistol = nullptr;

        unsigned int Wall_Count = 0;
        unsigned int Zombie_Count = 0;
        unsigned int Door_Count = 0;
        unsigned int Ammo_Count = 0;

        unsigned int PlayerHealth = 100;

        unsigned int CurrentLevel = 1;

        bool Is_Get_Pistol = false;

        bool initiate = true;
    };

    struct PublicData
    {
        float Font_timer = 0.f;
        Collision* m_collision = nullptr;
        RigidBody* player_rigidbody = nullptr;
        Object* player = nullptr;
        std::vector<Object*> number_objects;
        std::vector<Transform*> number_trans;
        bool isDanger = false;
        Timer timer;
        float light_timer = 0.f;
        Object* Poison1 = nullptr;
        Transform* gatepass_transform = nullptr;
        Object* Danger_sign = nullptr;
        Transform* Danger_sign_Transform = nullptr;
        Hud* Danger_sign_Hud = nullptr;
        Object* DamageWarning = nullptr;
        Transform* DamageWarningtransform = nullptr;
        Hud* DamageWarningHud = nullptr;
        int PrintFontCondition = 0;
        Object* FirstNumber = nullptr;
        SpriteText* FirstNumberText = nullptr;
        Object* SecondNumber = nullptr;
        SpriteText* SecondNumberText = nullptr;
        Object* ThirdNumber = nullptr;
        SpriteText* ThirdNumberText = nullptr;
        Object* ForthNumber = nullptr;
        SpriteText* ForthNumberText = nullptr;
        SpriteText* LoseFontText = nullptr;
        Transform* Playertransform = nullptr;
        Object* LoseFont = nullptr;
        Object* hint_hud1 = nullptr;
        Object* hint_hud2 = nullptr;
        Object* hint_hud3 = nullptr;
        Object* hint_hud4 = nullptr;
    };
}
#endif
