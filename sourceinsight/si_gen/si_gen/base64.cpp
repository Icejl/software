
#include "pch.h"


// ����1��base64���룬���ر����Դ�ַ����ַ�������-1�������
static int base64_string(const unsigned char* src, size_t srclen, unsigned char* dest, size_t destlen, unsigned char* base64, int index)
{
    if (NULL == src || NULL == dest || NULL == base64 || index < 0)
        return -1;
    if (srclen <= 0 || destlen < 5) {
        return -1; // // dest����1������β��0
    }

    unsigned char one;
    unsigned char two;
    unsigned char thr;
    unsigned char fou;

    if (srclen >= 3)
    {
        one = src[0] >> 2;
        two = ((src[0] & 0x03) << 4) | (src[1] >> 4);
        thr = ((src[1] & 0x0F) << 2) | (src[2] >> 6);
        fou = src[2] & 0x3F;

        *(dest + index++) = base64[one];
        *(dest + index++) = base64[two];
        *(dest + index++) = base64[thr];
        *(dest + index) = base64[fou];
    }
    else if (srclen == 2)
    {
        one = src[0] >> 2;
        two = ((src[0] & 0x03) << 4) | (src[1] >> 4);
        thr = (src[1] & 0x0F) << 2;

        *(dest + index++) = base64[one];
        *(dest + index++) = base64[two];
        *(dest + index++) = base64[thr];
        *(dest + index) = '=';
    }
    else if (srclen == 1)
    {
        one = src[0] >> 2;
        two = (src[0] & 0x03) << 4;

        *(dest + index++) = base64[one];
        *(dest + index++) = base64[two];
        *(dest + index++) = '=';
        *(dest + index) = '=';
    }

    return srclen >= 3 ? 3 : srclen;
}

// base64���룬�����dest�ռ����>=src * 4 / 3 + 3���ܱ�֤��ȫ
void base64_encode(const unsigned char* src, int srclen, unsigned char* dest, int destlen)
{
    if (NULL == src || srclen == 0 || NULL == dest || destlen < srclen * 4 / 3 + 3)
        return;

    unsigned char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int index = 0;
    while (srclen > 0)
    {
        int step = base64_string(src, srclen, dest, destlen, base64, index);
        if (step == -1) {
            break;
        }

        destlen -= 4; // ÿ���õ�4�ֽ�
        index += 4; // ��ô����ÿ�α�Ȼ����4

        srclen -= step; // ÿ�μ���3�ֽڻ�2����1��2��1���ǽ�βʣ���ַ�����
        src += step; // ��ôÿ������3����2����1
    }

    *(dest + index) = '\0';
}


// ������base64����ĺ���
// ������base64����ĺ���

void create_array(unsigned char* array)
{
    int index = 0;
    for (index = 0; index < 123; index += 1)
    {
        if (index == 0x2B)
        {
            *(array + index) = 0x3E;
        }
        else if (index == 0x2F)
        {
            *(array + index) = 0x3F;
        }
        else if (index >= 0x30 && index <= 0x39)
        {
            *(array + index) = 0x34 + index - 0x30;
        }
        else if (index == 0x3D)
        {
            /* �����ַ�'='��Ҳ�ɺϲ���else��� */
            *(array + index) = 0x00;
        }
        else if (index >= 0x41 && index <= 0x5A)
        {
            *(array + index) = index - 0x41;
        }
        else if (index >= 0x61 && index <= 0x7A) {
            *(array + index) = 0x1A + index - 0x61;
        }
        else
        {
            *(array + index) = 0x00;
        }
    }

    *(array + 123) = '\0';
}

int decode_string(const unsigned char* src, size_t srclen, unsigned char* dest, size_t destlen, unsigned char* array, int index)
{
    if (NULL == src || NULL == dest || NULL == array || index < 0)
        return -1;
    if (srclen < 4 || destlen < 4) {
        return -1; // // dest����1������β��0
    }

    int step = 0;

    unsigned char one;
    unsigned char two;
    unsigned char thr;
    if (src[3] == '=' && src[2] == '=')
    {
        one = (array[src[0]] << 2) | (array[src[1]] >> 4);
        *(dest + index) = one;

        step = 1;
    }
    else if (src[3] == '=')
    {
        one = (array[src[0]] << 2) | (array[src[1]] >> 4);
        two = ((array[src[1]] & 0x0F) << 4) | (array[src[2]] >> 2);

        *(dest + index++) = one;
        *(dest + index) = two;

        step = 2;
    }
    else
    {
        one = (array[src[0]] << 2) | (array[src[1]] >> 4);
        two = ((array[src[1]] & 0x0F) << 4) | (array[src[2]] >> 2);
        thr = (array[src[2]] << 6) | array[src[3]];

        *(dest + index++) = one;
        *(dest + index++) = two;
        *(dest + index) = thr;

        step = 3;
    }

    return step;
}

// base64���룬�����dest�ռ�=src�ռ� * 3 / 4 + 4��������Ҫ��
void base64_decode(const unsigned char* src, size_t srclen, unsigned char* dest, size_t destlen)
{
    if (NULL == src || NULL == dest || srclen < 0 || destlen < srclen * 3 / 4 + 4)
        return;

    static unsigned char array[124] = { '\0' };
    if (array[0x2B] == '\0') { // ��Ҫ��ʼ��
        create_array(array);
    }

    int index = 0;
    while (srclen)
    {
        int step = decode_string(src, srclen, dest, destlen, array, index);
        if (step == -1) {
            break;
        }

        srclen -= 4; // ÿ�ν���4���ֽ�
        src += 4; // Դ�ַ���ǰ��4�ֽ�

        destlen -= step; // ÿ������step��������3�ֽڣ�Ҳ������2�ֽڻ�1�ֽڣ�
        index += step; // Ŀ���ַ���ÿ��ǰ��step�ֽ�
    }

    *(dest + index) = '\0';
}

// �����ǵ�����MFC�õ�
CString Base64Encode(const unsigned char* src, size_t srclen)
{
    CString dest;
    srclen = srclen > 0 ? srclen : strlen((const char*)src);
    size_t destlen = srclen * 4 / 3 + 3;
    base64_encode(src, srclen, (unsigned char*)dest.GetBuffer(destlen), destlen);
    dest.ReleaseBuffer();
    return dest;
}

CString Base64Decode(const unsigned char* src, size_t srclen)
{
    CString dest;
    srclen = srclen > 0 ? srclen : strlen((const char*)src);
    size_t destlen = srclen * 3 / 4 + 4;
    base64_decode(src, srclen, (unsigned char*)dest.GetBuffer(destlen), destlen);
    dest.ReleaseBuffer();
    return dest;
}



