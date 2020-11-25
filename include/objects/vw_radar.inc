//##############################################################################//
//                                                                              //
//                               СИСТЕМА РАДАРОВ                                //
//                                                                              //
//##############################################################################//


//для радаров начало
new nearest[MAX_PLAYERS];//номер ближайщего радара

new ticket_rate = 1200; //штраф на радаре

new GaiWant[MAX_PLAYERS];
new GaiRad[MAX_PLAYERS];
new speedpl[MAX_PLAYERS];//записываем скорость при которой было нарушение, т.е. превышенная скорость
new ExcessPlayerVelocities[MAX_PLAYERS];
new gPlayerUsedBridge[MAX_PLAYERS] = {-1, ...};//хранит номер моста который используется игроком
new PlayerText:txdRADAR[MAX_PLAYERS];

#define MAX_RADARS 32//18
enum radStats
{	//Highscore enum
	radName[20],
	Float:radRange,
//координаты где проверяется установка блока
	Float:radX,
	Float:radY,
	Float:radZ,
	objModelid,
//координаты для установки блоков мостов
	Float:objX,
	Float:objY,
	Float:objZ,
	Float:objrX,
	Float:objrY,
	Float:objrZ,
	radSpeed//скорость в этом месте
};
new aRadar[MAX_RADARS][radStats] = {//Float:
//LS Exit bridges
{"LombardBridge",16.0, 	73.9863,-1548.1802,4.1315, 		4504,53.11,-1531.88,6.8,0.0,0.0,-10.0, 60},// 0
{"LS Tunnel",	12.0, 	83.5625,-1268.7329,13.1062, 	4522,87.5,-1257.5,15.8,0.0,0.0,215.0, 60},// 1
{"Flint",		61.0,	-41.4180,-836.3509,10.9948, 	4521,-84.5,-909.0,18.3,0.0,0.0,64.0, 60},// 2
{"ReaganBridge",51.0,	7.9181,-478.5251,2.9529, 		4505,40.0,-530.0,11.9,0.0,-1.0,113.0, 60},// 3
{"Foothill",	14.0, 	254.8218,-364.1302,7.1676, 		4505,269.0,-375.88,10.5,0.0,-1.0,-15.0, 60},// 4
{"Blueberry",	34.0, 	526.6143,-197.6302,34.9774, 	4505,508.0,-244.88,40.6,0.0,-3.0,260.0, 60},// 5
{"HilltopW",	14.0, 	761.0995,-157.6868,17.1419,		4507,789.5,-165.0,20.3,0.0,0.0,-8.0, 60},// 6
{"HilltopE",	6.0, 	1230.7341,-140.9773,38.0379,	4507,1212.5,-147.4,41.7,0.0,-2.0,210.0, 60},// 7
{"Montgomerry",	58.0, 	1625.0771,54.4102,35.7143,		4504,1639.5,-17.0,38.3,0.0,-1.0,-70.0, 60},// 8
{"EisenhowerBridge",51.0,1856.7710,-108.8276,33.8846,	4507,1881.20,-53.81,36.7,0.0,0.0,250.0, 60},// 9
{"Bay",			18.0, 	2128.7993,48.0067,24.9748,		4507,2104.0,43.0,28.1,0.0,0.0,-8.0, 60},// 10
{"Hankypanky",	30.0, 	2219.9561,218.4040,13.2883,		4507,2183.0,233.50,16.3,0.0,0.0,-11.0, 60},// 11
{"Palomino",	53.0, 	2117.0146,328.5672,32.6397,		4504,2180.0,317.0,34.7,0.0,-1.0,180.0, 60},// 12
//---------------------------
{"FallowBridgeSE",15.0,	606.7228,336.1728,17.8885,		4514,599.0,360.6914,19.8,0.0,0.0,210.0, 60},//13
{"FallowBridgeNW",15.0,	434.5453,608.3110,17.7189,		4515,442.0,585.0,19.9000,0.0,0.0,30.0, 60},//14
{"MartinBridgeS",15.0,	-206.9377,251.1098,10.8371,		4514,-193.0,271.0,13.0,0.0,0.0,164.0, 60},//15
{"MartinBridgeN",15.0,	-129.8598,481.2558,10.5910,		4515,-144.0,460.0,13.0,0.0,0.0,344.0, 60},//16
{"MakoSpan",	18.0,	1732.0326,503.8889,28.0302,		4518,1739.0,525.0,28.8,0.0,0.0,250.0, 60},//17
{"FordBridgeNE",	20.0,	-939.1281,-244.9905,36.5910,	4508,-954.5,-270.0028,38.6,0.0,0.0,75.0, 60},//18
{"FordBridgeSW",	14.0,	-990.1411,-431.6132,34.8422,	4509,-980.9,-410.0,38.1,0.0,0.0,252.0, 60},//19
{"GarverBridgeC",135.0,	-1663.6604,548.1568,37.2369,	4518,-1564.0,653.0,44.6,0.0,0.0,225.0, 90},// 20
{"GarverBridgeN",25.0,	-1134.6958,1105.5576,37.1936,	4518,-1158.0148,1081.0595,40.5381,0.0,0.0,50.0, 90},//21
{"GarverBridgeS",18.0,	-1816.3235,388.2858,15.7592,	4525,-1807.3154,396.5960,18.0777,0.0,0.0,0.0, 90},//22
{"GantBridgeC",		60.0,	-2682.5525,2182.0322,55.4829,	4518,-2682.1931,2112.0420,56.5125,0.0,0.0,90.0, 90},//23
{"GantBridgeS",		10.0,	-2681.8884,1282.6108,55.0844,	4512,-2677.5529,1240.8820,60.5570,0.0,0.0,268.0, 60},// 24
{"GantBridgeN",		27.0,	-2758.4387,2366.5383,73.5040,	4513,-2750.9890,2339.9306,73.2,0.0,0.0,0.0, 90},//25
{"HarrisonBridge",	82.0,	-1023.8364,-2871.2415,66.2995,	4504,-1116.1190,-2857.2317,69.4500,0.0,-1.0,0.0, 60},//26
{"SouthSFBridge",	128.0,	-2856.5476,-920.6494,7.6570,	4504,-2892.6824,-1054.4211,11.2,0.0,0.0,80.0, 90},//27
{"HooverBridge",156.0,	-743.9632,716.4573,16.7779,		4509,-591.3614,635.1079,18.4217,0.0,-1.0,-22.0, 90},//28
{"Fort Carson",	72.0,	-411.7317,1007.4991,9.6129,	4507,-477.9767,1055.1423,12.8,0.0,0.0,-35.0, 60},//29
{"Valle Ocultado",100.0,-961.6342,2709.5122,44.4672,	4507,-1070.7911,2705.7324,47.6672,0.0,-0.5,5.0, 60},//30
{"Palen",		72.0,	-1742.7834,-1660.4154,34.2988, 	4505,-1663.7911,-1636.7324,37.9,0.0,-2.0,205.0, 60}//31

/*
//32 для радаров //1269 - столбы таксометра //18880 - радары //19076 - ёлки
{true, 18880, 73.9863,-1548.1802,4.1315,0.0,0.0,0.0},//134 //0
{true, 18880, 83.5625,-1268.7329,13.1062,0.0,0.0,0.0},// 1
{true, 18880, -41.4180,-836.3509,10.9948,0.0,0.0,0.0},// 2
{true, 18880, 7.9181,-478.5251,2.9529,0.0,0.0,0.0},// 3
{true, 18880, 254.8218,-364.1302,7.1676,0.0,0.0,0.0},// 4
{true, 18880, 526.6143,-197.6302,34.9774,0.0,0.0,0.0},// 5
{true, 18880, 761.0995,-157.6868,17.1419,0.0,0.0,0.0},// 6
{true, 18880, 1230.7341,-140.9773,38.0379,0.0,0.0,0.0},// 7
{true, 18880, 1625.0771,54.4102,35.7143,0.0,0.0,0.0},// 8
{true, 18880, 1856.7710,-108.8276,33.8846,0.0,0.0,0.0},// 9
{true, 18880, 2128.7993,48.0067,24.9748,0.0,0.0,0.0},// 10
{true, 18880, 2219.9561,218.4040,13.2883,0.0,0.0,0.0},// 11
{true, 18880, 2117.0146,328.5672,32.6397,0.0,0.0,0.0},// 12
//-------------------------------------------------
{true, 18880, 606.7228,336.1728,17.8885,0.0,0.0,0.0},//13
{true, 18880, 434.5453,608.3110,17.7189,0.0,0.0,0.0},//14
{true, 18880, -206.9377,251.1098,10.8371,0.0,0.0,0.0},//15
{true, 18880, -129.8598,481.2558,10.5910,0.0,0.0,0.0},//16
{true, 18880, 1732.0326,503.8889,28.0302,0.0,0.0,0.0},//17
{true, 18880, -939.1281,-244.9905,36.5910,0.0,0.0,0.0},//18
{true, 18880, -990.1411,-431.6132,34.8422,0.0,0.0,0.0},//19
{true, 18880, -1663.6604,548.1568,37.2369,0.0,0.0,0.0},//20
{true, 18880, -1134.6958,1105.5576,37.1936,0.0,0.0,0.0},//21
{true, 18880, -1816.3235,388.2858,15.7592,0.0,0.0,0.0},//22
{true, 18880, -2682.5525,2182.0322,55.4829,0.0,0.0,0.0},//23
{true, 18880, -2681.8884,1282.6108,55.0844,0.0,0.0,0.0},//24
{true, 18880, -2758.4387,2366.5383,73.5040,0.0,0.0,0.0},//25
{true, 18880, -1023.8364,-2871.2415,66.2995,0.0,0.0,0.0},//26
{true, 18880, -2856.5476,-920.6494,7.6570,0.0,0.0,0.0},//27
{true, 18880, -743.9632,716.4573,16.7779,0.0,0.0,0.0},//28
{true, 18880, -411.7317,1007.4991,9.6129,0.0,0.0,0.0},//29
{true, 18880, -961.6342,2709.5122,44.4672,0.0,0.0,0.0},//30
{true, 18880, -1742.7834,-1660.4154,34.2988,0.0,0.0,0.0},//165//31
*/
//---------------------------
//SF Exit bridges
//{"Bridge",100.0,-1215.4867,-772.4171,63.4006, 4507,0.0,0.0,0.0,0.0,0.0,0.0}//32
//---------------------------
};
//new STREAMER_TAG_3D_TEXT_LABEL: aRadarlabel;


