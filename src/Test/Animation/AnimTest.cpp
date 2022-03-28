#include <sys/stat.h>
#include <sstream>
#include <iomanip>

#include "AnimTest.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

//Internal functions
string getFilename(const int& image);
bool saveImage(const int& image);
bool createImageFolder();
void renderNothing(const int& image) {} //just for safety
bool initRenderer();
void cleanup();
bool createVideo();

int main() {
    cout << "Hello World" << endl;

    cout << "Starting animation test" << endl;

    if (!createImageFolder()) {
        cerr << "couldn't create image folder. Abort" << endl;
        return 1;
    }

    if (!initRenderer()) {
        cerr << "couldn't initialize renderer. Abort" << endl;
        return 2;
    }

    void (*animFunc)(const int&);
    int result = 0;
    for (int index = 0; index < 300; index++) {
        cout << "Rendering frame " << index << endl;
        renderer->setColor(Colors::Transparent);
        renderer->clear();

        //Choose animation method
        switch (index / 60) {
            case 0: 
                animFunc = renderShapes;
                break;
            case 1:
                animFunc = renderTextures;
                break;
            case 2:
                animFunc = renderBlending;
                break;
            case 3:
                animFunc = renderRepetition;
                break;
            case 4:
                animFunc = renderFonts;
                break;
            default:
                animFunc = renderNothing;
        }

        //Actually call it
        animFunc(index % 60);

        //Save rendered image
        if (!saveImage(index)) {
            cerr << "couldn't save image " << index << ". Abort" << endl;
            result = index + 3; //Indices from 3 to 302 mean image (n - 3) couldn't be saved
            break;
        }
    }

    if (!result && !createVideo()) result = 303; //Return value 303: Couldn't create video

    cleanup();

    return result;
}

string getFilename(const int& image) {
    ostringstream str;
    str << "images/Animation-";
    str << setw(3) << setfill('0') << image;
    str << ".png";

    return str.str();
}

bool saveImage(const int& image) {
    string filename = getFilename(image);

    //Save via stb_image
    return stbi_write_png(filename.c_str(), 1920, 1080, 4, renderer->getData(), 1920*4);
}

bool createImageFolder() {
    cout << "Checking for image folder" << endl;

    //Using old API, instead of C++17 std::filesystem
    struct stat info;

    //Checking if the image folder exists, otherwise create it
    if (stat("images", &info)) {
        cout << "Can't access image folder (it probably doesn't exist)" << endl;
        cout << "Trying to create it" << endl;

        int result;
        #if (defined __WIN32__ || _WIN64)
            //Windows doing everything else (again)
            result = mkdir("images");
        #else
            result = mkdir("images", 0077);
        #endif
        
        if (result == -1) return false;

        cout << "Image folder was created successfully" << endl;

    } else if (!(S_ISDIR(info.st_mode))) {
        cout << "\"images\" exists, but is a file (not a directory)" << endl;
        return false;
    } else {
        cout << "\"images\" exists and is a directory" << endl;
    }

    return true;
}

bool initRenderer() {
    //Init
    renderer = new Renderer(1920, 1080); //Init renderer with native size of Full HD
    textureMan = new TextureManager;
    fontMan = new FontManager;

    //Load fonts and images


    return true;
}

void cleanup() {
    cout << "Deleting managers and renderer" << endl;
    delete fontMan;
    delete textureMan;
    delete renderer;
}