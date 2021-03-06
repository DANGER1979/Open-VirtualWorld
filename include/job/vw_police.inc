new rbCounter = 0;//������� ����������� ������

enum pddinfo
{
	Article,//������
	Part,//�����
	Title[64],//��������
	Commentary[128],//���������, �� ������� ���������� ���������������� ���������
	Jailed,//���� � ���� ���������: 1 - �������������� ��� �����, 2 - �����, 3 - ����� ���� ������� 4 - ����� � ��������
	Bail,//����� - ���-�� ������� ������� /������� ��������� ����� ������� //ticket = PDD[i][Bail]*1*360;//3600
	Period//����� ������ ����
};
//����� 18. ���������������� �������������� ������ ������������ �������� � ������������ ����������
new PDD[47][pddinfo] = {
{1,1, "���������� ������������ ������������ ������������", "����� �������� �����������, ��������� ������ ��� ���� ��������",2,6,0},
{2,2, "��������� ������ ������������", "�������� ��� ������������ ������������� ��������",2,5,0},//2,15,0},
{3,5, "��������� ������, �������������� ������������ ��������", "������ �� ��������������� ����� � ��������������� ����� ",2,2,0},
{4,1, "��������� ������ ����������� ���������������� ��", "������ �� ����� ������",2,3,0},
{5,4, "��������� ������ ������������ �������", "����������� ������ ��� ������ �� ���������� ���������",1,2,0},
{10,21, "��������� ������ ��������� ������", "� ����������� ����� ��� �� 15 %%",2,1,0},//1-3
{11,77, "��������� ����������� ������������", "��������� � �������������� ����",4,1,3},
{12,1, "H�������� ������ ������������ ��", "���������� ��, ������� ������������� ��� ������������ ���. �������������",1,1,0},//1-3
{12,79, "��������� ������������ ������� ��������� �����", "������������ ������������� ���������� ����������� �������������",3,1,3},
{12,80, "��������� ������ ������������ �������� �� ��������� ��", "������������ ������������� ���������� �� � ������������",3,1,3},
{13,1, "���������� ������������� �������� ��������", "�� 10-20 ��/�.",1,1,0},
{13,2, "���������� ������������� �������� ��������", "�� 20-30 ��/�.",2,1,0},//1-2
{13,3, "���������� ������������� �������� ��������", "�� 30 ��/�.",2,2,0},//2-10
{13,4, "���������� ������������� �������� ��������", "����������� �������� � ������� 1 ���� ����� ��������� ���������",3,4,1},//4-15
{14,1, "������������ �����, ����������� �� ����������", "�������� �������������, ��������� ������ ��������� ����� ��� ������",1,1,0},//1-5
{14,3, "������������ �����, ����������� �� ����������", "������ ������������ ��, ������, ������ �� ������ ���������� ��������",2,5,0},//5-10
{14,4, "������������ ����������", "������, ��������, ������������, ����������, ��������������, ���������������� ������������",1,1,0},//1-5
{14,5, "������������ �����, ����������� �� ����������", "������ �� ����������� ������������������ ������� �� ������������ ����������",2,2,1},//2-10
{14,6, "������������ �����, ����������� �� ����������", "������ �������� �� ��������������",1,3,0},//1-4
{14,7, "������������ ���������� ������", "� ����� ����� ���� �������� �� ���������� ��������, ��������, ��������� ��� �������",1,1,0},//1-3
{14,8, "������������ �����, ����������� �� ����������", "������ ������� � ��������� ������������ ��, ��������� ������ ������������ ��������",3,5,1},//5-10
{14,9, "������������ �����, ����������� �� ����������", "��������� �������� ��������� ����������",3,10,2},//10-20
{14,10, "������������ �����, ����������� �� ����������", "����������� �����- � ���������� ������ �� ����� ��������",1,1,0},//1-2
{15,1, "H�������� �����, ����������� ��, ������", "������� ���������������� ��������",2,2,0},//2-4
{15,2, "H�������� �����, ����������� ��, ������", "������� ���������������� �������� ����������� ��������",2,4,0},//4-20
{16,1, "���������� ��", "����� ����������� � ��������� ��������� ��� ��� ������������ ������������� �������",4,15,3},//15-35
{16,2, "���������� ��", "� ��������� ��������� �� ������� ����� ���������� ��",4,25,3},//25-45
{17,1, "��������� ���", "��������� ���������� ������� ��������� ����������� ���� ����������� ��, �����, �������� � ��. ����������",3,10,2},//10-30
{17,2, "��������� ��� �����, ����������� ��", "����������� �����, �� ������� ����� ���������� ���� ��",4,20,2},//20-50
{17,3, "��������� ���", "��������� ���������� ������� ��������� ����������� ���� ������",4,10,5},//10-30
{17,4, "��������� ��� �����, ����������� ��", "���������� ��������� ����� ���",3,20,3},//20-50
{18,1, "���������� ��", "����� �� ������� ����������, ���� ����� �� ������������",3,10,0},//��������������� ����� �� ���������� �� ������ ���������
{19,1, "���� ��", "����������� ��� ������� ��� ��������� ��� � ��������, ������� �� ������ ��� ����� � ��������.",3,20,2},
{19,2, "���� ��", "����������� ������� ���, ��������� ���������� ������ � ����� ������� �������",4,20,3},
{20,1, "���������� ��", "��� ���������� �������� ������������� �����������",2,2,0},//2-5
{20,2, "���������� ��", "��� ���������� �������� ����������� � ������ ���������� ���",2,5,0},//5-10
{21,1, "������������ �����, ����������� ��", "���������� ��������� ������� �� ��������� ��",2,1,0},//1,1,0
{21,2, "������������ �����, ����������� ��", "������������� ���������� ��������� ������� �� ��������� ��",3,1,1},//1,1,0
{22,1, "��������� �����, ����������� ��", "������ ��������� ��� ������� ������������� ��������",1,1,0},
{23,1, "H�������� ��� ���������� ��������� ��������", "����������� ����������� ��� �����, ����������� � �������� � �� ����������� ��",1,1,0},
//{24,1, "������ � ������������ ��, �������� �������������", "��� ������� ������� ��� ������������ ���������, ��� ������������������ ��� ���������������� ����������, ��� �� ������������������� � ������������� �������, ��� �� ���������� ���������������� ������������ �������",2,4-6,0},
{26,1, "��������� ������ ����� � ������", "��������� �������������� ������ ����� � ������",2,4,0},
{27,1, "H�������� �����, ����������� ��, ������", "������� ���� ���������, ��������� �������� ��",1,1,0},
{29,1, "H�������� �����, ����������� ��, ������", "������������ ��� ��������� ������� ������",2,2,0},//2-10
{35,1, "�����������, �������������, �����������", "����������, �.�. ��������, ��. ���������� ��� ������� �������������",2,2,0},//2-5
{36,1, "H�������� ��-�� ������� ����������� ��������", "���������� ��� �������, ������������� � ����������",2,2,0},//2-10
{36,2, "H�������� ��-�� ������� ����������� ��������", "���������� �� ������� ������ ����������� ���������",2,2,0},//2-5
{36,4, "H�������� ��-�� ������� ����������� ��������", "�����, ����� � ��������������� ��� �������������� ������",2,1,0}
};

