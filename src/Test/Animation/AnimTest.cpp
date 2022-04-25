#include <sys/stat.h>
#include <sstream>
#include <iomanip>

#include "AnimTest.hpp"
#include "MemoryDump.hpp"
#include "AnimPart.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

int main() {
    cout << "Hello World" << endl;

    AnimationTest test;
    return test.onExecute();
}

int AnimationTest::onExecute() {
    cout << "Starting animation test" << endl;

    if (!createImageFolder()) {
        cerr << "couldn't create image folder. Abort" << endl;
        return 1;
    }

    if (!initRenderer()) {
        cerr << "couldn't initialize renderer. Abort" << endl;
        return 2;
    }

    void (AnimationTest::*animFunc)(const int&);
    int result = 0, index = 0;
    Part* part;

    //Render parts
    for (int i = 0; i < parts.size(); i++) {
        if (result) break;

        cout << "Rendering Part " << (i + 1) << ": " << parts.at(i)->name << endl;
        part = parts.at(i);

        for (int image = 0; image < 60; image++) {
            cout << "Rendering frame " << index << endl;
            renderer->setColor(Colors::Blue);
            renderer->clear();

            part->renderPart(image);
            if (!saveImage(index)) {
                cerr << "couldn't save image " << index << ". Abort" << endl;
                result = 3;
                break;
            }
            index++;
        }
    }

    //Create videos
    if (!result && !createVideoParts()) result = 4; //Return value 304: couldn't create parts


    /*for (int index = 0; index < 300; index++) {
        cout << "Rendering frame " << index << endl;
        renderer->setColor(Colors::Blue);
        renderer->clear();

        //Choose animation method
        switch (index / 60) {
            case 0: 
                animFunc = &AnimationTest::renderShapes;
                break;
            case 1:
                animFunc = &AnimationTest::renderTextures;
                break;
            case 2:
                animFunc = &AnimationTest::renderBlending;
                break;
            case 3:
                animFunc = &AnimationTest::renderRepetition;
                break;
            case 4:
                animFunc = &AnimationTest::renderFonts;
                break;
            default:
                animFunc = &AnimationTest::renderNothing;
        }

        //Actually call it
        (this->*animFunc)(index % 60);

        //Save rendered image
        if (!saveImage(index)) {
            cerr << "couldn't save image " << index << ". Abort" << endl;
            result = 3;
            break;
        }
    }

    //if (!result && !createVideo()) result = 303; //Return value 303: Couldn't create video

    if (!result && !createVideoParts()) result = 4; //Return value 304: couldn't create parts*/

    cleanup();

    return result;
}

void AnimationTest::registerPart(Part* part) {
    parts.push_back(part);
}

string AnimationTest::getFilename(const int& image) {
    ostringstream str;
    str << "images/Animation-";
    str << setw(3) << setfill('0') << image;
    str << ".png";

    return str.str();
}

bool AnimationTest::saveImage(const int& image) {
    string filename = getFilename(image);

    //Save via stb_image
    return stbi_write_png(filename.c_str(), 1920, 1080, 4, renderer->getData(), 1920*4);
}

bool AnimationTest::createVideoParts() {
    cout << "Image rendering complete. Using ffmpeg to create videos" << endl << endl;

    bool result = true;
    int value;
    ostringstream str;
    string cmd;

    for (int index = 0; index < parts.size(); index++) {
        cout << "Creating part " << (index + 1) << endl;
        
        //prepare start argument
        str << "ffmpeg -y -r 30 -start_number ";
        str << (index * 60);
        str << " -i images/Animation-%03d.png -frames 60 \"";
        str << parts.at(index)->videoName << "\"";
        cmd = str.str();
        str.clear();
        str.str("");

        //run command
        value = system(cmd.c_str());
        if (value) result = false;
    }

    return result;
}

bool AnimationTest::createImageFolder() {
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

bool AnimationTest::initRenderer() {
    //Init
    renderer = new Renderer(1920, 1080); //Init renderer with native size of Full HD
    textureMan = new TextureManager;
    fontMan = new FontManager;
    if (!fontMan->isInitialized) return false;

    //Load fonts and images
    robotoFont = fontMan->getFont({"res/Roboto-Regular.ttf"});
    if (!robotoFont->isLoaded) { //Testing for up to 2 directories above the current directory
        delete robotoFont;
        robotoFont = fontMan->getFont({"../res/Roboto-Regular.ttf"});
        if (!robotoFont->isLoaded) {
            delete robotoFont;
            robotoFont = fontMan->getFont({"../../res/Roboto-Regular.ttf"});
            if (!robotoFont->isLoaded) return false;
        }
    }
    futureFont = fontMan->getFont({Kenney_Future_ttf, Kenney_Future_ttf_len});
    if (!futureFont->isLoaded) return false;

    fruit = textureMan->getTexture({"res/Fruits.jpg"});
    if (!fruit) { //Testing for up to 2 directories above the current directory
        fruit = textureMan->getTexture({"../res/Fruits.jpg"});
        if (!fruit) {
            fruit = textureMan->getTexture({"../../res/Fruits.jpg"});
            if (!fruit) return false;
        }
    }
    check = textureMan->getTexture({GreenCheck_png, GreenCheck_png_len});
    if (!check) return false;

    //create parts
    registerPart(new PartShapes(this));
    registerPart(new PartTexture(this));
    registerPart(new PartBlend(this));

    return true;
}

void AnimationTest::cleanup() {
    cout << "Deleting managers and renderer" << endl;
    delete fontMan;
    delete textureMan;
    delete renderer;
}