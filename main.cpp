/*
 * Programmer   : Kyle Kloberdanz
 * Date Created : 17 Feb 2016
 *
 * Description  : Reads an input file (specified from command line)
 *                and creates an output file (specified from command line)
 *                with the encrypted text
 *
 * File         : main.cpp
 *
 * Usage        : To encipher:
 *                    ./vigenerecipher INPUTFILE OUTPUTFILE
 *
 *                Encipher without spaces:
 *                    ./vigenerecipher INPUTFILE OUTPUTFILE --no-spaces
 *
 *                To decipher:
 *                    ./vigenerecipher INPUTFILE OUTPUTFILE -d
 *
 *                Decipher withoug spaces:
 *                    ./vigenerecipher INPUTFILE OUTPUTFILE -d --no-spaces
 *
 * Notes        : Compiled with g++ (Debian 5.3.1-8) (stretch-sid)
 *                and GNU Make 4.1
 *
 *                For best results, compile and run with a linux system
 *                (Not tested for Windows, OSX, or any other OS)
 *
 *                To compile, ensure you are in the same directory as the
 *                Makefile, then type 'make'
 *
 *                To compile without make, type:
 *  'g++ main.cpp vigenerecipher.cpp -o vigenerecipher -Wall -Wextra -O2 -std=gnu++11'
 *
 */

#include <iostream>
#include <cstdlib>
#include <fstream>

#include "vigenerecipher.h"

int main(int argc, char* argv[]){

    /*
     * input handling
     */
    bool setDecrypt = false;
    bool noSpaces   = false;
    if( (argc > 1) && ((std::string)argv[1] == "--help" ) ){
        printHelp();
        exit(EXIT_FAILURE);

    } else if( (argc == 4) && ((std::string)argv[3] == "-d") ){
        setDecrypt = true;

    } else if ( (argc == 4) && ((std::string)argv[3] == "--no-spaces") ) {
        noSpaces = true;

    } else if ( (argc == 5) && ((std::string)argv[3] == "-d") 
                            && ((std::string)argv[4] == "--no-spaces")){
        setDecrypt = true;
        noSpaces = true;

    } else if( argc < 3 ){
        std::cout << "vigenerecipher: not enough input arguments" << std::endl;
        std::cout << "(Type vigenerecipher --help for usage)" << std::endl;
        exit(EXIT_FAILURE);

    } else if( argc > 3 ){
        std::cout << "vigenerecipher: too many input arguments" << std::endl;
        std::cout << "(Type vigenerecipher --help for usage)" << std::endl;
        exit(EXIT_FAILURE);
    }
    char* inputFilename = argv[1]; 

    std::ifstream inputFile;

    inputFile.open(inputFilename);

    if( !inputFile.is_open() ){
        std::cout << "vigenerecipher: Could not open file: " << inputFilename 
            << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ofstream outputFile;
    char* outputFilename = argv[2];

    outputFile.open(outputFilename);

    // key will be used to encrypt the text
    std::string key = "";
    std::cout << (setDecrypt? "Enter key to decrypt: " :
                         "Enter key to encrypt: ");
    std::cin >> key;

    std::string line;
    std::string plainText = "";
    std::string keyString = "";
    std::string cipherText = "";
    std::string decipheredText = "";

    if( setDecrypt ){
        while( getline(inputFile, line) ){
            // remove non-alpha characters and lowercase all letters
            cipherText = preproscess(line, noSpaces);

            // makes a std::string of the key repeated for the length of line
            keyString  = generateKeyString(key, cipherText.length());

            // decipher text
            decipheredText = decipher(cipherText, keyString);

            outputFile << decipheredText << std::endl;
        }

    } else {

        while( getline(inputFile, line) ){
            // remove non-alpha characters and lowercase all letters
            plainText  = preproscess(line, noSpaces);

            // makes a std::string of the key repeated for the length of line
            keyString  = generateKeyString(key, plainText.length());

            // apply cipher to line
            cipherText = applyCipher(plainText, keyString);

            outputFile << cipherText << std::endl;
        }
    }

    outputFile.close();
    inputFile.close();
    return 0;
}

