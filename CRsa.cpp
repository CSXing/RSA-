
#include <windows.h>
#include <stdio.h>
#include <string>
#include <sys/timeb.h>
#include "cRsa.h"

int ������[98] = {
    0x0002,0x0003,0x0005,0x0007,0x000B,0x000D,0x0011,0x0013,0x0017,0x001D,
    0x001F,0x0025,0x0029,0x002B,0x002F,0x0035,0x003B,0x003D,0x0043,0x0047,
    0x0049,0x004F,0x0053,0x0059,0x0061,0x0065,0x0067,0x006B,0x006D,0x0071,
    0x007F,0x0083,0x008B,0x0095,0x0097,0x009D,0x00A3,0x00A7,0x00AD,0x00B5,
    0x00C1,0x00C5,0x00C7,0x00D3,0x00DF,0x00E5,0x00E9,0x00F1,0x00FB, //49
    0x7FED,0x5551,0x332F,0x2485,0x1741,0x13AF,0x0F0D,0x0D79,0x0B1B,0x08CB,
    0x0841,0x06DF,0x063D,0x05F3,0x0565,0x04CF,0x0455,0x042D,0x03D1,0x0397,
    0x0377,0x033D,0x0313,0x02DD,0x02A1,0x0287,0x0277,0x025F,0x0259,0x0241,
    0x01FD,0x01F3,0x01D3,0x01B7,0x01B1,0x0199,0x0191,0x0185,0x0175,0x0167,
    0x0151,0x014B,0x013D,0x0133,0x0125,0x011B,0x0119,0x010F,0x0101, //98
};


�ඨ��_����::�ඨ��_����() {
    this->_��˽��_���� = 9;
    this->_�˻�_���� = (this->_��˽��_����-1) / 2;
    this->_��Կ_�˻�_xAx = this->_˽Կ_�˻�_xAx = 0;
}
�ඨ��_����::~�ඨ��_����() {
    this->_�ͷ��ڴ�();
}
unsigned long �ඨ��_����::����(const char *����, unsigned long ���ĳ���, char *����) {
    if (���� == 0) { return 0; }
    if (���ĳ��� >= 0xFFFFFFL) { return 0; }

    int iK=0;
    unsigned long i = 0, j = 0, id = 0, iNum = 0, iN = 0;
    unsigned char _ucOne = 0;
    //����֯�����Ƶ���Ӣ���ַ����ձ�
    unsigned long _���ձ��� = (���ĳ���+7)/8;
    ����[0] = (_���ձ��� & 0xFF);
    ����[1] = (_���ձ��� & 0xFF00)/0x100;
    ����[2] = (_���ձ��� & 0xFF0000)/0x10000;
    
    //����_���ձ�ֻ��¼�����ַ�λ��
    i=0;
    memset(&����[3], 0, _���ձ���);
    while (i < ���ĳ���)
    {
        _ucOne = (unsigned char)����[i];
        if (_ucOne & 0x80) { //����
            id = i/8+3;
            ����[id] += 1<<(7-(i%8));
        }
        i++;
    }
    
    iK=0; i=0; id=_���ձ���+3;
    while (i < ���ĳ���)
    {
        _ucOne = (unsigned char)����[i++];
        if ((_ucOne & 0x80)) {
            iNum = _ucOne;
        } else {
            iNum = _ucOne * 0x100;
            if (i < ���ĳ���){
                _ucOne = (unsigned char)����[i++];
                iNum += _ucOne;
            }
        }
            iN = PowMod(iNum, this->_��Կ_�˻�_xAx[iK], this->_��Կ_�˻�_xAx[this->_�˻�_����]);
            ����[id++] = (unsigned char)( iN & 0xFF);
            ����[id++] = (unsigned char)((iN & 0xFF00) / 0x100);
        iK++;
        if(iK==this->_�˻�_����) {
            iK++;
        } else if(iK>=this->_��˽��_����) {
            iK=0;
        }
    }
    //FILE *hFiles = fopen("_����.txt", "wb");
    //    fwrite(����, sizeof(char), id, hFiles);
    //fclose(hFiles);
    return id;
}

