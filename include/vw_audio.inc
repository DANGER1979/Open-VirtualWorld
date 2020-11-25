new RepeatAudio[MAX_PLAYERS];

stock PlayerPlayMusic(playerid)//запускается при начислении денег каждый час или при покупке чего-либо
{
	PlaySoundForPlayer(playerid, SOUND_DUAL_TRACK_START);
	SetTimerEx("tStopMusic", 5000, 0, "d", playerid);
/*Format syntax SetTimerEx
Placeholder 	Meaning
i 	Stands for an integer parameter.
d 	Exactly the same as i.
a 	Passes an array, the next parameter must be an integer ("i") with the array's size.
s 	Stands for a strings parameter.
f 	Stands for a float parameter.
b 	Stands for a boolean parameter.*/
}
forward tStopMusic(playerid);
public tStopMusic(playerid)//запускается через 5 секунд 1 раз
{
	PlaySoundForPlayer(playerid, SOUND_DUAL_TRACK_STOP);
}


forward RepeatAudioStreamForPlayerEx(playerid, const audiourl[]);
public RepeatAudioStreamForPlayerEx(playerid, const audiourl[])
{
	StopAudioStreamForPlayer(playerid);
    new strtmp[28+64+64 + 12];
	format(strtmp, sizeof(strtmp), "http://%s/soundVW/%s", HostName, audiourl);
	PlayAudioStreamForPlayer(playerid, strtmp);
}

forward StopAudioStreamForPlayerEx(playerid);
public StopAudioStreamForPlayerEx(playerid)
{
	StopAudioStreamForPlayer(playerid);
	if(RepeatAudio[playerid]) {	KillTimer(RepeatAudio[playerid]); RepeatAudio[playerid] = -1; }
}

stock audio_OnPlayerConnect(playerid)
{
	RepeatAudio[playerid] = -1;
}
new threeseconds[MAX_PLAYERS];//счётчик для 3-хсекундного пакетника

stock PlayAudioStreamForPlayerEx(playerid, const audiourl[], Float:posX = 0.0, Float:posY = 0.0, Float:posZ = 0.0, Float:distance = 50.0, usepos = 0)
{
#if defined LOCAL
	//#pragma unused audiourl
	
	if(GetTickCount() >= threeseconds[playerid] + 3000)
	{
		//if( !strcmp(php_host, "localhost", true) )
		//{
		StopAudioStreamForPlayer(playerid);
		new strtmp[28+64+64 + 12];
		//format(strtmp, sizeof(strtmp), "http://%s/soundVW/%s", HostName, audiourl);//http://localhost/soundVW/GTAV_titles.mp3 http://127.0.0.1/soundVW/GTAV_titles.mp3
		format(strtmp, sizeof(strtmp), "http://127.0.0.1/SoundVW/%s", audiourl);//http://localhost/soundVW/GTAV_titles.mp3
		PlayAudioStreamForPlayer(playerid, strtmp, posX, posY, posZ, distance, usepos);
			
		//PlayAudioStreamForPlayer(playerid, "localhost/soundVW/GTAV_titles.mp3", posX, posY, posZ, distance, usepos);
		//PlayAudioStreamForPlayer(playerid, "http://127.0.0.1/soundVW/GTAV_titles.mp3", posX, posY, posZ, distance, usepos);

		//}
		threeseconds[playerid] = GetTickCount();
	}
#elseif defined STRIKEARENA_7777
	if(GetTickCount() >= threeseconds[playerid] + 3000)
	{
		if( strcmp(php_host, "localhost", true) )
		{//не localhost
			StopAudioStreamForPlayer(playerid);
			new strtmp[28+64+64 + 12];
			format(strtmp, sizeof(strtmp), "http://%s/soundVW/%s", HostName, audiourl);
			PlayAudioStreamForPlayer(playerid, strtmp, posX, posY, posZ, distance, usepos);
		}
		threeseconds[playerid] = GetTickCount();
	}
#else
	#pragma unused playerid
	#pragma unused audiourl
	#pragma unused posX
	#pragma unused posY
	#pragma unused posZ
	#pragma unused distance
	#pragma unused usepos
#endif
	return 1;
}



stock AudioMessage(playerid, const text[], const lang[] = "ru")
{
   new strtmp[72+128 + 12];
   format(strtmp, sizeof(strtmp), "http://translate.google.ru/translate_tts?ie=UTF-8&q=%s&tl=%s&prev=input", text, lang);
   PlayAudioStreamForPlayer(playerid, strtmp);
}//https://translate.google.ru/#view=home&op=translate&sl=auto&tl=ru&text=привет.как дела.
