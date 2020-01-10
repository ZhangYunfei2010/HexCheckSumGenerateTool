#include "pch.h"
#include <fstream>
#include "Utils.h"
#include "HexTools.h"


HexTools::HexTools()
{

}
HexTools::~HexTools()
{
        
}

bool HexTools::verifyHex(uint8_t* hex, int hexLength)
{
    return true;
}

uint8_t HexTools::GenerateCheckSum(uint8_t* hex, int hexLength)
{
    uint8_t CheckSum = 0;
    for(int i = 0; i < hexLength; i++){
        CheckSum += hex[i];
    }
    CheckSum = 0x100 - CheckSum;
    return CheckSum;
}

bool HexTools::GenerateCheckSum(const char* hexStr, char* checkSumStr)
{
    int length = strlen(hexStr);
    uint8_t* hex = new uint8_t[length / 2];
    const char* pHexStr = hexStr;
    if (pHexStr[0] == ':') {
        pHexStr++;
        length--;
    }
    if (!Utils::StrToHex(pHexStr, length, hex)) {
        return false;
    }
    uint8_t CheckSum = GenerateCheckSum(hex, length / 2);
    if (!Utils::HexToStr(&CheckSum, 1, checkSumStr)) {
        return false;
    }
    return true;
}

bool HexTools::GenerateCheckSum(const char* inFileName, const char* outFileName)
{
    std::fstream infs(inFileName, std::ios::in);
    if(!infs){
        return false;
    }
    char text[1024];
    char checkSum[3];
    infs.seekg(std::ios::beg);

    std::list<std::string> outStr;
    while(infs.getline(text, 1024)){
        uint8_t hexLen = 0;
        Utils::StrToHex(text + 1, 2, &hexLen);
        if((2 * (hexLen + 4)) == (strlen(text)&0xFFFFFFFE)){
            
        }
        else if((2 * (hexLen + 5)) == (strlen(text)&0xFFFFFFFE)){
            text[strlen(text) - 2] = 0x00;
        }
        else{
            return false;
        }
        if (!GenerateCheckSum(text, checkSum)) {
            return false;
        }
        outStr.push_back(std::string(text) + std::string(checkSum) + std::string("\r\n"));
    }
    infs.close();

    std::fstream outfs(outFileName, std::ios::binary | std::ios::out);
    if(!outfs){
        return false;
    }
    outfs.seekg(std::ios::beg);
    for(std::list<std::string>::iterator it = outStr.begin(); it != outStr.end(); it++){
        outfs.write((*it).c_str(), (*it).length());
    }
    outfs.close();
    return true;
}
