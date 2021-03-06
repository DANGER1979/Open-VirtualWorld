//��� �������
new gLadderNumber[MAX_PLAYERS];//����� �������� � ������� LadderInfo

new LadderPickupWaitTime[MAX_PLAYERS];//�������� ����� ����� ��������� �� ����������

//���� gLadderNumber ����� ���� �� ������ �������� ��� �� �����������
enum lLadders
{
	Float: Postions[5],
	Float: Ranges,
	Pickup[2],//pickupid ������� � ��������
	Float: Offset[3]
}
new LadderInfo[STAIRWAYS][lLadders];



/*new Float:Stairway[43][4] = {//��������
{2729.4377,-2195.3003,13.5469,285.7090},// - ���� � ��
//{2736.7446,-2190.3552,36.1457,182.3266},// - ���� � ��
//{2687.3096,-2112.8406,13.5488,107.3114},// - ���� � ��
//{2679.7605,-2117.8340,36.1457,357.9362},// - ���� � ��
{-2328.9941,1528.6578,-0.5134,3.5243},//  - ������� ����� �����
{-1059.5161,-603.5989,35.9492,268.7716},// - ��� �������� ����� ��
{-1009.1819,-704.0970,32.0078,266.2834},// - ��� �������� ����� ��
{-1013.5000,-719.1574,32.0078,177.2309},// - ��� �������� ����� ��
//{-1017.9928,-703.8479,32.0078,90.9565},//  - ��� �������� ����� ��
{-1055.5400,-719.3679,32.0078,179.8628},// - ��� �������� ����� ��
{-1099.6943,-719.3623,32.0078,178.2544},// - ��� �������� ����� ��
{-1062.7322,-670.4625,32.3516,180.8840},// - ��� �������� ����� ��
{-1073.1176,-645.8724,32.0078,175.6200},// - ��� �������� ����� ��
{-1110.7913,-645.8748,32.0078,180.5916},// - ��� �������� ����� ��
{-1097.3257,-640.2999,34.0896,2.9299},//   - ��� �������� ����� ��
{-1063.1713,-640.0411,34.0896,0.1516},//   - ��� �������� ����� ��
//{-1015.2742,-700.8284,32.0078,113.6139},// - ��� �������� ����� ��
//{-1026.8075,-700.3597,47.7875,180.7305},// - ��� �������� ����� ��
{-1154.2854,-476.7553,1.9609,57.7369},//   - ���� � ��
{-1081.8784,-207.9435,1.9609,109.7925},//  - ���� � ��
{-1182.6094,60.4037,1.9609,132.1647},//    - ���� � ��
{-1115.8254,335.3107,1.9609,43.4045},//    - ���� � ��
{-1164.5923,370.0497,1.9609,222.9672},//   - ���� � ��
{-1444.4330,90.2637,1.9609,227.7926},//    - ���� � ��
{-1618.7378,-84.0036,1.9609,228.8162},//   - ���� � ��
{-1736.4484,-446.0066,1.9609,276.6313},//  - ���� � ��
{178.2037,1454.2150,10.5912,289.8082},// - ����� ���� ����� ���� 51
{245.7919,1475.9341,10.5859,202.6615},// - ����� ���� ����� ���� 51
{197.7353,1411.9525,10.5859,201.7867},// - ����� ���� ����� ���� 51
{250.8561,1468.5189,33.0129,88.7532},// - ����� ���� ����� ���� 51
{185.5572,1459.0507,33.0129,175.9024},// - ����� ���� ����� ���� 51
{202.6839,1404.4503,33.0129,85.5362},//  - ����� ���� ����� ���� 51
{600.9718,1251.8148,11.7113,85.6657},//  - �������� �� ������� � ��
{2632.5359,2836.7737,24.3494,183.9740},// - LV ���������� ����
{2713.6851,2773.6018,10.8203,269.3685},// - LV ���������� ����
{2688.1030,2637.9453,10.8203,357.6897},// - LV ���������� ����
{2657.3945,2643.9116,10.8203,358.7133},// - LV ���������� ����
{2613.2019,2643.9114,10.8203,359.0058},// - LV ���������� ����
{2571.1519,2643.9050,10.8203,358.4208},// - LV ���������� ����
{2588.5640,2638.3997,10.8203,270.5403},// - LV ���������� ����
{2501.6514,2690.5066,10.8130,268.7856},//- LV ���������� ����
{2703.1785,2676.8325,12.8222,358.4184}// - LV ���������� ����
};*/
//��� �������
stock ladder_OnGameModeInit()
{
	new time = GetTickCount();
    // ************************* �������� ���� � �� �1 #2  **************************** //
    LadderInfo[0][Postions][0] = 2729.4373; 		// X
    LadderInfo[0][Postions][1] = -2195.4172;  		// y
    LadderInfo[0][Postions][2] = 14.0;              // Z
    LadderInfo[0][Postions][3] = 296.1060;          // Angle
    LadderInfo[0][Postions][4] = 47.8048;           // �������� ����� Z �������.
    LadderInfo[0][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[0][Offset][1] = 0.05;                // �� ������� X ��� ������ ������.

    // ************************* �������� ������� ����� ����� #3  **************************** //
    LadderInfo[1][Postions][0] = -2328.9941; 		// X
    LadderInfo[1][Postions][1] = 1528.6578;  		// y
    LadderInfo[1][Postions][2] = 0.0;           	// Z
    LadderInfo[1][Postions][3] = 3.5243;          	// Angle
    LadderInfo[1][Postions][4] = 19.9134;           // �������� ����� Z �������.
    LadderInfo[1][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[1][Offset][1] = 0.0;                // �� ������� X ��� ������ ������.
    LadderInfo[1][Offset][2] = 0.05;               	// �� ������� Y ��� ������ ������.


   	// ************************* �������� ��� �������� ����� �� �1 #4  **************************** //
    LadderInfo[2][Postions][0] = -1059.9993; 		// X
    LadderInfo[2][Postions][1] = -603.6131;  		// y
    LadderInfo[2][Postions][2] = 34.0896;           // Z
    LadderInfo[2][Postions][3] = 268.1924;          // Angle
    LadderInfo[2][Postions][4] = 94.5896;           // �������� ����� Z �������.
    LadderInfo[2][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[2][Offset][1] = 0.09;                // �� ������� X ��� ������ ������.
    LadderInfo[2][Offset][2] = 0.0;               	// �� ������� Y ��� ������ ������.
    // ************************* �������� ��� �������� ����� �� �2 #5  **************************** //
    LadderInfo[3][Postions][0] = -1009.1819; 		// X
    LadderInfo[3][Postions][1] = -704.0970;  		// y
    LadderInfo[3][Postions][2] = 32.3078;           // Z
    LadderInfo[3][Postions][3] = 266.2834;          // Angle
    LadderInfo[3][Postions][4] = 94.6011;           // �������� ����� Z �������.
    LadderInfo[3][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[3][Offset][1] = 0.09;                // �� ������� X ��� ������ ������.
    LadderInfo[3][Offset][2] = 0.0;               	// �� ������� Y ��� ������ ������.
   	// ************************* �������� ��� �������� ����� �� �3 #6  **************************** //
    LadderInfo[4][Postions][0] = -1013.5000; 		// X
    LadderInfo[4][Postions][1] = -719.1574;  		// y
    LadderInfo[4][Postions][2] = 32.5078;           // Z
    LadderInfo[4][Postions][3] = 177.2309;          // Angle
    LadderInfo[4][Postions][4] = 56.0;           	// �������� ����� Z �������.
    LadderInfo[4][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[4][Offset][1] = 0.0;               	// �� ������� X ��� ������ ������.
    LadderInfo[4][Offset][2] = (-0.09);             	// �� ������� Y ��� ������ ������.
   	// ************************* �������� ��� �������� ����� �� �4 #7  **************************** //
    LadderInfo[5][Postions][0] = -1055.5400; 		// X
    LadderInfo[5][Postions][1] = -719.0;  			// y
    LadderInfo[5][Postions][2] = 32.5078;           // Z
    LadderInfo[5][Postions][3] = 179.8628;          // Angle
    LadderInfo[5][Postions][4] = 56.0;           	// �������� ����� Z �������.
    LadderInfo[5][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[5][Offset][1] = 0.0;               	// �� ������� X ��� ������ ������.
    LadderInfo[5][Offset][2] = (-0.09);             // �� ������� Y ��� ������ ������.
   	// ************************* �������� ��� �������� ����� �� �5 #8  **************************** //
    LadderInfo[6][Postions][0] = -1099.6943; 		// X
    LadderInfo[6][Postions][1] = -719.0;  			// y
    LadderInfo[6][Postions][2] = 32.5078;           // Z
    LadderInfo[6][Postions][3] = 178.2544;          // Angle
    LadderInfo[6][Postions][4] = 56.0;           	// �������� ����� Z �������.
    LadderInfo[6][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[6][Offset][1] = 0.0;               	// �� ������� X ��� ������ ������.
    LadderInfo[6][Offset][2] = (-0.09);             // �� ������� Y ��� ������ ������.
   	// ************************* �������� ��� �������� ����� �� �5 #9  **************************** //
    LadderInfo[7][Postions][0] = -1062.7322; 		// X
    LadderInfo[7][Postions][1] = -670.4625;  		// y
    LadderInfo[7][Postions][2] = 32.4516;           // Z
    LadderInfo[7][Postions][3] = 180.8840;          // Angle
    LadderInfo[7][Postions][4] = 59.1;           	// �������� ����� Z �������.
    LadderInfo[7][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[7][Offset][1] = 0.0;               	// �� ������� X ��� ������ ������.
    LadderInfo[7][Offset][2] = (-0.09);             // �� ������� Y ��� ������ ������.
   	// ************************* �������� ��� �������� ����� �� �7 #10  **************************** //
    LadderInfo[8][Postions][0] = -1073.3176; 		// X
    LadderInfo[8][Postions][1] = -645.5724;  		// y
    LadderInfo[8][Postions][2] = 32.3078;           // Z
    LadderInfo[8][Postions][3] = 175.6200;          // Angle
    LadderInfo[8][Postions][4] = 56.0;            	// �������� ����� Z �������.
    LadderInfo[8][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[8][Offset][1] = 0.0;               	// �� ������� X ��� ������ ������.
    LadderInfo[8][Offset][2] = (-0.09);             // �� ������� Y ��� ������ ������.
   	// ************************* �������� ��� �������� ����� �� �8 #11  **************************** //
    LadderInfo[9][Postions][0] = -1110.8791; 		// X
    LadderInfo[9][Postions][1] = -645.5748;  		// y
    LadderInfo[9][Postions][2] = 32.3078;          // Z
    LadderInfo[9][Postions][3] = 180.5916;         // Angle
    LadderInfo[9][Postions][4] = 56.0;            	// �������� ����� Z �������.
    LadderInfo[9][Offset][0] = 1.0;           	// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[9][Offset][1] = 0.0;               	// �� ������� X ��� ������ ������.
    LadderInfo[9][Offset][2] = (-0.09);            // �� ������� Y ��� ������ ������.
   	// ************************* �������� ��� �������� ����� �� �9 #12  **************************** //
    LadderInfo[10][Postions][0] = -1097.3257; 		// X
    LadderInfo[10][Postions][1] = -640.5999;  		// y
    LadderInfo[10][Postions][2] = 34.3896;          // Z
    LadderInfo[10][Postions][3] = 2.9299;          	// Angle
    LadderInfo[10][Postions][4] = 44.08;            // �������� ����� Z �������.
    LadderInfo[10][Offset][0] = 1.0;           	// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[10][Offset][1] = 0.0;               	// �� ������� X ��� ������ ������.
    LadderInfo[10][Offset][2] = 0.09;             	// �� ������� Y ��� ������ ������.
   	// ************************* �������� ��� �������� ����� �� �10 #13  **************************** //
    LadderInfo[11][Postions][0] = -1063.1713; 		// X
    LadderInfo[11][Postions][1] = -640.5999;  		// y
    LadderInfo[11][Postions][2] = 34.3896;          // Z
    LadderInfo[11][Postions][3] = 0.1516;          	// Angle
    LadderInfo[11][Postions][4] = 44.08;            // �������� ����� Z �������.
    LadderInfo[11][Offset][0] = 1.0;           	// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[11][Offset][1] = 0.0;               	// �� ������� X ��� ������ ������.
    LadderInfo[11][Offset][2] = 0.09;             	// �� ������� Y ��� ������ ������.
   	// ************************* �������� ��� �������� ����� �� �11 #15  **************************** //
    LadderInfo[12][Postions][0] = -1060.1162; 		// X
    LadderInfo[12][Postions][1] = -617.6572;  		// y
    LadderInfo[12][Postions][2] = 34.3;          	// Z
    LadderInfo[12][Postions][3] = 268.8642;         // Angle
    LadderInfo[12][Postions][4] = 130.1;            // �������� ����� Z �������.
    LadderInfo[12][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[12][Offset][1] = 0.09;              	// �� ������� X ��� ������ ������.
    LadderInfo[12][Offset][2] = 0.0;             	// �� ������� Y ��� ������ ������.
   	// ************************* �������� ��� �������� ����� �� �12 #16  **************************** //
    LadderInfo[13][Postions][0] = -1056.0107; 		// X
    LadderInfo[13][Postions][1] = -627.7312;  		// y
    LadderInfo[13][Postions][2] = 32.3078;          // Z
    LadderInfo[13][Postions][3] = 179.2056;         // Angle
    LadderInfo[13][Postions][4] = 130.1;            // �������� ����� Z �������.
    LadderInfo[13][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[13][Offset][1] = 0.0;              	// �� ������� X ��� ������ ������.
    LadderInfo[13][Offset][2] = (-0.09);            // �� ������� Y ��� ������ ������.

   	// ************************* �������� ���� � �� �1 #14  **************************** //
    LadderInfo[14][Postions][0] = -1154.1854; 		// X
    LadderInfo[14][Postions][1] = -476.7553;  		// y
    LadderInfo[14][Postions][2] = 2.0;          	// Z
    LadderInfo[14][Postions][3] = 57.7369;          // Angle
    LadderInfo[14][Postions][4] = 13.85;            // �������� ����� Z �������.
    LadderInfo[14][Offset][0] = 1.0;           	// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[14][Offset][1] = (-0.09);            // �� ������� X ��� ������ ������.
    LadderInfo[14][Offset][2] = 0.0;             	// �� ������� Y ��� ������ ������.
   	// ************************* �������� ���� � �� �2  #17  **************************** //
    LadderInfo[15][Postions][0] = -1081.7784; 		// X
    LadderInfo[15][Postions][1] = -207.8435;  		// y
    LadderInfo[15][Postions][2] = 2.0;          	// Z
    LadderInfo[15][Postions][3] = 109.7925;         // Angle
    LadderInfo[15][Postions][4] = 13.85;            // �������� ����� Z �������.
    LadderInfo[15][Offset][0] = 1.0;           	// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[15][Offset][1] = (-0.09);            // �� ������� X ��� ������ ������.
    LadderInfo[15][Offset][2] = 0.0;             	// �� ������� Y ��� ������ ������.
   	// ************************* �������� ���� � �� �3  #18  **************************** //
    LadderInfo[16][Postions][0] = -1182.5094; 		// X
    LadderInfo[16][Postions][1] = 60.5037;  		// y
    LadderInfo[16][Postions][2] = 2.0;          	// Z
    LadderInfo[16][Postions][3] = 132.1647;         // Angle
    LadderInfo[16][Postions][4] = 13.85;            // �������� ����� Z �������.
    LadderInfo[16][Offset][0] = 1.0;           	// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[16][Offset][1] = (-0.09);            // �� ������� X ��� ������ ������.
    LadderInfo[16][Offset][2] = 0.0;             	// �� ������� Y ��� ������ ������.
   	// ************************* �������� ���� � �� �4  #19  **************************** //
    LadderInfo[17][Postions][0] = -1115.7254; 		// X
    LadderInfo[17][Postions][1] = 335.3107;  		// y
    LadderInfo[17][Postions][2] = 2.0;          	// Z
    LadderInfo[17][Postions][3] = 43.4045;         	// Angle
    LadderInfo[17][Postions][4] = 13.85;            // �������� ����� Z �������.
    LadderInfo[17][Offset][0] = 1.0;           	// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[17][Offset][1] = 0.0;            	// �� ������� X ��� ������ ������.
    LadderInfo[17][Offset][2] = 0.09;            	// �� ������� Y ��� ������ ������.
   	// ************************* �������� ���� � �� �5  #20  **************************** //
    LadderInfo[18][Postions][0] = -1164.6923; 		// X
    LadderInfo[18][Postions][1] = 370.0497;  		// y
    LadderInfo[18][Postions][2] = 2.0;          	// Z
    LadderInfo[18][Postions][3] = 222.9672;        	// Angle
    LadderInfo[18][Postions][4] = 13.85;            // �������� ����� Z �������.
    LadderInfo[18][Offset][0] = 1.0;           	// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[18][Offset][1] = 0.0;            	// �� ������� X ��� ������ ������.
    LadderInfo[18][Offset][2] = (-0.09);            // �� ������� Y ��� ������ ������.

   	// ************************* �������� ���� � �� �6  #21  **************************** //
    LadderInfo[19][Postions][0] = -1444.5330; 		// X
    LadderInfo[19][Postions][1] = 90.2637;  		// y
    LadderInfo[19][Postions][2] = 2.0;          	// Z
    LadderInfo[19][Postions][3] = 227.7926;        	// Angle
    LadderInfo[19][Postions][4] = 13.85;            // �������� ����� Z �������.
    LadderInfo[19][Offset][0] = 1.0;           	// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[19][Offset][1] = 0.0;            	// �� ������� X ��� ������ ������.
    LadderInfo[19][Offset][2] = (-0.09);            // �� ������� Y ��� ������ ������.
   	// ************************* �������� ���� � �� �7  #22  **************************** //
    LadderInfo[21][Postions][0] = -1736.5484; 		// X
    LadderInfo[21][Postions][1] = -446.0066;  		// y
    LadderInfo[21][Postions][2] = 2.0;          	// Z
    LadderInfo[21][Postions][3] = 276.6313;        	// Angle
    LadderInfo[21][Postions][4] = 13.85;            // �������� ����� Z �������.
    LadderInfo[21][Offset][0] = 1.0;           	// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[21][Offset][1] = 0.09;            	// �� ������� X ��� ������ ������.
    LadderInfo[21][Offset][2] = 0.0;            	// �� ������� Y ��� ������ ������.
	// ************************* �������� ���� SF-���� �8 #1  **************************** //
    LadderInfo[22][Postions][0] = -1618.8063; 		// X
    LadderInfo[22][Postions][1] = -83.9022;  		// y
    LadderInfo[22][Postions][2] = 2.0;               // Z
    LadderInfo[22][Postions][3] = 225.9389;          // Angle
    LadderInfo[22][Postions][4] = 13.9609;           // �������� ����� Z �������.
    LadderInfo[22][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[22][Offset][1] = 0.05;                // �� ������� X ��� ������ ������.
	// ************************* �������� ���� SF-���� �9 #2  **************************** //
	//-1361.0659,-696.6440,1.9609
    LadderInfo[23][Postions][0] = -1361.0659; 		// X
    LadderInfo[23][Postions][1] = -696.6440;  		// y
    LadderInfo[23][Postions][2] = 2.0609;               // Z
    LadderInfo[23][Postions][3] = 5.5487;          // Angle
    LadderInfo[23][Postions][4] = 14.1484;           // �������� ����� Z �������.
    LadderInfo[23][Offset][0] = 1.0;           	 // �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[23][Offset][1] = 0.0;               	// �� ������� X ��� ������ ������.
    LadderInfo[23][Offset][2] = 0.09;             	// �� ������� Y ��� ������ ������.
	// ************************* �������� ���� SF-���� �9 #3  **************************** //
	//-1603.3799,-696.6437,1.9609
    LadderInfo[24][Postions][0] = -1603.3799; 		// X
    LadderInfo[24][Postions][1] = -696.6437;  		// y
    LadderInfo[24][Postions][2] = 2.0609;               // Z
    LadderInfo[24][Postions][3] = 1.9609;          // Angle
    LadderInfo[24][Postions][4] = 14.1440;           // �������� ����� Z �������.
    LadderInfo[24][Offset][0] = 1.0;           	 // �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[24][Offset][1] = 0.0;               	// �� ������� X ��� ������ ������.
    LadderInfo[24][Offset][2] = 0.09;             	// �� ������� Y ��� ������ ������.

   	// ************************* �������� �������� �� ������� � ��  #23  **************************** //
    LadderInfo[25][Postions][0] = 601.2; 			// X
    LadderInfo[25][Postions][1] = 1251.8148;  		// y
    LadderInfo[25][Postions][2] = 11.7113;          // Z
    LadderInfo[25][Postions][3] = 85.6657;        	// Angle
    LadderInfo[25][Postions][4] = 28.7113;          // �������� ����� Z �������.
    LadderInfo[25][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[25][Offset][1] = (-0.09);            // �� ������� X ��� ������ ������.
    LadderInfo[25][Offset][2] = 0.00;            	// �� ������� Y ��� ������ ������.

   	// ************************* �������� LV ���������� ���� �1 #24  **************************** //
    LadderInfo[26][Postions][0] = 2632.5359; 		// X
    LadderInfo[26][Postions][1] = 2836.7737;  		// y
    LadderInfo[26][Postions][2] = 22.5494;          // Z
    LadderInfo[26][Postions][3] = 183.9740;        	// Angle
    LadderInfo[26][Postions][4] = 123.5494;         // �������� ����� Z �������.
    LadderInfo[26][Offset][0] = 1.0;           	// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[26][Offset][1] = 0.0;            	// �� ������� X ��� ������ ������.
    LadderInfo[26][Offset][2] = (-0.09);            // �� ������� Y ��� ������ ������.
   	// ************************* �������� LV ���������� ���� �2 #25  **************************** //
    LadderInfo[27][Postions][0] = 2713.1851; 		// X
    LadderInfo[27][Postions][1] = 2773.6018;  		// y
    LadderInfo[27][Postions][2] = 12.8203;          // Z
    LadderInfo[27][Postions][3] = 269.3685;        	// Angle
    LadderInfo[27][Postions][4] = 76.0;         	// �������� ����� Z �������.
    LadderInfo[27][Offset][0] = 1.0;           	// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[27][Offset][1] = 0.09;            	// �� ������� X ��� ������ ������.
    LadderInfo[27][Offset][2] = 0.0;            	// �� ������� Y ��� ������ ������.
   	// ************************* �������� LV ���������� ���� �3 #26  **************************** //
    LadderInfo[28][Postions][0] = 2688.1000; 		// X
    LadderInfo[28][Postions][1] = 2637.9453;  		// y
    LadderInfo[28][Postions][2] = 11.0;          	// Z
    LadderInfo[28][Postions][3] = 357.689;        	// Angle
    LadderInfo[28][Postions][4] = 36.0;         	// �������� ����� Z �������.
    LadderInfo[28][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[28][Offset][1] = 0.0;            	// �� ������� X ��� ������ ������.
    LadderInfo[28][Offset][2] = 0.09;            	// �� ������� Y ��� ������ ������.
   	// ************************* �������� LV ���������� ���� �4 #27  **************************** //
    LadderInfo[29][Postions][0] = 2657.3945; 		// X
    LadderInfo[29][Postions][1] = 2643.9116;  		// y
    LadderInfo[29][Postions][2] = 11.0;          	// Z
    LadderInfo[29][Postions][3] = 358.713;        	// Angle
    LadderInfo[29][Postions][4] = 36.0;         	// �������� ����� Z �������.
    LadderInfo[29][Offset][0] = 1.0;          		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[29][Offset][1] = 0.0;            	// �� ������� X ��� ������ ������.
    LadderInfo[29][Offset][2] = 0.09;            	// �� ������� Y ��� ������ ������.
   	// ************************* �������� LV ���������� ���� �5 #28  **************************** //
    LadderInfo[30][Postions][0] = 2613.2019; 		// X
    LadderInfo[30][Postions][1] = 2643.9114;  		// y
    LadderInfo[30][Postions][2] = 11.0;          	// Z
    LadderInfo[30][Postions][3] = 359.0058;        	// Angle
    LadderInfo[30][Postions][4] = 36.0;         	// �������� ����� Z �������.
    LadderInfo[30][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[30][Offset][1] = 0.0;            	// �� ������� X ��� ������ ������.
    LadderInfo[30][Offset][2] = 0.09;            	// �� ������� Y ��� ������ ������.
   	// ************************* �������� LV ���������� ���� �6 #29  **************************** //
    LadderInfo[31][Postions][0] = 2571.1519; 		// X
    LadderInfo[31][Postions][1] = 2643.9050;  		// y
    LadderInfo[31][Postions][2] = 11.0;          	// Z
    LadderInfo[31][Postions][3] = 358.4208;        	// Angle
    LadderInfo[31][Postions][4] = 36.0;         	// �������� ����� Z �������.
    LadderInfo[31][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[31][Offset][1] = 0.0;            	// �� ������� X ��� ������ ������.
    LadderInfo[31][Offset][2] = 0.09;            	// �� ������� Y ��� ������ ������.
   	// ************************* �������� LV ���������� ���� �7 #30  **************************** //
    LadderInfo[32][Postions][0] = 2588.5640; 		// X
    LadderInfo[32][Postions][1] = 2638.3997;  		// y
    LadderInfo[32][Postions][2] = 11.0;          	// Z
    LadderInfo[32][Postions][3] = 270.5403;        	// Angle
    LadderInfo[32][Postions][4] = 109.5;         	// �������� ����� Z �������.
    LadderInfo[32][Offset][0] = 1.0;           	// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[32][Offset][1] = 0.09;            	// �� ������� X ��� ������ ������.
    LadderInfo[32][Offset][2] = 0.0;            	// �� ������� Y ��� ������ ������.
   	// ************************* �������� LV ���������� ���� �8 #31  **************************** //
    LadderInfo[33][Postions][0] = 2501.0514; 		// X
    LadderInfo[33][Postions][1] = 2690.5066;  		// y
    LadderInfo[33][Postions][2] = 13.0130;          // Z
    LadderInfo[33][Postions][3] = 268.7856;        	// Angle
    LadderInfo[33][Postions][4] = 76.4130;         	// �������� ����� Z �������.
    LadderInfo[33][Offset][0] = 1.0;           	// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[33][Offset][1] = 0.09;            	// �� ������� X ��� ������ ������.
    LadderInfo[33][Offset][2] = 0.0;            	// �� ������� Y ��� ������ ������.
   	// ************************* �������� LV ���������� ���� �9 #32  **************************** //
    LadderInfo[34][Postions][0] = 2703.1785; 		// X
    LadderInfo[34][Postions][1] = 2676.8325;  		// y
    LadderInfo[34][Postions][2] = 13.0;          	// Z
    LadderInfo[34][Postions][3] = 358.4184;        	// Angle
    LadderInfo[34][Postions][4] = 23.8222;         	// �������� ����� Z �������.
    LadderInfo[34][Offset][0] = 1.0;           		// �� ������� ����� ��������� ������ ��� �������� ��� ������ ������� ������.
    LadderInfo[34][Offset][1] = 0.0;            	// �� ������� X ��� ������ ������.
    LadderInfo[34][Offset][2] = 0.09;            	// �� ������� Y ��� ������ ������.


	// �������� ������� ��� ������� �� ��� �� ������.
	for(new l=0; l < STAIRWAYS; l++)
	{
		if(LadderInfo[l][Postions][0] != 0.0)
		{
			LadderInfo[l][Pickup][0] = SetPickupEx(1559, 23, LadderInfo[l][Postions][0],
		    	LadderInfo[l][Postions][1],
		    	(LadderInfo[l][Postions][2]+0.15));
		   	LadderInfo[l][Pickup][1] = SetPickupEx(1318, 23, LadderInfo[l][Postions][0],
		    	LadderInfo[l][Postions][1],
		    	LadderInfo[l][Postions][4]);
		}
 	}
	printf("10/17. [�������� �������]: ���� ��������� - %d, ��������� - %d (ms)", STAIRWAYS, (GetTickCount()-time));
	return;
}
stock ladder_OnPlayerDeath(playerid)
{
	LadderInit(playerid);
}
stock ladder_OnPlayerConnect(playerid)
{
	LadderInit(playerid);
}
stock ladder_OnPlayerSpawn(playerid)
{
	LadderInit(playerid);
}

//��� �������
stock LadderInit(playerid)
{
    LadderPickupWaitTime[playerid] = 0;
    gLadderNumber[playerid] = 0;
}

stock ladder_OnPlayerKeyState_PRESSED(playerid)//��� �������
{ //���� ������ ALT
		//#pragma unused oldkeys
		if(gLadderNumber[playerid] <= 0) return 1;

		new Keys, UpDown, lr;
	    GetPlayerKeys(playerid, Keys, UpDown, lr);

//if(UpDown > 0) SendClientMessage(playerid, 0xFFFFFFFF, "DOWN");
//else if(UpDown < 0) SendClientMessage(playerid, 0xFFFFFFFF, "UP");

//if(lr > 0) SendClientMessage(playerid, 0xFFFFFFFF, "RIGHT");
//else if(lr < 0) SendClientMessage(playerid, 0xFFFFFFFF, "LEFT");

  		new Float: CurrentPos[3];
   		if(UpDown < 0)
		{ //W+ALT
			GetPlayerPos(playerid, CurrentPos[0], CurrentPos[1], CurrentPos[2]);
			if(CurrentPos[2] < LadderInfo[gLadderNumber[playerid]-1][Postions][4])
			{//���� Z ������� ������ ������ �������� ����� Z �������.
				SetPlayerPos(playerid,
					LadderInfo[gLadderNumber[playerid]-1][Postions][0],
					LadderInfo[gLadderNumber[playerid]-1][Postions][1],
					(CurrentPos[2]+LadderInfo[gLadderNumber[playerid]-1][Offset][0]) );
				//OnePlayAnim(playerid, "MTB", "MTB_sprint", 35.1, 1, 0, 0, 0, 0);
				//OnePlayAnim(playerid, "DOZER", "DOZER_Align_LHS",4.1, 0, 0, 0, 1, 0);
				ApplyAnimation(playerid, "PED", "CLIMB_Pull", 4.1, 0, 0, 0, 1, 0);

				//SendClientMessage(playerid, COLOR_LIGHTBLUE, "Info: ������ �������� �����.");
				return 1;
			}
			else//����� ���� �� �������� ������� �������� ����� Z �������
			{
				LadderPickupWaitTime[playerid] = GetTickCount();
			    TogglePlayerControllableEx(playerid, 1);
			    SendClientMessage(playerid, COLOR_LIGHTBLUE, "Info: ����� �������� �����.");
			    ApplyAnimation(playerid, "PED", "CLIMB_jump_B", 4.1, 0, 1, 1, 0, 0);
			    SetPlayerVelocity(playerid,
					LadderInfo[gLadderNumber[playerid]-1][Offset][1],
					LadderInfo[gLadderNumber[playerid]-1][Offset][2], 0.10);
			    gLadderNumber[playerid] = 0;
			    return 1;
			}
		}
		else if(UpDown > 0)
		{	//S+ALT
			GetPlayerPos(playerid, CurrentPos[0], CurrentPos[1], CurrentPos[2]);
			if(CurrentPos[2] > LadderInfo[gLadderNumber[playerid]-1][Postions][2])
			{   //���� �� �������� � �����, � ����� ���� ��� ���, �� ���� ������� ���������� ������
				//OnePlayAnim(playerid, "PED", "FALL_land", 4.1, 0, 0, 0, 0, 0);
				SetPlayerPos(playerid,
					LadderInfo[gLadderNumber[playerid]-1][Postions][0],
			   		LadderInfo[gLadderNumber[playerid]-1][Postions][1],
			    	(CurrentPos[2]-LadderInfo[gLadderNumber[playerid]-1][Offset][0]));
				ApplyAnimation(playerid, "MTB", "MTB_sprint", 35.1, 1, 0, 0, 0, 0);
				//"DOZER", "DOZER_Align_LHS"
				//OnePlayAnim(playerid, "DOZER", "DOZER_Align_RHS", 4.1, 0, 0, 0, 1, 0);
				//OnePlayAnim(playerid, "PED", "CLIMB_PUL", 4.1, 0, 0, 0, 1, 0);
				//OnePlayAnim(playerid, "PED", "FALL_glide", 4.1, 0, 0, 0, 1, 0);
   				//SendClientMessage(playerid, COLOR_LIGHTBLUE, "Info: ������ �������� ����.");
				return 1;
			}
			else
			{
				LadderPickupWaitTime[playerid] = GetTickCount();
			    SendClientMessage(playerid, COLOR_LIGHTBLUE, "Info: ����� �������� ����.");
			    SetPlayerPos(playerid,
					LadderInfo[gLadderNumber[playerid]-1][Postions][0],
			    	LadderInfo[gLadderNumber[playerid]-1][Postions][1],
			    	LadderInfo[gLadderNumber[playerid]-1][Postions][2]);
			    TogglePlayerControllableEx(playerid, 1);
			    gLadderNumber[playerid] = 0;
			    ApplyAnimation(playerid, "PED", "FALL_land", 4.1, 0, 1, 1, 0, 0);
			    return 1;
			}
 		}
		return 1;
}

//stock OnLadderPickUp(playerid, pickupid)
stock ladder_OnPlayerPickUp(playerid, pickupid)
{
	//----------------------------------------------------------------------
	//��� �������
	if((GetTickCount()-LadderPickupWaitTime[playerid]) < 5000) return 1;//���� ����� �������� ��� �� �����, �� �����
	if(gLadderNumber[playerid] >= 1) return 1;//���� ��� ����������� ��������, �� �����
	for(new l=0; l<STAIRWAYS; l++)
	{
	    if(pickupid == LadderInfo[l][Pickup][0] && pickupid != 0)
	    {
		   	TogglePlayerControllableEx(playerid, 0);
			SetPlayerPos(playerid, LadderInfo[l][Postions][0], LadderInfo[l][Postions][1], (LadderInfo[l][Postions][2]+0.25));
			SetPlayerFacingAngle(playerid, LadderInfo[l][Postions][3]);
			//OnePlayAnim(playerid, "MTB", "MTB_sprint", 4.1, 0, 1, 1, 1, 0);
			ApplyAnimation(playerid, "PED", "CLIMB_jump", 4.1, 0, 1, 1, 1, 0);
			//OnePlayAnim(playerid, "DOZER", "DOZER_Align_LHS", 4.1, 0, 1, 1, 0, 0);
			//OnePlayAnim(playerid, "TRUCK", "TRUCK_Align_LHS", 4.1, 0, 1, 1, 0, 0);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Info: ������� W + ��������� ALT ��� ������� �� ��������.");
			gLadderNumber[playerid] = l+1;
	        break;
		}
		else if(pickupid == LadderInfo[l][Pickup][1] && pickupid != 0)
  		{
			TogglePlayerControllableEx(playerid, 0);
			SetPlayerPos(playerid, LadderInfo[l][Postions][0], LadderInfo[l][Postions][1], (LadderInfo[l][Postions][4]-0.25));
			SetPlayerFacingAngle(playerid, LadderInfo[l][Postions][3]);
			//OnePlayAnim(playerid, "MTB", "MTB_sprint", 35.1, 1, 0, 0, 0, 0);
			ApplyAnimation(playerid, "PED", "FALL_glide", 4.1, 0, 1, 1, 1, 0);
			//OnePlayAnim(playerid, "DOZER", "DOZER_Align_RHS", 4.1, 1, 0, 0, 0, 0);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "Info: ������� S + ��������� ALT ��� ������ � ��������.");
			gLadderNumber[playerid] = l+1;
 		    break;
  		}
	}
	return 1;
}



