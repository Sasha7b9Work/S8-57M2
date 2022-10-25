#pragma once


template<typename T>
class Queue
{
public:
    Queue();

    ~Queue();

    void Push(T elem);

    T Front();

    T Back();

    int Size() const;

    bool IsEmpty() const;

    T &operator[](int n);
private:

    void Destroy();
    // ��������� �� ������ ���������
    T *pointer;
    // ������ ������� ��������
    int iFront;
    // ������ �������� �� ���������
    int iBack;

    // ������ ����������� ���������� ������
    static const int sizeChunk = 128;
};
