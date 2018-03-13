#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *decimal_to_binary(int);

void main()
{
    FILE *lab3_in = fopen("lab3-In.txt", "r");
    FILE *lab3_coef= fopen("lab3-coef.txt", "r");

    float inputs[1000];
    float coef[25];
    int i;

    for (i = 0; i < 1000; i++)
    {
        fscanf(lab3_in, "%f", &inputs[i]);
    }

    for (i = 0; i < 25; i++)
    {
        fscanf(lab3_coef, "%f", &coef[i]);
    }

    fclose(lab3_in);
    fclose(lab3_coef);

    for (i = 0; i < 1000; i++)
    {
        inputs[i] = inputs[i] * 32768;
    }

    for (i = 0; i < 25; i++)
    {
        coef[i] = coef[i] * 32768;
    }

    FILE *lab3_in_fixed_point = fopen("lab3-in-fixed-point.txt", "w");
    FILE *lab3_coef_fixed_point = fopen("lab3-coef-fixed-point.txt", "w");

    int n;
    char *pointer;
    for (i = 0; i < 1000; i++)
    {
        n = (int)inputs[i];
        pointer = decimal_to_binary(n);
        fprintf(lab3_in_fixed_point, "%s\n", pointer);
    }

    for (i = 0; i < 25; i++)
    {
        n = (int)coef[i];
        pointer = decimal_to_binary(n);
        fprintf(lab3_coef_fixed_point, "%s\n", pointer);
    }

    free(pointer);
    fclose(lab3_in_fixed_point);
    fclose(lab3_coef_fixed_point);
}

char *decimal_to_binary(int n)
{
    int c, d, count, i, invert_spot;
    char *pointer;
    int neg_number = 0;

    count = 0;
    pointer = (char *)malloc(16 + 1);

    int binary_digits[16];

    if (pointer == NULL)
        exit(EXIT_FAILURE);

    if (n < 0)
    {
        n = n * (-1);
        neg_number = 1;
    }

    for (c = 15; c >= 0; c--)
    {
        d = n >> c;

        if (d & 1)
            binary_digits[count] = 1;
        else
            binary_digits[count] = 0;
        count++;
    }

    if(!neg_number)
    {
        for(i = 0; i < 16; i++)
        {
            if(binary_digits[i] == 0)
            {
                *(pointer + i) = 0 + '0';
            }
            else
            {
                *(pointer + i) = 1 + '0';
            }
        }
    }
    else
    {
        for (i = 15; i >= 0; i--)
        {
            if (binary_digits[i] == 1)
            {
                invert_spot = i;
                break;
            }
        }

        for (i = 0; i < 16; i++)
        {
            if (i < invert_spot)
            {
                if (binary_digits[i] == 0)
                {
                    *(pointer + i) = 1 + '0';
                }
                else
                {
                    *(pointer + i) = 0 + '0';
                }
            }
            else
            {
                if (binary_digits[i] == 0)
                {
                    *(pointer + i) = 0 + '0';
                }
                else
                {
                    *(pointer + i) = 1 + '0';
                }
            }
        }
    }

    *(pointer + count) = '\0';

    return pointer;
}