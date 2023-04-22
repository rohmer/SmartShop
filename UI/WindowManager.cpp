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
	pluginManager = PluginManager::GetInstance();
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
	initalizePlugins();

	lv_init();
	void * buf1 = lv_mem_alloc(SDL_HOR_RES * SDL_VER_RES * sizeof(lv_color_t));
	lv_disp_draw_buf_init(&disp_buf, buf1, NULL, SDL_HOR_RES * SDL_VER_RES);
	sdl_init();
	sdl_disp_drv_init(&disp_drv, SDL_HOR_RES, SDL_VER_RES);;
	disp_drv.draw_buf   = &disp_buf;
	disp_drv.flush_cb   = sdl_display_flush;
	disp_drv.hor_res    = SDL_HOR_RES;
	disp_drv.ver_res    = SDL_VER_RES;
	lv_disp_t *disp=lv_disp_drv_register(&disp_drv);
	
	lv_disp_drv_register(&disp_drv);
	evdev_init();
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;

	/*This function will be called periodically (by the library) to get the mouse position and state*/
	indev_drv.read_cb = sdl_mouse_read;;
	lv_indev_drv_register(&indev_drv);
	
	runner = new std::thread([this]{tickThread(); });
	
	// Define the widget size
	// We are going 5, 5 tall
	widgetWidth = WIDTH / 5-10;
	widgetHeight = HEIGHT / 5 - 10;
	mainWindow = new MainWindow(widgetWidth, widgetHeight);
	log->LogI("WindowManager Initalized");
}

void WindowManager::tickThread()
{
	while (!shutdown)
	{
		lv_timer_handler();
		lv_tick_inc(5);
		lv_task_handler();
		usleep(5000);
	}
}

bool WindowManager::LoadFont(std::string fontName, uint8_t fontSize, std::string filename)
{
	std::pair<std::string, uint8_t> ftDesc(fontName, fontSize);
	if (loadedFonts.find(ftDesc) != loadedFonts.end())
		return true;
	/*std::stringstream path;
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
	*/
	return true;
}

lv_font_t* WindowManager::GetFont(std::string fontName, uint8_t fontSize)
{
	std::pair<std::string, uint8_t> ftDesc(fontName, fontSize);
	if (loadedFonts.find(ftDesc) == loadedFonts.end())
		return NULL;

	return loadedFonts[ftDesc];
}

void WindowManager::initalizePlugins()
{
	pluginManager->LoadPlugins();
	for (std::map<std::string, DLClass<UIWidget> *>::iterator it = pluginManager->GetLoadedPlugins().begin();
		 it != pluginManager->GetLoadedPlugins().end();
		 ++it)
	{
		std::shared_ptr<UIWidget> nw = std::dynamic_pointer_cast<UIWidget>(pluginManager->WidgetFactory(it->first));

		std::vector<std::string> sensorInputs = nw->GetSensorInputs();
		for (std::vector<std::string>::iterator eit = sensorInputs.begin(); eit!=sensorInputs.end(); ++eit)
		{
			if (eventToPlugin.find(*eit)!=eventToPlugin.end())
			{
				eventToPlugin[*eit].push_back(it->second);
			}
			else
			{
				eventToPlugin[*eit] = std::vector<DLClass<UIWidget> *>();
				eventToPlugin[*eit].push_back(it->second);
			}
		}
	}
}

void WindowManager::getActiveEventTypes()
{
	// Get a time 7 days ago
	time_t searchTime = time(0) - (60 * 60 * 24 * 7);
	using namespace sqlite_orm;
	std::vector<DBEventData> events = DB::GetInstance("")->GetStorage()->get_all<DBEventData>(
		distinct(&DBEventData::SensorName),
		columns(&DBEventData::SensorName),
		where(c(&DBEventData::EventTime) > searchTime));

}