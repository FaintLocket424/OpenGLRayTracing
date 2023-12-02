//
// Created by mpmat on 02/12/2023.
//

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
private:
    unsigned int id;
public:
    Texture(const char* filePath);
    unsigned int GetId();
};

#endif //TEXTURE_H
