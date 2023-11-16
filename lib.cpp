#include<CoreFoundation/CoreFoundation.h>
#include<string>
#include <numeric>

extern "C"
void getLocale(char *buffer, size_t bufferSize) {
    CFArrayRef arr = CFLocaleCopyPreferredLanguages();
    auto count = CFArrayGetCount(arr);

    std::vector<std::string> localeList;
    for (int i = 0; i < count; i++) {
        auto value = (CFStringRef) CFArrayGetValueAtIndex(arr, i);
        char tmpBuffer[128];
        bool succeed = CFStringGetCString(value, tmpBuffer, 128, kCFStringEncodingUTF8);
        if (!succeed) {
            continue;
        }
        auto s = std::string(tmpBuffer);
        localeList.push_back(s);
    }
    CFRelease(arr);

    auto result = std::accumulate(
            std::next(localeList.begin()),localeList.end(),localeList[0],
            [](const std::string& a, const std::string b) {
                return a + ":" + b;
            }
    );
    auto resultCStr = result.c_str();

    auto len = result.length();
    if (len > bufferSize - 1) {
        len = bufferSize - 1;
    }
    memset(buffer, 0, bufferSize);
    memcpy(buffer, resultCStr, len);
}