unsigned long �ඨ��_����::����(const char *����, unsigned long ���ĳ���, char *����) {
    if (���� == 0) { return 0; }

    int iK=0;
    unsigned long i = 0, j = 0, id = 0, iNum = 0, iN = 0;
    unsigned char _ucOne = 0;
    id = 3 + (unsigned char)����[0] + (unsigned char)����[1]*0x100L + (unsigned char)����[2]*0x10000L;
    
    while (id < ���ĳ���)
    {
        iN = (unsigned char)����[id++];
        iN+= (unsigned char)����[id++] * 0x100;
            iNum = PowMod(iN, this->_˽Կ_�˻�_xAx[iK], this->_˽Կ_�˻�_xAx[this->_�˻�_����]);
            if ((iNum & 0x80)) {
                _ucOne = (unsigned char)((iNum&0x7F00)/0x100);
                if (_ucOne==0) {
                    int _id=����[i/8+3]; j=1<<(7-(i%8));
                    if ((_id & j)==0) {
                        ����[i++] = 0;
                    }
                } else {
                    ����[i++] = _ucOne;
                }
                ����[i++] = (unsigned char)(iNum&0xFF);
            } else {
                ����[i++] = (unsigned char)((iNum&0x7F00)/0x100);
                ����[i++] = (unsigned char)(iNum&0xFF);
            }
        iK++;
        if(iK==this->_�˻�_����) {
            iK++;
        } else if(iK>=this->_��˽��_����) {
            iK=0;
        }
    }
    //FILE *hFiles = fopen("_����.txt", "wb");
    //    fwrite(����, sizeof(char), i-1, hFiles);
    //fclose(hFiles);
    return i-1;
}

bool �ඨ��_����::_��Կ�Ѵ���(unsigned short _��Կ, unsigned short _˽Կ) {
    int seqId=0, revId = this->_��˽��_����-1, halfCount = this->_��˽��_����/2+1;
    for (int seqId=0; seqId<halfCount; seqId++)
    {
        if (this->_��Կ_�˻�_xAx[seqId] == _��Կ || this->_˽Կ_�˻�_xAx[seqId] == _˽Կ) {
            return true;
        }
        if (this->_��Կ_�˻�_xAx[revId-seqId] == _��Կ || this->_˽Կ_�˻�_xAx[revId-seqId] == _˽Կ) {
            return true;
        }
    }
    return false;
}

/**
    ������������Կ
    ��������Կ�汾����Χ0-0xFF
    ����������˽Կ�͹�Կ
*/
void �ඨ��_����::������Կ(const unsigned char ��Կ�汾)
{
    const unsigned char _pqMax=98;
    const unsigned char _pqHalf=_pqMax/2;
    unsigned char pid = this->Rand(_pqHalf) & 0xFF;
    if (1<=��Կ�汾) pid = ((int)(_pqHalf * ��Կ�汾*0.75f) % (_pqHalf)) & 0xFF;
    unsigned char qid = (this->Rand(_pqHalf)+_pqHalf) & 0xFF;
    unsigned short p = ������[pid], q = ������[qid];
    unsigned long i=0, id = 0, _��Կ = 0, _˽Կ = 0, _�˻� = p * q;
    while(_�˻�>0xFFFF || _�˻�<0x8000 || p==q) { qid = this->Rand(_pqHalf)+_pqHalf; q = ������[qid]; _�˻� = p * q; }
    //�ͷ��ڴ�
    this->_�ͷ��ڴ�();
    //���ݰ汾������Կ��
    this->_��˽��_���� = 256;
    this->_�˻�_���� = (this->_��˽��_����-1+(this->_��˽��_����%2))*0.334f;
    unsigned short _���� = sizeof(unsigned short)*this->_��˽��_����+1;
    this->_��Կ_�˻�_xAx = (unsigned short*)malloc(_����);
    this->_˽Կ_�˻�_xAx = (unsigned short*)malloc(_����);
    memset(this->_��Կ_�˻�_xAx, 0, _����);
    memset(this->_˽Կ_�˻�_xAx, 0, _����);
    //������Կ
    for (i=0; i<this->_��˽��_����; i++)
    {
        _��Կ = this->����(this->Rand(0xEFFE) + 0x1001);
        _˽Կ = reverseMod(_��Կ, (p - 1)*(q - 1));
        while (this->_��Կ�Ѵ���(_��Կ,_˽Կ)) {
	        _��Կ = this->����(this->Rand(0xEFFE) + 0x1001);
	        _˽Կ = reverseMod(_��Կ, (p - 1)*(q - 1));
        }
        this->_��Կ_�˻�_xAx[id] = _��Կ;
        this->_˽Կ_�˻�_xAx[id] = _˽Կ;
        id++;
    }
    this->_��Կ_�˻�_xAx[this->_�˻�_����] = this->_˽Կ_�˻�_xAx[this->_�˻�_����] = _�˻�;
}
    
/**
    ��������Կ
    ������
    ��������ȡ��Կ����
        ��Կ:(7BEF 70B7 2C41 B9AD 6F1F 7193 FCEF 8605 8DD9 70B7 6DCD 6FFB 19B5)
        ˽Կ:(0B0F AF27 56D1 1CA5 73FF 6C9B FCEF 3C0D 2479 AF27 2525 1B83 E5CD)
*/
unsigned long �ඨ��_����::��Կ����()
{
    return sizeof(unsigned short)*this->_��˽��_����;
}
unsigned short* �ඨ��_����::˽Կ()
{
    return this->_˽Կ_�˻�_xAx;
}

