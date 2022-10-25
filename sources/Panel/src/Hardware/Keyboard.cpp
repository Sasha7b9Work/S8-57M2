#include "defines.h"
#include "common/Command.h"
#include "Hardware/Keyboard.h"
#include "Hardware/HAL/HAL.h"


#define SL0 GPIO_PIN_14
#define SL1 GPIO_PIN_13
#define SL2 GPIO_PIN_15
#define SL3 GPIO_PIN_12
#define SL4 GPIO_PIN_8
#define SL5 GPIO_PIN_8
#define SL6 GPIO_PIN_9
#define SL7 GPIO_PIN_9

#define RL0 GPIO_PIN_13
#define RL1 GPIO_PIN_8
#define RL2 GPIO_PIN_9
#define RL3 GPIO_PIN_11
#define RL4 GPIO_PIN_10
#define RL5 GPIO_PIN_12


static const Control controls[Keyboard::NUM_RL][Keyboard::NUM_SL] =
{ //          SL0/SL6                SL1/SL7                  SL2                     SL3                     SL4                     SL5              
    {Control::K_None,       Control::B_3,            Control::B_Down,        Control::K_None,        Control::B_TrigLevLess, Control::B_TrigLevMore,
     Control::B_RangeLessB, Control::B_RShiftMoreB},                                                                                            // RL0

    {Control::B_1,          Control::B_4,            Control::B_Right,       Control::B_Enter,       Control::K_Start,       Control::K_Trig,
     Control::B_RangeMoreB, Control::B_RShiftLessB},                                                                                            // RL1

    {Control::B_2,          Control::B_5,            Control::B_Up,          Control::B_Left,        Control::K_None,        Control::K_None,
     Control::K_None,       Control::K_ChannelB},                                                                                               // RL2

    {Control::K_Function,   Control::K_Service,      Control::B_RangeLessA,  Control::K_RangeMoreA,  Control::K_None,        Control::B_TShiftLess,
     Control::K_None,       Control::K_None},                                                                                                   // RL3
                                                     
    {Control::K_Measures,   Control::K_None,         Control::K_ChannelA,    Control::K_None,        Control::B_TBaseMore,   Control::B_TShiftMore,
     Control::K_None,       Control::K_None},                                                                                                   // RL4
                                                     
    {Control::K_Memory,     Control::K_Display,      Control::B_RShiftMoreA, Control::B_RShiftLessA, Control::K_Time,        Control::B_TBaseLess,
     Control::K_None,       Control::K_None}                                                                                                    // RL5
};               


static uint16 sls[Keyboard::NUM_SL]             = {SL0,   SL1,   SL2,   SL3,   SL4,   SL5,   SL6,   SL7};
static GPIO_TypeDef* slsPorts[Keyboard::NUM_SL] = {GPIOB, GPIOB, GPIOB, GPIOB, GPIOD, GPIOC, GPIOD, GPIOC}; //-V2571

static uint16 rls[Keyboard::NUM_RL]             = {RL0,   RL1,   RL2,   RL3,   RL4,   RL5};
static GPIO_TypeDef* rlsPorts[Keyboard::NUM_RL] = {GPIOD, GPIOA, GPIOA, GPIOD, GPIOA, GPIOD}; //-V2571

#define SET_SL(n)   HAL_GPIO_WritePin(slsPorts[n], sls[n], GPIO_PIN_SET);
#define SET_ALL_SL  HAL_GPIO_WritePin(GPIOB, SL0 | SL1 | SL2 | SL3, GPIO_PIN_SET);  \
                    HAL_GPIO_WritePin(GPIOC, SL5 | SL7 , GPIO_PIN_SET);             \
                    HAL_GPIO_WritePin(GPIOD, SL4 | SL6, GPIO_PIN_SET);
#define RESET_SL(n) HAL_GPIO_WritePin(slsPorts[n], sls[n], GPIO_PIN_RESET);
#define READ_RL(n)  HAL_GPIO_ReadPin(rlsPorts[n], rls[n]);

#define BUTTON_IS_PRESS(state) ((state) == 0)

// ����� ���������� ����������� �����
static uint prevRepeat = 0;
static uint prevPause = 0;


static void SendCommand(Control control, Control::Action::E action);

static uint TimeBetweenRepeats(uint time);
// ��� ����������� ������� ������ ���� ������������ ����� �������
static uint timePress[Keyboard::NUM_RL][Keyboard::NUM_SL];
// ������������� � true �������� ��������, ��� ��������� ����-���� ���������� � � ��������� ������ �� ���������� (����� �� ���� ������
// ������������ ���� Long
static bool alreadyLong[Keyboard::NUM_RL][Keyboard::NUM_SL];

static bool init;



