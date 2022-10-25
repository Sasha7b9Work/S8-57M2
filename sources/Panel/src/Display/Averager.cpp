#include "defines.h"
#include "common/Command.h"
#include "Averager.h"
#include <cstring>



static int enumAve = 0;

struct StructX
{
    // ���������� ������ ������ X
    uint data[TESTER_NUM_POINTS];
    // ���������� ���������, ����������� � data
    int cout;
};

struct StructY
{
    // ���������� ������ ������ ����
    uint16 data[TESTER_NUM_POINTS];
    // ���������� ���������, ����������� � data
    int cout;
};

struct StructAVE
{
    StructX x;
    StructY y;
};

struct StructDATA
{
    uint16 x[TESTER_NUM_POINTS];
    uint8 y[TESTER_NUM_POINTS];
};

// ��� �������������� ������ - ����� ����������
static StructDATA data      __attribute__((section("CCM_DATA")));
// ������ ����������� ����������
static StructAVE ave[5]     __attribute__((section("CCM_DATA")));
// ���������� �������� ������
static StructDATA old[5]     __attribute__((section("CCM_DATA")));
// ������� �������� ������
static StructDATA current[5] __attribute__((section("CCM_DATA")));



static void Copy16(uint16 *dest, const uint16 *src)
{
    std::memcpy(dest, src, TESTER_NUM_POINTS * 2);
}


static void Copy8(uint8 *dest, const uint8 *src)
{
    std::memcpy(dest, src, TESTER_NUM_POINTS);
}


void AveragerTester::SetCount(int count)
{
    if (enumAve != count)
    {
        for (int step = 0; step < 5; step++)
        {
            for (int i = 0; i < TESTER_NUM_POINTS; i++)
            {
                ave[step].x.data[i] = 0;
                ave[step].y.data[i] = 0;
            }
        }
    }

    enumAve = count;
}


void AveragerTester::Process(const uint16 *dataX, const uint8 *dataY, int step) //-V2506
{
    Copy16(current[step].x, dataX);
    Copy8(current[step].y, dataY);

    if (enumAve == 0)
    {
        Copy16(data.x, dataX);
        Copy8(data.y, dataY);

        return;
    }

    uint *ave32 = &ave[step].x.data[0];

    for (int i = 0; i < TESTER_NUM_POINTS; i++)
    {
        ave32[i] = static_cast<uint>(ave32[i] - (ave32[i] >> enumAve) + dataX[i]); //-V2563
        data.x[i] = static_cast<uint16>(ave32[i] >> enumAve);
    }

    Copy16(old[step].x, current[step].x);
    Copy8(old[step].y, current[step].y);
    
    uint16 *ave16 = &ave[step].y.data[0];

    for (int i = 0; i < TESTER_NUM_POINTS; i++)
    {
        ave16[i] = static_cast<uint16>(ave16[i] - (ave16[i] >> enumAve) + dataY[i]); //-V2563
        data.y[i] = static_cast<uint8>(ave16[i] >> enumAve);
    }
}


uint16 *AveragerTester::X()
{
    return data.x;
}


uint8 *AveragerTester::Y()
{
    return data.y;
}
