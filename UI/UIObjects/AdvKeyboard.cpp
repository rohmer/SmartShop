#include "AdvKeyboard.h"
lv_obj_t *AdvKeyboard::suggestions[4];

AdvKeyboard::AdvKeyboard(bool imethread)
{
	if(imethread)
		imeThread = new std::thread([this] { ime(); });
	suggestionsEnabled = true;
}

AdvKeyboard::AdvKeyboard(
	lv_obj_t *parent,
	lv_obj_t *textArea,
	uint x,
	uint y,
	std::string dictionary,
	bool IMEThread) :
	textArea(textArea)
{
	keyboard = lv_keyboard_create(parent);
	lv_obj_set_pos(keyboard, x, y);

	uint suggestionHeight = lv_font_get_line_height(LV_FONT_DEFAULT) + 4;
	suggestionBar = lv_obj_create(parent);
	lv_obj_set_size(suggestionBar, lv_obj_get_width(keyboard), suggestionHeight);
	lv_obj_align_to(suggestionBar, keyboard, LV_ALIGN_TOP_MID, 0, 0);

	lv_obj_set_layout(suggestionBar, LV_LAYOUT_FLEX);
	lv_obj_set_flex_flow(suggestionBar, LV_FLEX_FLOW_ROW);

	try
	{
		if (!LoadDictionary(dictionary))
			suggestionsEnabled = false;
		if (trie==NULL || !trie->empty())
			suggestionsEnabled = true;
	}
	catch (const std::exception &)
	{
	}
	if (suggestionsEnabled)
		lv_obj_add_event_cb(keyboard, keyboard_event_cb, LV_EVENT_VALUE_CHANGED, this);
	if (IMEThread)
	{
		imeThread = new std::thread([this] { ime(); });
	}
}

AdvKeyboard::AdvKeyboard(
	lv_obj_t *parent,
	lv_obj_t *textArea,
	uint x,
	uint y,
	marisa::Trie *dictionary,
	bool IMEThread) : trie(dictionary), textArea(textArea)
{
	keyboard = lv_keyboard_create(parent);
	lv_obj_set_pos(keyboard, x, y);

	uint suggestionHeight = lv_font_get_line_height(LV_FONT_DEFAULT) + 4;
	suggestionBar = lv_obj_create(parent);
	lv_obj_set_size(suggestionBar, lv_obj_get_width(keyboard), suggestionHeight);
	lv_obj_align_to(suggestionBar, keyboard, LV_ALIGN_TOP_MID, 0, 0);

	lv_obj_set_layout(suggestionBar, LV_LAYOUT_FLEX);
	lv_obj_set_flex_flow(suggestionBar, LV_FLEX_FLOW_ROW);

	if (trie==NULL || !trie->empty())
		suggestionsEnabled = true;
	if (suggestionsEnabled)
		lv_obj_add_event_cb(keyboard, keyboard_event_cb, LV_EVENT_VALUE_CHANGED, this);
	if (IMEThread)
	{
		imeThread = new std::thread([this] { ime(); });
	}
}

AdvKeyboard::AdvKeyboard(lv_obj_t *parent,
						 lv_obj_t *textArea,
						 eKeyboardAlignment preferedAlignment,
						 marisa::Trie *dictionary,
						 bool IMEThread) : trie(dictionary), textArea(textArea)
{
	keyboard = lv_keyboard_create(parent);

	if (preferedAlignment == eKeyboardAlignment::BELOW)
	{
		lv_area_t *coords;
		lv_obj_get_coords(textArea, coords);
		if ((lv_obj_get_height(keyboard) + coords->y2 + 5) > lv_scr_act()->coords.y2)
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_TOP_MID, 0, 5);
		}
		else
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
		}
	}

	if (preferedAlignment == eKeyboardAlignment::ABOVE)
	{
		lv_area_t *coords;
		lv_obj_get_coords(textArea, coords);
		if (coords->y1-5-lv_obj_get_height(keyboard) > 0)
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_TOP_MID, 0, 5);
		}
		else
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
		}
	}

	if (preferedAlignment == eKeyboardAlignment::LEFT)
	{
		lv_area_t *coords;
		lv_obj_get_coords(textArea, coords);
		if (coords->x1 - 5 - lv_obj_get_width(keyboard) > 0)
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_LEFT_MID, 0, 5);
		}
		else
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_RIGHT_MID, 0, 5);
		}
	}

	if (preferedAlignment == eKeyboardAlignment::RIGHT)
	{
		lv_area_t *coords;
		lv_obj_get_coords(textArea, coords);
		if (coords->x2 + 5 + lv_obj_get_width(keyboard) > lv_scr_act()->coords.x2)
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_LEFT_MID, 0, 5);
		}
		else
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_RIGHT_MID, 0, 5);
		}
	}
	uint suggestionHeight = lv_font_get_line_height(LV_FONT_DEFAULT) + 4;
	suggestionBar = lv_obj_create(parent);
	lv_obj_set_size(suggestionBar, lv_obj_get_width(keyboard), suggestionHeight);
	lv_obj_align_to(suggestionBar, keyboard, LV_ALIGN_TOP_MID, 0, 0);

	lv_obj_set_layout(suggestionBar, LV_LAYOUT_FLEX);
	lv_obj_set_flex_flow(suggestionBar, LV_FLEX_FLOW_ROW);

	if (trie==NULL || !trie->empty())
		suggestionsEnabled = true;
	if (suggestionsEnabled)
		lv_obj_add_event_cb(keyboard, keyboard_event_cb, LV_EVENT_VALUE_CHANGED, this);
	if (IMEThread)
	{
		imeThread = new std::thread([this] { ime(); });
	}
}

