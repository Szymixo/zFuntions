// 
// Include zFunctions.inc
// Autor: Szymixo
// Wersja 0.1 dev
//

/*

	Lista funkcji:

	a) Zwracające:
	• PlayerName(playerid);
	• PlayerScore(playerid);
	• PlayerMoney(playerid);
	• PlayerWeapon(playerid);
	• PlayerInterior(playerid);
	• PlayerVW(playerid);
	• PlayerVehID(playerid);
	• PlayerAmmo(playerid);
	• PlayerArmour(playerid);
	• PlayerHealth(playerid);
	• PlayerDrunk(playerid);
	• PlayerIP(playerid);
	• PlayerSerial(playerid);
	• CurrentTime();

	b) Wykonujące:
	• KickPlayer(playerid, powod[]);
	• WriteToLog(filename[], row[]);
	• SendClientMessageInRange(playerid, text[]);
	• SendMeMessageInRange(playerid, text[]);
	• SendDoMessageInRange(playerid, text[]);

	c) Dodatkowe:
	• GivePlayerScore(playerid, ilosc);
	• SetPlayerMoney(playerid, ilosc);
*/


native gpci(playerid, serial[], len);

stock PlayerName(playerid)
{
	new nick[24];
	GetPlayerName(playerid, nick, MAX_PLAYER_NAME);
	return nick;
}

stock PlayerScore(playerid)
{
	new score = GetPlayerScore(playerid);
	return score;
}

stock PlayerMoney(playerid)
{
	new money = GetPlayerMoney(playerid);
	return money;
}

stock PlayerWeapon(playerid)
{
	new gunid = GetPlayerWeapon(playerid);
	return gunid;
}

stock PlayerInterior(playerid)
{
	new interior = GetPlayerInterior(playerid);
	return interior;
}

stock PlayerVW(playerid)
{
	new vw = GetPlayerVirtualWorld(playerid);
	return vw;
}

stock PlayerVehID(playerid)
{
	new vehid = GetPlayerVehicleID(playerid);
	return vehid;
}

stock PlayerAmmo(playerid)
{
	new ammo = GetPlayerAmmo(playerid);
	return ammo;
}

stock PlayerArmour(playerid)
{
	new Float:armour;
	GetPlayerArmour(playerid, armour);
	return armour;
}

stock PlayerHealth(playerid)
{
	new Float:hp;
	GetPlayerHealth(playerid, hp);
	return hp;
}

stock PlayerDrunk(playerid)
{
	new drunk = GetPlayerDrunkLevel(playerid);
	return drunk;
}

stock PlayerIP(playerid)
{
	new ip[16];
	GetPlayerIp(playerid, ip, sizeof(ip));
	return ip;
}

stock PlayerSerial(playerid)
{
	new serial[41];
	gpci(playerid, serial, sizeof(serial));
	return serial;
}

stock CurrentTime()
{
	new Year, Month, Day;
	getdate(Year, Month, Day);

	new Hour, Minute, Second;
	gettime(Hour, Minute, Second);

	new time[100];
	format(time, sizeof(time), "[%02d:%02d:%02d, %02d.%02d.%d] ", Hour, Minute, Second, Day, Month, Year);
	return time;
}

// ======================================================================

stock KickPlayer(playerid)
{
	return SetTimerEx("PlayerKick", 100, false, "i", playerid);
}
forward PlayerKick(playerid);
public PlayerKick(playerid) return Kick(playerid);

stock SCM(playerid, string[])
{
	return SendClientMessage(playerid, -1, string);
}

stock WriteToLog(filename[], row[])
{
	new log[200];
	new File:handle = fopen(filename, io_write);
	if(handle)
	{
		format(log, sizeof(log), "%s %s", CurrentTime(), row);
		fwrite(handle, log);
		fclose(handle);
	}
	return 1;
}

stock SendClientMessageInRange(playerid, tekst[])
{
	new text[500];
	new Float:PosX1, Float:PosY1, Float:PosZ1;
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, PosX1, PosY1, PosZ1);
	for(new i; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			GetPlayerPos(i, x, y, z);
			if(IsPlayerInRangeOfPoint(i, 10, PosX1, PosY1, PosZ1))
			{
				format(text, sizeof(text), "%s mowi: %s", PlayerName(playerid), tekst);
				SCM(i, text);
			}
		}
	}
	return 1;
}

stock SendMeMessageInRange(playerid, tekst[])
{
	new text[500];
	new Float:pPos[3];
	new Float:oPos[3];
	GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
	for(new i; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			GetPlayerPos(i, oPos[0], oPos[1], oPos[2]);
			if(IsPlayerInRangeOfPoint(i, 10, pPos[0], pPos[1], pPos[2]))
			{
				format(text, sizeof text, "{cb49ff}* %s %s *", PlayerName(playerid), tekst);
				SCM(i, text);
			}
		}
	}
	return 1;
}

stock SendDoMessageInRange(playerid, tekst[])
{
	new text[500];
	new Float:pPos[3];
	new Float:oPos[3];
	GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
	for(new i; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			GetPlayerPos(i, oPos[0], oPos[1], oPos[2]);
			if(IsPlayerInRangeOfPoint(i, 10, pPos[0], pPos[1], pPos[2]))
			{
				format(text, sizeof text, "{cb49ff}**  %s ((%s))", tekst, PlayerName(playerid));
				SCM(i, text);
			}
		}
	}
	return 1;
}

// ======================================================================

stock GivePlayerScore(playerid, ilosc)
{
	return SetPlayerScore(playerid, ilosc+GetPlayerScore(playerid));
}

stock SetPlayerMoney(playerid, ilosc)
{
	new amount = GetPlayerMoney(playerid);
	GivePlayerMoney(playerid, -amount);
	GivePlayerMoney(playerid, ilosc);
	return 1;
}