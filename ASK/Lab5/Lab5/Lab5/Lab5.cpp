#include <iostream>

int fun1(uint8_t a)
{
    {
        uint8_t y = 0;
        uint8_t y1;

        uint8_t curr = a;
        uint8_t temp;
        for (int i = 0; i < 8; i++) {
            y <<= 1;
            temp = curr & 1;
            y = y | temp;
            curr >>= 1;
        }

        _asm {
            mov al, a // curr
            xor bl, bl // y
            xor cl, cl // i
            // dl temp

            for_loop:
            cmp cl, 8
                jz end_loop

                shl bl, 1
                mov dl, al
                and dl, 1
                or bl, dl
                shr al, 1

                add cl, 1
                jmp for_loop

            end_loop:

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
}

int fun2(uint16_t a)
{
    {
        uint16_t y;
        uint16_t y1;

        y = (a << 2) + (a >> 3);

        _asm {
            mov ax, a
            mov bx, a

            shl ax, 2
            shr bx, 3

            add ax, bx

            mov y1, ax
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
}

int main()
{
    fun1(0x80);
    fun1(0x12);
    fun1(0x48);

    fun2(0x0);
    fun2(0x1);
    fun2(0xFF);

    return 0;
}