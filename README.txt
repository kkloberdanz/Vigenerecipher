Programmer   : Kyle Kloberdanz
Date Created : 17 Feb 2016

Description  : Reads an input file (specified from command line)
               and creates an output file (specified from command line)
               with the encrypted text

               The cipher takes in a key, and shifts the letters
               of the plaintext according to the letters of the key
               to generate the encrypted text

               The key I used to test the program is: tesla

File         : main.cpp

Usage        : To encipher:
                   ./vigenerecipher INPUTFILE OUTPUTFILE

               Encipher without spaces:
                   ./vigenerecipher INPUTFILE OUTPUTFILE --no-spaces

               To decipher:
                   ./vigenerecipher INPUTFILE OUTPUTFILE -d

               Decipher withoug spaces:
                   ./vigenerecipher INPUTFILE OUTPUTFILE -d --no-spaces

Notes        : Compiled with g++ (Debian 5.3.1-8) (stretch-sid)
               and GNU Make 4.1

               For best results, compile and run with a linux system
               (Not tested for Windows, OSX, or any other OS)

               To compile, ensure you are in the same directory as the
               Makefile, then type 'make'

               To compile without make, type:
 'g++ main.cpp vigenerecipher.cpp -o vigenerecipher -Wall -Wextra -O2 -std=gnu++11'


