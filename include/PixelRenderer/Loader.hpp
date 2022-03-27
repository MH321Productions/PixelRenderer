#pragma once

#include <string>

/**
 * Eine Util-Klasse zum Laden von Fonts und Texturen
 * So kann man entweder aus einer Datei oder aus dem Speicher laden
 * (Dabei hat der Speicher eine höhere Priorität als die Dateien)
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