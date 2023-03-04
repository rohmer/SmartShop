#include "LogTable.h"

LogTable::LogTable(lv_obj_t *tabView, lv_obj_t *logTab)
	: tabView(tabView),
	logTab(logTab)
{
}

void LogTable::Refresh()
{
	// Dont update it if it isnt showing
	int v = lv_tabview_get_tab_act(tabView);
	if (lv_tabview_get_tab_act(tabView) != 2)
		return;
	if (tableObject == NULL)
	{
		tableObject = lv_table_create(logTab);
	}
	using namespace sqlite_orm;
	
	std::vector<LogMsg> msgs = DB::GetInstance()->GetStorage()->get_all<LogMsg>(order_by(&LogMsg::Timestamp).desc(), limit(14));
	lv_table_set_cell_value(tableObject, 0, 0, "Time");
	lv_table_set_col_width(tableObject, 0, 256);
	lv_table_set_col_width(tableObject, 1, 192);
	lv_table_set_col_width(tableObject, 2, 192);
	lv_table_set_col_width(tableObject, 3, WIDTH - 256-192-192-10);
	lv_table_set_cell_value(tableObject, 0, 1, "Severity");
	lv_table_set_cell_value(tableObject, 0, 2, "Host");
	lv_table_set_cell_value(tableObject, 0, 3, "Message");
	for (int i=0; i<msgs.size(); i++)
	{
		LogMsg msg=msgs[i];
		
		auto tm = *std::localtime(&msg.Timestamp);
		std::stringstream ts;
		ts << std::put_time(&tm, "%m/%d/%Y %H:%M:%S");
		lv_table_set_cell_value(tableObject, i+1, 0, ts.str().c_str());
		std::string sevString = "INFO";
		if (msg.Severity == 1)
			sevString = "WARNING";
		if (msg.Severity == 2)
			sevString = "CRITICAL";
		lv_table_set_cell_value(tableObject, i+1, 1, sevString.c_str());
		lv_table_set_cell_value(tableObject, i+1, 2, msg.Host.c_str());
		lv_table_set_cell_value(tableObject, i+1, 3, msg.Message.c_str());
	}
}