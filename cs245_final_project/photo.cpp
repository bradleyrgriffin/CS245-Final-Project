#include "photo.h"

Photo::Photo()
{

}


Photo:Photo(const std::string& pPath, const int& pId){
    if(pPath != ""){
        this->photoPath = pPath;
    }

    if(pId > 0){
        this->photoId = pId;
    }
}
