#ifndef xRSA_H
#define xRSA_H


class �ඨ��_����
{
public:
    �ඨ��_����();
    ~�ඨ��_����();
    unsigned long ����(const char *����, unsigned long ���ĳ���, char *����);
    unsigned long ����(const char *����, unsigned long ���ĳ���, char *����);

    /**
        ������������Կ
        ��������Կ�汾����Χ0-0xFF
        ����������˽Կ�͹�Կ
    */
    void ������Կ(const unsigned char ��Կ�汾);
    /**
        ��������Կ
        ������
        ��������ȡ��Կ����
            ��Կ:(7BEF 70B7 2C41 B9AD 6F1F 7193 FCEF 8605 8DD9 70B7 6DCD 6FFB 19B5)
            ˽Կ:(0B0F AF27 56D1 1CA5 73FF 6C9B FCEF 3C0D 2479 AF27 2525 1B83 E5CD)
    */
    unsigned short* ˽Կ();
    unsigned long ��Կ����();
    void ͬ��˽Կ();
    
    unsigned short ����(const unsigned short _in��ʼֵ, const unsigned char _in����=10);
    //�ж��Ƿ�������
    bool �Ƿ�����(const unsigned short _inֵ);
    /**
        ������������Կ
        ������[uint]��Կ {xxxx,y,xxxx}
             [uint]��С������������
        ��������ʼ����Կ��
    */
    void ��Կ(unsigned short *_in��Կ, unsigned int _in��С);
private:
    unsigned short *_��Կ_�˻�_xAx, *_˽Կ_�˻�_xAx, _��˽��_����, _�˻�_����;

    //unsigned int _�˻�; //n=p*q
    //unsigned int _˽Կ; //a���ڦ�(n)��ģ��Ԫ��
    //unsigned int _��Կ;

    void _�ͷ��ڴ�();

    bool _��Կ�Ѵ���(unsigned short _��Կ, unsigned short _˽Կ);
    
    //ģ�����㣬����ֵ x=a*b mod n
    //ģ�����㣬����ֵ x=base^pow mod n
    unsigned int PowMod(unsigned int _inֵ, unsigned int _in��Կ, unsigned int _in�˻�);
    
    //����d=gcd(a,b);�Ͷ�Ӧ�ڵ�ʽax+by=d�е�x,y
    int extend_gcd(int one, int two, int &x, int &y);
    //ax = 1(mod n) ��X
    int reverseMod(int one, int two);

    /* ================================
        ����: Rand
        ����: [in]seeds=������,���ֵ
        ����: ���������������
       ================================ */
    unsigned int time_stamp;
    unsigned int Rand(const unsigned int seeds);
};
#endif