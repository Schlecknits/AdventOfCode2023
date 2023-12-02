#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int part_one(char* filename){
    FILE *fp = fopen(filename, "r");
    printf("I'm here");

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
        int reds = 0;
        int greens = 0;
        int blues = 0;
        char current_cubes[16]; 
        int cube_index = 0;
        for(int i = 8; i < strlen(buffer); i++) // beginning to read at position 5 as the "Game x: "-part of the is just incrementing
        {
            if(current_cubes[cube_index] != ',' || current_cubes[cube_index] != ';'){
                current_cubes[cube_index] = buffer[i];
                cube_index++;
            }
            else{
                int sum_current_color = 0;
                for(int j = 0; j <= cube_index; j++){
                    if(isdigit(current_cubes[j])){
                        while(1){ //loop that connects the digits of a count to an integer
                            if(!isdigit(current_cubes[j])){
                                break;
                            }
                            sum_current_color *= 10;
                            sum_current_color += current_cubes[j] - 48;
                            j++;
                        }
                    }
                    else if (current_cubes[j] == ' '){
                        continue;
                    }
                    else {
                        //as each possible color has unique starting letters, only those are checked
                        if (current_cubes[j] == 'r'){
                            reds += sum_current_color;
                        }
                        if (current_cubes[j] == 'g'){
                            greens += sum_current_color;
                        }
                        if (current_cubes[j] == 'b'){
                            blues += sum_current_color;
                        }
                        i++; //this is so that the space after the colomn/semicolomn is skipped
                        break;
                    }
                }
                cube_index = 0;
                memset(current_cubes, 0, sizeof(current_cubes));
            }
        }
        
        //check if game is possible
        if (reds <= 12 && greens <= 13 && blues <= 14){
            sum += current_game;
        }

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
    int sum = 0;
    fclose(fp);
    return 0;
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