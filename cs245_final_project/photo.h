#ifndef PHOTO_H
#define PHOTO_H

#include <string>

class Photo
{
public:
    Photo();
    Photo(const std::string& pPath, const int& pId);

    int getPhotoId(){ return this->photoId; }
    std::string getPhotoPath(){ return this->photoPath; }

private:
    int photoId;
    std::string photoPath;
};

#endif // PHOTO_H
