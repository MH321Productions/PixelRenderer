#include <iostream>
#include <string>

#include "PixelRenderer/Unicode.hpp"

using namespace std;

//Bitmasks and header values for code detection
enum ByteHeaders : unsigned char {NotAscii = 0x80, TwoBytes = 0xE0, ThreeBytes = 0xF0, FourBytes = 0xF8, FollowByte = 0xC0,
    TwoBytesContent = FollowByte, ThreeBytesContent = TwoBytes, FourBytesContent = ThreeBytes, FollowByteContent = NotAscii
};

enum MultiByteLimits: uint32_t {OneByteLimit = 0x7F, TwoByteLimit = 0x7FF, ThreeByteLimit = 0xFFFF, FourByteLimit = 0x10FFFF};

enum MultiByteContent: uint32_t {
    TwoByteOne = 0x7C0, TwoByteTwo = 0x3F,
    ThreeByteOne = 0xF000, ThreeByteTwo = 0xFC0, ThreeByteThree = TwoByteTwo,
    FourByteOne = 0x1C0000, FourByteTwo = 0x3F000, FourByteThree = ThreeByteTwo, FourByteFour = TwoByteTwo
};

const uint32_t String32::replacementCharacter = 0xFFFD;

vector<uint32_t> String32::FromUTF8(const char* text, const std::size_t& max) {
    vector<uint32_t> res;
    unsigned char currentChar;
    uint32_t realChar;

    for (size_t i = 0; i < max; i++) {
        currentChar = text[i];
        if (currentChar == '\0') break; //'\0' is always the last char of a C-string

        if (currentChar & NotAscii) { //Multibyte Character

            if ((currentChar & TwoBytes) == TwoBytesContent) { //Two Bytes
                unsigned char nextChar = text[i + 1];
                if ((nextChar & FollowByte) == FollowByteContent) { //Check if following Byte is valid
                    //Take the last 5 Bits from the first and the last 6 Bits from the second character
                    //0000 ... 0111 1122 2222
                    realChar = ((currentChar & ~TwoBytes) << 6) | (nextChar & ~FollowByte);

                    /**
                     * Only append the character if it is bigger than 128 (not in ASCII).
                     * This is forbidden by the Unicode standard for safety reasons
                     */ 
                    if (realChar <= OneByteLimit) res.push_back(replacementCharacter);
                    else res.push_back(realChar);

                    i++; //Jump over the next character as it's already used
                } else {
                    //In case of an error, use the replacement character
                    res.push_back(replacementCharacter);
                }

            } else if ((currentChar & ThreeBytes) == ThreeBytesContent) { //Three Bytes
                unsigned char c2 = text[i + 1], c3 = text[i + 2];

                if ((c2 & FollowByte) == FollowByteContent && (c3 & FollowByte) == FollowByteContent) { //Check if the next 2 Bytes are valid
                    //0000 .... 1111 2222 2233 3333
                    realChar = ((currentChar & ~ThreeBytes) << 12) | ((c2 & ~FollowByte) << 6) | (c3 & ~FollowByte);

                    if (realChar <= TwoByteLimit) res.push_back(replacementCharacter);
                    else res.push_back(realChar);

                    i += 2;
                } else {
                    res.push_back(replacementCharacter);
                }

            } else if ((currentChar & FourBytes) == FourBytesContent) { //Four Bytes
                unsigned char c2 = text[i + 1], c3 = text[i + 2], c4 = text[i + 3];

                if ((c2 & FollowByte) == FollowByteContent && (c3 & FollowByte) == FollowByteContent && (c4 & FollowByte) == FollowByteContent) {
                    //0000 .... 0001 1122 2222 3333 3344 4444
                    realChar = ((currentChar & ~ThreeBytes) << 18) | ((c2 & ~FollowByte) << 12) | ((c3 & ~FollowByte) << 6) | (c4 & ~FollowByte);

                    if (realChar <= ThreeByteLimit || realChar > FourByteLimit) res.push_back(replacementCharacter);
                    else res.push_back(realChar);

                    i += 3;
                } else {
                    res.push_back(replacementCharacter);
                }

            /**
             * This is a failsafe in case someone uses an illegal character (like 0b111110xx, the start of a 5 Byte sequence).
             * Every followup character is skipped unless decoded by the above functions
             */ 
            } else if (currentChar & FollowByte == FollowByteContent) {
                continue;

            } else { //Charakter couldn't be decoded, add a replacement character and move on
                res.push_back(replacementCharacter);
            }

        } else { //ASCII
            res.push_back((uint32_t) currentChar);
        }
    }

    return res;
}

string String32::ToUTF8(const std::vector<uint32_t>& data) {
    vector<char> res;

    for (const uint32_t& c: data) {
        if (c <= OneByteLimit) res.push_back((char) c);
        else if (c > OneByteLimit && c <= TwoByteLimit) {
            //Add Two-Byte header and content of the 11 Bits
            res.push_back(TwoBytesContent | ((c & TwoByteOne) >> 6));
            res.push_back(FollowByteContent | (c & TwoByteTwo));
        } else if (c > TwoByteLimit && c <= ThreeByteLimit) {
            res.push_back(ThreeBytesContent | ((c & ThreeByteOne) >> 12));
            res.push_back(FollowByteContent | ((c & ThreeByteTwo) >> 6));
            res.push_back(FollowByteContent | (c & ThreeByteThree));
        } else if (c > ThreeByteLimit && c <= FourByteLimit) {
            res.push_back(FourBytesContent | ((c & FourByteOne) >> 18));
            res.push_back(FollowByteContent | ((c & FourByteTwo) >> 12));
            res.push_back(FollowByteContent | ((c & FourByteThree) >> 6));
            res.push_back(FollowByteContent | (c & FourByteFour));
        }
    }

    //Add \0 as last character
    res.push_back('\0');

    return string(res.data());
}