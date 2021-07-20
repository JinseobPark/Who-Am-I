/**
\file        RandomGenerator.cpp
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM250
\date        06/14/2018
\brief       Random Generator.
All content (c) 2018 DigiPen (USA) Corporation, all rights reserved.
*/
#include "Headers_Components.h"
#include "Input.h"
#include "ObjectFactory.h"
#include "ObjectGenerator.h"
#include "PlayerController.h"
#include "RandomGenerator.h"
#include "RandomGeneratorLogic.h"
#include "jsonReader.h"
#include <cstdlib>  //rand
#include <ctime>    //time
#define WIDTH 1280
#define HEIGHT_TEMP 640 //720

namespace FindersEngine
{
    unsigned Game_Random_Data::maxItemBoxCount = 0;

    void RandomInitPlayer(Game_Random_Data& data)
    {
        glm::vec3 player_position = glm::vec3(0.f, 0.f, 0.f);
        switch (data.Last_Door)
        {
            case (LAST_UP):
            {
                player_position = OBJECT_FACTORY->FindObjectID(4101)->GetPosition() + glm::vec3(0.f, 0.35f, 0.f);
                break;
            }
            case (LAST_DOWN):
            {
                player_position = OBJECT_FACTORY->FindObjectID(4100)->GetPosition() - glm::vec3(0.f, 0.35f, 0.f);
                break;
            }
            case (LAST_LEFT):
            {
                player_position = OBJECT_FACTORY->FindObjectID(4103)->GetPosition() - glm::vec3(0.35f, 0.f, 0.f);
                break;
            }
            case (LAST_RIGHT):
            {
                player_position = OBJECT_FACTORY->FindObjectID(4102)->GetPosition() + glm::vec3(0.35f, 0.f, 0.f);
                break;
            }
			case (LAST_NONE):
			{
				player_position = OBJECT_FACTORY->FindObjectID(4102)->GetPosition() + glm::vec3(0.35f, 0.f, 0.f);
				break;
			}
            default:
                break;
        }

        data.Player = OBJECT_GEN->CreatePlayer(player_position, PlayerId);
    }

