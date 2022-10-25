#pragma once
#include "common/Command.h"



typedef bool(*pFuncBU8)(uint8);


class DDecoder
{
public:

    static void AddData(uint8 data);

    // ���������� true, ���� ���� ���������
    static bool Update();

    // ���������� ������ ������, ���������� ���������
    static int BytesInBuffer();

    // ���������� ��������� �� ������ ������� �������������� ������
    static uint8 *Buffer();
};
