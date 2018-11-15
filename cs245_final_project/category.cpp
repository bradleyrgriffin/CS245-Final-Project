#include "category.h"
#include "databaseconnection.h"
#include <map>

Category::Category()
{

}

Category::Category(const std::string& cName, const int& cId){
    if(cId > 0){
        this->categoryId = cId;
    }

    if(cName != ""){
        this->categoryName = cName;
    }
}
