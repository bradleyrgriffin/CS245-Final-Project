#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>


class Category
{
public:
    Category();
    Category(const std::string& cName, const int& cId);

    std::string getCategoryName(){return this->categoryName; }
    int getCategoryId(){return this->categoryId; }

private:
    std::string categoryName;
    int categoryId;
};

#endif // CATEGORY_H
