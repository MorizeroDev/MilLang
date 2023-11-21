#include <string>
#include <windows.h>
#include <vector>


std::string getLocale() {
    ULONG numberOfLanguages = 0;
    DWORD bufferLength = 0;
    const auto result1 = GetUserPreferredUILanguages(MUI_LANGUAGE_NAME,
                                                     &numberOfLanguages,
                                                     nullptr,
                                                     &bufferLength);
    if (!result1) {
        return "";
    }

    std::vector<wchar_t> languagesBuffer(static_cast<int>(bufferLength));
    const auto result2 = GetUserPreferredUILanguages(MUI_LANGUAGE_NAME,
                                                     &numberOfLanguages,
                                                     languagesBuffer.data(),
                                                     &bufferLength);
    if (!result2) {
        return "";
    }

    std::string result;
    bool newFlag = false;
    for (auto rune: languagesBuffer) {
        if (rune != '\0') {
            if (newFlag) {
                result += ':';
                newFlag = false;
            }
            result += rune;
        } else {
            newFlag = true;
        }
    }
    return result;
}

extern "C"
void getLocale(char *buffer, size_t bufferSize) {
    auto result = getLocale();
    auto resultCStr = result.c_str();
    auto len = result.length();
    if (len > bufferSize - 1) {
        len = bufferSize - 1;
    }
    memset(buffer, 0, bufferSize);
    memcpy(buffer, resultCStr, len); // NOLINT(*-not-null-terminated-result)
}
