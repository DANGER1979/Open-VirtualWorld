//для грибников
new Gribb[147];

stock mushroomer_OnGameModeInit()
{	
	Gribb[0] = SetPickupEx(1603, 2,2554.4866,-1547.8124,23.2360); // гриб
	Gribb[1] = SetPickupEx(1603, 2,2345.8481,-1195.5409,27.9766); // гриб
	Gribb[2] = SetPickupEx(1603, 2,2304.1467,-1062.5970,49.0484); // гриб
	Gribb[3] = SetPickupEx(1603, 2,2309.5652,-955.3655,68.5016); // гриб
	Gribb[4] = SetPickupEx(1603, 2,2125.7244,-893.8331,92.3929); // гриб
	Gribb[5] = SetPickupEx(1603, 2,2186.6958,-803.8046,104.8348); // гриб
	Gribb[6] = SetPickupEx(1603, 2,2320.6594,-744.3228,131.3328); // гриб
	Gribb[7] = SetPickupEx(1603, 2,2429.1521,-662.7400,124.9573); // гриб
	Gribb[8] = SetPickupEx(1603, 2,2542.7705,-366.3636,76.7907); // гриб
	Gribb[9] = SetPickupEx(1603, 2,2431.5322,-313.9982,23.8638); // гриб
	Gribb[10] = SetPickupEx(1603, 2,2439.3552,-158.5956,30.8487); // гриб
	Gribb[11] = SetPickupEx(1603, 2,2476.1921,-127.5978,33.5769); // гриб
	Gribb[12] = SetPickupEx(1603, 2,2564.1060,-89.7050,52.4176); // гриб
	Gribb[13] = SetPickupEx(1603, 2,2618.6733,-94.6426,50.9832); // гриб
	Gribb[14] = SetPickupEx(1603, 2,2791.4004,29.6416,21.3129); // гриб
	Gribb[15] = SetPickupEx(1603, 2,2619.4827,116.6820,28.9666); // гриб
	Gribb[16] = SetPickupEx(1603, 2,2611.2283,130.6392,33.0409); // гриб
	Gribb[17] = SetPickupEx(1603, 2,2589.5901,207.4245,57.5631); // гриб
	Gribb[18] = SetPickupEx(1603, 2,2551.7651,257.1455,45.4480); // гриб
	Gribb[19] = SetPickupEx(1603, 2,2505.1697,341.1525,26.7362); // гриб
	Gribb[20] = SetPickupEx(1603, 2,2358.6782,159.8499,27.1063); // гриб
	Gribb[21] = SetPickupEx(1603, 2,2380.0933,60.0288,26.9827); // гриб
	Gribb[22] = SetPickupEx(1603, 2,2380.4814,18.5658,27.0453); // гриб
	Gribb[23] = SetPickupEx(1603, 2,2410.3960,-46.7937,27.2389); // гриб
	Gribb[24] = SetPickupEx(1603, 2,2182.5391,16.7902,21.2947); // гриб
	Gribb[25] = SetPickupEx(1603, 2,1935.5726,170.8273,37.2752); // гриб
	Gribb[26] = SetPickupEx(1603, 2,1937.0952,264.9478,29.8482); // гриб
	Gribb[27] = SetPickupEx(1603, 2,1892.2891,342.8441,21.7069); // гриб
	Gribb[28] = SetPickupEx(1603, 2,1502.9844,315.4365,18.8417); // гриб
	Gribb[29] = SetPickupEx(1603, 2,1485.9904,314.0277,18.8417); // гриб
	Gribb[30] = SetPickupEx(1603, 2,1488.8948,298.4258,18.8192); // гриб
	Gribb[31] = SetPickupEx(1603, 2,1496.9701,256.1078,19.2641); // гриб
	Gribb[32] = SetPickupEx(1603, 2,1515.2375,200.4065,22.0268); // гриб
	Gribb[33] = SetPickupEx(1603, 2,1570.6921,185.7788,24.5648); // гриб
	Gribb[34] = SetPickupEx(1603, 2,1454.4762,114.9145,25.0431); // гриб
	Gribb[35] = SetPickupEx(1603, 2,1429.7319,161.6507,21.8437); // гриб
	Gribb[36] = SetPickupEx(1603, 2,1170.3596,276.6147,18.8740); // гриб
	Gribb[37] = SetPickupEx(1603, 2,1080.5236,500.5382,24.3347); // гриб
	Gribb[38] = SetPickupEx(1603, 2,953.0927,298.1285,26.4466); // гриб
	Gribb[39] = SetPickupEx(1603, 2,882.9598,58.2159,80.9003); // гриб
	Gribb[40] = SetPickupEx(1603, 2,898.8014,-56.8222,60.8444); // гриб
	Gribb[41] = SetPickupEx(1603, 2,935.3439,-69.7337,68.7465); // гриб
	Gribb[42] = SetPickupEx(1603, 2,2300.7822,-1674.0874,14.3935); // гриб
	Gribb[43] = SetPickupEx(1603, 2,405.5328,-1671.5540,28.9598); // гриб
	Gribb[44] = SetPickupEx(1603, 2,128.5249,-1516.3375,10.0527); // гриб
	Gribb[45] = SetPickupEx(1603, 2,-73.0915,-1576.4926,2.6172); // гриб
	Gribb[46] = SetPickupEx(1603, 2,-144.3858,-1604.6605,5.1791); // гриб
	Gribb[47] = SetPickupEx(1603, 2,-192.2744,-1600.7976,5.8638); // гриб
	Gribb[48] = SetPickupEx(1603, 2,-401.0091,-1467.1946,25.7266); // гриб
	Gribb[49] = SetPickupEx(1603, 2,-454.8707,-1447.0631,19.3151); // гриб
	Gribb[50] = SetPickupEx(1603, 2,-601.1472,-1286.1947,21.6525); // гриб
	Gribb[51] = SetPickupEx(1603, 2,-656.3286,-1212.7950,25.5466); // гриб
	Gribb[52] = SetPickupEx(1603, 2,-631.0942,-1086.1055,26.4368); // гриб
	Gribb[53] = SetPickupEx(1603, 2,-389.1690,-968.0870,51.0263); // гриб
	Gribb[54] = SetPickupEx(1603, 2,-393.1837,-771.3217,32.0947); // гриб
	Gribb[55] = SetPickupEx(1603, 2,-467.1896,-677.1692,17.3798); // гриб
	Gribb[56] = SetPickupEx(1603, 2,-464.0555,-593.8693,12.0775); // гриб
	Gribb[57] = SetPickupEx(1603, 2,-464.1641,-428.5057,17.9460); // гриб
	Gribb[58] = SetPickupEx(1603, 2,-636.0601,-448.6402,28.7089); // гриб
	Gribb[59] = SetPickupEx(1603, 2,-726.6664,-508.7917,30.0043); // гриб
	Gribb[60] = SetPickupEx(1603, 2,-919.0322,-520.2017,25.9536); // гриб
	Gribb[61] = SetPickupEx(1603, 2,-960.1893,-527.4004,25.9609); // гриб
	Gribb[62] = SetPickupEx(1603, 2,-960.4894,-524.3131,25.9536); // гриб
	Gribb[63] = SetPickupEx(1603, 2,-960.2265,-530.4597,25.9609); // гриб
	Gribb[64] = SetPickupEx(1603, 2,-959.9890,-534.2108,25.9609); // гриб
	Gribb[65] = SetPickupEx(1603, 2,-1156.2784,-568.8078,31.6953); // гриб
	Gribb[66] = SetPickupEx(1603, 2,-2001.1237,1100.9250,53.2891); // гриб
	Gribb[67] = SetPickupEx(1603, 2,-2097.6895,999.2496,68.6629); // гриб
	Gribb[68] = SetPickupEx(1603, 2,-2310.3076,1226.1506,38.6032); // гриб
	Gribb[69] = SetPickupEx(1603, 2,-2494.4038,1262.5997,30.8725); // гриб
	Gribb[70] = SetPickupEx(1603, 2,-2763.6106,2245.3145,72.8797); // гриб
	Gribb[71] = SetPickupEx(1603, 2,-2770.7556,2229.0144,78.1315); // гриб
	Gribb[72] = SetPickupEx(1603, 2,-2812.6680,2305.1401,89.2030); // гриб
	Gribb[73] = SetPickupEx(1603, 2,-2817.2490,2401.6272,103.9846); // гриб
	Gribb[74] = SetPickupEx(1603, 2,-2812.8237,2513.0842,115.7776); // гриб
	Gribb[75] = SetPickupEx(1603, 2,-2701.0725,2705.9910,104.4801); // гриб
	Gribb[76] = SetPickupEx(1603, 2,-2596.4209,2723.8613,92.5703); // гриб
	Gribb[77] = SetPickupEx(1603, 2,-2494.5605,2712.9219,87.3680); // гриб
	Gribb[78] = SetPickupEx(1603, 2,-2394.2227,2709.9497,79.8139); // гриб
	Gribb[79] = SetPickupEx(1603, 2,-2374.3442,2483.8066,7.4035); // гриб
	Gribb[80] = SetPickupEx(1603, 2,-2446.5996,2405.6804,14.0091); // гриб
	Gribb[81] = SetPickupEx(1603, 2,-1577.2052,598.0028,8.2881); // гриб
	Gribb[82] = SetPickupEx(1603, 2,-1651.0817,378.1865,7.1875); // гриб
	Gribb[83] = SetPickupEx(1603, 2,-1830.4517,-1063.4424,59.3774); // гриб
	Gribb[84] = SetPickupEx(1603, 2,-1666.9426,-1188.2601,70.2212); // гриб
	Gribb[85] = SetPickupEx(1603, 2,-1589.8344,-1354.8910,49.1934); // гриб
	Gribb[86] = SetPickupEx(1603, 2,-1590.6637,-1358.2773,48.9742); // гриб
	Gribb[87] = SetPickupEx(1603, 2,-1586.8938,-1360.8566,49.1557); // гриб
	Gribb[88] = SetPickupEx(1603, 2,-1589.2026,-1350.0601,49.4420); // гриб
	Gribb[89] = SetPickupEx(1603, 2,-1583.5529,-1345.4556,49.9615); // гриб
	Gribb[90] = SetPickupEx(1603, 2,-1605.7303,-1348.4092,48.5156); // гриб
	Gribb[91] = SetPickupEx(1603, 2,-1523.7123,-1529.4391,38.0784); // гриб
	Gribb[92] = SetPickupEx(1603, 2,-2022.1582,-1865.2584,46.9355); // гриб
	Gribb[93] = SetPickupEx(1603, 2,-2265.3816,-2176.2122,35.8124); // грибгриб
	Gribb[94] = SetPickupEx(1603, 2,-2304.9014,-2215.5938,27.8517); // гриб
	Gribb[95] = SetPickupEx(1603, 2,-2342.1433,-2281.6294,19.3744); // гриб
	Gribb[96] = SetPickupEx(1603, 2,-2402.8459,-2380.4077,25.2372); // гриб
	Gribb[97] = SetPickupEx(1603, 2,-2313.4932,-2487.4343,26.3837); // гриб
	Gribb[98] = SetPickupEx(1603, 2,-2168.1919,-2485.4460,30.9716); // гриб
	Gribb[99] = SetPickupEx(1603, 2,-1912.0115,-2481.5762,31.5543); // гриб
	Gribb[100] = SetPickupEx(1603, 2,-1800.2501,-2441.1323,23.2183); // гриб
	Gribb[101] = SetPickupEx(1603, 2,-1578.4258,-2584.7219,36.2463); // гриб
	Gribb[102] = SetPickupEx(1603, 2,-1513.5410,-2668.0273,57.1113); // гриб
	Gribb[103] = SetPickupEx(1603, 2,-1405.9407,-2680.9951,71.6945); // гриб
	Gribb[104] = SetPickupEx(1603, 2,-1235.4177,-2692.0947,33.7634); // гриб
	Gribb[105] = SetPickupEx(1603, 2,-1121.8243,-2673.6692,24.3401); // гриб
	Gribb[106] = SetPickupEx(1603, 2,-906.2039,-2639.0376,96.2026); // гриб
	Gribb[107] = SetPickupEx(1603, 2,-816.4166,-2604.4084,88.4525); // гриб
	Gribb[108] = SetPickupEx(1603, 2,-651.0701,-2567.5120,66.6344); // гриб
	Gribb[109] = SetPickupEx(1603, 2,-562.8860,-2508.2971,72.3594); // гриб
	Gribb[110] = SetPickupEx(1603, 2,-613.4986,-2471.6025,51.3335); // гриб
	Gribb[111] = SetPickupEx(1603, 2,-644.3444,-2399.6804,33.0600); // гриб
	Gribb[112] = SetPickupEx(1603, 2,-634.4722,-2251.3743,23.4546); // гриб
	Gribb[113] = SetPickupEx(1603, 2,-620.9742,-2212.2234,22.4436); // гриб
	Gribb[114] = SetPickupEx(1603, 2,-588.6625,-2207.4114,29.5228); // гриб
	Gribb[115] = SetPickupEx(1603, 2,-563.0853,-2195.2778,39.9875); // гриб
	Gribb[116] = SetPickupEx(1603, 2,-653.4344,-2176.2383,18.4148); // гриб
	Gribb[117] = SetPickupEx(1603, 2,-684.7582,-2153.3953,24.0302); // гриб
	Gribb[118] = SetPickupEx(1603, 2,-708.1529,-2161.4941,21.9770); // гриб
	Gribb[119] = SetPickupEx(1603, 2,-799.1942,-2071.5979,25.0910); // гриб

	Gribb[120] = SetPickupEx(1603, 2,-981.6686,-1737.8022,77.4927); // гриб
	Gribb[121] = SetPickupEx(1603, 2,-568.4184,-2001.5415,47.9738); // гриб
	Gribb[122] = SetPickupEx(1603, 2,273.7918,-662.8467,5.4138); // гриб
	Gribb[123] = SetPickupEx(1603, 2,472.6691,-532.4324,41.8585); // гриб
	Gribb[124] = SetPickupEx(1603, 2,-630.3486,-1404.0731,18.1328); // гриб
	Gribb[125] = SetPickupEx(1603, 2,-382.7001,-1737.0554,12.2355); // гриб
	Gribb[126] = SetPickupEx(1603, 2,-308.5620,-2044.9047,26.6413); // гриб
	Gribb[127] = SetPickupEx(1603, 2,-834.0952,-2305.2205,26.9752); // гриб
	Gribb[128] = SetPickupEx(1603, 2,-312.5072,-1968.3159,21.0904); // гриб
	Gribb[129] = SetPickupEx(1603, 2,-305.8598,-2061.5278,30.1516); // гриб
	Gribb[130] = SetPickupEx(1603, 2,-384.8099,-2055.8118,34.5996); // гриб
	Gribb[131] = SetPickupEx(1603, 2,-385.4564,-2056.3611,34.9362); // гриб
	Gribb[132] = SetPickupEx(1603, 2,-407.1934,-1967.1241,23.2379); // гриб
	Gribb[133] = SetPickupEx(1603, 2,-505.7665,-2004.7998,48.6457); // гриб
	Gribb[134] = SetPickupEx(1603, 2,-505.7665,-2004.7998,48.6457); // гриб
	Gribb[135] = SetPickupEx(1603, 2,-586.6637,-1994.5146,44.7200); // гриб
	Gribb[136] = SetPickupEx(1603, 2,-596.7676,-1953.9158,37.1502); // гриб
	Gribb[137] = SetPickupEx(1603, 2,-651.5683,-1915.3408,12.0861); // гриб
	Gribb[138] = SetPickupEx(1603, 2,-692.4496,-2012.7374,21.0567); // гриб

	Gribb[139] = SetPickupEx(1603, 2,-410.3562,-1517.8588,23.2737);
	Gribb[140] = SetPickupEx(1603, 2,-453.7148,-1528.2802,16.2438);
	Gribb[141] = SetPickupEx(1603, 2,-448.8864,-1499.4187,18.6492);
	Gribb[142] = SetPickupEx(1603, 2,-489.5084,-1430.3676,14.7027);
	Gribb[143] = SetPickupEx(1603, 2,-609.5909,-1423.5277,15.2368);
	Gribb[144] = SetPickupEx(1603, 2,-602.0017,-1489.6946,13.9490);
	Gribb[145] = SetPickupEx(1603, 2,-608.4830,-1469.3499,13.9078);
	Gribb[146] = SetPickupEx(1603, 2,-614.8417,-1347.9437,19.3655);

	print("  vw_mushroomer 1.0 By: DANGER1979");
	print("_____________________________________________");
	print(" ");
}