new DOTL[23][18] = {//��� PenalCode - �� ��
{1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2},//0. �� 2 �����
{1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3},//1. �� 3 �����
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5},//2. �� 5 �����
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6},//3. �� 6 �����
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7},//4. �� 7 �����
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10},//5. 2-10 �����
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 7, 8, 9, 10},//6. 3-10 �����
{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 7, 8, 9, 10},//7. 5-10 �����
{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 8, 9, 10},//8. 6-10 �����
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 5},//9. 2-5 �����
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 5, 6},//10. 2-6 �����
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 4, 5, 6, 7},//11. 2-7 �����
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 7},//12. 3-7 �����
{5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7},//13. 5�7 �����
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 7, 8},//14. 3-8 ����
{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 6, 7, 8, 9, 10, 11, 12},//15. 4-12 �����
{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 7, 8, 9, 10, 11, 12},//16. 5-12 �����
{5, 5, 5, 5, 5, 5, 5, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},//17. 5-15 �����
{6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},//18. 6-15 �����
{7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 10, 11, 12, 13},//19. 8-13 �����
{7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 10, 11, 12, 13, 14, 15},//20. 8-15 �����
{7, 8, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 12, 13, 14, 15},//21. 10-15 �����
{8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}//22. 8-25 �����
};
enum punishmentinfo
{
	Article,//����� ������
	Part,//����� �����
	Title[64],//�������� ������/�����
	Commentary[128],//����������/���������
	Bail,//����� ��� ����� - ���-�� ������� �������
	Jailed,//3 - ������ ���������������� ����������, 10 - �������������� �������
	Period,//����� ������ �� ������� - ����� ���������� �� ������� DOTL ������
	Wanted//������� ��������� ����� ������� //1-6 - �����, 7-14 - �������, 15-25 - ������
};
//1. ����������:
//1.1. ���������������� ��������������� ���������� ��� �� ��������� ��������������:
new PenalCode[81][punishmentinfo] = {
{83,1, "���� ������������� �� ���������������, ���� �����", "1 �. ��� ������������ �� ��������������� ������� ��������� (2 �. ��� ����)",0,0,0,0},
{83,2, "���� ������������� �� ��������� ���������������, ���� �������", "�� 1 �� 3 �. ��� ���������� ����� ������� ������������ (5 �. ��� ����)",0,0,0,0},
{83,3, "���� ������������� �� ��������� ���������������, ���� �������", "�� 3 �� 5 �. ��� ���������� ������� ������������ (10 �. ��� ����)",0,0,0,0},
{86,1, "����, ������� ����������� ������������ ������������", "� ���������������� ���������������: ����� 15 �����",1,3,0,0},
{90,1, "�������-��������� ������������ �� ���������", "��� ��� ��������� ���������, ������������ ����������� ����.",0,0,0,0},
{90,2, "�������-��������� ������������ �� ���������", "����� ������� 1/2 �����, �� ������������, �� �������������� ������� ���������",0,0,0,0},
{90,3, "�������-��������� ������������ �� ���������", "����� ������� 2/3 �����, �� ������ ������������",0,0,0,0},
{90,4, "�������-��������� ������������ �� ���������", "����� ������� 3/4 �����, �� ����� ������ ������������",0,0,0,0},
{118,1, "������������ �� ��������� ���������������", "����, ������� ����������� ������������ �� 18 ���, �� �������������� ������� ���������",0,0,0,0},
//------------------------------------------------------------------------------
{139,1, "��������", "���������� �������������� ������� ����� ������� ��������",15,10,18,25},
{139,2, "��������", "�������� 2-� ��� ����� ���, ���� ����������� ������� ���",20,10,20,30},
{139,3, "��������", "�������� ��� ���������� ���, ����������� ��� ���������� ����, ������������ ������������",3,10,1,7},
{139,4, "��������", "�������� ��� ���������� �������� ����������� �������",4,3,0,14},//",4,3,0,14
{139,5, "��������", "�������� ���������� ������� ���������� ���",25,10,19,35},
{144,1, "���������� ������ �� ��������������", "���������� ������� �����, ��������� ������",3,10,1,15},
{144,2, "���������� ������ �� ��������������", "���� ��� ����� �����",5,10,2,20},
{149,1, "���������� ���������� ����� ������� ��������� �����������", "���������� ������������ �������� ���� ������ ����������������",3,3,1,5},
{149,2, "���������� ���������� ����� ������� ��������� �����������", "����������� ������� ��� ���� ��������, ������� �������� ������� ��� ���������",5,10,2,6},
{150,1, "���������� ���������� ������� ��������� �����������", "��� ���������� �������� ����������� �������",5,3,1,10},
{150,2, "���������� ���������� ������� ��������� �����������", "��������� � ����� � ��������������� �������������� ����������",7,10,2,14},
{161,1, "���������� ������ ��������", "������������ ���������� ���������������� ������������ ����������� ����������",3,3,0,2},//",3,3,0,2
{182,1, "��������� ��������", "������ ���������",5,10,13,7},
{182,2, "��������� ��������", "����������� ������� ��� c ����������� ������ � ��������� ���� ��� ����� ���",7,10,17,15},
{182,3, "��������� ��������", "������������ ������ ������������ ��� ���� ������ �����������",8,10,21,20},
{188,1, "�������. �����������. �������� ������ �����", "��������������� �������� ������, ��������� ������ ���� ����������, ���������� �������� ����� � �����������",2,3,0,2},//",2,3,0,2
{188,2, "�������. �����������. �������� ������ �����", "����������� � ��������� �����������",3,3,0,7},//",3,3,0,7
{188,3, "�������. �����������. �������� ������ �����", "c���������� � ���������� � ������ ��� ����� ������ ������������",3,10,1,15},
{202,1, "��������� �������� �������� �������", "���������� ��������� � ������ ������� ���� �����������",1,3,0,2},//",1,3,0,2
{202,2, "��������� �������� �������� �������", "����������� ����������� ����� � �������������� ����� ��������� ����������",1,3,0,2},//",1,3,0,2
{205,1, "�����. ������. ����", "����������� ��� ������� ��� ��������� ��� � ��������, ������� �� ������ ��� ����� � ��������.",2,10,1,3},
{205,2, "�����. ������. ����", "����������� ������� ���, ��������� ���������� ������ � ����� ������� �������",3,10,11,7},
{205,3, "�����. ������. ����", "��������� ������ ��������",6,10,7,15},//������.
{209,1, "�������������", "���������� ���������� ����� ������ ��� ��������������� ��������",5,10,1,3},
{209,2, "�������������", "����������� �������� ���� ������� ���, � ������� �������",10,10,20,7},
{209,3, "�������������", "����������� �������������� ������� ���, ���� � ����� ������� �������",12,10,6,15},
{285,1, "���������", "�������� ����������� ������������ ������������",5,3,0,2},//",5,3,0,2
{285,2, "���������", "������� � ���������� ����������� � ����� ���� �����",4,3,0,2},//",4,3,0,2
{293,1, "�������� ����������", "�������, �������, ����������� ���������, ����������� ������������� �������������� ������",6,10,17,15},
{293,2, "�������� ����������", "����������� �������� ���� ������� ���",4,10,14,8},
{295,1, "���������� �������� � ��������� �������������� ������", "���������� ������������, ������������, �������� �� ��������, ����, �������� ��� �������",3,10,4,6},
{295,2, "���������� �������� � ��������� �������������� ������", "����������� �������� ���� ������� ��� �� ���������������� �������",3,10,5,14},
{295,3, "���������� �������� � ��������� �������������� ������", "����������� �������������� �������",4,10,15,20},
{317,1, "��������� ���(�������) ��� ������������ ��", "��������� ���������� ������ ���� ����� ������� ��������� �����������",1,3,0,2},//",1,3,0,2
{317,2, "��������� ���(�������) ��� ������������ ��", "��������� ������ �������� ���� ���������� ������� ��������� �����������",5,10,5,7},
{317,3, "��������� ���(�������) ��� ������������ ��", "��������� ������ ���� ��� ����� ���, ",8,10,15,20},
{317,4, "��������� ���(�������) ��� ������������ ��", "���������� ������������ � ��������� ���������",1,3,0,15},//",1,3,0,15
{328,1, "���������� ������ ������������� �������", "�������� ������������� �������",2,3,0,2},//",2,3,0,2
{328,2, "���������� ������ ������������� �������", "������������ � ����� �����, ���� ���� ������������� �������",3,10,0,14},
{328,3, "���������� ������ ������������� �������", "����������� ������� ���, � ������� �������, � ����� ���������� �����������",4,10,19,20},
{339,1, "�����������", "�������� ���������� ������������ ������� ��� ���������� ���������� � ��������",2,10,1,3},
{339,2, "�����������", "����������� ������� ��� ��� �������� �� �������������� ������ � ����������������� �����",4,10,3,5},
{339,3, "�����������", "����������� � ����������� ������ ��� ���������� �������� �����������",6,10,6,10},
{363,1, "������������� ����, ���������� ������������ �������", "��� ���������� �� ������������ �� ������ ������������� �������",2,10,1,3},
{363,2, "������������� ����, ���������� ������������ �������", "����������� � ����������� ������� ��� � ������� ��� ����������",4,10,2,5},// � ���������� ���� ���������� ��������
{369,1, "����������� ������������� ������", "��������� ����������� � ����� � ����������� �� ��������� ������������",2,10,1,3},
{383,1, "�������������", "����������� ������������� ������ ��������������� ��� ��������������� �����",3,3,0,2},//",3,3,0,2
{397,1, "�������� ���������� ����������", "���������� ��� ������, ���� ���������� ��� �������",2,10,1,3},
{397,2, "�������� ���������� ����������", "��������� ������ ����������� (������ ��������)",3,10,11,7},
{402,1, "����� ���� ��������� �� ���� ���������", "����� ���� ��������� ��������� ��� ������������ �� ���� ���������",2,3,0,2},
{413,1, "�����", "����� �� ��������������� ����������, ��� ��-��� ������",12,10,1,3},//30000,10,1,3
{413,2, "�����", "����������� ������� ���, ���� � ����������� �������, �������� ��� ����� � ��������",17,10,11,7},//70000,10,11,7
{414,1, "��������� �� ������", "��������� �� ��������� ��������� � ���� ������� ������� ��� ������",2,10,1,2},
{418,1, "��������� �� ������ ������", "��������� �� ������ ������",2,10,1,6},//20000,3,0,2
{424,1, "��������������� �������. ���������� ������", "��������� ���������� ������ � ������� ������� ��� ������������� ����� ������������ ���������",2,10,1,3},
{424,2, "��������������� �������. ���������� ������", "����������� �� ��������� ��� ���� ������ ������������������ � ����������� ������ ",3,10,3,6},
{424,3, "��������������� �������. ���������� ������", "����������� ������������� ���������, ��������� ������ �����������, ����������� � ������� ����������",4,10,6,10},
{425,1, "����������� ������������ ����. ��������� ����������", "���������� ������������ ����������� ����� ��������, ���������������",3,10,1,3},//������� ��������� ������
{425,2, "����������� ������������ ����. ��������� ����������", "����������� ������������ ���� �� ��������� ��� ���� ������ ������������������",4,10,3,6},
{425,3, "����������� ������������ ����. ��������� ����������", "����������� ������������� ���������, ��������� ������ �����������",5,10,6,10},
{430,1, "��������� ������", "������������ ����� �������������� ���������",3,10,4,7},
{430,2, "��������� ������", "����������� ������� ��� �� ���������������� �������, ���� � ������� �������",4,10,8,10},
{430,3, "��������� ������", "����������� ����� ���������� ������������� ��������� � ����� ������� �������, �������������� �������",4,10,20,15},
{431,1, "���� ������", "���� ������",2,10,2,5},
{431,2, "���� ������", "�������� �� �������� ���������� �������� � ������� �������",4,10,11,7},
{438,1, "�������������. ������������ �������", "�������� ����� ���� ���� ���������� ����������� �������",2,10,1,2},
{438,2, "�������������. ������������ �������", "����������� ������� ��� � ������ ���������� ��������� ������ �����������",4,10,4,7},
{445,1, "������������", "������ � ���� ��� ������������ ������ (2-10 �����)",2,3,0,2},
{445,2, "������������", "����������� ���������� ����� ������, ������ � ���� ��� ������������ ������ (10-60 �����)",3,10,1,3},
{445,3, "������������", "����������� ���������� ����� ����",4,10,2,5},
{445,4, "������������", "����������� � ������ ����������",6,10,7,10},
{581,1, "�������������", "������ ���� ��� ��. ������ �������� ��� ����������� �� �� ����������",50,10,15,14}//50,10,15,14
};