void �ඨ��_����::ͬ��˽Կ()
{
    unsigned short _���� = sizeof(unsigned short)*this->_��˽��_����+1;
    memset(&this->_˽Կ_�˻�_xAx[0], 0, _����);
    memcpy(&this->_˽Կ_�˻�_xAx[0], &this->_��Կ_�˻�_xAx[0], _����);
}

unsigned short �ඨ��_����::����(const unsigned short _in��ʼֵ, const unsigned char _in����)
{
    for (int i=0; i<_in����; i++)
    {
        if (this->�Ƿ�����(_in��ʼֵ+i)) return _in��ʼֵ+i;
    }
    return 0;
}
//�ж��Ƿ�������
bool �ඨ��_����::�Ƿ�����(const unsigned short _inֵ)
{
	if (_inֵ == 2 || _inֵ == 3) return true;
    if (_inֵ <= 1 || (_inֵ % 6 != 1 && _inֵ % 6 != 5)) return false;

	unsigned short i, halfNum = (int)sqrt((double)_inֵ);
	for (i = 5; i <= halfNum; i += 6)
		if (_inֵ % i == 0 || _inֵ % (i + 2) == 0)
			return false;
	return true;
}


//����d=gcd(a,b);�Ͷ�Ӧ�ڵ�ʽax+by=d�е�x,y
int �ඨ��_����::extend_gcd(int one, int two, int &x, int &y) {
    if (one == 0 && two == 0) return -1;//�����Լ��
    if (two == 0) {
        x = 1; y = 0; return one;
    }
    int d = extend_gcd(two, one%two, y, x);
    y -= one / two * x;
    return d;
}
//ax = 1(mod n) ��X
int �ඨ��_����::reverseMod(int one, int two) {
    int x, y;
    int d = extend_gcd(one, two, x, y);
    if (d == 1)
        return (x%two + two) % two;
    else return -1;
}

/* ================================
    ����: Rand
    ����: [in]seeds=������,���ֵ
    ����: ���������������
    ================================ */
unsigned int �ඨ��_����::Rand(const unsigned int seeds)
{
    if (seeds == 0) return seeds;
    struct timeb timeSeed;
    ftime(&timeSeed);
    unsigned int _timestamp = ((timeSeed.time & 0xFFFFFFFFUL) * 0x10000UL + timeSeed.millitm) & 0xFFFFFFFFUL;
    if (_timestamp - time_stamp > 100) {
        time_stamp = _timestamp;
        srand(time_stamp); // milli time
    }
    unsigned int _randVal = rand();
    return _randVal % seeds;
}

/**
    ������������Կ
    ������[uint]��Կ {xxxx,y,xxxx}
            [uint]��С������������
    ��������ʼ����Կ��
*/
void �ඨ��_����::��Կ(unsigned short *_in��Կ, unsigned int _in��С)
{
    this->_�ͷ��ڴ�();
    this->_��˽��_���� = _in��С;
    this->_�˻�_���� = (this->_��˽��_����-1+(this->_��˽��_����%2))*0.334f;

    unsigned short _���� = sizeof(unsigned short)*this->_��˽��_����+1;
    this->_��Կ_�˻�_xAx = (unsigned short*)malloc(_����);
    this->_˽Կ_�˻�_xAx = (unsigned short*)malloc(_����);
    memcpy(&this->_��Կ_�˻�_xAx[0], &_in��Կ[0], _����);
    memcpy(&this->_˽Կ_�˻�_xAx[0], &_in��Կ[0], _����);
}

void �ඨ��_����::_�ͷ��ڴ�() {
    if (this->_��Կ_�˻�_xAx) { free(this->_��Կ_�˻�_xAx); this->_��Կ_�˻�_xAx=0; }
    if (this->_˽Կ_�˻�_xAx) { free(this->_˽Կ_�˻�_xAx); this->_˽Կ_�˻�_xAx=0; }
}

//ģ�����㣬����ֵ x=a*b mod n
//ģ�����㣬����ֵ x=base^pow mod n
unsigned int �ඨ��_����::PowMod(unsigned int _inֵ, unsigned int _in��Կ, unsigned int _in�˻�)
{
    if (_inֵ == 0)
        return 0;
    else if (_in��Կ == 1)
        return _inֵ % _in�˻�;
    else
        return (PowMod(_inֵ, _in��Կ / 2, _in�˻�)*PowMod(_inֵ, _in��Կ - _in��Կ / 2, _in�˻�)) % _in�˻�;
}