void Keyboard::Init()
{
    for (int i = 0; i < NUM_RL; ++i)
    {
        for (int j = 0; j < NUM_SL; ++j)
        {
            timePress[i][j] = 0;
        }
    }

    GPIO_InitTypeDef isGPIO;

    // ����� �����
    isGPIO.Pin = RL1 | RL2 | RL4;
    isGPIO.Mode = GPIO_MODE_INPUT;
    isGPIO.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &isGPIO); //-V2571

    isGPIO.Pin = RL0 | RL5 | RL3;
    HAL_GPIO_Init(GPIOD, &isGPIO); //-V2571

    // ����� ������
    isGPIO.Pin = SL0 | SL1 | SL2 | SL3;
    isGPIO.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(GPIOB, &isGPIO); //-V2571

    isGPIO.Pin = SL5 | SL7;
    HAL_GPIO_Init(GPIOC, &isGPIO); //-V2571

    isGPIO.Pin = SL4 | SL6;
    HAL_GPIO_Init(GPIOD, &isGPIO); //-V2571

    SET_ALL_SL; //-V2571

    init = true;
}


void Keyboard::Update() //-V2506
{
    if (!init)
    {
        return;
    }

    uint time = HAL_GetTick();

    for (int sl = 0; sl < NUM_SL; ++sl)
    {
        RESET_SL(sl);

        for (int rl = 0; rl < NUM_RL; ++rl)
        {
            uint state = READ_RL(rl);

            Control control = controls[rl][sl];

            if (control != Control::K_None)
            {
                if (timePress[rl][sl])                      // ���� ������� ��������� � ������� ���������
                {
                    if (time - timePress[rl][sl] > 100)     // ���� ������ ����� 100 �� � ������� �������
                    {
                        if (!BUTTON_IS_PRESS(state))        // ���� ������ ������ ��������� � ������� ���������
                        {
                            timePress[rl][sl] = 0;
                            if (!alreadyLong[rl][sl])
                            {
                                SendCommand(controls[rl][sl], Control::Action::Release);
                            }
                            alreadyLong[rl][sl] = false;
                            prevRepeat = 0;
                        }
                        else if(control.IsRepeatable() && !alreadyLong[rl][sl])  // � ����� ��� �������� � ������� ��������� - ������������ ����������
                        {
                            if (prevRepeat == 0)
                            {
                                prevRepeat = time;
                                prevPause = 100;
                            }
                            
                            if (prevRepeat + prevPause < time)
                            {
                                prevPause = TimeBetweenRepeats(prevPause);
                                prevRepeat = time;
                                SendCommand(controls[rl][sl], Control::Action::Repeat);
                            }
                        }
                        else if(time - timePress[rl][sl] > 500 && !alreadyLong[rl][sl])
                        {
                            SendCommand(controls[rl][sl], Control::Action::Long);
                            alreadyLong[rl][sl] = true;
                        }
                        else
                        {
                            // ��������� �� ������������
                        }
                    }
                }
                else if (BUTTON_IS_PRESS(state) && !alreadyLong[rl][sl])
                {
                    timePress[rl][sl] = time;
                    SendCommand(controls[rl][sl], Control::Action::Press);
                    prevRepeat = 0;
                }
                else
                {
                    // ��������� �� ������������
                }
            }
        }

        SET_ALL_SL; //-V2571
    }

    SET_ALL_SL; //-V2571
}


static void SendCommand(Control control, Control::Action::E action)
{
    uint8 data[3] =
    {
        Command::ButtonPress,
        static_cast<uint8>(control),
        static_cast<uint8>(action)
    };

    HAL_BUS::SendToDevice(data, 3);
}   


const char *Keyboard::ControlName(Control control)
{
    static const char *names[Control::Count] =
    {
        "None",
        "�������",
        "�����",
        "������",
        "������",
        "����� 1",
        "����� 2",
        "���������",
        "����/����",
        "�����",
        "�������",
        "Range 1 ������",
        "Range 1 ������",
        "RShift 1 ������",
        "RShift 1 ������",
        "Range 2 ������",
        "Range 2 ������",
        "RShift 2 ������",
        "RShift 2 ������",
        "TBase ������",
        "TBase ������",
        "TShift ������",
        "TShift ������",
        "����� ������",
        "����� ������",
        "�����",
        "������",
        "�����",
        "����",
        "����",
        "1",
        "2",
        "3",
        "4",
        "5"
    };

    return names[control];
}


bool Control::IsRepeatable() const
{
    return value == B_RShiftLessA ||
        value == B_RShiftMoreA ||
        value == B_RShiftLessB ||
        value == B_RShiftMoreB ||
        value == B_TShiftLess ||
        value == B_TShiftMore ||
        value == B_TrigLevLess ||
        value == B_TrigLevMore ||
        value == B_Left ||
        value == B_Right ||
        value == B_Down ||
        value == B_Up;
}


static uint TimeBetweenRepeats(uint prev)
{
    uint retValue = static_cast<uint>(static_cast<float>(prev) / 1.1F);

    if (retValue < 10)
    {
        retValue = 10;
    }

    return retValue;
}
