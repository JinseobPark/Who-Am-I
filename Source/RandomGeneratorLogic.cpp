/**
\file        RandomGeneratorLogic.cpp
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM250
\date        06/14/2018
\brief       Random Generator logic.
All content (c) 2018 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Collision.h"
#include "GameStateManager.h"
#include "JsonWriter.h"
#include "Object.h"
#include "RandomGenerator.h"
#include "RandomGeneratorLogic.h"
#ifdef _WIN32
#include "..\include\SoundManager.h"
#else
#include "SoundManager.h"
#endif
#include "input.h"

#ifdef _WIN32
#include "..\Include\ObjectGenerator.h"
#include <SDL.h>
#else
#include "ObjectGenerator.h"
#include <SDL2/SDL.h>
#endif

using namespace std;
namespace FindersEngine
{
    bool CirRectCollisionCheck(Object* pA, Object* pB, Game_Random_Data& data)
    {
        glm::vec3 a_rect_pos = pA->GetPosition();
        glm::vec3 b_circle_pos = pB->GetPosition();

        a_rect_pos.x *= 840.f;
        a_rect_pos.y *= 840.f;
        b_circle_pos.x *= 840.f;
        b_circle_pos.y *= 840.f;

        glm::vec3 a_rect_size = pA->GetScale();
        glm::vec3 b_radius = pB->GetScale() * 0.5f;


        glm::vec3 a_distance = glm::vec3(0.f, 0.f, 0.f);

        a_distance.x = (glm::abs(b_circle_pos.x - a_rect_pos.x));
        a_distance.y = (glm::abs(b_circle_pos.y - a_rect_pos.y));


        if (a_distance.x > (a_rect_size.x * .5f) + (b_radius.x))
            return false;
        if (a_distance.y > (a_rect_size.y * .5f) + (b_radius.y))
            return false;

        if (a_distance.x <= (a_rect_size.x * .5f))
        {
            if (a_distance.x <= a_distance.y)
            {
                if (a_rect_pos.y >= b_circle_pos.y)
                {
                    data.Current_Door = CURRENT_UP;
                }
                else
                {
                    data.Current_Door = CURRENT_DOWN;
                }
            }
            else
            {
                if (a_rect_pos.x >= b_circle_pos.x)
                {
                    data.Current_Door = CURRENT_RIGHT;
                }
                else
                {
                    data.Current_Door = CURRENT_LEFT;
                }
            }
            return true;
        }
        if (a_distance.y <= (a_rect_size.y * .5f))
        {
            if (a_distance.x <= a_distance.y)
            {
                if (a_rect_pos.y >= b_circle_pos.y)
                {
                    data.Current_Door = CURRENT_UP;
                }
                else
                {
                    data.Current_Door = CURRENT_DOWN;
                }
            }
            else
            {
                if (a_rect_pos.x >= b_circle_pos.x)
                {
                    data.Current_Door = CURRENT_RIGHT;
                }
                else
                {
                    data.Current_Door = CURRENT_LEFT;
                }
            }
            return true;
        }

        return false;
    }
    void OpenTheDoor(Game_Random_Data& data)
    {
		if (Input::GetInstance().IsTriggered(SDL_SCANCODE_F) || Input::GetInstance().IsGamePadTriggered(SDL_CONTROLLER_BUTTON_X))
		{
			for (unsigned int i = 0; i < data.Door_Count; ++i)
			{
				if (CirRectCollisionCheck(data.Door[i], data.Player, data))
				{
					if (data.Room_Number % 2)
					{
						if (!data.IsGetHint[data.Room_Number / 2] && data.Room_Number < 8)
						{
							SOUNDMANAGER->play("FINDHINT.mp3");
							return;
						}
					}
				}
			}
			if (data.Player->isGetPass == true)
			{
				if (data.currLevel == 1)
				{
					if (data.Room_Number == data.EventNumbers[3] && data.currLevel == 1)
					{
						data.Player->is_in_Final = true;
					}
					else
					{
						data.Player->is_in_Final = false;
						for (unsigned int i = 0; i < data.Door_Count; ++i)
						{
							if (CirRectCollisionCheck(data.Door[i], data.Player, data))
							{
								SetIsLastDoor(data);
								switch (data.Door_Stat)
								{
								case (RG_NEXT):
								{
									data.Last_Door = LastDoor(data.Current_Door);
									data.Room_Number++;
									data.Current_Door = CURRENT_NONE;
									GAME_STATE->Restart();
									break;
								}
								case (RG_BEFORE):
								{
									break;
								}
								case (RG_CURRENT):
								{
									break;
								}
								default:
								{
									break;
								}
								}
							}
						}
					}
				}
				else if (data.currLevel == 2)
				{
					if (data.Room_Number == data.EventNumbers[5] && data.Player->is_in_Final == false)
					{
						data.Player->is_in_Final = true;
					}
					else
					{
						data.Player->is_in_Final = false;
						for (unsigned int i = 0; i < data.Door_Count; ++i)
						{
							if (CirRectCollisionCheck(data.Door[i], data.Player, data))
							{
								SetIsLastDoor(data);
								switch (data.Door_Stat)
								{
								case (RG_NEXT):
								{
									data.Last_Door = LastDoor(data.Current_Door);
									data.Room_Number++;
									data.Current_Door = CURRENT_NONE;
									GAME_STATE->Restart();
									break;
								}
								case (RG_BEFORE):
								{
									break;
								}
								case (RG_CURRENT):
								{
									break;
								}
								default:
								{
									break;
								}
								}
							}
						}
					}
				}
			}

			else
			{
				SOUNDMANAGER->play("LOCKED_DOOR_SOUND.wav");
			}
		}
    }

    LastDoor PickOneDoor(LastDoor first, LastDoor second, LastDoor third)
    {
        int Choose = RandomIntNumber(1, 4);
        switch (Choose)
        {
            case (1):
            {
                return first;
                break;
            }
            case (2):
            {
                return second;
                break;
            }
            case (3):
            {
                return third;
                break;
            }
            default:
                break;
        }
        return first;
    }

    void JudgeMakeDoor(Game_Random_Data& data)
    {
        int Choose = RandomIntNumber(1, 4);

        switch (Choose)
        {
            case (1):
            {
                data.IsDoorWay = {false, false, false, false};
                switch (data.Last_Door)
                {
                    case (LAST_UP):
                    {
                        data.IsDoorWay.DownDoor = true;
                        switch (PickOneDoor(LAST_DOWN, LAST_LEFT, LAST_RIGHT))
                        {
                            case (LAST_DOWN):
                            {
                                data.IsDoorWay.UpDoor = true;
                                break;
                            }
                            case (LAST_LEFT):
                            {
                                data.IsDoorWay.RightDoor = true;
                                break;
                            }
                            case (LAST_RIGHT):
                            {
                                data.IsDoorWay.LeftDoor = true;
                                break;
                            }
                            default:
                                break;
                        }
                        break;
                    }
                    case (LAST_DOWN):
                    {
                        data.IsDoorWay.UpDoor = true;
                        switch (PickOneDoor(LAST_UP, LAST_LEFT, LAST_RIGHT))
                        {
                            case (LAST_UP):
                            {
                                data.IsDoorWay.DownDoor = true;
                                break;
                            }
                            case (LAST_LEFT):
                            {
                                data.IsDoorWay.RightDoor = true;
                                break;
                            }
                            case (LAST_RIGHT):
                            {
                                data.IsDoorWay.LeftDoor = true;
                                break;
                            }
                            default:
                                break;
                        }
                        break;
                    }
                    case (LAST_LEFT):
                    {
                        data.IsDoorWay.RightDoor = true;
                        switch (PickOneDoor(LAST_UP, LAST_DOWN, LAST_RIGHT))
                        {
                            case (LAST_UP):
                            {
                                data.IsDoorWay.DownDoor = true;
                                break;
                            }
                            case (LAST_DOWN):
                            {
                                data.IsDoorWay.UpDoor = true;
                                break;
                            }
                            case (LAST_RIGHT):
                            {
                                data.IsDoorWay.LeftDoor = true;
                                break;
                            }
                            default:
                                break;
                        }
                        break;
                    }
                    case (LAST_RIGHT):
                    {
                        data.IsDoorWay.LeftDoor = true;
                        switch (PickOneDoor(LAST_UP, LAST_DOWN, LAST_LEFT))
                        {
                            case (LAST_UP):
                            {
                                data.IsDoorWay.DownDoor = true;
                                break;
                            }
                            case (LAST_DOWN):
                            {
                                data.IsDoorWay.UpDoor = true;
                                break;
                            }
                            case (LAST_LEFT):
                            {
                                data.IsDoorWay.RightDoor = true;
                                break;
                            }
                            default:
                                break;
                        }
                        break;
                    }
                    default:
                    {
                        data.IsDoorWay = {true, true, true, true};
                        break;
                    }
                }
                break;
            }
            case (2):
            {
                data.IsDoorWay = {true, true, true, true};
                switch (data.Last_Door)
                {
                    case (LAST_UP):
                    {
                        switch (PickOneDoor(LAST_DOWN, LAST_LEFT, LAST_RIGHT))
                        {
                            case (LAST_DOWN):
                            {
                                data.IsDoorWay.UpDoor = false;
                                break;
                            }
                            case (LAST_LEFT):
                            {
                                data.IsDoorWay.RightDoor = false;
                                break;
                            }
                            case (LAST_RIGHT):
                            {
                                data.IsDoorWay.LeftDoor = false;
                                break;
                            }
                            default:
                                break;
                        }
                        break;
                    }
                    case (LAST_DOWN):
                    {
                        switch (PickOneDoor(LAST_UP, LAST_LEFT, LAST_RIGHT))
                        {
                            case (LAST_UP):
                            {
                                data.IsDoorWay.DownDoor = false;
                                break;
                            }
                            case (LAST_LEFT):
                            {
                                data.IsDoorWay.RightDoor = false;
                                break;
                            }
                            case (LAST_RIGHT):
                            {
                                data.IsDoorWay.LeftDoor = false;
                                break;
                            }
                            default:
                                break;
                        }
                        break;
                    }
                    case (LAST_LEFT):
                    {
                        switch (PickOneDoor(LAST_UP, LAST_DOWN, LAST_RIGHT))
                        {
                            case (LAST_UP):
                            {
                                data.IsDoorWay.DownDoor = false;
                                break;
                            }
                            case (LAST_DOWN):
                            {
                                data.IsDoorWay.UpDoor = false;
                                break;
                            }
                            case (LAST_RIGHT):
                            {
                                data.IsDoorWay.LeftDoor = false;
                                break;
                            }
                            default:
                                break;
                        }
                        break;
                    }
                    case (LAST_RIGHT):
                    {
                        switch (PickOneDoor(LAST_UP, LAST_DOWN, LAST_LEFT))
                        {
                            case (LAST_UP):
                            {
                                data.IsDoorWay.DownDoor = false;
                                break;
                            }
                            case (LAST_DOWN):
                            {
                                data.IsDoorWay.UpDoor = false;
                                break;
                            }
                            case (LAST_LEFT):
                            {
                                data.IsDoorWay.RightDoor = false;
                                break;
                            }
                            default:
                                break;
                        }
                        break;
                    }
                    default:
                    {
                        data.IsDoorWay = {true, true, true, true};
                        break;
                    }
                }
                break;
            }
            case (3):
            {
                data.IsDoorWay = {true, true, true, true};
                break;
            }
            default:
            {
                data.IsDoorWay = {true, true, true, true};
                break;
            }
        }
    }
	void JudgeMakeDoorBoss(Game_Random_Data & data)
	{
		data.IsDoorWay = { false, false, false, false };
		switch (data.Last_Door)
		{
		case (LAST_UP):
		{
			data.IsDoorWay.DownDoor = true;
			switch (PickOneDoor(LAST_DOWN, LAST_LEFT, LAST_RIGHT))
			{
			case (LAST_DOWN):
			{
				data.IsDoorWay.UpDoor = true;
				break;
			}
			case (LAST_LEFT):
			{
				data.IsDoorWay.RightDoor = true;
				break;
			}
			case (LAST_RIGHT):
			{
				data.IsDoorWay.LeftDoor = true;
				break;
			}
			default:
				break;
			}
			break;
		}
		case (LAST_DOWN):
		{
			data.IsDoorWay.UpDoor = true;
			switch (PickOneDoor(LAST_UP, LAST_LEFT, LAST_RIGHT))
			{
			case (LAST_UP):
			{
				data.IsDoorWay.DownDoor = true;
				break;
			}
			case (LAST_LEFT):
			{
				data.IsDoorWay.RightDoor = true;
				break;
			}
			case (LAST_RIGHT):
			{
				data.IsDoorWay.LeftDoor = true;
				break;
			}
			default:
				break;
			}
			break;
		}
		case (LAST_LEFT):
		{
			data.IsDoorWay.RightDoor = true;
			switch (PickOneDoor(LAST_UP, LAST_DOWN, LAST_RIGHT))
			{
			case (LAST_UP):
			{
				data.IsDoorWay.DownDoor = true;
				break;
			}
			case (LAST_DOWN):
			{
				data.IsDoorWay.UpDoor = true;
				break;
			}
			case (LAST_RIGHT):
			{
				data.IsDoorWay.LeftDoor = true;
				break;
			}
			default:
				break;
			}
			break;
		}
		case (LAST_RIGHT):
		{
			data.IsDoorWay.LeftDoor = true;
			switch (PickOneDoor(LAST_UP, LAST_DOWN, LAST_LEFT))
			{
			case (LAST_UP):
			{
				data.IsDoorWay.DownDoor = true;
				break;
			}
			case (LAST_DOWN):
			{
				data.IsDoorWay.UpDoor = true;
				break;
			}
			case (LAST_LEFT):
			{
				data.IsDoorWay.RightDoor = true;
				break;
			}
			default:
				break;
			}
			break;
		}
		default:
		{
			data.IsDoorWay = { true, true, true, true };
			break;
		}
		}
	}
    void SetIsLastDoor(Game_Random_Data& data)
    {

        switch (data.Current_Door)
        {
            case (CURRENT_UP):
            {
                if (data.Last_Door == LAST_DOWN)
                {
                    data.Door_Stat = RG_BEFORE;
                }
                else
                {
                    data.Door_Stat = RG_NEXT;
                }
                break;
            }
            case (CURRENT_DOWN):
            {
                if (data.Last_Door == LAST_UP)
                {
                    data.Door_Stat = RG_BEFORE;
                }
                else
                {
                    data.Door_Stat = RG_NEXT;
                }
                break;
            }
            case (CURRENT_LEFT):
            {
                if (data.Last_Door == LAST_RIGHT)
                {
                    data.Door_Stat = RG_BEFORE;
                }
                else
                {
                    data.Door_Stat = RG_NEXT;
                }
                break;
            }
            case (CURRENT_RIGHT):
            {
                if (data.Last_Door == LAST_LEFT)
                {
                    data.Door_Stat = RG_BEFORE;
                }
                else
                {
                    data.Door_Stat = RG_NEXT;
                }
                break;
            }
            default:
            {
                data.Door_Stat = RG_NEXT;
                break;
            }
        }
    }
}
