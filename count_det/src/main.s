.text

.global count_det
count_det:

    ldr r1, [r0], #4
    ldr r2, [r0], #4
    ldr r3, [r0], #4
    ldr r4, [r0], #4
    ldr r5, [r0], #4
    ldr r6, [r0], #4
    mul r7, r1, r5  //a11 * a22 +
    mul r8, r1, r6  //a11 * a23 -
    mul r1, r2, r6  //a12 * a23 +
    mul r6, r2, r4  //a12 * a21 -
    mul r2, r3, r4  //a13 * a21 +
    mul r4, r3, r5  //a13 * a22 -
    ldr r3, [r0], #4
    mul r1, r3  //12 23 31
    mul r4, r3  //13 22 31
    sub r1, r4
    ldr r3, [r0], #4
    mul r8, r3  //11 23 32
    sub r1, r8
    mul r2, r3  //13 21 32
    add r1, r2
    ldr r3, [r0], #4
    mul r6, r3  //12 21 33
    sub r1, r6
    mul r7, r3  //11 22 33
    add r1, r7
    mov r0, r1
    bx lr
