new guildcounter;
#define MAX_CLANS 10
enum gInfo
{
	NumberGuild,

	gID,//ID
	gOwner[24],//
	gMembers,//

	gBrevis[4],//абривиатура
	gDiscription[128],
	gMOTD[256+1],//приветствие

	gLogo[64],//логотиип

//спавн
	Float:gSpawns[4],
	gInterior,
	gWorld,
	gLocal,

//касса
	Float:gEntranceX,
	Float:gEntranceY,
	Float:gEntranceZ,
	gInt,

	gBuyPrice,
	gLevel,
	gLock,
	gEntranceCost,
	gProducts,
	gBuyProd,
	gSellProd,
	gTill,
	gDate,
	gInkas
};
new ClanInfo[MAX_CLANS][gInfo];


stock ClearGuild(guild)
{
	ClanInfo[guild][gID] = 0;
	strmid(ClanInfo[guild][gOwner], "No-One", 0, 8, 8);
	ClanInfo[guild][gMembers] = 0;

    ClanInfo[guild][gBuyPrice] = 0;
    ClanInfo[guild][gEntranceCost] = 0;
    ClanInfo[guild][gProducts] = 100;
    ClanInfo[guild][gBuyProd] = 1;
	ClanInfo[guild][gSellProd] = 10;

	ClanInfo[guild][gTill] = 0;
	ClanInfo[guild][gDate] = 0;
	ClanInfo[guild][gInkas] = 0;

	guildcounter --;
}