AdvKeyboard::AdvKeyboard(
	lv_obj_t *parent,
	lv_obj_t *textArea,
	eKeyboardAlignment preferedAlignment,
	std::string dictionary, 
	bool IMEThread) : textArea(textArea)
{
	keyboard = lv_keyboard_create(parent);

	if (preferedAlignment == eKeyboardAlignment::BELOW)
	{
		lv_area_t *coords;
		lv_obj_get_coords(textArea, coords);
		if ((lv_obj_get_height(keyboard) + coords->y2 + 5) > lv_scr_act()->coords.y2)
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_TOP_MID, 0, 5);
		}
		else
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
		}
	}

	if (preferedAlignment == eKeyboardAlignment::ABOVE)
	{
		lv_area_t *coords;
		lv_obj_get_coords(textArea, coords);
		if (coords->y1 - 5 - lv_obj_get_height(keyboard) > 0)
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_TOP_MID, 0, 5);
		}
		else
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
		}
	}

	if (preferedAlignment == eKeyboardAlignment::LEFT)
	{
		lv_area_t *coords;
		lv_obj_get_coords(textArea, coords);
		if (coords->x1 - 5 - lv_obj_get_width(keyboard) > 0)
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_LEFT_MID, 0, 5);
		}
		else
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_RIGHT_MID, 0, 5);
		}
	}

	if (preferedAlignment == eKeyboardAlignment::RIGHT)
	{
		lv_area_t *coords;
		lv_obj_get_coords(textArea, coords);
		if (coords->x2 + 5 + lv_obj_get_width(keyboard) > lv_scr_act()->coords.x2)
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_LEFT_MID, 0, 5);
		}
		else
		{
			lv_obj_align_to(keyboard, textArea, LV_ALIGN_OUT_RIGHT_MID, 0, 5);
		}
	}
	uint suggestionHeight = lv_font_get_line_height(LV_FONT_DEFAULT) + 4;
	suggestionBar = lv_obj_create(parent);
	lv_obj_set_size(suggestionBar, lv_obj_get_width(keyboard), suggestionHeight);
	lv_obj_align_to(suggestionBar, keyboard, LV_ALIGN_TOP_MID, 0, 0);

	lv_obj_set_layout(suggestionBar, LV_LAYOUT_FLEX);
	lv_obj_set_flex_flow(suggestionBar, LV_FLEX_FLOW_ROW);
	if (!LoadDictionary(dictionary))
		suggestionsEnabled = false;

	if (trie==NULL || !trie->empty())
		suggestionsEnabled = true;
	if (suggestionsEnabled)
		lv_obj_add_event_cb(keyboard, keyboard_event_cb, LV_EVENT_VALUE_CHANGED, this);

	if (IMEThread)
	{
		imeThread = new std::thread([this] { ime(); });
	}
}

AdvKeyboard::~AdvKeyboard()
{
	shutdown = true;
	if(imeThread!=NULL)
		imeThread->join();
	if (keyboard != NULL)
		lv_obj_del_async(keyboard);
	if (suggestionBar != NULL)
		lv_obj_del_async(suggestionBar);
	if (trie != NULL)
		delete (trie);
}

bool AdvKeyboard::LoadDictionary(std::string dictionary)
{
	if (std::filesystem::exists(dictionary))
	{
		trie = new marisa::Trie();
		trie->mmap(dictionary.c_str());
		terminators.push_back('.');
		terminators.push_back('?');
		terminators.push_back('!');
		terminators.push_back(';');
		if(trie!=NULL)
			return true;
	}
	return false;
}

