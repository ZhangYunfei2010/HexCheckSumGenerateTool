#pragma once

class HexTools
{
private:

protected:

public:
    HexTools();
    ~HexTools();

public:
    static bool verifyHex(uint8_t* hex, int hexLength);
    static uint8_t GenerateCheckSum(uint8_t* hex, int hexLength);
    static bool GenerateCheckSum(const char* hex, char* checkSum);
    bool AppendCheckSum(char* hex);
    static bool GenerateCheckSum(const char* inFileName, const char* outFileName);
};

