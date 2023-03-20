#include "MainWindow.h"

lv_obj_t *MainWindow::timeString;
int MainWindow::wifiUpdateTimer = 0;
int MainWindow::logUpdateTimer = 0;
lv_obj_t *MainWindow::logTab;
lv_obj_t *MainWindow::wifiNetworkLabel, *MainWindow::wifiStrIcon;
LV_IMG_DECLARE(Wifi4);
LV_IMG_DECLARE(Wifi3);
LV_IMG_DECLARE(Wifi2);
LV_IMG_DECLARE(Wifi1);
LV_IMG_DECLARE(noWifi);
LogTable *MainWindow::logTable;

MainWindow::MainWindow(uint widgetWidth, uint widgetHeight)
{
	windowObj = lv_win_create(lv_scr_act(), 40);
	
	// The status bar is divided into 3rds
	// Left is the app title
	// Mid is the time
	// Right is the Wifi info
	
	appTitle = lv_label_create(lv_win_get_header(windowObj));
	lv_obj_set_pos(appTitle, 0, 0);
#ifdef APP_NAME
	lv_label_set_text(appTitle, APP_NAME)
#else
	lv_label_set_text(appTitle, "SmartShop Server");
#endif
	timeString = lv_label_create(lv_win_get_header(windowObj));
	
	wifiStrIcon=lv_img_create(lv_win_get_header(windowObj));
	wifiNetworkLabel = lv_label_create(lv_win_get_header(windowObj));
	wifiUpdateTimer = 61;
	updateTimer = new std::thread([this]{updateWinTask(); });
	
	tabView = lv_tabview_create(windowObj, LV_DIR_TOP, 50);
	eventTab = lv_tabview_add_tab(tabView, "Events");
	nodeTab = lv_tabview_add_tab(tabView, "Nodes");
	logTab = lv_tabview_add_tab(tabView, "Logs");
	logTable = new LogTable(tabView, logTab);
	uint width = lv_obj_get_width(lv_tabview_get_content(tabView));
	uint height = lv_obj_get_height(lv_tabview_get_content(tabView));
	//nodeWidgetManager = new NodeWidgetManager(nodeTab, width, height);
}

// TODO Make this a standard thread.  This is a mess of statics

void MainWindow::updateWinTask()
{
	while (!shutdown)
	{
		// Update the time string
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		std::stringstream ts;
		ts << std::put_time(&tm, "%m/%d/%Y %H:%M:%S");
		lv_label_set_text(timeString, ts.str().c_str());
		if (logUpdateTimer > 30)
		{
			logUpdateTimer = 0;
			
			logTable->Refresh();
			updateNodeWidgets();
		}
		if (wifiUpdateTimer > 60)
		{
			sSignalStrength ss = NetworkTools::GetSignalStrength();
			lv_label_set_text(wifiNetworkLabel, ss.network.c_str());
			if (ss.network.length() == 0)
			{
				lv_img_set_src(wifiStrIcon, &noWifi);	
			}
			else
			{
				switch (ss.signalStrength)
				{
				case 4:
					lv_img_set_src(wifiStrIcon, &Wifi4);
					break;
				case 3:
					lv_img_set_src(wifiStrIcon, &Wifi3);
					break;
				case 2:
					lv_img_set_src(wifiStrIcon, &Wifi2);
					break;
				default:
					lv_img_set_src(wifiStrIcon, &Wifi1);
					break;
				}
			}
			wifiUpdateTimer = 0;
		}
	
		wifiUpdateTimer++;
		logUpdateTimer++;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void MainWindow::updateNodeWidgets()
{
	std::vector<std::string> newNodes = nodeWidgetManager->CheckNew();
	for (std::vector<std::string>::iterator it = newNodes.begin();
		it != newNodes.end();
		++it)
	{
		nodeWidgetManager->CreateNodeWidget(*it);
	}
}