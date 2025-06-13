// TextLoader.cpp
#include "TextLoader.h"
#include <fstream>
#include <sstream>

bool TextLoader::LoadText(int level) {
    std::string filePath = "../assets/text/level" + std::to_string(level) + ".txt";
    std::ifstream file(filePath);
    if(!file.is_open()) return false;

    m_TextData.clear();
    std::string line;
    int sentenceCount = 0;

    // 讀取第一行，取得句子數量
    if(std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> sentenceCount;
    } else {
        return false;
    }

    // 依序讀取每一句
    for(int i = 0; i < sentenceCount && std::getline(file, line); ++i) {
        m_TextData.push_back(line);
    }

    return m_TextData.size() == sentenceCount;
}

const std::vector<std::string>& TextLoader::GetText() const {
    return m_TextData;
}