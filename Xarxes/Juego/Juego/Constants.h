#pragma once



enum PacketType
{

	//Estas constantes se pueden cambiar para tener el nombre que nosotros queramos
	//a la hora de serializar los bits que enviamos.

	PT_EMPTY,
	PT_HELLO,
	PT_WELCOME,
	PT_FULL,
	PT_MOVE,
	PT_AUTHOR,
	PT_DISCONNECT,
	PT_RESETPLAYER,
	PT_FINISH
};
