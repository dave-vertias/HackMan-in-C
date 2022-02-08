# HackMan-in-C
HackMan challenge 

Doing this from scratch even though I was told not to. Runs in terminal/terminal emulator. 

Supported Platforms:
  Debian/Ubuntu

Dependancies: 
  -LibCurl4-OpenSSL

Install on Ubuntu:
  sudo apt install libcurl4-openssl-dev
  
  
How to Compile and run project:

go to line 39 in source and add your API key to the query string. 


39: curl_easy_setopt(curl, CURLOPT_URL, "https://clemsonhackman.com/api/word?key=");


gcc hangman.c -lcurl -o example
  
  
  ./example
