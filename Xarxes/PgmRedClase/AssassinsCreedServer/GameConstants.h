#pragma once


#define HEADER_NICK "NICK"
#define HEADER_CHAT "CHAT"
#define HEADER_KILL "KILL"
#define HEADER_CATCHYOU "ICATCHYOU"
#define HEADER_RESEND "RESENDPLAYERSSTATE"

#define PLAYER_STATE_ALIVE 0
#define PLAYER_STATE_DEAD 1

#define PLAYER_ROLE_ASSASSIN 0
#define PLAYER_ROLE_POLICE 1
#define PLAYER_ROLE_VICTIM 2

static std::string aStrStates[] = {"VIVO", "MUERTO"};
static std::string aStrRoles[] = { "ASESION", "POLICIA", "VICTIMA" };