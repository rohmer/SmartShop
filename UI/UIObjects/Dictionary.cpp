#include "Dictionary.h"

std::string Dictionary::currentDict = "";
std::string Dictionary::loadedDict = "";

Dictionary *Dictionary::instance = NULL;