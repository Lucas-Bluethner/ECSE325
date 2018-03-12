#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *decimal_to_binary(int);

void main()
{
    FILE *lab2_x = fopen("lab2-x.txt", "r");
    FILE *lab2_y = fopen("lab2-y.txt", "r");

    int N = 1000;
    float x_values[N];
    float y_values[N];
    int i;

    for (i = 0; i < N; i++) 
    {
        fscanf(lab2_x, "%f", &x_values[i]);
    }

    for (i = 0; i < N; i++) 
    {
        fscanf(lab2_y, "%f", &y_values[i]);
    }

    fclose(lab2_x);
    fclose(lab2_y);

    int W = 10;
    int F = 7;

    for(i = 0; i < N; i++)
    {
        x_values[i] = x_values[i]*128; 
    }

    for(i = 0; i < N; i++)
    {
        y_values[i] = y_values[i]*128;
    }

    FILE *lab2_x_fixed_point = fopen("lab2-x-fixed-point.txt", "w");
    FILE *lab2_y_fixed_point = fopen("lab2-y-fixed-point.txt", "w");

    int n;
    char *pointer;
    for(i = 0; i < N; i++) 
    {
        n = (int)x_values[i];
        pointer = decimal_to_binary(n);
        fprintf(lab2_x_fixed_point,"%s ", pointer);
    }

    for(i = 0; i < N; i++)
    {
        n = (int)y_values[i];
        pointer = decimal_to_binary(n);
        fprintf(lab2_y_fixed_point,"%s ", pointer);
    }

    free(pointer);
    fclose(lab2_x_fixed_point);
    fclose(lab2_y_fixed_point);
}

char *decimal_to_binary(int n)
{
    int c, d, count;
    char *pointer;
    int neg_number = 0;
 
    count = 0;
    pointer = (char*)malloc(10+1);
 
    if (pointer == NULL)
      exit(EXIT_FAILURE);

    if (n < 0)
    {
        n = n*(-1);
        neg_number = 1;
    }

    if(!neg_number)
    {
        for (c = 9; c >= 0 ; c--)
        {

            d = n >> c;

            if (d & 1)
                *(pointer+count) = 1 + '0';
            else
                *(pointer+count) = 0 + '0';
            count++;
        
        }
    }
    else
    {
        for(c = 9; c >=0; c--)
        {

            d = n >> c;

            if(c == 9) 
                *(pointer+count) = 1 + '0';
            else if (d & 1)
                *(pointer+count) = 1 + '0';
            else
                *(pointer+count) = 0 + '0';
            count++;
        }
    }

    *(pointer+count) = '\0';
    
    return pointer;
}