stock armsdealer_OnPlayerPickUp(playerid, pickupid)
{
	#pragma unused pickupid
	//--------------------------------------------------------------------------
	//else if( IsPlayerInRangeOfPoint(playerid, 2.1, 2419.8484,2778.5667,10.8203) )
	if( IsPlayerInRangeOfPoint(playerid, 2.1, 246.2071,1825.1620,7.5547) )
	{	//для оружейников STEP1 получение пакетов
		if(PlayerInfo[playerid][pJob] == ARMSDEALER && MatsHolding[playerid] == 0)
		{	//factory production Material
			//GameTextForPlayerEx(playerid, "~y~Welcome to the ~n~Factory~n~~b~Use (~w~/materials get~b~)~n~~g~to take a Materials Packages", 5000, 3);
			/*new index;
			for(new j=0, i; j<MaxPlayers; j++)	{
				i = PLIDs[j];
				if( !IsPlayerConnectedEx(i) ) continue;
				if(PlayerInfo[i][pMember] != DoD) continue;
				if(!IsPlayerInArea(i, specialzone[0])) continue;
				index++;
			}
			if(index < 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Вы не можете украсть материалы пока зона не охраняется!");
				return 1;
			}*/
			new level = PlayerInfo[playerid][pGunSkill];
			new package;//для экономики
			if(level < 50) { package = 60; }//цена 1 пакета
			else if(level >= 50 && level < 100) { package = 68; }
			else if(level >= 100 && level < 200) { package = 74; }
			else if(level >= 200 && level < 400) { package = 78; }
			else if(level >= 400) { package = 80; }//new amountmaterials = 30;//кол-во матеров в одном пакете
	        //if(MatsHolding[playerid] >= package)
	        //{
			//	SendClientMessage(playerid, COLOR_GREY, "   Вы не можете взять больше Пакетов с Материалами !");
			//	return 1;
	        //}

			//pricepackage*package - цена коробки
			//50*20=$4000 - цена коробки
			//amountmaterials*package - кол-во матеров к получке
			//30*30=900 материалов на 1 скиле
			//30*40=1200 матеров на 5 скиле
			//12 - кол-во рейсов за час
			//pricepackage/amountmaterials=7/30=2
			//0.23*900 = 207*12 - 1500(на топливо) = 984 ЗП в час на 1 скиле
			//0.23*1200 = 276*12 - 1500(на топливо) = 1812 ЗП в час на 1 скиле
			//new price = floatround((1.0+skill/(10.0))*pricematerials*PlayerInfo[playerid][pMats]) - pricepackage*package;

		    format(strings, sizeof(strings), "* Вы украли %d Пакетов с Материалами.", package);
		    SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

			checktimedeliver[playerid] = GetTickCount();
		    format(strings, sizeof(strings), "При доставке быстрее чем за %d секунд у вас обнулится скилл.", 60);//MinTimeCheckpoint[playerid]/1000);
		    SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);

		    //GivePlayerMoneyH(1, playerid, -price);//убрали т.к. оружейники счас воруют матеры, а не покупают
		    //SBizInfo[9][sbTill] += price/2;//перечислили деньги в биз General Store за покупку пакетов оружейников
		    //BizInfo[0][bProducts] += price/2;//перечислили деньги в БАНК
		    MatsHolding[playerid] = package;

		    if(MilitaryCounter > 1) FamilyInfo[DoD][fMaterial] -= MatsHolding[playerid];
			//else
			//{
			//    format(strings, sizeof(strings), "   У Вас нет $%d для получения %d пакетов с Материалами !", price, package);
			//    SendClientMessage(playerid, COLOR_GREY, strings);
			//}
			//GameTextForPlayerEx(playerid, "~w~Welcome to the ~~y~Factory~n~~g~You have got 10 Packages a Material", 5000, 3);
		}
		//return 1;
	}
	//else if(IsPlayerInRangeOfPoint(playerid, 3.0, -2119.5469,-178.5679,35.3203))
	else if( IsPlayerInRangeOfPoint(playerid, 2.1, -2185.6946,-262.7819,40.7195) )
	{   //для оружейников STEP2 сдача материалов
		if(PlayerInfo[playerid][pJob] == ARMSDEALER)
		{
			//GameTextForPlayerEx(playerid, "~y~Welcome to the Gun Plant~n~~b~Use (~w~/materials deliver~b~)~n~~g~to take a Materials for Gun", 5000, 3);
	        if(MatsHolding[playerid] > 0)
	        {
		        //верт 2 мин 57 сек
   				//if(PlayerInfo[playerid][pCarTime] > 0) { PlayerInfo[playerid][pGunSkill] = 0; PlayerInfo[playerid][pMats] = 0; }
   				if(GetTickCount() < (checktimedeliver[playerid]+60000) )// && !gAnticheat[playerid])
   				{//если игрок управился меньше чем за 60 секунд, т.е. 600 секунд ещё не прошло, а он уже снова на сдаче, то обнулить скил, т.к. это читер
					format(strings, sizeof(strings), "%s[%d] Reset GunSkill:%d Mats:%d checktimedeliver:%d[%d] sec",
						PlayerName(playerid),playerid, PlayerInfo[playerid][pGunSkill], PlayerInfo[playerid][pMats], (GetTickCount()-checktimedeliver[playerid])/1000, 60);
					Log(JOB, strings);
					PlayerInfo[playerid][pGunSkill] = 0;
					PlayerInfo[playerid][pMats] = 0;
					MatsHolding[playerid] = 0;
					SendClientMessage(playerid, COLOR_GREY, strings);
					return 1;
   				}
				//format(strings, sizeof(strings), "%s[%d] GunSkill:%d checktimedeliver:%d sec",
				//	PlayerName(playerid),playerid, PlayerInfo[playerid][pGunSkill], (GetTickCount()-checktimedeliver[playerid])/1000);
				//Log(JOB, strings);

	            new payout = amountmaterials*MatsHolding[playerid];//цена коробки 25*100=$2500 за amountmaterials*package = 50*25=1250 матеров
	            PlayerInfo[playerid][pMats] += payout;
	            format(strings, sizeof(strings), "* Завод передал Вам %d Материал(ов) за %d доставленных Пакетов с Материалами.", payout, MatsHolding[playerid]);
			    SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	            MatsHolding[playerid] = 0;
	        }
	        else SendClientMessage(playerid, COLOR_GREY, "   У вас нет больше Пакетов с Материалами !");
 			GameTextForPlayerEx(playerid, "~w~Welcome to the ~y~Gun Plant~n~~g~You have got Material for Weapons", 5000, 3);
		}
	}
	return 1;
}


stock armsdealer_OnPlayerDeath(playerid, killerid)
{
	if(	PlayerInfo[killerid][pJob] == ARMSDEALER &&
		IsPlayerInArea(killerid, specialzone[0]) &&
		IsPlayerInRangeOfPlayer(30.0, killerid, playerid) &&//при смерти расстояние другое
		PlayerInfo[playerid][pMember] == DoD && gOnDuty[playerid] )
	{
		SetPVarInt(killerid, "PlayerID", playerid);
		ShowPlayerDialogGap(killerid, SKINS_DIALOG, DIALOG_STYLE_MSGBOX, "СЕРВЕР", "Вы хотите переодеться в военную форму?\
\n\n{AFAFAF}Нажмите Accept, если согласны.", "Accept", "Cancel");
	}
	if(PlayerInfo[playerid][pJob] == ARMSDEALER && MatsHolding[playerid] > 0)
	{
		//SetPlayerSkinEx(killerid, PlayerInfo[playerid][pChar]);
		//PlayerInfo[playerid][pChar] = PlayerInfo[playerid][pModel];
		FamilyInfo[DoD][fMaterial] += MatsHolding[playerid];
		MatsHolding[playerid] = 0;
	}
}