void AdvKeyboard::keyboard_event_cb(lv_event_t *e)
{
	AdvKeyboard *ak = (AdvKeyboard *)lv_event_get_user_data(e);
	if (ak == NULL)
		return;

	if (ak->HasIME())
	{
		ak->IMEEvent();
		return;
	}
}

std::string AdvKeyboard::reverseString(std::string s)
{
	int n = s.length();
	if (n == 0)
		return s;
	// Swap character starting from two
	// corners
	for (int i = 0; i < n / 2; i++)
		std::swap(s[i], s[n - i - 1]);

	return s;
}

void AdvKeyboard::suggestion_event_cb(lv_event_t *)
{
}

void AdvKeyboard::ime()
{
	while (!shutdown)
	{
		if (imeEvent)
		{
			processSuggestions(
				std::string(lv_textarea_get_text(textArea)),
				lv_textarea_get_cursor_pos(textArea)
			);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

bool AdvKeyboard::charIsTerminator(char c)
{
	for (int i = 0; i < terminators.size(); i++)
		if (c == terminators[i])
			return true;
	return false;
}

std::multimap<float, std::string, std::greater<float>>
AdvKeyboard::GetSuggestions(std::string text, uint cursorPos)
{
	std::multimap<float, std::string, std::greater<float>> results;

	if (!suggestionsEnabled)
		return results;
	if (trie == NULL)
		return results;

	// First we have to figure out is the a single word, the end of a bigram, trigram
	// or is it a new word
	
	// First step, is previous char a terminator
	int pos = cursorPos;
	int ngram = 0;
	std::string searchString = "";
	while (pos >= 0 && !charIsTerminator(text[pos]))
		pos--;
	if (pos == -1)
	{
		searchString = text.substr(0, cursorPos);
	}
	else
	{
		searchString = text.substr(pos, (cursorPos - pos));
	}

	pos = searchString.length();
	std::stringstream grams[3];
	while (pos >= 0 && text[pos] == ' ')
	{
		pos--;
	}
	if (pos == -1)
		return results;  // all we have is whitespace

	int wordCtr = 2;
	while (pos >= 0 && wordCtr >= 0)
	{
		if (charIsTerminator(text[pos]))		// We dont do ngrams beyond a sentence
			break;
		if (text[pos] == ' ')
		{
			wordCtr--;
			while (pos >= 0 && text[pos] == ' ')
				pos--;
		}
		else
		{
			grams[wordCtr] << text[pos];
			pos--;
		}
	
	}
	std::vector<std::string> checkPhrase;
	;
	for (int i = 0; i < 3; i++)
		checkPhrase.push_back(reverseString(grams[i].str()));
	std::stringstream ssPhrase;
	for (int i = 0; i < 3; i++)
	{
		if (checkPhrase[i].length() > 0)
		{
			if (ssPhrase.str().length() > 0)
				ssPhrase << " " << checkPhrase[i];
			else
				ssPhrase << checkPhrase[i];
		}
	}
	agent.clear();
	std::string toCheck = ssPhrase.str();
	agent.set_query(toCheck.c_str(), toCheck.length());
	int resCtr = 0;
	keySet.reset();
	while (trie->predictive_search(agent) && resCtr<10)
	{
		results.emplace(agent.key().weight(), agent.key().str());
		resCtr++;
	}
	
	return results;
}

void AdvKeyboard::processSuggestions(std::string text, uint cursorPos)
{
	std::multimap<float, std::string, std::greater<float>> results;
	results = GetSuggestions(text, cursorPos);

	// At this point we have the sorted result list
	if (results.size() <= 4)
	{
		for (int i = results.size(); i <= 4; i++)
		{
			lv_obj_del_async(suggestions[i - 1]);
		}
	}
	if (results.size() == 0)
		return;
	uint sugCt = 4;
	if (results.size() < 4)
		sugCt = results.size();
	int i = 0;
	for(std::multimap<float,std::string, std::greater<float>>::iterator it=results.begin();
		i<4 && it!=results.end();
		++it)
	{
		lv_obj_t *label = NULL;
		if (suggestions[i] == NULL)
		{
			suggestions[i] = lv_btn_create(suggestionBar);
			lv_obj_t *sugLabel = lv_label_create(suggestions[i]);
			lv_obj_set_align(sugLabel, LV_ALIGN_CENTER);
			label = sugLabel;
		}
		else
		{
			// The suggestions will only have one child
			label=lv_obj_get_child(suggestions[i], 0);
		}
		lv_label_set_text(label, it->second.c_str());
		sSugButtonData data;
		data.suggestion = it->second;
		data.cursorPos = cursorPos;
		lv_obj_add_event_cb(suggestions[i], suggestion_event_cb, LV_EVENT_CLICKED, &data);
		i++;
	}
}