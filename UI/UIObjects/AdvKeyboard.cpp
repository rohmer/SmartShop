#include "AdvKeyboard.h"

AdvKeyboard::AdvKeyboard(
	lv_obj_t *parent,
	lv_obj_t *textArea,
	uint x,
	uint y,
	std::string dictionary)
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
		trie = LoadDictionary(dictionary);
		if (trie==NULL || !trie->empty())
			suggestionsEnabled = true;
	}
	catch (const std::exception &)
	{
	}
	if (suggestionsEnabled)
		lv_obj_add_event_cb(keyboard, keyboard_event_cb, LV_EVENT_VALUE_CHANGED, this);
}

AdvKeyboard::AdvKeyboard(
	lv_obj_t *parent,
	lv_obj_t *textArea,
	uint x,
	uint y,
	marisa::Trie *dictionary) : trie(dictionary)
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
}

AdvKeyboard::AdvKeyboard(lv_obj_t *parent,
						 lv_obj_t *textArea,
						 eKeyboardAlignment preferedAlignment,
						 marisa::Trie *dictionary) : trie(dictionary)
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
}

AdvKeyboard::AdvKeyboard(
	lv_obj_t *parent,
	lv_obj_t *textArea,
	eKeyboardAlignment preferedAlignment,
	std::string dictionary)
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
	trie = LoadDictionary(dictionary);
	
	if (trie==NULL || !trie->empty())
		suggestionsEnabled = true;
	if (suggestionsEnabled)
		lv_obj_add_event_cb(keyboard, keyboard_event_cb, LV_EVENT_VALUE_CHANGED, this);
}

AdvKeyboard::~AdvKeyboard()
{
	if (keyboard != NULL)
		lv_obj_del_async(keyboard);
	if (suggestionBar != NULL)
		lv_obj_del_async(suggestionBar);
	if (trie != NULL)
		delete (trie);
}

marisa::Trie *AdvKeyboard::LoadDictionary(std::string dictionary)
{
	if (std::filesystem::exists(dictionary))
	{
		marisa::Trie *trie = new marisa::Trie();
		trie->load(dictionary.c_str());
		return trie;
	}
	return NULL;
}

void AdvKeyboard::keyboard_event_cb(lv_event_t *e)
{
	AdvKeyboard *ak = (AdvKeyboard *)lv_event_get_user_data(e);
	if (ak == NULL)
		return;

	lv_obj_t *keyboard = lv_event_get_target(e);
	lv_obj_t *textArea = lv_keyboard_get_textarea(keyboard);
	marisa::Trie *trie = ak->GetDictionary();

	std::string text(lv_textarea_get_text(textArea));
	uint cursorPos = lv_textarea_get_cursor_pos(textArea);

	std::string grams[3] = {"", "", ""};
	int wordCt = 0;
	std::string currentWord="";
	while (wordCt < 3 && cursorPos > 0)
	{
		if (text[cursorPos] != ' ')
		{
			currentWord += text[cursorPos];
		}
		else
		{
			if (currentWord.length() > 0)
			{
				grams[2 - wordCt] = currentWord;
				currentWord = "";
				wordCt++;
			}
		}
		cursorPos--;
		if (text[cursorPos] == '.' || text[cursorPos] == '?' || text[cursorPos] == '!')
			wordCt = 3;
	}
	std::stringstream gramSS;
	if (grams[0].length() > 0)
	{
		gramSS << reverseString(grams[0]) << ' ';
	}
	if (grams[1].length() > 0)
	{
		gramSS << reverseString(grams[1]) << ' ';
	}
	if (grams[2].length() > 0)
	{
		gramSS << reverseString(grams[2]) << ' ';
	}
	marisa::Agent agent;
	marisa::Keyset keyset;
	std::string lookup = gramSS.str();
	try
	{
		agent.set_query(lookup.c_str(), lookup.length());
	}
	catch (const std::exception &)
	{
	}

	int i = 0;
	while (i < 4 && trie->predictive_search(agent))
	{
		keyset.push_back(agent.key());
		i++;
	}
	if (keyset.empty())
	{
		for (int i = 0; i < 4; i++)
			lv_obj_del_async(suggestions[i]);
	}
	else
	{
		size_t v = 4;
		const std::size_t end = std::min(v, keyset.size());
		for (int i = 0; i < end; ++i)
		{
			if (suggestions[i] == NULL)
			{
				suggestions[i] = lv_btn_create(ak->GetSuggestionBar());
				lv_obj_set_size(suggestions[i],
								lv_obj_get_width(ak->GetSuggestionBar()) / 5,
								lv_obj_get_height(ak->GetSuggestionBar()) - 2);
				lv_obj_set_layout(suggestions[i], LV_LAYOUT_FLEX);
				lv_obj_set_flex_flow(suggestions[i], LV_FLEX_FLOW_ROW);
				lv_obj_t *sugLabel = lv_label_create(suggestions[i]);
				lv_label_set_text(sugLabel,keyset[i].ptr());
				lv_obj_add_event_cb(suggestions[i], suggestion_event_cb, LV_EVENT_CLICKED, textArea);
			}
		}
		for (int i = end; i < end; i++)
			lv_obj_del_async(suggestions[i]);
	}
}

std::string AdvKeyboard::reverseString(std::string s)
{
	std::stringstream ss;
	for (int i = s.length(); i >= 0; i--)
		ss << s[i];
	return ss.str();
}