stock radar_OnGameModeInit()///загрузка глобальных объектов
{
	new time = GetTickCount();

	for(new r=0; r<MAX_RADARS; r++)
	{
		CreateObjectEx(18880, aRadar[r][radX],aRadar[r][radY],aRadar[r][radZ], 0.0,0.0,0.0, 0, 0, -1, 300.0);
	}
	printf("10/19. [Загрузка радаров]: Было загружено - %d, потрачено - %d (ms)", MAX_RADARS, GetTickCount() - time);//new time = GetTickCount();
}


stock radar_OnPlayerConnect(playerid)
{
	GaiWant[playerid] = 0;//подготовить ГАИ к сканированию
	ExcessPlayerVelocities[playerid] = 0;//убрать превышение
	GaiRad[playerid] = 0;//подготовить радар к сканированию
	gPlayerUsedBridge[playerid] = -1;
}



stock radar_OneSecondTimers(playerid)
{
    if(CurState[playerid] != PLAYER_STATE_DRIVER) return 1;
  	new strtmp[71+2+2];
//==============================================================================
//ДЛЯ РАДАРОВ 		//для антирадара
    //Если игрок проехал с большой скоростью мимо гаишника
	/*if( (PlayerInfo[playerid][pMember] != DoT && PlayerInfo[playerid][pLevel] > 1) ||
		(PlayerInfo[playerid][pMember] == DoT && gOnDuty[playerid] == 0))//для гаишников начало
	{   //если игрок playerid не гаишник или не на дежурстве
		new found = -1;
		for(new j=0, i; j<MaxPlayers; j++)	{
			i = PLIDs[j];
   //сканируем всех гаишников
			if( !IsPlayerConnectedEx(i) || !gPlayerSpawned[i] ) continue;
			if(i == playerid) continue;
			if(spectateid[i] != MAX_PLAYERS-1) continue;
		    if(PlayerInfo[i][pMember] != DoT || !gOnDuty[i]) continue;
		    if( !IsPlayerInAnyVehicle(i) ) continue;
   			//сканируем всех гаишников на дежурстве в коп каре
			if( !IsInCopCar(nCarID[i]) ) continue;
			if(nCarID[playerid] == nCarID[i]) continue;//если игрок не сидит в машине полицмена
			if(	!IsPlayerInRangeOfPlayer(60.0, playerid, i) ) continue;
       	    found = i;
       	    break;
   		}
   		if(found != -1)
   		{
   			new velocity = GetVehicleSpeed(nCarID[playerid]);
			if( GaiWant[playerid] == 0 &&
				//PlayerInfo[playerid][pJob] == CARMECHANIC &&
				velocity > 50 &&
				nCarModel[playerid] == 525 &&
				IsTrailerAttachedToVehicle(nCarID[playerid]))
			{	//если нарушитель ещё не в розыске и превысил скорость в городе при буксировке
				PlaySoundForPlayer(playerid, SOUND_CAMERA_SHOT);
				WantedPoints[playerid] += 3;
				//strings[0] = EOS;
				//new strtmp[41+3+3];
				format(strtmp, sizeof(strtmp), "Нарушение правил буксировки [%d] %d км/ч", nCarID[playerid], velocity);//velocity
				SetPlayerCriminal(DoT, playerid, found, strtmp);
				SendTeamMessage(DoT, COLOR_DARKTURQUOISE, "   USE: /pdd [14] [4] [playerid/PartOfName]");
				//14,4, "Невыполнение требований", "знаков, разметки, перекрестков, буксировки, маневрирования, непредставление преимущества",1,3,0},//1-5
				GaiWant[playerid] = 1;//объявляем розыск
			}
       	    if(GaiWant[playerid] == 0 && !IsInPlane(nCarID[playerid]) && !IsInBoat(nCarID[playerid]))
       	    {   //если нарушитель ещё не в розыске и превысил скорость в городе
				if(	ExcessPlayerVelocities[playerid] == 1 &&
					GetVehicleSpeed(nCarID[found]) < 5 && SpecialBleep[nCarID[playerid]] == 0)
			   {
					PlaySoundForPlayer(playerid, SOUND_CAMERA_SHOT);
					WantedPoints[playerid] += 6;
					//strings[0] = EOS;
					//new strtmp[64];
					format(strtmp, sizeof(strtmp), "Нарушение скоростного режима [%d] %dкм/ч", nCarID[playerid], speedpl[playerid]);//velocity
					SendTeamMessage(DoT, COLOR_DARKTURQUOISE, "   USE: /pdd [13] [1-4] [playerid/PartOfName]");
					SetPlayerCriminal(DoT, playerid, found, strtmp);
					//25.4 Превышение установленной скорости движения ТС - Штраф 5000$
					GaiWant[playerid] = 1;//объявляем розыск
				}
       		}
       		else //if(GaiWant[playerid] == 1)
       		{   //иначе если игрок уже в розыске
   			    if(velocity > 90)
   			    {
					if(DriveProgress[playerid] > 6)//если игрок сдавал экзамен по городу
					{
						StopDriveProgress(playerid);
				        format(strings, sizeof(strings), "CEPBEP: {800000}урок остановлен у %s's. Причина: превышение скорости !", PlayerName(playerid));
						SendTeamMessage(DoE, COLOR_LIGHTBROWN, strings);
					}
					RemovePlayerFromVehicleEx(playerid);//высадить из машины игрока
		  			GaiWant[playerid] = 0;//подготовить ГАИ к сканированию
		  			//GaiRad[playerid] = 0;//подготовить радар к сканированию
		  			ExcessPlayerVelocities[playerid] = 0;//убрать превышение
           		}
	      		//else SendClientMessage(i,COLOR_LIGHTBLUE, "У игрока скорость выше 90 км/ч, тебе его не поймать, попробуй замедлить его!!!.");
           	}
  			//GaiRad[playerid] = 0;//для гаишников конец
  		}
	}*/
	//----------------------------------------------------------------------
	//НАЧАЛО ОПРЕДЕЛЕНИЯ ПРЕВЫШЕННОЙ СКОРОСТИ
	new velocity = GetVehicleSpeed(nCarID[playerid]);
	if(velocity < 60)//для информационной панели начало
	{
		ExcessPlayerVelocities[playerid] = 0;
	}
	else if(velocity >= 60 && velocity <= 90)
	{
   		if(velocity >= 70 && SpecialBleep[nCarID[playerid]] == 0 )
   		{
			ExcessPlayerVelocities[playerid] = 1;
			speedpl[playerid] = velocity;
		}
	}
	else if(velocity > 90)
	{
   		if(velocity >= 100 && SpecialBleep[nCarID[playerid]] == 0)//velocity>=100 &&
   		{
			ExcessPlayerVelocities[playerid] = 2;
   			speedpl[playerid] = velocity;
		}
	}
	//--------------------------------------------------------------------------
	//НАЧАЛО ВЫВОДА РАСТОЯНИЯ ДО РАДАРА
	new hypotenuse = 6000;//ширина всей карты
	for(new ir=0; ir<MAX_RADARS; ir++)
	{   //сканируем все радары без исключения
	  	//НАЧАЛО РАСЧЁТА РАСТОЯНИЯ ДО РАДАРА
		new range = floatround(GetPlayerDistanceFromPoint(playerid, aRadar[ir][radX],aRadar[ir][radY],aRadar[ir][radZ]));
		if(range < hypotenuse)
		{   //находим минимальное значение min(value1,value2)
			hypotenuse = range;//расстояние до ближайшего радара
			nearest[playerid] = ir;//записали ближайший радар
		}
	}
    if(hypotenuse < 450 && gHide[playerid] == true && TextDrawShowSpeed[playerid] == true
		// && (PlayerInfo[playerid][pAntiradar] == 1 ||
		//(PlayerInfo[playerid][pMember] == DoT && gOnDuty[playerid] == 1))
	  )
    {
       //DistanceToRadar(playerid, hypotenuse);
    }
	//==========================================================================
  	if(GaiRad[playerid] == 1)
  	{// && ExcessPlayerVelocities[playerid] != 0

//ИНФОРМИРОВАНИЕ
////new strings[MAX_STRING];
//format(strings, sizeof(strings), "расчёт штрафа по радару %d", nearest[playerid]);
//ABroadCast(COLOR_MAROON, strings, 6);
//SendAllAdminMessage(COLOR_RED, strings, 6);
		GaiRad[playerid] = 2;//переводим радар в режим ожидания сброса
		ExcessPlayerVelocities[playerid] = 0;//убрать превышение (убирается автоматически и ставится)

	  	new money;
		if((speedpl[playerid]-aRadar[nearest[playerid]][radSpeed]) >= 5 && (speedpl[playerid]-aRadar[nearest[playerid]][radSpeed]) < 15) money = 1*1*ticket_rate;//WantedLevel[playerid]=0
		else if((speedpl[playerid]-aRadar[nearest[playerid]][radSpeed]) >= 15  && (speedpl[playerid]-aRadar[nearest[playerid]][radSpeed]) < 30) money = 2*1*ticket_rate;
		else if((speedpl[playerid]-aRadar[nearest[playerid]][radSpeed]) >= 30)
		{//определяем величину штрафа
			money = 6*1*ticket_rate;
		}
		//----------------------------------------------------------------------
		//GivePlayerMoneyH(ffamily+DoT, playerid, -money);
		//new strtmp[71+2+2];
		if(money > 0
			//&& GetPlayerMoneyH(playerid) > 3*money
			)//если у игрока денег с запасом
		{// && PlayerInfo[playerid][Level] >= 5
			//if(money >= 1000) FinaceList(playerid, money, 0, ffamily+DoT);
			format(strtmp, sizeof(strtmp), "~b~+~g~%s$", NiceMoney(money));
			PlayerInfo[playerid][pCash] -= money;
			//PlaySoundForPlayer(playerid, SOUND_PART_MISSION_COMPLETE);
			//PlayAudioStreamForPlayerEx(playerid, "photo.wav");
			PlaySoundForPlayer(playerid, SOUND_CAMERA_SHOT);

			Blind(playerid);
			
			ResetPlayerMoney(playerid);
			gConsumingMoney[playerid] = 2;
			GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
			LastMoney[playerid] = PlayerInfo[playerid][pCash];
			//----------------------------------------------------------------------
			FamilyInfo[DoT][fBank] += money/2;
			if(BizInfo[0][bTill]+money < 2147480000) { BizInfo[0][bTill] += money/2; BizInfo[0][bExport] += money/2; }

			PlayerInfo[playerid][pTicket] ++;
//ИНФОРМИРОВАНИЕ
			/*format(strtmp, sizeof(strtmp), "Зарегистрировано превышение скорости: %d. Радар: %d. Ограничение: %d км/ч.",
				(speedpl[playerid]-aRadar[nearest[playerid]][radSpeed]), nearest[playerid], aRadar[nearest[playerid]][radSpeed]);
	    	SendClientMessage(playerid, COLOR_RED, strtmp);
			format(strtmp, sizeof(strtmp), "Ваша скорость: %d км/ч. Штраф: $%d", speedpl[playerid], money);
	    	SendClientMessage(playerid, COLOR_RED, strtmp);*/
	    	
   			//new strtmp2[43+3+10];//{FFFFFF}%s's{0080FF} по цене {33AA33}$%d
	    	format(PagerMessage, sizeof(PagerMessage), "Превышение скорости на %d км/ч. Штраф: $%d", (speedpl[playerid]-aRadar[nearest[playerid]][radSpeed]), money);
	    	SendPagerMessage(playerid);
		}
  	}
	return 1;
}


