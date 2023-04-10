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

std::multimap<float, std::string, std::greater<float>>
AdvKeyboard::GetSuggestions(std::string text, uint cursorPos)
{
	std::multimap<float, std::string, std::greater<float>> results;

	if (!suggestionsEnabled)
		return results;
	if (trie == NULL)
		return results;
	
	int pos = cursorPos;
	// Get the string up to where the cursor is
	text = text.substr(0, pos);

	if (text.length() == 0)
		return results;

	// Now we have what we are going to predict against, the next step
	// is to split into words
	// Note, for the time being this is puncuation naieve
	int wordCtr = 2;
	std::string words[3] = {"", "", ""};
	bool nextWordPrediction = text[pos] == ' ';
	while (pos >= 0 && !isalnum(text[pos]))
	{
		pos--;
	}

	while (pos >= 0 && wordCtr >= 0)
	{
		std::stringstream word;
		while (pos >= 0 && isalnum(text[pos]))
		{
			word << text[pos];
			pos--;
		}

		words[wordCtr] = reverseString(word.str());
		wordCtr--;
		word.str("");
	}

	wordCtr = 2;
	marisa::Agent agent;
	marisa::Keyset keyset;
	agent.set_query(words[2].c_str(), words[2].length());
	
	if (trie->lookup(agent))
	{
		results.emplace(std::pair<float, std::string>(0, words[2]));
	}
	while (words[wordCtr].length() > 0 && wordCtr>=0)
	{
		std::stringstream wstream;
		for (int i = wordCtr; i <= 2; i++)
		{
			wstream << words[i];
			if (i != 2)
				wstream << " ";
		}
		std::string word = wstream.str();
		agent.set_query(word.c_str(), word.length());
		int resultCt = 0;
		while (trie->predictive_search(agent) && resultCt < 10)
		{
			keyset.push_back(agent.key());
			resultCt++;
		}		
		wordCtr--;
	}
	const std::size_t end = std::min((size_t)5, keyset.size());
	for (std::size_t i = 0; i < end; ++i)
	{
		float weight = keyset[i].weight();
		std::string gram = keyset[i].ptr();
		results.emplace(keyset[i].weight(), gram.substr(0,keyset[i].length()));
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