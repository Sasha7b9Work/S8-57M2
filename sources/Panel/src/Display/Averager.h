#pragma once


struct AveragerTester
{
    // ������ ���������� ���������. ���� �������� ���������� �� ����, ������� ��� ������� ��� ���������� ������, ���������� ���������.
    static void SetCount(int enumAverage);

    static void Process(const uint16 *x, const uint8 *y, int step);

    static uint16 *X();
    static uint8 *Y();
};
