#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>

namespace PixelRenderer {

    class String32 {
        private:
            std::vector<uint32_t> data;
            std::size_t sizeIntern;

            //Used internally
            String32(const std::vector<uint32_t>& data, std::size_t& size) : data(data), sizeIntern(size) {}
        public:
            static const std::size_t npos;
            static const uint32_t replacementCharacter;

            /**
             * Converts an UTF-8 String to a vector of Unicode code points
             * @param text The text
             * @param max The maximum number of charakters to copy (leave out to copy all)
             * @returns The filled vector
             */ 
            static std::vector<uint32_t> FromUTF8(const char* text, const std::size_t& max = npos);
            
            /**
             * Converts a vector of Unicode code points to an UTF-8 String
             * @param data The data
             * @returns The standard string
             */ 
            static std::string ToUTF8(const std::vector<uint32_t>& data);

            /**
             * Initialized from UTF-32 text
             * @param text The text, buildable via U"...";
             * @param max The maximum number of charakters to copy (leave out to copy all)
             */ 
            String32(const char32_t* text, const std::size_t& max = npos);

            /**
             * Initialize with 32-Bit data
             * @param data The data
             */ 
            String32(const std::vector<uint32_t>& data) : data(data), sizeIntern(data.size()) {}

            /**
             * Initialize with an standard UTF-8 string
             * @param str The string
             */ 
            String32(const std::string& str);

            /**
             * Initialize with an UTF-8 C-string
             * @param str The string
             */ 
            String32(const char* str);

            String32(): sizeIntern(0) {}

            //Iterators
            std::vector<uint32_t>::iterator begin();
            std::vector<uint32_t>::iterator end();
            std::vector<uint32_t>::const_iterator begin() const;
            std::vector<uint32_t>::const_iterator end() const;

            bool isEmpty() const;
            std::size_t size() const;
            uint32_t& at(const std::size_t& index);
            std::string toString() const;

            void append(const String32& other);
            void append(char32_t* text, const std::size_t& max = npos);
            void append(const std::vector<uint32_t>& newData);
            void append(const char32_t& c);
            void append(const uint32_t& i);
            void append(const std::string& str);

            String32& operator += (const String32& other);
            String32& operator += (char32_t* other);
            String32& operator += (const std::vector<uint32_t>& other);
            String32& operator += (const char32_t& other);
            String32& operator += (const uint32_t& other);
            String32& operator += (const std::string& other);

            String32 operator + (const String32& other) const;
            String32 operator + (char32_t* other) const;
            String32 operator + (const std::vector<uint32_t>& other) const;
            String32 operator + (const char32_t& c) const;
            String32 operator + (const uint32_t& i) const;
            String32 operator + (const std::string& str) const;

            String32& operator = (const String32& other);
            String32& operator = (char32_t* other);
            String32& operator = (const std::vector<uint32_t>& other);
            String32& operator = (const char32_t& c);
            String32& operator = (const uint32_t& i);
            String32& operator = (const std::string& str);

            bool operator == (const String32& other);
            bool operator == (char32_t* other);
            bool operator == (const std::vector<uint32_t>& other);
            bool operator == (const std::string& str);

            friend std::ostream& operator << (std::ostream& os, String32& other);
            friend std::istream& operator >> (std::istream& is, String32& other);
    };
}

namespace std {
    //overload getline for comfort purposes
    std::istream& getline(std::istream& in, PixelRenderer::String32& other);
}