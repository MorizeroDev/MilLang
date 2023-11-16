#include <CoreFoundation/CoreFoundation.h>

// change it to CFLocaleCopyPreferredLanguages
extern "C"
void getLocale(char *buffer) {
    memset(buffer,0,16);

    CFArrayRef arr = CFLocaleCopyPreferredLanguages();
    auto count = CFArrayGetCount(arr);
    if (count == 0) {
        return;
    }

    auto value = (CFStringRef) CFArrayGetValueAtIndex(arr,0);
    CFStringGetCString(value, buffer, 15, kCFStringEncodingUTF8);
    CFRelease(arr);
}

//extern "C"
//void getLocale(char *buffer) {
//    CFLocaleRef cflocale = CFLocaleCopyCurrent();
//    auto value = (CFStringRef) CFLocaleGetValue(cflocale, kCFLocaleIdentifier);
//    CFStringGetCString(value, buffer, 16, kCFStringEncodingUTF8);
//    CFRelease(cflocale);
//}
