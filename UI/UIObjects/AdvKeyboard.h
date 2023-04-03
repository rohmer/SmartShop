#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <lvgl.h>

#include <marisa.h>

class AdvKeyboard
{
  public:
	enum eKeyboardAlignment
	{
		BELOW,
		LEFT,
		ABOVE,
		RIGHT
	};
	AdvKeyboard(lv_obj_t *parent,
				  lv_obj_t *textArea,
				  uint x, uint y,
				  std::string dictionary);
	AdvKeyboard(lv_obj_t *parent,
				lv_obj_t *textArea,
				uint x,
				uint y,
				marisa::Trie *dictionary);
	AdvKeyboard(lv_obj_t *parent,
				lv_obj_t *textArea,
				eKeyboardAlignment preferedAlignment,
				marisa::Trie *dictionary);
	AdvKeyboard(lv_obj_t *parent,
				lv_obj_t *textArea,
				eKeyboardAlignment preferedAlignment,
				std::string dictionary);

	~AdvKeyboard();
	marisa::Trie *LoadDictionary(std::string dictionary);

	marisa::Trie *GetDictionary() { return trie; }

	lv_obj_t *GetSuggestionBar() { return suggestionBar; }

  private:
	lv_obj_t *keyboard;
	lv_obj_t *suggestionBar;
	static lv_obj_t *suggestions[4];

	bool suggestionsEnabled = false;
	marisa::Trie *trie=NULL;

	static void keyboard_event_cb(lv_event_t *e);
	static void suggestion_event_cb(lv_event_t *e);
	static std::string reverseString(std::string s);
};