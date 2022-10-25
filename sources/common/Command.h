#pragma once



struct Command
{           //  ��������               0  |     1       |     2      |      3      |     4        |      5       |   6    |         ������
    enum E                                              
    {                                                   
/* 00 */    None,                   //    |             |            |             |              |              |        |
/* 01 */    ButtonPress,            // 01 |   Item      | TypePress  |             |              |              |        |
/* 02 */    Paint_BeginScene,       // 02 |             |            |             |              |              |        |
/* 03 */    Paint_EndScene,         // 03 |             |            |             |              |              |        |
/* 04 */    Paint_SetColor,         // 04 |   Color     |            |             |              |              |        |
/* 05 */    Paint_FillRegion,       // 05 |   x[0:7]    |  x[8:15]   |      y      | width[0:7]   | width[8:15]  | height |
/* 06 */    Paint_DrawText,         // 06 |   x[0:7]    |  x[8:15]   |      y      | num symbols  |              |        |
/* 07 */    Paint_SetPalette,       // 07 | numColor    | value[0:7] | value[8:15] | value[16:23] | value[24:31] |        |
/* 08 */    Paint_DrawRectangle,    // 08 |   x[0:7]    |  x[8:15]   |      y      | width[0:7]   | width[8:15]  | height |
/* 09 */    Paint_DrawVLine,        // 09 |   x[0:7]    |  x[8:15]   |      y0     |      y1      |              |        |
/* 10 */    Paint_DrawHLine,        // 10 |    y        |  x0[0:7]   |   x0[8:15]  |   x1[0:7]    |  x1[8:15]    |        |
/* 11 */    Paint_SetFont,          // 11 | typeFont    |            |             |              |              |        |
/* 12 */    Paint_SetPoint,         // 12 |   x[0:7]    |  x[8:15]   |      y      |              |              |        |
/* 13 */    Paint_DrawLine,         // 13 |  x0[0:7]    | x0[8:15]   |     y0      |   x1[0:7]    |   x1[8:15]   |   y1   |
// � ������ ����� �������� ����� - ������� ��� == 0 - �����, 0 - �����
// ���� 1..3 - ����� ����
// � ������� ��������� �������� ���������� ���������� 0 - 1, 1 - 2, 2 - 4, 3 - 8, 4 - 16, 5 - 32, 6 - 64, 7 - 128, 8 - 256
/* 14 */    Paint_TesterLines,      // 14 |   mode      |   Color    | x[TESTER_NUM_POINTS]        y[TESTER_NUM_POINTS]         3 + 240 * 2 + 240 = 723
/* 15 */    Display_Brightness,     // 15 | �������
/* 16 */    Screen,                 // 16 |  numRow     |
/* 17 */    Paint_VPointLine,       // 17 |   x[0:7]    |  x[8:15]   |      y      |   delta      | count        |
/* 18 */    Paint_HPointLine,       // 18 |   x[0:7]    |  x[8:15]   |      y      |   delta      | count        |
/* 19 */    Paint_SetMinWidthFont,  // 19 |   width     |
/* 20 */    Paint_SetTextSpacing,   // 20 |   0 | 1     |
/* 21 */    AddToConsole,           // 21 | num symb    |  ..... symbols ....
/* 22 */    Count
    };
};


#define TESTER_NUM_POINTS 120


#define SIZE_STRING (320)


// ��������� ����� ��������� - ������� (1) ��� ������� (0)
#define BUILD_MODE(modeDraw, step, enumAverage) ((uint8)(((enumAverage) << 4) + ((step) << 1) + (modeDraw)))

#define EXTRACT_MODE_DRAW(x)    ((x) & 0x01)
#define EXTRACT_STEP(x)         (((x) >> 1) & 0x07)
#define EXTRACT_ENUM_AVERAGE(x) (((x) >> 4) & 0x0f)
