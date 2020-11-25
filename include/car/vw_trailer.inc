//ф-ии дл€ работы с прицепами
new gTrailerAttached[MAX_PLAYERS];
new IsTrailerAttach[MAX_VEHICLES+1];//пл индексу прицепа записывает к какой тачке он прицеплен

stock trailer_OnPlayerKeyState(playerid)
{
	//if(gLoading[playerid]) { return 1; }
	//if(gUnLoading[playerid]) { return 1; }
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) { return 1; }
	if(!IsInHardTruck(nCarID[playerid]))
	{
		SendClientMessage(playerid, COLOR_GREY, "   ƒанное транспортное средство не оборудовано прицепным устройством !");
		return 1;
	}
	if(GetVehicleSpeed(nCarID[playerid]) > 10)
	{
		SendClientMessage(playerid, COLOR_GREY, "Ќельз€ прицепл€ть/отцепл€ть прицеп во врем€ движени€ !");
 		return 1;
    }
//nTrailerID[playerid] = GetVehicleTrailer(nCarID[playerid]);//ѕолучить ID трейлера прикреплЄнного к машине.
//nTrailerModel[playerid] = GetVehicleModel(nTrailerID[playerid]);//”знает ID модели данного трейлера прикреплЄнного к машине.
	if(!IsTrailerAttachedToVehicle(nCarID[playerid]))
	{
		new trailerid = 0;  new Float:vX,Float:vY,Float:vZ;
		new vid = 1;
		for(new v=0; v!=-1; v=StreamedVehicle[playerid][v])	{
			if(StreamedVehicle[playerid][v] == -1) continue;
			vid = StreamedVehicle[playerid][v];

			if(vid <= 0) continue;
			if(!IsValidVehicle(vid)) continue;//if(nCarModel[playerid] < 400) continue;
			new modelid = VehInfo[vid][cModel];//GetVehicleModel(carid)
			if(VehicleArray[modelid-400][Category] != Trailers) continue;
			if(IsTrailerAttach[vid]) continue;//пропускаем уже прицепленные
			if(VehInfo[vid][cVirt] != 0) continue;
			GetVehicleModelInfo(modelid, VEHICLE_MODEL_INFO_SIZE, vX, vY, vZ);
			if(GetDistanceToCar(playerid, vid) >= (10.0+vY/2.0)) continue;//vY = 13.5299
			trailerid = vid;
			break;
		}
		if(!trailerid)
		{   //чтобы не мог пассажир отсоеденить прицеп
			format(strings, sizeof(strings), "  Ќет прицепов в радиусе %.4f м!", (10.0+vY/2.0));
			SendClientMessage(playerid, COLOR_GREY, strings);
			return 1;
		}
		AttachTrailerToVehicleEx(trailerid, nCarID[playerid]);
		//SendClientMessage(playerid, COLOR_GREY, "AttachTrailerToVehicleEx");
		gTrailerAttached[playerid] = 1;
		//nTrailerID[playerid] = trailerid;
	}
	else
	{
		DetachTrailerFromVehicleEx(nCarID[playerid]);
		//SendClientMessage(playerid, COLOR_GREY, "DetachTrailerFromVehicleEx");
		gTrailerAttached[playerid] = 0;
		//nTrailerID[playerid] = 0;
		//nTrailerModel[playerid] = 0;
	}
	return 1;
}


stock AttachTrailerToVehicleEx(trailerid, vehicleid)
{
	AttachTrailerToVehicle(trailerid, vehicleid);
	IsTrailerAttach[trailerid] = vehicleid;
}
stock DetachTrailerFromVehicleEx(vehicleid)
{
	IsTrailerAttach[GetVehicleTrailer(vehicleid)] = 0;
	DetachTrailerFromVehicle(vehicleid);
}

stock IsInHardTruck(vehicleid)//возвращает 1 если это грузовик, которым может т€гать прицеп
{
	new carmodelid = VehInfo[vehicleid][cModel];//GetVehicleModel(vehicleid);//”знает ID модели данного транспортного средства.
	if(carmodelid==403 || carmodelid==485 || carmodelid==514 || carmodelid==515 || carmodelid==531 || carmodelid==552 || carmodelid==583) { return 1; }
	return 0;
}
