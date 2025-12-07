#include <iostream>

int fun1()
{
    uint32_t y = 0x00;
    uint32_t y1 = 0x00;
    
    for (int i = 0; i != 5; i++) y += i;

    _asm {
        mov eax, 0

        petla_for:
        mov ebx, eax
        sub ebx, 5
            jz petla_for_koniec
            add y1, eax
            add eax, 1
            jmp petla_for
        petla_for_koniec:
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

int fun2(uint32_t a)
{
    uint32_t y;
    uint32_t y1;

    y = a;
    while (y != 5) y += 1;

    _asm {
        mov eax, a

        while_loop :
        mov ebx, eax
        sub ebx, 5
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

int fun3(uint8_t a) {
    uint8_t y;
    uint8_t y1;

    y = 0;
    if (!(a & 0x01)) y++;
    if (!(a & 0x02)) y++;
    if (!(a & 0x04)) y++;
    if (!(a & 0x08)) y++;
    if (!(a & 0x10)) y++;
    if (!(a & 0x20)) y++;
    if (!(a & 0x40)) y++;
    if (!(a & 0x80)) y++;

    _asm {
        mov al, a
        xor bl, bl

        mov cl, al
        and cl, 0x01
        cmp cl, 0
        jnz end_if0
        add bl, 1
        end_if0:

        mov cl, al
        and cl, 0x02
        cmp cl, 0
        jnz end_if1
        add bl, 1
        end_if1:

        mov cl, al
        and cl, 0x04
        cmp cl, 0
        jnz end_if2
        add bl, 1
        end_if2:

        mov cl, al
        and cl, 0x08
        cmp cl, 0
        jnz end_if3
        add bl, 1
        end_if3:

        mov cl, al
        and cl, 0x10
        cmp cl, 0
        jnz end_if4
        add bl, 1
        end_if4:

        mov cl, al
        and cl, 0x20
        cmp cl, 0
        jnz end_if5
        add bl, 1
        end_if5:

        mov cl, al
        and cl, 0x40
        cmp cl, 0
        jnz end_if6
        add bl, 1
        end_if6:

        mov cl, al
        and cl, 0x80
        cmp cl, 0
        jnz end_if7
        add bl, 1
        end_if7:

        mov y1, bl
    }

    if (y == y1) {
        printf("test passed (no loop) %#x = %#x\n", y, y1);
        return 0;
    }
    else {
        printf("test failed (no loop) %#x != %#x\n", y, y1);
        return 1;
    }
}

int fun31(uint8_t a) {
    // sprawdzic
    _asm {
        xor bl, bl
        and al, 0x1
        add bl, al
        shr b, 1
        mov y, bl
    }


}

int fun4(uint8_t a)
{
    uint8_t y;
    uint8_t y1;

    y = 0;
    uint8_t curr = a;
    for (int i = 0; i < 8; i++) {
        if ((curr & 1) == 0) y++;
        curr >>= 1;
    }

    _asm {
        mov al, a
        mov bl, 0
        mov cl, 0

        for_loop:
            cmp cl, 8
            jz end_loop

            mov dl, al
            and dl, 1
            cmp dl, 1
            jz end_if

                add bl, 1

            end_if:

            shr al, 1
            add cl, 1
            jmp for_loop

        end_loop :
        mov y1, bl
    }

    if (y == y1) {
        printf("test passed (loop) %#x = %#x\n", y, y1);
        return 0;
    }
    else {
        printf("test failed (loop) %#x != %#x\n", y, y1);
        return 1;
    }
}

int fun5(uint8_t a) {
    uint8_t y;
    uint8_t y1;

    uint8_t curr = 0;
    if (a & 0x01) curr++;
    if (a & 0x02) curr++;
    if (a & 0x04) curr++;
    if (a & 0x08) curr++;
    if (a & 0x10) curr++;
    if (a & 0x20) curr++;
    if (a & 0x40) curr++;
    if (a & 0x80) curr++;

    y = !(curr & 0x01);

    _asm {
        mov al, a
        xor bl, bl

        mov cl, al
        and cl, 0x01
        cmp cl, 0
        jnz end_if0
        add bl, cl
        end_if0:

        mov cl, al
        and cl, 0x02
        cmp cl, 0
        jnz end_if1
        add bl, 1
        end_if1:

        mov cl, al
        and cl, 0x04
        cmp cl, 0
        jnz end_if2
        add bl, 1
        end_if2:

        mov cl, al
        and cl, 0x08
        cmp cl, 0
        jnz end_if3
        add bl, 1
        end_if3:

        mov cl, al
        and cl, 0x10
        cmp cl, 0
        jnz end_if4
        add bl, 1
        end_if4:

        mov cl, al
        and cl, 0x20
        cmp cl, 0
        jnz end_if5
        add bl, 1
        end_if5:

        mov cl, al
        and cl, 0x40
        cmp cl, 0
        jnz end_if6
        add bl, 1
        end_if6:

        mov cl, al
        and cl, 0x80
        cmp cl, 0
        jnz end_if7
        add bl, 1
        end_if7:

        and bl, 1
        xor bl, 1
        mov y1, bl
    }

    if (y == y1) {
        printf("test passed (no loop) %#x = %#x\n", y, y1);
        return 0;
    }
    else {
        printf("test failed (no loop) %#x != %#x\n", y, y1);
        return 1;
    }
}

int fun6(uint8_t a)
{
    uint8_t y;
    uint8_t y1;

    uint8_t count = 0;
    uint8_t curr = a;
    for (int i = 0; i < 8; i++) {
        if ((curr & 1) == 1) count++;
        curr >>= 1;
    }

    y = !(count & 0x01);

    _asm {
        mov al, a
        mov bl, 0
        mov cl, 0

        for_loop:
        cmp cl, 8
            jz end_loop

            mov dl, al
            and dl, 1
            cmp dl, 1
            jz end_if

            add bl, 1

            end_if:

        shr al, 1
            add cl, 1
            jmp for_loop

            end_loop :

        and bl, 1
        xor bl, 1
        mov y1, bl
    }

    if (y == y1) {
        printf("test passed (loop) %#x = %#x\n", y, y1);
        return 0;
    }
    else {
        printf("test failed (loop) %#x != %#x\n", y, y1);
        return 1;
    }
}

int main()
{
    //for (int i = 0; i < 256; i++) {
    //    fun3(i);
    //    fun4(i);
    //}
    fun5(0x00);
    fun5(0x80);
    fun5(0x12);
    fun5(0x13);

    fun6(0x00);
    fun6(0x80);
    fun6(0x12);
    fun6(0x13);
    
    return 0;
}