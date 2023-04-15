#pragma once

#include <cstring>
#include <filesystem>
#include <string>

#include <marisa.h>

class Dictionary
{
  public:
	static Dictionary *GetInstance(std::string DictionaryFile = "dict.trie")
	{
		if (instance == NULL)
			instance = new Dictionary();
		currentDict = DictionaryFile;
		return instance;
	}

	~Dictionary()
	{
		if (trie != NULL)
			delete (trie);
	}
	
	marisa::Trie *GetTrie()
	{
		if (trie == NULL)
		{
			trie = new marisa::Trie();
		}
		if (std::strcmp(loadedDict.c_str(), currentDict.c_str()) != 0)
		{
			if (std::filesystem::exists(currentDict))
			{
				trie->mmap(currentDict.c_str());
				loadedDict = currentDict;
			}
		}
		return trie;
	}

  private:
	static Dictionary *instance;
	;
	Dictionary()
	{
	}
	static std::string loadedDict, currentDict;
	marisa::Trie *trie = NULL;
};