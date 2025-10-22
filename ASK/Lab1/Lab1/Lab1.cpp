#include <iostream>

int fun1(unsigned char a, unsigned char b)
{
    unsigned char y;
    unsigned char y1;

    y = a + b;

    _asm {
        xor al, al
        xor bl, bl

        mov al, a
        mov bl, b
        add al, bl // wynik w al
        mov y1, al
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

int fun2(unsigned char a, unsigned char b, unsigned char c)
{
    unsigned char y;
    unsigned char y1;

    y = a + b - c;

    _asm {
        xor al, al
        xor bl, bl

        mov al, a
        mov bl, b

        add al, bl

        mov bl, c

        sub al, bl

        mov y1, al
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

int fun3(unsigned char a)
{
    unsigned char y;
    unsigned char y1;

    y = a << 2;

    _asm {
        xor al, al

        mov al, a

        SHL al, 2

        mov y1, al
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
    fun1(0xA, 6);
    fun2(0xA, 6, 6);
    fun3(0xA);

    return 0;
}