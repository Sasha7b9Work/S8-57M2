#include "defines.h"
#include "Decoder_d.h"
#ifdef DEVICE
#include "Menu/Menu.h"
#endif
#include "Display/Display.h"
#include "Display/Painter.h"
#include "Keyboard/BufferButtons.h"
#include <cstdlib>


static int pointer = 0;
static pFuncBU8 curFunc = nullptr;  // ����������� �������
static int step = 0;                // ������� ���� ����������� �������
static const int SIZE_BUFFER = 1024;
static uint8 buffer[SIZE_BUFFER];


static void RunStep(uint8 data);

// ��� ������� ���� �������� ����� ���������� ���������� ����
static void FinishCommand();

// ��������� ��������� ������ � �������
static bool AddToConsole(uint8);

static bool ButtonPress(uint8);


void DDecoder::AddData(uint8 data)
{
    if (pointer < SIZE_BUFFER)
    {
        buffer[pointer++] = data;
    }
}


bool DDecoder::Update()
{
    bool result = (pointer != 0);

    if (pointer)
    {
        for (int i = 0; i < pointer; i++)
        {
            RunStep(buffer[i]);
        }
        pointer = 0;
    }

    return result;
}


static bool E(uint8)
{
    return true;
}


static void RunStep(uint8 data) //-V2506
{
    static const struct StructFunc
    {
        pFuncBU8 func;
        StructFunc(pFuncBU8 f) : func(f) {};
    }
    commands[Command::Count] =
    {
        E,              // None,
        ButtonPress,    // ButtonPress,
        E,              // Paint_BeginScene,
        E,              // Paint_EndScene,
        E,              // Paint_SetColor,
        E,              // Paint_FillRegion,
        E,              // Paint_DrawText,
        E,              // Paint_SetPalette,
        E,              // Paint_DrawRectangle,
        E,              // Paint_DrawVLine,
        E,              // Paint_DrawHLine,
        E,              // Paint_SetFont,
        E,              // Paint_SetPoint,
        E,              // Paint_DrawLine,
        E,              // Paint_TesterLines,
        E,              // Paint_DrawBigText,
        E,              // Screen
        E,              // Paint_VPointLine
        E,              // Paint_HPointLine
        E,              // Paint_SetMonoSpaceFont
        E,              // Paint_SetTextSpacing
        AddToConsole    // AddToConsole
    };

    if (step == 0)
    {
        if (data < Command::Count)
        {
            curFunc = commands[data].func;
        }
        else
        {
            FinishCommand();
            return;
        }
    }

    if (curFunc)
    {
        if (curFunc(data))
        {
            FinishCommand();
        }
        else
        {
            ++step;
        }
    }
    else
    {
        FinishCommand();
    }
}


static bool ButtonPress(uint8 data) //-V2506
{
    static Key::E button;
    if (step == 0)
    {
        return false;
    }
    else if (step == 1)
    {
        button = static_cast<Key::E>(data);
        return false;
    }
    else
    {
        BufferButtons::Push(KeyEvent(button, static_cast<TypePress::E>(data)));
    }

    return true;
}


static bool AddToConsole(uint8 data) //-V2506
{
    static char *text = nullptr;        // ����� ����� ��������� �������� ������

    static uint8 allSymbols = 0;        // ���������� �������� � ������ ��� ����� ������������ ����

    static uint8 recvSymbols = 0;       // ������� �������� ��� �������

    if (step == 0)
    {
        return false;
    }

    if (step == 1)
    {
        allSymbols = data;
        text = static_cast<char *>(std::malloc(allSymbols + 1U)); //-V2511
        recvSymbols = 0;
        return false;
    }

    text[recvSymbols++] = static_cast<char>(data); //-V2563

    if (recvSymbols == allSymbols)
    {
        std::free(text); //-V2511
    }

    return (recvSymbols == allSymbols);
}


static void FinishCommand()
{
    step = 0;
    curFunc = 0;
}


int DDecoder::BytesInBuffer()
{
    return pointer;
}


uint8 *DDecoder::Buffer()
{
    return buffer;
}
