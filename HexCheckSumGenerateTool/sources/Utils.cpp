#include "pch.h"
#include "Utils.h"



Utils::Utils(/* args */)
{
}

Utils::~Utils()
{
}

void Utils::test(void)
{

}

uint8_t _s2b(const char ch)
{
    if((ch >= '0') && (ch <= '9')){
        return ch - '0';
    }
    else if((ch >= 'a') && (ch <= 'f')){
        return ch - 'a' + 10;
    }
    else if((ch >= 'A') && (ch <= 'F')){
        return ch - 'A' + 10;
    }
    return (uint8_t)-1;
}

bool Utils::HexToStr(const uint8_t* pHex, const int nHexLength, char* pStr)
{
    int i = 0, j = 0;
    char* p = pStr;
    for (; i < nHexLength; i++) {
        //_itoa_s(pHex[i], p, 3, 0x10);
        sprintf_s(p, 3, "%02X", pHex[i]);
        p += 2;
    }
    return true;
}

bool Utils::StrToHex(const char* str, const int strLength, uint8_t* hex)
{
    if (strLength & 0x01) {
        return false;
    }
    int i = 0;
    int j = 0;
    for(; i < strLength; i += 2){
        hex[j++] = (_s2b(str[i]) << 0x04) + (_s2b(str[i + 1]) & 0x0F);
    }
    return true;
}

bool Utils::WStrToStr(const wchar_t* wstr, char* str)
{
    return true;
}

bool Utils::StrToWStr(const char* str, wchar_t* wstr)
{
    return true;
}


bool Utils::WStrToStr(std::wstring wstr, std::string& str)
{
    size_t length = WideCharToMultiByte(CP_ACP, 0,
        wstr.c_str(), wstr.length(),
        NULL, 0,
        NULL, NULL);
    char* tempStr = new char[length * 2];
    WideCharToMultiByte(CP_ACP, 0,
        wstr.c_str(), wstr.length(),
        tempStr, length,
        NULL, NULL);
    tempStr[length] = 0;
    str = tempStr;
    delete[]tempStr;
    return true;
}

bool Utils::StrToWStr(std::string str, std::wstring& wstr)
{
    size_t length = MultiByteToWideChar(CP_ACP, 0,
        str.c_str(), str.length(),
        NULL, 0);
    wchar_t* tempStr = new wchar_t[length + 1];
    MultiByteToWideChar(CP_ACP, 0,
        str.c_str(), str.length(),
        tempStr, length);
    tempStr[length] = 0;
    wstr = tempStr;
    delete[]tempStr;
    return true;
}
