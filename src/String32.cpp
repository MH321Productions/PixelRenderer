#include <iostream>

#include "PixelRenderer/Unicode.hpp"

using namespace std;

namespace PixelRenderer {
    
    const size_t String32::npos = static_cast<size_t>(-1);

    String32::String32(const char32_t* text, const std::size_t& max) : sizeIntern(0) {
        for (size_t i = 0; i < max; i++) {
            if (text[i] == '\0') break; //'\0' is always the last char of a C-string

            data.push_back((uint32_t) text[i]);
            sizeIntern++;
        }
    }

    String32::String32(const std::string& str) {
        data = FromUTF8(str.c_str());
        sizeIntern = data.size();
    }

    String32::String32(const char* str) {
        data = FromUTF8(str);
        sizeIntern = data.size();
    }

    vector<uint32_t>::iterator String32::begin() {
        return data.begin();
    }

    vector<uint32_t>::iterator String32::end() {
        return data.end();
    }

    vector<uint32_t>::const_iterator String32::begin() const {
        return data.begin();
    }

    vector<uint32_t>::const_iterator String32::end() const {
        return data.end();
    }


    bool String32::isEmpty() const {
        return sizeIntern == 0;
    }

    size_t String32::size() const {
        return sizeIntern;
    }

    uint32_t& String32::at(const size_t& index) {
        return data.at(index);
    }

    string String32::toString() const {
        return ToUTF8(data);
    }

    String32& String32::append(const String32& other) {
        size_t max = sizeIntern + other.sizeIntern;
        data.resize(max);

        for (size_t i = 0; i < other.sizeIntern; i++) {
            data.at(sizeIntern + i) = other.data.at(i);
        }

        sizeIntern = max;
        return *this;
    }

    String32& String32::append(char32_t* text, const std::size_t& max) {
        for (size_t i = 0; i < max; i++) {
            if (text[i] == '\0') break; //'\0' is always the last char of a C-string

            data.push_back((uint32_t) text[i]);
            sizeIntern++;
        }

        return *this;
    }

    String32& String32::append(const std::vector<uint32_t>& newData) {
        size_t max = sizeIntern + newData.size();
        data.resize(max);

        for (size_t i = 0; i < newData.size(); i++) {
            data.at(sizeIntern + i) = newData.at(i);
        }

        sizeIntern = max;
        return *this;
    }

    String32& String32::append(const char32_t& c) {
        data.push_back((uint32_t) c);
        sizeIntern++;

        return *this;
    }

    String32& String32::append(const uint32_t& i) {
        data.push_back(i);
        sizeIntern++;

        return *this;
    }

    String32& String32::append(const string& str) {
        vector<uint32_t> newData = FromUTF8(str.c_str());
        
        size_t s = sizeIntern;
        data.resize(s + newData.size());

        for (size_t i = 0; i < newData.size(); i++) data.at(s + i) = newData.at(i);
        sizeIntern += newData.size();

        return *this;
    }

    String32 String32::substring(const size_t& start, const size_t& end) {
        String32 ret;
        for (size_t i = start; i < sizeIntern; i++) {
            if (i >= end) break;

            ret.append(data.at(i));
        }

        return ret;
    }

    String32& String32::operator += (const String32& other) {
        append(other);
        return *this;
    }

    String32& String32::operator += (char32_t* other) {
        append(other);
        return *this;
    }

    String32& String32::operator += (const std::vector<uint32_t>& other) {
        append(other);
        return *this;
    }

    String32& String32::operator += (const char32_t& other) {
        append(other);
        return *this;
    }

    String32& String32::operator += (const uint32_t& other) {
        append(other);
        return *this;
    }

    String32& String32::operator += (const string& other) {
        append(other);
        return *this;
    }

    String32 String32::operator + (const String32& other) const {
        size_t newSize = sizeIntern + other.sizeIntern;
        vector<uint32_t> newData(newSize);

        size_t index = 0;

        for (const uint32_t& i: data) newData.at(index) = i; index++; //Current string
        for (const uint32_t& i: other.data) newData.at(index) = i; index++; //New String

        return {newData, newSize};
    }

