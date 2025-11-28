.intel_syntax noprefix
.global maxHeapAdd

.global DynamicArray_add
.global DynamicArray_swap

.global maxHeapGetParent
.global maxHeapBubbleUp
.global elementCompare

maxHeapAdd:
    sub rsp, 32     # shadow space

    # mov eax, [ebp + 8]     # this pointer
    #mov edx, [ebp + 12]     # val (pointer or value depending on SomeObject)
    
    # rcx - this pointer
    # rdx - val

    # array is at offset 0
    # lea eax, [eax + 0]     # pointer to array

    # call DynamicArray_add(array, val)
    # push edx               # val
    # push eax               # this pointer
    #mov rcx, [rcx]
    #mov rdx, rdx
    call DynamicArray_add
    # add esp, 8             # clean stack

    # pop ebp
    add rsp, 32
    ret

maxHeapGetParent:
    sub rcx, 1
    shr rcx, 1
    mov rax, rcx

    ret

maxHeapBubbleUp:
    # rcx    this pointer
    # rdx    child
    # r8    pointer to cmp

    push r12

    mov r9, rcx           # save this pointer
    mov r10, rdx          # save child
    mov r11, r8           # save pointer to cmp

    test rdx, rdx
    jz finish
    
    # int maxHeapGetParent(int child);
    mov rcx, rdx
    sub rsp, 40
    call maxHeapGetParent
    add rsp, 40

    mov r12, rax           # save parent

    # int elementCompare(int new_obj, int list_obj)
    mov r8, [r9]         # array

    lea rcx, [r8 + r10*4]   # get array[child]
    mov rcx, [rcx]

    lea rdx, [r8 + r12*4]   # get array[parent]
    mov rdx, [rdx]

    sub rsp, 40
    call elementCompare
    add rsp, 40

    cmp rax, 0
    jle finish

    # void DynamicArray_swap(DynamicArray<int> *arr, int index1, int index2)
    mov rcx, r8
    mov rdx, r10
    mov r8, r12

    sub rsp, 40
    call DynamicArray_swap
    add rsp, 40

    # int maxHeapBubbleUp(struct MaxHeap2 *heap, int child, int (*cmp)(const int, const int))
    mov rcx, r9
    mov rdx, r12
    mov r8, r11
    
    sub rsp, 40
    call maxHeapBubbleUp
    add rsp, 40

finish:
    pop r12
    ret