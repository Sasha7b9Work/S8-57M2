#pragma once
#include "defines.h"


struct PSymbol
{
    uchar width;
    uchar bytes[8];
};

struct PTypeFont
{
    enum E
    {
        _5,
        _8,
        _UGO, //-V2573
        _UGO2, //-V2573
        _GOST28, //-V2573
        _GOST72bold,    // ������������ ��� ������ ��������� ����������� //-V2573
        _OMEGA72,       // ������������ � ����������� ��� ������ ����������� ��. ����� ������ ���� ������ //-V2573
        Count,
        None
    } value;
};

struct PFont
{
    int _height;
    PSymbol symbols[256];

public:
    // ������������� ������� �����. ����� ������������� ����� ������������ �������� Pop()
    static void Set(const PTypeFont::E typeFont);
    static PTypeFont::E Current();
    // ��������������� �����, ������ ������� ����� ��������� ������� SetCurrent()
    static void Pop();
    static bool IsBig();
    static uint8 GetWidth(uint8 symbol);
    static uint8 GetWidth(char symbol);
    static uint8 GetHeight();
    static bool RowNotEmpty(uint8 symbol, int row);
    static bool BitIsExist(uint8 symbol, int row, int bit);
    // ������������� ���������� ������ �������� ����� ���������.
    static void SetSpacing(int spacing);
};