stock police_OnGameModeInit()
{

	print("  vw_police 1.0 By: DANGER1979");
	print("_____________________________________________");
	print(" ");

}

stock police_OnPlayerConnect(playerid)
{
    //��������� ��������� ���
	RemoveBuildingForPlayer(playerid, 968, -2436.810, 495.468, 29.679, 0.250);
	RemoveBuildingForPlayer(playerid, 966, -2436.850, 495.453, 28.953, 0.250);
	RemoveBuildingForPlayer(playerid, 967, -2438.729, 495.007, 29.101, 0.250);
	RemoveBuildingForPlayer(playerid, 1622, -2447.010, 516.046, 32.648, 0.250);
}


stock police_OnPlayerExitedMenu(playerid, Menu:Current)
{
	if(Current == mPoliceDepartment)//��� �������� �������
	{
		HideMenuForPlayerEx(Current,playerid);
		TogglePlayerControllableEx(playerid, 1);
	}
}

stock police_OnPlayerSelectedMenuRow(playerid, row, Menu:Current)
{
	//new Menu:Current = GetPlayerMenu(playerid);//�������� ID ����
	if(Current != mPoliceDepartment) return 1;
	switch(row)
	{
		case 0://Wanted list
		{
			if(PlayerInfo[playerid][pMember] == DoD || IsACop(playerid))
			{   //���� ����� ������� ��� ���
				WantedList(playerid);
				TogglePlayerControllableEx(playerid, 1);
			}
			else
			{
				ShowMenuForPlayerEx(mPoliceDepartment, playerid);
				SendClientMessage(playerid, COLOR_GREY, "   �� �� ��� / FBI / National Guard !");
			}
		}
		case 1://Clear Wanted
		{
			//new member = PlayerInfo[playerid][pMember];
			new leader = PlayerInfo[playerid][pLeader];
			//new rank = PlayerInfo[playerid][pRank];
	 		if(IsACop(playerid) || leader == 5 || leader == 6)
			{
				TogglePlayerControllableEx(playerid, 1);
				ShowPlayerDialogEx(playerid, CLEARWANTED_DIALOG, DIALOG_STYLE_INPUT, "Clear Wanted", "������� ID ������ [playerid] \n��� ����� ����� [PartOfName]", "OK", "Cancel");
			}
			else
			{
				/*if(WantedLevel[playerid] >= 2)
				{
					SendClientMessage(playerid, COLOR_GREY, "   �� �������������� ��� ����� ������� ���������� � �� �� ������ ����� � ���� ������ !");
				}
				else if(WantedLevel[playerid] == 1)
				{*/   //��� ���������
				new ticket;
				if(PlayerInfo[playerid][pArticle] >= 1 && PlayerInfo[playerid][pArticle] <= 36)
				{
					for(new i=0; i<sizeof(PDD); i++)
					{
						if(PlayerInfo[playerid][pArticle] != PDD[i][Article]) continue;
						if(PlayerInfo[playerid][pPart] != PDD[i][Part]) continue;
		 				ticket = PDD[i][Bail]*WantedLevel[playerid]*ticket_rate;//3600
						break;
					}
				}
				else if(PlayerInfo[playerid][pArticle] >= 83)
				{
					for(new i=0; i<sizeof(PenalCode); i++)
					{
						if(PlayerInfo[playerid][pArticle] != PenalCode[i][Article]) continue;
						if(PlayerInfo[playerid][pPart] != PenalCode[i][Part]) continue;
						ticket = PenalCode[i][Bail]*WantedLevel[playerid]*ticket_rate;//3600
						break;
					}
				}
				else
				{
					if(WantedPoints[playerid] <= 0 && GaiWant[playerid] == 1) { ticket = 500; }//����� �� ��������� ���
					else if(WantedPoints[playerid] > 0) { ticket = WantedPoints[playerid]*500; }//5000 � ����������� �� ����� ������� ��������� �����
				}
				TicketMoney[playerid] = ticket;
		        if(GetPlayerMoneyH(playerid) > TicketMoney[playerid])
		        {
					GivePlayerMoneyH(ffamily+FBI, playerid, -TicketMoney[playerid]);
				}
		        else if(PlayerInfo[playerid][pBank] > TicketMoney[playerid])
		        {
					GivePlayerMoneyB(ffamily+FBI, playerid, -TicketMoney[playerid]);
				}
		        else
		        {
		            SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ��������� ���� �������� ����� !");
					return 1;
		        }
				PlayerInfo[playerid][pTicket] ++;

				if(ticket == 500) FamilyInfo[DoT][fBank] += TicketMoney[playerid];
				else FamilyInfo[FBI][fBank] += TicketMoney[playerid];

				format(strings, sizeof(strings), "B� �������� ����� � ������� $%d. ������� ������������ ��� %d.", TicketMoney[playerid], LevelToCriminality);
				SendClientMessage(playerid, COLOR_BLUEGREY,strings);// ����� � ��������� ������������!

				PlayerInfo[playerid][pArticle] = 0;//������ ������
				PlayerInfo[playerid][pPart] = 0;//������ �����
				ClearCrime(playerid, playerid, TicketMoney[playerid]);
				TicketMoney[playerid] = 0;
				ShowMenuForPlayerEx(mPoliceDepartment, playerid);
			}
		}
		case 2://MobileDataComputer
		{
			/*new Menu:Current = GetPlayerMenu(playerid);//�������� ID ����
			if(Current == mPoliceDepartment)
			{*/
			HideMenuForPlayerEx(mPoliceDepartment,playerid);
			//}
			MobileDataComputer(playerid);
			//TogglePlayerControllableEx(playerid, 0);//�������������
		}
		case 3://Lock Door
		{
	        if(IsACop(playerid))
	        {
				if(gPDLockDoor == 1)
				{
					gPDLockDoor = 0;
					GameTextForPlayerEx(playerid, "~w~Door ~g~Unlocked", 5000, 6);
					PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
					ShowMenuForPlayerEx(mPoliceDepartment, playerid);
				}
				else// if(gPDLockDoor == 0)
				{
					gPDLockDoor = 1;
					GameTextForPlayerEx(playerid, "~w~Door ~r~Locked", 5000, 6);
					PlaySoundForPlayer(playerid, SOUND_RESTAURANT_TRAY_COLLISION);
					ShowMenuForPlayerEx(mPoliceDepartment, playerid);
				}
	        }
			else
			{
			    SendClientMessage(playerid, COLOR_GREY, "   �� �� ��� / FBI!");// / National Guard
				ShowMenuForPlayerEx(mPoliceDepartment, playerid);
			}
		}
	}
	return 1;
}


