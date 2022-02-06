#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>


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
    curl_easy_setopt(curl, CURLOPT_URL, "https://clemsonhackman.com/api/word?key=26392");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

    result = curl_easy_perform(curl);

    if(result == CURLE_OK)
        printf("Download Complete\n\n");
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

    printf("%s\n\n",buffer);

    int count = 0;
    for(int i = 9, j = 0; i < strlen(buffer)-1; i++, j++){
        word[j] = buffer[i];
        count++;
    }
    word[count-1] = 0;
    printf("%s\n\n",word);

    //section 3 Graphics and game itself. 

    return 0;
    }
