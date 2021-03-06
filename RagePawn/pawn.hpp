#pragma once

#include "main.hpp"
#include <filesystem>
#include "../amxlib/amx.h"

class Pawn
{
public:
	Pawn();

	void SetMultiplayer(rage::IMultiplayer *mp);
	void Callback(const char * name, const char * fmt, ...);
	rage::IMultiplayer *GetMultiplayer() { return m_mp; }

	int RunAMX(const std::string& path);
	int Terminate() const;
	void TerminateScript();

	static Pawn& GetInstance() { static Pawn instance; return instance; }

	//static cell AMX_NATIVE_CALL n_print_int(AMX *amx, const cell *params);
	//void print_int(int value);
		
private:
	rage::IMultiplayer *m_mp;
	AMX amx;
	int err;
};

namespace gm
{
	class EventHandler
		: public rage::IEventHandler,
		public rage::IPlayerHandler,
		public rage::ITickHandler
	{
	public:

		static EventHandler& GetInstance() { static EventHandler instance; return instance; }

		virtual rage::ITickHandler *GetTickHandler() { return this; }
		virtual rage::IPlayerHandler *GetPlayerHandler() { return this; }

		virtual void OnPlayerJoin(rage::IPlayer *player)
		{
			//std::cout << "Player: " << player->GetId() << std::endl;
			Pawn::GetInstance().Callback("OnPlayerConnect", "d", (int)player->GetId());
		}

		virtual void Tick() {  }
	};
}