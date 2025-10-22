#include <iostream>

int fun1(uint8_t a)
{
    uint16_t y;
    uint16_t y1;

    y = a * 20;

    _asm {
        xor ax, ax
        xor bx, bx

        mov al, a
        mov bl, a

        SHL ax, 4
        SHL bx, 2

        ADD ax, bx

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

int fun2(unsigned char a)
{
    unsigned char y;
    unsigned char y1;

    if (a == 0x16) {
        y = 0;
    }
    else {
        y = 1;
    }

    _asm {
        mov al, a

        sub al, 0x16

        jz jump
        mov y1, 1
        jmp end

        jump :
        mov y1, 0

            end :
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

int fun3(uint32_t a)
{
    uint32_t y;
    uint32_t y1;

    y = a;
    for (int i = 0; i != 5; i++) {
        y += i;
    }

    _asm {
        mov eax, a
        mov ecx, ecx

        for_loop:
        cmp ecx, 5
            jz end_loop

            add eax, ecx
            add ecx, 1
            jmp for_loop

            end_loop :

        mov y1, eax
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

int fun4(uint32_t a)
{
    uint32_t y;
    uint32_t y1;

    y = a;
    while (y != 5) y += 1;

    _asm {
        mov eax, a

        while_loop :
        cmp eax, 5
            jz end_loop

            add eax, 1
            jmp while_loop

            end_loop :

        mov y1, eax
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

int fun4_(uint32_t a)
{
    uint32_t y;
    uint32_t y1;

    y = a;
    do {
        y += 1;
    } while (y != 5);

    _asm {
        mov eax, a

        while_loop :
        add eax, 1

            cmp eax, 5
            jz end_loop

            jmp while_loop

            end_loop :

        mov y1, eax
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

int fun5(uint8_t a)
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
        xor cl, cl //i

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

        end_loop :
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

int fun6(uint8_t a)
{
    uint8_t y;
    uint8_t y1;

    bool even = true;
    uint8_t curr = a;
    for (int i = 0; i < 8; i++) {
        if (curr & 1) {
            even = (even) ? false : true;
        }
        curr >>= 1;
    }
    y = even;


    _asm {
        mov al, a
        mov bl, 1
        mov cl, 0

        for_loop:
        cmp cl, 8
            jz end_loop

            test al, 1
            jz end_if
            
            xor bl, 1

            end_if:

            shr al, 1
            add cl, 1
            jmp for_loop

        end_loop :
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

int fun7(uint8_t a)
{
    uint8_t y;
    uint8_t y1;

    y = 0;
    uint8_t curr = a;
    for (int i = 0; i < 8; i++) {
        if (!(curr & 1)) y++;
        curr >>= 1;
    }


    _asm {
        mov al, a
        mov bl, 0
        mov cl, 0

        for_loop:
            cmp cl, 8
            jz end_loop

            test al, 1
            jnz end_if

            add bl, 1

            end_if:

            shr al, 1
            add cl, 1
            jmp for_loop

        end_loop :
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

int fun8(uint8_t a, uint8_t b)
{
    uint16_t y;
    uint16_t y1;

    y = a * b;

    _asm {
        mov al, a
        xor bx, bx
        mov bl, b
        xor cl, cl
        xor dx, dx

        for_loop:
            cmp cl, 8
            jz end_loop

            test al, 1
                jz end_if

                add dx, bx

            end_if:

            shr al, 1
            shl bx, 1

            add cl, 1
            jmp for_loop


        end_loop:

        mov y1, dx
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

int fun9(uint16_t a)
{
    uint16_t y;
    uint16_t y1;

    y = a * 4.125;

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

int fun10(uint8_t a)
{
    uint8_t y = 0;
    uint8_t y1;

    uint8_t temp;
    uint8_t curr = a;

    for (int i = 0; i < 4; i++) {
        temp = curr & 1;
        curr >>= 1;

        y >>= 1;
        if (curr & 1) y |= 128;
        y >>= 1;
        if (temp) y |= 128;

        curr >>= 1;
    }

    _asm {
        mov al, a // curr
        xor bl, bl // y1
        xor cl, cl // i
        // dl temp

        for_loop:
            cmp cl, 4
            jz end_loop

            // temp = curr & 1
            test al, 1
            jz temp_0

            mov dl, 1
            jmp end_if1

        temp_0:
                xor dl, dl
        end_if1:

            // curr >>= 1;
            shr al, 1

            // y>>= 1
            shr bl, 1

            // if (curr & 1) y |= 128;
            test al, 1
            jz end_if2
            or bl, 128
         end_if2:

            // y>>= 1
            shr bl, 1

            // if (temp) y |= 128;
            cmp dl, 1
            jnz end_if3

            or bl, 128
        end_if3:

            // curr >>= 1;
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

int main()
{
    /*fun1(0xFF);
    fun2(0x16);
    fun2(0xA);
    fun3(0xAFD124);
    fun4(0x0);
    fun4_(0x3);
    fun5(0x80);
    fun5(0x12);
    fun5(0x48);
    fun6(0x00);
    fun6(0x80);
    fun6(0x12);
    fun6(0x13);
    fun7(0x00);
    fun7(0x80);
    fun7(0x12);
    fun7(0x13);
    fun8(0x0, 0x1);
    fun8(0x1, 0x2);
    fun8(0x4, 0x4);
    fun8(0x2, 0x2);
    fun8(0xF4, 0xAF);
    fun9(0x0);
    fun9(0x1);
    fun9(0xFF);*/
    fun10(0x99);
    fun10(0x02);
    fun10(0xEE);

    return 0;
}