    String32 String32::operator + (char32_t* other) const {
        size_t newSize = sizeIntern;
        vector<uint32_t> newData(newSize);

        size_t index = 0;

        for (const uint32_t& i: data) newData.at(index) = i; index++; //Current string
        
        index = 0;
        while (other[index] != '\0') { //New String
            newData.push_back((uint32_t) other[index]);
            newSize++;
            index++;
        }

        return {newData, newSize};
    }

    String32 String32::operator + (const vector<uint32_t>& other) const {
        size_t newSize = sizeIntern + other.size();
        vector<uint32_t> newData(newSize);

        size_t index = 0;

        for (const uint32_t& i: data) newData.at(index) = i; index++; //Current string
        for (const uint32_t& i: other) newData.at(index) = i; index++; //New String

        return {newData, newSize};
    }

    String32 String32::operator + (const char32_t& c) const {
        size_t newSize = sizeIntern + 1;
        vector<uint32_t> newData(newSize);

        size_t index = 0;

        for (const uint32_t& i: data) newData.at(index) = i; index++; //Current string
        newData.at(index) = (uint32_t) c; //New String

        return {newData, newSize};
    }

    String32 String32::operator + (const uint32_t& i) const {
        size_t newSize = sizeIntern + 1;
        vector<uint32_t> newData(newSize);

        size_t index = 0;

        for (const uint32_t& i: data) newData.at(index) = i; index++; //Current string
        newData.at(index) = i; //New String

        return {newData, newSize};
    }

    String32 String32::operator + (const string& other) const {
        vector<uint32_t> otherUni = FromUTF8(other.c_str());
        
        size_t newSize = sizeIntern + otherUni.size();
        vector<uint32_t> newData(newSize);

        size_t index = 0;

        for (const uint32_t& i: data) newData.at(index) = i; index++; //Current string
        for (const uint32_t& i: otherUni) newData.at(index) = i; index++; //New String

        return {newData, newSize};
    }

    String32& String32::operator = (const String32& other) {
        data = other.data;
        sizeIntern = other.sizeIntern;

        return *this;
    }

    String32& String32::operator = (char32_t* other) {
        data.clear();
        sizeIntern = 0;

        while (other[sizeIntern] != '\0') data.push_back((uint32_t) other[sizeIntern]); sizeIntern++; //New String

        return *this;
    }

    String32& String32::operator = (const std::vector<uint32_t>& other) {
        data = other;
        sizeIntern = other.size();

        return *this;
    }

    String32& String32::operator = (const char32_t& c) {
        data.resize(1);
        sizeIntern = 1;

        data.at(0) = (uint32_t) c;

        return *this;
    }

    String32& String32::operator = (const uint32_t& i) {
        data.resize(1);
        sizeIntern = 1;

        data.at(0) = i;

        return *this;
    }

    String32& String32::operator = (const string& other) {
        data = FromUTF8(other.c_str());
        sizeIntern = data.size();

        return *this;
    }

    bool String32::operator == (const String32& other) {
        return data == other.data && sizeIntern == other.sizeIntern;
    }
    bool String32::operator == (char32_t* other) {
        vector<uint32_t> oData;
        size_t index = 0;
        while (other[index] != '\0') {
            oData.push_back((uint32_t) other[index]);
        }

        return data == oData && sizeIntern == oData.size();
    }
    bool String32::operator == (const std::vector<uint32_t>& other) {
        return data == other && sizeIntern == other.size();
    }
    bool String32::operator == (const std::string& str) {
        vector<uint32_t> oData = FromUTF8(str.c_str());

        return data == oData && sizeIntern == oData.size();
    }

    std::ostream& operator << (std::ostream& os, String32& other) {
        os << other.toString();
        return os;
    }

    std::istream& operator >> (std::istream& is, String32& other) {
        string s;
        is >> s;
        other = s;
        return is;
    }
}

namespace std {

    std::istream& getline(std::istream& in, PixelRenderer::String32& other) {
        string s;
        istream& ret = getline(in, s);
        other = s;

        return ret;
    }
}