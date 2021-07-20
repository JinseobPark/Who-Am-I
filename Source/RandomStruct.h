/**
\file        RandomStruct.h
\author      jinseob.park
\par         email: 0814owl@gmail.com
\par         course: GAM250
\date        06/14/2018
\brief       Random map struct.
All content (c) 2018 DigiPen (USA) Corporation, all rights reserved.
*/
#ifndef RANDOMSTRUCTURE_H
#define RANDOMSTRUCTURE_H
namespace FindersEngine
{
    static const int BaseId = 5001;
    static const int PlayerId = 100;
    static const int ZombieId = 1000;
    static const int PistolId = 2000;
    static const int AmmoId = 2100;
    static const int ArmorId = 2200;
    static const int WallId = 4000;
    static const int DoorId = 4100;
    static const int TutorialId = 5000;
    static const int HPbar_Id = 3500;
    static const int ArmorbarId = 3501;

    static const int room_style_number = 30;

    enum class RoomStyle
    {
        O_ONEBYONE = 0,
        O_TWOBYTWO,
        O_HOLE,
        H_ONE,
        H_TWO,
        V_ONE,
        V_TWO,
        L_THREE_1,
        L_THREE_2,
        L_THREE_3,
        L_THREE_4,
        L_FOUR_1,
        L_FOUR_2,
        L_FOUR_3,
        L_FOUR_4,
        L_FOUR_5,
        L_FOUR_6,
        L_FOUR_7,
        L_FOUR_8,
        L_FIVE,
        N_V,
        N_H,
        T_UP,
        T_DOWN,
        T_RIGHT,
        T_LEFT,
        X_UNIQUE,
        U_UP,
        U_DOWN,
        U_RIGHT,
        U_LEFT
    };

    enum DoorStat
    {
        RG_NEXT,
        RG_BEFORE,
        RG_CURRENT
    };

    enum LastDoor
    {
        LAST_UP,
        LAST_DOWN,
        LAST_LEFT,
        LAST_RIGHT,
        LAST_NONE
    };

    enum CurrentDoor
    {
        CURRENT_UP,
        CURRENT_DOWN,
        CURRENT_LEFT,
        CURRENT_RIGHT,
        CURRENT_NONE
    };

    struct SureIsCabinet
    {
        bool UpCabinet;
        bool DownCabinet;
        bool LeftCabinet;
        bool RightCabinet;
    };

    struct SureIsDoor
    {
        bool UpDoor;
        bool DownDoor;
        bool LeftDoor;
        bool RightDoor;
    };

    inline const char* ToString(RoomStyle room_name)
    {
        switch (room_name)
        {
            case RoomStyle::O_ONEBYONE:
                return "O_ONEBYONE";
            case RoomStyle::O_TWOBYTWO:
                return "O_TWOBYTWO";
            case RoomStyle::O_HOLE:
                return "O_HOLE";
            case RoomStyle::H_ONE:
                return "H_ONE";
            case RoomStyle::H_TWO:
                return "H_TWO";
            case RoomStyle::V_ONE:
                return "V_ONE";
            case RoomStyle::V_TWO:
                return "V_TWO";
            case RoomStyle::L_THREE_1:
                return "L_THREE_1";
            case RoomStyle::L_THREE_2:
                return "L_THREE_2";
            case RoomStyle::L_THREE_3:
                return "L_THREE_3";
            case RoomStyle::L_THREE_4:
                return "L_THREE_4";
            case RoomStyle::L_FOUR_1:
                return "L_FOUR_1";
            case RoomStyle::L_FOUR_2:
                return "L_FOUR_2";
            case RoomStyle::L_FOUR_3:
                return "L_FOUR_3";
            case RoomStyle::L_FOUR_4:
                return "L_FOUR_4";
            case RoomStyle::L_FOUR_5:
                return "L_FOUR_5";
            case RoomStyle::L_FOUR_6:
                return "L_FOUR_6";
            case RoomStyle::L_FOUR_7:
                return "L_FOUR_7";
            case RoomStyle::L_FOUR_8:
                return "L_FOUR_8";
            case RoomStyle::L_FIVE:
                return "L_FIVE";
            case RoomStyle::N_V:
                return "N_V";
            case RoomStyle::N_H:
                return "N_H";
            case RoomStyle::T_UP:
                return "T_UP";
            case RoomStyle::T_DOWN:
                return "T_DOWN";
            case RoomStyle::T_RIGHT:
                return "T_RIGHT";
            case RoomStyle::T_LEFT:
                return "T_LEFT";
            case RoomStyle::X_UNIQUE:
                return "X_UNIQUE";
            case RoomStyle::U_UP:
                return "U_UP";
            case RoomStyle::U_DOWN:
                return "U_DOWN";
            case RoomStyle::U_RIGHT:
                return "U_RIGHT";
            case RoomStyle::U_LEFT:
                return "U_LEFT";
            default:
                return "";
        }
    }
}


#endif