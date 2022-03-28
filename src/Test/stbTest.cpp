#include <iostream>
#include <random>
#include <chrono>

//#include "portable-file-dialogs.h"
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;
using namespace chrono;

using rgb = unsigned char;

int main(int anzahl, char* args[]) {
    cout << "Hello World" << endl;

    cout << "Testing stb-image" << endl;
    cout << string(50, '-') << endl;

    const int width = 1000, height = 1000, channels = 3, lineCount = 5;
    const int size = width * height * channels;
    rgb pixels[size];
    mt19937 gen;
    string normal = "random.png", dark = "randomDark.png";
    gen.seed(system_clock::now().time_since_epoch().count());

    cout << "Generating random color values" << endl;
    for (int i = 0; i < size; i++) {
        if (i < width * channels * lineCount) pixels[i] = (rgb) 0xFF;
        else pixels[i] = (rgb) gen() % 256;
    }

    cout << "Saving image";
    int result = stbi_write_png(normal.c_str(), width, height, channels, pixels, width * channels);
    if (result) {
        cout << " -- success" << endl;
    } else {
        cout << " -- error. Quitting" << endl;
        return result;
    }

    cout << "Load written image";
    int w, h, c;
    rgb* read = stbi_load(normal.c_str(), &w, &h, &c, channels);

    if (read == NULL || w != width || h != height || c != channels) {
        cout << " -- error. Quitting" << endl;
        return result;
    } else {
        cout << " -- success" << endl;
    }

    cout << "Test for white lines";
    bool testLines = true;
    for (int i = 0; i < width * channels * lineCount; i++) if (read[i] != 0xFF) testLines = false;

    if (testLines) cout << " -- success" << endl;
    else cout << " -- error" << endl;

    cout << "Dividing values by 2" << endl;
    for (int i = 0; i < size; i++) read[i] /= 2;

    cout << "Flipping darker image and saving it again";
    stbi_flip_vertically_on_write(true);
    result = stbi_write_png(dark.c_str(), width, height, channels, read, width * channels);

    if (result) cout << " -- success" << endl;
    else cout << " -- error" << endl;

    cout << "Deleting read data" << endl;
    stbi_image_free(read);

    cout << "Test finished" << endl;
    cout << string(50, '-') << endl;
}
