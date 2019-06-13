#pragma once

#define DIRECTINPUT_VERSION 0x0800  

#include <dinput.h>

#define Safe_Release(object) if((object) != NULL) { (object)->Release(); (object)=NULL; }

#define ITEMS_NUM   10


static LPDIRECTINPUT8			pInput = NULL;				//DirectInput����
BOOL CALLBACK Enum_Joystick(LPCDIDEVICEINSTANCE device_instance, LPVOID data);


class CInput
{
public:
	CInput(void);
public:
	~CInput(void);
private:
	bool bUseJoystick;

	
	LPDIRECTINPUTDEVICE8	pKeyboard;				//�����豸����
	LPDIRECTINPUTDEVICE8	pMouse;					//����豸����
	LPDIRECTINPUTDEVICE8	pJoystick;				//��Ϸ���豸����

	char keyBuffer[256];							// �������ݻ��� (immediate mode)
	char oldKeyBuffer[256];
	DIDEVICEOBJECTDATA mouseBuffer[ITEMS_NUM];    // ������ݻ��� (buffer mode)
	DIJOYSTATE2 joystickBuffer;                   // ��Ϸ�����ݻ��� (immediate mode)

	int mouseMoveX, mouseMoveY;    // mouse move coordinate
public:
	void CreateInput(HINSTANCE instance, HWND hwnd, int min = -100, int max = 100, 
		int nDeadZone = 20, bool bUseJoystick = false);

	bool ReadKeyboard();
	bool ReadMouse();
	bool ReadJoystick();
	bool IsLButtonPressed();
	bool IsRButtonPressed();    
	bool IsMButtonPressed();

	bool IsLButtonUp();
	bool IsRButtonUp();    
	bool IsMButtonUp();


	// �ж��Ƿ��а�������
	bool IsKeyPressed(int key);
	//�ж�ָ�����Ƿ�̧��
	bool IsKeyUp(int key);

	int GetMouseX() { return mouseMoveX; }
	int GetMouseY() { return mouseMoveY; }

	// �ж���Ϸ�˵�ĳ����ť�Ƿ���
	bool IsJSButtonPressed(int button)
	{
		return (joystickBuffer.rgbButtons[button] & 0x80) ? true : false;
	}
private:
	bool CreateDirectinput(HINSTANCE instance);							//����DirectInput����
	bool CreateKeyboard(HWND hwnd);										//���������豸����
	bool CreateMouse(HWND hwnd);										//��������豸����
	bool CreateJoystick(HWND hwnd, int min, int max, int nDeadZone);	//������Ϸ�˶���
	void ReleaseInput();												//�ͷ��������Ķ���

};