stock WantedList(playerid)
{   //���������� �� police_OnPlayerSelectedMenuRow(playerid, row)
	//new strings[MAX_STRING];
	//format(strings, sizeof(strings), "������ �������������:", LevelToCriminality);
	SendClientMessage(playerid, COLOR_BROWNGREEN, "������ �������������:");

	new wanted_counter, ind, strtmp[128];
    for(new j=0, i; j<MaxPlayers; j++)	{
		i = PLIDs[j];
		if( !IsPlayerConnectedEx(i) ) continue;
		if(WantedLevel[i] > 0 && PlayerInfo[i][pJailed] == 0)
		{
			if(PlayerInfo[i][pArticle] >= 139) format(strtmp, sizeof(strtmp), "%s{99CCFF}%s[%d]: %d", strtmp, PlayerName(i), i, WantedLevel[i]);
			else if(PlayerInfo[i][pArticle] >= 1 && PlayerInfo[i][pArticle] <= 36) format(strtmp, sizeof(strtmp), "%s{33CCCC}%s[%d]: %d", strtmp, PlayerName(i), i, WantedLevel[i]);
			else format(strtmp, sizeof(strtmp), "%s{666699}%s[%d]: %d", strtmp, PlayerName(i), i, WantedLevel[i]);
			ind ++;
			if(ind > 3)
			{//���� ������� ���-�� ����� �� ����� ������ ������ 3, ��
			    SendClientMessage(playerid, COLOR_BLUEGREY, strtmp);
			    ind = 0;
				strdel(strtmp, 0, sizeof(strtmp));
			}
			else
			{
				format(strtmp, sizeof(strtmp), "%s, ", strtmp);//������ ������� ����� ������
			}
			wanted_counter ++;
		}
	}
	if(ind > 0 && ind <= 3)
	{//������ ����� � ����� ������
		strtmp[strlen(strtmp)-2] = '.';
	    SendClientMessage(playerid, COLOR_BLUEGREY, strtmp);
	}
	format(strings, sizeof(strings), "���� �������, {%06x}���� ���, {%06x}���� ���", COLOR_DARKTURQUOISE >>> 72, COLOR_PALEPURPLE >>> 72);
	SendClientMessage(playerid, COLOR_BLUEGREY, strings);

	format(strings, sizeof(strings), "T������ ������� ������������ � ����� ���-�������: %d.", LevelToCriminality);
	SendClientMessage(playerid, COLOR_BROWNGREEN, strings);
}


