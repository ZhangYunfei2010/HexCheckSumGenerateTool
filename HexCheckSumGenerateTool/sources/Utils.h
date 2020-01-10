#pragma once

struct Utils
{
private:
    void test(void);
public:
    Utils(/* args */);
    ~Utils();
    static bool HexToStr(const uint8_t* hex, const int hexLength, char* str);
    static bool StrToHex(const char* str, const int strLength, uint8_t* hex);
    static bool WStrToStr(const wchar_t* wstr, char* str);
    static bool StrToWStr(const char* str, wchar_t* wstr);
    static bool WStrToStr(std::wstring wstr, std::string& str);
    static bool StrToWStr(std::string str, std::wstring& wstr);
};
