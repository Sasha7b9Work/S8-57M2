#pragma once



class Message
{
public:
    explicit Message();
    explicit Message(uint size, uint8);
    explicit Message(uint size, uint8, uint8);
    explicit Message(uint size, uint8, uint16, uint8);
    explicit Message(uint size, uint8, uint8, uint);
    explicit Message(uint size, uint8, uint16, uint8, uint8);
    explicit Message(uint8, uint8, uint8, uint8 *, uint16, uint8 *, uint16);
    explicit Message(uint size, uint8, uint16, uint8, uint16, uint8);
    explicit Message(uint8, uint16, uint8, char *);
    ~Message();

    uint Size() const { return allocated; }

    uint8 *Data(int pos = 0) { return data + pos; }	// -V104 //-V2563

    class Create
    {
    public:

        static void DrawHLine(Message &message, int y, int x0, int x1);

        static void DrawRectangle(Message &message, int x, int y, int width, int height);
    };

private:

    // �������� ���� ����
    void PutByte(uint8);
    
    // �������� �������
    void PutHalfWord(uint16);
    
    // �������� �����
    void PutWord(uint);
    
    // �������� ������
    bool Allocate(uint size);
    
    // ���������� ������� ������
    void Free();
    
    // ������� �������� ������
    uint allocated;
    
    // ������� ��������� (��������� PutX())
    uint used;
    
    // ��������� �� ���������� ������� ������
    uint8 *data;
};