stock police_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	//#pragma unused inputtext
	if(dialogid != CLEARWANTED_DIALOG) return 1;
	SetPVarInt(playerid, "gShowDialog", -1);
	new msgitem[256+1];
	new giveplayerid;
//mPoliceDepartment
	if(!response)
	{
		TogglePlayerControllableEx(playerid, 0);//�������������
		if(PlayerInfo[playerid][pLocal] >= 246 && PlayerInfo[playerid][pLocal] <= 248) ShowMenuForPlayerEx(mPoliceDepartment, playerid);
		else if(PlayerInfo[playerid][pLocal] == 100) ShowMenuForPlayerEx(mBank, playerid);
		return 1;
	}
//ShowPlayerDialogEx(playerid, 16, DIALOG_STYLE_INPUT, "Clear Wanted", "������� ID ������ [playerid] \n��� ����� ����� [PartOfName]", "OK", "Cancel");
//ShowPlayerDialogEx(playerid, 16, DIALOG_STYLE_INPUT, "Transfer", "������� ID ������ [playerid] \n��� ����� ����� [PartOfName]", "OK", "Cancel");
//Clear Wanted
	if(PlayerInfo[playerid][pLocal] >= 246 && PlayerInfo[playerid][pLocal] <= 248)
	{
		giveplayerid = ReturnUser(inputtext);
		if( !IsPlayerConnected(giveplayerid) )
		{
			format(msgitem, sizeof(msgitem), "   ID:%d ����������� �� �������.", giveplayerid);
			SendClientMessage(playerid, COLOR_GREY, msgitem);
			return 1;
		}
	    if(WantedLevel[giveplayerid] <= 0)
		{
		  	SendClientMessage(playerid, COLOR_GREY, "   ������ ����� �� � �������!");
		  	return 1;
		}
		if(IsACop(playerid) && PlayerInfo[playerid][pRank] >= 4)
		{
			if(!IsAtPolice(playerid))
			{
				SendClientMessage(playerid, COLOR_GREY, "   �� �� � ����������� �������!");
				return 1;
			}
			if(gGotOrder[playerid] != giveplayerid && PlayerInfo[giveplayerid][pAdmin] != 9)
			{
			    SendClientMessage(playerid, COLOR_GREY, "   � ��� ��� ���������� �� ������ ������ ������������ ����� �������� !");
			    return 1;
			}
			if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����� ������� ������������ � ������ ����!"); return 1; }
		   	if(PlayerInfo[giveplayerid][pJailed] > 0) { SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����� ������� ������� � ������������!"); return 1; }
			format(msgitem, sizeof(msgitem), "* �� ����� ������� ������������ � %s.", PlayerName(giveplayerid));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
			format(msgitem, sizeof(msgitem), "* ������ %s ���� ������� ������������.", PlayerName(playerid));
			SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
			PlayerInfo[giveplayerid][pArticle] = 0;//������ ������
			PlayerInfo[giveplayerid][pPart] = 0;//������ �����
			gGotOrder[playerid] = MAX_PLAYERS-1;
			//PlayerInfo[giveplayeri][pJailTime] = 0;//������ ����
			//PlayerInfo[giveplayerid][pJailed] = 0;//����� �� � ������
			ClearCrime(giveplayerid, playerid, 1);
		}
		else if(PlayerInfo[playerid][pLeader] == LCN || PlayerInfo[playerid][pLeader] == Yakuza)//���� �� ����� �����
		{
			//if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����� ������� ������������ � ������ ����!"); return 1; }
			if(PlayerInfo[giveplayerid][pJailed] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   �� �� ������ ����� ������� ������� � ������������!");
				return 1;
			}
		    if(GetPlayerMoneyH(playerid) < 500)
			{
				SendClientMessage(playerid, COLOR_GREY, "   ��� ����� $500, ����� ������� ������� ������������!");
				return 1;
			}
		   	if(WantedLevel[giveplayerid] > 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   �� ���� �� ������ ����� ������� ������� � ��������������!");
				return 1;
			}
			PlayerInfo[giveplayerid][pArticle] = 0;//������ ������
			PlayerInfo[giveplayerid][pPart] = 0;//������ �����
			ClearCrime(giveplayerid, playerid, 500);

			GivePlayerMoneyH(ftax, playerid, -500);//��� ���������
			if(BizInfo[0][bTill] < 2147480000) { BizInfo[0][bTill] += 500; BizInfo[0][bExport] += 500; }

		    format(msgitem, sizeof(msgitem), "* �� �������� ������ � ������� ������� � {FFFFFF}%s{0080FF} �� {33AA33}$500.", PlayerName(giveplayerid));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, msgitem);
			format(msgitem, sizeof(msgitem), "* ����� ����� %s, ������� ���� ������ � ������� �������.", PlayerName(playerid));
			SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, msgitem);
		}
		else SendClientMessage(playerid, COLOR_GREY, "   �� �� ����������� >4 ����� / Family Leader !");// National Guard
	}
	return 1;
}

