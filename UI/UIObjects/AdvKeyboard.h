#pragma once

#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <map>
#include <string>
#include <thread>
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
	
	// Only really used for testing
	AdvKeyboard(bool imethread);

	AdvKeyboard(lv_obj_t *parent,
				lv_obj_t *textArea,
				uint x, uint y,
				std::string dictionary,
				bool IMEThread = true);
	AdvKeyboard(lv_obj_t *parent,
				lv_obj_t *textArea,
				uint x,
				uint y,
				marisa::Trie *dictionary, 
				bool IMEThread=true);
	AdvKeyboard(lv_obj_t *parent,
				lv_obj_t *textArea,
				eKeyboardAlignment preferedAlignment,
				marisa::Trie *dictionary,
				bool IMEThread=true);
	AdvKeyboard(lv_obj_t *parent,
				lv_obj_t *textArea,
				eKeyboardAlignment preferedAlignment,
				std::string dictionary,
				bool IMEThread=true);

	~AdvKeyboard();
	bool LoadDictionary(std::string dictionary);

	marisa::Trie *GetDictionary() { return trie; }

	lv_obj_t *GetSuggestionBar() { return suggestionBar; }

	bool HasIME() { return imeThread != NULL; }
	void IMEEvent() { imeEvent = true; }

	std::multimap<float, std::string, std::greater<float>> GetSuggestions(std::string text, uint cursorPos);

  private:
	lv_obj_t *keyboard;
	lv_obj_t *suggestionBar;
	lv_obj_t *textArea;
	static lv_obj_t *suggestions[4];
	bool shutdown = false;
	
	std::thread *imeThread=NULL;

	void ime();
	void processSuggestions(std::string text, uint cursorPos);
	bool imeEvent = false;
	bool suggestionsEnabled = false;
	marisa::Trie *trie=NULL;

	static void keyboard_event_cb(lv_event_t *e);
	static void suggestion_event_cb(lv_event_t *e);
	static std::string reverseString(std::string s);

	struct sSugButtonData
	{
	  public:
		uint cursorPos;
		std::string suggestion;
	};
};