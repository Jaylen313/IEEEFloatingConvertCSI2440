

#include <stdio.h>
#include <math.h>

void decimalToBinary(float num) {
    int *binaryNum = (int*)&num;
    int binary[32];
    for (int i = 0; i < 32; ++i) {
        binary[31 - i] = (*binaryNum >> i) & 1;
    }

    printf("IEEE 754 representation of %f is: ", num);
    for (int i = 0; i < 32; ++i) {
        printf("%d", binary[i]);
    }
    printf("\n");
}

float binaryToDecimal(char *binary) {
    int sign = (binary[0] == '1') ? -1 : 1;
    int exponent = 0;
    double mantissa = 0.0;
    int bias = 127;

    for (int i = 1; i <= 8; i++) {
        exponent = exponent * 2 + (binary[i] - '0');
    }

    for (int i = 9; i <= 31; i++) {
        mantissa += (binary[i] - '0') * pow(2, 8 - i);
    }

    if (exponent == 255 && mantissa != 0) {
        return NAN;
    } else if (exponent == 255 && mantissa == 0 && sign == 1) {
        return INFINITY;
    } else if (exponent == 255 && mantissa == 0 && sign == -1) {
        return -INFINITY;
    } else if (exponent > 0 && exponent < 255) {
        return sign * pow(2, exponent - bias) * (mantissa + 1);
    } else if (exponent == 0 && mantissa != 0) {
        return sign * pow(2, 1 - bias) * mantissa;
    } else if (exponent == 0 && mantissa == 0 && sign == 1) {
        return 0.0;
    } else if (exponent == 0 && mantissa == 0 && sign == -1) {
        return -0.0;
    }
}

int main() {
    int choice;
    printf("1. Convert decimal to IEEE 754 binary\n");
    printf("2. Convert IEEE 754 binary to decimal\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        float num;
        printf("Enter a decimal number: ");
        scanf("%f", &num);
        decimalToBinary(num);
    } else if (choice == 2) {
        char binary[33];
        printf("Enter a binary number: ");
        scanf("%s", binary);
        printf("Decimal: %f\n", binaryToDecimal(binary));
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}