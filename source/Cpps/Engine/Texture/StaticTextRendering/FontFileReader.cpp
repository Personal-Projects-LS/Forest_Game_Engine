#include "Headers/Engine/Texture/StaticTextRendering/FontFileReader.h"

FontFileReader::FontFileReader(const char *filename) {
    std::ifstream file(filename); //automatically closes file in std::ifstream's constructor

    std::array<int, 8> numbersForChar{};

    std::string line;
    while(getline(file, line, '\n')) {
        int numbersForCharIndex = 0;
        std::string numberAsString;
        for(int i = 0; i < line.size() && numbersForCharIndex < numbersForChar.size(); ++i) {
            if(isIntegral(line[i])) {
                numberAsString += line[i];

                if(!isIntegral(line[i+1])) {
                    numbersForChar[numbersForCharIndex] = std::stoi(numberAsString);

                    numberAsString.clear();
                    ++numbersForCharIndex;
                }
            }
        }
        fontInfo.emplace<const char, const Character>(static_cast<char>(numbersForChar[0]), Character(numbersForChar));
    }
}

Character FontFileReader::getChar(char id) {
    return fontInfo[id];
}
