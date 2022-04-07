#pragma once

#include <string>

/**
 * A util class to load fonts and textures
 * With this, You can load from disk as well as from the memory
 * (In case of a conflict, the memory has higher priority)
 */ 
class LoadInfo {
    public:
        std::string path;
        unsigned char* data;
        unsigned int size;

        LoadInfo() : path(""), data(NULL), size(0) {}
        LoadInfo(const std::string& path) : path(path), data(NULL), size(0) {}
        LoadInfo(unsigned char* data, const unsigned int& size) : path(""), data(data), size(size) {}

        inline bool usePath() const {return !path.empty() && !data && !size;}
        inline bool useMemory() const {return data && size;}
        inline bool isValid() const {return (data && size) || !path.empty();}
        
        bool operator == (const LoadInfo& info) {
            return path == info.path && data == info.data && size == info.size;
        }
};