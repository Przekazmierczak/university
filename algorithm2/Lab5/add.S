.intel_syntax noprefix
.global maxHeapAdd

.global DynamicArray_add
.global DynamicArray_swap
.global DynamicArray_size

#.global maxHeapGetParent
#.global maxHeapBubbleUp
#.global elementCompare

maxHeapAdd:
    push r12
    push r13
    mov r12, rcx
    mov r13, r8

    sub rsp, 40     # shadow space
    call DynamicArray_add
    add rsp, 40

    # int maxHeapBubbleUp(struct MaxHeap2 *heap, int child, int (*cmp)(const int, const int))
    mov rcx, r12    # this pointer

    sub rsp, 40
    call DynamicArray_size
    add rsp, 40

    sub rax, 1

    mov rcx, r12    # this pointer
    mov rdx, rax
    mov r8, r13      # pointer to cmp

    sub rsp, 40
    call maxHeapBubbleUp
    add rsp, 40

    pop r13
    pop r12
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

    #push r12

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

    mov r8, rax           # save parent

    # int elementCompare(int new_obj, int list_obj)
    mov rax, [r9]         # array

    #lea rcx, [r8 + r10*4]   # get array[child]
    mov rcx, [rax + r10*4]

    #lea rdx, [r8 + r12*4]   # get array[parent]
    mov rdx, [rax + r8*4]

    sub rsp, 40
    call r11
    add rsp, 40

    cmp eax, 0
    jle finish

    # void DynamicArray_swap(DynamicArray<int> *arr, int index1, int index2)
    mov rcx, r9
    mov rdx, r10
    mov r8, r8

    sub rsp, 40
    call DynamicArray_swap
    add rsp, 40

    # int maxHeapBubbleUp(struct MaxHeap2 *heap, int child, int (*cmp)(const int, const int))
    mov rcx, r9
    mov rdx, r8
    mov r8, r11
    
    sub rsp, 40
    call maxHeapBubbleUp
    add rsp, 40

finish:
    #pop r12
    ret