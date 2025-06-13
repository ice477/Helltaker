//
// Created by 蘇柏瑄 on 202
#ifndef TEXTLOADER_H
#define TEXTLOADER_H
#include <vector>
#include <string>

class TextLoader {
public:

    bool LoadText(int level);
    const std::vector<std::string>& GetText() const;

private:
    std::vector<std::string> m_TextData;
};



#endif //TEXTLOADER_H
