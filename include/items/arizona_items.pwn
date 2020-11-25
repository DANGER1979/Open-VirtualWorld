#include <a_samp>
/*#include <file>
#include <string>
#include <a_actor>
#include <a_mysql>
#include <Pawn.CMD>
#include <mxINI>
#include <sscanf2>
#include <streamer>
#include <fixobject>
#include <TOTP>
#include <mail>
#include <progress>
#include <a_http>
#include <crashdetect>
#include <nex-ac>
#include <foreach>
#include <easy_screen_fade_by_otacon>
#include <geolocation>
#include <fly>
*/

#define publics%0(%1) forward%0(%1); public%0(%1)
new PlayerText:InfoItems[MAX_PLAYERS][6];
new PlayerText:fstd_p[MAX_PLAYERS][7];
new PlayerText:dropmenu[MAX_PLAYERS][8];

enum pInfo
{
	pID,
	pNone,
	pNameFamily,
	pNameFamily2[15],
	pPlayedTime,
	pKey,
	pPodtverTrade,
	pQiwi[16],
	pVivod,
	pDep,
	pSumkaIzi,
	pNetNalogi,
	pCrypto,
	pAvtorization,
	pCMDplveh,
	pFamily,
	pRefID,
	pDepTime,
	pDepTime2,
	pFamilyMute,
	pFamilyChat,
	//Text3D: pFamText[128],
	pVxod,
	Float:pStoika,
	pFamilyMember,
	pDopInv[72],
	Float:pSuperComp,
	pLavkaCost[10],
	Float:pServer,
	Float:pKvant,
	Float:pData,
	Float:pStoikaCost,
	Float:pSuperCompCost,
	Float:pServerCost,
	Float:pKvantCost,
	Float:pDataCost,
	pFamColor,
	pCraftDrug,
	Float:pVKCOIN,
	Float:pClick,
	Float:pClickCost,
	Float:pKarta,
	Float:pKartaCost,
	pFamName[16],
	pInventoryS[72],
	pInventorySK[72],
	pFamType[16],
	pDiscord[31],
	pRaidCall[31],
	pObyava[61],
	pFamSlog[41],
	pSod[61],
	pTalons,
	pDiceLox,
	pDiceWin,
	pColorInv,
	pKeyCheck,
	pInventori2,
	pOldRepl,
	pDontShkaf,
	pCreateFam,
	pIDTime,
	pRemoved,
	pGolda,
	pSilverW,
	pKamenb,
	pSostoyanie,
	pMoreHouses,
	pDonatMoney,
	pRefs,
	pPromoUsed,
	pPromo,
	pPlanshet,
	pInventoryKolvoDop,
	pCraftClose,
	pAllRepl,
	pMusorPos,
	pMailCheck,
	pCraftX,
	pCraftC,
	pCraftV,
	pCraftB,
	pCraftN,
	pLanguage,
	pYaPolniyDolboeb,
	pLevel,
	pXyina,
	pInventori,
	pCarSkill,
	pTimeInv3,
	pMoney,
	pCheepsTimer,
	pSupreme,
	pBeg[5],
	pExp,
	pEventStart,
	pInvColors,
	pCoins300,
	pCoins500,
	pDolboeb,
	pDopKletki,
	pMoney1000000,
	pProstoTak2,
	pProstoTak,
	pSkate,
	pInvOpen,
	pTrailers,
	pGovnoSuper,
	pTrailerStop,
	pTrailerSpawn,
	pYadolboeb,
	pCraft,
	pCraft2,
	pCraft3,
	pCraft4,
	pCraft5,
	pCraft6,
	pCraft7,
	pCraft8,
	pCraft9,
	pCraft10,
	pCraftA,
	pCraftS,
	pCraftD,
	pCraftF,
	pSecretMoney,
	pSecretMoney2,
	pSecretMoney3,
	pTrash,
	pTrashOpen,
	pCraftG,
	pCraftH,
	pCraftJ,
	pCraftK,
	pCraftL,
	pCraftZ,
	pCraftA1,
	pCraftS2,
	pCraftD3,
	pCraftF4,
	pCraftG5,
	pCraftH6,
	pCraftJ7,
	pCraftK8,
	pCraftL9,
	pCraftZ10,
	pClicked,
	pSuperGOVNO,
	pSuperGOVNO2,
	pSuperGOVNO3,
	pSuperGOVNO4,
	pSuperCraft2,
	pSuperCraft,
	pTrailerTime,
	pInventoryKolvo[72],
	pInvs[72],
	pCoins200,
	pEnterTrailer,
	pInventory[72],
	pTrailerShtraf,
	pFirstCase,
	pMoney2000000,
	pMoney5000000,
	pExp2,
	pExp4,
	pBuyTrailer,
	//pInventory,
	pExp8,
	pInvStandart,
	pGovnishePolnoe,
	pSecondpage,
	pWanted,
	pVIP,
	pLeader,
	pMember,
	pAdmin,
	pCodes,
	pHelper,
	pWeapon[3],
	pAmmo[3],
	pGunLic,
	pBoatLic,
	pFishLic,
	pFlyLic,
	pCarLic,
	pBikeLic,
	pPodtver,
Float:pPos_X,
Float:pPos_Y,
Float:pPos_Z,
Float:pPos_A,
Float:pOld_X,
Float:pOld_Y,
Float:pOld_Z,
Float:pCPos_X,
Float:pCPos_Y,
Float:pCPos_Z,
	pVirMoney,
	pWarns,
	pHouseKey,
	pSnow,
	pBizKey,
	pFWarns,
	pView,
	pRank,
	pContractTime,
	pCars,
	pSex,
	pSigs,
	pLighter,
	pRace,
	pBank,
	pSkin,
	pOldSkin,
	pTelNum,
	pPhone,
	pMats,
	pValue,
	pPackets,
	pD_Packets,
	pDrugs,
	pScrew,
	pPlayHours,
	pJob,
	pMuteTime,
	pFMuteTime,
	pHeal,
	pHealTime,
	pJailTime,
	pJail,
	pBailPrice,
	pKungfu,
	pKneehead,
	pElbow,
	pBoxing,
	pSpawned,
	pSpining,
	pWorms,
	pRadio,
	pLotto,
	pMask,
	pMaskON,
	pRoliki,
	pFuel,
 	pPasatizhi,
	pDCTime,
	pPhoneBook,
	pPistol_Skill,
	pSDPistol_Skill,
	pEagle_Skill,
	pShotGun_Skill,
	pUZI_Skill,
	pMP5_Skill,
	pAK47_Skill,
	pM4_Skill,
	pSniper_Skill,
	pInvGun,
	pInvAmmo,
	pGlasses,
	pBandans,
	pGold,
	pHats,
	pFrom,
	pOOC,
	pBL,
	pZKP,
Float:pHealth,
Float:pArmour,
Float:pShield,
	pArmours,
	pPoison,
	pPack,
	pSprunk,
	pCheeps,
	pBeer,
	pRepPack,
	pSprunks,
	pCheepses,
	pBeers,
	pFeFinder,
	pGetBonus,
	pClip,
	pCredit,
	pBlackout,
	pSyringe,
	pRope,
	pBomb,
	pRepBan,
	pAskBan,
	pRPTest,
	pStatsStyle,
	pPayDay,
	pAge,
	pEnterKey,
	pWalentin,
	pBuyWalent,
	pF_Skill,
	pZ_Skill,
	pP_Skill,
	pZa_Skill,
	pIn_Skill,
	pMy_Skill,
	pBy_Skill,
	pEnergy,
	pAmmos[13],
	pGuns[13],
	pShowName,
	plveh,
	pMerrit[25],
	pSendName[25],
	pCalling,
	pONPhoneTalk,
	pbydilnik,
	pKazpay,
	pKlogin,
Float:Admin_X,
Float:Admin_Y,
Float:Admin_Z,
	pFtime1,
	pLastGun,
	pLastAmmo,
	pTimeToLastWarn,
	oInTir,
	preOrg,
	preOrgg,
	pObjikt,
Float:pLeftPosx,
Float:pLeftPosy,
Float:pRightPosx,
Float:pRightPosy,
	pHSpectr,
	pScutes,
	pMScutes,
	pVID,
	pType,
	pSlotItem[8],
	pType2,
	pNeedMessage,
	pRedio,
	pHospital,
	pSecond,
	pHavePassword,
	pMore,
	pLastLogin[120],
	pLastIP[60],
	pShowIper,
	pShowCase,
	pVipTime,
	pBuildType,
	pZall,pWhore, pAmountSex, pDisease,pMesh,
	pName,
	pReputation,
	pLoadTextures,
	pPredlog,
	pCotton,
	pTeleport,
	pBronzeRoulette,
	pSilverRoulette,
	pGoldRoulette,
	pChestTime,
	pSeat,
	pEventTime,
	pInvLang,
	pAWarns,
	pDataReg[12],
	pAPass[65],
	pPodtverApanel,
	pLastIPAdm[60],
	pVirtualWorld,
	pInterior,
	pTypeSpeed,
	Float:pInvPos_X,
	Float:pInvPos_Y,
	Float:pInvSize_X,
	Float:pInvSize_Y,
	pAdminPrefix[64],
	pGoogleCode[64],
	pGoogleStatus,
	pKolZakladka,
	pDailyQuest
}
new PlayerInfo[MAX_PLAYERS][pInfo];

#define MAX_HOUSES 		(1200)
enum hInfo
{
	hID,
Float:hEnter_X,
Float:hEnter_Y,
Float:hEnter_Z,
Float:hEnter_A,
Float:hExit_X,
Float:hExit_Y,
Float:hExit_Z,
	hCost,
	hLevel,
	hOwner[24],
	hInt,
	hLock,
	hRent,
	hMoney,
	hDrugs,
	hMats,
	hBar,
	hCabinet,
	hSkin[5],
	hShkafSlot[30],
	hShkafSlotKol[30],
	hNalog,
	hNalog2,
	hNoOwner,
	hKlass,
	hMed,
	hGarage,
Float:hGarage_X,
Float:hGarage_Y,
Float:hGarage_Z,
	hPodval,
	hIntGarage,
	hIntPodval,
//	hGarageLock
}
new HouseInfo[MAX_HOUSES][hInfo];

new PickInventTrade[MAX_PLAYERS][72];
new PickInvent[MAX_PLAYERS];
new HouseEntered[MAX_PLAYERS];


