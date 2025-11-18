#include <iostream>

int fun1(uint8_t a, uint8_t b)
{
    uint8_t y;
    uint8_t y1;

    y = (a & 0x02) | (b & 0xFD);

    _asm {
        mov al, a
        mov bl, b
        and al, 0x02
        and bl, 0xFD
        or bl, al
        mov y1, bl
    }

    if (y == y1) {
        printf("test passed %#x = %#x\n", y, y1);
        return 0;
    }
    else {
        printf("test failed %#x != %#x\n", y, y1);
        return 1;
    }
}

int fun2(uint8_t a, uint8_t b)
{
    uint8_t y;
    uint8_t y1;

    y = ((a & 0x01) << 2) | (b & 0xFB);

    _asm {
        mov al, a
        mov bl, b
        and al, 0x01
        shl al, 2
        and bl, 0xFB
        or bl, al
        mov y1, bl
    }

    if (y == y1) {
        printf("test passed %#x = %#x\n", y, y1);
        return 0;
    }
    else {
        printf("test failed %#x != %#x\n", y, y1);
        return 1;
    }
}

int fun3(uint8_t b)
{
    uint8_t y;
    uint8_t y1;

    uint8_t b1;
    uint8_t b2;
    
    b1 = (b & 0xAA) >> 1;
    b2 = (b & 0x55) << 1;

    y = b1 | b2;

    _asm {
        mov cl, b
        mov dl, b

        and cl, 0xAA
        shr cl, 1
        and dl, 0x55
        shl dl, 1

        or cl, dl

        mov y1, cl
    }

    if (y == y1) {
        printf("test passed %#x = %#x\n", y, y1);
        return 0;
    }
    else {
        printf("test failed %#x != %#x\n", y, y1);
        return 1;
    }
}

int main()
{
    fun3(0xF1);

    return 0;
}