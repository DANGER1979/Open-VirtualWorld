stock PlayerInfoMenu(playerid, forplayerid)
{//главная задача просмотр в игре параметров с возможностью править особых
    SetPVarInt(playerid, "ForPlayerID", forplayerid);
	new caption[70+1];
    format(caption, sizeof(caption), "Вы выбрали игрока %s[%d]", PlayerName(forplayerid), forplayerid);
	new listitems[158*20 + 158*3];//1712
	new strtmp[25+6*3];
	//strcat(listitems, "Параметр\tЗначение\n");
	format(strtmp, sizeof(strtmp), 	"1.IP:\t%s\n", PlayerInfo[playerid][pIP]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"2.Sex:\t%d\n", PlayerInfo[playerid][pSex]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"3.Age:\t%s\n", PlayerInfo[playerid][pAge]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"4.Origin:\t%d\n", PlayerInfo[playerid][pOrigin]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"5.DepositDay:\t%d\n", PlayerInfo[playerid][pDepositDay]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"6.Level:\t%d\n", PlayerInfo[playerid][pLevel]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"7.AdminLevel:\t%d\n", PlayerInfo[playerid][pAdmin]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"8.Account:\t%d\n", PlayerInfo[playerid][pAccount]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"9.Muted:\t%d\n", PlayerInfo[playerid][pMuted]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"10.Warns:\t%d\n", PlayerInfo[playerid][pWarns]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"11.ConnectTime:\t%d\n", PlayerInfo[playerid][pConnectTime]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"12.Respect:\t%d\n", PlayerInfo[playerid][pRespect]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"13.RespectDay:\t%d\n", PlayerInfo[playerid][pRespectDay]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"14.PayCheck:\t%d\n", PlayerInfo[playerid][pPayCheck]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"15.PayDay:\t%d\n", PlayerInfo[playerid][pPayTime]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"16.Deposit:\t%d\n", PlayerInfo[playerid][pDeposit]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"17.Cash:\t%d\n", PlayerInfo[playerid][pCash]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"18.Bank:\t%d\n", PlayerInfo[playerid][pBank]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"19.Gold:\t%d\n", PlayerInfo[playerid][pGold]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"20.SHealth:\t%.1f\n", PlayerInfo[playerid][pSHealth]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"21.Health:\t%.1f\n", PlayerInfo[playerid][pHealth]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"22.Interior:\t%d\n", PlayerInfo[playerid][pInt]);	strcat(listitems, strtmp);
//чтобы смотреть с какими координатами игрок будет входить в игру
	format(strtmp, sizeof(strtmp), 	"23.Pos_x:\t%.3f\n", PlayerInfo[playerid][pPos_x]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"24.Pos_y:\t%.3f\n", PlayerInfo[playerid][pPos_y]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"25.Pos_z:\t%.3f\n", PlayerInfo[playerid][pPos_z]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"26.Virtual:\t%d\n", PlayerInfo[playerid][pVirtual]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"27.Local:\t%d\n", PlayerInfo[playerid][pLocal]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"28.House:\t%d\n", PlayerInfo[playerid][pHouse]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"29.Bizz:\t%d\n", PlayerInfo[playerid][pBizz]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"30.Job:\t%d\n", PlayerInfo[playerid][pJob]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"31.Team:\t%d\n", PlayerInfo[playerid][pTeam]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"32.Member:\t%d\n", PlayerInfo[playerid][pMember]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"33.Leader:\t%d\n", PlayerInfo[playerid][pLeader]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"34.Rank:\t%d\n", PlayerInfo[playerid][pRank]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"35.Char:\t%d\n", PlayerInfo[playerid][pChar]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"36.Model:\t%d\n", PlayerInfo[playerid][pModel]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"37.ContractTime:\t%d\n", PlayerInfo[playerid][pContractTime]);	strcat(listitems, strtmp);
	
/* просматривается через SkillInfo(playerid)
	format(strtmp, sizeof(strtmp), 	"37.MinerSkill:\t%d\n", PlayerInfo[playerid][pMinerSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"38.LawSkill:\t%d\n", PlayerInfo[playerid][pLawSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"39.RoadSkill:\t%d\n", PlayerInfo[playerid][pRoadSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"40.DrugsSkill:\t%d\n", PlayerInfo[playerid][pDrugsSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"41.JackSkill:\t%d\n", PlayerInfo[playerid][pJackSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"42.ProfSkill:\t%d\n", PlayerInfo[playerid][pProfSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"43.MechSkill:\t%d\n", PlayerInfo[playerid][pMechSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"44.FarmSkill:\t%d\n", PlayerInfo[playerid][pFarmSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"45.GunSkill:\t%d\n", PlayerInfo[playerid][pGunSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"46.CarSkill:\t%d\n", PlayerInfo[playerid][pCarSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"47.InkasSkill:\t%d\n", PlayerInfo[playerid][pInkasSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"48.BookmakerSkill:\t%d\n", PlayerInfo[playerid][pBookmakerSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"49.TaxiSkill:\t%d\n", PlayerInfo[playerid][pTaxiSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"50.BusSkill:\t%d\n", PlayerInfo[playerid][pBusSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"51.CourierSkill:\t%d\n", PlayerInfo[playerid][pCourierSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"52.TruckSkill:\t%d\n", PlayerInfo[playerid][pTruckSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"53.TrashSkill:\t%d\n", PlayerInfo[playerid][pTrashSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"54.LoadSkill:\t%d\n", PlayerInfo[playerid][pLoadSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"55.WoodSkill:\t%d\n", PlayerInfo[playerid][pWoodSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"56.FishSkill:\t%d\n", PlayerInfo[playerid][pFishSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"57.FireSkill:\t%d\n", PlayerInfo[playerid][pFireSkill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"58.CookSkill:\t%d\n", PlayerInfo[playerid][pCookSkill]);	strcat(listitems, strtmp);
*/
	format(strtmp, sizeof(strtmp), 	"59.CarLic:\t%d\n", PlayerInfo[playerid][pCarLic]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"60.BikeLic:\t%d\n", PlayerInfo[playerid][pBikeLic]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"61.FlyLic:\t%d\n", PlayerInfo[playerid][pFlyLic]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"62.BoatLic:\t%d\n", PlayerInfo[playerid][pBoatLic]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"63.FishLic:\t%d\n", PlayerInfo[playerid][pFishLic]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"64.GunLic:\t%d\n", PlayerInfo[playerid][pGunLic]);	strcat(listitems, strtmp);

	format(strtmp, sizeof(strtmp), 	"65.Gun1:\t%d\n", PlayerInfo[playerid][pGun1]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"66.Ammo1:\t%d\n", PlayerInfo[playerid][pAmmo1]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"67.Gun2:\t%d\n", PlayerInfo[playerid][pGun2]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"68.Ammo2:\t%d\n", PlayerInfo[playerid][pAmmo2]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"69.Gun3:\t%d\n", PlayerInfo[playerid][pGun3]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"70.Ammo3:\t%d\n", PlayerInfo[playerid][pAmmo3]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"71.Gun4:\t%d\n", PlayerInfo[playerid][pGun4]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"72.Ammo4:\t%d\n", PlayerInfo[playerid][pAmmo4]);	strcat(listitems, strtmp);
	
	format(strtmp, sizeof(strtmp), 	"73.Gun22Skill:\t%d\n", PlayerInfo[playerid][pGun22Skill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"74.Gun23Skill:\t%d\n", PlayerInfo[playerid][pGun23Skill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"75.Gun24Skill:\t%d\n", PlayerInfo[playerid][pGun24Skill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"76.Gun25Skill:\t%d\n", PlayerInfo[playerid][pGun25Skill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"77.Gun26Skill:\t%d\n", PlayerInfo[playerid][pGun26Skill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"78.Gun27Skill:\t%d\n", PlayerInfo[playerid][pGun27Skill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"79.Gun28Skill:\t%d\n", PlayerInfo[playerid][pGun28Skill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"80.Gun29Skill:\t%d\n", PlayerInfo[playerid][pGun29Skill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"81.Gun30Skill:\t%d\n", PlayerInfo[playerid][pGun30Skill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"82.Gun31Skill:\t%d\n", PlayerInfo[playerid][pGun31Skill]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"83.Gun34Skill:\t%d\n", PlayerInfo[playerid][pGun34Skill]);	strcat(listitems, strtmp);
	
	format(strtmp, sizeof(strtmp), 	"84.HeadValue:\t%d\n", PlayerInfo[playerid][pHeadValue]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"85.Wins:\t%d\n", PlayerInfo[playerid][pWins]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"86.Loses:\t%d\n", PlayerInfo[playerid][pLoses]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"87.Kills:\t%d\n", PlayerInfo[playerid][pKills]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"88.Deaths:\t%d\n", PlayerInfo[playerid][pDeaths]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"89.Accident:\t%d\n", PlayerInfo[playerid][pAccident]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"90.Ticket:\t%d\n", PlayerInfo[playerid][pTicket]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"91.Crimes:\t%d\n", PlayerInfo[playerid][pCrimes]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"92.Arrested:\t%d\n", PlayerInfo[playerid][pArrested]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"93.WantedDeaths:\t%d\n", PlayerInfo[playerid][pWantedDeaths]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"94.Wanted:\t%d\n",  WantedPoints[playerid]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"95.Article:\t%d\n", PlayerInfo[playerid][pArticle]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"96.Part:\t%d\n", PlayerInfo[playerid][pPart]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"97.Jailed:\t%d\n", PlayerInfo[playerid][pJailed]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"98.JailTime:\t%d\n", PlayerInfo[playerid][pJailTime]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"99.JailPrice:\t%d\n", PlayerInfo[playerid][pJailPrice]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"100.UpgradePoints:\t%d\n", PlayerInfo[playerid][pPupgrade]);	strcat(listitems, strtmp);

//перки
	format(strtmp, sizeof(strtmp), 	"101.pAlcohol:\t%d\n", PlayerInfo[playerid][pAlcoholPerk]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"102.pDrug:\t%d\n", PlayerInfo[playerid][pDrugPerk]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"103.pMiser:\t%d\n", PlayerInfo[playerid][pMiserPerk]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"104.pPain:\t%d\n", PlayerInfo[playerid][pPainPerk]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"105.pTrader:\t%d\n", PlayerInfo[playerid][pTraderPerk]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"106.pHunger:\t%d\n", PlayerInfo[playerid][pHunger]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"107.pLeisure:\t%d\n", PlayerInfo[playerid][pLeisure]);	strcat(listitems, strtmp);//досуг
	format(strtmp, sizeof(strtmp), 	"108.pContact:\t%d\n", PlayerInfo[playerid][pContact]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"109.pToilet:\t%d\n", PlayerInfo[playerid][pToilet]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"110.pVigour:\t%d\n", PlayerInfo[playerid][pVigour]);	strcat(listitems, strtmp);

	format(strtmp, sizeof(strtmp), 	"111.STD:\t%d\n", PlayerInfo[playerid][pSTD]);	strcat(listitems, strtmp);

/*//инвентарь см. Items(playerid)
	format(strtmp, sizeof(strtmp), 	"112.pDice:\t%d\n", PlayerInfo[playerid][pDice]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"113.pCigars:\t%d\n", PlayerInfo[playerid][pCigars]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"114.gChickens:\t%d\n", Groceries[playerid][gChickens]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"115.gHamburgers:\t%d\n", Groceries[playerid][gHamburgers]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"116.gPizzas:\t%d\n", Groceries[playerid][gPizzas]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"117.pFishes:\t%d\n", PlayerInfo[playerid][pFishes]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"118.pAdrenalin:\t%d\n", PlayerInfo[playerid][pAdrenalin]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"119.gBeer:\t%d\n", Groceries[playerid][gBeer]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"120.pAntiradar::\t%d\n", PlayerInfo[playerid][pAntiradar]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"121.pGPS:\t%d\n", PlayerInfo[playerid][pGPS]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"122.pCDPlayer:\t%d\n", PlayerInfo[playerid][pCDPlayer]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"123.pFuel:\t%d\n", PlayerInfo[playerid][pFuel]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"124.Dice:\t%d\n", PlayerInfo[playerid][pDice]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"125.Drugs:\t%d\n", PlayerInfo[playerid][pDrugs]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"126.Cigars:\t%d\n", PlayerInfo[playerid][pCigars]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"127.Fishes:\t%d\n", PlayerInfo[playerid][pFishes]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"128.Fuel:\t%d\n", PlayerInfo[playerid][pFuel]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"129.LottoNr:\t%d\n", PlayerInfo[playerid][pLottoNr]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"130.Materials:\t%d\n", PlayerInfo[playerid][pMats]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"131.Mushroom:\t%d\n", PlayerInfo[playerid][pMushroom]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"132.PhoneNr:\t%d\n", PlayerInfo[playerid][pPnumber]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"133.Helmet:\t%d\n", PlayerInfo[playerid][pHelmet]);	strcat(listitems, strtmp);
*/
	format(strtmp, sizeof(strtmp), 	"134.Married:\t%d\n", PlayerInfo[playerid][pMarried]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"135.Offline:\t%d\n", PlayerInfo[playerid][pOffline]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"136.Reason:\t%d\n", 	PlayerInfo[playerid][pReason]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"137.CarTime:\t%d\n", PlayerInfo[playerid][pCarTime]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"138.Tutorial:\t%d\n", PlayerInfo[playerid][pTut]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"139.Vote:\t%d\n", 	PlayerInfo[playerid][pVote]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"140.PurposeMurder:\t%d\n", PlayerInfo[playerid][pPurposeMurder]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"141.Referal:\t%s\n", PlayerInfo[playerid][pReferal]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"142.Online:\t%d\n", 	PlayerInfo[playerid][pOnline]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"143.Score:\t%d\n", 	PlayerInfo[playerid][pScore]);	strcat(listitems, strtmp);
//потребности
	format(strtmp, sizeof(strtmp), 	"144.Param1:\t%d\n", 	PlayerInfo[playerid][pParam1]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"145.Param2:\t%d\n", 	PlayerInfo[playerid][pParam2]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"146.Param3:\t%d\n", 	PlayerInfo[playerid][pParam3]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"147.Param4:\t%d\n", 	PlayerInfo[playerid][pParam4]);	strcat(listitems, strtmp);
	format(strtmp, sizeof(strtmp), 	"158.Param5:\t%d\n", 	PlayerInfo[playerid][pParam5]);	strcat(listitems, strtmp);

	if( strlen(listitems) > sizeof(listitems) )
	{
		format(strings, sizeof(strings), "AdmWarning:\t strlen(info):\t%d > sizeof(listitems):\t%d", strlen(listitems), sizeof(listitems));
		SendAllAdminMessage(COLOR_MAROON, strings, 3);
	 	return 1;
	}
	if( strlen(caption) > sizeof(caption) )
	{
		format(strings, sizeof(strings), "AdmWarning:\t strlen(caption):\t%d > sizeof(caption):\t%d", strlen(caption), sizeof(caption));
		SendAllAdminMessage(COLOR_MAROON, strings, 3);
	 	return 1;
	}
	ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_TABLIST, caption, listitems, "Ок", "Назад");
	return 1;
}



stock PlayerInfoMenu_DialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//#pragma unused listitem
	//#pragma unused inputtext
	if(dialogid != PLAYERINFO_DIALOG) return 1;// && dialogid != H_DIALOG
	if(!response)
	{
		DeletePVar(playerid, "Action");
		/*DeletePVar(playerid, "InputValue");
		DeletePVar(playerid, "InputCounter");
		DeletePVar(playerid, "ForPlayerID");*/
		new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
		admin_OnPlayerClick(playerid, giveplayerid);
		return 1;
	}
	new msgitem[256+1];
	new strcmd[MAX_STRING];
	new Float:pX, Float:pY, Float:pZ, Float:pA; //new Float:ang;
	//new Float:vX, Float:vY, Float:vZ;//, Float:vA;
	new giveplayerid = GetPVarInt(playerid, "ForPlayerID");
	/*if(!IsPlayerAdmin(playerid))
	{
		SendClientMessage(playerid, COLOR_GREY, "   Вы не уполномочены использовать эту команду !");
		return 1;
	}*/

	/*if(CHECKING == 1)
	{//ИНФОРМИРОВАНИЕ
	format(strings, sizeof(strings), "admin_OnDialogResponse(playerid:%d, giveplayerid:%d, \
Action:%d, InputCounter:%d) InputValue:%d",
playerid, giveplayerid,
GetPVarInt(playerid, "Action"), GetPVarInt(playerid, "InputCounter"), strval(inputtext));
GetPVarInt(playerid, "InputValue"), GetPVarInt(giveplayerid, "InputValue"));
	SendClientMessage(playerid, COLOR_PURPLE, strings);
	}*/
//==============================================================================
	if(GetPVarInt(playerid, "Action") == 0)
	{//если операция ещё не выбрана, т.е. это ввод первого параметра
	    //не забыть обнулить при окончанию ввода параметров
		//if(dialogid == DEVELOPER_DIALOG)
		SetPVarInt(playerid, "Action", listitem+1);//записали выбранную операцию
		DeletePVar(playerid, "InputCounter");//очистили от предыдущих операций
	}
	new operation = GetPVarInt(playerid, "Action");
//------------------------------------------------------------------------------
	if(operation == 2)//Установить пол
	{//2.Sex:\t%d\n
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение 1(М) или 2(Ж). \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || (strval(inputtext) != 1 && strval(inputtext) != 2))
			{
				ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение 1(М) или 2(Ж). \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			new Sex = strval(inputtext);
			PlayerInfo[giveplayerid][pSex] = Sex;

			format(strcmd, sizeof(strcmd), "*  Bы установили %s пол %d.",  PlayerName(giveplayerid), Sex);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
			format(strcmd, sizeof(strcmd), "AdmCmd: %s has %s's set to Sex %d.", PlayerName(playerid), PlayerName(giveplayerid), Sex);
   			Log(ADMINLOG, strcmd);

			DeletePVar(playerid, "Action");
		}
	}
	else if(operation == 6)//Level:
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 1 до 50. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 1 || strval(inputtext) > 50)
			{
				ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 50. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			new level = strval(inputtext);
			PlayerInfo[giveplayerid][pLevel] = level;
			DollahScoreUpdate(giveplayerid);

			format(strcmd, sizeof(strcmd), "*  Bы установили %s уровень %d.",  PlayerName(giveplayerid), level);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
			format(strcmd, sizeof(strcmd), "AdmCmd: %s has %s's set to level %d.", PlayerName(playerid), PlayerName(giveplayerid), level);
   			Log(ADMINLOG, strcmd);

			DeletePVar(playerid, "Action");
		}
	}
	else if(operation == 7)//AdminLevel
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 10. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 10)
			{
				ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 10. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
/*#if defined vw_sql//#endif
			new ToBase[64+24+2];
			format(ToBase, sizeof(ToBase), "SELECT `IND` FROM `blacklist` WHERE `Player`='%s' AND Family=%d", playername, DoE+1);
			mysql_query(ToBase); mysql_store_result();
			if(mysql_num_rows() > 0)
		 	{
				mysql_free_result();
	       		SendClientMessage(playerid, COLOR_GREY, "   Нельзя назначать игроков находящихся в Админском Чёрном Списке !");
				return 1;
			}
			format(ToBase, sizeof(ToBase), "UPDATE `players` SET `AdminLevel`=%d WHERE `Name`='%s'", PlayerInfo[giveplayerid][pAdmin], PlayerName(giveplayerid));
			mysql_query(ToBase);
			mysql_free_result();
#endif*/

			new level = strval(inputtext);
			PlayerInfo[giveplayerid][pAdmin] = level;

			format(strcmd, sizeof(strcmd), "*  Bы повысили %s до уровня %d администрирования.",  PlayerName(giveplayerid), level);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
			format(strcmd, sizeof(strcmd), "AdmCmd: %s has promoted %s's to a level %d admin.", PlayerName(playerid), PlayerName(giveplayerid), level);
   			Log(ADMINLOG, strcmd);
   			
			DeletePVar(playerid, "Action");
		}
	}
	else if(operation == 22)//Interior
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 18. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 18)
			{
				ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 18. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			new interiorid = strval(inputtext);
			if( IsPlayerInAnyVehicle(giveplayerid) )
			{
				SetPlayerInteriorEx(giveplayerid, interiorid);
				LinkVehicleToInteriorEx(nCarID[giveplayerid], interiorid);
			}
			else SetPlayerInteriorEx(giveplayerid, interiorid);

			PlayerInfo[giveplayerid][pInt] = interiorid;
			format(strcmd, sizeof(strcmd), "Aдмин %s установил Вам интерьер %d.", PlayerName(playerid), interiorid);
			SendClientMessage(giveplayerid, COLOR_RED, strcmd);
			format(strcmd, sizeof(strcmd), "AdmCmd: %s установил %s'у интерьер %d.", PlayerName(playerid), PlayerName(giveplayerid), interiorid);
			//Log(ADMINLOG, strcmd);
			SendAllAdminMessage(COLOR_RED, strcmd, 6);

			DeletePVar(playerid, "Action");
		}
	}
	else if(operation == 23)//Установить позицию
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			//new Float:pX, Float:pY, Float:pZ, Float:pA;
			/*if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 100)
			{
				ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}*/
			new Array[4][MAX_STRING];//40
			new idx;
			Array[0] = strtoko(inputtext, idx, ',');
			if(!strlen(Array[0]))
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: X,Y,Z,Ang");//,[Ang]
				return 1;
			}
			pX = floatstr(Array[0]);//Конвертирует строку в соответствующее вещественное число.

			Array[1] = strtoko(inputtext, idx, ',');
			if(!strlen(Array[1]))
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: X,Y,Z,Ang");//,[Ang]
				return 1;
			}
			pY = floatstr(Array[1]);

			Array[2] = strtoko(inputtext, idx, ',');
			if(!strlen(Array[2]))
			{
				SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: X,Y,Z,Ang");//,[Ang]
				return 1;
			}
			pZ = floatstr(Array[2]);

			Array[3] = strtoko(inputtext, idx, ',');
			pA = floatstr(Array[3]);

			//format(strcmd, sizeof(strcmd), "SetAngle(%d, %.4f)", playerid, Ang);
			//SendClientMessage(playerid, COLOR_GRAYWHITE, strcmd);

			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				SetVehiclePosEx(GetPlayerVehicleID(giveplayerid), pX, pY, pZ);
			}
			else
			{
				SetPlayerPosEx(playerid, pX, pY, pZ, pA);
				//SetPlayerPosFindZ(giveplayerid, pX, pY, pZ);
			}

 			//format(strcmd, sizeof(strcmd), "SetPos(%d, %.4f, %.4f, %.4f)", giveplayerid, pX, pY, pZ);
			//SendClientMessage(playerid, COLOR_GRAYWHITE, strcmd);

			format(msgitem, sizeof(msgitem), "AdmCmd: %s set %s's SetPos(%d, %.4f, %.4f, %.4f)", PlayerName(playerid), PlayerName(giveplayerid), giveplayerid, pX, pY, pZ);
			//Log(ADMINLOG, msgitem);
			//ABroadCast(COLOR_RED, msgitem, 9);
			SendClientMessage(playerid, ADMINS_MESSAGE_COLOR, msgitem);

	    	//SendClientMessage(playerid, COLOR_LIGHTBLUE, "   Вы телепорнули игрока по новым координатам !");
			DeletePVar(playerid, "Action");
		}
	}
	
	else if(operation == 26)//26.Virtual:
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 999. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 999)
			{
				ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 999. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			new virtualid = strval(inputtext);
			if( IsPlayerInAnyVehicle(giveplayerid) )
			{
				SetPlayerVirtualWorldEx(giveplayerid, virtualid);
				SetVehicleVirtualWorldEx(nCarID[giveplayerid],virtualid);
			}
			else SetPlayerVirtualWorldEx(giveplayerid, virtualid);
			PlayerInfo[giveplayerid][pVirtual] = virtualid;
			//SetPlayerWeather(giveplayerid,8);
			format(strcmd, sizeof(strcmd), "Aдмин %s отправил Вас в паралельный мир.", PlayerName(playerid));
			SendClientMessage(giveplayerid, COLOR_RED, strcmd);
			format(strcmd, sizeof(strcmd), "Aдмин %s отправил %s'a в мир %d-й", PlayerName(playerid), PlayerName(giveplayerid), virtualid);
			//Log(ADMINLOG, strcmd);
			SendAllAdminMessage(COLOR_RED, strcmd, 6);

			DeletePVar(playerid, "Action");
		}
	}
	else if(operation == 27)//27.Local
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 999. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 999)
			{
				ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 999. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			new location = strval(inputtext);
			PlayerInfo[playerid][pLocal] = location;
			format(strcmd, sizeof(strcmd), "Aдмин %s установил %s'у локацию %d", PlayerName(playerid), PlayerName(giveplayerid), location);
			SendClientMessage(giveplayerid, COLOR_RED, strcmd);
			//Log(ADMINLOG, strcmd);
			SendAllAdminMessage(COLOR_RED, strcmd, 6);
			
			DeletePVar(playerid, "Action");
		}
	}
	else if(operation == 30)//30.Job:
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{
			ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 23. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > 23)
			{
				ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до 23. \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			
			PlayerInfo[giveplayerid][pJob] = strval(inputtext);
			gJobDuty[giveplayerid] = 0;
			FixJobCounter(giveplayerid);

			format(strcmd, sizeof(strcmd), "AdmCmd: %s set Job for %s's to %d", PlayerName(playerid), PlayerName(giveplayerid), PlayerInfo[giveplayerid][pJob]);
	  		Log(ADMINLOG, strcmd);
			SendAllAdminMessage(ADMINS_MESSAGE_COLOR, strcmd, 6);

			DeletePVar(playerid, "Action");
		}
	}
	else if(operation == 32)//32.Member
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{//SendClientMessage(playerid, COLOR_GREY, "Hомер может быть от "#TEAM_GROVE" до "#DoE"! Сделать гражданским: 0 !");
			ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до "#DoE". \nСделать гражданским: 0\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");

			SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Grove Street("#TEAM_GROVE"), The Ballas("#TEAM_BALLAS"), Varios Los Aztecas("#TEAM_AZTEC"), Los Santos Vagos("#TEAM_VAGOS")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Da Nang Boys("#TEAM_NANG"), San Fierro Rifa("#TEAM_RIFA "), The Traids("#TEAM_TRIAD"), Bikers("#TEAM_BIKER"), The Mafia("#TEAM_MAFIA")");

			SendClientMessage(playerid, COLOR_GRAYWHITE, "Депортамент: DoT("#DoT"), FBI("#FBI"), DoD("#DoD"), DoH("#DoH"), DoJ("#DoJ"), DoE("#DoE")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Семьи: LaCosaNostra("#LCN"), Yakuza("#Yakuza")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Агентства: Hitman("#Hitman"), SAN("#SAN")");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > DoE)
			{
				ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от "#TEAM_GROVE" до "#DoE". \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");

				SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Grove Street("#TEAM_GROVE"), The Ballas("#TEAM_BALLAS"), Varios Los Aztecas("#TEAM_AZTEC"), Los Santos Vagos("#TEAM_VAGOS")");
				SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Da Nang Boys("#TEAM_NANG"), San Fierro Rifa("#TEAM_RIFA "), The Traids("#TEAM_TRIAD"), Bikers("#TEAM_BIKER"), The Mafia("#TEAM_MAFIA")");

				SendClientMessage(playerid, COLOR_GRAYWHITE, "Депортамент: DoT("#DoT"), FBI("#FBI"), DoD("#DoD"), DoH("#DoH"), DoJ("#DoJ"), DoE("#DoE")");
				SendClientMessage(playerid, COLOR_GRAYWHITE, "Семьи: LaCosaNostra("#LCN"), Yakuza("#Yakuza")");
				SendClientMessage(playerid, COLOR_GRAYWHITE, "Агентства: Hitman("#Hitman"), SAN("#SAN")");
				return 1;
			}
			/*if(PlayerInfo[giveplayerid][pMember] >= TEAM_GROVE)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Игрок находится в Организации (USE: /uninvite)!");
				return 1;
			}
		    if( !IsPlayerConnected(giveplayerid) )
			{
				format(strcmd, sizeof(strcmd), "   ID:%d отсутствует на сервере.", giveplayerid); SendClientMessage(playerid, COLOR_GREY, strcmd);
				return 1;
			}*/
			new family = strval(inputtext);
			if(PlayerInfo[giveplayerid][pMember] > 0) FamilyInfo[PlayerInfo[giveplayerid][pMember]][fMembers] --;
			PlayerInfo[giveplayerid][pMember] = family;
			FamilyInfo[family][fMembers] ++;

	        format(strcmd, sizeof(strcmd), "* %s сделал Bас членом %s.", PlayerName(playerid), GetFamilyName(family));
	       	SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strcmd);
			format(strcmd, sizeof(strcmd), "AdmCmd: %s set %s's fraction %s", PlayerName(playerid), PlayerName(giveplayerid), GetFamilyName(family));
	       	SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
	  		Log(ADMINLOG, strcmd);

#if defined vw_sql//#endif
			InviteList(playerid, PlayerName(giveplayerid), family, PlayerInfo[giveplayerid][pRank], 1);
#endif

			DeletePVar(playerid, "Action");
		}
	}
	else if(operation == 33)//33.Leader
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{//SendClientMessage(playerid, COLOR_GREY, "Hомер может быть от "#TEAM_GROVE" до "#DoE"! Сделать гражданским: 0 !");
			ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до "#DoE". \nСделать гражданским: 0\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");

			SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Grove Street("#TEAM_GROVE"), The Ballas("#TEAM_BALLAS"), Varios Los Aztecas("#TEAM_AZTEC"), Los Santos Vagos("#TEAM_VAGOS")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Da Nang Boys("#TEAM_NANG"), San Fierro Rifa("#TEAM_RIFA "), The Traids("#TEAM_TRIAD"), Bikers("#TEAM_BIKER"), The Mafia("#TEAM_MAFIA")");

			SendClientMessage(playerid, COLOR_GRAYWHITE, "Депортамент: DoT("#DoT"), FBI("#FBI"), DoD("#DoD"), DoH("#DoH"), DoJ("#DoJ"), DoE("#DoE")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Семьи: LaCosaNostra("#LCN"), Yakuza("#Yakuza")");
			SendClientMessage(playerid, COLOR_GRAYWHITE, "Агентства: Hitman("#Hitman"), SAN("#SAN")");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < 0 || strval(inputtext) > DoE)
			{
				ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от 0 до "#DoE". \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");

				SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Grove Street("#TEAM_GROVE"), The Ballas("#TEAM_BALLAS"), Varios Los Aztecas("#TEAM_AZTEC"), Los Santos Vagos("#TEAM_VAGOS")");
				SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Da Nang Boys("#TEAM_NANG"), San Fierro Rifa("#TEAM_RIFA "), The Traids("#TEAM_TRIAD"), Bikers("#TEAM_BIKER"), The Mafia("#TEAM_MAFIA")");

				SendClientMessage(playerid, COLOR_GRAYWHITE, "Депортамент: DoT("#DoT"), FBI("#FBI"), DoD("#DoD"), DoH("#DoH"), DoJ("#DoJ"), DoE("#DoE")");
				SendClientMessage(playerid, COLOR_GRAYWHITE, "Семьи: LaCosaNostra("#LCN"), Yakuza("#Yakuza")");
				SendClientMessage(playerid, COLOR_GRAYWHITE, "Агентства: Hitman("#Hitman"), SAN("#SAN")");
				return 1;
			}
			/*if(PlayerInfo[giveplayerid][pMember] >= TEAM_GROVE)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Игрок находится в Организации (USE: /uninvite)!");
				return 1;
			}
		    if( !IsPlayerConnected(giveplayerid) )
			{
				format(strcmd, sizeof(strcmd), "   ID:%d отсутствует на сервере.", giveplayerid); SendClientMessage(playerid, COLOR_GREY, strcmd);
				return 1;
			}*/
			new family = strval(inputtext);
	   	 	if(family == TEAM_NONE)
	   	 	{//если снимаем лидерку
				format(strcmd, sizeof(strcmd), "AdmCmd: %s лишил Лидерки %s'а из фракции %s. Ранг остался прежним.",
					PlayerName(playerid), PlayerName(giveplayerid), GetFamilyName(PlayerInfo[giveplayerid][pLeader]));
				PlayerInfo[giveplayerid][pLeader] = 0;
				Log(INVITE,strcmd);
				SendClientMessage(giveplayerid, COLOR_RED, strcmd);
				SendClientMessage(playerid, COLOR_RED, strcmd);
				//format(strcmd, sizeof(strcmd), "   Bы лишили Лидерки %s'а. Ранг остался прежним.", PlayerName(giveplayerid));
				//SendClientMessage(playerid, COLOR_RED, strcmd);
				return 1;
	   	 	}

			if(PlayerInfo[giveplayerid][pMember] > 0) FamilyInfo[PlayerInfo[giveplayerid][pMember]][fMembers] --;
			PlayerInfo[giveplayerid][pMember] = family;
			PlayerInfo[giveplayerid][pLeader] = family;
			FamilyInfo[family][fMembers] ++;

	        format(strcmd, sizeof(strcmd), "* %s сделал Bас лидером %s.", PlayerName(playerid), GetFamilyName(family));
	       	SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strcmd);
			format(strcmd, sizeof(strcmd), "AdmCmd: %s set %s's fraction %s", PlayerName(playerid), PlayerName(giveplayerid), GetFamilyName(family));
	       	SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
	  		Log(ADMINLOG, strcmd);
	  		
#if defined vw_sql//#endif
			InviteList(playerid, PlayerName(giveplayerid), family, PlayerInfo[giveplayerid][pRank], 1);
#endif

			DeletePVar(playerid, "Action");
		}
	}
	else if(operation == 34)//34.Rank
	{
		if(GetPVarInt(playerid, "InputCounter") == 0)
		{//SendClientMessage(playerid, COLOR_GREY, "Hомер может быть от "#TEAM_GROVE" до "#DoE"! Сделать гражданским: 0 !");
			ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от "#TEAM_GROVE" до "#DoE". \nСделать гражданским: 0\n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
		}
		else
		{
			if(!strlen(inputtext) || strval(inputtext) < TEAM_GROVE || strval(inputtext) > DoE)
			{
				ShowPlayerDialogEx(playerid, PLAYERINFO_DIALOG, DIALOG_STYLE_INPUT, inputtext, "Введите значение от "#TEAM_GROVE" до "#DoE". \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");

				SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Grove Street("#TEAM_GROVE"), The Ballas("#TEAM_BALLAS"), Varios Los Aztecas("#TEAM_AZTEC"), Los Santos Vagos("#TEAM_VAGOS")");
				SendClientMessage(playerid, COLOR_GRAYWHITE, "Банды: Da Nang Boys("#TEAM_NANG"), San Fierro Rifa("#TEAM_RIFA "), The Traids("#TEAM_TRIAD"), Bikers("#TEAM_BIKER"), The Mafia("#TEAM_MAFIA")");

				SendClientMessage(playerid, COLOR_GRAYWHITE, "Депортамент: DoT("#DoT"), FBI("#FBI"), DoD("#DoD"), DoH("#DoH"), DoJ("#DoJ"), DoE("#DoE")");
				SendClientMessage(playerid, COLOR_GRAYWHITE, "Семьи: LaCosaNostra("#LCN"), Yakuza("#Yakuza")");
				SendClientMessage(playerid, COLOR_GRAYWHITE, "Агентства: Hitman("#Hitman"), SAN("#SAN")");
				return 1;
			}
			new rank = strval(inputtext);
			PlayerInfo[giveplayerid][pRank] = rank;

	        format(strcmd, sizeof(strcmd), "* %s присвоен Ранг %d.", PlayerName(playerid), PlayerInfo[giveplayerid][pRank]);
	       	SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, strcmd);
			format(strcmd, sizeof(strcmd), "AdmCmd: %s set %s's rank %s", PlayerName(playerid), PlayerName(giveplayerid), PlayerInfo[giveplayerid][pRank]);
	       	SendClientMessage(playerid, COLOR_LIGHTBLUE, strcmd);
	  		Log(ADMINLOG, strcmd);

			DeletePVar(playerid, "Action");
		}
	}
	
	else DeletePVar(playerid, "Action");
	GivePVarInt(playerid, "InputCounter", +1);//счётчик кол-ва входов в данную обработку
	//format(strings, sizeof(strings), "admin_OnDialogResponse(playerid:%d, giveplayerid:%d, Action:%d, InputCounter:%d)", playerid, giveplayerid, GetPVarInt(playerid, "Action"), GetPVarInt(playerid, "InputCounter") );
	//SendClientMessage(playerid, COLOR_GREEN, strings);
	return 1;
}