    void RandomInitWall(Game_Random_Data& data)
    {
        data.Walls.UWall_Count = JSONREADER->getUWallCount();
        data.Walls.DWall_Count = JSONREADER->getDWallCount();
        data.Walls.LWall_Count = JSONREADER->getLWallCount();
        data.Walls.RWall_Count = JSONREADER->getRWallCount();
        data.Walls.CornerWall_Count = JSONREADER->getCornerWallCount();
        data.Walls.UWall.clear();
        data.Walls.DWall.clear();
        data.Walls.LWall.clear();
        data.Walls.RWall.clear();
        data.Walls.CornerWall.clear();
        for (unsigned int i = 0; i < data.Walls.UWall_Count; ++i)
        {
            std::string num = std::to_string(i);
            if (JSONREADER->getUWallInverse(i))
            {
                data.Walls.UWall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getUWallPos(i), JSONREADER->getUWallScale(i) + glm::vec3(6, 0, 0), WallId + i, "Wall" + num, "PIN_DWALL.png"));
            }
            else
                data.Walls.UWall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getUWallPos(i), JSONREADER->getUWallScale(i) + glm::vec3(6, 0, 0), WallId + i, "Wall" + num, "PIN_UWALL.png"));
        }
        for (unsigned int i = 0; i < data.Walls.DWall_Count; ++i)
        {
            std::string num = std::to_string(i);
            if (JSONREADER->getDWallInverse(i))
            {
                data.Walls.DWall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getDWallPos(i), JSONREADER->getDWallScale(i) + glm::vec3(6, 0, 0), WallId + i, "Wall" + num, "PIN_UWALL.png"));
            }
            else
                data.Walls.DWall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getDWallPos(i), JSONREADER->getDWallScale(i) + glm::vec3(6, 0, 0), WallId + i, "Wall" + num, "PIN_DWALL.png"));
        }
        for (unsigned int i = 0; i < data.Walls.LWall_Count; ++i)
        {
            std::string num = std::to_string(i);
            if (JSONREADER->getLWallInverse(i))
            {
                data.Walls.LWall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getLWallPos(i), JSONREADER->getLWallScale(i) + glm::vec3(0, 6, 0), WallId + i, "Wall" + num, "PIN_RWALL.png"));
            }
            else
                data.Walls.LWall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getLWallPos(i), JSONREADER->getLWallScale(i) + glm::vec3(0, 6, 0), WallId + i, "Wall" + num, "PIN_LWALL.png"));
        }
        for (unsigned int i = 0; i < data.Walls.RWall_Count; ++i)
        {
            std::string num = std::to_string(i);
            if (JSONREADER->getRWallInverse(i))
            {
                data.Walls.RWall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getRWallPos(i), JSONREADER->getRWallScale(i) + glm::vec3(0, 6, 0), WallId + i, "Wall" + num, "PIN_LWALL.png"));
            }
            else
                data.Walls.RWall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getRWallPos(i), JSONREADER->getRWallScale(i) + glm::vec3(0, 6, 0), WallId + i, "Wall" + num, "PIN_RWALL.png"));
        }
        for (unsigned int i = 0; i < data.Walls.CornerWall_Count; ++i)
        {
            std::string num = std::to_string(i);
            if (JSONREADER->getCornerWallType(i))
            {
                data.Walls.CornerWall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getCornerWallPos(i), JSONREADER->getCornerWallScale(i), WallId + i, "Wall" + num, "PIN_L_EDGE.png"));
            }
            else
                data.Walls.CornerWall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getCornerWallPos(i), JSONREADER->getCornerWallScale(i), WallId + i, "Wall" + num, "PIN_R_EDGE.png"));
        }
    }

    void RandomInitDoor(Game_Random_Data& data)
    {
        JudgeMakeDoor(data);
        data.Door_Count = 0;
        data.Door.clear();
        int ChooseWall;
        glm::vec3 temp;

        if (data.IsDoorWay.UpDoor)
        {
            ChooseWall = RandomIntNumber(0, data.Walls.UWall_Count);
            temp = data.Walls.UWall[ChooseWall]->GetPosition();
            temp.x += RandomFloatNumber(-data.Walls.UWall[ChooseWall]->GetScale().x / 1280.f * 0.5f, data.Walls.UWall[ChooseWall]->GetScale().x / 1280.f * 0.5f);
            if (data.Last_Door == LAST_DOWN)
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_USED_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 0));
            else
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 0));
            data.Door_Count++;
        }
        if (data.IsDoorWay.DownDoor)
        {
            ChooseWall = RandomIntNumber(0, data.Walls.DWall_Count);
            temp = data.Walls.DWall[ChooseWall]->GetPosition();
            temp.x += RandomFloatNumber(-data.Walls.DWall[ChooseWall]->GetScale().x / 1280.f * 0.5f, data.Walls.DWall[ChooseWall]->GetScale().x / 1280.f * 0.5f);
            if (data.Last_Door == LAST_UP)
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_USED_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 1, glm::radians(180.f)));
            else
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 1, glm::radians(180.f)));
            data.Door_Count++;
        }
        if (data.IsDoorWay.LeftDoor)
        {
            ChooseWall = RandomIntNumber(0, data.Walls.LWall_Count);
            temp = data.Walls.LWall[ChooseWall]->GetPosition();
            temp.y += RandomFloatNumber(-data.Walls.LWall[ChooseWall]->GetScale().y / 1280.f * 0.5f, data.Walls.LWall[ChooseWall]->GetScale().y / 1280.f * 0.5f);
            if (data.Last_Door == LAST_RIGHT)
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_USED_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 2, glm::radians(90.f)));
            else
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 2, glm::radians(90.f)));
            data.Door_Count++;
        }
        if (data.IsDoorWay.RightDoor)
        {
            ChooseWall = RandomIntNumber(0, data.Walls.RWall_Count);
            temp = data.Walls.RWall[ChooseWall]->GetPosition();
            temp.y += RandomFloatNumber(-data.Walls.RWall[ChooseWall]->GetScale().y / 1280.f * 0.5f, data.Walls.RWall[ChooseWall]->GetScale().y / 1280.f * 0.5f);
            if (data.Last_Door == LAST_LEFT)
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_USED_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 3, glm::radians(-90.f)));
            else
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 3, glm::radians(-90.f)));
            data.Door_Count++;
        }
    }

    void RandomInitDoorBoss(Game_Random_Data& data)
    {
        JudgeMakeDoorBoss(data);
        data.Door_Count = 0;
        data.Door.clear();
        int ChooseWall;
        glm::vec3 temp;

        if (data.IsDoorWay.UpDoor)
        {
            ChooseWall = RandomIntNumber(0, data.Walls.UWall_Count);
            temp = data.Walls.UWall[ChooseWall]->GetPosition();
            temp.x += RandomFloatNumber(-data.Walls.UWall[ChooseWall]->GetScale().x / 1280.f * 0.5f, data.Walls.UWall[ChooseWall]->GetScale().x / 1280.f * 0.5f);
            if (data.Last_Door == LAST_DOWN)
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_USED_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 0, glm::radians(180.f)));
            else
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 0));
            data.Door_Count++;
        }
        if (data.IsDoorWay.DownDoor)
        {
            ChooseWall = RandomIntNumber(0, data.Walls.DWall_Count);
            temp = data.Walls.DWall[ChooseWall]->GetPosition();
            temp.x += RandomFloatNumber(-data.Walls.DWall[ChooseWall]->GetScale().x / 1280.f * 0.5f, data.Walls.DWall[ChooseWall]->GetScale().x / 1280.f * 0.5f);
            if (data.Last_Door == LAST_UP)
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_USED_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 1));
            else
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 1, glm::radians(180.f)));
            data.Door_Count++;
        }
        if (data.IsDoorWay.LeftDoor)
        {
            ChooseWall = RandomIntNumber(0, data.Walls.LWall_Count);
            temp = data.Walls.LWall[ChooseWall]->GetPosition();
            temp.y += RandomFloatNumber(-data.Walls.LWall[ChooseWall]->GetScale().y / 1280.f * 0.5f, data.Walls.LWall[ChooseWall]->GetScale().y / 1280.f * 0.5f);
            if (data.Last_Door == LAST_RIGHT)
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_USED_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 2, glm::radians(90.f)));
            else
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 2, glm::radians(90.f)));
            data.Door_Count++;
        }
        if (data.IsDoorWay.RightDoor)
        {
            ChooseWall = RandomIntNumber(0, data.Walls.RWall_Count);
            temp = data.Walls.RWall[ChooseWall]->GetPosition();
            temp.y += RandomFloatNumber(-data.Walls.RWall[ChooseWall]->GetScale().y / 1280.f * 0.5f, data.Walls.RWall[ChooseWall]->GetScale().y / 1280.f * 0.5f);
            if (data.Last_Door == LAST_LEFT)
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_USED_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 3, glm::radians(-90.f)));
            else
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_UDOOR.png", temp, glm::vec3(460, 300, 0), OT_RANDOMDOOR, ST_RECTANGLE, DoorId + 3, glm::radians(-90.f)));
            data.Door_Count++;
        }
    }

    void RandomInitZombie(Game_Random_Data& data)
    {
        int zombie_type;

        data.Zombie_Count = RandomIntNumber(2, 5 + (int)(data.Room_Number / 2));
        data.Zombie.clear();
        if (!(data.Room_Number == 1))
        {
            for (unsigned int i = 0; i < data.Zombie_Count; ++i)
            {
                zombie_type = RandomIntNumber(1, 4);
                data.Zombie.push_back(OBJECT_GEN->CreateZombie(SetObjectPos(120, data), ZombieId + i, ZombieType(zombie_type)));
            }
        }
    }

    void RandomInitZombie2(Game_Random_Data& data)
    {
        int zombie_type;

        data.Zombie_Count = RandomIntNumber(2, 4 + (int)(data.Room_Number / 2));
        data.Zombie.clear();
        if (!(data.Room_Number == 1) )
        {
			if(!(data.Room_Number == data.EventNumbers[5]))
            for (unsigned int i = 0; i < data.Zombie_Count; ++i)
            {
                zombie_type = RandomIntNumber(1, 4);
                data.Zombie.push_back(OBJECT_GEN->CreateZombie(SetObjectPos(120, data), ZombieId + i, ZombieType(zombie_type)));
            }
			data.Zombie.push_back(OBJECT_GEN->CreateZombie(SetObjectPos(120, data), ZombieId + data.Zombie_Count, Z_HOLDER));
        }
    }


    void RandomCabinet(Game_Random_Data& data)
    {
        const int itembox_count = RandomIntNumber(2, 4);
        Game_Random_Data::maxItemBoxCount = itembox_count;
        int choose_wall;
        int item_box_way = RandomIntNumber(1, 5); //1~4, direction of item box
        int iter = 1;
        int even_num = 0;

        Object* up_door = OBJECT_FACTORY->FindObjectID(4100);
        Object* down_door = OBJECT_FACTORY->FindObjectID(4101);
        Object* left_door = OBJECT_FACTORY->FindObjectID(4102);
        Object* right_door = OBJECT_FACTORY->FindObjectID(4103);

        Transform* up_trans = nullptr;
        Transform* down_trans = nullptr;
        Transform* left_trans = nullptr;
        Transform* right_trans = nullptr;

        if (up_door)
            up_trans = dynamic_cast<Transform*>(up_door->GetComponent(CT_TRANSFORM));
        if (down_door)
            down_trans = dynamic_cast<Transform*>(down_door->GetComponent(CT_TRANSFORM));
        if (left_door)
            left_trans = dynamic_cast<Transform*>(left_door->GetComponent(CT_TRANSFORM));
        if (right_door)
            right_trans = dynamic_cast<Transform*>(right_door->GetComponent(CT_TRANSFORM));

        glm::vec3 door_pos;
        glm::vec3 door_scale;
        float min_offset;
        float max_offset;
        float wall_min_offset;
        float wall_max_offset;
        glm::vec3 itemBox_pos;
        glm::vec3 prev_itemBox_pos = glm::vec3(0, 0, 0);
        glm::vec3 prev_box_minOffset;
        glm::vec3 prev_box_maxOffset;
        if (data.Room_Number % 2 == 1)
        {
            switch (item_box_way)
            {
                case 1:
                    choose_wall = RandomIntNumber(0, data.Walls.LWall_Count);
                    itemBox_pos = data.Walls.LWall[choose_wall]->GetPosition();
                    itemBox_pos.y = RandomFloatNumber(data.Walls.LWall[choose_wall]->GetPosition().y - data.Walls.LWall[choose_wall]->GetScale().y / 800.f * 0.5f,
                                                      data.Walls.LWall[choose_wall]->GetPosition().y + data.Walls.LWall[choose_wall]->GetScale().y / 800.f * 0.5f);
                    if (left_trans)
                    {
                        door_pos = left_trans->getPosition();
                        door_scale = left_trans->getScale();
                        min_offset = door_pos.y - (door_scale.y / 720.f * 0.5f);
                        max_offset = door_pos.y + (door_scale.y / 720.f * 0.5f);
                        wall_min_offset = data.Walls.LWall[choose_wall]->GetPosition().y - data.Walls.LWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        wall_max_offset = data.Walls.LWall[choose_wall]->GetPosition().y + data.Walls.LWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        while ((itemBox_pos.y < max_offset) && (itemBox_pos.y > min_offset) && (itemBox_pos.y < wall_max_offset) && (itemBox_pos.y > wall_min_offset))
                        {
                            itemBox_pos.y = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), data.Room_Number, item_box_way));
                    }
                    else
                    {
                        wall_min_offset = data.Walls.LWall[choose_wall]->GetPosition().y - data.Walls.LWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        wall_max_offset = data.Walls.LWall[choose_wall]->GetPosition().y + data.Walls.LWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        while ((itemBox_pos.y < wall_max_offset) && (itemBox_pos.y > wall_min_offset))
                        {
                            itemBox_pos.y = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), data.Room_Number, item_box_way));
                    }
                    break;
                case 2:
                    choose_wall = RandomIntNumber(0, data.Walls.UWall_Count);
                    itemBox_pos = data.Walls.UWall[choose_wall]->GetPosition();
                    itemBox_pos.x = RandomFloatNumber(data.Walls.UWall[choose_wall]->GetPosition().x - data.Walls.UWall[choose_wall]->GetScale().x / 1200.f * 0.5f,
                                                      data.Walls.UWall[choose_wall]->GetPosition().x + data.Walls.UWall[choose_wall]->GetScale().x / 1200.f * 0.5f);
                    if (up_trans)
                    {
                        door_pos = up_trans->getPosition();
                        door_scale = up_trans->getScale();
                        min_offset = door_pos.x - (door_scale.x / 1280.f * 0.5f);
                        max_offset = door_pos.x + (door_scale.x / 1280.f * 0.5f);
                        wall_min_offset = data.Walls.UWall[choose_wall]->GetPosition().x - data.Walls.UWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        wall_max_offset = data.Walls.UWall[choose_wall]->GetPosition().x + data.Walls.UWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        while ((itemBox_pos.x < max_offset) && (itemBox_pos.x > min_offset) && (itemBox_pos.x < wall_max_offset) && (itemBox_pos.x > wall_min_offset))
                        {
                            itemBox_pos.x = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), data.Room_Number, item_box_way));
                    }
                    else
                    {
                        wall_min_offset = data.Walls.UWall[choose_wall]->GetPosition().x - data.Walls.UWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        wall_max_offset = data.Walls.UWall[choose_wall]->GetPosition().x + data.Walls.UWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        while ((itemBox_pos.x < wall_max_offset) && (itemBox_pos.x > wall_min_offset))
                        {
                            itemBox_pos.x = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), data.Room_Number, item_box_way));
                    }
                    break;
                case 3:
                    choose_wall = RandomIntNumber(0, data.Walls.RWall_Count);
                    itemBox_pos = data.Walls.RWall[choose_wall]->GetPosition();
                    itemBox_pos.y = RandomFloatNumber(data.Walls.RWall[choose_wall]->GetPosition().y - data.Walls.RWall[choose_wall]->GetScale().y / 800.f * 0.5f,
                                                      data.Walls.RWall[choose_wall]->GetPosition().y + data.Walls.RWall[choose_wall]->GetScale().y / 800.f * 0.5f);
                    if (right_trans)
                    {
                        door_pos = right_trans->getPosition();
                        door_scale = right_trans->getScale();
                        min_offset = door_pos.y - (door_scale.y / 720.f * 0.5f);
                        max_offset = door_pos.y + (door_scale.y / 720.f * 0.5f);
                        wall_min_offset = data.Walls.RWall[choose_wall]->GetPosition().y - data.Walls.RWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        wall_max_offset = data.Walls.RWall[choose_wall]->GetPosition().y + data.Walls.RWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        while ((itemBox_pos.y < max_offset) && (itemBox_pos.y > min_offset) && (itemBox_pos.y < wall_max_offset) && (itemBox_pos.y > wall_min_offset))
                        {
                            itemBox_pos.y = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), data.Room_Number, item_box_way));
                    }
                    else
                    {
                        wall_min_offset = data.Walls.RWall[choose_wall]->GetPosition().y - data.Walls.RWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        wall_max_offset = data.Walls.RWall[choose_wall]->GetPosition().y + data.Walls.RWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        while ((itemBox_pos.y < wall_max_offset) && (itemBox_pos.y > wall_min_offset))
                        {
                            itemBox_pos.y = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), data.Room_Number, item_box_way));
                    }
                    break;
                case 4:
                    choose_wall = RandomIntNumber(0, data.Walls.DWall_Count);
                    itemBox_pos = data.Walls.DWall[choose_wall]->GetPosition();
                    itemBox_pos.x = RandomFloatNumber(data.Walls.DWall[choose_wall]->GetPosition().x - data.Walls.DWall[choose_wall]->GetScale().x / 1200.f * 0.5f,
                                                      data.Walls.DWall[choose_wall]->GetPosition().x + data.Walls.DWall[choose_wall]->GetScale().x / 1200.f * 0.5f);
                    if (down_trans)
                    {
                        door_pos = down_trans->getPosition();
                        door_scale = down_trans->getScale();
                        min_offset = door_pos.x - (door_scale.x / 1280.f * 0.5f);
                        max_offset = door_pos.x + (door_scale.x / 1280.f * 0.5f);
                        wall_min_offset = data.Walls.DWall[choose_wall]->GetPosition().x - data.Walls.DWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        wall_max_offset = data.Walls.DWall[choose_wall]->GetPosition().x + data.Walls.DWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        while ((itemBox_pos.x < max_offset) && (itemBox_pos.x > min_offset) && (itemBox_pos.x < wall_max_offset) && (itemBox_pos.x > wall_min_offset))
                        {
                            itemBox_pos.x = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), data.Room_Number, item_box_way));
                    }
                    else
                    {
                        wall_min_offset = data.Walls.DWall[choose_wall]->GetPosition().x - data.Walls.DWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        wall_max_offset = data.Walls.DWall[choose_wall]->GetPosition().x + data.Walls.DWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        while ((itemBox_pos.x < wall_max_offset) && (itemBox_pos.x > wall_min_offset))
                        {
                            itemBox_pos.x = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), data.Room_Number, item_box_way));
                    }
                    break;
                default:
                    break;
            }
            iter = 2;
        }
        for (iter; iter <= itembox_count; ++iter)
        {
            if (item_box_way > 4)
                item_box_way = 1;
            if (iter % 2 == 1)
            {
                even_num = iter + 1;
            }
            else
                even_num += 2;
            switch (item_box_way)
            {
                case 1:
                    choose_wall = RandomIntNumber(0, data.Walls.LWall_Count);
                    itemBox_pos = data.Walls.LWall[choose_wall]->GetPosition();
                    itemBox_pos.y = RandomFloatNumber(data.Walls.LWall[choose_wall]->GetPosition().y - data.Walls.LWall[choose_wall]->GetScale().y / 800.f * 0.5f,
                                                      data.Walls.LWall[choose_wall]->GetPosition().y + data.Walls.LWall[choose_wall]->GetScale().y / 800.f * 0.5f);
                    if (left_trans)
                    {
                        door_pos = left_trans->getPosition();
                        door_scale = left_trans->getScale();
                        prev_box_minOffset = prev_itemBox_pos;
                        prev_box_maxOffset = prev_itemBox_pos;
                        prev_box_minOffset.y = prev_itemBox_pos.y - 400 / 720.f;
                        prev_box_maxOffset.y = prev_itemBox_pos.y + 400 / 720.f;
                        min_offset = door_pos.y - (door_scale.y / 720.f * 0.5f);
                        max_offset = door_pos.y + (door_scale.y / 720.f * 0.5f);
                        wall_min_offset = data.Walls.LWall[choose_wall]->GetPosition().y - data.Walls.LWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        wall_max_offset = data.Walls.LWall[choose_wall]->GetPosition().y + data.Walls.LWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        while (itemBox_pos.y < max_offset && itemBox_pos.y > min_offset && itemBox_pos.y < wall_max_offset && itemBox_pos.y > wall_min_offset
                            /*&& itemBox_pos.y < prev_box_maxOffset.y && itemBox_pos.y > prev_box_minOffset.y*/)
                        {
                            itemBox_pos.y = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        if (even_num <= 7)
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), even_num, item_box_way));
                        else
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), iter, item_box_way));
                    }
                    else
                    {
                        wall_min_offset = data.Walls.LWall[choose_wall]->GetPosition().y - data.Walls.LWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        wall_max_offset = data.Walls.LWall[choose_wall]->GetPosition().y + data.Walls.LWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        while (itemBox_pos.y < wall_max_offset && itemBox_pos.y > wall_min_offset)
                        {
                            itemBox_pos.y = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        if (even_num <= 7)
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), even_num, item_box_way));
                        else
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), iter, item_box_way));
                    }
                    ++item_box_way;
                    break;
                case 2:
                    choose_wall = RandomIntNumber(0, data.Walls.UWall_Count);
                    itemBox_pos = data.Walls.UWall[choose_wall]->GetPosition();
                    itemBox_pos.x = RandomFloatNumber(data.Walls.UWall[choose_wall]->GetPosition().x - data.Walls.UWall[choose_wall]->GetScale().x / 800.f * 0.5f,
                                                      data.Walls.UWall[choose_wall]->GetPosition().x + data.Walls.UWall[choose_wall]->GetScale().x / 800.f * 0.5f);
                    if (up_trans)
                    {
                        door_pos = up_trans->getPosition();
                        door_scale = up_trans->getScale();
                        prev_box_minOffset = prev_itemBox_pos;
                        prev_box_maxOffset = prev_itemBox_pos;
                        prev_box_minOffset.x = prev_itemBox_pos.x - 400 / 1280.f;
                        prev_box_maxOffset.x = prev_itemBox_pos.x + 400 / 1280.f;
                        min_offset = door_pos.x - (door_scale.x / 1280.f * 0.5f);
                        max_offset = door_pos.x + (door_scale.x / 1280.f * 0.5f);
                        wall_min_offset = data.Walls.UWall[choose_wall]->GetPosition().x - data.Walls.UWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        wall_max_offset = data.Walls.UWall[choose_wall]->GetPosition().x + data.Walls.UWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        while (itemBox_pos.x < max_offset && itemBox_pos.x > min_offset && itemBox_pos.x < wall_max_offset && itemBox_pos.x > wall_min_offset
                            /*&& itemBox_pos.x < prev_box_maxOffset.x && itemBox_pos.x > prev_box_minOffset.x*/)
                        {
                            itemBox_pos.x = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        if (even_num <= 7)
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), even_num, item_box_way));
                        else
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), iter, item_box_way));
                    }
                    else
                    {
                        wall_min_offset = data.Walls.UWall[choose_wall]->GetPosition().x - data.Walls.UWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        wall_max_offset = data.Walls.UWall[choose_wall]->GetPosition().x + data.Walls.UWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        while (itemBox_pos.x < wall_max_offset && itemBox_pos.x > wall_min_offset)
                        {
                            itemBox_pos.x = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        if (even_num <= 7)
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), even_num, item_box_way));
                        else
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), iter, item_box_way));
                    }
                    ++item_box_way;
                    break;
                case 3:
                    choose_wall = RandomIntNumber(0, data.Walls.RWall_Count);
                    itemBox_pos = data.Walls.RWall[choose_wall]->GetPosition();
                    itemBox_pos.y = RandomFloatNumber(data.Walls.RWall[choose_wall]->GetPosition().y - data.Walls.RWall[choose_wall]->GetScale().y / 800.f * 0.5f,
                                                      data.Walls.RWall[choose_wall]->GetPosition().y + data.Walls.RWall[choose_wall]->GetScale().y / 800.f * 0.5f);
                    if (right_trans)
                    {
                        door_pos = right_trans->getPosition();
                        door_scale = right_trans->getScale();
                        min_offset = door_pos.y - (door_scale.y / 720.f * 0.5f);
                        max_offset = door_pos.y + (door_scale.y / 720.f * 0.5f);

                        prev_box_minOffset = prev_itemBox_pos;
                        prev_box_maxOffset = prev_itemBox_pos;
                        prev_box_minOffset.y = prev_itemBox_pos.y - 400 / 720.f;
                        prev_box_maxOffset.y = prev_itemBox_pos.y + 400 / 720.f;
                        wall_min_offset = data.Walls.RWall[choose_wall]->GetPosition().y - data.Walls.RWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        wall_max_offset = data.Walls.RWall[choose_wall]->GetPosition().y + data.Walls.RWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        while (itemBox_pos.y < max_offset && itemBox_pos.y > min_offset && itemBox_pos.y < wall_max_offset && itemBox_pos.y > wall_min_offset
                            /*&& itemBox_pos.y < prev_box_maxOffset.y && itemBox_pos.y > prev_box_minOffset.y*/)
                        {
                            itemBox_pos.y = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        if (even_num <= 7)
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), even_num, item_box_way));
                        else
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), iter, item_box_way));
                    }
                    else
                    {
                        wall_min_offset = data.Walls.RWall[choose_wall]->GetPosition().y - data.Walls.RWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        wall_max_offset = data.Walls.RWall[choose_wall]->GetPosition().y + data.Walls.RWall[choose_wall]->GetScale().y / 800.f * 0.5f;
                        while (itemBox_pos.y < wall_max_offset && itemBox_pos.y > wall_min_offset)
                        {
                            itemBox_pos.y = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        if (even_num <= 7)
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), even_num, item_box_way));
                        else
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), iter, item_box_way));
                    }
                    ++item_box_way;
                    break;
                case 4:
                    choose_wall = RandomIntNumber(0, data.Walls.DWall_Count);
                    itemBox_pos = data.Walls.DWall[choose_wall]->GetPosition();
                    itemBox_pos.x = RandomFloatNumber(data.Walls.DWall[choose_wall]->GetPosition().x - data.Walls.DWall[choose_wall]->GetScale().x / 800.f * 0.5f,
                                                      data.Walls.DWall[choose_wall]->GetPosition().x + data.Walls.DWall[choose_wall]->GetScale().x / 800.f * 0.5f);
                    if (down_trans)
                    {
                        door_pos = down_trans->getPosition();
                        door_scale = down_trans->getScale();
                        min_offset = door_pos.x - (door_scale.x / 1280.f * 0.5f);
                        max_offset = door_pos.x + (door_scale.x / 1280.f * 0.5f);
                        prev_box_minOffset = prev_itemBox_pos;
                        prev_box_maxOffset = prev_itemBox_pos;
                        prev_box_minOffset.x = prev_itemBox_pos.x - 400 / 1280.f;
                        prev_box_maxOffset.x = prev_itemBox_pos.x + 400 / 1280.f;
                        wall_min_offset = data.Walls.DWall[choose_wall]->GetPosition().x - data.Walls.DWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        wall_max_offset = data.Walls.DWall[choose_wall]->GetPosition().x + data.Walls.DWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        while (itemBox_pos.x < max_offset && itemBox_pos.x > min_offset && itemBox_pos.x < wall_max_offset && itemBox_pos.x > wall_min_offset
                            /*&& itemBox_pos.x < prev_box_maxOffset.x && itemBox_pos.x > prev_box_minOffset.x*/)
                        {
                            itemBox_pos.x = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        if (even_num <= 7)
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), even_num, item_box_way));
                        else
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), iter, item_box_way));
                    }
                    else
                    {
                        wall_min_offset = data.Walls.DWall[choose_wall]->GetPosition().x - data.Walls.DWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        wall_max_offset = data.Walls.DWall[choose_wall]->GetPosition().x + data.Walls.DWall[choose_wall]->GetScale().x / 1200.f * 0.5f;
                        while (itemBox_pos.x < wall_max_offset && itemBox_pos.x > wall_min_offset)
                        {
                            itemBox_pos.x = RandomFloatNumber(wall_min_offset, wall_max_offset);
                        }
                        prev_itemBox_pos = itemBox_pos;
                        if (even_num <= 7)
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), even_num, item_box_way));
                        else
                            data.Cabinet.push_back(OBJECT_GEN->CreateRandItemBox(itemBox_pos, glm::vec3(100, 100, 0), iter, item_box_way));
                    }
                    ++item_box_way;
                    break;

                default:
                    break;
            }
        }
    }

    void RandomInitCamera(Game_Random_Data& data)
    {
    }

    void RandomInitTrap(Game_Random_Data& data)
    {
        if (data.Room_Number == data.EventNumbers[1] || data.Room_Number == data.EventNumbers[2])
        {
            /*data.Poison1 = OBJECT_GEN->CreatePoison(SetObjectPos(120, data), glm::vec3(600, 600, 0), 9600, "PIN_POISON.png");
            data.PoisonDrum = OBJECT_GEN->CreateSprite("PIN_POISONDRUM.png", glm::vec3(data.Poison1->GetPosition().x - 0.2f,
                                                                                       data.Poison1->GetPosition().y + 0.5f,0),glm::vec3(350, 250, 0), 9602);*/

            data.Poison1 = OBJECT_GEN->CreatePoison(SetObjectPosWithoutPlayer(300, data), glm::vec3(700, 700, 0), 9600, "PIN_POISON.png");
            data.PoisonDrum = OBJECT_GEN->CreateSprite("PIN_POISONDRUM.png",
                                                       glm::f32vec3(data.Poison1->GetPosition().x - 0.2f, data.Poison1->GetPosition().y + 0.2f, 0),
                                                       glm::vec3(350, 250, 0), 9602);
        }
    }

    void RandomInitTrap2(Game_Random_Data& data)
    {
        if (data.Room_Number == data.EventNumbers[1] || data.Room_Number == data.EventNumbers[2] || data.Room_Number == data.EventNumbers[4])
        {
            /*data.Poison1 = OBJECT_GEN->CreatePoison(SetObjectPos(120, data), glm::vec3(600, 600, 0), 9600, "PIN_POISON.png");
            data.PoisonDrum = OBJECT_GEN->CreateSprite("PIN_POISONDRUM.png", glm::vec3(data.Poison1->GetPosition().x - 0.2f,
            data.Poison1->GetPosition().y + 0.5f,0),glm::vec3(350, 250, 0), 9602);*/

            data.Poison1 = OBJECT_GEN->CreatePoison(SetObjectPosWithoutPlayer(300, data), glm::vec3(700, 700, 0), 9600, "PIN_POISON.png");
            data.PoisonDrum = OBJECT_GEN->CreateSprite("PIN_POISONDRUM.png",
                                                       glm::f32vec3(data.Poison1->GetPosition().x - 0.2f, data.Poison1->GetPosition().y + 0.2f, 0),
                                                       glm::vec3(350, 250, 0), 9602);
        }
    }

    void RandomInitBoss(Game_Random_Data& data)
    {
        data.Boss = OBJECT_GEN->CreateBoss(SetObjectPos(120, data), 10002, Z_NORMAL);
    }

    void RandomGatePass(Game_Random_Data& data)
    {
        if (data.Room_Number == data.EventNumbers[0])
        {
            data.Item_Zombie = OBJECT_GEN->CreateZombie(SetObjectPos(120, data), 11000, Z_ITEMDROP);
            /*glm::vec4 red(1.0f, 0.0f, 0.0f, 1.0f);
            data.Item_Zombie->set_Color(red);*/
            data.Player->isGetPass = false;
        }
        else
        {
            data.Player->isGetPass = true;
        }
    }

    void RandomGatePass2(Game_Random_Data& data)
    {
        if (data.Room_Number == data.EventNumbers[0] || data.Room_Number == data.EventNumbers[3])
        {
            data.Item_Zombie = OBJECT_GEN->CreateZombie(SetObjectPos(120, data), 11000, Z_ITEMDROP);
            /*glm::vec4 red(1.0f, 0.0f, 0.0f, 1.0f);
            data.Item_Zombie->set_Color(red);*/
            data.Player->isGetPass = false;
        }
        else
        {
            data.Player->isGetPass = true;
        }
    }

    void RandomLoadLastHint(Game_Random_Data& data)
    {
        /*data.Player->gathered_password.clear();
        for (auto i : data.player_hint_1)
        {
            data.Player->gathered_password.push_back(i);
        }*/
    }

    void RandomSaveLastHint(Game_Random_Data& data)
    {
        if (data.currLevel == 1)
        {
            for (auto i : data.Player->gathered_password)
            {
                data.player_hint_1.push_back(i);
            }
            data.Player->gathered_password.clear();
        }
        else if (data.currLevel == 2)
        {
            for (auto i : data.Player->gathered_password)
            {
                data.player_hint_2.push_back(i);
            }
            data.Player->gathered_password.clear();
        }
    }

    void RandomInitHint(Game_Random_Data& data)
    {
        if (data.currLevel == 1)
        {
            for (unsigned i = 0; i < data.player_hint_1.size(); ++i)
            {
                if (data.IsGetHint[i])
                {
                    OBJECT_GEN->CreateHud(glm::vec3(50.0f + 50.f * i, HEIGHT_TEMP, 0), glm::vec3(50.f, 50.f, 0.f),
                                          3052, "PIN_NUM" + std::to_string(GAMELOGIC->WhatIsSecretNumber(i) - 48) + ".png");
                }
            }
        }
        else if (data.currLevel == 2)
        {
            for (unsigned i = 0; i < data.player_hint_2.size(); ++i)
            {
                if (data.IsGetHint[i])
                {
                    OBJECT_GEN->CreateHud(glm::vec3(50.0f + 50.f * i, HEIGHT_TEMP, 0), glm::vec3(50.f, 50.f, 0.f),
                                          3052, "PIN_NUM" + std::to_string(GAMELOGIC->WhatIsSecretNumber(i) - 48) + ".png");
                }
            }
        }
    }

    void RandomInitAmmo(Game_Random_Data& data)
    {
        if (data.Room_Number == 1)
        {
            /*data.ammo1 = OBJECT_GEN->CreateSprite("PIN_AMMO.png", SetObjectPos(50, data), glm::vec3(150, 150, 0), 11000);
            data.ammo2 = OBJECT_GEN->CreateSprite("PIN_AMMO.png", SetObjectPos(50, data), glm::vec3(150, 150, 0), 11001);
            data.ammo3 = OBJECT_GEN->CreateSprite("PIN_AMMO.png", SetObjectPos(50, data), glm::vec3(150, 150, 0), 11001);
            data.ammo4 = OBJECT_GEN->CreateSprite("PIN_AMMO.png", SetObjectPos(50, data), glm::vec3(150, 150, 0), 11001);*/
        }
    }

    void RandomEventNumbersLevel1(Game_Random_Data& data)
    {
        /*
			eventlist:
			1. gatepass 2.poison 3. poison 4. password
		*/
        data.EventNumbers.clear();
        int stacknumber = RandomIntNumber(3, 5);
        data.EventNumbers.push_back(stacknumber);
        stacknumber += RandomIntNumber(2, 5);
        data.EventNumbers.push_back(stacknumber);
        stacknumber += RandomIntNumber(2, 5);
        data.EventNumbers.push_back(stacknumber);
        stacknumber += RandomIntNumber(2, 3);
        data.EventNumbers.push_back(stacknumber);
    }

    void RandomEventNumbersLevel2(Game_Random_Data& data)
    {
        /*
		eventlist:
		0. gatepass 1. poison 2. poison 3. gatepass 4. poison 5. boss 6. password
		*/
        data.EventNumbers.clear();
        int stacknumber = RandomIntNumber(2, 4);
        data.EventNumbers.push_back(stacknumber);
        stacknumber += RandomIntNumber(2, 4);
        data.EventNumbers.push_back(stacknumber);
        stacknumber += RandomIntNumber(2, 4);
        data.EventNumbers.push_back(stacknumber);
        stacknumber += RandomIntNumber(2, 4);
        data.EventNumbers.push_back(stacknumber);
        stacknumber += RandomIntNumber(2, 4);
        data.EventNumbers.push_back(stacknumber);
        stacknumber += RandomIntNumber(3, 5);
        data.EventNumbers.push_back(stacknumber);
		stacknumber += 1;
		data.EventNumbers.push_back(stacknumber);
    }

    void BeforeWall(Game_Random_Data& data)
    {
        data.Walls.UWall_Count = JSONREADER->getUWallCount();
        data.Walls.DWall_Count = JSONREADER->getDWallCount();
        data.Walls.LWall_Count = JSONREADER->getLWallCount();
        data.Walls.RWall_Count = JSONREADER->getRWallCount();
        data.Walls.UWall.clear();
        data.Walls.DWall.clear();
        data.Walls.LWall.clear();
        data.Walls.RWall.clear();
        for (unsigned int i = 0; i < data.Walls.UWall_Count; ++i)
        {
            std::string num = std::to_string(i);
            data.Walls.UWall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getUWallPos(i), JSONREADER->getUWallScale(i) + glm::vec3(400, 0, 0), WallId + i, "Wall" + num, "PIN_UWALL.png"));
        }
        for (unsigned int i = 0; i < data.Walls.DWall_Count; ++i)
        {
            std::string num = std::to_string(i);
            data.Walls.DWall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getDWallPos(i), JSONREADER->getDWallScale(i) + glm::vec3(400, 0, 0), WallId + i, "Wall" + num, "PIN_DWALL.png"));
        }
        for (unsigned int i = 0; i < data.Walls.LWall_Count; ++i)
        {
            std::string num = std::to_string(i);
            data.Walls.LWall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getLWallPos(i), JSONREADER->getLWallScale(i) + glm::vec3(0, 400, 0), WallId + i, "Wall" + num, "PIN_LWALL.png"));
        }
        for (unsigned int i = 0; i < data.Walls.RWall_Count; ++i)
        {
            std::string num = std::to_string(i);
            data.Walls.RWall.push_back(OBJECT_GEN->CreateWall(JSONREADER->getRWallPos(i), JSONREADER->getRWallScale(i) + glm::vec3(0, 400, 0), WallId + i, "Wall" + num, "PIN_RWALL.png"));
        }
    }

    void BeforeDoor(Game_Random_Data& data)
    {
        data.Door_Count = JSONREADER->getDoorCount();
        data.Door.clear();
        for (unsigned int i = 0; i < data.Door_Count; ++i)
        {
            if (JSONREADER->getDoorScale(i).x >= 300)
            {
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_UDOOR.png", JSONREADER->getDoorPos(i), JSONREADER->getDoorScale(i), OT_RANDOMDOOR, ST_RECTANGLE, JSONREADER->GetDoorID(i)));
            }
            else
            {
                data.Door.push_back(OBJECT_GEN->CreateObject("PIN_UDOOR.png", JSONREADER->getDoorPos(i), JSONREADER->getDoorScale(i), OT_RANDOMDOOR, ST_RECTANGLE, JSONREADER->GetDoorID(i), glm::radians(90.f)));
            }
        }
    }

    void BeforeZombie(Game_Random_Data& data)
    {
        data.Zombie_Count = JSONREADER->getZombieCount();
        data.Zombie.clear();
        for (unsigned int i = 0; i < data.Zombie_Count; ++i)
        {
            data.Zombie.push_back(OBJECT_GEN->CreateZombie(JSONREADER->getZombiePos(i), ZombieId + i, Z_NORMAL));
        }
    }

    void BeforePistol(Game_Random_Data& data)
    {

    }

    void BeforePlayer(Game_Random_Data& data)
    {
        data.Player = OBJECT_GEN->CreatePlayer(JSONREADER->getPlayerPos(), PlayerId);
        data.Player->curr_ammo = data.curr_ammo_;
        data.Player->curr_grenade = data.curr_grenade;
        data.Player->is_get_pistol = data.Is_Get_Pistol;
        data.Player->curr_Health = data.PlayerHealth;
    }

    void SavePlayerStatus(Game_Random_Data& data)
    {
        data.curr_ammo_ = data.Player->curr_ammo;
        data.curr_grenade = data.Player->curr_grenade;
        data.PlayerHealth = data.Player->curr_Health;
        data.Is_Get_Pistol = data.Player->is_get_pistol;
    }

    void LoadPlayerStatus(Game_Random_Data& data)
    {
        data.Player->curr_ammo = data.curr_ammo_;
        data.Player->curr_grenade = data.curr_grenade;
        data.Player->curr_Health = data.PlayerHealth;
        data.Player->is_get_pistol = data.Is_Get_Pistol;
    }

    void SetRoomStyle(Game_Random_Data& data)
    {
        data.Room_Style = RoomStyle(RandomIntNumber(0, room_style_number));
        std::string roomname = ToString(data.Room_Style);
    }

    void CheatCode(Game_Random_Data& data)
    {
        if (Input::GetInstance().IsPressed(SDL_SCANCODE_LCTRL) && Input::GetInstance().IsTriggered(SDL_SCANCODE_1))
			PlayerController::player_health += 300;

        if (Input::GetInstance().IsPressed(SDL_SCANCODE_LCTRL) && Input::GetInstance().IsTriggered(SDL_SCANCODE_2))
            PlayerController::is_ammo_cheat_on = true;

        if (Input::GetInstance().IsPressed(SDL_SCANCODE_LCTRL) && Input::GetInstance().IsTriggered(SDL_SCANCODE_3))
        {
            data.Room_Number--;
            GAME_STATE->Restart();
        }
        if (Input::GetInstance().IsPressed(SDL_SCANCODE_LCTRL) && Input::GetInstance().IsTriggered(SDL_SCANCODE_4))
        {
            data.Room_Number++;
            GAME_STATE->Restart();
        }
        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_F4))
            GAME_STATE->SetNextState(SL_RANDOMLEVEL);

        if (Input::GetInstance().IsTriggered(SDL_SCANCODE_F5))
            GAME_STATE->SetNextState(SL_RANDOMLEVEL3);
    }

    glm::vec3 SetObjectPos(float size, Game_Random_Data& data)
    {
        glm::vec3 random_position = glm::vec3(0.f, 0.f, -0.1f);
        // 1 size = 0.0013 pos
        float pos_size = 0.00065f * size;
       
        switch (data.Room_Style)
        {
            case RoomStyle::O_ONEBYONE:
            {
                random_position.x = RandomFloatNumber(-1.6f + pos_size, 1.6f - pos_size);
                random_position.y = RandomFloatNumber(-1.6f + pos_size, 1.6f - pos_size);

                while ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                       (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                {
                    random_position.x = RandomFloatNumber(-1.6f + pos_size, 1.6f - pos_size);
                    random_position.y = RandomFloatNumber(-1.6f + pos_size, 1.6f - pos_size);
                }
                break;
            }
            case RoomStyle::O_TWOBYTWO:
            {
                random_position.x = RandomFloatNumber(-3.3f + pos_size, 3.3f - pos_size);
                random_position.y = RandomFloatNumber(-3.8f + pos_size, 3.8f - pos_size);

                while ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                       (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                {
                    random_position.x = RandomFloatNumber(-3.3f + pos_size, 3.3f - pos_size);
                    random_position.y = RandomFloatNumber(-3.8f + pos_size, 3.8f - pos_size);
                }
                break;
            }
            case RoomStyle::O_HOLE:
            {
                random_position.x = RandomFloatNumber(-3.3f + pos_size, 3.3f - pos_size);
                random_position.y = RandomFloatNumber(-3.8f + pos_size, 3.8f - pos_size);

                while ((random_position.x > -1.5f - pos_size && random_position.x < 1.5f + pos_size) &&
                       (random_position.y > -1.5f - pos_size && random_position.y < 1.5f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-3.3f + pos_size, 3.3f - pos_size);
                    random_position.y = RandomFloatNumber(-3.8f + pos_size, 3.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::H_ONE:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.3f + pos_size, 1.3f - pos_size);

                while ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                       (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.3f + pos_size, 1.3f - pos_size);
                }
                break;
            }
            case RoomStyle::H_TWO:
            {
                random_position.x = RandomFloatNumber(-4.5f + pos_size, 4.5f - pos_size);
                random_position.y = RandomFloatNumber(-1.3f + pos_size, 1.3f - pos_size);

                while ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                       (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                {
                    random_position.x = RandomFloatNumber(-4.5f + pos_size, 4.5f - pos_size);
                    random_position.y = RandomFloatNumber(-1.3f + pos_size, 1.3f - pos_size);
                }
                break;
            }
            case RoomStyle::V_ONE:
            {
                random_position.x = RandomFloatNumber(-1.3f + pos_size, 1.3f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                       (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                {
                    random_position.x = RandomFloatNumber(-1.3f + pos_size, 1.3f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                }
                break;
            }
            case RoomStyle::V_TWO:
            {
                random_position.x = RandomFloatNumber(-1.3f + pos_size, 1.3f - pos_size);
                random_position.y = RandomFloatNumber(-4.5f + pos_size, 4.5f - pos_size);

                while ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                       (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                {
                    random_position.x = RandomFloatNumber(-1.3f + pos_size, 1.3f - pos_size);
                    random_position.y = RandomFloatNumber(-4.5f + pos_size, 4.5f - pos_size);
                }
                break;
            }
            case RoomStyle::L_THREE_1:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > 0.f - pos_size && random_position.x < 2.f + pos_size) &&
                       (random_position.y > 0.f - pos_size && random_position.y < 2.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::L_THREE_2:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -2.f - pos_size && random_position.x < 0.f + pos_size) &&
                       (random_position.y > 0.f - pos_size && random_position.y < 2.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::L_THREE_3:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -2.f - pos_size && random_position.x < 0.f + pos_size) &&
                       (random_position.y > -2.f - pos_size && random_position.y < 0.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::L_THREE_4:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > 0.f - pos_size && random_position.x < 2.f + pos_size) &&
                       (random_position.y > -2.f - pos_size && random_position.y < 0.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::L_FOUR_1:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((random_position.x > 0.f - pos_size && random_position.x < 2.f + pos_size) &&
                       (random_position.y > -1.f - pos_size && random_position.y < 3.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::L_FOUR_2:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -1.f - pos_size && random_position.x < 3.f + pos_size) &&
                       (random_position.y > 0.f - pos_size && random_position.y < 2.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::L_FOUR_3:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((random_position.x > -2.f - pos_size && random_position.x < 0.f + pos_size) &&
                       (random_position.y > -1.f - pos_size && random_position.y < 3.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::L_FOUR_4:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -3.f - pos_size && random_position.x < 1.f + pos_size) &&
                       (random_position.y > 0.f - pos_size && random_position.y < 2.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::L_FOUR_5:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((random_position.x > -2.f - pos_size && random_position.x < 0.f + pos_size) &&
                       (random_position.y > -3.f - pos_size && random_position.y < 1.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::L_FOUR_6:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -3.f - pos_size && random_position.x < 1.f + pos_size) &&
                       (random_position.y > -2.f - pos_size && random_position.y < 0.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::L_FOUR_7:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((random_position.x > 0.f - pos_size && random_position.x < 2.f + pos_size) &&
                       (random_position.y > -1.f - pos_size && random_position.y < 3.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::L_FOUR_8:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -1.f - pos_size && random_position.x < 3.f + pos_size) &&
                       (random_position.y > -2.f - pos_size && random_position.y < 0.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::L_FIVE:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((random_position.x > -1.f - pos_size && random_position.x < 3.f + pos_size) &&
                       (random_position.y > -1.f - pos_size && random_position.y < 3.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::N_V:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while (((random_position.x > -2.f - pos_size && random_position.x < 0.f + pos_size) &&
                        (random_position.y > 1.f - pos_size && random_position.y < 3.f + pos_size)) ||
                       ((random_position.x > 0.f - pos_size && random_position.x < 2.f + pos_size) &&
                        (random_position.y > -3.f - pos_size && random_position.y < -1.f + pos_size)))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::N_H:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while (((random_position.x > -3.f - pos_size && random_position.x < -1.f + pos_size) &&
                        (random_position.y > 0.f - pos_size && random_position.y < 2.f + pos_size)) ||
                       ((random_position.x > 1.f - pos_size && random_position.x < 3.f + pos_size) &&
                        (random_position.y > -2.f - pos_size && random_position.y < 0.f + pos_size)))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::T_UP:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while (((random_position.x > -3.f - pos_size && random_position.x < -1.f + pos_size) &&
                        (random_position.y > -3.f - pos_size && random_position.y < 1.f + pos_size)) ||
                       ((random_position.x > 1.f - pos_size && random_position.x < 3.f + pos_size) &&
                        (random_position.y > -3.f - pos_size && random_position.y < 1.f + pos_size)))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::T_DOWN:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while (((random_position.x > -3.f - pos_size && random_position.x < -1.f + pos_size) &&
                        (random_position.y > -1.f - pos_size && random_position.y < 3.f + pos_size)) ||
                       ((random_position.x > 1.f - pos_size && random_position.x < 3.f + pos_size) &&
                        (random_position.y > -1.f - pos_size && random_position.y < 3.f + pos_size)))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::T_RIGHT:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while (((random_position.x > -3.f - pos_size && random_position.x < 1.f + pos_size) &&
                        (random_position.y > 1.f - pos_size && random_position.y < 3.f + pos_size)) ||
                       ((random_position.x > -3.f - pos_size && random_position.x < 1.f + pos_size) &&
                        (random_position.y > -3.f - pos_size && random_position.y < -1.f + pos_size)))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::T_LEFT:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while (((random_position.x > -1.f - pos_size && random_position.x < 3.f + pos_size) &&
                        (random_position.y > 1.f - pos_size && random_position.y < 3.f + pos_size)) ||
                       ((random_position.x > -1.f - pos_size && random_position.x < 3.f + pos_size) &&
                        (random_position.y > -3.f - pos_size && random_position.y < -1.f + pos_size)))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::X_UNIQUE:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while (((random_position.x > -3.f - pos_size && random_position.x < -1.f + pos_size) &&
                        (random_position.y > -3.f - pos_size && random_position.y < -1.f + pos_size)) ||
                       ((random_position.x > -3.f - pos_size && random_position.x < -1.f + pos_size) &&
                        (random_position.y > 1.f - pos_size && random_position.y < 3.f + pos_size)) ||
                       ((random_position.x > 1.f - pos_size && random_position.x < 3.f + pos_size) &&
                        (random_position.y > -3.f - pos_size && random_position.y < -1.f + pos_size)) ||
                       ((random_position.x > 1.f - pos_size && random_position.x < 3.f + pos_size) &&
                        (random_position.y > 1.f - pos_size && random_position.y < 3.f + pos_size)))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::U_UP:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -1.f - pos_size && random_position.x < 1.f + pos_size) &&
                       (random_position.y > -2.f - pos_size && random_position.y < 0.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::U_DOWN:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -1.f - pos_size && random_position.x < 1.f + pos_size) &&
                       (random_position.y > 0.f - pos_size && random_position.y < 2.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::U_RIGHT:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((random_position.x > -2.f - pos_size && random_position.x < 0.f + pos_size) &&
                       (random_position.y > -1.f - pos_size && random_position.y < 1.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            case RoomStyle::U_LEFT:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((random_position.x > 0.f - pos_size && random_position.x < 2.f + pos_size) &&
                       (random_position.y > -1.f - pos_size && random_position.y < 1.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    if ((data.Player->GetPosition().x - 0.4f < random_position.x && data.Player->GetPosition().x + 0.4f > random_position.x) &&
                        (data.Player->GetPosition().y - 0.4f < random_position.y && data.Player->GetPosition().y + 0.4f > random_position.y))
                    {
                        continue;
                    }
                }
                break;
            }
            default:
                break;
        }
        return random_position;
    }

    glm::vec3 SetObjectPosWithoutPlayer(float size, Game_Random_Data& data)
    {
        glm::vec3 random_position = glm::vec3(0.f, 0.f, -0.1f);
        // 1 size = 0.0013 pos
        float pos_size = 0.00065f * size;

        switch (data.Room_Style)
        {
            case RoomStyle::O_ONEBYONE:
            {
                random_position.x = RandomFloatNumber(-1.6f + pos_size, 1.6f - pos_size);
                random_position.y = RandomFloatNumber(-1.6f + pos_size, 1.6f - pos_size);

                break;
            }
            case RoomStyle::O_TWOBYTWO:
            {
                random_position.x = RandomFloatNumber(-3.3f + pos_size, 3.3f - pos_size);
                random_position.y = RandomFloatNumber(-3.8f + pos_size, 3.8f - pos_size);

                break;
            }
            case RoomStyle::O_HOLE:
            {
                random_position.x = RandomFloatNumber(-3.3f + pos_size, 3.3f - pos_size);
                random_position.y = RandomFloatNumber(-3.8f + pos_size, 3.8f - pos_size);

                while ((random_position.x > -1.5f - pos_size && random_position.x < 1.5f + pos_size) &&
                       (random_position.y > -1.5f - pos_size && random_position.y < 1.5f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-3.3f + pos_size, 3.3f - pos_size);
                    random_position.y = RandomFloatNumber(-3.8f + pos_size, 3.8f - pos_size);
                }
                break;
            }
            case RoomStyle::H_ONE:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.3f + pos_size, 1.3f - pos_size);

                break;
            }
            case RoomStyle::H_TWO:
            {
                random_position.x = RandomFloatNumber(-4.5f + pos_size, 4.5f - pos_size);
                random_position.y = RandomFloatNumber(-1.3f + pos_size, 1.3f - pos_size);

                break;
            }
            case RoomStyle::V_ONE:
            {
                random_position.x = RandomFloatNumber(-1.3f + pos_size, 1.3f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                break;
            }
            case RoomStyle::V_TWO:
            {
                random_position.x = RandomFloatNumber(-1.3f + pos_size, 1.3f - pos_size);
                random_position.y = RandomFloatNumber(-4.5f + pos_size, 4.5f - pos_size);

                break;
            }
            case RoomStyle::L_THREE_1:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > 0.f - pos_size && random_position.x < 2.f + pos_size) &&
                       (random_position.y > 0.f - pos_size && random_position.y < 2.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                }
                break;
            }
            case RoomStyle::L_THREE_2:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -2.f - pos_size && random_position.x < 0.f + pos_size) &&
                       (random_position.y > 0.f - pos_size && random_position.y < 2.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                }
                break;
            }
            case RoomStyle::L_THREE_3:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -2.f - pos_size && random_position.x < 0.f + pos_size) &&
                       (random_position.y > -2.f - pos_size && random_position.y < 0.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                }
                break;
            }
            case RoomStyle::L_THREE_4:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > 0.f - pos_size && random_position.x < 2.f + pos_size) &&
                       (random_position.y > -2.f - pos_size && random_position.y < 0.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                }
                break;
            }
            case RoomStyle::L_FOUR_1:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((random_position.x > 0.f - pos_size && random_position.x < 2.f + pos_size) &&
                       (random_position.y > -1.f - pos_size && random_position.y < 3.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                }
                break;
            }
            case RoomStyle::L_FOUR_2:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -1.f - pos_size && random_position.x < 3.f + pos_size) &&
                       (random_position.y > 0.f - pos_size && random_position.y < 2.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                }
                break;
            }
            case RoomStyle::L_FOUR_3:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((random_position.x > -2.f - pos_size && random_position.x < 0.f + pos_size) &&
                       (random_position.y > -1.f - pos_size && random_position.y < 3.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                }
                break;
            }
            case RoomStyle::L_FOUR_4:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -3.f - pos_size && random_position.x < 1.f + pos_size) &&
                       (random_position.y > 0.f - pos_size && random_position.y < 2.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                }
                break;
            }
            case RoomStyle::L_FOUR_5:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((random_position.x > -2.f - pos_size && random_position.x < 0.f + pos_size) &&
                       (random_position.y > -3.f - pos_size && random_position.y < 1.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                }
                break;
            }
            case RoomStyle::L_FOUR_6:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -3.f - pos_size && random_position.x < 1.f + pos_size) &&
                       (random_position.y > -2.f - pos_size && random_position.y < 0.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                }
                break;
            }
            case RoomStyle::L_FOUR_7:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((random_position.x > 0.f - pos_size && random_position.x < 2.f + pos_size) &&
                       (random_position.y > -1.f - pos_size && random_position.y < 3.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                }
                break;
            }
            case RoomStyle::L_FOUR_8:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -1.f - pos_size && random_position.x < 3.f + pos_size) &&
                       (random_position.y > -2.f - pos_size && random_position.y < 0.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                }
                break;
            }
            case RoomStyle::L_FIVE:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((random_position.x > -1.f - pos_size && random_position.x < 3.f + pos_size) &&
                       (random_position.y > -1.f - pos_size && random_position.y < 3.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                }
                break;
            }
            case RoomStyle::N_V:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while (((random_position.x > -2.f - pos_size && random_position.x < 0.f + pos_size) &&
                        (random_position.y > 1.f - pos_size && random_position.y < 3.f + pos_size)) ||
                       ((random_position.x > 0.f - pos_size && random_position.x < 2.f + pos_size) &&
                        (random_position.y > -3.f - pos_size && random_position.y < -1.f + pos_size)))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                }
                break;
            }
            case RoomStyle::N_H:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while (((random_position.x > -3.f - pos_size && random_position.x < -1.f + pos_size) &&
                        (random_position.y > 0.f - pos_size && random_position.y < 2.f + pos_size)) ||
                       ((random_position.x > 1.f - pos_size && random_position.x < 3.f + pos_size) &&
                        (random_position.y > -2.f - pos_size && random_position.y < 0.f + pos_size)))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                }
                break;
            }
            case RoomStyle::T_UP:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while (((random_position.x > -3.f - pos_size && random_position.x < -1.f + pos_size) &&
                        (random_position.y > -3.f - pos_size && random_position.y < 1.f + pos_size)) ||
                       ((random_position.x > 1.f - pos_size && random_position.x < 3.f + pos_size) &&
                        (random_position.y > -3.f - pos_size && random_position.y < 1.f + pos_size)))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                }
                break;
            }
            case RoomStyle::T_DOWN:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while (((random_position.x > -3.f - pos_size && random_position.x < -1.f + pos_size) &&
                        (random_position.y > -1.f - pos_size && random_position.y < 3.f + pos_size)) ||
                       ((random_position.x > 1.f - pos_size && random_position.x < 3.f + pos_size) &&
                        (random_position.y > -1.f - pos_size && random_position.y < 3.f + pos_size)))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                }
                break;
            }
            case RoomStyle::T_RIGHT:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while (((random_position.x > -3.f - pos_size && random_position.x < 1.f + pos_size) &&
                        (random_position.y > 1.f - pos_size && random_position.y < 3.f + pos_size)) ||
                       ((random_position.x > -3.f - pos_size && random_position.x < 1.f + pos_size) &&
                        (random_position.y > -3.f - pos_size && random_position.y < -1.f + pos_size)))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                }
                break;
            }
            case RoomStyle::T_LEFT:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while (((random_position.x > -1.f - pos_size && random_position.x < 3.f + pos_size) &&
                        (random_position.y > 1.f - pos_size && random_position.y < 3.f + pos_size)) ||
                       ((random_position.x > -1.f - pos_size && random_position.x < 3.f + pos_size) &&
                        (random_position.y > -3.f - pos_size && random_position.y < -1.f + pos_size)))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                }
                break;
            }
            case RoomStyle::X_UNIQUE:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while (((random_position.x > -3.f - pos_size && random_position.x < -1.f + pos_size) &&
                        (random_position.y > -3.f - pos_size && random_position.y < -1.f + pos_size)) ||
                       ((random_position.x > -3.f - pos_size && random_position.x < -1.f + pos_size) &&
                        (random_position.y > 1.f - pos_size && random_position.y < 3.f + pos_size)) ||
                       ((random_position.x > 1.f - pos_size && random_position.x < 3.f + pos_size) &&
                        (random_position.y > -3.f - pos_size && random_position.y < -1.f + pos_size)) ||
                       ((random_position.x > 1.f - pos_size && random_position.x < 3.f + pos_size) &&
                        (random_position.y > 1.f - pos_size && random_position.y < 3.f + pos_size)))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                }
                break;
            }
            case RoomStyle::U_UP:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -1.f - pos_size && random_position.x < 1.f + pos_size) &&
                       (random_position.y > -2.f - pos_size && random_position.y < 0.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                }
                break;
            }
            case RoomStyle::U_DOWN:
            {
                random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);

                while ((random_position.x > -1.f - pos_size && random_position.x < 1.f + pos_size) &&
                       (random_position.y > 0.f - pos_size && random_position.y < 2.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                    random_position.y = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                }
                break;
            }
            case RoomStyle::U_RIGHT:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((random_position.x > -2.f - pos_size && random_position.x < 0.f + pos_size) &&
                       (random_position.y > -1.f - pos_size && random_position.y < 1.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                }
                break;
            }
            case RoomStyle::U_LEFT:
            {
                random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);

                while ((random_position.x > 0.f - pos_size && random_position.x < 2.f + pos_size) &&
                       (random_position.y > -1.f - pos_size && random_position.y < 1.f + pos_size))
                {
                    random_position.x = RandomFloatNumber(-1.8f + pos_size, 1.8f - pos_size);
                    random_position.y = RandomFloatNumber(-2.8f + pos_size, 2.8f - pos_size);
                }
                break;
            }
            default:
                break;
        }
        return random_position;
    }

    int RandomIntNumber(int min_num, int max_num)
    {
        if (min_num >= max_num)
        {
            return min_num;
        }
        else
        {
            return (rand() % (max_num - min_num)) + min_num;
        }
    }


    bool RandomChanceBool(int chance)
    {
        int number = RandomIntNumber(0, 100);
        if (number <= chance)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    float RandomFloatNumber(float min_num, float max_num)
    {
        if (min_num >= max_num)
        {
            return min_num;
        }
        else
        {
            return min_num + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_num - min_num)));
        }
    }

    void get_rand_item_box_count()
    {
        return;
    }
}
