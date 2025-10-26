#include <iostream>

int fun1(uint8_t a)
{
    uint16_t y;
    uint16_t y1;

    y = a * 18;

    _asm {
        mov ax, 0
        mov bx, 0

        MOV al, a
        MOV bl, a

        SHL ax, 4
        SHL bx, 1

        ADD ax, bx

        MOV y1, ax
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

int fun2(uint8_t a)
{
    uint16_t y;
    uint16_t y1;

    y = (a << 6) + (a << 1);

    _asm {
        mov ax, 0
        mov bx, 0

        MOV al, a
        MOV bl, a

        SHL ax, 6
        SHL bx, 1

        ADD ax, bx

        MOV y1, ax
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

int fun3(uint8_t a)
{
    uint16_t y;
    uint16_t y1;

    y = (a << 6) - (a << 4) - (a << 3) - (a << 2);

    _asm {
        mov ax, 0
        mov bx, 0
        mov cx, 0
        mov dx, 0

        MOV al, a
        MOV bl, a
        MOV cl, a
        MOV dl, a

        SHL ax, 6
        SHL bx, 4
        SHL cx, 3
        SHL dx, 2

        SUB ax, bx
        SUB ax, cx
        SUB ax, dx

        MOV y1, ax
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

int fun4(uint8_t a)
{
    uint8_t y;
    uint8_t y1;

    y = (a == 0x16) ? 0 : 1;

    _asm {
        mov al, a

        sub al, 0x16

        jnz notEqual
            mov al, 0
            jmp endd
        notEqual:
            mov al, 1
        endd:
        
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
    //fun1(0x1F);
    //fun1(0x11);
    //fun1(0xFF);
    //fun2(0xFF);
    //fun3(0xFF);
    fun4(0x16);
    fun4(0x14);
    return 0;
}





//_asm {
//    mov al, a
//
//    sub al, 0x16
//
//    jz jump
//    mov y1, 1
//    jmp end
//
//    jump :
//    mov y1, 0
//
//        end :
//}