stock mushroomer_OnPlayerPickUp(playerid, pickupid)
{
//для грибников
	if(pickupid >= Gribb[0] && pickupid <= Gribb[sizeof(Gribb)-1] &&
		 IsPlayerInRangeOfPoint(playerid, 2.1, Pickups[pickupid][p_x],Pickups[pickupid][p_y],Pickups[pickupid][p_z]))
    {
		if(PlayerInfo[playerid][pInt] != 0) return 1;
		if(PlayerInfo[playerid][pVirtual] != 0) return 1;
		if(PlayerInfo[playerid][pLocal] != FREEROAM) return 1;
        //У вас нет корзинки для грибов. Её можно получить в пункте приёма грибов.

	    //format(strings, sizeof(strings), "   Вы достаете корзинку и аккуратно кладёте Гриб в корзинку.", PlayerName(playerid)); //сообщение
	 	SetPlayerChatBubble(playerid, "Срезал Гриб и положил в корзинку.",COLOR_PURPLE,30.0,3000);
	    //GivePVarInt(playerid, "GribsCounter", +1);
	    PlayerInfo[playerid][pMushroom] ++;
	    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 6.1, 0, 0, 0, 0, 0,1);
	    format(strings,sizeof(strings),"Грибов собрано: {ffffff}%d. Вы можете продать их в Пункте приёма грибов (USE: /gps 1033)", PlayerInfo[playerid][pMushroom]);
	    SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	    SendClientMessage(playerid, COLOR_YELLOW, "Чтобы посмотреть сколько грибов у вас в корзине (USE: /mushrooms)");
		
    }
	return 1;
}


