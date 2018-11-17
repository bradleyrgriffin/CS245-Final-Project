#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

using namespace std;

class Category
{
public:
    Category();
    Category(const string& cName, const int& cId){
        this->categoryId = cId;
        this->categoryName = cName;
    }

    int getCategoryId(){return this->categoryId; }
    string getCategoryName(){return this->categoryName; }

private:
    int categoryId;
    string categoryName;

};

#endif // CATEGORY_H
