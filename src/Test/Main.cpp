#include <iostream>
#include <random>
#include <chrono>

#include "portable-file-dialogs.h"
#include "stb_image.h"
#include "stb_image_write.h"

using namespace std;
using namespace chrono;

using rgb = unsigned char;

int main(int anzahl, char* args[]) {
    cout << "Hello World" << endl;

    cout << "Teste Portable File Dialogs" << endl;
    pfd::notify("PFD Test", "Dies ist eine Benachrichtigung", pfd::icon::warning);
    pfd::message("PFD Test", "Dies ist eine MessageBox", pfd::choice::abort_retry_ignore, pfd::icon::question);

    cout << "Teste stb-image" << endl;
    cout << string(50, '-') << endl;

    cout << "Starte Test" << endl;

    const int width = 1000, height = 1000, channels = 3, lineCount = 5;
    const int size = width * height * channels;
    rgb pixels[size];
    mt19937 gen;
    string normal = "random.png", dark = "randomDark.png";
    gen.seed(system_clock::now().time_since_epoch().count());

    cout << "Generiere Randomisierte Pixeldaten" << endl;
    for (int i = 0; i < size; i++) {
        if (i < width * channels * lineCount) pixels[i] = (rgb) 0xFF;
        else pixels[i] = (rgb) gen() % 256;
    }

    cout << "Speichere Bild";
    int result = stbi_write_png(normal.c_str(), width, height, channels, pixels, width * channels);
    if (result) {
        cout << " -- Erfolgreich" << endl;
    } else {
        cout << " -- Fehlgeschlagen. Breche weiteren Test ab" << endl;
        return result;
    }

    cout << "Lade gelesenes Bild wieder aus";
    int w, h, c;
    rgb* read = stbi_load(normal.c_str(), &w, &h, &c, channels);

    if (read == NULL || w != width || h != height || c != channels) {
        cout << " -- Fehlgeschlagen. Breche weiteren Test ab" << endl;
        return result;
    } else {
        cout << " -- Erfolgreich" << endl;
    }

    cout << "Teste nach weißen Reihen";
    bool testLines = true;
    for (int i = 0; i < width * channels * lineCount; i++) if (read[i] != 0xFF) testLines = false;

    if (testLines) cout << " -- Erfolgreich" << endl;
    else cout << " -- Fehlgeschlagen" << endl;

    cout << "Halbiere Werte" << endl;
    for (int i = 0; i < size; i++) read[i] /= 2;

    cout << "Flippe und schreibe dunkleres Bild";
    stbi_flip_vertically_on_write(true);
    result = stbi_write_png(dark.c_str(), width, height, channels, read, width * channels);

    if (result) cout << " -- Erfolgreich" << endl;
    else cout << " -- Fehlgeschlagen" << endl;

    cout << "Lösche gelesene Daten" << endl;
    stbi_image_free(read);

    cout << "Test erfolgreich abgeschlossen" << endl;
    cout << string(50, '-') << endl;

    cout << endl << "ENTER zum Beenden";
    cin.get();
}