enum ItemInfo
{
    ItemModel,//модель
    bool:itemused,//можно ли использовать
    ItemQuantity,//макс значение в стеке
    ItemPhoneColor[25],//для одинаковых моделей
	ItemUse[8],
	ItemUseRus[16],
	ItemAksColor,
    ItemColor,//цвет модели
    NameItemLavka[50],//для центр рынка
    ItemName2[50],//отдельное имя предмета
    ItemName[70],//имя предмета
	ItemInfos[500],//инфо о предмете
    Float:POSTDx,
    Float:POSTDy,
    Float:POSTDz,
    Float:POSTDc
};
#define MAX_ITEMS 617
new ItemsInfo[MAX_ITEMS][ItemInfo] = {
    {1649, false, 0, "", "N", "N", 0x333333FF, 0x333333FF, "Kletka", "Пусто", "Пусто", "", 0.000000, 0.000000, 90.000000, 2.000000},//клетка
    {1, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: The Truth (ID:1)", "{FDCF28}Скин: The Truth (ID:1)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{2, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Maccer (ID:2)", "{FDCF28}Скин: Maccer (ID:2)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{3, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Andre (ID:3)", "{FDCF28}Скин: Andre (ID:3)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{4, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Barry ''Big Bear'' Thorne [Thin] (ID:4)", "{FDCF28}Скин: Barry ''Big Bear'' Thorne [Thin] (ID:4)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{5, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Barry ''Big Bear'' Thorne [Big] (ID:5)", "{FDCF28}Скин: Barry ''Big Bear'' Thorne [Big] (ID:5)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{6, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Emmet (ID:6)", "{FDCF28}Скин: Emmet (ID:6)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{7, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Taxi Driver/Train Driver (ID:7)", "{FDCF28}Скин: Taxi Driver/Train Driver (ID:7)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{8, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Janitor (ID:8)", "{FDCF28}Скин: Janitor (ID:8)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{9, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:9)", "{FDCF28}Скин: Normal Ped (ID:9)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{10, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Old Woman (ID:10)", "{FDCF28}Скин: Old Woman (ID:10)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{11, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Casino croupier (ID:11)", "{FDCF28}Скин: Casino croupier (ID:11)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{12, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Rich Woman (ID:12)", "{FDCF28}Скин: Rich Woman (ID:12)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{13, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Street Girl (ID:13)", "{FDCF28}Скин: Street Girl (ID:13)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{14, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:14)", "{FDCF28}Скин: Normal Ped (ID:14)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{15, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Mr.Whittaker (RS Haul Owner) (ID:15)", "{FDCF28}Скин: Mr.Whittaker (RS Haul Owner) (ID:15)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{16, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Airport Ground Worker (ID:16)", "{FDCF28}Скин: Airport Ground Worker (ID:16)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{17, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Businessman (ID:17)", "{FDCF28}Скин: Businessman (ID:17)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{18, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Beach Visitor (ID:18)", "{FDCF28}Скин: Beach Visitor (ID:18)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{19, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: DJ (ID:19)", "{FDCF28}Скин: DJ (ID:19)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{20, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Rich Guy (Madd Dogg's Manager) (ID:20)", "{FDCF28}Скин: Rich Guy (Madd Dogg's Manager) (ID:20)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{21, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:21)", "{FDCF28}Скин: Normal Ped (ID:21)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{22, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:22)", "{FDCF28}Скин: Normal Ped (ID:22)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{23, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: BMXer (ID:23)", "{FDCF28}Скин: BMXer (ID:23)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{24, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin",  "Скин Madd Dogg Bodyguard: (ID:24)", "{FDCF28}Скин: Madd Dogg Bodyguard (ID:24)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{25, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Madd Dogg Bodyguard (ID:25)", "{FDCF28}Скин: Madd Dogg Bodyguard (ID:25)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{26, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Backpacker (ID:26)", "{FDCF28}Скин: Backpacker (ID:26)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{27, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Скин: Construction Worker (ID:27)", "{FDCF28}Скин: Construction Worker (ID:27)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{28, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Drug Dealer (ID:28)", "{FDCF28}Скин: Drug Dealer (ID:28)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{29, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Drug Dealer (ID:29)", "{FDCF28}Скин: Drug Dealer (ID:29)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{30, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Drug Dealer (ID:30)", "{FDCF28}Скин: Drug Dealer (ID:30)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{31, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Farm-Town inhabitant (ID:31)", "{FDCF28}Скин: Farm-Town inhabitant (ID:31)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{32, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Farm-Town inhabitant (ID:32)", "{FDCF28}Скин: Farm-Town inhabitant (ID:32)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{33, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Farm-Town inhabitant (ID:33)", "{FDCF28}Скин: Farm-Town inhabitant (ID:33)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{34, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Farm-Town inhabitant (ID:34)", "{FDCF28}Скин: Farm-Town inhabitant (ID:34)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{35, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Gardener (ID:35)", "{FDCF28}Скин: Gardener (ID:35)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{36, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Golfer (ID:36)", "{FDCF28}Скин: Golfer (ID:36)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{37, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Golfer (ID:37)", "{FDCF28}Скин: Golfer (ID:37)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{38, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:38)", "{FDCF28}Скин: Normal Ped (ID:38)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{39, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:39)", "{FDCF28}Скин: Normal Ped (ID:39)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{40, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:40)", "{FDCF28}Скин: Normal Ped (ID:40)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{41, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:41)", "{FDCF28}Скин: Normal Ped (ID:41)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{42, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Jethro (ID:42)", "{FDCF28}Скин: Jethro (ID:42)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{43, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:43)", "{FDCF28}Скин: Normal Ped (ID:43)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{44, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:44)", "{FDCF28}Скин: Normal Ped (ID:44)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{45, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Beach Visitor (ID:45)", "{FDCF28}Скин: Beach Visitor (ID:45)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{46, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:46)", "{FDCF28}Скин: Normal Ped (ID:46)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{47, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:47)", "{FDCF28}Скин: Normal Ped (ID:47)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{48, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:48)", "{FDCF28}Скин: Normal Ped (ID:48)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{49, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Snakehead (Da Nang) (ID:49)", "{FDCF28}Скин: Snakehead (Da Nang) (ID:49)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{50, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Mechanic (ID:50)", "{FDCF28}Скин: Mechanic (ID:50)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{51, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Mountain Biker (ID:51)", "{FDCF28}Скин: Mountain Biker (ID:51)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{52, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Mountain Biker (ID:52)", "{FDCF28}Скин: Mountain Biker (ID:52)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{53, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Unknown (ID:53)", "{FDCF28}Скин: Unknown (ID:53)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{54, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:54)", "{FDCF28}Скин: Normal Ped (ID:54)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{55, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:55)", "{FDCF28}Скин: Normal Ped (ID:55)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{56, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:56)", "{FDCF28}Скин: Normal Ped (ID:56)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{57, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Oriental Ped (ID:57)", "{FDCF28}Скин: Oriental Ped (ID:57)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{58, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Oriental Ped (ID:58)", "{FDCF28}Скин: Oriental Ped (ID:58)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{59, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:59)", "{FDCF28}Скин: Normal Ped (ID:59)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{60, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:60)", "{FDCF28}Скин: Normal Ped (ID:60)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{61, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Pilot (ID:61)", "{FDCF28}Скин: Pilot (ID:61)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{62, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Colonel Fuhrberger (ID:62)", "{FDCF28}Скин: Colonel Fuhrberger (ID:62)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{63, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Prostitute (ID:63)", "{FDCF28}Скин: Prostitute (ID:63)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{64, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Prostitute (ID:64)", "{FDCF28}Скин: Prostitute (ID:64)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{65, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Kendl Johnson (ID:65)", "{FDCF28}Скин: Kendl Johnson (ID:65)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{66, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Pool Player (ID:66)", "{FDCF28}Скин: Pool Player (ID:66)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{67, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Pool Player (ID:67)", "{FDCF28}Скин: Pool Player (ID:67)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{68, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Priest/Preacher (ID:68)", "{FDCF28}Скин: Priest/Preacher (ID:68)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{69, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:69)", "{FDCF28}Скин: Normal Ped (ID:69)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{70, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Scientist (ID:70)", "{FDCF28}Скин: Scientist (ID:70)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{71, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Security Guard (ID:71)", "{FDCF28}Скин: Security Guard (ID:71)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{72, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Hippy (ID:72)", "{FDCF28}Скин: Hippy (ID:72)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{73, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Hippy (ID:73)", "{FDCF28}Скин: Hippy (ID:73)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{74, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Unknown (ID:74)", "{FDCF28}Скин: Unknown (ID:74)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{75, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Prostitute (ID:75)", "{FDCF28}Скин: Prostitute (ID:75)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{76, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:76)", "{FDCF28}Скин: Normal Ped (ID:76)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{77, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Homeless (ID:77)", "{FDCF28}Скин: Homeless (ID:77)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{78, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Homeless  (ID:78)", "{FDCF28}Скин: Homeless (ID:78)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{79, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Homeless (ID:79)", "{FDCF28}Скин: Homeless (ID:79)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{80, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Boxer (ID:80)", "{FDCF28}Скин: Boxer (ID:80)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{81, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Boxer (ID:81)", "{FDCF28}Скин: Boxer (ID:81)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{82, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Black Elvis (ID:82)", "{FDCF28}Скин: Black Elvis (ID:82)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{83, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: White Elvis (ID:83)", "{FDCF28}Скин: White Elvis (ID:83)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{84, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Blue Elvis (ID:84)", "{FDCF28}Скин: Blue Elvis (ID:84)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{85, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Prostitute (ID:85)", "{FDCF28}Скин: Prostitute (ID:85)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{86, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Ryder with robbery mask (ID:86)", "{FDCF28}Скин: Ryder with robbery mask (ID:86)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{87, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Stripper (ID:87)", "{FDCF28}Скин: Stripper (ID:87)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{88, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:88)", "{FDCF28}Скин: Normal Ped (ID:88)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{89, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:89)", "{FDCF28}Скин: Normal Ped (ID:89)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{90, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Jogger (ID:90)", "{FDCF28}Скин: Jogger (ID:90)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{91, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Rich Woman (ID:91)", "{FDCF28}Скин: Rich Woman (ID:91)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{92, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Rollerskater (ID:92)", "{FDCF28}Скин: Rollerskater (ID:92)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{93, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:93)", "{FDCF28}Скин: Normal Ped (ID:93)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{94, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:94)", "{FDCF28}Скин: Normal Ped (ID:94)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{95, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:95)", "{FDCF28}Скин: Normal Ped (ID:95)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{96, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Jogger (ID:96)", "{FDCF28}Скин: Jogger (ID:95)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{97, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Lifeguard (ID:97)", "{FDCF28}Скин: Lifeguard (ID:97)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{98, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Normal Ped (ID:98)", "{FDCF28}Скин: Normal Ped (ID:98)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{99, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Rollerskater (ID:99)", "{FDCF28}Скин: Rollerskater (ID:99)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{100, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Biker (ID:100)", "{FDCF28}Скин: Biker (ID:100)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{101, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:101)", "{FDCF28}Скин:  (ID:101)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{102, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:102)", "{FDCF28}Скин:  (ID:102)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{103, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:103)", "{FDCF28}Скин:  (ID:103)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{104, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:104)", "{FDCF28}Скин:  (ID:104)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{105, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:105)", "{FDCF28}Скин:  (ID:105)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{106, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:106)", "{FDCF28}Скин:  (ID:106)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{107, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:107)", "{FDCF28}Скин:  (ID:107)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{108, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:108)", "{FDCF28}Скин:  (ID:108)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{109, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:109)", "{FDCF28}Скин:  (ID:109)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{110, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:110)", "{FDCF28}Скин:  (ID:110)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{111, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:111)", "{FDCF28}Скин:  (ID:111)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{112, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:112)", "{FDCF28}Скин:  (ID:112)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{113, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:113)", "{FDCF28}Скин:  (ID:113)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{114, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:114)", "{FDCF28}Скин:  (ID:114)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{115, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:115)", "{FDCF28}Скин:  (ID:115)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{116, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:116)", "{FDCF28}Скин:  (ID:116)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{117, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:117)", "{FDCF28}Скин:  (ID:117)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{118, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:118)", "{FDCF28}Скин:  (ID:118)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{119, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:119)", "{FDCF28}Скин:  (ID:119)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{120, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:120)", "{FDCF28}Скин:  (ID:120)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{121, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:121)", "{FDCF28}Скин:  (ID:121)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{122, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:122)", "{FDCF28}Скин:  (ID:122)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{123, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:123)", "{FDCF28}Скин:  (ID:123)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{124, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:124)", "{FDCF28}Скин:  (ID:124)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{125, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:125)", "{FDCF28}Скин:  (ID:125)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{126, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:126)", "{FDCF28}Скин:  (ID:126)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{127, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:127)", "{FDCF28}Скин:  (ID:127)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{128, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:128)", "{FDCF28}Скин:  (ID:128)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{129, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:129)", "{FDCF28}Скин:  (ID:129)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{130, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:130)", "{FDCF28}Скин:  (ID:130)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{131, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:131)", "{FDCF28}Скин:  (ID:131)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{132, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:132)", "{FDCF28}Скин:  (ID:132)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{133, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:133)", "{FDCF28}Скин:  (ID:133)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{134, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:134)", "{FDCF28}Скин:  (ID:134)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{135, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:135)", "{FDCF28}Скин:  (ID:135)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{136, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:136)", "{FDCF28}Скин:  (ID:136)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{137, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:137)", "{FDCF28}Скин:  (ID:137)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{138, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:138)", "{FDCF28}Скин:  (ID:138)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{139, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:139)", "{FDCF28}Скин:  (ID:139)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{140, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:140)", "{FDCF28}Скин:  (ID:140)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{141, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:141)", "{FDCF28}Скин:  (ID:141)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{142, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:142)", "{FDCF28}Скин:  (ID:142)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{143, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:143)", "{FDCF28}Скин:  (ID:143)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{144, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:144)", "{FDCF28}Скин:  (ID:144)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{145, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:145)", "{FDCF28}Скин:  (ID:145)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{146, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:146)", "{FDCF28}Скин:  (ID:146)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{147, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:147)", "{FDCF28}Скин:  (ID:147)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{148, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:148)", "{FDCF28}Скин:  (ID:148)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{149, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:149)", "{FDCF28}Скин:  (ID:149)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{150, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:150)", "{FDCF28}Скин:  (ID:150)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{151, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:151)", "{FDCF28}Скин:  (ID:151)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{152, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:152)", "{FDCF28}Скин:  (ID:152)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{153, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:153)", "{FDCF28}Скин:  (ID:153)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{154, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:154)", "{FDCF28}Скин:  (ID:154)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{155, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:155)", "{FDCF28}Скин:  (ID:155)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{156, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:156)", "{FDCF28}Скин:  (ID:156)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{157, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:157)", "{FDCF28}Скин:  (ID:157)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{158, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:158)", "{FDCF28}Скин:  (ID:158)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{159, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:159)", "{FDCF28}Скин:  (ID:159)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{160, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:160)", "{FDCF28}Скин:  (ID:160)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{161, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:161)", "{FDCF28}Скин:  (ID:161)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{162, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:162)", "{FDCF28}Скин:  (ID:162)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{163, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:163)", "{FDCF28}Скин:  (ID:163)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{164, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:164)", "{FDCF28}Скин:  (ID:164)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{165, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:165)", "{FDCF28}Скин:  (ID:165)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{166, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:166)", "{FDCF28}Скин:  (ID:166)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{167, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:167)", "{FDCF28}Скин:  (ID:167)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{168, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:168)", "{FDCF28}Скин:  (ID:168)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{169, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:169)", "{FDCF28}Скин:  (ID:169)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{170, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:170)", "{FDCF28}Скин:  (ID:170)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{171, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:171)", "{FDCF28}Скин:  (ID:171)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{172, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:172)", "{FDCF28}Скин:  (ID:172)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{173, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:173)", "{FDCF28}Скин:  (ID:173)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{174, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:174)", "{FDCF28}Скин:  (ID:174)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{175, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:175)", "{FDCF28}Скин:  (ID:175)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{176, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:176)", "{FDCF28}Скин:  (ID:176)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{177, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:177)", "{FDCF28}Скин:  (ID:177)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{178, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:178)", "{FDCF28}Скин:  (ID:178)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{179, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:179)", "{FDCF28}Скин:  (ID:179)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{180, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:180)", "{FDCF28}Скин:  (ID:180)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{181, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:181)", "{FDCF28}Скин:  (ID:181)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{182, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:182)", "{FDCF28}Скин:  (ID:182)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{183, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:183)", "{FDCF28}Скин:  (ID:183)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{184, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:184)", "{FDCF28}Скин:  (ID:184)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{185, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:185)", "{FDCF28}Скин:  (ID:185)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{186, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:186)", "{FDCF28}Скин:  (ID:186)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{187, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:187)", "{FDCF28}Скин:  (ID:187)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{188, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:188)", "{FDCF28}Скин:  (ID:188)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{189, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:189)", "{FDCF28}Скин:  (ID:189)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{190, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:190)", "{FDCF28}Скин:  (ID:190)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{191, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:191)", "{FDCF28}Скин:  (ID:191)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{192, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:192)", "{FDCF28}Скин:  (ID:192)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{193, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:193)", "{FDCF28}Скин:  (ID:193)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{194, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:194)", "{FDCF28}Скин:  (ID:194)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{195, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:195)", "{FDCF28}Скин:  (ID:195)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{196, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:196)", "{FDCF28}Скин:  (ID:196)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{197, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:197)", "{FDCF28}Скин:  (ID:197)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{198, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:198)", "{FDCF28}Скин:  (ID:198)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{199, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:199)", "{FDCF28}Скин:  (ID:199)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{200, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:200)", "{FDCF28}Скин:  (ID:200)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{201, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:201)", "{FDCF28}Скин:  (ID:201)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{202, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:202)", "{FDCF28}Скин:  (ID:202)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{203, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:203)", "{FDCF28}Скин:  (ID:203)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{204, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:204)", "{FDCF28}Скин:  (ID:204)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{205, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:205)", "{FDCF28}Скин:  (ID:205)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{206, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:206)", "{FDCF28}Скин:  (ID:206)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{207, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:207)", "{FDCF28}Скин:  (ID:207)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{208, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:208)", "{FDCF28}Скин:  (ID:208)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{209, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:209)", "{FDCF28}Скин:  (ID:209)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{210, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:210)", "{FDCF28}Скин:  (ID:210)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{211, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:211)", "{FDCF28}Скин:  (ID:211)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{212, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:212)", "{FDCF28}Скин:  (ID:212)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{213, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:213)", "{FDCF28}Скин:  (ID:213)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{214, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:214)", "{FDCF28}Скин:  (ID:214)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{215, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:215)", "{FDCF28}Скин:  (ID:215)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{216, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:216)", "{FDCF28}Скин:  (ID:216)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{217, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:217)", "{FDCF28}Скин:  (ID:217)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{218, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:218)", "{FDCF28}Скин:  (ID:218)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{219, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:219)", "{FDCF28}Скин:  (ID:219)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{220, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:220)", "{FDCF28}Скин:  (ID:220)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{221, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:221)", "{FDCF28}Скин:  (ID:221)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{222, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:222)", "{FDCF28}Скин:  (ID:222)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{223, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:223)", "{FDCF28}Скин:  (ID:223)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{224, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:224)", "{FDCF28}Скин:  (ID:224)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{225, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:225)", "{FDCF28}Скин:  (ID:225)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{226, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:226)", "{FDCF28}Скин:  (ID:226)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{227, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:227)", "{FDCF28}Скин:  (ID:227)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{228, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:228)", "{FDCF28}Скин:  (ID:228)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{229, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:229)", "{FDCF28}Скин:  (ID:229)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{230, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: Homeless (ID:230)", "{FDCF28}Скин: Homeless (ID:230)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{231, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:231)", "{FDCF28}Скин:  (ID:231)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{232, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:232)", "{FDCF28}Скин:  (ID:232)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{233, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:233)", "{FDCF28}Скин:  (ID:233)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{234, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:234)", "{FDCF28}Скин:  (ID:234)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{235, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:235)", "{FDCF28}Скин:  (ID:235)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{236, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:236)", "{FDCF28}Скин:  (ID:236)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{237, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:237)", "{FDCF28}Скин:  (ID:237)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{238, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:238)", "{FDCF28}Скин:  (ID:238)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{239, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:239)", "{FDCF28}Скин:  (ID:239)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{240, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:240)", "{FDCF28}Скин:  (ID:240)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{241, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:241)", "{FDCF28}Скин:  (ID:241)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{242, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:242)", "{FDCF28}Скин:  (ID:242)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{243, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:243)", "{FDCF28}Скин:  (ID:243)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{244, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:244)", "{FDCF28}Скин:  (ID:244)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{245, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:245)", "{FDCF28}Скин:  (ID:245)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{246, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:246)", "{FDCF28}Скин:  (ID:246)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{247, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:247)", "{FDCF28}Скин:  (ID:247)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{248, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:248)", "{FDCF28}Скин:  (ID:248)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{249, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:249)", "{FDCF28}Скин:  (ID:249)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{250, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:250)", "{FDCF28}Скин:  (ID:250)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{251, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:251)", "{FDCF28}Скин:  (ID:251)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{252, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:252)", "{FDCF28}Скин:  (ID:252)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{253, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:253)", "{FDCF28}Скин:  (ID:253)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{254, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:254)", "{FDCF28}Скин:  (ID:254)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{255, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:255)", "{FDCF28}Скин:  (ID:255)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{256, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:256)", "{FDCF28}Скин:  (ID:256)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{257, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:257)", "{FDCF28}Скин:  (ID:257)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{258, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:258)", "{FDCF28}Скин:  (ID:258)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{259, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:259)", "{FDCF28}Скин:  (ID:259)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{260, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:260)", "{FDCF28}Скин:  (ID:260)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{261, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:261)", "{FDCF28}Скин:  (ID:261)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{262, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:262)", "{FDCF28}Скин:  (ID:262)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{263, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:263)", "{FDCF28}Скин:  (ID:263)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{264, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:264)", "{FDCF28}Скин:  (ID:264)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{265, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:265)", "{FDCF28}Скин:  (ID:265)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{266, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:266)", "{FDCF28}Скин:  (ID:266)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{267, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:267)", "{FDCF28}Скин:  (ID:267)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{268, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:268)", "{FDCF28}Скин:  (ID:268)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{269, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:269)", "{FDCF28}Скин:  (ID:269)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{270, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:270)", "{FDCF28}Скин:  (ID:270)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{271, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:271)", "{FDCF28}Скин:  (ID:271)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{272, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:272)", "{FDCF28}Скин:  (ID:272)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{273, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:273)", "{FDCF28}Скин:  (ID:273)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{274, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:274)", "{FDCF28}Скин:  (ID:274)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{275, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:275)", "{FDCF28}Скин:  (ID:275)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{276, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:276)", "{FDCF28}Скин:  (ID:276)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{277, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:277)", "{FDCF28}Скин:  (ID:277)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{278, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:278)", "{FDCF28}Скин:  (ID:278)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{279, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:279)", "{FDCF28}Скин:  (ID:279)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{280, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:280)", "{FDCF28}Скин:  (ID:280)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{281, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:281)", "{FDCF28}Скин:  (ID:281)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{282, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:282)", "{FDCF28}Скин:  (ID:282)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{283, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:283)", "{FDCF28}Скин:  (ID:283)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{284, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:284)", "{FDCF28}Скин:  (ID:284)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{285, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:285)", "{FDCF28}Скин:  (ID:285)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{286, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:286)", "{FDCF28}Скин:  (ID:286)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{287, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:287)", "{FDCF28}Скин:  (ID:287)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{288, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:288)", "{FDCF28}Скин:  (ID:288)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{289, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:289)", "{FDCF28}Скин:  (ID:289)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{290, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:290)", "{FDCF28}Скин:  (ID:290)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{291, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:291)", "{FDCF28}Скин:  (ID:291)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{292, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:292)", "{FDCF28}Скин:  (ID:292)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{293, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:293)", "{FDCF28}Скин:  (ID:293)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{294, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:294)", "{FDCF28}Скин:  (ID:294)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{295, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:295)", "{FDCF28}Скин:  (ID:295)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{296, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:296)", "{FDCF28}Скин:  (ID:296)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{297, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:297)", "{FDCF28}Скин:  (ID:297)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{298, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:298)", "{FDCF28}Скин:  (ID:298)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{299, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:299)", "{FDCF28}Скин:  (ID:299)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{300, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:300)", "{FDCF28}Скин:  (ID:300)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{301, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:301)", "{FDCF28}Скин:  (ID:301)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{302, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:302)", "{FDCF28}Скин:  (ID:302)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{303, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:303)", "{FDCF28}Скин:  (ID:303)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{304, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:304)", "{FDCF28}Скин:  (ID:304)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{305, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:305)", "{FDCF28}Скин:  (ID:305)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{306, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:306)", "{FDCF28}Скин:  (ID:306)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{307, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:307)", "{FDCF28}Скин:  (ID:307)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{308, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:308)", "{FDCF28}Скин:  (ID:308)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{309, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:309)", "{FDCF28}Скин:  (ID:309)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{310, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:310)", "{FDCF28}Скин:  (ID:310)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{311, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Skin", "Скин: (ID:311)", "{FDCF28}Скин:  (ID:311)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{18888, false, 0, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Skin", "Скин: ID(:)",  "Скин: (ID:20)", "{FFFFFF}Можно приобрести в магазине одежды,\nцентральном рынке, или с {FFD700}gold {FFFFFF}рулетки\nИспользуется для изменения внешнего\nвида персонажа. Можно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{19918, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Roulette Chest", "Сундук рулетки", "Предмет: {FDCF28}Сундук рулетки", "{FFFFFF}Выдается при регистрации на сервере. Нельзя продать, выкинуть, {FDCF28}обменять{ffffff}.\nМожно открывать каждые 10 минут игры в онлайне. При открытии вы можете получить\nзолотую или серебряную или бронзовую рулетки, которые можно крутить прямо в игре.", 161.000000, 174.000000, 126.000000, 1.225234},//сундук
    {11738, true,1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Aptechka", "Аптечка", "Предмет: {FDCF28}Аптечка", "{FFFFFF}Можно приобрести в магазине {FDCF28}24/7{FFFFFF},\nили на центральном рынке.\nПополняет здоровье на 100%\nМожно использовать.\nБыстрый доступ: {FDCF28}/usemed.", 0.000000, 351.000000, 180.000000, 1.100103},//аптечка
    {2663, true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Cheeps", "Чипсы", "Предмет: {FDCF28}Чипсы", "{FFFFFF}Можно приобрести в магазине {FDCF28}24/7{FFFFFF},\nили на центральном рынке.\nВосстанавливает голод.\nМожно использовать.\nБыстрый доступ: {FDCF28}/eat.", 0.000000, 5.000000, 333.000000, 1.256517},//чипсы
    {1924, false, 10000000, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "Fishki", "Фишки для казино", "Предмет: {FDCF28}Фишки для казино", "{FFFFFF}Можно получить в казино {FDCF28}4 Dragons{FFFFFF}\nЧтобы начать играть с игроком: {FDCF28}/dice.", 58.000000, 0.000000, 0.000000, 1.000000},//фишки
    {1951, true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Poison", "Яд", "Предмет: {FDCF28}Яд", "{FFFFFF}Можно приобрести в магазине {FDCF28}24/7{FFFFFF},\nили на центральном рынке.\nМожно использовать только тогда, когда у вас мало здоровья.\nБыстрый доступ: {FDCF28}/killme.", 0.000000, 360.000000, 216.000000, 1.032325},//яд
    {19627, true, 5, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Rep Pack", "Набор для починки", "Предмет: {FDCF28}Набор для починки", "{FFFFFF}Можно приобрести в любом магазине {FDCF28}АЗС{FFFFFF},\nили на центральном рынке.\nПолностью ремонтирует вашу машину.\nНеобходимо находиться в машине.\nМожно использовать.\nБыстрый доступ: {FDCF28}/repcar.", 87.000000, 0.000000, -42.000000, 1.000000},//набор для починки
    {19163, true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Mask", "Маска", "Предмет: {FDCF28}Маска", "{FFFFFF}Можно приобрести в магазине {FDCF28}24/7{FFFFFF},\nили на центральном рынке.\nСкрывает вас на мини-карте на 10 минут.\nМожно использовать.\nБыстрый доступ: {FDCF28}/mask.", 10.000000, 0.000000, -256.000000, 1.000000},//маска
    {19998, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Lighter", "Зажигалка", "Предмет: {FDCF28}Зажигалка", "{FFFFFF}Можно приобрести в магазине {FDCF28}24/7{FFFFFF},\nили на центральном рынке.\nВосстанавливает немного здоровья после использования.\nМожно использовать.\nБыстрый доступ: {FDCF28}/smoke.", 0.000000, 0.000000, 0.000000, 1.000000},//зажигалка
    {19625,  true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Cigarettes", "Сигарета", "Предмет: {FDCF28}Сигарета", "{FFFFFF}Можно приобрести в магазине {FDCF28}24/7{FFFFFF},\nили на центральном рынке.\nВосстанавливает немного здоровья после использования.\nМожно использовать.\nБыстрый доступ: {FDCF28}/smoke.", -90.000000, 0.000000, 35.000000, 1.000000},//сигареты
    {13646,  true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Gold Rulet", "Золотая рулетка", "Предмет: {FDCF28}Золотая рулетка", "{FFFFFF}Можно получить при ежедневных входах в игру,\nили купить на центральном рынке.\nИспользуется для получения{FFD700} рандомного {FFFFFF}товара\nиз списка доступного в этой рулетке.", 90.000000, 179.000000, 90.000000, 1.887382},//голда
    {1895,  true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Silver Rulet", "Серебряная рулетка", "Предмет: {FDCF28}Серебряная рулетка", "{FFFFFF}Можно получить при ежедневных входах в игру,\nили купить на центральном рынке.\nИспользуется для получения{FFD700} рандомного {FFFFFF}товара\nиз списка доступного в этой рулетке.", 0.000000, 0.000000, 0.000000, 1.934306},//серебро
    {1979,  true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Bronze Rulet", "Бронзовая рулетка", "Предмет: {FDCF28}Бронзовая рулетка", "{FFFFFF}Можно получить при ежедневных входах в игру,\nили купить на центральном рынке.\nИспользуется для получения{FFD700} рандомного {FFFFFF}товара\nиз списка доступного в этой рулетке.", 264.000000, 178.000000, 189.000000, 1.845672},//брноза
    {1486,  true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Beer", "Пиво", "Предмет: {FDCF28}Пиво", "{FFFFFF}Можно приобрести в магазине {FDCF28}24/7{FFFFFF},\nили на центральном рынке.\nВосстанавливает немного здоровья после использования.\nМожно использовать.\nБыстрый доступ: {FDCF28}/beer.", 333.000000, 12.000000, 286.000000, 0.928049},//пиво
    {2601, true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Sprunk", "Спранк", "Предмет: {FDCF28}Спранк", "{FFFFFF}Можно приобрести в любом магазине {FDCF28}АЗС{FFFFFF},\nили на центральном рынке.\nВосстанавливает здоровье.\nБыстрый доступ: {FDCF28}/sprunk.", 333.000000, 12.000000, 286.000000, 0.928049},//спранк
    {2894, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Phone Book", "Телефонная книга", "Предмет: {FDCF28}Телефонная книга", "{FFFFFF}Можно приобрести в любом магазине {FDCF28}АЗС{FFFFFF},\nили на центральном рынке.\nНаходит номера телефона по ID.\nНеобходимо находиться в машине.\nБыстрый доступ: {FDCF28}/number [ID].", 90.000000, 0.000000, 180.000000, 1.000000},//телефонная книга
    {11748,true, 5, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "break", "Скрепка", "Предмет: {FDCF28}Скрепка", "{FFFFFF}Можно приобрести в магазине {FDCF28}24/7{FFFFFF},\nили на центральном рынке.\nВзламывает транспорт.\nМожно использовать.\nБыстрый доступ: {FDCF28}/break.", 267.000000, 345.000000, 20.000000, 1.032325},//скрепка
    {18874, true, 1, "ксиаоми", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0xFFFFFFFF, "Xiaomi Mi 8 (White)", "Телефон Xiaomi Mi 8 (Белый)", "Предмет: {FDCF28}Телефон Xiaomi Mi 8 (Белый)", "{FFFFFF}Можно купить в любом салоне ''{FDCF28}Сотовая связь{FFFFFF}'',\nили на центральном рынке.\nИмеет набор стандартных функций телефона.\nБыстрый доступ {FDCF28}/phone", 90.000000, 180.000000, 0.000000, 1.000000},//телефон
    {1242, true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Armour", "Бронежилет", "Предмет: {FDCF28}Бронежилет", "{FFFFFF}Можно приобрести в магазине {FDCF28}24/7{FFFFFF},\nили на центральном рынке.\nПополняет броню на 100%.\nМожно использовать.\nБыстрый доступ: {FDCF28}/armour.", 360.000000, 360.000000, 8.000000, 0.980186},//броник
    {365,  true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Ballonchik", "Баллончик с краской", "Предмет: {FDCF28}Баллончик с краской", "{FFFFFF}Информация об этом предмете не указана", 360.000000, 360.000000, 8.000000, 0.980186},//балончик с краской
    {1650, true, 5, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Fuel", "Канистра", "Предмет: {FDCF28}Канистра", "{FFFFFF}Можно приобрести в любом магазине {FDCF28}АЗС{FFFFFF},\nили на центральном рынке.\nЗаправляет вашу машину на 15%.\nНеобходимо находиться в машине.\nМожно использовать.\nБыстрый доступ: {FDCF28}/fillcar.", 360.000000, 360.000000, 11.000000, 1.100103},//канистра
    {1288,  true, 5, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Supreme", "Наклейка Supreme", "Предмет: {FDCF28}Наклейка Supreme", "{FFFFFF}Можно купить за талоны у {FDCF28}Нейтона{FFFFFF},\nили на центральном рынке.\nДелает вашу машину красивой.\nБыстрый доступ {FDCF28}/supreme.", 178.000000, 90.000000, 360.000000, 1.584983},//суприм
    {2102, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Kolonka", "Колонка", "Аксессуар: {FDCF28}Колонка", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 193.000000, 0.872784},//колонка
    {2710,  false, 200, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "Podarok", "Подарок", "Предмет: {FDCF28}Подарок", "{FFFFFF}Можно найти в любом месте {FDCF28}города{FFFFFF},\nили на центральном рынке.\nМожно обменять на шкатулку у {FFD700}Эдварда.{FFFFFF}\nМожно использовать.", 149.000000, 187.000000, 134.000000, 1.006255},
	{2690, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Extinguisher", "Огнетушитель", "Аксессуар: {FDCF28}Огнетушитель", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 171.000000, 1.060479},
	{2045, true, 1, "1", "PUT", "HAѓET’", 0xf44242FF, 0x333333FF,  "Bat with nails", "Бита с гвоздями", "Аксессуар: {FDCF28}Бита с гвоздями", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 119.000000, 0.000000, 0.929092},
	{19590, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Sword", "Меч", "Аксессуар: {FDCF28}Меч", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 119.000000, 0.000000, 1.451511},
	{19631, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hammer", "Молот", "Аксессуар: {FDCF28}Молот", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 270.000000, 90.000000, 0.000000, 0.929092},
	{18963, true, 1, "1", "PUT", "HAѓET’", 0xf44242FF, 0x333333FF, "Maska CJ", "Маска CJ", "Аксессуар: {FDCF28}Маска CJ", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 114.000000, 0.725755},
	{19921, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Red Suitcase", "Красный чемодан", "Аксессуар: {FDCF28}Красный чемодан", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 270.000000, 0.000000, 0.000000, 1.304483},
	{19200, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Helmet", "Шлем", "Аксессуар: {FDCF28}Шлем", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 193.000000, 0.872784},
	{19036, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Maska", "Белая маска", "Аксессуар: {FDCF28}Белая маска", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 90.000000, 0.721063},
	{19037, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Maska", "Красная маска", "Аксессуар: {FDCF28}Красная маска", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 90.000000, 0.721063},
	{19038, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Maska", "Зеленая маска", "Аксессуар: {FDCF28}Зеленая маска", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 90.000000, 0.721063},
	{854, false, 200, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "Trash", "Мусор", "Предмет: {FDCF28}Мусор", "{FFFFFF}Информация об этом предмете не указана.", 298.000000, 0.000000, 0.000000, 1.000000},
	{826, false, 200, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "Resource: cotton", "Хлопок", "Предмет: {FDCF28}Хлопок", "{FFFFFF}Можно собрать на {FDCF28}ферме{FFFFFF}\nИспользуется для создания вещей в {FDCF28}подвале.", 161.000000, 174.000000, 126.000000, 1.225234},
	{2226, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Boombox", "Бумбокс", "Аксессуар: {FDCF28}Бумбокс", "{FFFFFF}Можно купить в меню {FDCF28}доната{FFFFFF},\nили купить на центральном рынке.\nМожно надеть. Можно использовать", 161.000000, 174.000000, 126.000000, 1.225234},
	{19090, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Blue hat", "Синяя шапка", "Аксессуар: {FDCF28}Синяя шапка", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 185.000000, 310.000000, 323.000000, 0.802919},
	{19091, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Red hat", "Красная шапка", "Аксессуар: {FDCF28}Красная шапка", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 185.000000, 310.000000, 323.000000, 0.802919},
	{19092, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Green hat", "Зеленая шапка", "Аксессуар: {FDCF28}Зеленая шапка", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 185.000000, 310.000000, 323.000000, 0.802919},
	{19904, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Vest", "Жилет", "Аксессуар: {FDCF28}Жилет", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 180.000000, 0.904066},
	{19469, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Neck Bandage", "Повязка на шею", "Аксессуар: {FDCF28}Повязка на шею", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 270.000000, 0.000000, 0.757038},
 	{333, true, 1, "1", "PUT", "HAѓET’", 0xf4dc41FF, 0x333333FF, "Klushka", "Клюшка", "Аксессуар: {FDCF28}Клюшка", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 123.000000, 19.000000, 0.000000, 1.001042},
 	{336, true, 1, "БитаАкс", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bat", "Бита", "Аксессуар: {FDCF28}Бита", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 131.000000, 26.000000, 85.000000, 1.001042},
 	{337, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Shovel", "Лопата", "Аксессуар: {FDCF28}Лопата", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 142.000000, 29.000000, 123.000000, 1.465067},
 	{338, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "cue", "Кий", "Аксессуар: {FDCF28}Кий", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 142.000000, 29.000000, 123.000000, 1.465067},
 	{339, true, 1, "КатанаАкс", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Katana", "Катана", "Аксессуар: {FDCF28}Катана", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 142.000000, 29.000000, 123.000000, 1.465067},
 	{326, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "cane", "Трость", "Аксессуар: {FDCF28}Трость", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 142.000000, 29.000000, 123.000000, 1.465067},
 	{18636, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Police Cap", "Полицейская кепка", "Аксессуар: {FDCF28}Полицейская кепка", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 142.000000, 29.000000, 123.000000, 1.465067},
 	{18637, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Shield", "Щит", "Аксессуар: {FDCF28}Щит", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 142.000000, 29.000000, 123.000000, 1.465067},
 	{3929, false, 200, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "Resource: stone", "Камень", "Ресурс: {FDCF28}Камень", "{FFFFFF}Можно выкопать на {FDCF28}шахте{FFFFFF},\nили купить на центральном рынке.\nИспользуется для создания предмета в подвале.", 236.000000, 0.000000, 0.000000, 1.558915},
 	{19941, false, 200, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "Resource: gold", "Золото", "Ресурс: {FDCF28}Золото", "{FFFFFF}Можно выкопать на {FDCF28}шахте{FFFFFF},\nили купить на центральном рынке.\nИспользуется для создания предмета в подвале.", 29.000000, 18.000000, 220.000000, 1.256517},
 	{17027, false, 200, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "Resource: silver", "Серебро", "Ресурс: {FDCF28}Серебро", "{FFFFFF}Можно выкопать на {FDCF28}шахте{FFFFFF},\nили купить на центральном рынке.\nИспользуется для создания предмета в подвале.", 251.000000, 0.000000, 0.000000, 1.392075},
 	{1314, false, 200, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "Family Talon", "Семейный талон", "Предмет: {FDCF28}Семейный талон", "{FFFFFF}Получается за выполнение {FDCF28}заданий{FFFFFF}.\nИспользуется для\nобмена на ценные товары у ЖК Аксиома({FDCF28}/GPS{FFFFFF})\nМожно приобрести на центральном рынке.", 182.000000, 169.000000, 190.000000, 1.287799},
 	{19874, true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Adrenaline Tablet", "Таблетка адреналина", "Предмет: {FDCF28}Таблетка адреналина", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nВосстанавливает здоровье на 50%.\nУскоряет ваш шаг на некоторое время.\nМожно использовать.", 76.000000, 219.000000, 0.000000, 0.835245},
 	{321, false, 1, "1", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0xf44242FF, "Penis", "Хуй", "Аксессуар: {FDCF28}Хуй", "{FFFFFF}Информация об этом предмете не указана", 236.000000, 0.000000, 0.000000, 1.558915},
 	{411, true, 1, "",  "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "certificate: infernus", "Infernus", "Сертификат: {FDCF28}Infernus", "{FFFFFF}Информация об этом предмете не указана", 160.000000, 174.000000, 195.000000, 1.000000},
 	{19591, true, 1, "1", "PUT", "HAѓET’", 0xf4dc41FF, 0x333333FF, "Veer made in china", "Веер", "Аксессуар: {FDCF28}Веер", "{FFFFFF}Информация об этом предмете не указана", 236.000000, 0.000000, 0.000000, 1.558915},
 	{411, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0xefaf40FF,0x333333FF, "certificate: Infernus", "Infernus", "Сертификат: {FDCF28}Infernus", "{FFFFFF}Информация об этом предмете не указана", 160.000000, 174.000000, 195.000000, 1.000000},
 	{415, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0xefaf40FF,0x333333FF, "certificate: Cheetah", "Cheetah", "Сертификат: {FDCF28}Cheetah", "{FFFFFF}Информация об этом предмете не указана", 160.000000, 174.000000, 195.000000, 1.000000},
 	{442, true, 1, "",  "USE", "…CЊO‡’€OBAT’", 0xefaf40FF,0x333333FF, "certificate: Romero", "Romero", "Сертификат: {FDCF28}Romero", "{FFFFFF}Информация об этом предмете не указана", 160.000000, 174.000000, 195.000000, 1.000000},
 	{451, true, 1, "",  "USE", "…CЊO‡’€OBAT’", 0xefaf40FF,0x333333FF, "certificate: Turismo", "Turismo", "Сертификат: {FDCF28}Turismo", "{FFFFFF}Информация об этом предмете не указана", 160.000000, 174.000000, 195.000000, 1.000000},
 	{495, true, 1, "",  "USE", "…CЊO‡’€OBAT’", 0xefaf40FF,0x333333FF, "certificate: Sandking", "Sandking", "Сертификат: {FDCF28}Sandking", "{FFFFFF}Информация об этом предмете не указана", 160.000000, 174.000000, 195.000000, 1.000000},
 	{494, true, 1, "",  "USE", "…CЊO‡’€OBAT’", 0xefaf40FF,0x333333FF, "certificate: Hotring Racer", "Hotring Racer", "Сертификат: {FDCF28}Hotring Racer", "{FFFFFF}Информация об этом предмете не указана", 160.000000, 174.000000, 195.000000, 1.000000},
 	{503, true, 1, "",  "USE", "…CЊO‡’€OBAT’", 0xefaf40FF,0x333333FF, "certificate: Hotring Racer", "Hotring Racer", "Сертификат: {FDCF28}Hotring Racer", "{FFFFFF}Информация об этом предмете не указана", 160.000000, 174.000000, 195.000000, 1.000000},
 	{502, true, 1, "",  "USE", "…CЊO‡’€OBAT’", 0xefaf40FF,0x333333FF, "certificate: Hotring Racer", "Hotring Racer", "Сертификат: {FDCF28}Hotring Racer", "{FFFFFF}Информация об этом предмете не указана", 160.000000, 174.000000, 195.000000, 1.000000},
 	{541, true, 1, "",  "USE", "…CЊO‡’€OBAT’", 0xefaf40FF, 0x333333FF, "certificate: Bullet", "Bullet", "Сертификат: {FDCF28}Bullet", "{FFFFFF}Информация об этом предмете не указана", 160.000000, 174.000000, 195.000000, 1.000000},
 	{560, true, 1, "",  "USE", "…CЊO‡’€OBAT’", 0xefaf40FF, 0x333333FF, "certificate: Sultan", "Sultan", "Сертификат: {FDCF28}Sultan", "{FFFFFF}Информация об этом предмете не указана", 160.000000, 174.000000, 195.000000, 1.000000},
 	{562, true, 1, "",  "USE", "…CЊO‡’€OBAT’", 0xefaf40FF, 0x333333FF, "certificate: Elegy", "Elegy", "Сертификат: {FDCF28}Elegy", "{FFFFFF}Информация об этом предмете не указана", 160.000000, 174.000000, 195.000000, 1.000000},
 	{579, true, 1, "",  "USE", "…CЊO‡’€OBAT’", 0xefaf40FF, 0x333333FF, "certificate: Huntley", "Huntley", "Сертификат: {FDCF28}Huntley", "{FFFFFF}Информация об этом предмете не указана", 160.000000, 174.000000, 195.000000, 1.000000},
 	{18874, true, 1, "белый", "USE", "…CЊO‡’€OBAT’",0x333333FF, 0x778899FF, "Google Pixel 3 (White)", "Телефон Google Pixel 3 (Белый)", "Предмет: {FDCF28}Телефон Google Pixel 3 (Белый)", "{FFFFFF}Можно купить в любом салоне ''{FDCF28}Сотовая связь{FFFFFF}'',\nили на центральном рынке.\nИмеет набор стандартных функций телефона.\nБыстрый доступ {FDCF28}/phone", 90.000000, 180.000000, 0.000000, 1.000000},//телефон
 	{18874, true, 1, "голубой", "USE", "…CЊO‡’€OBAT’",0x333333FF, 0x4286f4FF, "Google Pixel 3 (Blue)", "Телефон Google Pixel 3 (Голубой)", "Предмет: {FDCF28}Телефон Google Pixel 3 (Голубой)", "{FFFFFF}Можно купить в любом салоне ''{FDCF28}Сотовая связь{FFFFFF}'',\nили на центральном рынке.\nИмеет набор стандартных функций телефона.\nБыстрый доступ {FDCF28}/phone", 90.000000, 180.000000, 0.000000, 1.000000},
 	{18874, true, 1, "зеленый", "USE", "…CЊO‡’€OBAT’",0x333333FF, 0x1c9118FF, "Google Pixel 3 (Green)", "Телефон Google Pixel 3 (Зеленый)", "Предмет: {FDCF28}Телефон Google Pixel 3 (Зеленый)", "{FFFFFF}Можно купить в любом салоне ''{FDCF28}Сотовая связь{FFFFFF}'',\nили на центральном рынке.\nИмеет набор стандартных функций телефона.\nБыстрый доступ {FDCF28}/phone", 90.000000, 180.000000, 0.000000, 1.000000},//телефон
 	{18874, true, 1, "оранжевый", "USE", "…CЊO‡’€OBAT’",0x333333FF, 0xed9822FF, "Google Pixel 3 (Orange)", "Телефон Google Pixel 3 (Оранжевый)", "Предмет: {FDCF28}Телефон Google Pixel 3 (Оранжевый)", "{FFFFFF}Можно купить в любом салоне ''{FDCF28}Сотовая связь{FFFFFF}'',\nили на центральном рынке.\nИмеет набор стандартных функций телефона.\nБыстрый доступ {FDCF28}/phone", 90.000000, 180.000000, 0.000000, 1.000000},
 	{18874, true, 1, "золотой", "USE", "…CЊO‡’€OBAT’",0x333333FF, 0xedc423FF,  "Google Pixel 3 (Gold)", "Телефон Google Pixel 3 (Золотой)", "Предмет: {FDCF28}Телефон Google Pixel 3 (Золотой)", "{FFFFFF}Можно купить в любом салоне ''{FDCF28}Сотовая связь{FFFFFF}'',\nили на центральном рынке.\nИмеет набор стандартных функций телефона.\nБыстрый доступ {FDCF28}/phone", 90.000000, 180.000000, 0.000000, 1.000000},//телефон
 	{18874, true, 1, "розовый", "USE", "…CЊO‡’€OBAT’",0x333333FF, 0xE86868FF,  "Google Pixel 3 (Pink)", "Телефон Google Pixel 3 (Розовый)", "Предмет: {FDCF28}Телефон Google Pixel 3 (Розовый)", "{FFFFFF}Можно купить в любом салоне ''{FDCF28}Сотовая связь{FFFFFF}'',\nили на центральном рынке.\nИмеет набор стандартных функций телефона.\nБыстрый доступ {FDCF28}/phone", 90.000000, 180.000000, 0.000000, 1.000000},
 	{18874, true, 1, "черный", "USE", "…CЊO‡’€OBAT’",0x333333FF, 0x000000FF,  "Google Pixel 3 (Black)", "Телефон Google Pixel 3 (Черный)", "Предмет: {FDCF28}Телефон Google Pixel 3 (Черный)", "{FFFFFF}Можно купить в любом салоне ''{FDCF28}Сотовая связь{FFFFFF}'',\nили на центральном рынке.\nИмеет набор стандартных функций телефона.\nБыстрый доступ {FDCF28}/phone", 90.000000, 180.000000, 0.000000, 1.000000},//телефон
 	{18874, true, 1, "желтый", "USE", "…CЊO‡’€OBAT’",0x333333FF, 0xffee00FF,  "Google Pixel 3 (Yellow)", "Телефон Google Pixel 3 (Желтый)", "Предмет: {FDCF28}Телефон Google Pixel 3 (Желтый)", "{FFFFFF}Можно купить в любом салоне ''{FDCF28}Сотовая связь{FFFFFF}'',\nили на центральном рынке.\nИмеет набор стандартных функций телефона.\nБыстрый доступ {FDCF28}/phone", 90.000000, 180.000000, 0.000000, 1.000000},
 	{19487, true, 1, "1", "PUT", "HAѓET’", 0x1c9118FF, 0x333333FF, "Bell", "Колпак", "Аксессуар: {FDCF28}Колпак", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
 	{19352, true, 1, "1", "PUT", "HAѓET’", 0x1c9118FF, 0x333333FF, "Bell", "Колпак", "Аксессуар: {FDCF28}Колпак", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 25.000000, 0.000000, 1.00000},
 	{19350, true, 1, "1", "PUT", "HAѓET’", 0x1c9118FF, 0x333333FF, "mustache", "Усы", "Аксессуар: {FDCF28}Усы", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 90.000000, 90.000000, 1.00000},
 	{19318, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "White Guitar", "Белая гитара", "Аксессуар: {FDCF28}Белая гитара", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 189.000000, 138.000000, 0.000000, 0.959332},
 	{19319, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Black Guitar", "Черная гитара", "Аксессуар: {FDCF28}Черная гитара", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 189.000000, 138.000000, 0.000000, 0.959332},
 	{19317, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Red Guitar", "Красная гитара", "Аксессуар: {FDCF28}Красная гитара", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 189.000000, 138.000000, 0.000000, 0.959332},
 	{19472, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Respirator", "Респиратор", "Аксессуар: {FDCF28}Респиратор", "{FFFFFF}Можно получить за деньги у {FDCF28}банка ЛС{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{1276, true, 1, "1", "PUT", "HAѓET’", 0xf44242FF, 0x333333FF, "Amulet", "Амулет", "Аксессуар: {FDCF28}Амулет", "{FFFFFF}Информация об этом предмете не указана", 236.000000, 0.000000, 0.000000, 1.558915},
 	{19064, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "New Year Hat", "Новогодняя шапка", "Аксессуар: {FDCF28}Новогодняя шапка", "{FFFFFF}Можно получить за выполнение {FDCF28}квестов{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19065, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "New Year Hat", "Новогодняя шапка", "Аксессуар: {FDCF28}Новогодняя шапка", "{FFFFFF}Можно получить за выполнение {FDCF28}квестов{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19066, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "New Year Hat", "Новогодняя шапка", "Аксессуар: {FDCF28}Новогодняя шапка", "{FFFFFF}Можно получить за выполнение {FDCF28}квестов{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19054, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Accesories: Present", "Подарок (Аксессуар)", "Аксессуар: {FDCF28}Подарок", "{FFFFFF}Можно получить за выполнение {FDCF28}квестов{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19055, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Accesories: Present", "Подарок (Аксессуар)", "Аксессуар: {FDCF28}Подарок", "{FFFFFF}Можно получить за выполнение {FDCF28}квестов{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19056, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Accesories: Present", "Подарок (Аксессуар)", "Аксессуар: {FDCF28}Подарок", "{FFFFFF}Можно получить за выполнение {FDCF28}квестов{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19057, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Accesories: Present", "Подарок (Аксессуар)", "Аксессуар: {FDCF28}Подарок", "{FFFFFF}Можно получить за выполнение {FDCF28}квестов{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19058, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Accesories: Present", "Подарок (Аксессуар)", "Аксессуар: {FDCF28}Подарок", "{FFFFFF}Можно получить за выполнение {FDCF28}квестов{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19085, true, 1, "1", "PUT", "HAѓET’", 0xf44242FF, 0x333333FF, "eye patch", "Повязка на глаз", "Аксессуар: {FDCF28}Повязка на глаз", "{FFFFFF}Можно получить за выполнение {FDCF28}квестов{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19315, false, 200, "1", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "Resource: Corse Deer", "Тушка оленя", "Ресурс: {FDCF28}Тушка оленя", "{FFFFFF}Можно получить на охоте за оленями,\nили купить на центральном рынке.", 0.000000, 0.000000, 174.000000, 0.727320},
 	{11704, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Maska", "Маска демона", "Аксессуар: {FDCF28}Маска демона", "{FFFFFF}Можно получить в меню покупки {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19137, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Maska", "Маска петуха", "Аксессуар: {FDCF28}Маска петуха", "{FFFFFF}Можно получить в меню покупки {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
	{19346, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hot Dog", "Хотдог", "Аксессуар: {FDCF28}Хотдог", "{FFFFFF}Можно получить в меню покупки {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{6865, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Maska", "Маска кентавра", "Аксессуар: {FDCF28}Маска кентавра", "{FFFFFF}Можно получить в меню покупки {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{18952, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Helmet", "Боксерский шлем", "Аксессуар: {FDCF28}Боксерский шлем", "{FFFFFF}Можно получить в меню покупки {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19847, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Meat", "Мясо на спину", "Аксессуар: {FDCF28}Мясо на спину", "{FFFFFF}Можно получить в меню покупки {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19136, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Dreads", "Дреды", "Аксессуар: {FDCF28}Дреды", "{FFFFFF}Можно получить в меню покупки {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
	{11745, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bag for drugs", "Сумка для наркотиков", "Аксессуар: {FDCF28}Сумка для наркотиков", "{FFFFFF}Можно купить у {FDCF28}Гурмама{FFFFFF},\nили купить на центральном рынке.\nМожно надеть. С помощью этой сумки, Вы не будете терять вещи.", 0.0000, 0.0000, 90.0000, 1.0000},
	{19094, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Burger on head", "Бургер на голову", "Аксессуар: {FDCF28}Бургер на голову", "{FFFFFF}Можно получить в меню покупки {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19141, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Helmet SWAT", "Шлем SWAT", "Аксессуар: {FDCF28}Шлем SWAT", "{FFFFFF}Можно получить в меню покупки {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19314, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Horns on head", "Рога на голову", "Аксессуар: {FDCF28}Рога на голову", "{FFFFFF}Можно получить в меню покупки {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{2908, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Maska Zombie", "Маска зомби", "Аксессуар: {FDCF28}Маска зомби", "{FFFFFF}Можно получить в меню покупки {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
    {2803, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Meat bag", "Мешок с мясом", "Аксессуар: {FDCF28}Мешок с мясом", "{FFFFFF}Можно получить в меню {FDCF28}доната{FFFFFF},\nили купить на центральном рынке.\nМожно надеть. Можно использовать каждые 15 минут игры\nПополняет сытость на 100%", 182.000000, 190.000000, 259.000000, 1.001042},
    {19878, true, 1, "1", "PUT", "HAѓET’", 0xab9154FF, 0x333333FF, "Skate", "Скейт", "Аксессуар: {FDCF28}Скейт", "{FFFFFF}Можно приобрести в магазине аксессуаров,\nна центральном рынке, на праздничных евентах,\nили при использовании {FDCF28}gold рулетки.\nИспользуется для изменения внешнего вида персонажа. Можно надеть.\n{FDCF28}Использовать: Пробел", 220.000000, 146.000000, 156.000000, 1.001042},
    {18874, true, 1, "серебряный", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0xffee00FF, "Samsung Galaxy S10 (Silver)", "Телефон Samsung Galaxy S10 (Серебряный)", "Предмет: {FDCF28}Телефон Samsung Galaxy S10 (Серебряный)", "{FFFFFF}Можно купить в любом салоне ''{FDCF28}Сотовая связь{FFFFFF}'',\nили на центральном рынке.\nИмеет набор стандартных функций телефона.\nБыстрый доступ {FDCF28}/phone", 90.000000, 180.000000, 0.000000, 1.000000},
    {2406, true, 1, "", "PUT", "HAѓET’", 0xab9154FF, 0x333333FF, "Surf Skate", "Доска для серфинга", "Аксессуар: {FDCF28}Доска для серфинга", "{FFFFFF}Можно приобрести в магазине аксессуаров,\nна центральном рынке, на праздничных евентах,\nили при использовании {FDCF28}gold рулетки.\nИспользуется для изменения внешнего вида персонажа. Можно надеть.\n{FDCF28}Использовать: Пробел", 220.000000, 146.000000, 156.000000, 1.001042},
    {19636, true, 1, "1еу", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Kiosk", "Переносной ларек", "Аксессуар: {FDCF28}Переносной ларек", "{FFFFFF}Можно приобрести в {FDCF28}игровом магазине {FFFFFF}или\nна {FDCF28}центральном рынке{FFFFFF}. Дает возможность\nустановить ларек и продавать в нем, в\n{FDCF28}любом месте\n", 248.000000, 331.000000, 0.000000, 1.162147},
	{19421, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Headphones", "Наушники", "Аксессуар: {FDCF28}Наушники", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 120.000000, 0.000000, 0.000000, 1.000000},
 	{19422, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Headphones", "Наушники", "Аксессуар: {FDCF28}Наушники", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 120.000000, 0.000000, 0.000000, 1.000000},
 	{19423, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Headphones", "Наушники", "Аксессуар: {FDCF28}Наушники", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 120.000000, 0.000000, 0.000000, 1.000000},
 	{19424, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Headphones", "Наушники", "Аксессуар: {FDCF28}Наушники", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 120.000000, 0.000000, 0.000000, 1.000000},
 	{19069, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шапка", "Аксессуар: {FDCF28}Шапка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
 	{19068, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шапка", "Аксессуар: {FDCF28}Шапка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
 	{19067, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шапка", "Аксессуар: {FDCF28}Шапка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
 	{19554, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шапка", "Аксессуар: {FDCF28}Шапка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
 	{18953, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шапка", "Аксессуар: {FDCF28}Шапка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
 	{18954, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шапка", "Аксессуар: {FDCF28}Шапка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
 	{18968, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Panamka", "Панамка", "Аксессуар: {FDCF28}Панамка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 35.000000, 1.00000},
 	{18967, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Panamka", "Панамка", "Аксессуар: {FDCF28}Панамка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 35.000000, 1.00000},
 	{18969, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Panamka", "Панамка", "Аксессуар: {FDCF28}Панамка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 35.000000, 1.00000},
 	{18955, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Cap", "Кепка", "Аксессуар: {FDCF28}Кепка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, -180.000000, 1.00000},
 	{18956, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Cap", "Кепка", "Аксессуар: {FDCF28}Кепка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, -180.000000, 1.00000},
 	{18957, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Cap", "Кепка", "Аксессуар: {FDCF28}Кепка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, -180.000000, 1.00000},
 	{18959, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Cap", "Кепка", "Аксессуар: {FDCF28}Кепка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, -180.000000, 1.00000},
 	{18926, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Cap", "Кепка", "Аксессуар: {FDCF28}Кепка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, -180.000000, 1.00000},
 	{18927, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Cap", "Кепка", "Аксессуар: {FDCF28}Кепка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, -180.000000, 1.00000},
 	{18928, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Cap", "Кепка", "Аксессуар: {FDCF28}Кепка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, -180.000000, 1.00000},
 	{18929, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Cap", "Кепка", "Аксессуар: {FDCF28}Кепка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, -180.000000, 1.00000},
 	{18930, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Cap", "Кепка", "Аксессуар: {FDCF28}Кепка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, -180.000000, 1.00000},
 	{18931, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Cap", "Кепка", "Аксессуар: {FDCF28}Кепка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, -180.000000, 1.00000},
 	{18932, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Cap", "Кепка", "Аксессуар: {FDCF28}Кепка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, -180.000000, 1.00000},
 	{18933, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Cap", "Кепка", "Аксессуар: {FDCF28}Кепка", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, -180.000000, 1.00000},
 	{19104, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Helmet", "Каска", "Аксессуар: {FDCF28}Каска", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 0.000000, 90.000000, 1.00000},
 	{19105, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Helmet", "Каска", "Аксессуар: {FDCF28}Каска", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 0.000000, 90.000000, 1.00000},
 	{19106, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Helmet", "Каска", "Аксессуар: {FDCF28}Каска", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 0.000000, 90.000000, 1.00000},
 	{19107, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Helmet", "Каска", "Аксессуар: {FDCF28}Каска", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 0.000000, 90.000000, 1.00000},
 	{19108, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Helmet", "Каска", "Аксессуар: {FDCF28}Каска", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 0.000000, 90.000000, 1.00000},
 	{19109, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Helmet", "Каска", "Аксессуар: {FDCF28}Каска", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 0.000000, 90.000000, 1.00000},
 	{18925, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Beret", "Берет", "Аксессуар: {FDCF28}Берет", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 0.000000, 90.000000, 1.00000},
 	{18922, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Beret", "Берет", "Аксессуар: {FDCF28}Берет", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 0.000000, 90.000000, 1.00000},
 	{18923, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Beret", "Берет", "Аксессуар: {FDCF28}Берет", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 0.000000, 90.000000, 1.00000},
 	{18924, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Beret", "Берет", "Аксессуар: {FDCF28}Берет", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 0.000000, 90.000000, 1.00000},
    {18921, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Beret", "Берет", "Аксессуар: {FDCF28}Берет", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 0.000000, 90.000000, 1.00000},
 	{19519, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Wig", "Парик", "Аксессуар: {FDCF28}Парик", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19274, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Wig", "Парик", "Аксессуар: {FDCF28}Парик", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 182.000000, 190.000000, 259.000000, 1.001042},
 	{19011, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19012, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19013, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19014, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19015, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19016, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19017, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19018, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19019, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19024, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19027, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19028, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19029, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
    {19022, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19035, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19031, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19032, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{19033, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Glasses", "Очки", "Аксессуар: {FDCF28}Очки", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -20.000000, 0.000000, 90.000000, 1.000000},
 	{18911, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana", "Бандана", "Аксессуар: {FDCF28}Бандана", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
 	{18912, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana", "Бандана", "Аксессуар: {FDCF28}Бандана", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
 	{18913, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana", "Бандана", "Аксессуар: {FDCF28}Бандана", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
 	{18914, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana", "Бандана", "Аксессуар: {FDCF28}Бандана", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
 	{18915, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana", "Бандана", "Аксессуар: {FDCF28}Бандана", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
 	{18916, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana", "Бандана", "Аксессуар: {FDCF28}Бандана", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
 	{18917, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana", "Бандана", "Аксессуар: {FDCF28}Бандана", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
 	{18918, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana", "Бандана", "Аксессуар: {FDCF28}Бандана", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
 	{18919, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana", "Бандана", "Аксессуар: {FDCF28}Бандана", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
 	{18920, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana", "Бандана", "Аксессуар: {FDCF28}Бандана", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
    {18947, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шляпа", "Аксессуар: {FDCF28}Шляпа", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -15.000000, 0.000000, 0.000000, 1.00000},
    {18948, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шляпа", "Аксессуар: {FDCF28}Шляпа", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -15.000000, 0.000000, 0.000000, 1.00000},
    {18949, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шляпа", "Аксессуар: {FDCF28}Шляпа", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -15.000000, 0.000000, 0.000000, 1.00000},
    {18950, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шляпа", "Аксессуар: {FDCF28}Шляпа", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -15.000000, 0.000000, 0.000000, 1.00000},
    {18951, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шляпа", "Аксессуар: {FDCF28}Шляпа", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -15.000000, 0.000000, 0.000000, 1.00000},
    {19042, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Clock", "Часы", "Аксессуар: {FDCF28}Часы", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19041, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Clock", "Часы", "Аксессуар: {FDCF28}Часы", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19040, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Clock", "Часы", "Аксессуар: {FDCF28}Часы", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19039, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Clock", "Часы", "Аксессуар: {FDCF28}Часы", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19043, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Clock", "Часы", "Аксессуар: {FDCF28}Часы", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19044, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Clock", "Часы", "Аксессуар: {FDCF28}Часы", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19045, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Clock", "Часы", "Аксессуар: {FDCF28}Часы", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19046, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Clock", "Часы", "Аксессуар: {FDCF28}Часы", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19048, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Clock", "Часы", "Аксессуар: {FDCF28}Часы", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19049, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Clock", "Часы", "Аксессуар: {FDCF28}Часы", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19050, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Clock", "Часы", "Аксессуар: {FDCF28}Часы", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19051, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Clock", "Часы", "Аксессуар: {FDCF28}Часы", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19053, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Clock", "Часы", "Аксессуар: {FDCF28}Часы", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {3026, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Briefcase", "Портфель", "Аксессуар: {FDCF28}Портфель", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 15.000000, 0.000000, 1.00000},
    {371, true, 1, "ПортфельАкс", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Briefcase", "Портфель", "Аксессуар: {FDCF28}Портфель", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 12.000000, 0.000000, 1.00000},
    {19559, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Briefcase", "Портфель", "Аксессуар: {FDCF28}Портфель", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {18970, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шляпа", "Аксессуар: {FDCF28}Шляпа", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -15.000000, 0.000000, 0.000000, 1.00000},
    {18973, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шляпа", "Аксессуар: {FDCF28}Шляпа", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -15.000000, 0.000000, 0.000000, 1.00000},
    {18972, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шляпа", "Аксессуар: {FDCF28}Шляпа", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -15.000000, 0.000000, 0.000000, 1.00000},
    {18971, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Hat", "Шляпа", "Аксессуар: {FDCF28}Шляпа", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -15.000000, 0.000000, 0.000000, 1.00000},
    {18910, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana on head", "Бандана на голову", "Аксессуар: {FDCF28}Бандана на голову", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
    {18909, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana on head", "Бандана на голову", "Аксессуар: {FDCF28}Бандана на голову", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
    {18908, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana on head", "Бандана на голову", "Аксессуар: {FDCF28}Бандана на голову", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
    {18907, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana on head", "Бандана на голову", "Аксессуар: {FDCF28}Бандана на голову", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
    {18906, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bandana on head", "Бандана на голову", "Аксессуар: {FDCF28}Бандана на голову", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
	{18875, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Radio", "Радио", "Предмет: {FDCF28}Радио", "{FFFFFF}Можно купить в магазине{FDCF28}24/7{FFFFFF},\nили купить на центральном рынке.\nМожно использовать.", 303.000000, 360.000000, 195.000000, 0.948905},
    {18632, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Fishing rod", "Удочка", "Предмет: {FDCF28}Удочка", "{FFFFFF}Можно купить в магазине{FDCF28}24/7{FFFFFF},\nили купить на центральном рынке.\nМожно использовать.", 0.000000, 350.000000, 0.000000, 1.220020},
    {1554, false, 200, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "Worms", "Черви", "Предмет: {FDCF28}Черви", "{FFFFFF}Можно купить в магазине{FDCF28}24/7{FFFFFF},\nили купить на центральном рынке.\nПредназначен для наживки при ловле рыбы.", 0.000000, 350.000000, 182.000000, 1.204379},
    {2709, true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Tablets", "Таблетки от наркозависимости", "Предмет: {FDCF28}Таблетки от наркозависимости", "{FFFFFF}Можно купить в магазине{FDCF28}24/7{FFFFFF},\nили купить на центральном рынке.\nМожно использовать.", 0.000000, 0.000000, 0.000000, 1.000000},
    {1575, true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Drugs", "Наркотики", "Предмет: {FDCF28}Наркотики", "{FFFFFF}Информация об этом предмете не указана.\nМожно использовать.", 0.000000, 0.000000, 0.000000, 1.000000},
	{331, true, 1000, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Brass Knuckles", "Кастет", "Предмет: {FDCF28}Кастет", "{FFFFFF}Можно купить в магазине {FDCF28}оружия{FFFFFF}\nМожно использовать.", 0.000000, 27.000000, 134.000000, 1.978623},
	{335, true, 1000, "Бита", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Baseball bat (Weapon)", "Бита", "Предмет: {FDCF28}Бита", "{FFFFFF}Можно купить в магазине {FDCF28}оружия{FFFFFF}\nМожно использовать.", 0.000000, 27.000000, 134.000000, 1.978623},
	{339, true, 1000, "Катана", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Katana (Weapon)", "Катана", "Предмет: {FDCF28}Катана", "{FFFFFF}Можно купить в магазине {FDCF28}оружия{FFFFFF}\nМожно использовать.", 0.000000, 27.000000, 134.000000, 1.978623},
	{371, true, 1000, "Парашют", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Parachute", "Парашют", "Предмет: {FDCF28}Парашют", "{FFFFFF}Можно купить в магазине {FDCF28}оружия{FFFFFF}\nМожно использовать.", 0.000000, 27.000000, 134.000000, 1.978623},
	{343, true, 1000, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Teargas", "Дымовая Шашка", "Предмет: {FDCF28}Дымовая Шашка", "{FFFFFF}Можно купить в магазине {FDCF28}оружия{FFFFFF}\nМожно использовать.", 0.000000, 27.000000, 134.000000, 1.978623},
	{348, true, 1000, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Desert Eagle", "Desert Eagle", "Предмет: {FDCF28}Desert Eagle", "{FFFFFF}Можно купить в магазине {FDCF28}оружия{FFFFFF}\nМожно использовать.", 0.000000, 27.000000, 134.000000, 1.978623},
	{349, true, 1000, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Shotgun", "Shotgun", "Предмет: {FDCF28}Shotgun", "{FFFFFF}Можно купить в магазине {FDCF28}оружия{FFFFFF}\nМожно использовать.", 0.000000, 27.000000, 134.000000, 1.978623},
	{353, true, 1000, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "MP5", "MP5", "Предмет: {FDCF28}MP5", "{FFFFFF}Можно купить в магазине {FDCF28}оружия{FFFFFF}\nМожно использовать.", 0.000000, 27.000000, 134.000000, 1.978623},
	{355, true, 1000, "Калаш", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "AK-47", "AK-47", "Предмет: {FDCF28}AK-47", "{FFFFFF}Можно купить в магазине {FDCF28}оружия{FFFFFF}\nМожно использовать.", 0.000000, 27.000000, 134.000000, 1.978623},
	{356, true, 1000, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "M4", "M4", "Предмет: {FDCF28}M4", "{FFFFFF}Можно купить в магазине {FDCF28}оружия{FFFFFF}\nМожно использовать.", 0.000000, 27.000000, 134.000000, 1.978623},
	{357, true, 1000,  "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Country Rifle", "Country Rifle", "Предмет: {FDCF28}Country Rifle", "{FFFFFF}Можно купить в магазине {FDCF28}оружия{FFFFFF}\nМожно использовать.", 0.000000, 27.000000, 134.000000, 1.978623},
	{368, true, 1, "", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Night Vision Googles", "Очки ночного видения", "Аксессуар: {FDCF28}Очки ночного видения", "{FFFFFF}Можно обменять у Джозефа за тушки оленя в {FDCF28}лесу{FFFFFF}\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.000000},
	{1274, true, 10000, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "AZ Coins", "Талон AZ Coins", "Предмет: {FDCF28}Талон AZ Coins", "{FFFFFF}Можно получить за {FDCF28}квесты{FFFFFF}\nМожно использовать.", 0.000000, 0.000000, 0.000000, 1.000000},
	{16134, false, 200, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "Resource: bronze", "Бронза", "Ресурс: {FDCF28}Бронза", "{FFFFFF}Можно выкопать на {FDCF28}шахте{FFFFFF},\nили купить на центральном рынке.\nИспользуется для создания предмета в подвале.", 236.000000, 0.000000, 0.000000, 1.558915},
	{2936, false, 200, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "Resource: metal", "Метал", "Ресурс: {FDCF28}Метал", "{FFFFFF}Можно выкопать на {FDCF28}шахте{FFFFFF},\nили купить на центральном рынке.\nИспользуется для создания предмета в подвале.", 236.000000, 0.000000, 0.000000, 1.558915},
	{19079, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Parrot on", "Попугай на плечо", "Аксессуар: {FDCF28}Попугай на плечо", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
	{8492, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Wings", "Крылья на спину", "Аксессуар: {FDCF28}Крылья на спину", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
	{2511, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Air", "Самолетик", "Аксессуар: {FDCF28}Самолетик", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
	{11712, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Krest", "Крест", "Аксессуар: {FDCF28}Крест", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", -0.0000, 10.0000, 140.0000, 1.0000},
	{19521, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Policeman cap", "Фуражка полицейского", "Аксессуар: {FDCF28}Фуражка полицейского", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 90.000000, 90.000000, 0.000000, 1.000000},
	{11723, false, 100, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "Summer coin", "Летняя монета", "Предмет: {FDCF28}Летняя монета", "{FFFFFF}Можно получать каждый PayDay.\n{FFD700}Бессмысленный предмет", 90.000000, 0.000000, 90.000000, 0.811783},
	{355, false, 1, "КалашАкс", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "AK47", "Автомат Калашникова", "Предмет: {FDCF28}Автомат Калашникова", "{FFFFFF}Можно купить в магазине {FDCF28}оружия{FFFFFF}\nМожно использовать.", 0.000000, 27.000000, 134.000000, 1.978623},
	{2694, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Launch Stick", "Наклейка Launch", "Предмет: {FDCF28}Наклейка Launch", "{FFFFFF}Можно получить в донате.\n{FFD700}Можно использовать. Делает вашу машину красивой", 90.000000, 0.000000, 90.000000, 0.811783},
	{19882, true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Cook Fish", "Жареная рыба", "Предмет: {FDCF28}Жареная рыба", "{FFFFFF}Можно получить при приготовлении сырой рыбы\nна костре, или на центральном рынке.\nМожно использовать. Восстанавливает {FDCF28}20{FFFFFF} процентов голода.\nБыстрый доступ: {FDCF28}/jfish", 172.000000, 169.000000, 190.000000, 0.740354},
	{573, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Dune", "Сертификат Dune", "Сертификат: {FDCF28}Dune", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{451, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Turismo", "Сертификат Turismo", "Сертификат: {FDCF28}Turismo", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{541, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Bullet", "Сертификат Bullet", "Сертификат: {FDCF28}Bullet", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{411, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Infernus", "Сертификат Infernus", "Сертификат: {FDCF28}Infernus", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{560, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Sultan", "Сертификат Sultan", "Сертификат: {FDCF28}Sultan", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{495, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Sandking", "Сертификат Sandking", "Сертификат: {FDCF28}Sandking", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{415, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Cheetah", "Сертификат Cheetah", "Сертификат: {FDCF28}Cheetah", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{442, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Romero", "Сертификат Romero", "Сертификат: {FDCF28}Romero", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{428, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Securicar", "Сертификат Securicar", "Сертификат: {FDCF28}Securicar", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{494, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Hotring Racer", "Сертификат Hotring Racer", "Сертификат: {FDCF28}Hotring Racer", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{506, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Super GT", "Сертификат Super GT", "Сертификат: {FDCF28}Super GT", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{562, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Elegy", "Сертификат Elegy", "Сертификат: {FDCF28}Elegy", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{568, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Bandito", "Сертификат Bandito", "Сертификат: {FDCF28}Bandito", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{579, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Huntley", "Сертификат Huntley", "Сертификат: {FDCF28}Huntley", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{444, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Monster", "Сертификат Monster", "Сертификат: {FDCF28}Monster", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{522, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate NRG-500", "Сертификат NRG-500", "Сертификат: {FDCF28}NRG-500", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{528, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate FBI Truck", "Сертификат FBI Truck", "Сертификат: {FDCF28}FBI Truck", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{559, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Jester", "Сертификат Jester", "Сертификат: {FDCF28}Jester", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{571, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Kart", "Сертификат Kart", "Сертификат: {FDCF28}Kart", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{539, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Vortex", "Сертификат Vortex", "Сертификат: {FDCF28}Vortex", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{530, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Forklift", "Сертификат Forklift", "Сертификат: {FDCF28}Forklift", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{531, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Tractor", "Сертификат Tractor", "Сертификат: {FDCF28}Tractor", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{535, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Slamvan", "Сертификат Slamvan", "Сертификат: {FDCF28}Slamvan", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{561, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Stratum", "Сертификат Stratum", "Сертификат: {FDCF28}Stratum", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{599, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Police Ranger", "Сертификат Police Ranger", "Сертификат: {FDCF28}Police Ranger", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{1550, true, 5, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Money 5 000 000$", "Купон на 5 000 000$", "Данный портфель с суммой в {FDCF28}5 000 000$", "{FFFFFF}Можно открыть и получить деньги.", 160.000000, 174.000000, 195.000000, 1.000000},
	{2919, true, 10, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Money 2 000 000$", "Купон на 2 000 000$", "Данный портфель с суммой в {FDCF28}2 000 000$", "{FFFFFF}Можно открыть и получить деньги.", 160.000000, 174.000000, 195.000000, 1.000000},
	{1212, true, 15, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Money 1 000 000$", "Купон на 1 000 000$", "Данный портфель с суммой в {FDCF28}1 000 000$", "{FFFFFF}Можно открыть и получить деньги.", 160.000000, 174.000000, 195.000000, 1.000000},
	{18631, true, 100, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Ticket Exp", "Талон Exp", "Талон с опытом", "{FFFFFF}Можно открыть и получить опыт.", 160.000000, 174.000000, 195.000000, 1.000000},
	{19917, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Twin-Turbo", "Twin-Turbo: Тюнинг", "{FFFFFF}Можно установить на свой транспорт","Набор ускорит ваше транспортное средство!", 160.000000, 174.000000, 195.000000, 1.000000},
	{487, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Сertificate Maverick", "Сертификат Maverick", "Сертификат: {FDCF28}Maverick", "{FFFFFF}Можно расспоковать на Автобазаре.", 160.000000, 174.000000, 195.000000, 1.000000},
	{1829, false, 10000, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x4286f4FF, "EURO", "Евро", "Валюта: {FDCF28}ЕВРО", "{FFFFFF}\nМожно приобрести в банке или\nна центральном рынке. Необходим для хранения\nденежных средств в валюте.", 180.0000, 0.0000, 340.0000, 1.0000},
	{501, true, 1, "",  "USE", "…CЊO‡’€OBAT’", 0xefaf40FF,0x333333FF, "controller: Rc maverick", "Rc maverick", "Контроллер: {FDCF28}Rc maverick", "{FFFFFF}Вертолетик на радио управлении", 160.000000, 174.000000, 195.000000, 1.000000},
 	{441, true, 1, "",  "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "controller: Rc bandit", "Rc Bandit", "Контроллер: {FDCF28}Rc Bandit", "{FFFFFF}Машинка на радио управлении", 160.000000, 174.000000, 195.000000, 1.000000},
 	{464, true, 1, "",  "USE", "…CЊO‡’€OBAT’", 0xefaf40FF, 0x333333FF, "controller: Airoplane", "Airoplane", "Контроллер: {FDCF28}Airoplane", "{FFFFFF}Чтобы выйти введите /rc", 160.000000, 174.000000, 195.000000, 1.000000},
 	{3105, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Bell", "Костюм попугая", "Аксессуар: {FDCF28}Костюм попугая", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19823, true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Alco", "Виски", "Предмет: {FDCF28}Виски", "{FFFFFF}Можно приобрести в любом магазине {FDCF28}АЗС{FFFFFF},\nили на центральном рынке.\nВосстанавливает здоровье.", 337.000000, 0.000000, 0.000000, 1.000000},//виски
    {19824, true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Alco", "Коньяк", "Предмет: {FDCF28}Коньяк", "{FFFFFF}Можно приобрести в любом магазине {FDCF28}АЗС{FFFFFF},\nили на центральном рынке.\nВосстанавливает здоровье.", 337.000000, 0.000000, 0.000000, 1.000000},//коньяк
    {2814, true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Pizza", "Пицца", "Предмет: {FDCF28}Пицца", "{FFFFFF}Можно приобрести в любом магазине {FDCF28}АЗС{FFFFFF},\nили на центральном рынке.\nВосстанавливает здоровье.", -30.000000, 0.000000, 0.000000, 1.000000},//пицца
    {2768, true, 200, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Burger", "Бургер", "Предмет: {FDCF28}Бургер", "{FFFFFF}Можно приобрести в любом магазине {FDCF28}АЗС{FFFFFF},\nили на центральном рынке.\nВосстанавливает здоровье.", 0.000000, 0.000000, 110.000000, 1.000000},//бургер
	{2684, false, 1, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "License Auto", "Лицензия на авто", "Предмет: {FDCF28}Лицензия на авто", "{FFFFFF}Можно получить в автошколе города SF или\nв игровом магазине. Необходима для управления\n автомобилем. Имеет срок годности. Нельзя выкинуть\nили передать другому игроку.", 0.000000, 0.000000, 0.000000, 1.000000},
	{2684, false, 1, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "License Bike", "Лицензия на мото", "Предмет: {FDCF28}Лицензия на мото", "{FFFFFF}Можно получить в автошколе города SF или\nв игровом магазине. Необходима для управления\n автомобилем. Имеет срок годности. Нельзя выкинуть\nили передать другому игроку.", 0.000000, 0.000000, 0.000000, 1.000000},
	{2684, false, 1, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "License Boat", "Лицензия на лодочный транспорт", "Предмет: {FDCF28}Лицензия на лодочный транспорт", "{FFFFFF}Можно получить в автошколе города SF или\nв игровом магазине. Необходима для управления\n автомобилем. Имеет срок годности. Нельзя выкинуть\nили передать другому игроку.", 0.000000, 0.000000, 0.000000, 1.000000},
	{2684, false, 1, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "License Fly", "Лицензия на полеты", "Предмет: {FDCF28}Лицензия на полеты", "{FFFFFF}Можно получить в автошколе города SF или\nв игровом магазине. Необходима для управления\n автомобилем. Имеет срок годности. Нельзя выкинуть\nили передать другому игроку.", 0.000000, 0.000000, 0.000000, 1.000000},
	{2684, false, 1, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "License Gun", "Лицензия на оружие", "Предмет: {FDCF28}Лицензия на оружие", "{FFFFFF}Можно получить в автошколе города SF или\nв игровом магазине. Необходима для управления\n автомобилем. Имеет срок годности. Нельзя выкинуть\nили передать другому игроку.", 0.000000, 0.000000, 0.000000, 1.000000},
    {19332, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Воздушный шар #1", "Воздушный шар #1", "Воздушный шар #1", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно летать.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19333, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Воздушный шар #2", "Воздушный шар #2", "Воздушный шар #2", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно летать.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19334, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Воздушный шар #3", "Воздушный шар #3", "Воздушный шар #3", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно летать.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19335, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Воздушный шар #4", "Воздушный шар #4", "Воздушный шар #4", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно летать.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19336, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Воздушный шар #5", "Воздушный шар #5", "Воздушный шар #5" , "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно летать.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19337, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Воздушный шар #6", "Воздушный шар #6", "Воздушный шар #6", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно летать.", 0.000000, 0.000000, 0.000000, 1.00000},
    {19338, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Воздушный шар #7", "Воздушный шар #7", "Воздушный шар #7"  , "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно летать.", 0.000000, 0.000000, 0.000000, 1.00000},
    {1609, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Turtle on", "Черепаха на спину", "Аксессуар: {FDCF28}Черепаха на спину", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 160.000000, 174.000000, 195.000000, 1.000000},
	{16776, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Chicken on", "Курица на плечо", "Аксессуар: {FDCF28}Курица на плечо", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить в донате.\nМожно надеть.", 160.000000, 174.000000, 195.000000, 1.000000},
	{19064, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Новогодняя шапка", "Новогодняя шапка", "Аксессуар: {FDCF28}Новогодняя шапка", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
	{19065, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Новогодняя шапка с надписью Merry Xmas", "Новогодняя шапка с надписью Merry Xmas", "Аксессуар: {FDCF28}Новогодняя шапка с надписью Merry Xmas", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
	{19066, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Новогодняя шапка с надписью Happy Xmas", "Новогодняя шапка с надписью Happy Xmas", "Аксессуар: {FDCF28}Новогодняя шапка с надписью Happy Xmas", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
	{1212, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Деньги на спину", "Деньги на спину", "Аксессуар: {FDCF28}Деньги на спину", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
	{1254, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Череп на грудь", "Череп на грудь", "Аксессуар: {FDCF28}Череп на грудь", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
	{341, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Бензопила", "Бензопила", "Аксессуар: {FDCF28}Бензопила", "{FFFFFF}Можно получить в магазине {FDCF28}аксессуаров{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 112.000000, 2.368091},
	{3056, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Магнит на спину", "Магнит на спину", "Аксессуар: {FDCF28}Магнит на спину", "{FFFFFF}Можно получить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть.", 0.000000, 0.000000, 0.000000, 1.00000},
	{18846, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Hallowen Nabor", "Hallowen тюнинг", "Предмет: {FDCF28}Hallowen тюнинг", "{FFFFFF}Можно получить в донате.\n{FFD700}Можно использовать на модели: {FFFF00}Infernus, Chetah, Huntley, Maverick, Turismo, Clover\nАктивация: Use в инвентаре", 90.000000, 0.000000, 90.000000, 0.811783},
	{1097, true, 1, "", "USE", "…CЊO‡’€OBAT’", 0x333333FF, 0x333333FF, "Newyear Nabor", "Новогодний тюнинг", "Предмет: {FDCF28}Новогодний комплект тюнинга", "{FFFFFF}Можно получить в донате.\n{FFD700}Можно использовать на модели: {FFFF00}Infernus\nАктивация: Use в инвентаре", 90.000000, 0.000000, 90.000000, 0.811783},
	{11722, false, 100, "", "DROP", "B‘ЂPOC…T’", 0x333333FF, 0x333333FF, "Citizen Ticket", "Гражданский талон", "Предмет: {FDCF28}Гражданский талон", "{FFFFFF}Получается каждый PAYDAY если вы используете\nлаунчер{FDCF28} SER LAUNCH{FFFFFF}. Скачать можно на\nсайте проекта: {FDCF28}vk.com/arzser{FFFFFF}\nИспользуется для обмена на ценные товары у\nторговца ЭДВАРДА у площади Центрального банка.", 90.000000, 0.000000, 90.000000, 0.811783},
	{18635, true, 1, "1", "PUT", "HAѓET’", 0xf44242FF, 0x333333FF,  "Hummer", "Вечный молоток", "Аксессуар: {FDCF28}Вечный молоток", "{FFFFFF}Можно купить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nДаёт возможность бесплатно чинить авто - /molotok\n{FDCF28}Можно использовать раз в пол часа, полностью восстанавливает машину.", 90.000000, 119.000000, 0.000000, 0.929092},
	{2057, true, 1, "1", "PUT", "HAѓET’", 0xf44242FF, 0x333333FF,  "Bat with nails", "Волшебная канистра", "Аксессуар: {FDCF28}Волшебная канистра", "{FFFFFF}Можно создать в {FDCF28}подвале{FFFFFF},\nили купить на центральном рынке.\nДаёт возможность бесплатно заправлять авто - /canistra\n{FDCF28}Можно использовать раз в час. Заправляет машину на +50 бензина.", 90.000000, 119.000000, 0.000000, 0.929092},
	{19197, true, 1, "1", "PUT", "HAѓET’", 0x333333FF, 0x333333FF, "Angel ring", "Ангельское кольцо", "Аксессуар: {FDCF28}Ангельское кольцо", "{FFFFFF}Можно купить в {FDCF28}донате{FFFFFF},\nили купить на центральном рынке.\nМожно надеть. Каждые 5 секунд регенерирует ваше здоровье.\n{FDCF28}Восстанавливает 1 процент здоровья каждые 5 секунд.", 258.000000, 180.000000, 0.000000, 0.803962}
};

/*
stock RefreshInv2(playerid, slot)
{
    for(new i = 0; i < 6; i++)
	{
	    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
	}
	for(new i = 0; i < 7; i++)
	{
		    DestroyPlayerTD(playerid, fstd_p[playerid][i]);
	}
	for(new i = 0; i < 8; i++)
	{
	    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
	}
    InvSlotUpdate(playerid, slot, PlayerInfo[playerid][pInventory][slot]);
    PickInvent[playerid] = 73;
    return true;
}
stock UseItem(playerid, td, itemid)
{
                updateslot6(playerid);
		        new string[1500];
		        for(new i = 1; i < 312; i++)
				{
									if(PlayerInfo[playerid][pInventory][PickInvent[playerid]] == i)
									{
											PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][46], 0x333333FF);
											timeskin[playerid] = 0;
											if(PlayerInfo[playerid][pSkin] == 18)
											{
											    PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 0);
											}
											PlayerTextDrawHide(playerid, InvTextDraws[playerid][46]);
											PlayerTextDrawShow(playerid, InvTextDraws[playerid][46]);
									}
				}
				PlayerInfo[playerid][pDopKletki] = 0;
				for(new i = 0; i < 7; i++)
				{
										DestroyPlayerTD(playerid, fstd_p[playerid][i]);
				}
				for(new i = 0; i < 8; i++)
				{
				    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
				}
				for(new i = 0; i < 6; i++)
				{
										DestroyPlayerTD(playerid, InfoItems[playerid][i]);
				}
				for(new i = 0; i < 2; i++)
				{
				    PlayerTextDrawHide(playerid, TDinvTrash[playerid][i]);
				}
                if(ItemsInfo[PlayerInfo[playerid][pInventory][PickInvent[playerid]]][itemused] == false)
    			{
					if(musorka[playerid] == 0)
					{
					    RefreshInv2(playerid, td);
						SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Выкинуть предмет можно только рядом с мусоркой!");
					}
					if(musorka[playerid] >= 1)
					{
					    if(PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 313) return RefreshInv2(playerid, PickInvent[playerid]), SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}Этот предмет нельзя передавать!");
                		if(PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 316) return RefreshInv2(playerid, PickInvent[playerid]), SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}Этот предмет нельзя передавать!");
                        if(PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 538) return RefreshInv2(playerid, PickInvent[playerid]), SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}Этот предмет нельзя передавать!");
                        if(PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 590 || PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 591 || PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 592 ||
						PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 593 || PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 594) return RefreshInv2(playerid, PickInvent[playerid]), SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}Этот предмет нельзя передавать!");
						for(new i = 0; i < 30; i++)
					    {
					        if(mInfo[musorka[playerid]][InventoryTrash][i] != PlayerInfo[playerid][pInventory][PickInvent[playerid]]) continue;
					        mInfo[musorka[playerid]][InventoryTrash][i] = PlayerInfo[playerid][pInventory][PickInvent[playerid]];
					        mInfo[musorka[playerid]][InventoryTrashKolvo][i] += PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
					        new ID = mInfo[musorka[playerid]][InventoryTrash][i], IDS = PlayerInfo[playerid][pInventory][PickInvent[playerid]];
					        format(string, 330, "Игрок <a href=/logsaccount?name=%s>%s</a> положил в мусорку предмет %s в кол-ве %d.",PN(playerid),Name(playerid), ItemsInfo[IDS][ItemName2], PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]]);
							AllLogs(playerid, string);
							foreach(Player, g)
							{
								TrashSlotUpdate(g, i, ID);
							}
							PlayerInfo[playerid][pInventory][PickInvent[playerid]] = 0;
							PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]] = 0;
							RefreshInv2(playerid, PickInvent[playerid]);
							SaveTrash(musorka[playerid]);
							return true;
					    }
					    for(new i = 0; i < 30; i++)
					    {
					        if(mInfo[musorka[playerid]][InventoryTrash][i] != 0) continue;
					        mInfo[musorka[playerid]][InventoryTrash][i] = PlayerInfo[playerid][pInventory][PickInvent[playerid]];
					        mInfo[musorka[playerid]][InventoryTrashKolvo][i] = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
					        new ID = mInfo[musorka[playerid]][InventoryTrash][i], IDS = PlayerInfo[playerid][pInventory][PickInvent[playerid]];
					        format(string, 330, "Игрок <a href=/logsaccount?name=%s>%s</a> положил в мусорку предмет %s в кол-ве %d.",PN(playerid),Name(playerid), ItemsInfo[IDS][ItemName2], PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]]);
							AllLogs(playerid, string);
		        			foreach(Player, g)
							{
								TrashSlotUpdate(g, i, ID);
							}
							PlayerInfo[playerid][pInventory][PickInvent[playerid]] = 0;
							PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]] = 0;
					        RefreshInv2(playerid, PickInvent[playerid]);
							SaveTrash(musorka[playerid]);
							return true;
					    }
					}
					return true;
				}
				new Float:X, Float:Y, Float:Z, Float:A;
				GetPlayerPos(playerid,X,Y,Z);
				GetPlayerFacingAngle(playerid,A);
			    switch(itemid)
			    {
					case 573:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 550, 1);
							CreateOwnableCar(573,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Dune'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 451:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 551, 1);
							CreateOwnableCar(451,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Turismo'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 541:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 552, 1);
							CreateOwnableCar(541,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Bullet'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 411:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 553, 1);
							CreateOwnableCar(411,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Infernus'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 560:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 554, 1);
							CreateOwnableCar(560,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Sultan'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 495:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 555, 1);
							CreateOwnableCar(495,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Sandking'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 415:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 556, 1);
							CreateOwnableCar(415,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Cheetah'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 442:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 557, 1);
							CreateOwnableCar(442,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Romero'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 428:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 558, 1);
							CreateOwnableCar(428,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Securicar'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 494:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 559, 1);
							CreateOwnableCar(494,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Hotring Racer'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 506:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 560, 1);
							CreateOwnableCar(506,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Rancher'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 562:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 561, 1);
							CreateOwnableCar(562,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Elegy'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 568:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 562, 1);
							CreateOwnableCar(568,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Bandito'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 579:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 563, 1);
							CreateOwnableCar(579,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Huntley'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 444:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 564, 1);
							CreateOwnableCar(444,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Monster'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 522:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 565, 1);
							CreateOwnableCar(522,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'NRG-500'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 528:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 566, 1);
							CreateOwnableCar(528,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'FBI Truck'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 559:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 567, 1);
							CreateOwnableCar(559,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Jester'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 571:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 568, 1);
							CreateOwnableCar(571,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Kart'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 539:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 569, 1);
							CreateOwnableCar(539,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Vortex'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 530:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 570, 1);
							CreateOwnableCar(530,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Forklift'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 531:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 571, 1);
							CreateOwnableCar(531,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Tractor'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 535:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 572, 1);
							CreateOwnableCar(535,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Slamvan'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 561:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 573, 1);
							CreateOwnableCar(561,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Stratum'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 599:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 574, 1);
							CreateOwnableCar(599,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Police Ranger'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 487:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 580, 1);
							CreateOwnableCar(487,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Maverick'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 1650:
					{
						callcmd::fillcar(playerid,"");
					}

					case 19917:
					{
						//new tunningupdate;
					    if(PlayerInfo[playerid][pCheepsTimer] == 1) return RefreshInv2(playerid, td), SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}Между использованием предметов должно пройти 3 секунды!");
						if(!IsPlayerInHisVehicle(playerid)) return SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}Вы не находитесь в личном транспорте!"), RefreshInv2(playerid, td);
						if(IsPlayerInHisVehicle(playerid))
						{
						    {
								new vehid = GetPlayerVehicleID(playerid);
								new number = GetVehicleID(vehid);
								if(!IsPlayerInHisVehicle(playerid)) return SendClientMessage(playerid,COLOR_RED,"[Ошибка] {FFFFFF}Вы должны находится в личном транспорте!");
			    				if(CarInfo[number][cTwinTurbo] == 1) return SendClientMessage(playerid,COLOR_RED,"[Ошибка] {FFFFFF}У вас уже установлен TwinTurbo тюнинг!");
							    ShowPlayerDialogEx(playerid,0,0,"","{FFFFFF}- Поздравляем!\n\n{FFFFFF}Теперь вы владелец {ad6757}очень {ffffff}быстрого авто!\nС мощностью автомобиля в комплектации {d4b584}TWINTURBO{ffffff}, сравняться лишь единицы!\n\n\tПриятной игры","Окей","");
								PerfomenceInfo[GetPlayerVehicleID(playerid)][Discs] = 5;
						     	SaveTuning(GetPlayerVehicleID(playerid), "Discs", PerfomenceInfo[GetPlayerVehicleID(playerid)][Discs]);
						     	PerfomenceInfo[GetPlayerVehicleID(playerid)][Bridge] = 4;
						     	SaveTuning(GetPlayerVehicleID(playerid), "Bridge", PerfomenceInfo[GetPlayerVehicleID(playerid)][Bridge]);
				 		     	PerfomenceInfo[GetPlayerVehicleID(playerid)][Shock_absorbers] = 5;
						     	SaveTuning(GetPlayerVehicleID(playerid), "Shock_absorbers", PerfomenceInfo[GetPlayerVehicleID(playerid)][Shock_absorbers]);
								TuningMod(GetPlayerVehicleID(playerid));
								CarInfo[number][cTwinTurbo] = 1;
						     	PerfomenceInfo[GetPlayerVehicleID(playerid)][Engine] = 3;
						     	SaveTuning(GetPlayerVehicleID(playerid), "Engine", PerfomenceInfo[GetPlayerVehicleID(playerid)][Engine]);
				 		     	PerfomenceInfo[GetPlayerVehicleID(playerid)][Wheel] = 5;
						     	SaveTuning(GetPlayerVehicleID(playerid), "Wheel", PerfomenceInfo[GetPlayerVehicleID(playerid)][Wheel]);
								SaveOwnableCar(number);
								SaveOwnableCar(vehid);
							}
						}
						DeleteItem(playerid, 579, 1);
						closeuse(playerid);
					}
					case 1288:
					{
					    if(PlayerInfo[playerid][pCheepsTimer] == 1) return RefreshInv2(playerid, td), SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Между использованием предметов должно пройти 3 секунды!");
						if(!IsPlayerInHisVehicle(playerid)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Вы не находитесь в личном транспорте!"), RefreshInv2(playerid, td);
						if(IsPlayerInHisVehicle(playerid))
						{
							new vehid = GetPlayerVehicleID(playerid);
							new number = GetVehicleID(vehid);
							if(CarInfo[number][Supreme] == 1) return SendClientMessage(playerid,COLOR_LIGHTRED,"[Ошибка] {FFFFFF}Уже установлено!"), RefreshInv2(playerid, td);
							{
								CarInfo[number][Supreme] = 1;
								SupremeInstall(vehid);
								PlayerInfo[playerid][pSupreme] -=1;
								RefreshInv(playerid, td);
								ShowPlayerDialogEx(playerid, 0,0,"","{FFFFFF}Поздравляем! Вы установили наклейку {FAAC58}Supreme.{FFFFFF}\nТеперь ваш автомобиль будет выглядеть бомбезно!","Принять","");
						    }
						}
						closeuse(playerid);
					}
					case 1550:
			        {
			            closeuse(playerid);
						GiveMoneyRoulette(playerid,5000000);
						format(string,400,"Игрок <a href=/logsaccount?name=%s>%s</a> получил деньги $5000000 по причине: обменял талон на 5кк (Money: %d)",PN(playerid),PN(playerid),PlayerInfo[playerid][pMoney]);
						MoneyLogs(playerid, string, 0);
						AllLogs(playerid, string);
	                    DeleteItem(playerid, 575, 1);
					}
					case 2919:
			        {
			            closeuse(playerid);
						GiveMoneyRoulette(playerid,2000000);
						format(string,400,"Игрок <a href=/logsaccount?name=%s>%s</a> получил деньги $2000000 по причине: обменял талон на 2кк (Money: %d)",PN(playerid),PN(playerid),PlayerInfo[playerid][pMoney]);
						MoneyLogs(playerid, string, 0);
						AllLogs(playerid, string);
	                    DeleteItem(playerid, 576, 1);
					}
					case 18631:
					{
					    vremya[playerid] = PickInvent[playerid];
					    ShowPlayerDialogEx(playerid, 4401, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
					}
			        case 2694:
			        {
			            closeuse(playerid);
			            callcmd::launchinst(playerid);
					}
			        case 2601:
					{
						closeuse(playerid);
						callcmd::sprunk(playerid, "");
					}
					case 18846:
                    {
			            closeuse(playerid);
			            callcmd::HalloweenInstall(playerid);
					}
				 	case 1097:
                    {
			            closeuse(playerid);
			            callcmd::NewyearInstall(playerid);
					}
					case 19823:
					{
						new Float:Health;
						GetPlayerHealth(playerid,Health);
						DeleteItem(playerid, 586, 1);
						SaveInventory(playerid);
						format(string, sizeof(string), "%s выпил(а) бутылочку виски", cPN(playerid));
						ProxDetector(25.0, playerid, string, COLOR_PURPLE);
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_SPRUNK);
						if(Health <= 92.0) J_SetPlayerHealth(playerid,Health+8);
						else J_SetPlayerHealth(playerid,100);
						closeuse(playerid);
					}
					case 19824:
					{
						new Float:Health;
						GetPlayerHealth(playerid,Health);
						DeleteItem(playerid, 587, 1);
						SaveInventory(playerid);
						format(string, sizeof(string), "%s выпил(а) бутылочку коньяка", cPN(playerid));
						ProxDetector(25.0, playerid, string, COLOR_PURPLE);
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_SPRUNK);
						if(Health <= 92.0) J_SetPlayerHealth(playerid,Health+8);
						else J_SetPlayerHealth(playerid,100);
                        closeuse(playerid);
					}
					case 2814:
					{
						new Float:Health;
						GetPlayerHealth(playerid,Health);
						DeleteItem(playerid, 588, 1);
						SaveInventory(playerid);
						format(string, sizeof(string), "%s съел(а) пиццу", cPN(playerid));
						ProxDetector(25.0, playerid, string, COLOR_PURPLE);
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_SPRUNK);
						if(Health <= 92.0) J_SetPlayerHealth(playerid,Health+8);
						else J_SetPlayerHealth(playerid,100);
						closeuse(playerid);
					}
					case 2768:
					{
						new Float:Health;
						GetPlayerHealth(playerid,Health);
						DeleteItem(playerid, 589, 1);
						SaveInventory(playerid);
						format(string, sizeof(string), "%s съел(а) бургер", cPN(playerid));
						ProxDetector(25.0, playerid, string, COLOR_PURPLE);
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_SPRUNK);
						if(Health <= 92.0) J_SetPlayerHealth(playerid,Health+8);
						else J_SetPlayerHealth(playerid,100);
						closeuse(playerid);
					}
					case 2663:
					{
						eatcheeps(playerid);
					    closeuse(playerid);
					}
					case 19882:
					{
					    callcmd::jfish(playerid);
					    closeuse(playerid);
					}
					case 19904,18637:
					{
					    if(PlayerInfo[playerid][pSlotItem][3] != 0) return ShowPlayerDialogEx(playerid, 11103, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks4(playerid, itemid, PickInvent[playerid]);
					}
					case 19921,11745,19624:
					{
					    if(PlayerInfo[playerid][pSlotItem][4] != 0) return ShowPlayerDialogEx(playerid, 11104, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks5(playerid, itemid, PickInvent[playerid]);
					}
					case 19469,19421..19424,19079,1609,11712,19347,1254,16776,3105,3056,341,1212:
					{
					    if(PlayerInfo[playerid][pSlotItem][0] != 0) return ShowPlayerDialogEx(playerid, 11106, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks6(playerid, itemid, PickInvent[playerid]);
					}
					case 19039..19053:
					{
					    if(PlayerInfo[playerid][pSlotItem][6] != 0) return ShowPlayerDialogEx(playerid, 13000, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks7(playerid, itemid, PickInvent[playerid]);
					}
					case 19011..19019,19024,19027,19028,19029,19022,19035,19031,19032,19033:
					{
					    if(PlayerInfo[playerid][pSlotItem][7] != 0) return ShowPlayerDialogEx(playerid, 13001, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks8(playerid, itemid, PickInvent[playerid]);
					}
			        case 19874:
			        {
			            if(PlayerInfo[playerid][pCheepsTimer] == 1) return RefreshInv2(playerid, td), SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Между использованием предметов должно пройти 3 секунды!");
                        RefreshInv(playerid, td);
						closeuse(playerid);
      					new Float:Health;
						Adrenaline[playerid] = CreateDynamicPickup(1241,5, X,Y,Z,GetPlayerInterior(playerid),GetPlayerVirtualWorld(playerid),playerid);
						GetPlayerHealth(playerid,Health);
						format(string, sizeof(string), "%s закинулся таблеткой адреналина", cPN(playerid));
						ProxDetector(25.0, playerid, string, COLOR_PURPLE);
						ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1,0,0,0,0,0,1);
						SetTimerEx("ClearAnims2",900, 0, "d", playerid);
						if(Health <= 50.0) J_SetPlayerHealth(playerid,Health+50);
						else J_SetPlayerHealth(playerid,100);
						PlayerInfo[playerid][pSecondpage] = 0;
						SetTimer("DeletePickup", 1000, 0);
					}
			        case 19998:
			        {
						callcmd::smoke(playerid, "");
						closeuse(playerid);
			        }
			        case 19918:
					{
						if(PlayerInfo[playerid][pChestTime] > 0) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Время после прошлого использования ещё не прошло!"), RefreshInv2(playerid, td);
						if(GetInvSet(playerid) >= 72) return RefreshInv2(playerid, PickInvent[playerid]), SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}У вас не хватает места в инвентаре!");
						if(PlayerInfo[playerid][pLevel] <= 2) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Открывать этот сундук можно только с 3 уровня!"), RefreshInv2(playerid, td);
						PlayerInfo[playerid][pChestTime] = 3600;
						switch(random(101))
						{
							case 0..69:
								{
									SendClientMessage(playerid, COLOR_GREEN, !"Вы использовали сундук с рулетками и получили бронзовую рулетку!"); AddItem2(playerid);
								}
							case 70..90:
								{
									SendClientMessage(playerid, COLOR_GREEN, !"Вы использовали сундук с рулетками и получили серебряную рулетку!"); AddItem3(playerid);
								}
							case 91..100:
								{
								    SendClientMessage(playerid, COLOR_GREEN, !"Вы использовали сундук с рулетками и получили золотую рулетку!"); AddItem1(playerid);
								}
						}
						SaveInventory(playerid);
						RefreshInv2(playerid, td);
					}
					case 1979:
					{
					    for(new i = 0; i < 7; i++)
					    {
					        TextDrawHideForPlayer(playerid, others[i]);
						}
						for(new i = 0; i < 2; i++)
						{
						    DestroyPlayerTD(playerid, kletka[playerid][i]);
						}
						for(new i = 0; i < 63; i++)
					    {
					        DestroyPlayerTD(playerid,InvTextDraws[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,Govnishe[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,GovnisheKletki[playerid][i]);
					    }
					    for(new i = 0; i < 6; i++)
						{
						    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
						}
						for(new i = 0; i < 7; i++)
						{
						    DestroyPlayerTD(playerid, TDinv[playerid][i]);
						}
						for(new i = 0; i < 8; i++)
						{
						    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
						}
						for(new i = 0; i < 4; i++)
						{
						    PlayerTextDrawHide(playerid, TDinvTrash[playerid][i]);
						}
						ShowRoulette(playerid);
					}
					case 2894:
					{
						InvNumber(playerid);
						RefreshInv2(playerid, td);
						closeuse(playerid);
						CancelSelectTextDraw(playerid);
					}
     			case 18874:
					{
					    new IDS = PickInvent[playerid];
					    new ID = PlayerInfo[playerid][pInventory][IDS];
      					for(new i = 0; i < 63; i++)
					    {
					        DestroyPlayerTD(playerid,InvTextDraws[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,Govnishe[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,GovnisheKletki[playerid][i]);
					    }
					    for(new i = 0; i < 6; i++)
						{
						    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
						}
						for(new i = 0; i < 7; i++)
						{
						    DestroyPlayerTD(playerid, TDinv[playerid][i]);
						}
						for(new i = 0; i < 8; i++)
						{
						    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
						}
						for(new i = 0; i < 4; i++)
						{
						    PlayerTextDrawHide(playerid, TDinvTrash[playerid][i]);
						}
						if(PlayerInfo[playerid][pTelNum] == 0 || PlayerInfo[playerid][pTelNum] == 1) return CancelSelectTextDraw(playerid), SendClientMessage(playerid, COLOR_GREY, !"У вас нет мобильного телефона или sim карты!");
                        CreatePhoneTD(playerid);
						if(skinmenu[playerid]==1)
						{
							PlayerTextDrawDestroy(playerid,MenuSkin[playerid]);
							skinmenu[playerid]=0;
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "ксиаоми"))
						{
							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал белый Xiaomi Mi 8 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, Xiaomi[playerid][29], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, Xiaomi[playerid][8], string);
							}
							else
							{
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, Xiaomi[playerid][29], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, Xiaomi[playerid][8], string);
							}
							for(new i;i<58;i++)PlayerTextDrawShow(playerid,Xiaomi[playerid][i]);
							for(new i = 23; i < 26; i++) PlayerTextDrawShow(playerid, XiaomiVK[playerid][i]);
							TelephoneOpen[playerid] = 1;
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "серебряный"))
						{
							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал серебряный Samsung Galaxy S10 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, samsung[playerid][29], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, samsung[playerid][50], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, samsung[playerid][29], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, samsung[playerid][50], string);
							}
							for(new i;i<72;i++)PlayerTextDrawShow(playerid,samsung[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 10;
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "белый"))
						{
							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал белый Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 2;
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "голубой"))
						{
							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал голубой Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 3;
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "зеленый"))
						{
							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал зеленый Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 4;
							SelectTextDraw(playerid, 0xe86868ff);
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "оранжевый"))
						{

							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал оранжевый Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 5;
							SelectTextDraw(playerid, 0xe86868ff);
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "желтый"))
						{

							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал желтый Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 6;
							SelectTextDraw(playerid, 0xe86868ff);
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "розовый"))
						{

							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал розовый Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 7;
							SelectTextDraw(playerid, 0xe86868ff);
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "черный"))
						{

							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал черный Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 8;
							SelectTextDraw(playerid, 0xe86868ff);
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "золотой"))
						{

							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал золотой Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							TelephoneOpen[playerid] = 9;
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 9;
							SelectTextDraw(playerid, 0xe86868ff);
						}

					}
					case 1486:
					{
					    if(PlayerInfo[playerid][pCheepsTimer] == 1) return RefreshInv2(playerid, td), SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Между использованием предметов должно пройти 3 секунды!");
                        RefreshInv(playerid, td);
						closeuse(playerid);
                        callcmd::beer(playerid, "");
					}
					case 11748:
					{
					        callcmd::break(playerid, "");
							closeuse(playerid);
					}
					case 365:
					{
						RefreshInv(playerid, td);
					    ShowPlayerDialogEx(playerid,2393,1, "Введите цвет","{FFFFFF}Введите цвет 1 и цвет 2 через запятую\n{9ACD32}- Пример: {0AD6FF}132,132","Далее","Отмена");
					    closeuse(playerid);
						PlayerInfo[playerid][pRepBan] -=1;
						CancelSelectTextDraw(playerid);
					}
					case 1242:
					{
					    callcmd::armour(playerid);
						closeuse(playerid);
					}
					case 13646:
					{
					    for(new i = 0; i < 7; i++)
					    {
					        TextDrawHideForPlayer(playerid, others[i]);
						}
						for(new i = 0; i < 2; i++)
						{
						    DestroyPlayerTD(playerid, kletka[playerid][i]);
						}
						for(new i = 0; i < 63; i++)
					    {
					        DestroyPlayerTD(playerid,InvTextDraws[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,Govnishe[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,GovnisheKletki[playerid][i]);
					    }
					    for(new i = 0; i < 6; i++)
						{
						    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
						}
						for(new i = 0; i < 7; i++)
						{
						    DestroyPlayerTD(playerid, TDinv[playerid][i]);
						}
						for(new i = 0; i < 8; i++)
						{
						    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
						}
						for(new i = 0; i < 4; i++)
						{
						    PlayerTextDrawHide(playerid, TDinvTrash[playerid][i]);
						}
						PlayerInfo[playerid][pSecondpage] = 0;
						ShowRoulette(playerid);
					}
					case 1895:
					{
					    for(new i = 0; i < 7; i++)
					    {
					        TextDrawHideForPlayer(playerid, others[i]);
						}
						for(new i = 0; i < 2; i++)
						{
						    DestroyPlayerTD(playerid, kletka[playerid][i]);
						}
						for(new i = 0; i < 63; i++)
					    {
					        DestroyPlayerTD(playerid,InvTextDraws[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,Govnishe[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,GovnisheKletki[playerid][i]);
					    }
					    for(new i = 0; i < 6; i++)
						{
						    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
						}
						for(new i = 0; i < 7; i++)
						{
						    DestroyPlayerTD(playerid, TDinv[playerid][i]);
						}
						for(new i = 0; i < 8; i++)
						{
						    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
						}
						for(new i = 0; i < 4; i++)
						{
						    PlayerTextDrawHide(playerid, TDinvTrash[playerid][i]);
						}
						ShowRoulette(playerid);
					}
					case 1..311:
					{
					    if(InJob[playerid] == 1) return RefreshInv2(playerid, td);
				    	if(TeamDuty[playerid] == 1) return RefreshInv2(playerid, td);
				    	CheckSuka(playerid);
					}
					case 11738:
					{
						callcmd::usemed(playerid, "");
					    closeuse(playerid);
					}
		            case 1951:
		            {
		                callcmd::killme(playerid, "");
						closeuse(playerid);
					}
					case 19627:
					{
					    callcmd::repcar(playerid, "");
						closeuse(playerid);
					}
					case 19163:
					{
					    callcmd::mask(playerid, "");
						closeuse(playerid);
					}
					case 19625:
					{
					    callcmd::smoke(playerid, "");
						closeuse(playerid);
			        }
			        case 331:
			        {
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Brass Knuckles' с боеприпасами 1");
                      		RefreshInv(playerid, td);
		                    _GiveGun(playerid, 1, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
					case 371:
			        {
			            new ID = PlayerInfo[playerid][pInventory][PickInvent[playerid]];
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];

			            if(GetString(ItemsInfo[ID][ItemPhoneColor], "ПортфельАкс"))
			            {
			                if(PlayerInfo[playerid][pSlotItem][5] != 0) return ShowPlayerDialogEx(playerid, 11102, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
						    CheckAks(playerid, itemid, PickInvent[playerid]);
						}
			            if(GetString(ItemsInfo[ID][ItemPhoneColor], "Парашют"))
			            {
				            if(ID2 == 1)
			                {
			                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Parachute' с боеприпасами 1");
			                    RefreshInv(playerid, td);
			                    _GiveGun(playerid, 46, 1);
			                    closeuse(playerid);
							 	return true;
							}
							ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
							vremya[playerid] = PickInvent[playerid];
							PlayerInfo[playerid][pDolboeb] = 1;
						}
					}
					case 343:
			        {
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Tear gas' с боеприпасами 1");
		                    RefreshInv(playerid, td);
		                    _GiveGun(playerid, 17, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
					case 348:
			        {
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Desert Eagle' с боеприпасами 1");
		                    RefreshInv(playerid, td);
		                    _GiveGun(playerid, 24, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
					case 349:
			        {
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Shotgun' с боеприпасами 1");
		                    RefreshInv(playerid, td);
		                    _GiveGun(playerid, 25, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
					case 353:
			        {
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'MP5' с боеприпасами 1");
		                    RefreshInv(playerid, td);
		                    _GiveGun(playerid, 29, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
					case 355:
					{
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'AK47' с боеприпасами 1");
		                    RefreshInv(playerid, td);
		                    _GiveGun(playerid, 30, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
					case 356:
			        {
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'M4' с боеприпасами 1");
		                    RefreshInv(playerid, td);
		                    _GiveGun(playerid, 31, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
					case 357:
			        {
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Country Rifle' с боеприпасами 1");
		                    RefreshInv(playerid, td);
		                    _GiveGun(playerid, 33, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
			        case 336:
			        {
			            new ID = PlayerInfo[playerid][pInventory][PickInvent[playerid]];
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(GetString(ItemsInfo[ID][ItemPhoneColor], "БитаАкс"))
			            {
				            if(PlayerInfo[playerid][pSlotItem][5] != 0) return ShowPlayerDialogEx(playerid, 11102, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
						    CheckAks(playerid, itemid, PickInvent[playerid]);
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "Бита"))
			            {
			                if(ID2 == 1)
			                {
			                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Baseball Bat' с боеприпасами 1");
			                    RefreshInv(playerid, td);
			                    _GiveGun(playerid, 5, 1);
			                    closeuse(playerid);
							 	return true;
							}
				            ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
				            vremya[playerid] = PickInvent[playerid];
				            PlayerInfo[playerid][pDolboeb] = 1;
						}
					}
			        case 339:
			        {
			            new ID = PlayerInfo[playerid][pInventory][PickInvent[playerid]];
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(GetString(ItemsInfo[ID][ItemPhoneColor], "КатанаАкс"))
			            {
				            if(PlayerInfo[playerid][pSlotItem][5] != 0) return ShowPlayerDialogEx(playerid, 11102, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
						    CheckAks(playerid, itemid, PickInvent[playerid]);
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "Катана"))
			            {
			                if(ID2 == 1)
			                {
			                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Katana' с боеприпасами 1");
							 	RefreshInv(playerid, td);
			                    _GiveGun(playerid, 8, 1);
			                    closeuse(playerid);
							 	return true;
							}
				            ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
				            vremya[playerid] = PickInvent[playerid];
				            PlayerInfo[playerid][pDolboeb] = 1;
						}
					}
			        case 2102,2690,2045,19590,19631,2226,333337,338,326,19591,1276,19317,19319,19318,19054,19055,19056,19057,19058,19847,2803,19878,2406,3026,19559,19636,2511,8492,19332,19333,19334,19335,19336,19337,19338,18635,2057:
					{
					    if(PlayerInfo[playerid][pSlotItem][5] != 0) return ShowPlayerDialogEx(playerid, 11102, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks(playerid, itemid, PickInvent[playerid]);
					}
					case 18963,19036,19037,19038,19472,19350,19085,11704,6865,18911..18920,368:
					{
					    if(PlayerInfo[playerid][pSlotItem][1] != 0) return ShowPlayerDialogEx(playerid, 11101, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks2(playerid, itemid, PickInvent[playerid]);
					}
					case 19090..19091,19092,18636,19487,19352,19064,19065,19066,19200,19141,2908,19314,19094,19197,19136,18952,19346,19137,19067..19069,19554,18953,18954,18968,18967,18969,18955,18956,18957,18959,18926,18927,18928,18929,18930,18931,18932,18933,19104..19109,18921..18925,19519,19274,18906..18910,18970..18973,18947,18948,18949,18950,18951,19521:
					{
					    if(PlayerInfo[playerid][pSlotItem][2] != 0) return ShowPlayerDialogEx(playerid, 11100, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks3(playerid, itemid, PickInvent[playerid]);
					}
					case 18875:
					{
					    callcmd::radio(playerid, "");
					    closeuse(playerid);
					}
					case 18632:
					{
					    callcmd::go_fished(playerid, "");
					    closeuse(playerid);
					}
					case 2709:
					{
						callcmd::usebad(playerid, "");
						closeuse(playerid);
					}
					case 862:
					{
					    callcmd::usedrugs(playerid, "");
					    closeuse(playerid);
					}
					case 1274:
					{
					    vremya[playerid] = PickInvent[playerid];
					    ShowPlayerDialogEx(playerid, 4400, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
					}
            	}
				RefreshInv2(playerid, td);
	            return true;
}
stock InfoItem(playerid, td)
{
                new IDS = td;
		        new ID = PlayerInfo[playerid][pInventory][IDS];
				deletevy(playerid);
				updateslot6(playerid);
				new str[570];
				for(new i = 0; i < 312; i++)
				{
					if(PlayerInfo[playerid][pInventory][IDS] == i)
					{
						if(GetPlayerSkin(playerid) != 18)
						{
					    	PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 1);
					    	PlayerTextDrawHide(playerid, InvTextDraws[playerid][46]);
					    	PlayerTextDrawShow(playerid, InvTextDraws[playerid][46]);
						}
					}
				}
       			PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][IDS], 1);
      			for(new i = 0; i < 7; i++)
				{
											DestroyPlayerTD(playerid, fstd_p[playerid][i]);
				}
				for(new i = 0; i < 8; i++)
				{
				    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
				}
				for(new i = 0; i < 6; i++)
				{
											DestroyPlayerTD(playerid, InfoItems[playerid][i]);
				}
				if(PickInvent[playerid] != 73)
                {
                	PlayerTextDrawBackgroundColor(playerid, Govnishe[playerid][td], 0x333333FF);
                }
			    format(str, sizeof(str), "{FFFFFF}%s\n%s", ItemsInfo[ID][ItemName], ItemsInfo[ID][ItemInfos]);
				ShowPlayerDialogEx(playerid, 5555, 0, "Информация о предмете", str, "Выход", "");
				RefreshInv2(playerid, td);
                return true;
}
new daunsp[MAX_PLAYERS];
stock AddItem1(playerid)
{
    daunsp[playerid] = 1;
	AddItem(playerid, 322, 1);
    daunsp[playerid] = 0;
	return true;
}
stock AddItem2(playerid)
{
    daunsp[playerid] = 1;
	AddItem(playerid, 324, 1);
    daunsp[playerid] = 0;
	return true;
}
stock AddItemLavka(numberlavki, itemid, itemkolvo, money)
{
	for(new i = 0; i < 10; i++)
    {
        if(ItemsLavka[numberlavki][i] != 0) continue;
        ItemsLavka[numberlavki][i] = itemid;
        ItemsLavkaKolvo[numberlavki][i] = itemkolvo;
        CostLavkaItem[numberlavki][i] = money;
        return true;
    }
	return true;
}
stock AddItem3(playerid)
{
	daunsp[playerid] = 1;
	AddItem(playerid, 323, 1);
    daunsp[playerid] = 0;
	return true;
}
publics Custom_AddShkafItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,
		last_quantity,
		total_quantity,
		house = HouseEntered[playerid];

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(HouseInfo[house][hShkafSlotKol][slot] >= max_quantity) return 0;

	total_quantity = HouseInfo[house][hShkafSlotKol][slot] + quantity;
	if(total_quantity > max_quantity)
	{
		last_quantity = total_quantity - max_quantity;
		HouseInfo[house][hShkafSlotKol][slot] = max_quantity;
	}
	else HouseInfo[house][hShkafSlotKol][slot] += quantity;

	if(last_quantity)
    {
        for(new i = 0; i < 30; i++)
	    {
	        if(HouseInfo[house][hShkafSlot][i] != itemid) continue;
	        if(!CallLocalFunction("Custom_AddShkafItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	    for(new i = 0; i < 30; i++)
	    {
	        if(HouseInfo[house][hShkafSlot][i] != 0) continue;
	        if(!CallLocalFunction("Custom_SetShkafItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	}
	return 1;
}
publics Custom_SetShkafItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,
		last_quantity,
		house = HouseEntered[playerid];

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(HouseInfo[house][hShkafSlotKol][slot] >= max_quantity)return 0;

	if(quantity > max_quantity)
	{
		last_quantity = quantity - max_quantity;
		quantity = max_quantity;
	}

	HouseInfo[house][hShkafSlot][slot] = itemid;
    HouseInfo[house][hShkafSlotKol][slot] = quantity;
	ShkafSlotUpdate(playerid, slot, HouseInfo[house][hShkafSlot][slot]);
    if(last_quantity)
    {
        for(new i = 0; i < 30; i++)
	    {
	        if(HouseInfo[house][hShkafSlot][i] != itemid) continue;
	        if(!CallLocalFunction("Custom_AddShkafItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	    for(new i = 0; i < 30; i++)
	    {
	        if(HouseInfo[house][hShkafSlot][i] != 0) continue;
	        if(!CallLocalFunction("Custom_SetShkafItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	}
	return 1;
}
publics Custom_AddTrashItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,

		last_quantity,
		total_quantity,
		musor = musorka[playerid];

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(mInfo[musor][InventoryTrashKolvo][slot] >= max_quantity)return 0;

	total_quantity = mInfo[musor][InventoryTrashKolvo][slot] + quantity;
	if(total_quantity > max_quantity)
	{
		last_quantity = total_quantity - max_quantity;
		mInfo[musor][InventoryTrashKolvo][slot] = max_quantity;
	}
	else mInfo[musor][InventoryTrashKolvo][slot] += quantity;
    foreach(Player, g)
	{
	    if(musorka[g] != musorka[playerid]) continue;
		TrashSlotUpdate(g, slot, mInfo[musor][InventoryTrash][slot]);
	}
	if(last_quantity)
    {
        for(new i = 0; i < 30; i++)
	    {
	        if(mInfo[musor][InventoryTrash][i] != itemid) continue;
	        if(!CallLocalFunction("Custom_AddTrashItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	    for(new i = 0; i < 30; i++)
	    {
	        if(mInfo[musor][InventoryTrash][i] != 0) continue;
	        if(!CallLocalFunction("Custom_SetTrashItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	}
	return 1;
}
publics Custom_SetTrashItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,
		last_quantity,
		musor = musorka[playerid];

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(mInfo[musor][InventoryTrashKolvo][slot] >= max_quantity)return 0;

	if(quantity > max_quantity)
	{
		last_quantity = quantity - max_quantity;
		quantity = max_quantity;
	}

	mInfo[musor][InventoryTrash][slot] = itemid;
    mInfo[musor][InventoryTrashKolvo][slot] = quantity;
    foreach(Player, g)
	{
	    if(musorka[g] != musorka[playerid]) continue;
		TrashSlotUpdate(g, slot, mInfo[musor][InventoryTrash][slot]);
	}
    if(last_quantity)
    {
        for(new i = 0; i < 30; i++)
	    {
	        if(mInfo[musor][InventoryTrash][i] != itemid) continue;
	        if(!CallLocalFunction("Custom_AddTrashItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	    for(new i = 0; i < 30; i++)
	    {
	        if(mInfo[musor][InventoryTrash][i] != 0) continue;
	        if(!CallLocalFunction("Custom_SetTrashItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	}
	return 1;
}
publics Custom_AddTrunkItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,

		last_quantity,
		total_quantity,
		trunk = idaofcar[playerid];

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(TrunkInfo[trunk][tBagazhnikSlotKol][slot] >= max_quantity)return 0;

	total_quantity = TrunkInfo[trunk][tBagazhnikSlotKol][slot] + quantity;
	if(total_quantity > max_quantity)
	{
		last_quantity = total_quantity - max_quantity;
		TrunkInfo[trunk][tBagazhnikSlotKol][slot] = max_quantity;
	}
	else TrunkInfo[trunk][tBagazhnikSlotKol][slot] += quantity;
    foreach(Player, g)
	{
	    if(idaofcar[g] != idaofcar[playerid]) continue;
		BagazhnikSlotUpdate(g, slot, TrunkInfo[idaofcar[g]][tBagazhnikSlot][slot]);
	}
    if(last_quantity)
    {
        for(new i = 0; i < 30; i++)
	    {
	        if(TrunkInfo[trunk][tBagazhnikSlot][i] != itemid) continue;
	        if(!CallLocalFunction("Custom_AddTrunkItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	    for(new i = 0; i < 30; i++)
	    {
	        if(TrunkInfo[trunk][tBagazhnikSlot][i] != 0) continue;
	        if(!CallLocalFunction("Custom_SetTrunkItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	}
	return 1;
}
publics Custom_SetTrunkItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,
		last_quantity,
		trunk = idaofcar[playerid];

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(TrunkInfo[trunk][tBagazhnikSlotKol][slot] >= max_quantity)return 0;

	if(quantity > max_quantity)
	{
		last_quantity = quantity - max_quantity;
		quantity = max_quantity;
	}

	TrunkInfo[trunk][tBagazhnikSlot][slot] = itemid;
    TrunkInfo[trunk][tBagazhnikSlotKol][slot] = quantity;
	foreach(Player, g)
	{
	    if(idaofcar[g] != idaofcar[playerid]) continue;
		BagazhnikSlotUpdate(g, slot, TrunkInfo[idaofcar[g]][tBagazhnikSlot][slot]);
	}
    if(last_quantity)
    {
        for(new i = 0; i < 30; i++)
	    {
	        if(TrunkInfo[trunk][tBagazhnikSlot][i] != itemid) continue;
	        if(!CallLocalFunction("Custom_AddTrunkItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	    for(new i = 0; i < 30; i++)
	    {
	        if(TrunkInfo[trunk][tBagazhnikSlot][i] != 0) continue;
			if(!CallLocalFunction("Custom_SetTrunkItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	}
	return 1;
}
publics Custom_AddInvItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,

		last_quantity,
		total_quantity;

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(PlayerInfo[playerid][pInventoryKolvo][slot] >= max_quantity)return 0;

	total_quantity = PlayerInfo[playerid][pInventoryKolvo][slot] + quantity;
	if(total_quantity > max_quantity)
	{
		last_quantity = total_quantity - max_quantity;
		PlayerInfo[playerid][pInventoryKolvo][slot] = max_quantity;
	}
	else PlayerInfo[playerid][pInventoryKolvo][slot] += quantity;
    if(TradeDone[playerid] == -1) RefreshInv2(playerid, slot);
	if(last_quantity) CallLocalFunction("AddItem", "ddd", playerid, itemid, last_quantity);
	return 1;
}
publics Custom_SetInvItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,
		last_quantity;

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(PlayerInfo[playerid][pInventoryKolvo][slot] >= max_quantity)return 0;

	if(quantity > max_quantity)
	{
		last_quantity = quantity - max_quantity;
		quantity = max_quantity;
	}

	PlayerInfo[playerid][pInventory][slot] = itemid;
    PlayerInfo[playerid][pInventoryKolvo][slot] = quantity;
    InvSlotUpdate(playerid, slot, itemid);
    if(last_quantity) CallLocalFunction("AddItem", "ddd", playerid, itemid, last_quantity);
	return 1;
}

stock AddItem(playerid, itemid, amount)
{
	new string[180];
	new send;
	//new kdkd;
	if(GetInvSet(playerid) >= 72) return SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}У вас не хватает места в инвентаре!");
	if(TradeDone[playerid] != -1 || ShkafOpen[playerid] == 1 || PlayerInfo[playerid][pTrashOpen] == 1 || BagazhnikOpen[playerid] == 1)
	{
		for(new i = 0; i < 72; i++)
	    {
	        if(PlayerInfo[playerid][pInventory][i] != itemid) continue;
	        if(!Custom_AddInvItem(playerid, i, itemid, amount)) continue;
	        return 1;
	    }
	    for(new i = 0; i < 72; i++)
	    {
	        if(PlayerInfo[playerid][pInventory][i] != 0) continue;
	        if(!Custom_SetInvItem(playerid, i, itemid, amount)) continue;
	        return 1;
	    }
	}
	send = 1;
	if(itemid == 313) send = 0;
	if(itemid == 0) send = 0;
	if(itemid == 324) send = 0;
	if(itemid == 323) send = 0;
	if(itemid == 322) send = 0;
	if(send == 1)
	{
		if(amount >= 2)
		{
	    	format(string, sizeof(string), "[Инвентарь] {FFFFFF}Вам был добавлен предмет '%s' (%d шт). Чтобы открыть инвентарь, введите /invent.", ItemsInfo[itemid][ItemName2], amount);
			SendClientMessage(playerid, COLOR_YELLOW, string);
		}
		else
		{
		    format(string, sizeof(string), "[Инвентарь] {FFFFFF}Вам был добавлен предмет '%s'. Чтобы открыть инвентарь, введите /invent.", ItemsInfo[itemid][ItemName2], amount);
			SendClientMessage(playerid, COLOR_YELLOW, string);
		}
	}
	for(new i = 0; i < 72; i++)
    {
        if(PlayerInfo[playerid][pInventory][i] != itemid) continue;
        if(!Custom_AddInvItem(playerid, i, itemid, amount)) continue;
        return 1;
    }
    for(new i = 0; i < 72; i++)
    {
        if(PlayerInfo[playerid][pInventory][i] != 0) continue;
        if(!Custom_SetInvItem(playerid, i, itemid, amount)) continue;
        return 1;
    }
	SaveInventory(playerid);
    return 1;
}

publics DeleteItem(playerid, itemid, amount)
{
    for(new i = 0; i < 72; i++)
    {
        if(PlayerInfo[playerid][pInventory][i] != itemid) continue;
        new daun;
		daun = amount-PlayerInfo[playerid][pInventoryKolvo][i];
		PlayerInfo[playerid][pInventoryKolvo][i] -= amount;
		if(PlayerInfo[playerid][pInventoryKolvo][i] <= -1)
		{
		    PlayerInfo[playerid][pInventoryKolvo][i] = 0;
		    PlayerInfo[playerid][pInventory][i] = 0;
      		CallLocalFunction("DeleteItem", "ddd", playerid, itemid, daun);
		}
		RefreshInv2(playerid, i);
        return 1;
    }
    return 1;
}
stock AddItemOn(playerid, itemid, amount)
{
    if(	PlayerInfo[playerid][pInventory][0] != 0 && PlayerInfo[playerid][pInventory][1] != 0 &&
		PlayerInfo[playerid][pInventory][2] != 0 && PlayerInfo[playerid][pInventory][3] != 0 &&
		PlayerInfo[playerid][pInventory][4] != 0 && PlayerInfo[playerid][pInventory][5] != 0 &&
		PlayerInfo[playerid][pInventory][6] != 0 && PlayerInfo[playerid][pInventory][7] != 0 &&
		PlayerInfo[playerid][pInventory][8] != 0 && PlayerInfo[playerid][pInventory][9] != 0 &&
		PlayerInfo[playerid][pInventory][10] != 0 && PlayerInfo[playerid][pInventory][11] != 0 &&
		PlayerInfo[playerid][pInventory][12] != 0 && PlayerInfo[playerid][pInventory][13] != 0 &&
		PlayerInfo[playerid][pInventory][14] != 0 && PlayerInfo[playerid][pInventory][15] != 0 &&
		PlayerInfo[playerid][pInventory][16] != 0 && PlayerInfo[playerid][pInventory][17] != 0 &&
		PlayerInfo[playerid][pInventory][18] != 0 && PlayerInfo[playerid][pInventory][19] != 0 &&
		PlayerInfo[playerid][pInventory][20] != 0 && PlayerInfo[playerid][pInventory][21] != 0 &&
		PlayerInfo[playerid][pInventory][22] != 0 && PlayerInfo[playerid][pInventory][23] != 0 &&
		PlayerInfo[playerid][pInventory][24] != 0 && PlayerInfo[playerid][pInventory][25] != 0 &&
		PlayerInfo[playerid][pInventory][26] != 0 && PlayerInfo[playerid][pInventory][27] != 0 &&
		PlayerInfo[playerid][pInventory][28] != 0 && PlayerInfo[playerid][pInventory][29] != 0 &&
		PlayerInfo[playerid][pInventory][30] != 0 && PlayerInfo[playerid][pInventory][31] != 0 &&
		PlayerInfo[playerid][pInventory][32] != 0 && PlayerInfo[playerid][pInventory][33] != 0 &&
		PlayerInfo[playerid][pInventory][34] != 0 && PlayerInfo[playerid][pInventory][35] != 0 &&
		PlayerInfo[playerid][pInventory][36] != 0 && PlayerInfo[playerid][pInventory][37] != 0 &&
		PlayerInfo[playerid][pInventory][38] != 0 && PlayerInfo[playerid][pInventory][39] != 0 &&
		PlayerInfo[playerid][pInventory][40] != 0 && PlayerInfo[playerid][pInventory][41] != 0 &&
		PlayerInfo[playerid][pInventory][42] != 0 && PlayerInfo[playerid][pInventory][43] != 0 &&
		PlayerInfo[playerid][pInventory][44] != 0 && PlayerInfo[playerid][pInventory][45] != 0 &&
		PlayerInfo[playerid][pInventory][46] != 0 && PlayerInfo[playerid][pInventory][47] != 0 &&
		PlayerInfo[playerid][pInventory][48] != 0 && PlayerInfo[playerid][pInventory][49] != 0 &&
		PlayerInfo[playerid][pInventory][50] != 0 && PlayerInfo[playerid][pInventory][51] != 0 &&
		PlayerInfo[playerid][pInventory][52] != 0 && PlayerInfo[playerid][pInventory][53] != 0 &&
		PlayerInfo[playerid][pInventory][54] != 0 && PlayerInfo[playerid][pInventory][55] != 0 &&
		PlayerInfo[playerid][pInventory][56] != 0 && PlayerInfo[playerid][pInventory][57] != 0 &&
		PlayerInfo[playerid][pInventory][58] != 0 && PlayerInfo[playerid][pInventory][59] != 0 &&
		PlayerInfo[playerid][pInventory][60] != 0 && PlayerInfo[playerid][pInventory][61] != 0 &&
		PlayerInfo[playerid][pInventory][62] != 0 && PlayerInfo[playerid][pInventory][63] != 0 &&
		PlayerInfo[playerid][pInventory][64] != 0 && PlayerInfo[playerid][pInventory][65] != 0 &&
		PlayerInfo[playerid][pInventory][66] != 0 && PlayerInfo[playerid][pInventory][67] != 0 &&
		PlayerInfo[playerid][pInventory][68] != 0 && PlayerInfo[playerid][pInventory][69] != 0 &&
		PlayerInfo[playerid][pInventory][70] != 0 && PlayerInfo[playerid][pInventory][71] != 0)
	{
		return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}У вас не хватает места в инвентаре!");
	}
    for(new i = 0; i < 72; i++)
    {
        if(PlayerInfo[playerid][pInventory][i] != itemid) continue;
        PlayerInfo[playerid][pInventoryKolvo][i] = amount;
        return true;
    }
    for(new i = 0; i < 72; i++)
    {
        if(PlayerInfo[playerid][pInventory][i] != 0) continue;
        PlayerInfo[playerid][pInventory][i] = itemid;
        PlayerInfo[playerid][pInventoryKolvo][i] = amount;
        return true;
    }
	SaveInventory(playerid);
    return true;
}

DestroyPlayerTD(playerid, &PlayerText:td)
{
	if(td != PlayerText:-1)
	{
		PlayerTextDrawDestroy(playerid, td);
		td = PlayerText:-1;
	}
	return true;
}


stock ShowInventory(playerid) // Функция
{
		DestroyPlayerTD(playerid, kletka[playerid][0]);
		DestroyPlayerTD(playerid, kletka[playerid][1]);
        for(new i = 0; i < 63; i++)
	    {
	        DestroyPlayerTD(playerid,InvTextDraws[playerid][i]);
	    }
	    for(new i = 0; i < 72; i++)
	    {
	        DestroyPlayerTD(playerid,Govnishe[playerid][i]);
	    }
	    for(new i = 0; i < 72; i++)
	    {
	        DestroyPlayerTD(playerid,GovnisheKletki[playerid][i]);
	    }
	    for(new i = 0; i < 4; i++)
	    {
	        DestroyPlayerTD(playerid, TDinvTrash[playerid][i]);
		}
		for(new i = 0; i < 6; i++)
	    {
	        DestroyPlayerTD(playerid, InfoItems[playerid][i]);
		}
		for(new i = 0; i < 6; i++)
	    {
	        DestroyPlayerTD(playerid, fstd_p[playerid][i]);
		}
	    DauningStreet2(playerid);
	    for(new i = 0; i < 72; i++){
		    PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][i], 1);
		}
		for(new a = 0; a < 72; a++)
	    {
	        if(PlayerInfo[playerid][pDopInv][a] == 1)
	        {
	            PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][a], 0);
				PlayerTextDrawColor(playerid, Govnishe[playerid][a], 0x777777FF);
			}
		}
	    SetPVarInt(playerid, "Kletki", 0);
	    SetPlayerChatBubble(playerid, "Заглянул в карман.", COLOR_PURPLE, 10.0, 1500);
		new string[128];
	    new Float:health;
     	AndruxaTop[playerid] = 1;
      	if(IsPlayerInHisVehicle(playerid)) //
		{
		    //машина
		    GetVehicleHealth(GetPlayerVehicleID(playerid), health);
		    format(string,sizeof(string),"HP: %.0f",health);
		    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][13], string);


			PlayerTextDrawLetterSize(playerid, InvTextDraws[playerid][47], 0.480000, 1.120000);
			PlayerTextDrawTextSize(playerid, InvTextDraws[playerid][47], 90.072655, 87.888893);
			PlayerTextDrawAlignment(playerid, InvTextDraws[playerid][47], 1);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][47], 0xFFFFFFFF);
			PlayerTextDrawUseBox(playerid, InvTextDraws[playerid][47], 0);
			PlayerTextDrawBoxColor(playerid, InvTextDraws[playerid][47], 0x80808080);
			PlayerTextDrawSetShadow(playerid, InvTextDraws[playerid][47], 2);
			PlayerTextDrawSetOutline(playerid, InvTextDraws[playerid][47], 0);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][47], 0x33333300);
			PlayerTextDrawFont(playerid, InvTextDraws[playerid][47], 5);
			PlayerTextDrawSetProportional(playerid, InvTextDraws[playerid][47], 1);
			PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][47], 0);
			PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][47], GetVehicleModel(GetPlayerVehicleID(playerid)));
			PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][47], 352.000000, 345.000000, 20.000000, 1.032325);

			DestroyPlayerTD(playerid, InvTextDraws[playerid][14]);
			DestroyPlayerTD(playerid, InvTextDraws[playerid][45]);
			DestroyPlayerTD(playerid, InvTextDraws[playerid][46]);

			DestroyPlayerTD(playerid, InvTextDraws[playerid][43]);
			DestroyPlayerTD(playerid, InvTextDraws[playerid][41]);
			DestroyPlayerTD(playerid, InvTextDraws[playerid][39]);
			DestroyPlayerTD(playerid, InvTextDraws[playerid][37]);
			DestroyPlayerTD(playerid, InvTextDraws[playerid][35]);
			DestroyPlayerTD(playerid, InvTextDraws[playerid][33]);


			InvTextDraws[playerid][14] = CreatePlayerTextDraw(playerid, 341.000000, 186.785217, "HUD:radar_centre");
			PlayerTextDrawLetterSize(playerid, InvTextDraws[playerid][14], 0.480000, 1.120000);
			PlayerTextDrawTextSize(playerid, InvTextDraws[playerid][14], 9.661929, 8.351837);
			PlayerTextDrawAlignment(playerid, InvTextDraws[playerid][14], 1);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][14], 0xFFFFFFFF);
			PlayerTextDrawUseBox(playerid, InvTextDraws[playerid][14], 0);
			PlayerTextDrawBoxColor(playerid, InvTextDraws[playerid][14], 0x80808080);
			PlayerTextDrawSetShadow(playerid, InvTextDraws[playerid][14], 2);
			PlayerTextDrawSetOutline(playerid, InvTextDraws[playerid][14], 0);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][14], 0x000000FF);
			PlayerTextDrawFont(playerid, InvTextDraws[playerid][14], 4);
			PlayerTextDrawSetProportional(playerid, InvTextDraws[playerid][14], 1);
			PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][14], 1);

			InvTextDraws[playerid][45] = CreatePlayerTextDraw(playerid, 390.469238, 190.790771, "usebox");
			PlayerTextDrawLetterSize(playerid, InvTextDraws[playerid][45], 0.000000, 0.045320);
			PlayerTextDrawTextSize(playerid, InvTextDraws[playerid][45], 350.661926, 0.000000);
			PlayerTextDrawAlignment(playerid, InvTextDraws[playerid][45], 1);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][45], 0xE1E1E1FF);
			PlayerTextDrawUseBox(playerid, InvTextDraws[playerid][45], 1);
			PlayerTextDrawBoxColor(playerid, InvTextDraws[playerid][45], 0x6C7B9570);
			PlayerTextDrawSetShadow(playerid, InvTextDraws[playerid][45], 2);
			PlayerTextDrawSetOutline(playerid, InvTextDraws[playerid][45], 0);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][45], 0x000000FF);
			PlayerTextDrawFont(playerid, InvTextDraws[playerid][45], 0);
			PlayerTextDrawSetProportional(playerid, InvTextDraws[playerid][45], 1);
			PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][45], 0);

			InvTextDraws[playerid][46] = CreatePlayerTextDraw(playerid, 371.965576, 190.790771, "usebox");
			PlayerTextDrawLetterSize(playerid, InvTextDraws[playerid][46], 0.000000, 0.045320);
			PlayerTextDrawTextSize(playerid, InvTextDraws[playerid][46], 350.661926, 0.000000);
			PlayerTextDrawAlignment(playerid, InvTextDraws[playerid][46], 1);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][46], 0xE1E1E1FF);
			PlayerTextDrawUseBox(playerid, InvTextDraws[playerid][46], 1);
			PlayerTextDrawBoxColor(playerid, InvTextDraws[playerid][46], 0x56BF4CFF);
			PlayerTextDrawSetShadow(playerid, InvTextDraws[playerid][46], 2);
			PlayerTextDrawSetOutline(playerid, InvTextDraws[playerid][46], 0);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][46], 0x000000FF);
			PlayerTextDrawFont(playerid, InvTextDraws[playerid][46], 0);
			PlayerTextDrawSetProportional(playerid, InvTextDraws[playerid][46], 1);
			PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 0);

			InvTextDraws[playerid][43] = CreatePlayerTextDraw(playerid, 341.000000, 198.137054, "HUD:radar_SWEET");
			PlayerTextDrawLetterSize(playerid, InvTextDraws[playerid][43], 0.480000, 1.120000);
			PlayerTextDrawTextSize(playerid, InvTextDraws[playerid][43], 9.661929, 8.351837);
			PlayerTextDrawAlignment(playerid, InvTextDraws[playerid][43], 1);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][43], 0xFFFFFFFF);
			PlayerTextDrawUseBox(playerid, InvTextDraws[playerid][43], 0);
			PlayerTextDrawBoxColor(playerid, InvTextDraws[playerid][43], 0x80808080);
			PlayerTextDrawSetShadow(playerid, InvTextDraws[playerid][43], 2);
			PlayerTextDrawSetOutline(playerid, InvTextDraws[playerid][43], 0);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][43], 0x000000FF);
			PlayerTextDrawFont(playerid, InvTextDraws[playerid][43], 4);
			PlayerTextDrawSetProportional(playerid, InvTextDraws[playerid][43], 1);
			PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][43], 1);

			InvTextDraws[playerid][41] = CreatePlayerTextDraw(playerid, 390.469238, 202.142609, "usebox");
			PlayerTextDrawLetterSize(playerid, InvTextDraws[playerid][41], 0.000000, 0.045320);
			PlayerTextDrawTextSize(playerid, InvTextDraws[playerid][41], 350.661926, 0.000000);
			PlayerTextDrawAlignment(playerid, InvTextDraws[playerid][41], 1);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][41], 0xE1E1E1FF);
			PlayerTextDrawUseBox(playerid, InvTextDraws[playerid][41], 1);
			PlayerTextDrawBoxColor(playerid, InvTextDraws[playerid][41], 0x6C7B9570);
			PlayerTextDrawSetShadow(playerid, InvTextDraws[playerid][41], 2);
			PlayerTextDrawSetOutline(playerid, InvTextDraws[playerid][41], 0);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][41], 0x000000FF);
			PlayerTextDrawFont(playerid, InvTextDraws[playerid][41], 0);
			PlayerTextDrawSetProportional(playerid, InvTextDraws[playerid][41], 1);
			PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][41], 0);

			InvTextDraws[playerid][39] = CreatePlayerTextDraw(playerid, 367.524689, 202.142609, "usebox");
			PlayerTextDrawLetterSize(playerid, InvTextDraws[playerid][39], 0.000000, 0.045320);
			PlayerTextDrawTextSize(playerid, InvTextDraws[playerid][39], 350.661926, 0.000000);
			PlayerTextDrawAlignment(playerid, InvTextDraws[playerid][39], 1);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][39], 0xE1E1E1FF);
			PlayerTextDrawUseBox(playerid, InvTextDraws[playerid][39], 1);
			PlayerTextDrawBoxColor(playerid, InvTextDraws[playerid][39], 0x407088FF);
			PlayerTextDrawSetShadow(playerid, InvTextDraws[playerid][39], 2);
			PlayerTextDrawSetOutline(playerid, InvTextDraws[playerid][39], 0);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][39], 0x000000FF);
			PlayerTextDrawFont(playerid, InvTextDraws[playerid][39], 0);
			PlayerTextDrawSetProportional(playerid, InvTextDraws[playerid][39], 1);
			PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][39], 0);

			InvTextDraws[playerid][37] = CreatePlayerTextDraw(playerid, 363.024231, 130.600006, "LD_CHAT:badchat");
			PlayerTextDrawLetterSize(playerid, InvTextDraws[playerid][37], 0.480000, 1.120000);
			PlayerTextDrawTextSize(playerid, InvTextDraws[playerid][37], 5.666667, 9.833333);
			PlayerTextDrawAlignment(playerid, InvTextDraws[playerid][37], 1);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][37], 0xFFFFFFFF);
			PlayerTextDrawUseBox(playerid, InvTextDraws[playerid][37], 0);
			PlayerTextDrawBoxColor(playerid, InvTextDraws[playerid][37], 0x80808080);
			PlayerTextDrawSetShadow(playerid, InvTextDraws[playerid][37], 2);
			PlayerTextDrawSetOutline(playerid, InvTextDraws[playerid][37], 0);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][37], 0x000000FF);
			PlayerTextDrawFont(playerid, InvTextDraws[playerid][37], 4);
			PlayerTextDrawSetProportional(playerid, InvTextDraws[playerid][37], 1);
			PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][37], 0);

			InvTextDraws[playerid][35] = CreatePlayerTextDraw(playerid, 365.857574, 130.600006, "LD_SPAC:WHITE");
			PlayerTextDrawLetterSize(playerid, InvTextDraws[playerid][35], 0.480000, 1.120000);
			PlayerTextDrawTextSize(playerid, InvTextDraws[playerid][35], 17.000000, 9.833333);
			PlayerTextDrawAlignment(playerid, InvTextDraws[playerid][35], 1);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][35], 0x1A1A1AFF);
			PlayerTextDrawUseBox(playerid, InvTextDraws[playerid][35], 0);
			PlayerTextDrawBoxColor(playerid, InvTextDraws[playerid][35], 0x80808080);
			PlayerTextDrawSetShadow(playerid, InvTextDraws[playerid][35], 2);
			PlayerTextDrawSetOutline(playerid, InvTextDraws[playerid][35], 0);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][35], 0x000000FF);
			PlayerTextDrawFont(playerid, InvTextDraws[playerid][35], 4);
			PlayerTextDrawSetProportional(playerid, InvTextDraws[playerid][35], 1);
			PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][35], 1);

			InvTextDraws[playerid][33] = CreatePlayerTextDraw(playerid, 375.774231, 131.994705, "…HЃO");
			PlayerTextDrawLetterSize(playerid, InvTextDraws[playerid][33], 0.125555, 0.704395);
			PlayerTextDrawTextSize(playerid, InvTextDraws[playerid][33], 1280.000000, 1280.000000);
			PlayerTextDrawAlignment(playerid, InvTextDraws[playerid][33], 2);
			PlayerTextDrawColor(playerid, InvTextDraws[playerid][33], 0xBBBBBBFF);
			PlayerTextDrawUseBox(playerid, InvTextDraws[playerid][33], 0);
			PlayerTextDrawBoxColor(playerid, InvTextDraws[playerid][33], 0x80808080);
			PlayerTextDrawSetShadow(playerid, InvTextDraws[playerid][33], 0);
			PlayerTextDrawSetOutline(playerid, InvTextDraws[playerid][33], 0);
			PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][33], 0x00000000);
			PlayerTextDrawFont(playerid, InvTextDraws[playerid][33], 2);
			PlayerTextDrawSetProportional(playerid, InvTextDraws[playerid][33], 1);
			PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][33], 0);

		}
		else
		{
		    new skin = GetPlayerSkin(playerid);
			PlayerTextDrawSetString(playerid, kletka[playerid][0], "~<~");
		    format(string,sizeof(string),"ID:%d",skin),
		    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][45], string);
		    GetPlayerHealth(playerid,health);
		    format(string,sizeof(string),"HP: %.0f",health),
		    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][13], string);
		    new Float:armour;
		    GetPlayerArmour(playerid,armour);
		    format(string,sizeof(string),"ARM: %.0f",armour),
		    PlayerTextDrawSetString(playerid, InvTextDraws[playerid][14], string);
		    PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][47], GetPlayerSkin(playerid));
		    if(PlayerInfo[playerid][pSlotItem][6] != 0) CheckInvs(playerid, 6);
			if(PlayerInfo[playerid][pSlotItem][5] != 0) CheckInvs(playerid, 5);
			if(PlayerInfo[playerid][pSlotItem][1] != 0) CheckInvs(playerid, 1);
			if(PlayerInfo[playerid][pSlotItem][2] != 0) CheckInvs(playerid, 2);
			if(PlayerInfo[playerid][pSlotItem][3] != 0) CheckInvs(playerid, 3);
			if(PlayerInfo[playerid][pSlotItem][4] != 0) CheckInvs(playerid, 4);
			if(PlayerInfo[playerid][pSlotItem][0] != 0) CheckInvs(playerid, 0);
			if(PlayerInfo[playerid][pSlotItem][7] != 0) CheckInvs(playerid, 7);


		}
	    PlayerTextDrawColor(playerid, InvTextDraws[playerid][8], 0x333333FF);
		PlayerTextDrawColor(playerid, InvTextDraws[playerid][9], PlayerInfo[playerid][pColorInv]);
		new carid = GetPlayerVehicleID(playerid);
		if(IsPlayerInVehicle(playerid, carid)) {
		    AksDel[playerid][5] = 1;
			RemovePlayerAttachedObject(playerid, 5);
		}
		for(new i = 0; i < 72; i++){
		   if(PlayerInfo[playerid][pInventoryKolvo][i] < 1){
			   PlayerInfo[playerid][pInventoryKolvo][i] = 0;
			   PlayerInfo[playerid][pInventory][i] = 0;
		   }
		}
        if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, InvTextDraws[playerid][27], "MENU");
        else PlayerTextDrawSetString(playerid, InvTextDraws[playerid][27], FixText("МЕНЮ"));
        if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, InvTextDraws[playerid][25], "SETTINGS");
        else PlayerTextDrawSetString(playerid, InvTextDraws[playerid][25], FixText("НАСТРОЙКИ"));
        if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, InvTextDraws[playerid][23], "CARS");
        else PlayerTextDrawSetString(playerid, InvTextDraws[playerid][23], FixText("ТРАНСПОРТ"));
        if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, InvTextDraws[playerid][21], "BUSINESS");
        else PlayerTextDrawSetString(playerid, InvTextDraws[playerid][21], FixText("БИЗНЕС"));
        if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, InvTextDraws[playerid][19], "DONATE");
        else PlayerTextDrawSetString(playerid, InvTextDraws[playerid][19], FixText("ДОНАТ"));
   	    if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, InvTextDraws[playerid][16], "FAMILY");
   	    else PlayerTextDrawSetString(playerid, InvTextDraws[playerid][16], FixText("СЕМЬЯ"));
        if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, InvTextDraws[playerid][11], "INVENTORY");
        else PlayerTextDrawSetString(playerid, InvTextDraws[playerid][11], FixText("ИНВЕНТАРЬ"));
        if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, InvTextDraws[playerid][55], "HELP");
        else PlayerTextDrawSetString(playerid, InvTextDraws[playerid][55], FixText("ПОМОЩЬ"));
        if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, InvTextDraws[playerid][53], "REPORT");
        else PlayerTextDrawSetString(playerid, InvTextDraws[playerid][53], FixText("РЕПОРТ"));
        if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, InvTextDraws[playerid][6], "CLOSE");
        else PlayerTextDrawSetString(playerid, InvTextDraws[playerid][6], FixText("ЗАКРЫТЬ"));
        if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, InvTextDraws[playerid][62], "QUEST");
        else PlayerTextDrawSetString(playerid, InvTextDraws[playerid][62], FixText("КВЕСТЫ"));
        if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, InvTextDraws[playerid][60], "REWARDS");
        else PlayerTextDrawSetString(playerid, InvTextDraws[playerid][60], FixText("ДОСТИЖЕНИЯ"));
		InvUpdateToColor(playerid);
		if(GetPlayerSkin(playerid) == 18) {
			PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 0);
			PlayerTextDrawSetPreviewModel(playerid, InvTextDraws[playerid][46], 1649);
			PlayerTextDrawSetPreviewRot(playerid, InvTextDraws[playerid][46], 0.000000, 0.000000, 90.000000, 2.000000);
			PlayerTextDrawSetString(playerid, InvTextDraws[playerid][45], "");
		}
		if(GetPlayerSkin(playerid) != 18) {
			PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 1);
		}
		new str[28];
	    for(new j = 0; j < 36; j++)
	    {
	        new ID = PlayerInfo[playerid][pInventory][j];
	        PlayerTextDrawSetPreviewModel(playerid, Govnishe[playerid][j], ItemsInfo[ID][ItemModel]);
	        PlayerTextDrawSetPreviewRot(playerid, Govnishe[playerid][j], ItemsInfo[ID][POSTDx], ItemsInfo[ID][POSTDy], ItemsInfo[ID][POSTDz], ItemsInfo[ID][POSTDc]);
            PlayerTextDrawBackgroundColor(playerid, Govnishe[playerid][j], ItemsInfo[ID][ItemColor]);
			format(string,sizeof(string), "%d",PlayerInfo[playerid][pInventoryKolvo][j]),
	        PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
	    }
	    for(new j = 0; j < 36; j++)
	    {
   			if(PlayerInfo[playerid][pInventoryKolvo][j] == 0 || PlayerInfo[playerid][pInventoryKolvo][j] == 1)
			{
				format(string,sizeof(string), "",PlayerInfo[playerid][pInventoryKolvo][j]),
		        PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
			}
			if(PlayerInfo[playerid][pInventory][j] == 313)
			{
				if(PlayerInfo[playerid][pChestTime] < 60)
				{
					format(string,sizeof(string),"%d SEC", PlayerInfo[playerid][pChestTime]);
		            PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
				if(PlayerInfo[playerid][pChestTime] == 0)
				{
		            PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], "");
				}
				if(PlayerInfo[playerid][pChestTime] > 60)
				{
		            format(string,sizeof(string),"%d MIN", PlayerInfo[playerid][pChestTime]/60);
		            PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
				}
			}
			if(PlayerInfo[playerid][pInventory][j] == 590)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pCarLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
			}
			if(PlayerInfo[playerid][pInventory][j] == 591)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pBikeLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
			}
			if(PlayerInfo[playerid][pInventory][j] == 592)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pBoatLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
			}
			if(PlayerInfo[playerid][pInventory][j] == 593)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pFlyLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
			}
			if(PlayerInfo[playerid][pInventory][j] == 594)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pGunLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], string);
			}
			for(new i = 1; i < 312; i++)
			{
				if(PlayerInfo[playerid][pInventory][j] == i)
		  		{
						format(str, sizeof(str), "ID:%d", i),
						PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][j], str);
						PlayerTextDrawColor(playerid, GovnisheKletki[playerid][j], 0xFFFFFFFF);
	            }
            }
		}
		if(HouseEntered[playerid] != -1)
		{
		    if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, TDinvTrash[playerid][1], "WAREHOUSE");
      		else PlayerTextDrawSetString(playerid, TDinvTrash[playerid][1], FixText("ШКАФ"));
		    PlayerTextDrawShow(playerid, TDinvTrash[playerid][1]);
  			PlayerTextDrawShow(playerid, TDinvTrash[playerid][0]);
			OpenDaun[playerid] = 3;
		}
		for(new i; i < MAX_MUSORS; i++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 3.0, MusorPos[i][0],  MusorPos[i][1],  MusorPos[i][2]))
			{
			          if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, TDinvTrash[playerid][1], "TRASH");
			          else PlayerTextDrawSetString(playerid, TDinvTrash[playerid][1], FixText("МУСОРКА"));
					  PlayerTextDrawShow(playerid, TDinvTrash[playerid][1]);
					  PlayerTextDrawShow(playerid, TDinvTrash[playerid][0]);
					  OpenDaun[playerid] = 2;
			}
		}
		for(new c = 1; c < ADD_VEHICLES; c ++)
		{
			if(!IsACar(c)) continue;
			new Float:X,Float:Y,Float:Z;
			GetVehicleShiftPos(c,1,X,Y,Z,2.0);
			if(IsPlayerInRangeOfPoint(playerid,2,X,Y,Z))
			{
				new Float:angle = GetPlayerAngleToPoint(playerid, X, Y);
				if(angle >= -55 && angle <= 55)
				{
        			idaofcar[playerid]=c;
					if(PlayerInfo[playerid][pLanguage] == 0) PlayerTextDrawSetString(playerid, TDinvTrash[playerid][1], "TRUNK");
     				else PlayerTextDrawSetString(playerid, TDinvTrash[playerid][1], FixText("БАГАЖНИК"));
			  		PlayerTextDrawShow(playerid, TDinvTrash[playerid][1]);
		  			PlayerTextDrawShow(playerid, TDinvTrash[playerid][0]);
					OpenDaun[playerid] = 1;
				}
			}
		}
		PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][46], 0x333333FF);
		PlayerTextDrawLetterSize(playerid, kletka[playerid][0], 0.134524, 0.754709);
		PlayerTextDrawShow(playerid, kletka[playerid][0]);
		PlayerTextDrawShow(playerid, kletka[playerid][1]);
	    for(new i = 0; i < 63; i++)
	    {
	        PlayerTextDrawShow(playerid,InvTextDraws[playerid][i]);
	    }
	    for(new i = 0; i < 36; i++)
	    {
	        PlayerTextDrawShow(playerid,Govnishe[playerid][i]);
	    }
	    for(new i = 0; i < 36; i++)
	    {
	        PlayerTextDrawShow(playerid,GovnisheKletki[playerid][i]);
	    }
	    for(new i = 2; i < 4; i++)
		{
		    PlayerTextDrawShow(playerid, TDinvTrash[playerid][i]);
		}
  		SelectTextDraw(playerid, PlayerInfo[playerid][pColorInv]-50);
  		PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][40], 0x333333FF);
	    return true;
}
stock HideInventory(playerid) // Скрываем инвентарь.
{
		for(new i = 0; i < 7; i++)
		{
		    TextDrawHideForPlayer(playerid, others[i]);
		}
		for(new i = 0; i < 2; i++)
		{
		    DestroyPlayerTD(playerid, kletka[playerid][i]);
		}
	    for(new i = 0; i < 63; i++)
	    {
	        DestroyPlayerTD(playerid,InvTextDraws[playerid][i]);
	    }
	    for(new i = 0; i < 72; i++)
	    {
	        DestroyPlayerTD(playerid,Govnishe[playerid][i]);
	    }
	    for(new i = 0; i < 72; i++)
	    {
	        DestroyPlayerTD(playerid,GovnisheKletki[playerid][i]);
	    }
	    for(new i = 0; i < 6; i++)
		{
		    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
		}
		for(new i = 0; i < 7; i++)
		{
			DestroyPlayerTD(playerid, fstd_p[playerid][i]);
		}
		for(new i = 0; i < 8; i++)
		{
		    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
		}
		for(new i = 0; i < 7; i++)
		{
		    DestroyPlayerTD(playerid, TDinv[playerid][i]);
		}
		for(new i = 0; i < 4; i++)
		{
  			DestroyPlayerTD(playerid, TDinvTrash[playerid][i]);
		}
		if(PlayerInfo[playerid][pTypeSpeed] == 1) //СПИДАК3
		{
			for(new i = 0; i < 7; i++) DestroyPlayerTD(playerid, speeddraw[playerid][i]);
		}
		PlayerInfo[playerid][pSecondpage] = 0;
		AndruxaTop[playerid] = 0;
		PlayerTextDrawSetString(playerid, InvTextDraws[playerid][48], "~<~");
    	CancelSelectTextDraw(playerid);
    	return true;
}


stock InvSlotUpdate(playerid, td, jdk)
{
			new string[28];
			new str[7];
		    PlayerTextDrawSetPreviewModel(playerid, Govnishe[playerid][td], ItemsInfo[jdk][ItemModel]);
		    PlayerTextDrawSetPreviewRot(playerid, Govnishe[playerid][td], ItemsInfo[jdk][POSTDx], ItemsInfo[jdk][POSTDy], ItemsInfo[jdk][POSTDz], ItemsInfo[jdk][POSTDc]);
            PlayerTextDrawBackgroundColor(playerid, Govnishe[playerid][td], ItemsInfo[jdk][ItemColor]);
			PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][td], 1);
		    format(string,sizeof(string), "%d",PlayerInfo[playerid][pInventoryKolvo][td]),
	        PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
	        PlayerTextDrawColor(playerid, GovnisheKletki[playerid][td], 0xAAAAAAFF);
			if(PlayerInfo[playerid][pInventoryKolvo][td] == 0 || PlayerInfo[playerid][pInventoryKolvo][td] == 1)
			{
				format(string,sizeof(string), "",PlayerInfo[playerid][pInventoryKolvo][td]),
		        PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
			if(PlayerInfo[playerid][pInventory][td] == 313)
			{
				if(PlayerInfo[playerid][pChestTime] < 60)
				{
					format(string,sizeof(string),"%d SEC", PlayerInfo[playerid][pChestTime]);
					PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
				}
				if(PlayerInfo[playerid][pChestTime] == 0)
				{
				       format(string,sizeof(string),""),
					   PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
					   PlayerInfo[playerid][pChestTime] = 0;
				}
				if(PlayerInfo[playerid][pChestTime] > 60)
				{
				   format(string,sizeof(string),"%d MIN", PlayerInfo[playerid][pChestTime]/60);
				   PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
				}
			}
			if(PlayerInfo[playerid][pInventory][td] == 590)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pCarLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
			if(PlayerInfo[playerid][pInventory][td] == 591)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pBikeLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
			if(PlayerInfo[playerid][pInventory][td] == 592)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pBoatLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
			if(PlayerInfo[playerid][pInventory][td] == 593)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pFlyLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
			if(PlayerInfo[playerid][pInventory][td] == 594)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pGunLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
			for(new j = 1; j < 312; j++)
			{
				if(PlayerInfo[playerid][pInventory][td] == j)
				{
							format(str, sizeof(str), "ID:%d", j),
							PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], str);
							PlayerTextDrawColor(playerid, GovnisheKletki[playerid][td], 0xFFFFFFFF);
							PlayerTextDrawShow(playerid, GovnisheKletki[playerid][td]);
   				}
 			}
		    PlayerTextDrawHide(playerid,Govnishe[playerid][td]);
		    PlayerTextDrawShow(playerid,Govnishe[playerid][td]);
		    PlayerTextDrawShow(playerid,GovnisheKletki[playerid][td]);
		    if(PlayerInfo[playerid][pSecondpage] == 1)
		    {
				for(new i = 0; i < 36; i++)
				{
					PlayerTextDrawHide(playerid, GovnisheKletki[playerid][i]);
				}
				for(new i = 0; i < 36; i++)
				{
					PlayerTextDrawHide(playerid, Govnishe[playerid][i]);
				}
			}
			if(PlayerInfo[playerid][pSecondpage] == 0)
		    {
				for(new i = 36; i < 72; i++)
				{
					PlayerTextDrawHide(playerid, GovnisheKletki[playerid][i]);
				}
				for(new i = 36; i < 72; i++)
				{
					PlayerTextDrawHide(playerid, Govnishe[playerid][i]);
				}
			}
			if(PlayerInfo[playerid][pSecondpage] == 0)
   			{
      			for(new i = 36; i < 72; i++)
         		{
           			PlayerTextDrawHide(playerid, GovnisheKletki[playerid][i]);
				}
			}
			if(PlayerInfo[playerid][pSecondpage] == 1)
   			{
      			for(new i = 0; i < 36; i++)
         		{
           			PlayerTextDrawHide(playerid, GovnisheKletki[playerid][i]);
				}
			}
			for(new i = 1; i < 312; i++)
			{
							if(PlayerInfo[playerid][pInventory][td] == i)
							{
									PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][46], 0x333333FF);
									timeskin[playerid] = 0;
									if(PlayerInfo[playerid][pSkin] == 18)
									{
									    PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 0);
									}
									else PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 0);
									PlayerTextDrawHide(playerid, InvTextDraws[playerid][46]);
									PlayerTextDrawShow(playerid, InvTextDraws[playerid][46]);
							}
			}
	    	return true;
}
stock TrashSlotUpdate(playerid, td, jdk)
{
			new string[28];
			new str[7];
		    PlayerTextDrawSetPreviewModel(playerid, TrashSlot[playerid][td], ItemsInfo[jdk][ItemModel]);
		    PlayerTextDrawSetPreviewRot(playerid, TrashSlot[playerid][td], ItemsInfo[jdk][POSTDx], ItemsInfo[jdk][POSTDy], ItemsInfo[jdk][POSTDz], ItemsInfo[jdk][POSTDc]);
            PlayerTextDrawBackgroundColor(playerid, TrashSlot[playerid][td], ItemsInfo[jdk][ItemColor]);
			PlayerTextDrawSetSelectable(playerid, TrashSlot[playerid][td], 1);
		    format(string,sizeof(string), "%d",mInfo[musorka[playerid]][InventoryTrashKolvo][td]),
	        PlayerTextDrawSetString(playerid, TrashSlotKol[playerid][td], string);
			if(mInfo[musorka[playerid]][InventoryTrashKolvo][td] == 0)
			{
				format(string,sizeof(string), "",mInfo[musorka[playerid]][InventoryTrashKolvo][td]),
		        PlayerTextDrawSetString(playerid, TrashSlotKol[playerid][td], string);
			}
			if(mInfo[musorka[playerid]][InventoryTrashKolvo][td] == 1)
			{
				format(string,sizeof(string), "",mInfo[musorka[playerid]][InventoryTrashKolvo][td]),
		        PlayerTextDrawSetString(playerid, TrashSlotKol[playerid][td], string);
			}
			for(new j = 1; j < 312; j++)
			{
				if(mInfo[musorka[playerid]][InventoryTrash][td] == j)
				{
							format(str, sizeof(str), "ID:%d", j),
							PlayerTextDrawSetString(playerid, TrashSlotKol[playerid][td], str);
							PlayerTextDrawColor(playerid, TrashSlotKol[playerid][td], 0xFFFFFFFF);
							PlayerTextDrawHide(playerid, TrashSlotKol[playerid][td]);
							PlayerTextDrawShow(playerid, TrashSlotKol[playerid][td]);
   				}
 			}
 			PlayerTextDrawHide(playerid, TrashSlot[playerid][td]);
 			PlayerTextDrawShow(playerid, TrashSlot[playerid][td]);
 			PlayerTextDrawHide(playerid, TrashSlotKol[playerid][td]);
 			PlayerTextDrawShow(playerid, TrashSlotKol[playerid][td]);
 			return true;
}
stock BagazhnikSlotUpdate(playerid, td, jdk)
{
			new string[28];
			new house = idaofcar[playerid];
			new str[7];
		    PlayerTextDrawSetPreviewModel(playerid, BagazhnikSlot[playerid][td], ItemsInfo[jdk][ItemModel]);
		    PlayerTextDrawSetPreviewRot(playerid, BagazhnikSlot[playerid][td], ItemsInfo[jdk][POSTDx], ItemsInfo[jdk][POSTDy], ItemsInfo[jdk][POSTDz], ItemsInfo[jdk][POSTDc]);
            PlayerTextDrawBackgroundColor(playerid, BagazhnikSlot[playerid][td], ItemsInfo[jdk][ItemColor]);
			PlayerTextDrawSetSelectable(playerid, BagazhnikSlot[playerid][td], 1);
		    format(string,sizeof(string), "%d",TrunkInfo[house][tBagazhnikSlotKol][td]),
	        PlayerTextDrawSetString(playerid, BagazhnikSlotKol[playerid][td], string);
			if(TrunkInfo[house][tBagazhnikSlotKol][td] == 0)
			{
				format(string,sizeof(string), ""),
		        PlayerTextDrawSetString(playerid, BagazhnikSlotKol[playerid][td], string);
			}
			if(TrunkInfo[house][tBagazhnikSlotKol][td] == 1)
			{
				format(string,sizeof(string), ""),
		        PlayerTextDrawSetString(playerid, BagazhnikSlotKol[playerid][td], string);
			}
			for(new j = 1; j < 312; j++)
			{
				if(TrunkInfo[house][tBagazhnikSlot][td] == j)
				{
							format(str, sizeof(str), "ID:%d", j),
							PlayerTextDrawSetString(playerid, BagazhnikSlotKol[playerid][td], str);
							PlayerTextDrawColor(playerid, BagazhnikSlotKol[playerid][td], 0xFFFFFFFF);
							PlayerTextDrawHide(playerid, BagazhnikSlotKol[playerid][td]);
							PlayerTextDrawShow(playerid, BagazhnikSlotKol[playerid][td]);
   				}
 			}
 			if(TrunkInfo[house][tBagazhnikSlot][td] == 313)
			{
				if(PlayerInfo[playerid][pChestTime] < 60)
				{
					format(string,sizeof(string),"%d SEC", PlayerInfo[playerid][pChestTime]);
		            PlayerTextDrawSetString(playerid, BagazhnikSlotKol[playerid][td], string);
				}
				if(PlayerInfo[playerid][pChestTime] == 0)
				{
					format(string,sizeof(string),""),
		            PlayerTextDrawSetString(playerid, BagazhnikSlotKol[playerid][td], string);
		            PlayerInfo[playerid][pChestTime] = 0;
				}
				if(PlayerInfo[playerid][pChestTime] > 60)
				{
		            format(string,sizeof(string),"%d MIN", PlayerInfo[playerid][pChestTime]/60);
		            PlayerTextDrawSetString(playerid, BagazhnikSlotKol[playerid][td], string);
				}
			}
			if(PlayerInfo[playerid][pInventory][td] == 590)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pCarLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
			if(PlayerInfo[playerid][pInventory][td] == 591)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pBikeLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
			if(PlayerInfo[playerid][pInventory][td] == 592)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pBoatLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
			if(PlayerInfo[playerid][pInventory][td] == 593)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pFlyLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
			if(PlayerInfo[playerid][pInventory][td] == 594)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pGunLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
 			PlayerTextDrawHide(playerid, BagazhnikSlot[playerid][td]);
 			PlayerTextDrawShow(playerid, BagazhnikSlot[playerid][td]);
 			PlayerTextDrawHide(playerid, BagazhnikSlotKol[playerid][td]);
 			PlayerTextDrawShow(playerid, BagazhnikSlotKol[playerid][td]);
 			return true;
}
stock ShkafSlotUpdate(playerid, td, jdk)
{
			new string[28];
			new house = HouseEntered[playerid];
			new str[7];
		    PlayerTextDrawSetPreviewModel(playerid, ShkafSlot[playerid][td], ItemsInfo[jdk][ItemModel]);
		    PlayerTextDrawSetPreviewRot(playerid, ShkafSlot[playerid][td], ItemsInfo[jdk][POSTDx], ItemsInfo[jdk][POSTDy], ItemsInfo[jdk][POSTDz], ItemsInfo[jdk][POSTDc]);
            PlayerTextDrawBackgroundColor(playerid, ShkafSlot[playerid][td], ItemsInfo[jdk][ItemColor]);
			PlayerTextDrawSetSelectable(playerid, ShkafSlot[playerid][td], 1);
		    format(string,sizeof(string), "%d",HouseInfo[house][hShkafSlotKol][td]),
	        PlayerTextDrawSetString(playerid, ShkafSlotKol[playerid][td], string);
			if(HouseInfo[house][hShkafSlotKol][td] == 0)
			{
				format(string,sizeof(string), ""),
		        PlayerTextDrawSetString(playerid, ShkafSlotKol[playerid][td], string);
			}
			if(HouseInfo[house][hShkafSlotKol][td] == 1)
			{
				format(string,sizeof(string), ""),
		        PlayerTextDrawSetString(playerid, ShkafSlotKol[playerid][td], string);
			}
			for(new j = 1; j < 312; j++)
			{
				if(HouseInfo[house][hShkafSlot][td] == j)
				{
							format(str, sizeof(str), "ID:%d", j),
							PlayerTextDrawSetString(playerid, ShkafSlotKol[playerid][td], str);
							PlayerTextDrawColor(playerid, ShkafSlotKol[playerid][td], 0xFFFFFFFF);
							PlayerTextDrawHide(playerid, ShkafSlotKol[playerid][td]);
							PlayerTextDrawShow(playerid, ShkafSlotKol[playerid][td]);
   				}
 			}
 			if(HouseInfo[house][hShkafSlot][td] == 313)
			{
				if(PlayerInfo[playerid][pChestTime] < 60)
				{
					format(string,sizeof(string),"%d SEC", PlayerInfo[playerid][pChestTime]);
		            PlayerTextDrawSetString(playerid, ShkafSlotKol[playerid][td], string);
				}
				if(PlayerInfo[playerid][pChestTime] == 0)
				{
					format(string,sizeof(string),""),
		            PlayerTextDrawSetString(playerid, ShkafSlotKol[playerid][td], string);
		            PlayerInfo[playerid][pChestTime] = 0;
				}
				if(PlayerInfo[playerid][pChestTime] > 60)
				{
		            format(string,sizeof(string),"%d MIN", PlayerInfo[playerid][pChestTime]/60);
		            PlayerTextDrawSetString(playerid, ShkafSlotKol[playerid][td], string);
				}
			}
			if(PlayerInfo[playerid][pInventory][td] == 590)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pCarLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
			if(PlayerInfo[playerid][pInventory][td] == 591)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pBikeLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
			if(PlayerInfo[playerid][pInventory][td] == 592)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pBoatLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
			if(PlayerInfo[playerid][pInventory][td] == 593)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pFlyLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
			if(PlayerInfo[playerid][pInventory][td] == 594)
			{
				format(string,sizeof(string),"%d DAY", PlayerInfo[playerid][pGunLic]);
    			PlayerTextDrawSetString(playerid, GovnisheKletki[playerid][td], string);
			}
 			PlayerTextDrawHide(playerid, ShkafSlot[playerid][td]);
 			PlayerTextDrawShow(playerid, ShkafSlot[playerid][td]);
 			PlayerTextDrawHide(playerid, ShkafSlotKol[playerid][td]);
 			PlayerTextDrawShow(playerid, ShkafSlotKol[playerid][td]);
 			return true;
}
cmd:invent(playerid)
{
	if(AndruxaTop[playerid] == 1) return 1;
	ShowInventory(playerid); // Вызываем функцию показа инвентаря.
	return true;
}
stock RefreshInv(playerid, slot)
{
	    if(PlayerInfo[playerid][pInventoryKolvo][slot] != 1)
	    {
	        PlayerInfo[playerid][pInventoryKolvo][slot] -= 1;
	    }
	    else
	    {
	        PlayerInfo[playerid][pInventory][slot] = 0;
	        PlayerInfo[playerid][pInventoryKolvo][slot] = 0;
	    }
	    for(new i = 0; i < 6; i++)
		{
		    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
		}
		for(new i = 0; i < 7; i++)
		{
		    DestroyPlayerTD(playerid, fstd_p[playerid][i]);
		}
		for(new i = 0; i < 8; i++)
		{
		    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
		}
		if(PlayerInfo[playerid][pInventoryKolvo][slot] < 1)
	    {
            PlayerInfo[playerid][pInventoryKolvo][slot] = 0;
            PlayerInfo[playerid][pInventory][slot] = 0;
	    }
	    for(new i = 1; i < 312; i++)
		{
							if(PlayerInfo[playerid][pInventory][PickInvent[playerid]] == i)
							{
									PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][46], 0x333333FF);
									timeskin[playerid] = 0;
									if(PlayerInfo[playerid][pSkin] == 18)
									{
									    PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 0);
									}
									PlayerTextDrawHide(playerid, InvTextDraws[playerid][46]);
									PlayerTextDrawShow(playerid, InvTextDraws[playerid][46]);
							}
		}
    	InvSlotUpdate(playerid, slot, PlayerInfo[playerid][pInventory][slot]);
    	PickInvent[playerid] = 73;
    	return true;
}
stock TrashSlotUpdate2(playerid, slot)
{
		mInfo[musorka[playerid]][InventoryTrash][slot] = 0;
		mInfo[musorka[playerid]][InventoryTrashKolvo][slot] = 0;
		if(mInfo[musorka[playerid]][InventoryTrashKolvo][slot] < 1)
	    {
            mInfo[musorka[playerid]][InventoryTrashKolvo][slot] = 0;
            mInfo[musorka[playerid]][InventoryTrash][slot] = 0;
	    }
	    foreach(Player, g)
	    {
    		TrashSlotUpdate(g, slot, mInfo[musorka[playerid]][InventoryTrash][slot]);
    	}
    	PickInventTrash[playerid] = 31;
    	return true;
}
new Adrenaline[MAX_PLAYERS];
stock BagazhnikSlotUpdate2(playerid, slot)
{
		new house = idaofcar[playerid];
		TrunkInfo[house][tBagazhnikSlotKol][slot] = 0;
		TrunkInfo[house][tBagazhnikSlotKol][slot] = 0;
		if(TrunkInfo[house][tBagazhnikSlotKol][slot] < 1)
	    {
            TrunkInfo[house][tBagazhnikSlotKol][slot] = 0;
            TrunkInfo[house][tBagazhnikSlot][slot] = 0;
	    }
	    foreach(Player, g)
	    {
    		BagazhnikSlotUpdate(g, slot, TrunkInfo[house][tBagazhnikSlot][slot]);
		}
    	PickInventBagazhnik[playerid] = 31;
    	return true;
}
stock ShkafSlotUpdate2(playerid, slot)
{
		new house = HouseEntered[playerid];
		HouseInfo[house][hShkafSlotKol][slot] = 0;
		HouseInfo[house][hShkafSlotKol][slot] = 0;
		if(HouseInfo[house][hShkafSlotKol][slot] < 1)
	    {
            HouseInfo[house][hShkafSlotKol][slot] = 0;
            HouseInfo[house][hShkafSlot][slot] = 0;
	    }
    	ShkafSlotUpdate(playerid, slot, HouseInfo[house][hShkafSlot][slot]);
    	PickInventShkaf[playerid] = 31;
    	return true;
}
stock RefreshInv2(playerid, slot)
{
    for(new i = 0; i < 6; i++)
	{
	    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
	}
	for(new i = 0; i < 7; i++)
	{
		    DestroyPlayerTD(playerid, fstd_p[playerid][i]);
	}
	for(new i = 0; i < 8; i++)
	{
	    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
	}
    InvSlotUpdate(playerid, slot, PlayerInfo[playerid][pInventory][slot]);
    PickInvent[playerid] = 73;
    return true;
}
stock UseItem(playerid, td, itemid)
{
                updateslot6(playerid);
		        new string[1500];
		        for(new i = 1; i < 312; i++)
				{
									if(PlayerInfo[playerid][pInventory][PickInvent[playerid]] == i)
									{
											PlayerTextDrawBackgroundColor(playerid, InvTextDraws[playerid][46], 0x333333FF);
											timeskin[playerid] = 0;
											if(PlayerInfo[playerid][pSkin] == 18)
											{
											    PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 0);
											}
											PlayerTextDrawHide(playerid, InvTextDraws[playerid][46]);
											PlayerTextDrawShow(playerid, InvTextDraws[playerid][46]);
									}
				}
				PlayerInfo[playerid][pDopKletki] = 0;
				for(new i = 0; i < 7; i++)
				{
										DestroyPlayerTD(playerid, fstd_p[playerid][i]);
				}
				for(new i = 0; i < 8; i++)
				{
				    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
				}
				for(new i = 0; i < 6; i++)
				{
										DestroyPlayerTD(playerid, InfoItems[playerid][i]);
				}
				for(new i = 0; i < 2; i++)
				{
				    PlayerTextDrawHide(playerid, TDinvTrash[playerid][i]);
				}
                if(ItemsInfo[PlayerInfo[playerid][pInventory][PickInvent[playerid]]][itemused] == false)
    			{
					if(musorka[playerid] == 0)
					{
					    RefreshInv2(playerid, td);
						SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Выкинуть предмет можно только рядом с мусоркой!");
					}
					if(musorka[playerid] >= 1)
					{
					    if(PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 313) return RefreshInv2(playerid, PickInvent[playerid]), SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}Этот предмет нельзя передавать!");
                		if(PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 316) return RefreshInv2(playerid, PickInvent[playerid]), SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}Этот предмет нельзя передавать!");
                        if(PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 538) return RefreshInv2(playerid, PickInvent[playerid]), SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}Этот предмет нельзя передавать!");
                        if(PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 590 || PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 591 || PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 592 ||
						PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 593 || PlayerInfo[playerid][pInventory][PickInvent[playerid]] == 594) return RefreshInv2(playerid, PickInvent[playerid]), SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}Этот предмет нельзя передавать!");
						for(new i = 0; i < 30; i++)
					    {
					        if(mInfo[musorka[playerid]][InventoryTrash][i] != PlayerInfo[playerid][pInventory][PickInvent[playerid]]) continue;
					        mInfo[musorka[playerid]][InventoryTrash][i] = PlayerInfo[playerid][pInventory][PickInvent[playerid]];
					        mInfo[musorka[playerid]][InventoryTrashKolvo][i] += PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
					        new ID = mInfo[musorka[playerid]][InventoryTrash][i], IDS = PlayerInfo[playerid][pInventory][PickInvent[playerid]];
					        format(string, 330, "Игрок <a href=/logsaccount?name=%s>%s</a> положил в мусорку предмет %s в кол-ве %d.",PN(playerid),Name(playerid), ItemsInfo[IDS][ItemName2], PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]]);
							AllLogs(playerid, string);
							foreach(Player, g)
							{
								TrashSlotUpdate(g, i, ID);
							}
							PlayerInfo[playerid][pInventory][PickInvent[playerid]] = 0;
							PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]] = 0;
							RefreshInv2(playerid, PickInvent[playerid]);
							SaveTrash(musorka[playerid]);
							return true;
					    }
					    for(new i = 0; i < 30; i++)
					    {
					        if(mInfo[musorka[playerid]][InventoryTrash][i] != 0) continue;
					        mInfo[musorka[playerid]][InventoryTrash][i] = PlayerInfo[playerid][pInventory][PickInvent[playerid]];
					        mInfo[musorka[playerid]][InventoryTrashKolvo][i] = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
					        new ID = mInfo[musorka[playerid]][InventoryTrash][i], IDS = PlayerInfo[playerid][pInventory][PickInvent[playerid]];
					        format(string, 330, "Игрок <a href=/logsaccount?name=%s>%s</a> положил в мусорку предмет %s в кол-ве %d.",PN(playerid),Name(playerid), ItemsInfo[IDS][ItemName2], PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]]);
							AllLogs(playerid, string);
		        			foreach(Player, g)
							{
								TrashSlotUpdate(g, i, ID);
							}
							PlayerInfo[playerid][pInventory][PickInvent[playerid]] = 0;
							PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]] = 0;
					        RefreshInv2(playerid, PickInvent[playerid]);
							SaveTrash(musorka[playerid]);
							return true;
					    }
					}
					return true;
				}
				new Float:X, Float:Y, Float:Z, Float:A;
				GetPlayerPos(playerid,X,Y,Z);
				GetPlayerFacingAngle(playerid,A);
			    switch(itemid)
			    {
					case 573:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 550, 1);
							CreateOwnableCar(573,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Dune'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 451:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 551, 1);
							CreateOwnableCar(451,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Turismo'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 541:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 552, 1);
							CreateOwnableCar(541,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Bullet'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 411:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 553, 1);
							CreateOwnableCar(411,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Infernus'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 560:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 554, 1);
							CreateOwnableCar(560,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Sultan'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 495:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 555, 1);
							CreateOwnableCar(495,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Sandking'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 415:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 556, 1);
							CreateOwnableCar(415,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Cheetah'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 442:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 557, 1);
							CreateOwnableCar(442,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Romero'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 428:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 558, 1);
							CreateOwnableCar(428,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Securicar'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 494:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 559, 1);
							CreateOwnableCar(494,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Hotring Racer'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 506:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 560, 1);
							CreateOwnableCar(506,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Rancher'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 562:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 561, 1);
							CreateOwnableCar(562,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Elegy'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 568:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 562, 1);
							CreateOwnableCar(568,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Bandito'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 579:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 563, 1);
							CreateOwnableCar(579,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Huntley'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 444:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 564, 1);
							CreateOwnableCar(444,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Monster'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 522:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 565, 1);
							CreateOwnableCar(522,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'NRG-500'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 528:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 566, 1);
							CreateOwnableCar(528,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'FBI Truck'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 559:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 567, 1);
							CreateOwnableCar(559,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Jester'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 571:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 568, 1);
							CreateOwnableCar(571,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Kart'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 539:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 569, 1);
							CreateOwnableCar(539,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Vortex'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 530:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 570, 1);
							CreateOwnableCar(530,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Forklift'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 531:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 571, 1);
							CreateOwnableCar(531,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Tractor'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 535:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 572, 1);
							CreateOwnableCar(535,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Slamvan'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 561:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 573, 1);
							CreateOwnableCar(561,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Stratum'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 599:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 574, 1);
							CreateOwnableCar(599,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Police Ranger'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 487:
			        {
						if(IsValidNumberCars(playerid))
						{
							if(!IsPlayerInRangeOfPoint(playerid, 150, -2123.6548,-854.3079,32.0939)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Активировать сертификат можно только на Автобазаре!");
							DeleteItem(playerid, 580, 1);
							CreateOwnableCar(487,X,Y,Z,A,PN(playerid));
							closeuse(playerid);
							RefreshInv2(playerid, PickInvent[playerid]);
							format(string, 200, "\n\n{FFFFFF}Поздравляем вы активировали {FE642E}'Maverick'\n{FFFFFF}Приятный игры на Arizona RP Huntwill");
							ShowPlayerDialogEx(playerid, 0,0, "", string, "Спасибо", "");
						}
						else
						{
							PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
							SendClientMessage(playerid,COLOR_GREY,"[Ошибка] {FFFFFF}Ваш уровень VIP недостаточно высок чтобы иметь столько авто!");
						}
					}
					case 1650:
					{
						callcmd::fillcar(playerid,"");
					}

					case 19917:
					{
						//new tunningupdate;
					    if(PlayerInfo[playerid][pCheepsTimer] == 1) return RefreshInv2(playerid, td), SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}Между использованием предметов должно пройти 3 секунды!");
						if(!IsPlayerInHisVehicle(playerid)) return SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}Вы не находитесь в личном транспорте!"), RefreshInv2(playerid, td);
						if(IsPlayerInHisVehicle(playerid))
						{
						    {
								new vehid = GetPlayerVehicleID(playerid);
								new number = GetVehicleID(vehid);
								if(!IsPlayerInHisVehicle(playerid)) return SendClientMessage(playerid,COLOR_RED,"[Ошибка] {FFFFFF}Вы должны находится в личном транспорте!");
			    				if(CarInfo[number][cTwinTurbo] == 1) return SendClientMessage(playerid,COLOR_RED,"[Ошибка] {FFFFFF}У вас уже установлен TwinTurbo тюнинг!");
							    ShowPlayerDialogEx(playerid,0,0,"","{FFFFFF}- Поздравляем!\n\n{FFFFFF}Теперь вы владелец {ad6757}очень {ffffff}быстрого авто!\nС мощностью автомобиля в комплектации {d4b584}TWINTURBO{ffffff}, сравняться лишь единицы!\n\n\tПриятной игры","Окей","");
								PerfomenceInfo[GetPlayerVehicleID(playerid)][Discs] = 5;
						     	SaveTuning(GetPlayerVehicleID(playerid), "Discs", PerfomenceInfo[GetPlayerVehicleID(playerid)][Discs]);
						     	PerfomenceInfo[GetPlayerVehicleID(playerid)][Bridge] = 4;
						     	SaveTuning(GetPlayerVehicleID(playerid), "Bridge", PerfomenceInfo[GetPlayerVehicleID(playerid)][Bridge]);
				 		     	PerfomenceInfo[GetPlayerVehicleID(playerid)][Shock_absorbers] = 5;
						     	SaveTuning(GetPlayerVehicleID(playerid), "Shock_absorbers", PerfomenceInfo[GetPlayerVehicleID(playerid)][Shock_absorbers]);
								TuningMod(GetPlayerVehicleID(playerid));
								CarInfo[number][cTwinTurbo] = 1;
						     	PerfomenceInfo[GetPlayerVehicleID(playerid)][Engine] = 3;
						     	SaveTuning(GetPlayerVehicleID(playerid), "Engine", PerfomenceInfo[GetPlayerVehicleID(playerid)][Engine]);
				 		     	PerfomenceInfo[GetPlayerVehicleID(playerid)][Wheel] = 5;
						     	SaveTuning(GetPlayerVehicleID(playerid), "Wheel", PerfomenceInfo[GetPlayerVehicleID(playerid)][Wheel]);
								SaveOwnableCar(number);
								SaveOwnableCar(vehid);
							}
						}
						DeleteItem(playerid, 579, 1);
						closeuse(playerid);
					}
					case 1288:
					{
					    if(PlayerInfo[playerid][pCheepsTimer] == 1) return RefreshInv2(playerid, td), SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Между использованием предметов должно пройти 3 секунды!");
						if(!IsPlayerInHisVehicle(playerid)) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Вы не находитесь в личном транспорте!"), RefreshInv2(playerid, td);
						if(IsPlayerInHisVehicle(playerid))
						{
							new vehid = GetPlayerVehicleID(playerid);
							new number = GetVehicleID(vehid);
							if(CarInfo[number][Supreme] == 1) return SendClientMessage(playerid,COLOR_LIGHTRED,"[Ошибка] {FFFFFF}Уже установлено!"), RefreshInv2(playerid, td);
							{
								CarInfo[number][Supreme] = 1;
								SupremeInstall(vehid);
								PlayerInfo[playerid][pSupreme] -=1;
								RefreshInv(playerid, td);
								ShowPlayerDialogEx(playerid, 0,0,"","{FFFFFF}Поздравляем! Вы установили наклейку {FAAC58}Supreme.{FFFFFF}\nТеперь ваш автомобиль будет выглядеть бомбезно!","Принять","");
						    }
						}
						closeuse(playerid);
					}
					case 1550:
			        {
			            closeuse(playerid);
						GiveMoneyRoulette(playerid,5000000);
						format(string,400,"Игрок <a href=/logsaccount?name=%s>%s</a> получил деньги $5000000 по причине: обменял талон на 5кк (Money: %d)",PN(playerid),PN(playerid),PlayerInfo[playerid][pMoney]);
						MoneyLogs(playerid, string, 0);
						AllLogs(playerid, string);
	                    DeleteItem(playerid, 575, 1);
					}
					case 2919:
			        {
			            closeuse(playerid);
						GiveMoneyRoulette(playerid,2000000);
						format(string,400,"Игрок <a href=/logsaccount?name=%s>%s</a> получил деньги $2000000 по причине: обменял талон на 2кк (Money: %d)",PN(playerid),PN(playerid),PlayerInfo[playerid][pMoney]);
						MoneyLogs(playerid, string, 0);
						AllLogs(playerid, string);
	                    DeleteItem(playerid, 576, 1);
					}
					case 18631:
					{
					    vremya[playerid] = PickInvent[playerid];
					    ShowPlayerDialogEx(playerid, 4401, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
					}
			        case 2694:
			        {
			            closeuse(playerid);
			            callcmd::launchinst(playerid);
					}
			        case 2601:
					{
						closeuse(playerid);
						callcmd::sprunk(playerid, "");
					}
					case 18846:
                    {
			            closeuse(playerid);
			            callcmd::HalloweenInstall(playerid);
					}
				 	case 1097:
                    {
			            closeuse(playerid);
			            callcmd::NewyearInstall(playerid);
					}
					case 19823:
					{
						new Float:Health;
						GetPlayerHealth(playerid,Health);
						DeleteItem(playerid, 586, 1);
						SaveInventory(playerid);
						format(string, sizeof(string), "%s выпил(а) бутылочку виски", cPN(playerid));
						ProxDetector(25.0, playerid, string, COLOR_PURPLE);
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_SPRUNK);
						if(Health <= 92.0) J_SetPlayerHealth(playerid,Health+8);
						else J_SetPlayerHealth(playerid,100);
						closeuse(playerid);
					}
					case 19824:
					{
						new Float:Health;
						GetPlayerHealth(playerid,Health);
						DeleteItem(playerid, 587, 1);
						SaveInventory(playerid);
						format(string, sizeof(string), "%s выпил(а) бутылочку коньяка", cPN(playerid));
						ProxDetector(25.0, playerid, string, COLOR_PURPLE);
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_SPRUNK);
						if(Health <= 92.0) J_SetPlayerHealth(playerid,Health+8);
						else J_SetPlayerHealth(playerid,100);
                        closeuse(playerid);
					}
					case 2814:
					{
						new Float:Health;
						GetPlayerHealth(playerid,Health);
						DeleteItem(playerid, 588, 1);
						SaveInventory(playerid);
						format(string, sizeof(string), "%s съел(а) пиццу", cPN(playerid));
						ProxDetector(25.0, playerid, string, COLOR_PURPLE);
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_SPRUNK);
						if(Health <= 92.0) J_SetPlayerHealth(playerid,Health+8);
						else J_SetPlayerHealth(playerid,100);
						closeuse(playerid);
					}
					case 2768:
					{
						new Float:Health;
						GetPlayerHealth(playerid,Health);
						DeleteItem(playerid, 589, 1);
						SaveInventory(playerid);
						format(string, sizeof(string), "%s съел(а) бургер", cPN(playerid));
						ProxDetector(25.0, playerid, string, COLOR_PURPLE);
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_SPRUNK);
						if(Health <= 92.0) J_SetPlayerHealth(playerid,Health+8);
						else J_SetPlayerHealth(playerid,100);
						closeuse(playerid);
					}
					case 2663:
					{
						eatcheeps(playerid);
					    closeuse(playerid);
					}
					case 19882:
					{
					    callcmd::jfish(playerid);
					    closeuse(playerid);
					}
					case 19904,18637:
					{
					    if(PlayerInfo[playerid][pSlotItem][3] != 0) return ShowPlayerDialogEx(playerid, 11103, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks4(playerid, itemid, PickInvent[playerid]);
					}
					case 19921,11745,19624:
					{
					    if(PlayerInfo[playerid][pSlotItem][4] != 0) return ShowPlayerDialogEx(playerid, 11104, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks5(playerid, itemid, PickInvent[playerid]);
					}
					case 19469,19421..19424,19079,1609,11712,19347,1254,16776,3105,3056,341,1212:
					{
					    if(PlayerInfo[playerid][pSlotItem][0] != 0) return ShowPlayerDialogEx(playerid, 11106, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks6(playerid, itemid, PickInvent[playerid]);
					}
					case 19039..19053:
					{
					    if(PlayerInfo[playerid][pSlotItem][6] != 0) return ShowPlayerDialogEx(playerid, 13000, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks7(playerid, itemid, PickInvent[playerid]);
					}
					case 19011..19019,19024,19027,19028,19029,19022,19035,19031,19032,19033:
					{
					    if(PlayerInfo[playerid][pSlotItem][7] != 0) return ShowPlayerDialogEx(playerid, 13001, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks8(playerid, itemid, PickInvent[playerid]);
					}
			        case 19874:
			        {
			            if(PlayerInfo[playerid][pCheepsTimer] == 1) return RefreshInv2(playerid, td), SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Между использованием предметов должно пройти 3 секунды!");
                        RefreshInv(playerid, td);
						closeuse(playerid);
      					new Float:Health;
						Adrenaline[playerid] = CreateDynamicPickup(1241,5, X,Y,Z,GetPlayerInterior(playerid),GetPlayerVirtualWorld(playerid),playerid);
						GetPlayerHealth(playerid,Health);
						format(string, sizeof(string), "%s закинулся таблеткой адреналина", cPN(playerid));
						ProxDetector(25.0, playerid, string, COLOR_PURPLE);
						ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1,0,0,0,0,0,1);
						SetTimerEx("ClearAnims2",900, 0, "d", playerid);
						if(Health <= 50.0) J_SetPlayerHealth(playerid,Health+50);
						else J_SetPlayerHealth(playerid,100);
						PlayerInfo[playerid][pSecondpage] = 0;
						SetTimer("DeletePickup", 1000, 0);
					}
			        case 19998:
			        {
						callcmd::smoke(playerid, "");
						closeuse(playerid);
			        }
			        case 19918:
					{
						if(PlayerInfo[playerid][pChestTime] > 0) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Время после прошлого использования ещё не прошло!"), RefreshInv2(playerid, td);
						if(GetInvSet(playerid) >= 72) return RefreshInv2(playerid, PickInvent[playerid]), SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}У вас не хватает места в инвентаре!");
						if(PlayerInfo[playerid][pLevel] <= 2) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Открывать этот сундук можно только с 3 уровня!"), RefreshInv2(playerid, td);
						PlayerInfo[playerid][pChestTime] = 3600;
						switch(random(101))
						{
							case 0..69:
								{
									SendClientMessage(playerid, COLOR_GREEN, !"Вы использовали сундук с рулетками и получили бронзовую рулетку!"); AddItem2(playerid);
								}
							case 70..90:
								{
									SendClientMessage(playerid, COLOR_GREEN, !"Вы использовали сундук с рулетками и получили серебряную рулетку!"); AddItem3(playerid);
								}
							case 91..100:
								{
								    SendClientMessage(playerid, COLOR_GREEN, !"Вы использовали сундук с рулетками и получили золотую рулетку!"); AddItem1(playerid);
								}
						}
						SaveInventory(playerid);
						RefreshInv2(playerid, td);
					}
					case 1979:
					{
					    for(new i = 0; i < 7; i++)
					    {
					        TextDrawHideForPlayer(playerid, others[i]);
						}
						for(new i = 0; i < 2; i++)
						{
						    DestroyPlayerTD(playerid, kletka[playerid][i]);
						}
						for(new i = 0; i < 63; i++)
					    {
					        DestroyPlayerTD(playerid,InvTextDraws[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,Govnishe[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,GovnisheKletki[playerid][i]);
					    }
					    for(new i = 0; i < 6; i++)
						{
						    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
						}
						for(new i = 0; i < 7; i++)
						{
						    DestroyPlayerTD(playerid, TDinv[playerid][i]);
						}
						for(new i = 0; i < 8; i++)
						{
						    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
						}
						for(new i = 0; i < 4; i++)
						{
						    PlayerTextDrawHide(playerid, TDinvTrash[playerid][i]);
						}
						ShowRoulette(playerid);
					}
					case 2894:
					{
						InvNumber(playerid);
						RefreshInv2(playerid, td);
						closeuse(playerid);
						CancelSelectTextDraw(playerid);
					}
     			case 18874:
					{
					    new IDS = PickInvent[playerid];
					    new ID = PlayerInfo[playerid][pInventory][IDS];
      					for(new i = 0; i < 63; i++)
					    {
					        DestroyPlayerTD(playerid,InvTextDraws[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,Govnishe[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,GovnisheKletki[playerid][i]);
					    }
					    for(new i = 0; i < 6; i++)
						{
						    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
						}
						for(new i = 0; i < 7; i++)
						{
						    DestroyPlayerTD(playerid, TDinv[playerid][i]);
						}
						for(new i = 0; i < 8; i++)
						{
						    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
						}
						for(new i = 0; i < 4; i++)
						{
						    PlayerTextDrawHide(playerid, TDinvTrash[playerid][i]);
						}
						if(PlayerInfo[playerid][pTelNum] == 0 || PlayerInfo[playerid][pTelNum] == 1) return CancelSelectTextDraw(playerid), SendClientMessage(playerid, COLOR_GREY, !"У вас нет мобильного телефона или sim карты!");
                        CreatePhoneTD(playerid);
						if(skinmenu[playerid]==1)
						{
							PlayerTextDrawDestroy(playerid,MenuSkin[playerid]);
							skinmenu[playerid]=0;
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "ксиаоми"))
						{
							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал белый Xiaomi Mi 8 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, Xiaomi[playerid][29], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, Xiaomi[playerid][8], string);
							}
							else
							{
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, Xiaomi[playerid][29], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, Xiaomi[playerid][8], string);
							}
							for(new i;i<58;i++)PlayerTextDrawShow(playerid,Xiaomi[playerid][i]);
							for(new i = 23; i < 26; i++) PlayerTextDrawShow(playerid, XiaomiVK[playerid][i]);
							TelephoneOpen[playerid] = 1;
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "серебряный"))
						{
							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал серебряный Samsung Galaxy S10 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, samsung[playerid][29], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, samsung[playerid][50], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, samsung[playerid][29], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, samsung[playerid][50], string);
							}
							for(new i;i<72;i++)PlayerTextDrawShow(playerid,samsung[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 10;
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "белый"))
						{
							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал белый Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 2;
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "голубой"))
						{
							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал голубой Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 3;
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "зеленый"))
						{
							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал зеленый Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 4;
							SelectTextDraw(playerid, 0xe86868ff);
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "оранжевый"))
						{

							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал оранжевый Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 5;
							SelectTextDraw(playerid, 0xe86868ff);
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "желтый"))
						{

							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал желтый Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 6;
							SelectTextDraw(playerid, 0xe86868ff);
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "розовый"))
						{

							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал розовый Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 7;
							SelectTextDraw(playerid, 0xe86868ff);
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "черный"))
						{

							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал черный Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 8;
							SelectTextDraw(playerid, 0xe86868ff);
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "золотой"))
						{

							if(PlayerInfo[playerid][pCalling]!=-1) return false;

							SelectTextDraw(playerid, 0xFF6347FF);
							if(PlayerInfo[playerid][pONPhoneTalk]>0)return 1;
							foreach(Player,id)if(PlayerInfo[id][pCalling]==playerid && IsPlayerLogged[id]) {return 1;}
							SetPlayerAttachedObject(playerid,9,18874,14,0.409999,0.037999,0.004999,-16.999998,-6.600011,-153.600067,1.000000,1.000000,1.000000);
							format(string,sizeof(string),"%s достал золотой Google Pixel 3 из кармана", cPN(playerid));
							ProxDetector(25.0, playerid, string, COLOR_ME);
							new hour,minuite;
							gettime(hour,minuite);
							TelephoneOpen[playerid] = 9;
							if (minuite < 10)
							{
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:0%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							else
							{
							    format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][30], string);
								format(string,sizeof(string),"%d:%d",hour,minuite);
								PlayerTextDrawSetString(playerid, GooglePixel[playerid][7], string);
							}
							for(new i;i<57;i++)PlayerTextDrawShow(playerid,GooglePixel[playerid][i]);
							for(new i = 0; i < 3; i++) PlayerTextDrawShow(playerid, GooglePixelVK[playerid][i]);
							PlayerInfo[playerid][pSecondpage] = 0;
							RefreshInv2(playerid, td);
							TelephoneOpen[playerid] = 9;
							SelectTextDraw(playerid, 0xe86868ff);
						}

					}
					case 1486:
					{
					    if(PlayerInfo[playerid][pCheepsTimer] == 1) return RefreshInv2(playerid, td), SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Между использованием предметов должно пройти 3 секунды!");
                        RefreshInv(playerid, td);
						closeuse(playerid);
                        callcmd::beer(playerid, "");
					}
					case 11748:
					{
					        callcmd::break(playerid, "");
							closeuse(playerid);
					}
					case 365:
					{
						RefreshInv(playerid, td);
					    ShowPlayerDialogEx(playerid,2393,1, "Введите цвет","{FFFFFF}Введите цвет 1 и цвет 2 через запятую\n{9ACD32}- Пример: {0AD6FF}132,132","Далее","Отмена");
					    closeuse(playerid);
						PlayerInfo[playerid][pRepBan] -=1;
						CancelSelectTextDraw(playerid);
					}
					case 1242:
					{
					    callcmd::armour(playerid);
						closeuse(playerid);
					}
					case 13646:
					{
					    for(new i = 0; i < 7; i++)
					    {
					        TextDrawHideForPlayer(playerid, others[i]);
						}
						for(new i = 0; i < 2; i++)
						{
						    DestroyPlayerTD(playerid, kletka[playerid][i]);
						}
						for(new i = 0; i < 63; i++)
					    {
					        DestroyPlayerTD(playerid,InvTextDraws[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,Govnishe[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,GovnisheKletki[playerid][i]);
					    }
					    for(new i = 0; i < 6; i++)
						{
						    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
						}
						for(new i = 0; i < 7; i++)
						{
						    DestroyPlayerTD(playerid, TDinv[playerid][i]);
						}
						for(new i = 0; i < 8; i++)
						{
						    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
						}
						for(new i = 0; i < 4; i++)
						{
						    PlayerTextDrawHide(playerid, TDinvTrash[playerid][i]);
						}
						PlayerInfo[playerid][pSecondpage] = 0;
						ShowRoulette(playerid);
					}
					case 1895:
					{
					    for(new i = 0; i < 7; i++)
					    {
					        TextDrawHideForPlayer(playerid, others[i]);
						}
						for(new i = 0; i < 2; i++)
						{
						    DestroyPlayerTD(playerid, kletka[playerid][i]);
						}
						for(new i = 0; i < 63; i++)
					    {
					        DestroyPlayerTD(playerid,InvTextDraws[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,Govnishe[playerid][i]);
					    }
					    for(new i = 0; i < 72; i++)
					    {
					        DestroyPlayerTD(playerid,GovnisheKletki[playerid][i]);
					    }
					    for(new i = 0; i < 6; i++)
						{
						    DestroyPlayerTD(playerid, InfoItems[playerid][i]);
						}
						for(new i = 0; i < 7; i++)
						{
						    DestroyPlayerTD(playerid, TDinv[playerid][i]);
						}
						for(new i = 0; i < 8; i++)
						{
						    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
						}
						for(new i = 0; i < 4; i++)
						{
						    PlayerTextDrawHide(playerid, TDinvTrash[playerid][i]);
						}
						ShowRoulette(playerid);
					}
					case 1..311:
					{
					    if(InJob[playerid] == 1) return RefreshInv2(playerid, td);
				    	if(TeamDuty[playerid] == 1) return RefreshInv2(playerid, td);
				    	CheckSuka(playerid);
					}
					case 11738:
					{
						callcmd::usemed(playerid, "");
					    closeuse(playerid);
					}
		            case 1951:
		            {
		                callcmd::killme(playerid, "");
						closeuse(playerid);
					}
					case 19627:
					{
					    callcmd::repcar(playerid, "");
						closeuse(playerid);
					}
					case 19163:
					{
					    callcmd::mask(playerid, "");
						closeuse(playerid);
					}
					case 19625:
					{
					    callcmd::smoke(playerid, "");
						closeuse(playerid);
			        }
			        case 331:
			        {
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Brass Knuckles' с боеприпасами 1");
                      		RefreshInv(playerid, td);
		                    _GiveGun(playerid, 1, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
					case 371:
			        {
			            new ID = PlayerInfo[playerid][pInventory][PickInvent[playerid]];
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];

			            if(GetString(ItemsInfo[ID][ItemPhoneColor], "ПортфельАкс"))
			            {
			                if(PlayerInfo[playerid][pSlotItem][5] != 0) return ShowPlayerDialogEx(playerid, 11102, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
						    CheckAks(playerid, itemid, PickInvent[playerid]);
						}
			            if(GetString(ItemsInfo[ID][ItemPhoneColor], "Парашют"))
			            {
				            if(ID2 == 1)
			                {
			                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Parachute' с боеприпасами 1");
			                    RefreshInv(playerid, td);
			                    _GiveGun(playerid, 46, 1);
			                    closeuse(playerid);
							 	return true;
							}
							ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
							vremya[playerid] = PickInvent[playerid];
							PlayerInfo[playerid][pDolboeb] = 1;
						}
					}
					case 343:
			        {
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Tear gas' с боеприпасами 1");
		                    RefreshInv(playerid, td);
		                    _GiveGun(playerid, 17, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
					case 348:
			        {
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Desert Eagle' с боеприпасами 1");
		                    RefreshInv(playerid, td);
		                    _GiveGun(playerid, 24, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
					case 349:
			        {
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Shotgun' с боеприпасами 1");
		                    RefreshInv(playerid, td);
		                    _GiveGun(playerid, 25, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
					case 353:
			        {
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'MP5' с боеприпасами 1");
		                    RefreshInv(playerid, td);
		                    _GiveGun(playerid, 29, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
					case 355:
					{
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'AK47' с боеприпасами 1");
		                    RefreshInv(playerid, td);
		                    _GiveGun(playerid, 30, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
					case 356:
			        {
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'M4' с боеприпасами 1");
		                    RefreshInv(playerid, td);
		                    _GiveGun(playerid, 31, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
					case 357:
			        {
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(ID2 == 1)
		                {
		                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Country Rifle' с боеприпасами 1");
		                    RefreshInv(playerid, td);
		                    _GiveGun(playerid, 33, 1);
		                    closeuse(playerid);
						 	return true;
						}
						ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
						vremya[playerid] = PickInvent[playerid];
						PlayerInfo[playerid][pDolboeb] = 1;
					}
			        case 336:
			        {
			            new ID = PlayerInfo[playerid][pInventory][PickInvent[playerid]];
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(GetString(ItemsInfo[ID][ItemPhoneColor], "БитаАкс"))
			            {
				            if(PlayerInfo[playerid][pSlotItem][5] != 0) return ShowPlayerDialogEx(playerid, 11102, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
						    CheckAks(playerid, itemid, PickInvent[playerid]);
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "Бита"))
			            {
			                if(ID2 == 1)
			                {
			                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Baseball Bat' с боеприпасами 1");
			                    RefreshInv(playerid, td);
			                    _GiveGun(playerid, 5, 1);
			                    closeuse(playerid);
							 	return true;
							}
				            ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
				            vremya[playerid] = PickInvent[playerid];
				            PlayerInfo[playerid][pDolboeb] = 1;
						}
					}
			        case 339:
			        {
			            new ID = PlayerInfo[playerid][pInventory][PickInvent[playerid]];
			            new ID2 = PlayerInfo[playerid][pInventoryKolvo][PickInvent[playerid]];
			            if(GetString(ItemsInfo[ID][ItemPhoneColor], "КатанаАкс"))
			            {
				            if(PlayerInfo[playerid][pSlotItem][5] != 0) return ShowPlayerDialogEx(playerid, 11102, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
						    CheckAks(playerid, itemid, PickInvent[playerid]);
						}
						if(GetString(ItemsInfo[ID][ItemPhoneColor], "Катана"))
			            {
			                if(ID2 == 1)
			                {
			                    SendClientMessage(playerid, COLOR_VALIK, !"[Информация] {FFFFFF}Вы достали из кармана 'Katana' с боеприпасами 1");
							 	RefreshInv(playerid, td);
			                    _GiveGun(playerid, 8, 1);
			                    closeuse(playerid);
							 	return true;
							}
				            ShowPlayerDialogEx(playerid, 12219, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
				            vremya[playerid] = PickInvent[playerid];
				            PlayerInfo[playerid][pDolboeb] = 1;
						}
					}
			        case 2102,2690,2045,19590,19631,2226,333337,338,326,19591,1276,19317,19319,19318,19054,19055,19056,19057,19058,19847,2803,19878,2406,3026,19559,19636,2511,8492,19332,19333,19334,19335,19336,19337,19338,18635,2057:
					{
					    if(PlayerInfo[playerid][pSlotItem][5] != 0) return ShowPlayerDialogEx(playerid, 11102, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks(playerid, itemid, PickInvent[playerid]);
					}
					case 18963,19036,19037,19038,19472,19350,19085,11704,6865,18911..18920,368:
					{
					    if(PlayerInfo[playerid][pSlotItem][1] != 0) return ShowPlayerDialogEx(playerid, 11101, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks2(playerid, itemid, PickInvent[playerid]);
					}
					case 19090..19091,19092,18636,19487,19352,19064,19065,19066,19200,19141,2908,19314,19094,19197,19136,18952,19346,19137,19067..19069,19554,18953,18954,18968,18967,18969,18955,18956,18957,18959,18926,18927,18928,18929,18930,18931,18932,18933,19104..19109,18921..18925,19519,19274,18906..18910,18970..18973,18947,18948,18949,18950,18951,19521:
					{
					    if(PlayerInfo[playerid][pSlotItem][2] != 0) return ShowPlayerDialogEx(playerid, 11100, 0, "", "{FFFFFF}Слот для данного аксессуара занят другим аксессуаром, заменить его на этот?", "Принять", "Отмена");
					    CheckAks3(playerid, itemid, PickInvent[playerid]);
					}
					case 18875:
					{
					    callcmd::radio(playerid, "");
					    closeuse(playerid);
					}
					case 18632:
					{
					    callcmd::go_fished(playerid, "");
					    closeuse(playerid);
					}
					case 2709:
					{
						callcmd::usebad(playerid, "");
						closeuse(playerid);
					}
					case 862:
					{
					    callcmd::usedrugs(playerid, "");
					    closeuse(playerid);
					}
					case 1274:
					{
					    vremya[playerid] = PickInvent[playerid];
					    ShowPlayerDialogEx(playerid, 4400, DIALOG_STYLE_INPUT, "", "{FFFFFF}Введите количество, которое хотите использовать", "Принять", "Отмена");
					}
            	}
				RefreshInv2(playerid, td);
	            return true;
}
stock InfoItem(playerid, td)
{
                new IDS = td;
		        new ID = PlayerInfo[playerid][pInventory][IDS];
				deletevy(playerid);
				updateslot6(playerid);
				new str[570];
				for(new i = 0; i < 312; i++)
				{
					if(PlayerInfo[playerid][pInventory][IDS] == i)
					{
						if(GetPlayerSkin(playerid) != 18)
						{
					    	PlayerTextDrawSetSelectable(playerid, InvTextDraws[playerid][46], 1);
					    	PlayerTextDrawHide(playerid, InvTextDraws[playerid][46]);
					    	PlayerTextDrawShow(playerid, InvTextDraws[playerid][46]);
						}
					}
				}
       			PlayerTextDrawSetSelectable(playerid, Govnishe[playerid][IDS], 1);
      			for(new i = 0; i < 7; i++)
				{
											DestroyPlayerTD(playerid, fstd_p[playerid][i]);
				}
				for(new i = 0; i < 8; i++)
				{
				    DestroyPlayerTD(playerid, dropmenu[playerid][i]);
				}
				for(new i = 0; i < 6; i++)
				{
											DestroyPlayerTD(playerid, InfoItems[playerid][i]);
				}
				if(PickInvent[playerid] != 73)
                {
                	PlayerTextDrawBackgroundColor(playerid, Govnishe[playerid][td], 0x333333FF);
                }
			    format(str, sizeof(str), "{FFFFFF}%s\n%s", ItemsInfo[ID][ItemName], ItemsInfo[ID][ItemInfos]);
				ShowPlayerDialogEx(playerid, 5555, 0, "Информация о предмете", str, "Выход", "");
				RefreshInv2(playerid, td);
                return true;
}
new daunsp[MAX_PLAYERS];
stock AddItem1(playerid)
{
    daunsp[playerid] = 1;
	AddItem(playerid, 322, 1);
    daunsp[playerid] = 0;
	return true;
}
stock AddItem2(playerid)
{
    daunsp[playerid] = 1;
	AddItem(playerid, 324, 1);
    daunsp[playerid] = 0;
	return true;
}
stock AddItemLavka(numberlavki, itemid, itemkolvo, money)
{
	for(new i = 0; i < 10; i++)
    {
        if(ItemsLavka[numberlavki][i] != 0) continue;
        ItemsLavka[numberlavki][i] = itemid;
        ItemsLavkaKolvo[numberlavki][i] = itemkolvo;
        CostLavkaItem[numberlavki][i] = money;
        return true;
    }
	return true;
}
stock AddItem3(playerid)
{
	daunsp[playerid] = 1;
	AddItem(playerid, 323, 1);
    daunsp[playerid] = 0;
	return true;
}
publics Custom_AddShkafItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,
		last_quantity,
		total_quantity,
		house = HouseEntered[playerid];

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(HouseInfo[house][hShkafSlotKol][slot] >= max_quantity) return 0;

	total_quantity = HouseInfo[house][hShkafSlotKol][slot] + quantity;
	if(total_quantity > max_quantity)
	{
		last_quantity = total_quantity - max_quantity;
		HouseInfo[house][hShkafSlotKol][slot] = max_quantity;
	}
	else HouseInfo[house][hShkafSlotKol][slot] += quantity;

	if(last_quantity)
    {
        for(new i = 0; i < 30; i++)
	    {
	        if(HouseInfo[house][hShkafSlot][i] != itemid) continue;
	        if(!CallLocalFunction("Custom_AddShkafItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	    for(new i = 0; i < 30; i++)
	    {
	        if(HouseInfo[house][hShkafSlot][i] != 0) continue;
	        if(!CallLocalFunction("Custom_SetShkafItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	}
	return 1;
}
publics Custom_SetShkafItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,
		last_quantity,
		house = HouseEntered[playerid];

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(HouseInfo[house][hShkafSlotKol][slot] >= max_quantity)return 0;

	if(quantity > max_quantity)
	{
		last_quantity = quantity - max_quantity;
		quantity = max_quantity;
	}

	HouseInfo[house][hShkafSlot][slot] = itemid;
    HouseInfo[house][hShkafSlotKol][slot] = quantity;
	ShkafSlotUpdate(playerid, slot, HouseInfo[house][hShkafSlot][slot]);
    if(last_quantity)
    {
        for(new i = 0; i < 30; i++)
	    {
	        if(HouseInfo[house][hShkafSlot][i] != itemid) continue;
	        if(!CallLocalFunction("Custom_AddShkafItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	    for(new i = 0; i < 30; i++)
	    {
	        if(HouseInfo[house][hShkafSlot][i] != 0) continue;
	        if(!CallLocalFunction("Custom_SetShkafItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	}
	return 1;
}
publics Custom_AddTrashItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,

		last_quantity,
		total_quantity,
		musor = musorka[playerid];

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(mInfo[musor][InventoryTrashKolvo][slot] >= max_quantity)return 0;

	total_quantity = mInfo[musor][InventoryTrashKolvo][slot] + quantity;
	if(total_quantity > max_quantity)
	{
		last_quantity = total_quantity - max_quantity;
		mInfo[musor][InventoryTrashKolvo][slot] = max_quantity;
	}
	else mInfo[musor][InventoryTrashKolvo][slot] += quantity;
    foreach(Player, g)
	{
	    if(musorka[g] != musorka[playerid]) continue;
		TrashSlotUpdate(g, slot, mInfo[musor][InventoryTrash][slot]);
	}
	if(last_quantity)
    {
        for(new i = 0; i < 30; i++)
	    {
	        if(mInfo[musor][InventoryTrash][i] != itemid) continue;
	        if(!CallLocalFunction("Custom_AddTrashItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	    for(new i = 0; i < 30; i++)
	    {
	        if(mInfo[musor][InventoryTrash][i] != 0) continue;
	        if(!CallLocalFunction("Custom_SetTrashItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	}
	return 1;
}
publics Custom_SetTrashItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,
		last_quantity,
		musor = musorka[playerid];

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(mInfo[musor][InventoryTrashKolvo][slot] >= max_quantity)return 0;

	if(quantity > max_quantity)
	{
		last_quantity = quantity - max_quantity;
		quantity = max_quantity;
	}

	mInfo[musor][InventoryTrash][slot] = itemid;
    mInfo[musor][InventoryTrashKolvo][slot] = quantity;
    foreach(Player, g)
	{
	    if(musorka[g] != musorka[playerid]) continue;
		TrashSlotUpdate(g, slot, mInfo[musor][InventoryTrash][slot]);
	}
    if(last_quantity)
    {
        for(new i = 0; i < 30; i++)
	    {
	        if(mInfo[musor][InventoryTrash][i] != itemid) continue;
	        if(!CallLocalFunction("Custom_AddTrashItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	    for(new i = 0; i < 30; i++)
	    {
	        if(mInfo[musor][InventoryTrash][i] != 0) continue;
	        if(!CallLocalFunction("Custom_SetTrashItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	}
	return 1;
}
publics Custom_AddTrunkItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,

		last_quantity,
		total_quantity,
		trunk = idaofcar[playerid];

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(TrunkInfo[trunk][tBagazhnikSlotKol][slot] >= max_quantity)return 0;

	total_quantity = TrunkInfo[trunk][tBagazhnikSlotKol][slot] + quantity;
	if(total_quantity > max_quantity)
	{
		last_quantity = total_quantity - max_quantity;
		TrunkInfo[trunk][tBagazhnikSlotKol][slot] = max_quantity;
	}
	else TrunkInfo[trunk][tBagazhnikSlotKol][slot] += quantity;
    foreach(Player, g)
	{
	    if(idaofcar[g] != idaofcar[playerid]) continue;
		BagazhnikSlotUpdate(g, slot, TrunkInfo[idaofcar[g]][tBagazhnikSlot][slot]);
	}
    if(last_quantity)
    {
        for(new i = 0; i < 30; i++)
	    {
	        if(TrunkInfo[trunk][tBagazhnikSlot][i] != itemid) continue;
	        if(!CallLocalFunction("Custom_AddTrunkItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	    for(new i = 0; i < 30; i++)
	    {
	        if(TrunkInfo[trunk][tBagazhnikSlot][i] != 0) continue;
	        if(!CallLocalFunction("Custom_SetTrunkItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	}
	return 1;
}
publics Custom_SetTrunkItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,
		last_quantity,
		trunk = idaofcar[playerid];

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(TrunkInfo[trunk][tBagazhnikSlotKol][slot] >= max_quantity)return 0;

	if(quantity > max_quantity)
	{
		last_quantity = quantity - max_quantity;
		quantity = max_quantity;
	}

	TrunkInfo[trunk][tBagazhnikSlot][slot] = itemid;
    TrunkInfo[trunk][tBagazhnikSlotKol][slot] = quantity;
	foreach(Player, g)
	{
	    if(idaofcar[g] != idaofcar[playerid]) continue;
		BagazhnikSlotUpdate(g, slot, TrunkInfo[idaofcar[g]][tBagazhnikSlot][slot]);
	}
    if(last_quantity)
    {
        for(new i = 0; i < 30; i++)
	    {
	        if(TrunkInfo[trunk][tBagazhnikSlot][i] != itemid) continue;
	        if(!CallLocalFunction("Custom_AddTrunkItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	    for(new i = 0; i < 30; i++)
	    {
	        if(TrunkInfo[trunk][tBagazhnikSlot][i] != 0) continue;
			if(!CallLocalFunction("Custom_SetTrunkItem", "dddd", playerid, i, itemid, last_quantity)) continue;
	        return 1;
	    }
	}
	return 1;
}
publics Custom_AddInvItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,

		last_quantity,
		total_quantity;

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(PlayerInfo[playerid][pInventoryKolvo][slot] >= max_quantity)return 0;

	total_quantity = PlayerInfo[playerid][pInventoryKolvo][slot] + quantity;
	if(total_quantity > max_quantity)
	{
		last_quantity = total_quantity - max_quantity;
		PlayerInfo[playerid][pInventoryKolvo][slot] = max_quantity;
	}
	else PlayerInfo[playerid][pInventoryKolvo][slot] += quantity;
    if(TradeDone[playerid] == -1) RefreshInv2(playerid, slot);
	if(last_quantity) CallLocalFunction("AddItem", "ddd", playerid, itemid, last_quantity);
	return 1;
}
publics Custom_SetInvItem(playerid, slot, itemid, quantity)
{
	new
		max_quantity = 0,
		last_quantity;

	max_quantity = ItemsInfo[itemid][ItemQuantity];
	if(!max_quantity)return 0;
	if(PlayerInfo[playerid][pInventoryKolvo][slot] >= max_quantity)return 0;

	if(quantity > max_quantity)
	{
		last_quantity = quantity - max_quantity;
		quantity = max_quantity;
	}

	PlayerInfo[playerid][pInventory][slot] = itemid;
    PlayerInfo[playerid][pInventoryKolvo][slot] = quantity;
    InvSlotUpdate(playerid, slot, itemid);
    if(last_quantity) CallLocalFunction("AddItem", "ddd", playerid, itemid, last_quantity);
	return 1;
}
stock AddItem(playerid, itemid, amount)
{
	new string[180];
	new send;
	//new kdkd;
	if(GetInvSet(playerid) >= 72) return SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}У вас не хватает места в инвентаре!");
	if(TradeDone[playerid] != -1 || ShkafOpen[playerid] == 1 || PlayerInfo[playerid][pTrashOpen] == 1 || BagazhnikOpen[playerid] == 1)
	{
		for(new i = 0; i < 72; i++)
	    {
	        if(PlayerInfo[playerid][pInventory][i] != itemid) continue;
	        if(!Custom_AddInvItem(playerid, i, itemid, amount)) continue;
	        return 1;
	    }
	    for(new i = 0; i < 72; i++)
	    {
	        if(PlayerInfo[playerid][pInventory][i] != 0) continue;
	        if(!Custom_SetInvItem(playerid, i, itemid, amount)) continue;
	        return 1;
	    }
	}
	send = 1;
	if(itemid == 313) send = 0;
	if(itemid == 0) send = 0;
	if(itemid == 324) send = 0;
	if(itemid == 323) send = 0;
	if(itemid == 322) send = 0;
	if(send == 1)
	{
		if(amount >= 2)
		{
	    	format(string, sizeof(string), "[Инвентарь] {FFFFFF}Вам был добавлен предмет '%s' (%d шт). Чтобы открыть инвентарь, введите /invent.", ItemsInfo[itemid][ItemName2], amount);
			SendClientMessage(playerid, COLOR_YELLOW, string);
		}
		else
		{
		    format(string, sizeof(string), "[Инвентарь] {FFFFFF}Вам был добавлен предмет '%s'. Чтобы открыть инвентарь, введите /invent.", ItemsInfo[itemid][ItemName2], amount);
			SendClientMessage(playerid, COLOR_YELLOW, string);
		}
	}
	for(new i = 0; i < 72; i++)
    {
        if(PlayerInfo[playerid][pInventory][i] != itemid) continue;
        if(!Custom_AddInvItem(playerid, i, itemid, amount)) continue;
        return 1;
    }
    for(new i = 0; i < 72; i++)
    {
        if(PlayerInfo[playerid][pInventory][i] != 0) continue;
        if(!Custom_SetInvItem(playerid, i, itemid, amount)) continue;
        return 1;
    }
	SaveInventory(playerid);
    return 1;
}
publics DeleteItem(playerid, itemid, amount)
{
    for(new i = 0; i < 72; i++)
    {
        if(PlayerInfo[playerid][pInventory][i] != itemid) continue;
        new daun;
		daun = amount-PlayerInfo[playerid][pInventoryKolvo][i];
		PlayerInfo[playerid][pInventoryKolvo][i] -= amount;
		if(PlayerInfo[playerid][pInventoryKolvo][i] <= -1)
		{
		    PlayerInfo[playerid][pInventoryKolvo][i] = 0;
		    PlayerInfo[playerid][pInventory][i] = 0;
      		CallLocalFunction("DeleteItem", "ddd", playerid, itemid, daun);
		}
		RefreshInv2(playerid, i);
        return 1;
    }
    return 1;
}
stock AddItemOn(playerid, itemid, amount)
{
    if(PlayerInfo[playerid][pInventory][0] != 0 && PlayerInfo[playerid][pInventory][1] != 0 && PlayerInfo[playerid][pInventory][2] != 0 && PlayerInfo[playerid][pInventory][3] != 0 && PlayerInfo[playerid][pInventory][4] != 0 && PlayerInfo[playerid][pInventory][5] != 0 && PlayerInfo[playerid][pInventory][6] != 0 && PlayerInfo[playerid][pInventory][7] != 0 && PlayerInfo[playerid][pInventory][8] != 0 && PlayerInfo[playerid][pInventory][9] != 0 && PlayerInfo[playerid][pInventory][10] != 0 && PlayerInfo[playerid][pInventory][11] != 0 && PlayerInfo[playerid][pInventory][12] != 0 && PlayerInfo[playerid][pInventory][13] != 0 && PlayerInfo[playerid][pInventory][14] != 0 && PlayerInfo[playerid][pInventory][15] != 0 && PlayerInfo[playerid][pInventory][16] != 0 && PlayerInfo[playerid][pInventory][17] != 0 && PlayerInfo[playerid][pInventory][18] != 0 && PlayerInfo[playerid][pInventory][19] != 0 && PlayerInfo[playerid][pInventory][20] != 0 && PlayerInfo[playerid][pInventory][21] != 0 && PlayerInfo[playerid][pInventory][22] != 0 && PlayerInfo[playerid][pInventory][23] != 0 && PlayerInfo[playerid][pInventory][24] != 0 && PlayerInfo[playerid][pInventory][25] != 0 && PlayerInfo[playerid][pInventory][26] != 0 && PlayerInfo[playerid][pInventory][27] != 0 && PlayerInfo[playerid][pInventory][28] != 0 && PlayerInfo[playerid][pInventory][29] != 0 && PlayerInfo[playerid][pInventory][30] != 0 && PlayerInfo[playerid][pInventory][31] != 0 && PlayerInfo[playerid][pInventory][32] != 0 && PlayerInfo[playerid][pInventory][33] != 0 && PlayerInfo[playerid][pInventory][34] != 0 && PlayerInfo[playerid][pInventory][35] != 0 && PlayerInfo[playerid][pInventory][36] != 0 && PlayerInfo[playerid][pInventory][37] != 0 && PlayerInfo[playerid][pInventory][38] != 0 && PlayerInfo[playerid][pInventory][39] != 0 && PlayerInfo[playerid][pInventory][40] != 0 && PlayerInfo[playerid][pInventory][41] != 0 && PlayerInfo[playerid][pInventory][42] != 0 && PlayerInfo[playerid][pInventory][43] != 0 && PlayerInfo[playerid][pInventory][44] != 0 && PlayerInfo[playerid][pInventory][45] != 0 && PlayerInfo[playerid][pInventory][46] != 0 && PlayerInfo[playerid][pInventory][47] != 0 && PlayerInfo[playerid][pInventory][48] != 0 && PlayerInfo[playerid][pInventory][49] != 0 && PlayerInfo[playerid][pInventory][50] != 0 && PlayerInfo[playerid][pInventory][51] != 0 && PlayerInfo[playerid][pInventory][52] != 0 && PlayerInfo[playerid][pInventory][53] != 0 && PlayerInfo[playerid][pInventory][54] != 0 && PlayerInfo[playerid][pInventory][55] != 0 && PlayerInfo[playerid][pInventory][56] != 0 && PlayerInfo[playerid][pInventory][57] != 0 && PlayerInfo[playerid][pInventory][58] != 0 && PlayerInfo[playerid][pInventory][59] != 0 && PlayerInfo[playerid][pInventory][60] != 0 && PlayerInfo[playerid][pInventory][61] != 0 && PlayerInfo[playerid][pInventory][62] != 0 && PlayerInfo[playerid][pInventory][63] != 0 && PlayerInfo[playerid][pInventory][64] != 0 && PlayerInfo[playerid][pInventory][65] != 0 && PlayerInfo[playerid][pInventory][66] != 0 && PlayerInfo[playerid][pInventory][67] != 0 && PlayerInfo[playerid][pInventory][68] != 0 && PlayerInfo[playerid][pInventory][69] != 0 && PlayerInfo[playerid][pInventory][70] != 0 && PlayerInfo[playerid][pInventory][71] != 0) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}У вас не хватает места в инвентаре!");
    for(new i = 0; i < 72; i++)
    {
        if(PlayerInfo[playerid][pInventory][i] != itemid) continue;
        PlayerInfo[playerid][pInventoryKolvo][i] = amount;
        return true;
    }
    for(new i = 0; i < 72; i++)
    {
        if(PlayerInfo[playerid][pInventory][i] != 0) continue;
        PlayerInfo[playerid][pInventory][i] = itemid;
        PlayerInfo[playerid][pInventoryKolvo][i] = amount;
        return true;
    }
	SaveInventory(playerid);
    return true;
}
publics Eating(playerid)
{
	ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1,0,0,0,0,0,1);
}
stock AddFirstCase(playerid)
{
	if(PlayerInfo[playerid][pFirstCase] == 1) return 1;
	AddItem(playerid, 313, 1);
	SaveInventory(playerid);
	PlayerInfo[playerid][pFirstCase] = 1;
	UpdatePlayerData(playerid, "pFirstCase", PlayerInfo[playerid][pFirstCase]);
	SaveInventory(playerid);
	return true;
}
cmd:additem(playerid, params[])
{
	new string[400];
	new id, amount;
	if(GetString(PN(playerid),FullDostup1) || GetString(PN(playerid),FullDostup2) || GetString(PN(playerid),FullDostup3) || GetString(PN(playerid),FullDostup4) || GetString(PN(playerid),FullDostup5) || GetString(PN(playerid),FullDostup6) || GetString(PN(playerid),FullDostup7) || GetString(PN(playerid),FullDostup8) || GetString(PN(playerid),FullDostup9) || GetString(PN(playerid),FullDostup10) || GetString(PN(playerid),FullDostup11) || GetString(PN(playerid),FullDostup12))
    {
		if(sscanf(params,"dddd",id,params[0], amount)) return SendClientMessage(playerid, COLOR_RED, !"[Информация] {FFFFFF}Используйте /additem: [ID игрока] [ID предмета(от 1 до 595)] [кол-во] [0-(добавить)1-(изменить)]");
		if(params[0] < 1 || params[0] > MAX_ITEMS-1) return SendClientMessage(playerid, COLOR_RED, !"[Информация] {FFFFFF}Используйте /additem: [ID игрока] [ID предмета(от 1 до 595)] [кол-во] [0-(добавить)1-(изменить)]");
		if(params[0] == 312) return SendClientMessage(playerid, COLOR_RED, !"[Ошибка] {FFFFFF}Данный предмет давать нельзя!");
        if(GetInvSet(id) >= 72) return SendClientMessage(playerid, COLOR_RED, "[Ошибка] {FFFFFF}У него не хватает места в инвентаре!");
		AddItem(id, params[0], amount);
 		SaveInventory(id);
  		for(new i = 0; i < 72; i++)
    	{
			   if(PlayerInfo[id][pInventoryKolvo][i] < 1)
			   {
				   PlayerInfo[id][pInventoryKolvo][i] = 0;
				   PlayerInfo[id][pInventory][i] = 0;
			   }
		}
		format(string, sizeof(string), "Администратор %s выдал игроку %s предмет %s. Кол-во: %d", Name(playerid), Name(id), ItemsInfo[params[0]][ItemName2], amount);
        SendAdminsMessage(COLOR_GREY, string);
		format(string, sizeof(string), "Администратор <a href=/logsaccount?name=%s>%s</a> выдал игроку <a href=/logsaccount?name=%s>%s</a> предмет %s. Кол-во: %d",PN(playerid), Name(playerid),Name(id), Name(id), ItemsInfo[params[0]][ItemName2], amount);
		AllLogs(playerid, string);
		SendClientMessage(playerid, COLOR_RED, !"[Информация] {FFFFFF}Предмет был успешно выдан.");
	}
	return true;
}
*/
