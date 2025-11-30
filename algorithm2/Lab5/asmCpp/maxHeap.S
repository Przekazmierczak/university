.intel_syntax noprefix
.global maxHeapAdd
.global maxHeapPop

.global DynamicArray_add
.global DynamicArray_swap
.global DynamicArray_size
.global DynamicArray_remove

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

# SomeObject maxHeapPop(struct MaxHeap2 *heap, int (*cmp)(const SomeObject*, const SomeObject*))
maxHeapPop:
    push r12       # this pointer
    push r13       # pointer to cmp
    push r14       # temp res
    mov r12, rcx
    mov r13, rdx

    mov r14, [r12]         # array
    mov r14, [r14]         # array[0]

    mov rcx, r12
    sub rsp, 40
    call DynamicArray_size
    add rsp, 40

    sub rax, 1
    
    # void DynamicArray_swap(DynamicArray *arr, int index1, int index2)
    mov rcx, r12
    mov rdx, 0
    mov r8, rax

    sub rsp, 40
    call DynamicArray_swap
    add rsp, 40

    # int DynamicArray_remove(DynamicArray<SomeObject> *arr)
    mov rcx, r12
    sub rsp, 40
    call DynamicArray_remove
    add rsp, 40

    # void bubbleDown(struct MaxHeap2 *heap, int parent, int (*cmp)(const Struct*, const Struct*))
    mov rcx, r12
    mov rdx, 0
    mov r8, r13

    sub rsp, 40
    call maxHeapBubbleDown
    add rsp, 40

    mov rax, r14

    pop r14
    pop r13
    pop r12
    ret

maxHeapBubbleUp:
    # rcx    this pointer
    # rdx    child
    # r8    pointer to cmp
    push r12
    push r13
    push r14
    push r15

    mov r12, rcx           # save this pointer
    mov r13, rdx          # save child
    mov r14, r8           # save pointer to cmp

    test r13, r13
    jz finishBubbleUp
    
    # maxHeapGetParent;
    mov rax, r13
    sub rax, 1
    shr rax, 1

    mov r15, rax           # save parent

    # Struct elementCompare(Struct obj1, Struct obj2)
    mov rax, [r12]         # array

    lea rcx, [rax + r13*8]   # get array[child]

    lea rdx, [rax + r15*8]   # get array[parent]

    sub rsp, 40
    call r14
    add rsp, 40

    cmp eax, 0
    jle finishBubbleUp

    # void DynamicArray_swap(DynamicArray *arr, int index1, int index2)
    mov rcx, r12
    mov rdx, r13
    mov r8, r15

    sub rsp, 40
    call DynamicArray_swap
    add rsp, 40

    # void maxHeapBubbleUp(struct MaxHeap *heap, int child, int (*cmp)(const Struct*, const Struct*))
    mov rcx, r12
    mov rdx, r15
    mov r8, r14
    
    sub rsp, 40
    call maxHeapBubbleUp
    add rsp, 40

finishBubbleUp:
    pop r15
    pop r14
    pop r13
    pop r12
    ret

# void bubbleDown(struct MaxHeap *heap, int parent, int (*cmp)(const Struct*, const Struct*))
maxHeapBubbleDown:
    # rcx    this pointer
    # rdx    parent
    # r8    pointer to cmp
    push r12     # this pointer
    push r13     # parent
    push r14     # pointer to cmp
    push r15     # child
    push rbx     # greatest
    push rdi     # size

    mov r12, rcx          # save this pointer
    mov r13, rdx          # save parent
    mov r14, r8           # save pointer to cmp

    # int maxHeapGetChild(int parent);
    mov rax, rdx
    shl rax, 1
    add rax, 1

    mov r15, rax           # save child

    mov rbx, r13           # save greatest

    mov rcx, r12
    sub rsp, 40
    call DynamicArray_size
    add rsp, 40

    mov rdi, rax           # save size

    ######### if (leftChild < array.size() && cmp(array[leftChild], array[parent]) > 0)
    cmp r15, rdi
    jge skipLeft

    # Struct elementCompare(Struct obj1, Struct obj2)
    mov rax, [r12]         # array

    lea rcx, [rax + r15*8]   # get array[child]

    lea rdx, [rax + r13*8]   # get array[parent]

    sub rsp, 40
    call r14
    add rsp, 40

    cmp eax, 0
    jle skipLeft

    mov rbx, r15

skipLeft:
    add r15, 1
    ######### if (rightChild < array.size() && cmp(array[rightChild], array[greatest]) > 0)
    cmp r15, rdi
    jge skipRight

    # Struct elementCompare(Struct obj1, Struct obj2)
    mov rax, [r12]         # array

    lea rcx, [rax + r15*8]   # get array[child]

    lea rdx, [rax + rbx*8]   # get array[greatest]

    sub rsp, 40
    call r14
    add rsp, 40

    cmp eax, 0
    jle skipRight

    mov rbx, r15

skipRight:
    ######### if (greatest != parent)
    cmp rbx, r13
    jz finishBubbleDown

    # void DynamicArray_swap(DynamicArray *arr, int index1, int index2)
    mov rcx, r12
    mov rdx, r13
    mov r8, rbx

    sub rsp, 40
    call DynamicArray_swap
    add rsp, 40

    # int maxHeapBubbleDown(struct MaxHeap *heap, int parent, int (*cmp)(const Struct*, const Struct*))
    mov rcx, r12
    mov rdx, rbx
    mov r8, r14
    
    sub rsp, 40
    call maxHeapBubbleDown
    add rsp, 40


finishBubbleDown:
    pop rdi
    pop rbx
    pop r15
    pop r14
    pop r13
    pop r12
    ret