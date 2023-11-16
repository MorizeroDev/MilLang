#include <CoreFoundation/CoreFoundation.h>

extern "C"
void getLocale(char *buffer) {
    memset(buffer, 0, 4096);

    CFArrayRef arr = CFLocaleCopyPreferredLanguages();
    auto count = CFArrayGetCount(arr);
    size_t dstIdx = 0;

    for (int i = 0; i < count; i++) {
        auto value = (CFStringRef) CFArrayGetValueAtIndex(arr, i);
        char tmpBuffer[128];
        bool succeed = CFStringGetCString(value, tmpBuffer, 128, kCFStringEncodingUTF8);
        if (succeed) {
            strcpy(buffer + dstIdx, tmpBuffer);
            dstIdx += strlen(tmpBuffer);
            buffer[dstIdx] = ':';
            dstIdx++;
        }
    }

    if (dstIdx > 1) {
        buffer[dstIdx - 1] = '\0';
        dstIdx--;
    }
    CFRelease(arr);
}
