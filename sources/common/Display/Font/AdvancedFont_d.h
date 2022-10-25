#pragma once
#include "Font_d.h"



struct DAdvancedFont
{
    DAdvancedFont() {};
    // ���������� ����������� �����
    DAdvancedFont(DTypeFont::E type);
    // ���������� true, ���� � ������ row ���� �������
    bool RowNotEmpty(uint8 symbol, int row);
    // ���������� ������ �������
    uint8 GetWidth(uint8 symbol);
    // ���������� ������ �������
    uint8 GetHeight(uint8 symbol);
    // ���������� ������ ������ �������� �������
    uint8 GetHeight();

    bool BitIsExist(uint8 symbol, int row, int bit);

private:
    static DTypeFont::E currentType;
};