stock police_OneSecondTimers(playerid)
{
	if(	gTutorial[playerid] == 1) return 1;
	//��� �������c��� ���������
	if(	GPS_OnOff[playerid] == 1 && PlayerInfo[playerid][pGPS] == 1 &&
		GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
    	if((PlayerInfo[playerid][pMember] == DoT || PlayerInfo[playerid][pMember] == DoH) &&
			(nCarModel[playerid] == 497 ||	nCarModel[playerid] == 447) )
		{
		    if(MarkerToPlayer[playerid] != MAX_PLAYERS-1 && GetPVarInt(playerid, "gCheckpointStatus") < MAX_PLAYERS)
			{
				new Float:X,Float:Y,Float:Z;
				GetPlayerPos(MarkerToPlayer[playerid], X, Y, Z);
				SetPlayerRouting(playerid, X, Y, Z);
			}
		}
	}
	return 1;
}

#define MAX_ROADBLOCK 60
enum rbInfo
{
	rbCreated,
    Float:rbX,
    Float:rbY,
    Float:rbZ,
    rbObject
};
new RoadBlock[MAX_ROADBLOCK][rbInfo];//������ ����������� ������


stock police_OnPlayerKeyState_LEFT(playerid)
{
		new strcmd[MAX_STRING];//, tmp[MAX_STRING], gMessage[MAX_STRING];
		if(PlayerInfo[playerid][pMember] != DoT && PlayerInfo[playerid][pAdmin] != 4)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not a Road Policemen San-Andreas !");
			return 1;
		}
		if(PlayerInfo[playerid][pRank] < 4 && PlayerInfo[playerid][pAdmin] != 4)
		{
			SendClientMessage(playerid, COLOR_GREY, "   ��� ����� ���� 4, ����� ������������� �������� ����� !");
			return 1;
		}
        if(gOnDuty[playerid] != 1 && PlayerInfo[playerid][pAdmin] != 4)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   �� �� ��� ���������� ��������� ������������ !");
		    return 1;
		}

		if(PlayerInfo[playerid][pInt] != 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   � ��������� �� ����������� ������������� �������� ����� !");
			return 1;
		}
		if(IsPlayerInArea(playerid, specialzone[0]))
		{
			SendClientMessage(playerid, COLOR_GREY, "   � ���� ����� ��������� ��������� �������� ������ !");
			return 1;
		}
		new Float:rX, Float:rY, Float:rZ, Float:rA;
		GetXYZInFrontOfPlayer(playerid, 2.0, rX,rY,rZ, rA);
		if(rbCounter < MAX_ROADBLOCK/2)
		{
	  	    if(RoadBlock[rbCounter][rbCreated] == 0)
	  	    {
	            RoadBlock[rbCounter][rbCreated] = 1;
	            RoadBlock[rbCounter][rbX] = rX;
	            RoadBlock[rbCounter][rbY] = rY;
	            RoadBlock[rbCounter][rbZ] = rZ;
				RoadBlock[rbCounter][rbObject] = CreateObjectEx(981, rX, rY, rZ, 0.0, 0.0, rA);
				format(strcmd, sizeof(strcmd), "%s has installed roadblock %d[%d]", PlayerName(playerid), RoadBlock[rbCounter][rbObject], rbCounter);
				SendTeamMessage(DoT, COLOR_DARKTURQUOISE, strcmd);
				rbCounter ++;
			}
	  	    if(RoadBlock[rbCounter][rbCreated] == 0)
	  	    {
	            RoadBlock[rbCounter][rbCreated] = 1;
	            RoadBlock[rbCounter][rbX] = rX;
	            RoadBlock[rbCounter][rbY] = rY;
	            RoadBlock[rbCounter][rbZ] = rZ-0.3;
				RoadBlock[rbCounter][rbObject] = CreateObjectEx(982, rX, rY, rZ-0.3, 0.0, 0.0, rA+90.0);
				format(strcmd, sizeof(strcmd), "%s has installed roadblock %d[%d]", PlayerName(playerid), RoadBlock[rbCounter][rbObject], rbCounter);
				SendTeamMessage(DoT, COLOR_DARKTURQUOISE, strcmd);
				rbCounter ++;
			}
		}
		else SendClientMessage(playerid, COLOR_GREY, "   ��������� ������ ��������� �������� ������ !");
		//SendClientMessage(playerid, COLOR_GRAYWHITE, "USE: /roadblock [number radar 1-32] (0 = OFF)");
		return 1;
}

