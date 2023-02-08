#include "WindowManager.h"

lv_disp_draw_buf_t WindowManager::draw_buf_dsc;
lv_color_t WindowManager::buf[DISP_BUF_SIZE];
lv_disp_drv_t WindowManager::disp_drv;
lv_disp_draw_buf_t WindowManager::disp_buf;
lv_indev_drv_t WindowManager::indev_drv;
WindowManager *WindowManager::instance = NULL;

WindowManager::WindowManager()
{
	log = Logger::GetInstance();
}

WindowManager::~WindowManager()
{
	shutdown = true;
	runner->join();
}

WindowManager *WindowManager::GetInstance()
{
	if (instance == NULL)
		instance = new WindowManager();
	return instance;
}

void WindowManager::Init()
{
	lv_init();
	fbdev_init();
	
	lv_disp_draw_buf_init(&disp_buf, &buf, NULL, DISP_BUF_SIZE);
	lv_disp_drv_init(&disp_drv);
	disp_drv.draw_buf   = &disp_buf;
	disp_drv.flush_cb   = fbdev_flush;
	disp_drv.hor_res    = WIDTH;
	disp_drv.ver_res    = HEIGHT;
	lv_disp_drv_register(&disp_drv);
	
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;

	/*This function will be called periodically (by the library) to get the mouse position and state*/
	indev_drv.read_cb = evdev_read;
	lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv);
	
	runner = new std::thread([this]{tickThread(); });
	
	LoadWidgets();
	
	mainWindow = new MainWindow();
}

void WindowManager::tickThread()
{
	while (!shutdown)
	{
		lv_timer_handler();
		lv_tick_inc(5);
		usleep(5000);
		
	}
}

bool WindowManager::LoadFont(std::string fontName, uint8_t fontSize, std::string filename)
{
	std::pair<std::string, uint8_t> ftDesc(fontName, fontSize);
	if (loadedFonts.find(ftDesc) != loadedFonts.end())
		return true;
	std::stringstream path;
	path << "A:./fonts" << filename;
	lv_font_t* font = lv_tiny_ttf_create_file(path.str().c_str(), fontSize);
	if (font == NULL)
	{
		std::stringstream ss;
		ss << "Failed to load font: " << filename << ", size: " << fontSize;
		log->LogC(ss.str());
		return false;
	}
	loadedFonts[ftDesc]=font;
	return true;
}

lv_font_t* WindowManager::GetFont(std::string fontName, uint8_t fontSize)
{
	std::pair<std::string, uint8_t> ftDesc(fontName, fontSize);
	if (loadedFonts.find(ftDesc) == loadedFonts.end())
		return NULL;

	return loadedFonts[ftDesc];
}

void WindowManager::WidgetCallback(lv_event_t *event)
{
	int id=(int)event->user_data;

}

void WindowManager::LoadWidgets()
{
	std::filesystem::path cwd = std::filesystem::current_path();
	std::filesystem::path uiPath = cwd;
	uiPath /= "UI";
	
	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(uiPath))
	{
		if (entry.is_regular_file())
		{
			std::filesystem::path p = entry.path();
			if (p.extension().string() == ".so" && p.filename().string()!="UIWidget.so")
			{
				std::stringstream ss;
				ss << "Attempting to load: " << p.string();
				log->LogI(ss.str());
				
				try
				{
					auto dlWidget = new DLClass<UIWidget>(p.string());
					std::shared_ptr<UIWidget> widget = dlWidget->make_obj();
					sWidgets wdata;
					wdata.dataPoints = widget->GetSensorInputs();
					wdata.isMaximized = false;
					wdata.widget = widget;
					wdata.Name = widget->GetName();
					widgets.insert(std::pair<int, sWidgets>(widget->GetID(), wdata));					
				}
				catch (std::exception &)
				{
				}
			}
		}
	}
}