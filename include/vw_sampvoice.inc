new SV_GSTREAM: gstream;
new SV_LSTREAM: lstream[MAX_PLAYERS] = { SV_NULL, ... };

public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid,	SV_UINT:keyid)
{
	//if(CHECKING[PlayerRequestClass])
//ИНФОРМИРОВАНИЕ
	new str[50+3+10];
	format(str, sizeof(str),"OnPlayerActivationKeyPress(playerid:%d, keyid:%d)", playerid, keyid);
	SendClientMessage(playerid, -1, str);

	if (keyid == 0x42 && lstream[playerid]) SvAttachSpeakerToStream(lstream[playerid], playerid);
	if (keyid == 0x5A && gstream) SvAttachSpeakerToStream(gstream, playerid);
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
//ИНФОРМИРОВАНИЕ
	new str[50+3+10];
	format(str, sizeof(str),"OnPlayerActivationKeyRelease(playerid:%d, keyid:%d)", playerid, keyid);
	SendClientMessage(playerid, -1, str);
	
	if (keyid == 0x42 && lstream[playerid]) SvDetachSpeakerFromStream(lstream[playerid], playerid);
	if (keyid == 0x5A && gstream) SvDetachSpeakerFromStream(gstream, playerid);
}

stock sampvoice_OnGameModeInit()
{
	SvDebug(SV_TRUE);
	gstream = SvCreateGStream(0xffff0000, "G"); // blue color
}

stock sampvoice_OnPlayerConnect(playerid)
{
	if (!SvGetVersion(playerid)) SendClientMessage(playerid, -1, "Установите плагин sampvoice");
	else if (!SvHasMicro(playerid)) SendClientMessage(playerid, -1, "Микрофон не обнаружен");
	else if (lstream[playerid] == SvCreateDLStreamAtPlayer(40.0, SV_INFINITY, playerid, 0xff0000ff, "L"))
	{ // red color
		SendClientMessage(playerid, -1, "Голосовой чат инициализирован");
		if (gstream) SvAttachListenerToStream(gstream, playerid);
		SvAddKey(playerid, 0x42);
		SvAddKey(playerid, 0x5A);
	}
}

stock sampvoice_OnPlayerDisconnect(playerid)
{
	if (lstream[playerid])
	{
		SvDeleteStream(lstream[playerid]);
		lstream[playerid] = SV_NULL;
	}
}




