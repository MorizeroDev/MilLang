#include <string>
#include <windows.h>
#include <vector>

#include <MiLang/lib.h>

std::string getString(std::vector<wchar_t> data) {
    std::string result;
    bool newFlag = false;
    for (auto rune: data) {
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

std::string getUserDefaultLocal() {
    const int bufferLength = LOCALE_NAME_MAX_LENGTH + 128;
    std::vector<wchar_t> localeBuffer(static_cast<int>(bufferLength));
    const auto result = GetUserDefaultLocaleName(localeBuffer.data(),bufferLength);
    if (result == 0) {
        return "";
    }

    return getString(localeBuffer);
}

std::string getUserLanguage() {
    ULONG numberOfLanguages = 0;
    DWORD bufferLength = 0;
    const auto result1 = GetUserPreferredUILanguages(MUI_LANGUAGE_NAME,
                                                     &numberOfLanguages,
                                                     nullptr,
                                                     &bufferLength);
    if (result1 == 0) {
        return "";
    }

    std::vector<wchar_t> languagesBuffer(static_cast<int>(bufferLength));
    const auto result2 = GetUserPreferredUILanguages(MUI_LANGUAGE_NAME,
                                                     &numberOfLanguages,
                                                     languagesBuffer.data(),
                                                     &bufferLength);
    if (result2 == 0) {
        return "";
    }

    return getString(languagesBuffer);
}

std::string getResult() {
    auto s1 = getUserDefaultLocal();
    auto s2 = getUserLanguage();

    if (s1.length() == 0 && s2.length() == 0) {
        return "";
    }
    if (s1.length() == 0) {
        return s2;
    }
    if (s2.length() == 0) {
        return s1;
    }
    return s1 + ":" + s2;
}

void getLocale(char *buffer, size_t bufferSize) {
    auto result = getResult();
    auto resultCStr = result.c_str();
    auto len = result.length();
    if (len > bufferSize - 1) {
        len = bufferSize - 1;
    }
    memset(buffer, 0, bufferSize);
    memcpy(buffer, resultCStr, len); // NOLINT(*-not-null-terminated-result)
}
