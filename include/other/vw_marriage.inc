//для свадьбы
new DivorceOffer[MAX_PLAYERS];//id предложившего быть свидетелм расторжения брака
new gMarriageCeremoney[MAX_PLAYERS];
new ProposeOffer[MAX_PLAYERS];//id Предложившего Вам Брак
new ProposedTo[MAX_PLAYERS];//id Принявшего Предложение Брака
new GotProposedBy[MAX_PLAYERS];
new MarryWitness[MAX_PLAYERS];
new MarryWitnessOffer[MAX_PLAYERS];



stock marriage_OnPlayerConnect(playerid)
{

//для свадьбы
	MarryWitness[playerid] = MAX_PLAYERS-1; MarryWitnessOffer[playerid] = MAX_PLAYERS-1; gMarriageCeremoney[playerid] = 0;
	GotProposedBy[playerid] = MAX_PLAYERS-1; DivorceOffer[playerid] = MAX_PLAYERS-1;
	ProposeOffer[playerid] = MAX_PLAYERS-1; ProposedTo[playerid] = MAX_PLAYERS-1;
}


stock marriage_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	if(dialogid != MARRIAGE_DIALOG) return 1;//ACCEPT_DIALOG
	new msgitem[256+1];
	if(!response)
	{
		iOfferTime[Offer[playerid]] = GetTickCount();
		iOfferTime[playerid] = GetTickCount();
		Offer[playerid] = MAX_PLAYERS-1;

		DrugPrice[playerid] = 0;
		DrugGram[playerid] = 0;

		GunPrice[playerid] = 0;
		OfferWeapon[playerid] = 0;
		OfferAmmo[playerid] = 0;
		GunMat[playerid] = 0;

		CarPrice[playerid] = 0;
		MarryWitnessOffer[playerid] = MAX_PLAYERS-1;
		if(ProposeOffer[playerid] < MAX_PLAYERS-1) MarryWitness[ProposeOffer[playerid]] = MAX_PLAYERS-1;
		ProposeOffer[playerid] = MAX_PLAYERS-1;
		if(Offer[playerid] < MAX_PLAYERS-1) gGotOrder[Offer[playerid]] = MAX_PLAYERS-1;
		TicketMoney[playerid] = 0;
		PaperPrice[playerid] = 0;

		format(msgitem, sizeof(msgitem), "%s отказался от предложенной услуги !!", PlayerName(playerid));
		ProxDetector(playerid, 30.0, msgitem, COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC,COLOR_LILAC);
		MenuOperation[playerid] = 0;
	 	return 1;
	}
	new giveplayerid;
	if(MenuOperation[playerid] == 15)
	//else if(!strcmp(x_job, "witness", true))
	{   // accept
	    if(MarryWitnessOffer[playerid] >= MAX_PLAYERS-1)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Нет Предложившего Вам быть Свидетелем Брака !");
		    return 1;
		}
        if(IsPlayerConnected(MarryWitnessOffer[playerid]))
        {
			if(!IsPlayerInRangeOfPlayer(8.0, playerid, MarryWitnessOffer[playerid])
				|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[MarryWitnessOffer[playerid]] != MAX_PLAYERS-1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");
				return 1;
			}
			format(msgitem, sizeof(msgitem), "* Вы приняли просьбу %s'а, быть Свидетелем его Брака.", PlayerName(MarryWitnessOffer[playerid]));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
			format(msgitem, sizeof(msgitem), "* %s принял просьбу, быть Свидетелем вашего Брака.", PlayerName(playerid));
			SendClientMessage(MarryWitnessOffer[playerid], COLOR_LIGHTBLUE, msgitem);
			MarryWitness[MarryWitnessOffer[playerid]] = playerid;
			MarryWitnessOffer[playerid] = MAX_PLAYERS-1;
		}
	}
	else if(MenuOperation[playerid] == 16)
    //else if(!strcmp(x_job, "propose", true))//для свадьбы
	{   // accept
	    if(ProposeOffer[playerid] >= MAX_PLAYERS-1)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Нет Предложившего Вам Брак!");
		    return 1;
		}
        if(	!IsPlayerInRangeOfPoint(playerid, 10.0, -1988.6638,1117.8837,54.4726) &&
			!IsPlayerInRangeOfPoint(playerid, 10.0, 2489.9905,918.4443,11.0234) &&
			!IsPlayerInRangeOfPoint(playerid, 10.0, -2482.3279,2406.4053,17.1094))
        {
            SendClientMessage(playerid, COLOR_GREY, "   Вы - не около Церкви. (USE: /gps).");//Church
            return 1;
        }
        if(IsPlayerConnected(ProposeOffer[playerid]))
        {
			if(!IsPlayerInRangeOfPlayer(8.0, playerid, ProposeOffer[playerid])
				|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[ProposeOffer[playerid]] != MAX_PLAYERS-1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");
				return 1;
			}
		    if(MarryWitness[ProposeOffer[playerid]] == MAX_PLAYERS-1)
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   Заявитель не имеет Свидетеля Брака !");
		        return 1;
		    }
		    if(IsPlayerConnected(MarryWitness[ProposeOffer[playerid]]))
		    {
			    if(IsPlayerInRangeOfPlayer(12.0, ProposeOffer[playerid], MarryWitness[ProposeOffer[playerid]]))
				{
					format(msgitem, sizeof(msgitem), "* Вы приняли предложение %s'а, быть вашим Мужем.", PlayerName(ProposeOffer[playerid]));
					SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
					format(msgitem, sizeof(msgitem), "* %s приняла ваше предложение, стать вашей Женой.", PlayerName(playerid));
					SendClientMessage(ProposeOffer[playerid], COLOR_LIGHTBLUE, msgitem);
					format(msgitem, sizeof(msgitem), "Cвященник: %s берёти ли вы %s'а в мужья? (наберите 'yes', другое отвергнет Брак)",
						PlayerName(playerid), PlayerName(ProposeOffer[playerid]));
					SendClientMessage(playerid, COLOR_WHITE, msgitem);
					gMarriageCeremoney[playerid] = 1;
					ProposedTo[ProposeOffer[playerid]] = playerid;
					GotProposedBy[playerid] = ProposeOffer[playerid];
					MarryWitness[ProposeOffer[playerid]] = MAX_PLAYERS-1;
					ProposeOffer[playerid] = MAX_PLAYERS-1;
					return 1;
				}
				else
				{
				    SendClientMessage(playerid, COLOR_GREY, "   Свидетель Брака - не около заявителя !");
				    return 1;
				}
			}
		}
	}
	else if(MenuOperation[playerid] == 17)
	//else if(!strcmp(x_job, "divorce", true))
	{
	    if(DivorceOffer[playerid] >= MAX_PLAYERS-1)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   Нет Предложившего Вам быть Свидетелем Расторжения Брака !");
		    return 1;
		}
        if(IsPlayerConnected(DivorceOffer[playerid]))
        {
			if(!IsPlayerInRangeOfPlayer(8.0, playerid, DivorceOffer[playerid])
				|| spectateid[playerid] != MAX_PLAYERS-1 || spectateid[DivorceOffer[playerid]] != MAX_PLAYERS-1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Этот игрок не рядом с Вами !");
				return 1;
			}
			format(msgitem, sizeof(msgitem), "* Вы приняли просьбу %s'а, быть Свидетелем Расторжения его Брака.", PlayerName(DivorceOffer[playerid]));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
			format(msgitem, sizeof(msgitem), "* %s принял просьбу, быть Свидетелем Расторжения вашего Брака.", PlayerName(playerid));
			SendClientMessage(DivorceOffer[playerid], COLOR_LIGHTBLUE, msgitem);
			ClearMarriage(playerid);
			ClearMarriage(DivorceOffer[playerid]);
		}
	}
	return 1;
}
