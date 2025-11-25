.intel_syntax noprefix
; .global _addTwo
; .global _addThree
.global _maxHeapAdd
.global _DynamicArray_add

; _addTwo:
;     mov eax, [esp + 4]
;     add eax, [esp + 8]
;     ret

; _addThree:
;     mov eax, [esp + 4]
;     add eax, [esp + 8]
;     add eax, [esp + 12]
;     ret

_maxHeapAdd:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]     # this pointer
    mov edx, [ebp + 12]     # val (pointer or value depending on SomeObject)

    # array is at offset 0
    lea ecx, [eax + 0]     # pointer to array

    # call DynamicArray_add(array, val)
    push edx               # val
    push ecx               # array pointer
    call _DynamicArray_add
    add esp, 8             # clean stack

    pop ebp
    ret