//для затемнения экрана
forward tHidePlayerBlind(playerid);
public tHidePlayerBlind(playerid)
{
	gTextDrawHideBlind[playerid] = true; OnPlayerTextDrawStateChange(playerid);
}

stock Blind(playerid)
{
	//PlayerTextDrawHide(playerid, txdBlind);
	TextDrawBoxColor(txdBlind,0xFFFFFF69);
	TextDrawBackgroundColor(txdBlind,0xFFFFFF69);
	TextDrawColor(txdBlind,0xFFFFFF69);
	//PlayerTextDrawShow(playerid, txdBlind);

	gTextDrawShowBlind[playerid] = true; OnPlayerTextDrawStateChange(playerid); //TextDrawShowForPlayer(playerid, Foto);
	SetTimerEx("RemoveBlind", 500, 1, "i", playerid);
}

forward RemoveBlind(playerid);
public RemoveBlind(playerid)
{
    //TextDrawHideForPlayer(playerid, Foto);
    gTextDrawHideBlind[playerid] = true; OnPlayerTextDrawStateChange(playerid);
    TextDrawBoxColor(txdBlind,0x000000FF);
    TextDrawColor(txdBlind,0x000000FF);
    return 1;
}

//stock PlayerTextDrawSetStringEx(playerid, PlayerText:text, string[])
stock DistanceToRadar(playerid, distance)
{
	if(distance >= 300)
	{
		//PlayerTextDrawColorEx(playerid, txdRADAR[playerid], COLOR_GREEN);
		PlayerTextDrawBackgroundColorEx(playerid, txdRADAR[playerid], 0x33AA3366);//0x000000FF//0xff000066
	}
	else if(distance >= 125 && distance < 300)//else if(hypotenuse >= 170 && hypotenuse < 290)
	{
		//PlayerTextDrawColorEx(playerid, txdRADAR[playerid], COLOR_YELLOW);
		PlayerTextDrawBackgroundColorEx(playerid, txdRADAR[playerid], 0xFFFF0066);
	}
	else if(distance < 125)//else if(hypotenuse < 170)
	{
		//PlayerTextDrawColorEx(playerid, txdRADAR[playerid], COLOR_RED);
		if((speedpl[playerid]-aRadar[nearest[playerid]][radSpeed]) >= 5)
		{
			PlayerTextDrawBackgroundColorEx(playerid, txdRADAR[playerid], 0xFF000066);
			PlaySoundForPlayer(playerid, SOUND_RADAR_LEVEL_WARNING);
			//PlayAudioStreamForPlayerEx(playerid, "antiradar.wav");
			//if( IsEvenNumber(hypotenuse) ) PlayAudioStreamForPlayerEx(playerid, "antiradar.wav");
		}
		else PlayerTextDrawBackgroundColorEx(playerid, txdRADAR[playerid], 0xFFFF0066);
	}
	new strtmp[71+2+2];
	format(strtmp, sizeof(strtmp), "%03d", distance);
	PlayerTextDrawSetStringEx(playerid, txdRADAR[playerid], strtmp);
}
