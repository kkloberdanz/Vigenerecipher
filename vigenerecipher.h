/*
 * Programmer   : Kyle Kloberdanz
 * Date Created : 17 Feb 2016
 *
 * Description  : Reads an input file (specified from command line)
 *                and creates an output file (specified from command line)
 *                with the encrypted text
 *
 * File         : vigenerecipher.h
 */

#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

void printHelp();
bool isLetter(char ch);
std::string preproscess(std::string line, bool noSpaces);
std::string generateKeyString(std::string key, int size);
std::string applyCipher(std::string plainText, std::string keyString);
std::string decipher(std::string cipherText, std::string keyString);
#endif
