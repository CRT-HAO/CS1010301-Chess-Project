/**
 *  File: PlayerUtil.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/11 02:55:43
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/16 19:03:57
 *  Description: Player Utility
 */

#pragma once

#include "TPlayer.hpp"

#include <string>

namespace Chess
{

    class PlayerUtil
    {
    public:
        static inline std::string typeToString(TPlayer type)
        {
            switch ( type )
            {
            case TPlayer::kWhite:
                return "white";
            case TPlayer::kBlack:
                return "black";
            default:
                return "undefined";
            }
            return "undefined";
        }
    };

}