stock mushroomer_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
		#pragma unused listitem
		//#pragma unused inputtext
		if(dialogid != MUSHROOMER_DIALOG) return 1;
//dialogid == 83
	    if(response)
	    {
	        if(!strlen(inputtext))
	        {// && PlayerInfo[playerid][pMushroom] > 0
	            ShowPlayerDialogGap(playerid, MUSHROOMER_DIALOG, DIALOG_STYLE_INPUT,"Пункт приема грибов","Введите количество Грибов, \nкоторое хотите Сдать \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
	            return 1;
            }
	        new Gribochek = strval(inputtext);
			if(Gribochek < 1)
	        {// && PlayerInfo[playerid][pMushroom] > 0
	            ShowPlayerDialogGap(playerid, MUSHROOMER_DIALOG, DIALOG_STYLE_INPUT,"Пункт приема грибов","Введите количество Грибов не менее 1, \nкоторое хотите Сдать \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
	            return 1;
            }
			if(Gribochek > PlayerInfo[playerid][pMushroom])
			{
				SendClientMessage(playerid, COLOR_GREY, "У вас нет столько грибов!");
	            ShowPlayerDialogGap(playerid, MUSHROOMER_DIALOG, DIALOG_STYLE_INPUT,"Пункт приема грибов","Введите количество Грибов не менее 1, \nкоторое хотите Сдать \n\n\t{8CAA63}По окончанию ввода нажмите OK.", "OK", "Cancel");
				return 1;
			}
			new Float: price = compcost*(100+SBizInfo[54][sbBuyProd])/100.0;
   			new money = floatround(Gribochek*price, floatround_floor);
			if(SBizInfo[54][sbTill] > money)
			{
				SBizInfo[54][sbProducts] += Gribochek;
				SBizInfo[54][sbTill] -= money;
				SBizInfo[54][sbImport] += money;

				//CallLocalFunction("GivePlayerMoneyH", "iii", 200+56, playerid, Gribochek*100);
				GivePlayerMoneyB(fsbiz+54, playerid, money); ///замените на свою выдачу денег
				PlayerInfo[playerid][pMushroom] -= Gribochek;

				//SetPlayerChatBubble(playerid, "Сдает Грибы",COLOR_PURPLE,30.0,10000);

				format(strings, sizeof(strings), "Вы сдали {FFFFFF}%d{0080FF} Грибов и получили {33AA33}$%d{0080FF}. (USE: /mushrooms)", Gribochek, money); //сообщение
				SendClientMessage(playerid, COLOR_LIGHTBLUE, strings);
	        }
	        else
	        {
	      		SendClientMessage(playerid, COLOR_GREY, "   Извените, в кассе нет больше денег.");
	        }
   		}
   		return 1;
}

