#ifndef _STRING_UTILS_H_
#define _STRING_UTILS_H_

#include <string>
#include <windows.h>

// It is recommended to use inline functions in header files 
// to avoid LNK2005 errors when included from multiple source files.

// Convert UTF-8 std::string to UTF-16 std::wstring
inline std::wstring Utf8ToWide(const std::string& utf8_str) {
    if (utf8_str.empty()) return std::wstring();
    int wide_len = MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, NULL, 0);
    if (wide_len <= 1) return std::wstring();
    std::wstring wide_str(wide_len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, &wide_str[0], wide_len);
    wide_str.resize(wide_len - 1);
    return wide_str;
}

// Convert CP932 (Shift_JIS) std::string to UTF-16 std::wstring
inline std::wstring Cp932ToWide(const std::string& cp932_str) {
    if (cp932_str.empty()) return std::wstring();
    int wide_len = MultiByteToWideChar(932, 0, cp932_str.c_str(), -1, NULL, 0);
    if (wide_len <= 1) return std::wstring();
    std::wstring wide_str(wide_len, L'\0');
    MultiByteToWideChar(932, 0, cp932_str.c_str(), -1, &wide_str[0], wide_len);
    wide_str.resize(wide_len - 1);
    return wide_str;
}

// Convert UTF-16 std::wstring to CP932 (Shift_JIS) std::string
inline std::string WideToCp932(const std::wstring& wide_str) {
    if (wide_str.empty()) return std::string();
    int cp932_len = WideCharToMultiByte(932, 0, wide_str.c_str(), -1, NULL, 0, NULL, NULL);
    if (cp932_len <= 1) return std::string();
    std::string cp932_str(cp932_len, '\0');
    WideCharToMultiByte(932, 0, wide_str.c_str(), -1, &cp932_str[0], cp932_len, NULL, NULL);
    cp932_str.resize(cp932_len - 1);
    return cp932_str;
}

// Convert CP932 (Shift_JIS) to UTF-8
inline std::string Cp932ToUtf8(const std::string& cp932_str) {
    if (cp932_str.empty()) return "";
    std::wstring wide_str = Cp932ToWide(cp932_str);
    if (wide_str.empty()) return "";

    int utf8_len = WideCharToMultiByte(CP_UTF8, 0, wide_str.c_str(), -1, NULL, 0, NULL, NULL);
    if (utf8_len <= 1) return "";
    std::string utf8_str(utf8_len, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wide_str.c_str(), -1, &utf8_str[0], utf8_len, NULL, NULL);
    utf8_str.resize(utf8_len - 1);
    return utf8_str;
}

// Convert UTF-8 to CP932 (Shift_JIS)
inline std::string Utf8ToCp932(const std::string& utf8_str) {
    if (utf8_str.empty()) return std::string();
    std::wstring wide_str = Utf8ToWide(utf8_str);
    return WideToCp932(wide_str);
}

#endif // _STRING_UTILS_H_
