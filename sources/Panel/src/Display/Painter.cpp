#include "defines.h"
#include "Painter.h"
#include "Display/Colors.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Utils/Math.h"
#include "Painter_common.h"


void Painter::DrawVPointLine(int x, int y, int delta, int count)
{
    for (int i = 0; i < count; i++)
    {
        SetPoint(x, y);
        y += delta;
    }
}


void Painter::DrawHPointLine(int x, int y, int delta, int count)
{
    for (int i = 0; i < count; i++)
    {
        SetPoint(x, y);
        x += delta;
    }
}


void Painter::DrawDashedHLine(int y, int x0, int x1, int deltaFill, int deltaEmpty, int deltaStart) //-V2506
{
    if (deltaStart < 0 || deltaStart >= (deltaFill + deltaEmpty))
    {
//        LOG_ERROR_TRACE("������������ �������� deltaStart = %d", deltaStart);
        return;
    }
    int x = x0;
    if (deltaStart != 0)                // ���� ����� ����� �������� �� � ������ ������
    {
        x += (deltaFill + deltaEmpty - deltaStart);
        if (deltaStart < deltaFill)     // ���� ������ ����� ���������� �� �����
        {
            DrawHLine(y, x0, x - 1);
        }
    }

    while (x < x1)
    {
        DrawHLine(y, x, x + deltaFill - 1);
        x += (deltaFill + deltaEmpty);
    }
}


void Painter::DrawDashedVLine(int x, int y0, int y1, int deltaFill, int deltaEmtpy, int deltaStart) //-V2506
{
    if (deltaStart < 0 || deltaStart >= (deltaFill + deltaEmtpy))
    {
//        LOG_ERROR_TRACE("������������ �������� deltaStart = %d", deltaStart);
        return;
    }
    int y = y0;
    if (deltaStart != 0)                 // ���� ����� ����� �������� �� � ������ ������
    {
        y += (deltaFill + deltaEmtpy - deltaStart);
        if (deltaStart < deltaFill)     // ���� ������ ����� ���������� �� �����
        {
            DrawVLine(x, y0, y - 1);
        }
    }

    while (y < y1)
    {
        DrawVLine(x, y, y + deltaFill - 1);
        y += (deltaFill + deltaEmtpy);
    }
}


Color Painter::GetColor()
{
    return currentColor;
}
