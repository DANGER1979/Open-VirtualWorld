enum pCooking
{
	pCook1[20],//название вида еды
	pCook2[20],
	pCook3[20],
	pCook4[20],
	pCook5[20],
	pCWeight1,
	pCWeight2,
	pCWeight3,
	pCWeight4,
	pCWeight5,
	pCookID1,
	pCookID2,
	pCookID3,
	pCookID4,
	pCookID5
};
new Cooking[MAX_PLAYERS][pCooking];


stock ClearCooking(playerid)//вызывается из ф-ии OnPlayerConnect
{
    Cooking[playerid][pCookID1] = 0; Cooking[playerid][pCookID2] = 0; Cooking[playerid][pCookID3] = 0;
	Cooking[playerid][pCookID4] = 0; Cooking[playerid][pCookID5] = 0;
	Cooking[playerid][pCWeight1] = 0; Cooking[playerid][pCWeight2] = 0; Cooking[playerid][pCWeight3] = 0;
	Cooking[playerid][pCWeight4] = 0; Cooking[playerid][pCWeight5] = 0;
	new strtmp[8];//MAX_PLAYER_NAME
	format(strtmp, sizeof(strtmp), "Nothing");
	strmid(Cooking[playerid][pCook1], strtmp, 0, strlen(strtmp), 20);
	strmid(Cooking[playerid][pCook2], strtmp, 0, strlen(strtmp), 20);
	strmid(Cooking[playerid][pCook3], strtmp, 0, strlen(strtmp), 20);
	strmid(Cooking[playerid][pCook4], strtmp, 0, strlen(strtmp), 20);
	strmid(Cooking[playerid][pCook5], strtmp, 0, strlen(strtmp), 20);
}
stock ClearCookingID(playerid, cook)
{
	new strtmp[8];//MAX_PLAYER_NAME
	format(strtmp, sizeof(strtmp), "Nothing");
	switch(cook)
	{
	    case 1:
	    {
	        strmid(Cooking[playerid][pCook1], strtmp, 0, strlen(strtmp), 20);
	        Cooking[playerid][pCWeight1] = 0;
	        Cooking[playerid][pCookID1] = 0;
	    }
	    case 2:
	    {
	        strmid(Cooking[playerid][pCook2], strtmp, 0, strlen(strtmp), 20);
	        Cooking[playerid][pCWeight2] = 0;
	        Cooking[playerid][pCookID2] = 0;
	    }
	    case 3:
	    {
	        strmid(Cooking[playerid][pCook3], strtmp, 0, strlen(strtmp), 20);
	        Cooking[playerid][pCWeight3] = 0;
	        Cooking[playerid][pCookID3] = 0;
	    }
	    case 4:
	    {
	        strmid(Cooking[playerid][pCook4], strtmp, 0, strlen(strtmp), 20);
	        Cooking[playerid][pCWeight4] = 0;
	        Cooking[playerid][pCookID4] = 0;
	    }
	    case 5:
	    {
	        strmid(Cooking[playerid][pCook5], strtmp, 0, strlen(strtmp), 20);
	        Cooking[playerid][pCWeight5] = 0;
	        Cooking[playerid][pCookID5] = 0;
	    }
	}
}
stock ClearGroceries(playerid)//вызывается из ф-ии OnPlayerConnect
{
    Groceries[playerid][gChickens] = 0; Groceries[playerid][gChicken] = 0;
    Groceries[playerid][gHamburgers] = 0; Groceries[playerid][gHamburger] = 0;
    Groceries[playerid][gPizzas] = 0; Groceries[playerid][gPizza] = 0;
}

