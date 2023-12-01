#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int part_one(char* filename){
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return EXIT_FAILURE;
    }
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    int sum = 0;

    while (fgets(buffer, MAX_LENGTH, fp))
    {
        int first_digit = -1; // Using -1 in case of a digit being zero
        int last_digit = -1;
        for(int i = 0; i < strlen(buffer); i++)
        {
            if (isdigit(buffer[i]))
            {
                if (first_digit == -1)
                {
                    first_digit = buffer[i]-48;
                }

                last_digit = buffer[i]-48;
            }
            
        }
        sum += (first_digit * 10 + last_digit);
    }
    fclose(fp);
    return sum;
}

int part_two(char* filename){
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return EXIT_FAILURE;
    }
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    int sum = 0;

    while (fgets(buffer, MAX_LENGTH, fp))
    {
        int first_digit = -1; // Using -1 in case of a digit being zero
        int last_digit = -1;
        int index_of_last_digit = 0;
        int corresponding_digit = -1;
        char current_word[MAX_LENGTH];
        for(int i = 0; i < strlen(buffer); i++)
        {
            if (isdigit(buffer[i]))
            {
                if (first_digit == -1)
                {
                    first_digit = buffer[i] - 48;
                }
                if(index_of_last_digit < i){
                    last_digit = buffer[i] - 48;
                    index_of_last_digit = i;
                }
            }
            
            for (int j = i; j < strlen(buffer); j++)
            {
                current_word[j - i] = buffer[j];
                if(!strcmp(current_word, "one"))
                {
                    corresponding_digit = 1;
                }
                if(!strcmp(current_word, "two"))
                {
                    corresponding_digit = 2;
                }
                if(!strcmp(current_word, "three"))
                {
                    corresponding_digit = 3;
                }
                if(!strcmp(current_word, "four"))
                {
                    corresponding_digit = 4;
                }
                if(!strcmp(current_word, "five"))
                {
                    corresponding_digit = 5;
                }
                if(!strcmp(current_word, "six"))
                {
                    corresponding_digit = 6;
                }
                if(!strcmp(current_word, "seven"))
                {
                    corresponding_digit = 7;
                }
                if(!strcmp(current_word, "eight"))
                {
                    corresponding_digit = 8;
                }
                if(!strcmp(current_word, "nine"))
                {
                    corresponding_digit = 9;
                }
                if(corresponding_digit != -1){
                    if(first_digit == -1){
                        first_digit = corresponding_digit;
                    }
                    if(index_of_last_digit < j){
                        last_digit = corresponding_digit;
                        index_of_last_digit = j;
                    }
                    corresponding_digit = -1;
                }
                
            }
            memset(current_word, 0, sizeof(current_word));
        }
        if (last_digit == -1)
        {
            last_digit = first_digit;
        }
        printf("%d%d\n", first_digit, last_digit);
        sum += (first_digit * 10 + last_digit);
        index_of_last_digit = 0;
        first_digit = 0;
        last_digit = 0;
    }

    fclose(fp);
    return sum;
}


int main(void){
    char *filename = "day1.txt";
    

    int choosen_assignment = 0;
    int sum = 0;
    printf("Choose Assignment: ");
    if(!scanf("%d", &choosen_assignment)){
        printf("ERROR: No valid Input provided.\n");
        return EXIT_FAILURE;
    }
    if(choosen_assignment == 1){
        sum = part_one(filename);
    }
    else if(choosen_assignment == 2){
        sum = part_two(filename);
    }
    else {
        printf("ERROR: No valid Input provided.\n");
    }
    
    
    printf("The sum of all calibration values is %d.\n", sum);

    
    return EXIT_SUCCESS;
}

