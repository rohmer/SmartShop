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
}

bool AdvKeyboard::LoadDictionary(std::string dictionary)
{
	if (std::filesystem::exists(dictionary))
	{
		trie = Dictionary::GetInstance(dictionary)->GetTrie();
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

void AdvKeyboard::suggestion_event_cb(lv_event_t *e)
{
	sSugButtonData* sugData = (sSugButtonData*)lv_event_get_user_data(e);
	std::stringstream ss;
	ss << lv_textarea_get_text(sugData->textBox);
	ss << sugData->suggestion;

	lv_textarea_set_text(sugData->textBox, ss.str().c_str());
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

std::vector<std::string> AdvKeyboard::GetNGrams(std::string text)
{
	int rightPointer = text.length() - 1;

	std::vector<std::string> grams = {"", "", ""};

	if (isspace(text[rightPointer]))
	{
		grams.erase(grams.begin());
		while (isspace(text[rightPointer]) && rightPointer >= 0)
			rightPointer--;
	}
	int leftPointer = rightPointer - 1;

	int wordPtr = grams.size() - 1;
	while (true)
	{
		if (leftPointer < 0)
		{
			grams[wordPtr] = text.substr(0, rightPointer+1);
			break;
		}
		if (charIsTerminator(text[leftPointer]))
		{
			std::string tmp = text.substr(leftPointer + 1, rightPointer - leftPointer);
			bool notSpace = true;
			for (int i = 0; i < tmp.length(); i++)
				if (isspace(tmp[i]))
					notSpace = false;
			if (notSpace)
				grams[wordPtr] = tmp;
			break;
		}
		if (isspace(text[leftPointer]))
		{
			grams[wordPtr] = text.substr(leftPointer + 1, rightPointer - leftPointer);
			wordPtr--;
			leftPointer--;

			if (wordPtr < 0)
				break;
			while (leftPointer >= 0 && isspace(text[leftPointer]))
			{
				leftPointer--;
				if (leftPointer < 0)
					break;
			}
			rightPointer = leftPointer;
		}
		else
		{
			leftPointer--;
		}
	}

	if (grams[1].length() == 0)
	{
		grams[0] = grams[2];
		grams[1] = "";
		grams[2] = "";
	}
	else if (grams[0].length() == 0)
	{
		grams[0] = grams[1];
		grams[1] = grams[2];
		grams[2] = "";
	}


	return grams;
}

std::vector<std::string> AdvKeyboard::wordSplit(std::string input)
{
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	std::vector<std::string> ret;
	while ((pos = input.find(delimiter)) != std::string::npos)
	{
		token = input.substr(0, pos);
		ret.push_back(token);
		input.erase(0, pos + delimiter.length());
	}
	ret.push_back(input);
	return ret;
}

std::multimap<float, std::string, std::greater<float>>
AdvKeyboard::GetSuggestions(std::string text, uint cursorPos)
{
	std::multimap<float, std::string, std::greater<float>> results;

	if (!suggestionsEnabled)
		return results;
	if (trie == NULL)
		return results;
	
	// For now we are going to not deal with suggestions if the cursor is in
	// the middle of a line of text
	if (cursorPos < text.length())
	{
		for (int i = cursorPos; i < text.length(); i++)
			if (isspace(static_cast<unsigned char>(text[i])))
				return results;
	}
	std::vector<std::string> grams = GetNGrams(text.substr(0, cursorPos));
	if (grams.size() == 0)
		return results;
	agent.clear();
	keySet.reset();
	std::stringstream query;
	for (int i = 0; i < grams.size(); i++)
	{
		if (i > 0)
			query << " ";
		query << grams[i];
	}
	std::string qstr = query.str();
	agent.set_query(query.str());
	bool nextWordPred = false;
	if (cursorPos > 0)
		if (isspace(text[cursorPos - 1]))
			nextWordPred = true;
	std::vector<std::string> sugs;
	while (trie->predictive_search(agent) && results.size() <=5)
	{
		marisa::Key key = agent.key();
		float weight = key.weight();
		std::string suggestion = key.ptr();
		std::vector<std::string> sGrams = wordSplit(suggestion);
		if (nextWordPred)
		{
			if (grams.size() < 3 && sGrams.size() > grams.size() + 1)
			{
				std::string ssug = sGrams[grams.size()];
				if (std::find(sugs.begin(), sugs.end(), ssug)==sugs.end())
					results.emplace(key.weight(), ssug);
			
			}
		}
		else
		{
			if (grams.size() <= sGrams.size())
			{
				std::string ssug = sGrams[grams.size() - 1];
				if (std::find(sugs.begin(), sugs.end(), ssug)==sugs.end())
					results.emplace(key.weight(), ssug);
			}
		}
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
		data.textBox = textArea;
		data.suggestion = it->second;
		if (text[text.length()] == ' ')
			cursorPos = text.length() + 1;
		else
		{
			while (cursorPos > 0 && !isspace(text[cursorPos]))
				cursorPos--;
		}
		data.cursorPos = cursorPos;
		lv_obj_add_event_cb(suggestions[i], suggestion_event_cb, LV_EVENT_CLICKED, &data);
		i++;
	}
}
