#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}

bool getBit (const uint64_t number, const uint8_t index) {
    uint64_t one = 1;
    uint64_t mask = one << index;
    uint64_t temp = mask & number;
    temp = temp >> index;
    return temp;
}


/**
 * Checkers here:
 */

bool checkBits (uint64_t number, uint8_t start, uint8_t stop, bool flag){
    bool check = false;
    for (uint8_t i = start; i <= stop; ++ i) {
        if (getBit(number, i) == flag) {
            check = true;
            break;
        }
    }
    return check;
}

bool checkNormal (uint64_t number) {
    bool expContainZero = checkBits(number, 52, 62, false);
    bool expContainOne = checkBits(number, 52, 62, true);
    return expContainZero && expContainOne;
}

bool checkDenormal (uint64_t number) {
    bool expAllZeros = !checkBits(number, 52, 62, true);
    bool fracContainOne = checkBits(number, 0, 51, true);
    return expAllZeros && fracContainOne;
}

bool checkForPlusZero (uint64_t number) {
    return number == 0x0000000000000000;
}

bool checkForMinusZero (uint64_t number) {
    return number == 0x8000000000000000;
}

bool checkForPlusInf (uint64_t number) {
    return number == 0x7FF0000000000000;
}

bool checkForMinusInf (uint64_t number) {
    return number == 0xFFF0000000000000;
}

bool checkForPlusNormal (uint64_t number) {
    bool signPlus = checkBits(number, 63, 63, false);
    bool normal = checkNormal(number);
    return signPlus && normal;
}

bool checkForMinusNormal (uint64_t number) {
    bool signMinus = checkBits(number, 63, 63, true);
    bool normal = checkNormal(number);
    return signMinus && normal; 
}

bool checkForPlusDenormal (uint64_t number) {
    bool signPlus = checkBits(number, 63, 63, false);
    bool denormal = checkDenormal(number); 
    return signPlus && denormal;
}

bool checkForMinusDenormal (uint64_t number) {
    bool signMinus = checkBits(number, 63, 63, true);
    bool denormal = checkDenormal(number);  
    return signMinus && denormal;
}

bool checkForSignalingNan (uint64_t number) {
    bool expAllOne = !checkBits(number, 52, 62, false);
    bool fracZero51 = checkBits(number, 51, 51, false);
    bool fracContainOne = checkBits(number, 0, 50, true);
    return  expAllOne && fracZero51 && fracContainOne;
}

bool checkForQuietNan (uint64_t number) {
    bool expAllOne = !checkBits(number, 52, 62, false);
    bool fracOne51 = checkBits(number, 51, 51, true);
    return  expAllOne && fracOne51;
}


void classify (double number) {
    if (checkForPlusZero(convertToUint64(number))) {
        printf("Plus zero\n");
    }

    else if (checkForMinusZero(convertToUint64(number))) {
        printf("Minus zero\n");
    }

    else if (checkForPlusInf(convertToUint64(number))) {
        printf("Plus inf\n");
    }

    else if (checkForMinusInf(convertToUint64(number))) {
        printf("Minus inf\n");
    }

    else if (checkForPlusNormal(convertToUint64(number))) {
        printf("Plus normal\n");
    }

    else if (checkForMinusNormal(convertToUint64(number))) {
        printf("Minus normal\n");
    }

    else if (checkForPlusDenormal(convertToUint64(number))) {
        printf("Plus Denormal\n");
    }

    else if (checkForMinusDenormal(convertToUint64(number))) {
        printf("Minus Denormal\n");
    }

    else if (checkForSignalingNan(convertToUint64(number))) {
        printf("Signailing NaN\n");
    }

    else if (checkForQuietNan(convertToUint64(number))) {
        printf("Quiet NaN\n");
    }

    else {
        printf("Error.\n");
    }
}


int main() {
    double number;
    scanf("%lf", &number);
    for (uint8_t i = 0; i < 64; ++ i) {
        printf("%d", getBit(convertToUint64(number), 63 - i));
    }
    printf("\n");
    classify(number);

    return 0;
}