stock police_OnPlayerKeyState_RIGHT(playerid)
{
		new strcmd[MAX_STRING];//, tmp[MAX_STRING], gMessage[MAX_STRING];
	    if((PlayerInfo[playerid][pMember] != DoT && PlayerInfo[playerid][pAdmin] < 4) ||
			(PlayerInfo[playerid][pMember] == DoT && PlayerInfo[playerid][pRank] < 4))
	    {
		    SendClientMessage(playerid, COLOR_GREY, "   �� �� ������������ ������������ ��� �������: destroyed roadblock !");
	        return 1;
	    }
        if(gOnDuty[playerid] != 1)
		{
		    SendClientMessage(playerid, COLOR_GREY, "   �� �� ��� ���������� ��������� ������������ !");
		    return 1;
		}
        //tmp = strtok(cmdtext, idx);
		//if(!strlen(tmp))
		//{
	    for(new rb = sizeof(RoadBlock)-1; rb >= 0; rb--)
	  	{
	  	    if(RoadBlock[rb][rbCreated] == 1)
	  	    {
		  	    if(IsPlayerInRangeOfPoint(playerid, 30.0, RoadBlock[rb][rbX], RoadBlock[rb][rbY], RoadBlock[rb][rbZ]))
		        {
		            RoadBlock[rb][rbCreated] = 0;
		            RoadBlock[rb][rbX] = 0.0;
		            RoadBlock[rb][rbY] = 0.0;
		            RoadBlock[rb][rbZ] = 0.0;
		            DestroyObjectEx(RoadBlock[rb][rbObject], 15);
					format(strcmd, sizeof(strcmd), "%s has destroyed roadblock %d[%d]", PlayerName(playerid), RoadBlock[rb], rb);
					SendTeamMessage(DoT, COLOR_DARKTURQUOISE, strcmd);
					rbCounter --;
			        return 1;//break;
		  	    }
			}
	  	}
		SendClientMessage(playerid, COLOR_GREY, "   �� ������ �� ������� !");
			//return 1;
		//}
		
		/*new oRoadBlock = strval(tmp);
		if(oRoadBlock == 0)// && PlayerInfo[playerid][pRank] >= 5
		{
			if(PlayerInfo[playerid][pAdmin] >= 4 || PlayerInfo[playerid][pRank] >= 11)
			{
		    	for(new rb = 0; rb < sizeof(RoadBlock); rb++)
		  		{
		  	    	if(RoadBlock[rb][rbCreated] == 1)
		  	    	{
			            RoadBlock[rb][rbCreated] = 0;
			            RoadBlock[rb][rbX] = 0.0;
			            RoadBlock[rb][rbY] = 0.0;
			            RoadBlock[rb][rbZ] = 0.0;
			            DestroyObjectEx(RoadBlock[rb][rbObject], 16);
			            rbCounter --;
			  	    }
				}
			  	SendClientMessage(playerid, COLOR_GREY, "   ��� ��������� ����������� ����� ���������� !");
				//GameTextForPlayerEx(playerid, "~g~All PoliceBlock deployed successfully", 5000, 5);
				return 1;
			}
		}*/
		return 1;
}
