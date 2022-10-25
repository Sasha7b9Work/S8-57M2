#pragma once


#define ERROR_HANDLER()  ::HAL::ErrorHandler(__FILE__, __LINE__)


struct HAL
{
    static void ErrorHandler(const char *, int);
};


// ������������ ��� ���������� �������� �������
struct HAL_DAC2
{
    static void Init();
    // �������� value �� 0 �� 100
    static void SetValue(int value);
};


struct HAL_BUS
{
    static void Init();

    static void SendToDevice(uint8 *data, uint size);

    static void Update();
};
