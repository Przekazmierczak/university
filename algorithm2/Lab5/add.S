.intel_syntax noprefix
.global _maxHeapAdd

.global _DynamicArray_add
.global _DynamicArray_swap

.global _maxHeapGetParent
.global _maxHeapBubbleUp
.global _elementCompare

_maxHeapAdd:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]     # this pointer
    mov edx, [ebp + 12]     # val (pointer or value depending on SomeObject)

    # array is at offset 0
    lea eax, [eax + 0]     # pointer to array

    # call DynamicArray_add(array, val)
    push edx               # val
    push eax               # this pointer
    call _DynamicArray_add
    add esp, 8             # clean stack

    pop ebp
    ret

_maxHeapGetParent:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]
    sub eax, 1
    shr eax, 1

    pop ebp
    ret

_maxHeapBubbleUp:
    push ebp
    mov ebp, esp 

    # [ebp + 8]     this pointer
    # [ebp + 12]    child
    # [ebp + 16]    pointer to cmp
    mov eax, [ebp + 12]    # child index

    test eax, eax
    jz finish

    push eax               # get parent to eax
    call _maxHeapGetParent
    add esp, 4

    mov ecx, eax           # save parent

    mov edx, [ebp + 8]     # this pointer
    lea edx, [edx + 0]     # pointer to array

    lea eax, [edx + ecx*4]   # get array[parent]
    push eax               # push array[parent]

    mov eax, [ebp + 12]    # get child
    lea eax, [edx + eax*4]   # get array[child]
    push eax               # push array[child]

    call _elementCompare
    add esp, 8

    cmp eax, 0
    jl finish
    ; je finish

    push ecx
    push [ebp + 12]
    push edx

    call _DynamicArray_swap
    add esp, 12

    push [ebp + 16]         # pointer to cmp
    push ecx         # push parent
    push [ebp + 8]          # push this pointer

    call _maxHeapBubbleUp
    add esp, 12

finish:
    pop ebp
    ret