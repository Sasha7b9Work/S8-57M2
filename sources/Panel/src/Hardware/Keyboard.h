#pragma once
#include "Controls.h"
#include "defines.h"


struct Keyboard
{
    static void Init();

    static void Update();
    // ���������� ������� RL ��� ������ ����������
    static const int NUM_RL = 6;
    // ���������� ������� SL ��� ������ ����������
    static const int NUM_SL = 8;
    // ��������� ��� ������ ����������
    static const char *ControlName(Control control);
};
