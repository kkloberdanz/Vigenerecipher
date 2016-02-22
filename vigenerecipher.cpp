/*
 * Programmer   : Kyle Kloberdanz
 * Date Created : 17 Feb 2016
 *
 * Description  : Reads an input file (specified from command line)
 *                and creates an output file (specified from command line)
 *                with the encrypted text
 *
 * File         : vigenerecipher.cpp
 */

#include <iostream>
#include <cstdlib>
#include <cassert>

void printHelp(){
    std::cout << "Usage: To encipher:\n"
            "        ./vigenerecipher INPUTFILE OUTPUTFILE\n\n"
 
            "Encipher without spaces:\n"
            "        ./vigenerecipher INPUTFILE OUTPUTFILE --no-spaces\n\n"

            "   To decipher:\n"
            "       ./vigenerecipher INPUTFILE OUTPUTFILE -d\n\n"

            "   Decipher withoug spaces:\n\n"
            "       ./vigenerecipher INPUTFILE OUTPUTFILE -d --no-spaces\n"
 << std::endl;
}

bool isLetter(char ch){
    return (((ch >= 'a')&&(ch <= 'z')) || ((ch >= 'A')&&(ch <= 'Z')));
}

std::string preproscess(std::string line, bool noSpaces){
    // Preproscessing, remove all non alpha characters, 
    // and lowercase all letters
    std::string outputline = "";
    unsigned int i;
    for( i = 0; i < line.length(); i++ ){
        if (noSpaces){
            if( (isLetter(line[i])) ){
                if( (line[i] >= 'A') && (line[i] <= 'Z') ){
                    // 32, the distance from a to A
                    line[i] = line[i] + 32;
                }
                outputline += line[i];
            }
        } else {
            if( (isLetter(line[i])) || (line[i] == ' ') ){
                if( (line[i] >= 'A') && (line[i] <= 'Z') ){
                    // 32, the distance from a to A
                    line[i] = line[i] + 32;
                }
                outputline += line[i];
            }
        }
    }
    return outputline;
}

std::string generateKeyString(std::string key, int size){
    int i;
    std::string outputString = "";
    for( i = 0; i < size; i++ ){
        outputString += key[i%key.length()];
    }
    return outputString;
}

std::string applyCipher(std::string plainText, std::string keyString){

    assert( plainText.length() == keyString.length() );

    std::string cipherText = "";
    unsigned int i;
    char mi;
    char ki;
    for( i = 0; i < plainText.length(); i++ ){
        mi = plainText[i] - 'a';
        ki = keyString[i] - 'a';
        if( plainText[i] != ' ' ){
            cipherText += ((mi + ki + 26) % 26) + 'a';
        } else {
            cipherText += plainText[i];
        }
    }
    return cipherText;
}

std::string decipher(std::string cipherText, std::string keyString){

    assert( cipherText.length() == keyString.length() );

    std::string plainText = "";
    unsigned int i;
    char ci;
    char ki;
    for( i = 0; i < cipherText.length(); i++ ){
        ci = cipherText[i] - 'a';
        ki = keyString [i] - 'a';
        if( cipherText[i] != ' ' ){
            plainText += ((ci - ki + 26) % 26) + 'a';
        } else {
            plainText += cipherText[i];
        }
    }
    return plainText;
}


