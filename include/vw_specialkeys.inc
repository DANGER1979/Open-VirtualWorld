#define HOLDING(%0) ((newkeys & (%0)) == (%0))//�����
#define PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0))) //�����
#define RELEASED(%0) (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0))) //��������

/*Special Keys
On Foot:						Define				Gametext-Key on Foot	Value
#define KEY_FOOT_TAB			KEY_ACTION			~k~~PED_ANSWER_PHONE~	//1 - �������� (F)
#define KEY_FOOT_CROUCH			KEY_CROUCH			~k~~PED_DUCK~ 			//2 - ��������  (C)
#define KEY_FOOT_FIRE			KEY_FIRE			~k~~PED_FIREWEAPON~     //4 - ����� (Mouse1 - LButton)
													~k~~PED_FIREWEAPON_ALT~	//4 - ����� (Mouse1 - LButton)
#define KEY_FOOT_SPRINT			KEY_SPRINT 			~k~~PED_SPRINT~			//8 - ������ (Space)
#define KEY_FOOT_ENTER_VEHICLE	KEY_SECONDARY_ATTACK~k~~VEHICLE_ENTER_EXIT~ //16 - (F/Enter) ����� �� �� ������������ ������� F6
#define KEY_FOOT_JUMP			KEY_JUMP	 		~k~~PED_JUMPING~ 		//32 - ������ (Shift)
#define KEY_FOOT_AIM_WEAPON		KEY_HANDBRAKE		~k~~PED_LOCK_TARGET~	//128 - ������������ (Mouse2 - RButton)
#define KEY_FOOT_LOOK_BEHIND	KEY_LOOK_BEHIND		~k~~PED_LOOKBEHIND~ 		//512 - �������� ����� (Mouse3 - MButton)
#define KEY_FOOT_SNEAK_WALK		KEY_WALK 			~k~~SNEAK_ABOUT~ 		//1024 - ���� ����� (Alt)

#define 						KEY_YES				~k~~CONVERSATION_YES~ 	(65536) Y
#define 						KEY_CTRL_BACK		~k~~GROUP_CONTROL_BWD~ 	(262144) H
#define 						KEY_NO				~k~~CONVERSATION_NO~ 	(131072) N

#define KEY_FOOT_SPECIAL_LEFT	KEY_ANALOG_LEFT 	~k~~VEHICLE_LOOKLEFT~ 	//8192 - ������ �����  A (Numpad4)
#define KEY_FOOT_SPECIAL_RIGHT	KEY_ANALOG_RIGHT 	~k~~VEHICLE_LOOKRIGHT~ 	//16384 - ������ ������ D (Numpad6)
*/
#define KEY_FOOT_AIM_FIRE 													132//KEY_FIRE+KEY_HANDBRAKE RIGHT Ctrl.
#define KEY_FOOT_ENTER_VEHICLE_FIRE 										20
//��������: ��� ������ ������� ������ ����� � ������ ��� ����� ������
//*********************************************************************************************
/*Vehicle:							Define				Gametext-Key in Vehicle		Value
#define KEY_VEHICLE_SECONDARY_FIRE	KEY_ACTION			~k~~VEHICLE_FIREWEAPON~	 	//1 - ����� (Mouse1 - LButton)
#define KEY_VEHICLE_HORN			KEY_CROUCH			~k~~VEHICLE_HORN~ 			//2 - ����� (H) /SIRENS
#define KEY_VEHICLE_FIRE 			KEY_FIRE			~k~~VEHICLE_FIREWEAPON~		//4 - LEFT ALT(Sneak on foot for me)**
														~k~~VEHICLE_FIREWEAPON_ALT~
#define KEY_VEHICLE_FORWARD			KEY_SPRINT			~k~~VEHICLE_ACCELERATE~		//8 - ����� ������ (W)
#define KEY_VEHICLE_EXIT_VEHICLE	KEY_SECONDARY_ATTACK~k~~VEHICLE_FIREWEAPON_ALT~	//16 - ����� �� ������ (F)
#define KEY_VEHICLE_BRAKE_REVERSE	KEY_JUMP	 	 	~k~~VEHICLE_BRAKE~			//32 - ������ ������/����� ����� (S)
#define KEY_VEHICLE_LOOK_RIGHT		KEY_LOOK_RIGHT 		~k~~VEHICLE_LOOKRIGHT~ 		//64 - �������� ������ (E)
#define KEY_VEHICLE_HANDBRAKE		KEY_HANDBRAKE 		~k~~VEHICLE_HANDBRAKE~		//128 - ������ ������ (Space)
#define KEY_VEHICLE_LOOK_LEFT		KEY_LOOK_LEFT 		~k~~VEHICLE_LOOKLEFT~ 		//256 - �������� ����� (Q)
#define KEY_VEHICLE_SUB-MISSION		KEY_SUBMISSION 		~k~~TOGGLE_SUBMISSIONS~ 	//512 - ��������� (2)//PLUS(+) ON KEYPAD**
#define KEY_VEHICLE_LOOK_BEHIND		KEY_LOOK_BEHIND		~k~~VEHICLE_LOOKBEHIND~ 	320	//�������� �� ����//(Combo of LOOK RIGHT(64) and LOOK LEFT(256))

#define KEY_VEHICLE_SPECIAL_UP		KEY_ANALOG_UP 		~k~~VEHICLE_TURRETUP~ 		//2048 - ������ ����� (Numpad8)//DELETE & UP ARROW(8 ) ON KEYPAD*
#define KEY_VEHICLE_SPECIAL_DOWN	KEY_ANALOG_DOWN 	~k~~VEHICLE_TURRETDOWN~		//4096 - ������ ���� (Numpad2)//END & DOWN ARROW(2) ON KEYPAD*
#define KEY_VEHICLE_SPECIAL_LEFT	KEY_ANALOG_LEFT 	~k~~VEHICLE_TURRETLEFT~ 	//8192 - ������ �����  A (Numpad4)//LEFT ARROW(4) ON KEYPAD*
#define KEY_VEHICLE_SPECIAL_RIGHT	KEY_ANALOG_RIGHT	~k~~VEHICLE_TURRETRIGHT~	//16384 - ������ ������ D (Numpad6) RIGHT ARROW(6) ON KEYPAD*

#define 							KEY_YES				~k~~CONVERSATION_YES~ 		(65536)
#define 							KEY_NO				~k~~CONVERSATION_NO~ 		(131072)
#define 							KEY_CTRL_BACK		~k~~GROUP_CONTROL_BWD~ 		(262144) DEL || R || ������� ������ ����� �� ���� - ����. ������������
*/
//#define KEY_VEHICLE_ACCELERATE								132	//RIGHT Ctrl. / �����

#define KEY_FOOT_FIRE			"���"
#define KEY_FOOT_AIM_WEAPON		"���"
#define SNEAK_ABOUT 			"�.ALT"
#define PED_SPRINT 				"������"
#define VEHICLE_FIREWEAPON 		"�.ALT"
#define VEHICLE_HANDBRAKE 		"������"

#define VEHICLE_TURRETLEFT 		"��� 4"
#define VEHICLE_TURRETRIGHT 	"��� 6"
#define VEHICLE_TURRETUP 		"��� 8"
#define VEHICLE_TURRETDOWN 		"��� 2"

#define KEY_VEHICLE_AIM_FIRE 		5//KEY_ACTION+KEY_FIRE
#define KEY_VEHICLE_FIRE_LOOK_RIGHT 68//KEY_FIRE+KEY_LOOK_RIGHT
#define KEY_VEHICLE_FIRE_LOOK_LEFT 	260//KEY_FIRE+KEY_LOOK_LEFT
/*
Up/Down-Keys
Define 		Value 	Gametext-Key on Foot 	Gametext-Key in Vehicle
KEY_UP		-128	~k~~GO_FORWARD~			~k~~VEHICLE_STEERUP~
KEY_DOWN	128		~k~~GO_BACK~			~k~~VEHICLE_STEERDOWN~

Left/Right-Keys
Define		Value	Gametext-Key on Foot	Gametext-Key in Vehicle
KEY_LEFT	-128	~k~~GO_LEFT~			~k~~VEHICLE_STEERLEFT~
KEY_RIGHT	128		~k~~GO_RIGHT~			~k~~VEHICLE_STEERRIGHT~
*/
