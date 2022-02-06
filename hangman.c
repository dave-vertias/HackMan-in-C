#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <math.h>
#include <unistd.h>

#define pi 3.142857

int contains(char entered, char *word, char *hidden_word, int *win_count){
    int c = 0;
    for(int i = 0; i < strlen(word); i++){
        if(word[i] == entered){
            hidden_word[i] = word[i];
            c++;
            (*win_count)++;
        }
    }
    return c;
}

//hangman game
int main(int argc, char **argv){


    //section 1: CALL API----------------------------------------------------------------
    CURL *curl;
    FILE *fp;
    int result;

    char word[19];
    word[18] = 0;

    fp = fopen("word.json", "wb");

    curl = curl_easy_init();

    //set URL and operations
    curl_easy_setopt(curl, CURLOPT_URL, "https://clemsonhackman.com/api/word?key=");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

    result = curl_easy_perform(curl);

    if(result == CURLE_OK){
        result = 0;
    }
    else
        printf("Error: %s\n\n", curl_easy_strerror(result));

    fclose(fp);
    curl_easy_cleanup(curl);


    //section 2 PARSE JSON----------------------------------------------------------------
    char *buffer = 0;
    long length;
    FILE *f = fopen ("word.json", "r");

    if (f)
    {
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer)
    {
        fread (buffer, 1, length, f);
    }
        fclose (f);
    }

    int count = 0;
    int win_count = 0;
    for(int i = 9, j = 0; i < strlen(buffer)-1; i++, j++){
        word[j] = buffer[i];
        count++;
    }
    word[count-1] = 0;
    if(word[count-2] == '"')
        word[count-2] = 0;

    count = 0;
    char hidden_word[strlen(word)];

    for(int i = 0; i < strlen(word); i++){
        hidden_word[i] = '*';
    }
    hidden_word[strlen(word)] = 0;

    //section 3 Graphics and game itself-------------------------------------------------

    char guessing = 0;
    while(1){
        system("clear");
        printf("\n\n====================================\n");
        printf("|       Welcome To HangMan         |\n");
        printf("====================================\n\n");

        printf("\n________________\n");
        //rope
        if (count==0)
        printf("|          \n"
               "|          \n"
               "|         \n"
               "|          \n"
               "|          \n"
               "|           \n");

        else if (count==1)
        printf("|          |\n"
               "|          \n"
               "|         \n"
               "|          \n"
               "|          \n"
               "|           \n");
        else if (count==2)
        printf("|          |\n"
               "|          O\n"
               "|         \n"
               "|          \n"
               "|          \n"
               "|           \n");
        else if (count==3)
        printf("|          |\n"
               "|          O\n"
               "|          |\n"
               "|          \n"
               "|          \n"
               "|           \n");
        else if (count==4)
        printf("|          |\n"
               "|          O\n"
               "|         /|\n"
               "|          \n"
               "|          \n"
               "|           \n");
        else if (count==5)
        printf("|          |\n"
               "|          O\n"
               "|         /|\\\n"
               "|          \n"
               "|          \n"
               "|           \n");
        else if (count==6)
        printf("|          |\n"
               "|          O\n"
               "|         /|\\\n"
               "|          /\n"
               "|          \n"
               "|           \n");
        else if (count>=7){
        
        printf("|          |\n"
               "|          O\n"
               "|         /|\\\n"
               "|          /\\\n"
               "|          \n"
               "|           \n");
        printf("GAME OVER! YOU LOST!\n\n");
        printf("Word: %s\n\n",word);
        exit(0);
        }
        if(win_count == (int)strlen(word)){
            system("clear");
            printf("\n\nYOU WIN!!\n\n");
            printf("\nWord: %s\n\n", word);
            exit(0);
        }

        printf("Word to Guess: %s\n", hidden_word);
        printf("\n\nEnter a character to guess: ");
        scanf(" %c",&guessing);
        printf("\n");

        if(contains(guessing, word, hidden_word, &win_count) == 0){
            count++;
        } 
        
        system("clear");
    }
    return 0;
    }
