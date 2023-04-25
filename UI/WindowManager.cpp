#include "WindowManager.h"

lv_disp_draw_buf_t WindowManager::draw_buf_dsc;
lv_color_t WindowManager::buf[DISP_BUF_SIZE];
lv_color_t WindowManager::buf2[DISP_BUF_SIZE];
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
	fbdev_init();
	
	lv_disp_draw_buf_init(&disp_buf, &buf, NULL, DISP_BUF_SIZE);
	lv_disp_drv_init(&disp_drv);
	disp_drv.draw_buf = &disp_buf;
	disp_drv.flush_cb = fbdev_flush;
	disp_drv.hor_res = WIDTH;
	disp_drv.ver_res = HEIGHT;
	lv_disp_drv_register(&disp_drv);

	evdev_init();
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;

	/*This function will be called periodically (by the library) to get the mouse position and state*/
	indev_drv.read_cb = evdev_read;
	lv_indev_drv_register(&indev_drv);
	// Define the widget size
	// We are going 5, 5 tall
	widgetWidth = WIDTH / 5 - 10;
	widgetHeight = HEIGHT / 5 - 10;
	mainWindow = new MainWindow(widgetWidth, widgetHeight);
	runner = new std::thread([this]{tickThread(); });
	
	getActiveEventTypes();
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
	std::map<std::string, DLClass<UIWidget> *> plugins = pluginManager->GetLoadedPlugins();
	for (std::map<std::string, DLClass<UIWidget> *>::iterator it = plugins.begin();
		 it != plugins.end();
		 ++it)
	{
		std::shared_ptr<UIWidget> nw = std::dynamic_pointer_cast<UIWidget>(pluginManager->WidgetFactory(it->first));

		std::vector<std::string> sensorInputs = nw->GetSensorInputs();
		uiPlugins.emplace(nw->GetName(), nw);
		for(int i=0; i<sensorInputs.size(); i++)
		{
			std::string sensorInput = sensorInputs[i];
			if (strcmp(sensorInput.c_str(), "SYSTEM") != 0)
			{
				if (eventToPlugin.find(sensorInput) != eventToPlugin.end())
				{
#ifdef DEBUG
					std::stringstream ss;
					ss << "Added plugin: " << it->first << " to event: " << sensorInput;
					Logger::GetInstance()->LogI(ss.str());
#endif
					eventToPlugin[sensorInput].push_back(nw);
				}
				else
				{
					eventToPlugin[sensorInput] = std::vector<std::shared_ptr<UIWidget>>();
#ifdef DEBUG
					std::stringstream ss;
					ss << "Added plugin: " << it->first << " to event: " << sensorInput;
					Logger::GetInstance()->LogI(ss.str());
#endif

					eventToPlugin[sensorInput].push_back(nw);
				}
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
		where(c(&DBEventData::EventTime) > searchTime));

	std::vector<std::string> createdPlugins;
	
	for (std::vector<DBEventData>::iterator it = events.begin();
		 it != events.end();
		 ++it)
	{
		if (eventToPlugin.find(it->SensorName) != eventToPlugin.end())
		{
			for (std::vector<std::shared_ptr<UIWidget>>::iterator pii = eventToPlugin[it->SensorName].begin();
				 pii != eventToPlugin[it->SensorName].end();
				 ++pii)
			{

				bool created = false;
				for (int i = 0; i < createdPlugins.size(); i++)
				{
					if (strcmp(pii->get()->GetName().c_str(), createdPlugins[i].c_str()) == 0)
					{
						created = true;
						break;
					}
				}
				if (!created)
				{
					createdPlugins.push_back(pii->get()->GetName().c_str());
#ifdef DEBUG
					std::stringstream ss;
					ss << "Registering UI Plugin: " << pii->get()->GetName().c_str()<< " with MainWindow";
					Logger::GetInstance()->LogI(ss.str());
#endif
					std::shared_ptr<UIWidget> widget = uiPlugins[it->SensorName];
					mainWindow->AddEventWidget(widget);
				}
			}
		}
	}
}