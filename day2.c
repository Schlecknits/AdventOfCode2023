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
    int current_game = 1;
    int sum = 0;

    while (fgets(buffer, MAX_LENGTH, fp))
    {
        int is_viable = 1;
        char current_cubes[200]; 
        int cube_index = 0;
        
        for(int i = 8; i < strlen(buffer); i++) // beginning to read at position 5 as the "Game x: "-part of the is just incrementing
        {
            if (buffer[i] == ',' || buffer[i] == ';' || i+1 == strlen(buffer)){
                int dice_current_color = 0;
                for(int j = 0; j <= cube_index; j++){
                    if(isdigit(current_cubes[j])){
                        while(1){ //loop that connects the digits of a count to an integer
                            if(!isdigit(current_cubes[j])){
                                
                                break;
                            }
                            dice_current_color *= 10;
                            dice_current_color += current_cubes[j] - 48;
                            j++;
                        }
                    }
                    else if (current_cubes[j] == ' ' || current_cubes[j] == ':'){
                        continue;
                    }
                    else {
                        printf("%d: current sum %c: %d\n", current_game, current_cubes[j], dice_current_color);
                        //as each possible color has unique starting letters, only those are checked
                        if (current_cubes[j] == 'r'){
                            if (dice_current_color > 12){
                                is_viable = 0;
                            }
                        }
                        if (current_cubes[j] == 'g'){
                            if (dice_current_color > 13){
                                is_viable = 0;
                            }
                        }
                        if (current_cubes[j] == 'b'){
                            if (dice_current_color > 14){
                                is_viable = 0;
                            }
                        }
                        i++; //this is so that the space after the colomn/semicolomn is skipped
                        break;
                    }
                }
                cube_index = 0;
                memset(current_cubes, 0, sizeof(current_cubes));
            }
            else
            {
                current_cubes[cube_index] = buffer[i];
                cube_index++;
            }
        }
        
        
        if (is_viable == 1){
            sum += current_game;
        }

        is_viable = 0;
        current_game++;
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
    int current_game = 1;
    int sum = 0;

    while (fgets(buffer, MAX_LENGTH, fp))
    {
        int min_reds = 0;
        int min_greens = 0;
        int min_blues = 0;
        char current_cubes[200]; 
        int cube_index = 0;
        
        for(int i = 8; i < strlen(buffer); i++) // beginning to read at position 5 as the "Game x: "-part of the is just incrementing
        {
            if (buffer[i] == ',' || buffer[i] == ';' || i+1 == strlen(buffer)){
                int dice_current_color = 0;
                for(int j = 0; j <= cube_index; j++){
                    if(isdigit(current_cubes[j])){
                        while(1){ //loop that connects the digits of a count to an integer
                            if(!isdigit(current_cubes[j])){
                                
                                break;
                            }
                            dice_current_color *= 10;
                            dice_current_color += current_cubes[j] - 48;
                            j++;
                        }
                        //printf("count: %d", sum_current_color);
                    }
                    else if (current_cubes[j] == ' ' || current_cubes[j] == ':'){
                        continue;
                    }
                    else {
                        printf("%d: current sum %c: %d\n", current_game, current_cubes[j], dice_current_color);
                        //as each possible color has unique starting letters, only those are checked
                        if (current_cubes[j] == 'r'){
                            if(min_reds < dice_current_color){
                                min_reds = dice_current_color;
                            }
                        }
                        if (current_cubes[j] == 'g'){
                            if(min_greens < dice_current_color){
                                min_greens = dice_current_color;
                            }
                        }
                        if (current_cubes[j] == 'b'){
                            if(min_blues < dice_current_color){
                                min_blues = dice_current_color;
                            }
                        }
                        i++; //this is so that the space after the colomn/semicolomn is skipped
                        break;
                    }
                }
                cube_index = 0;
                memset(current_cubes, 0, sizeof(current_cubes));
            }
            else
            {
                current_cubes[cube_index] = buffer[i];
                cube_index++;
            }
        }
        printf("%d: red %d, green %d, blue %d\n", current_game, min_reds, min_greens, min_blues);

        sum += min_reds * min_blues * min_greens;
        
        min_reds = 0;
        min_greens = 0;
        min_blues = 0;

        current_game++;
    }
    fclose(fp);
    return sum;
}

int main(void){
    char *filename = "day2.txt";
    int choosen_assignment = 0;
    int sum = 0;

    printf("Choose Assignment: ");
    if(!scanf("%d", &choosen_assignment)){
        printf("ERROR: No valid Input provided.\n");
        return EXIT_FAILURE;
    }
    if(choosen_assignment == 1){
        sum = part_one(filename);
        printf("The sum of all valid IDs is %d.\n", sum);
    }
    else if(choosen_assignment == 2){
        sum = part_two(filename);
        printf("The sum of the power of all Sets is %d.\n", sum);
    }
    else {
        printf("ERROR: No valid Input provided.\n");
    }
    
    return EXIT_SUCCESS;
}