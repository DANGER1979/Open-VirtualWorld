stock prints_OnFilterScriptInit()//��� �������� ��������
{
	print("========================================================================");
	print("                 Copyright DANGER_Hidden  � 2009 - 2029                 ");
	print("========================================================================");
	print("�������� ������� ��������� ������, ����� ��������� ��������� �������, ");
	print("��� ������ DANGER1979, �������� �� ����� ���������������");
	print("� ������������ � ������� �� ��������� �����");
	print("��������� ������ ������ (����� �����) �� ������������:");
	print("1. �� ����������� ����� ����.");
	print("2. �� ��������� ����� �� �������� ������.");
	print("3. �� ��������/������� ��������� � ���� �������.");
	print("4. ��� ������������ ��� � ���� ����������� ��������� DANGER1979@mail.ru.");
	//printf("5. ��� ������������ ������ � ���� ��������� ������ � ������� http://eragon-studio.3dn.ru");
	//printf("6. C����� ������ ����� �� �������� ������.");
	print("��������������� �� ����������� ���������� ������.");
	print("�� ����������� ��� �� ���� ����� � ����.");
	print("�� ������ �������� � ����� �������� �� DANGER1979@mail.ru.");
	print("========================================================================");
	printf("MAX_DIALOGS = %d, LOAD = %d", 32768, DIALOG100);
	printf("MAX_PICKUPS = %d, LOAD = %d", MAX_PICKUPS, PickupCounter);//��� �������� �����������
	printf("MAX_VEHICLES = %d[%d], LOAD = %d[%d]", MAX_VEHICLES, GetVehiclePoolSize(), LoadCarCounter, VehiclesCounter);//������ ���� ��������������
	printf("Vehicle Models Max = Unlimited, LOAD = %d", VehiclesModelsCounter);
	printf("MAX_OBJECTS = %d, ADD_OBJECTS = %d, CreateObjectCounter = %d", MAX_OBJECTS, MAX_STREAM_OBJECTS, CreateObjectCounter);//+MAX_ROADBLOCK+MAX_SPIKESTRIPS
	printf("STREAM: LoadDynamicObjects: %d, LoadDynamicActors: %d", CountDynamicObjects(), ActorCounter);
	printf("STREAM: LoadDynamicPickups: %d LoadDynamicLabels: %d LoadDynamicMapIcons: %d", CountDynamicPickups(), CountDynamic3DTextLabels(), CountDynamicMapIcons());
	printf("MAX_GANG_ZONES = %d, LOAD = %d", MAX_GANG_ZONES, MAX_TURFS);
	printf("MAX_ICONS = %d, MAX_STREAM_ICONS = %d, MAX_HOUSE_ICONS = %d", MAX_PLAYER_ICONS+1, MAX_STREAM_ICONS, MAX_HOUSE);
	printf("MAX_MENUS = %d, LOAD = %d", MAX_MENUS, MenuCounter);//MAX_MENU
	printf("MAX_TEXT_DRAWS = %d, LOAD = %d", MAX_TEXT_DRAWS, TEXT_DRAWS_COUNTER);
	printf("MAX_3DTEXT_GLOBAL = %d, LOAD = %d", MAX_3DTEXT_GLOBAL, Counter3DText);
	print("========================================================================");
}


