.intel_syntax noprefix
.global maxHeapAdd
.global maxHeapPop

# int DynamicArray_add(DynamicArray<SomeObject> *arr, SomeObject val, int (*cmp)(const SomeObject*, const SomeObject*))
.global DynamicArray_add
# void DynamicArray_swap(DynamicArray<SomeObject> *arr, int index1, int index2)
.global DynamicArray_swap
# int DynamicArray_size(DynamicArray<SomeObject> *arr)
.global DynamicArray_size
# int DynamicArray_remove(DynamicArray<SomeObject> *arr)
.global DynamicArray_remove

# int maxHeapAdd(struct MaxHeap *heap, SomeObject val, int (*cmp)(const SomeObject*, const SomeObject*))
maxHeapAdd:
    push r12
    push r13

    mov r12, rcx            # this pointer
    mov r13, r8             # cmp pointer

    # Call DynamicArray_add(arr, val, cmp)
    sub rsp, 32             # shadow space
    call DynamicArray_add
    add rsp, 32

    # Call DynamicArray_size(arr)
    mov rcx, r12

    sub rsp, 32
    call DynamicArray_size
    add rsp, 32

    # Call maxHeapBubbleUp(this, size - 1, cmp)
    sub rax, 1              # size - 1

    mov rcx, r12
    mov rdx, rax
    mov r8, r13

    sub rsp, 32
    call maxHeapBubbleUp
    add rsp, 32

    pop r13
    pop r12
    ret

# SomeObject maxHeapPop(struct MaxHeap2 *heap, int (*cmp)(const SomeObject*, const SomeObject*))
maxHeapPop:
    push r12
    push r13
    push r14

    mov r12, rcx            # this pointer
    mov r13, rdx            # cmp pointer

    mov r14, [r12]          # array pointer
    mov r14, [r14]          # temp array[0]

    # Call DynamicArray_size(arr)
    mov rcx, r12
    sub rsp, 32
    call DynamicArray_size
    add rsp, 32

    sub rax, 1              # size - 1
    
    # Call DynamicArray_swap(arr, 0, size - 1)
    mov rcx, r12
    mov rdx, 0
    mov r8, rax

    sub rsp, 32
    call DynamicArray_swap
    add rsp, 32

    # Call DynamicArray_remove(arr)
    mov rcx, r12
    sub rsp, 32
    call DynamicArray_remove
    add rsp, 32

    # Call maxHeapBubbleDown(this, 0, cmp)
    mov rcx, r12
    mov rdx, 0
    mov r8, r13

    sub rsp, 32
    call maxHeapBubbleDown
    add rsp, 32

    mov rax, r14           # return temp array[0]

    pop r14
    pop r13
    pop r12
    ret

# void maxHeapBubbleUp(struct MaxHeap *heap, int child, int (*cmp)(const SomeObject*, const SomeObject*))
maxHeapBubbleUp:
    push r12
    push r13
    push r14
    push r15

    mov r12, rcx           # this pointer
    mov r13, rdx           # child
    mov r14, r8            # cmp pointer

    # if (child == 0) return
    test r13, r13
    jz finishBubbleUp
    
    # get parent index
    mov rax, r13
    sub rax, 1
    shr rax, 1

    mov r15, rax           # parent

    # Call cmp(array[child], get array[parent])
    mov rax, [r12]         # array
    lea rcx, [rax + r13*8] # get array[child]
    lea rdx, [rax + r15*8] # get array[parent]

    sub rsp, 32
    call r14
    add rsp, 32

    cmp eax, 0
    jle finishBubbleUp

    # Call DynamicArray_swap(arr, child, parent)
    mov rcx, r12
    mov rdx, r13
    mov r8, r15

    sub rsp, 32
    call DynamicArray_swap
    add rsp, 32

    # Call maxHeapBubbleUp(this, parent, cmp)
    mov rcx, r12
    mov rdx, r15
    mov r8, r14
    
    sub rsp, 32
    call maxHeapBubbleUp
    add rsp, 32

finishBubbleUp:
    pop r15
    pop r14
    pop r13
    pop r12
    ret

# void bubbleDown(struct MaxHeap *heap, int parent, int (*cmp)(const Struct*, const Struct*))
maxHeapBubbleDown:
    push r12
    push r13
    push r14
    push r15
    push rbx
    push rdi

    mov r12, rcx          # this pointer
    mov r13, rdx          # parent
    mov r14, r8           # cmp pointer

    # get left child index
    mov rax, rdx
    shl rax, 1
    add rax, 1

    mov r15, rax           # left child

    mov rbx, r13           # greatest

    # Call DynamicArray_size(arr)
    mov rcx, r12
    sub rsp, 32
    call DynamicArray_size
    add rsp, 32

    mov rdi, rax           # size

    # if left child < size
    cmp r15, rdi
    jge skipLeft

    # if cmp(array[leftChild], array[parent]) > 0
    # Call cmp(array[leftChild], array[parent])
    mov rax, [r12]           # array
    lea rcx, [rax + r15*8]   # get array[leftChild]
    lea rdx, [rax + r13*8]   # get array[parent]

    sub rsp, 32
    call r14
    add rsp, 32

    cmp eax, 0
    jle skipLeft

    mov rbx, r15           # greatest

skipLeft:
    add r15, 1             # right child
    # if right child < size
    cmp r15, rdi
    jge skipRight

    # if cmp(array[rightChild], array[greatest]) > 0
    # Call cmp(array[rightChild], array[greatest])
    mov rax, [r12]           # array
    lea rcx, [rax + r15*8]   # get array[rightChild]
    lea rdx, [rax + rbx*8]   # get array[greatest]

    sub rsp, 32
    call r14
    add rsp, 32

    cmp eax, 0
    jle skipRight

    mov rbx, r15           # greatest

skipRight:
    # if greatest != parent
    cmp rbx, r13
    jz finishBubbleDown

    # Call DynamicArray_swap(arr, parent, greatest)
    mov rcx, r12
    mov rdx, r13
    mov r8, rbx

    sub rsp, 32
    call DynamicArray_swap
    add rsp, 32

    # Call maxHeapBubbleDown(this, greatest, cmp)
    mov rcx, r12
    mov rdx, rbx
    mov r8, r14
    
    sub rsp, 32
    call maxHeapBubbleDown
    add rsp, 32


finishBubbleDown:
    pop rdi
    pop rbx
    pop r15
    pop r14
    pop r13
    pop r12
    ret