#pragma once
#include <Arduino.h>

namespace Convert
{
    const char* fromString(const String& value) { return value.c_str(); }

    template <size_t size>
    struct same_size_int;

    template <size_t size>
    using same_size_int_t = typename same_size_int<size>::type;

    template <> struct same_size_int<1> { using type = int8_t; };
    template <> struct same_size_int<2> { using type = int16_t; };
    template <> struct same_size_int<4> { using type = int32_t; };
    template <> struct same_size_int<8> { using type = int64_t; };

    template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
    struct IntFloatUnion_impl {
        using type = union {
            same_size_int_t<sizeof(T)> x;
            T f;
        };
    };

    template <typename T>
    using IntFloatUnion = typename IntFloatUnion_impl<T>::type;

    template <typename T, size_t length = sizeof(T) * 2>
    auto toHex(T value)
    -> typename std::enable_if<std::is_integral<T>::value, String>::type
    {
        String format = "%0" + String(length) + "X";
        char hex[length + 1];

        sprintf(hex, format.c_str(), value);
        return String(hex);
    }

    int toInt(const String& intString) { return intString.toInt(); }

    int fromHexToInt(const String& intHexString) { return (int)strtol(intHexString.c_str(), NULL, 16); }

    char fromHexToChar(const String& charHexString) { return (char)strtol(charHexString.c_str(), NULL, 16); }

    float fromHexToFloat(const String& floatHexString)
    {
        IntFloatUnion<float> myUnion;
        myUnion.x = toIntegral<same_size_int_t<float>>(floatHexString);
        return myUnion.f;
    }
        return myUnion.f;
    }

    float toFloat(const String& floatString) { return floatString.toFloat(); }

    bool toBool(const String& boolString)
    {
        auto lower = boolString;
        lower.toLowerCase();
        if(lower == "true") return true;
        if(lower == "false") return false;
        LOG_WARNING("can not recognize the string");
        return false;
    }

    char toChar(const String& charString)
    {
        char c[] = {0};
        charString.toCharArray(c, charString.length());
        return *c;
    }

//    String toBinary(const String& value)
//    {
//        String out("");
//        size_t numBytes = value.length();
//        for(size_t i = 0; i < numBytes; i++) {
//            std::bitset<8> bitBuffer(value.c_str()[i]);
//            out += String(bitBuffer.to_ulong(), BIN);
//        }
//        return out;
//    }
//
//    String toBinary(const char* value) { return toBinary(String(value)); }
//
//    int fromBinaryToInt(const String& value)
//    {
//        const size_t intSize = sizeof(int) * 8;
//        std::bitset<intSize> binaryString(value.c_str()[0]);
//        return (int)binaryString.to_ulong();
//    }
//
//    char fromBinaryToChar(const String& value)
//    {
//        const size_t charSize = sizeof(char) * 8;
//        std::bitset<charSize> binaryString(value.c_str()[0]);
//        return (char) binaryString.to_ulong();
//    }
//
//    float fromBinaryToFloat(const String& value)
//    {
//        const size_t floatSize = sizeof(float) * 8;
//        std::bitset<floatSize> binaryString(value.c_str()[0]);
//        union ulongFloatUnion {
//                unsigned long result;
//                float f;
//        } myUFUnion;
//        myUFUnion.result = binaryString.to_ulong();
//        return myUFUnion.f;
//    }
//
//    template <class T>
//    String toBinary(const T& value) {
//        return std::bitset<8 * sizeof(T)>(*reinterpret_cast<const uint64_t*>(&value)).to_string();
//    }
}

// void uint8_to_hex_no_zero(uint8_t num, char *str, bool upper = false)
// {
//     if (upper)  sprintf(str, "%X", num);
//     else        sprintf(str, "%x", num);
// }
// void uint8_to_hex(uint8_t num, char *str, bool upper = false)
// {
//     if (upper)  sprintf(str, "%02X", num);
//     else        sprintf(str, "%02x", num);
// }
// void uint16_to_hex(uint16_t num, char *str, bool upper = false)
// {
//     if (upper)  sprintf(str, "%04X", num);
//     else        sprintf(str, "%04x", num);
// }
// void uint32_to_hex(uint32_t num, char *str, bool upper = false)
// {
//     char s_h[5] = {'\0'};
//     char s_l[5] = {'\0'};
//     uint16_t num_h = (num >> 16) & 0xFFFF;
//     uint16_t num_l = (num >>  0) & 0xFFFF;
//     uint16_to_hex(num_h, s_h);
//     uint16_to_hex(num_l, s_l);
//
//     String str_h = String(s_h);
//     String str_l = String(s_l);
//     String str_a = str_h + str_l;
//
//     str_a.toCharArray(str, 9);
// }
// void uint64_to_hex(uint64_t num, char *str, bool upper = false)
// {
//     char s_hh[5] = {'\0'};
//     char s_hl[5] = {'\0'};
//     char s_lh[5] = {'\0'};
//     char s_ll[5] = {'\0'};
//     uint16_t num_hh = (num >> 48) & 0xFFFF;
//     uint16_t num_hl = (num >> 32) & 0xFFFF;
//     uint16_t num_lh = (num >> 16) & 0xFFFF;
//     uint16_t num_ll = (num >>  0) & 0xFFFF;
//     uint16_to_hex(num_hh, s_hh);
//     uint16_to_hex(num_hl, s_hl);
//     uint16_to_hex(num_lh, s_lh);
//     uint16_to_hex(num_ll, s_ll);
//
//     String str_hh = String(s_hh);
//     String str_hl = String(s_hl);
//     String str_lh = String(s_lh);
//     String str_ll = String(s_ll);
//     String str_a = str_hh + str_hl + str_lh + str_ll;
//
//     str_a.toCharArray(str, 17);
// }
//
// template <typename T>
// void nun_to_char(T num, char *str, const char* format)
// {
//     sprintf(str, format, num);
// }
//
// String uint8_to_String(uint8_t num, bool upper = false)
// {
//     char s[] = {0};
//     uint8_to_hex(num, s, upper);
//     return String(s);
// }
