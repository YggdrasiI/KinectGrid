#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cv.h>

#define VERBOSE 1
#ifdef VERBOSE
#define VPRINT(...) fprintf(stdout, __VA_ARGS__)
#else
#define VPRINT(...)
#endif

/* Resoluton of kinect images */
//#define KRES_X = 640;
//#define KRES_Y = 480;
static const int KRES_X = 640;
static const int KRES_Y = 480;

/* Number of Frames to generate depth mask. Should be at least 5 */
static const int NMASKFRAMES = 30;

// tracker parameters
static const double TMINAREA   = 512;    // minimum area of blob to track
static const double TMAXAREA   = 512*8;    // maximum area of blob to track
static const double TMAXRADIUS = 24;    // a blob is identified with a blob in the previous frame if it exists within this radius
static const int MAXHANDS = 20; //maximal number of detected hands for tuio messages. This value limit the pool of ids.
static const int MAXAREAS = 20; //maximal number of areas.
static const int AREACOLORS[10][3] = { 
	{255, 0, 0 },
  {0, 255, 0 },
	{0, 0, 255},
	{255, 255, 0},
	{255, 0, 255},
	{0, 255, 255},
	{255, 128, 128},
	{128, 255, 128},
	{128, 128, 255},
	{255, 255, 255}
};
//
//

/* store which changes need attention */
enum Changes {
	NO=0,
	MASK=1,
	MOTOR=2,
	CONFIG=4,
	MARGIN=8,
	AREAS=16,
	FRONT_MASK=32,
	TUIO_PROTOCOL=64,
	REPOKE=128,
	BACK_MASK=256,
	CLIPPING=512,
	PARSE_AGAIN=1024,
	WEB_INTERFACE=2048,
	ALL=4095
};

/*
 * List of possible "states" of the main program.
 * I.e. hand detection mode, area detection mode, ...
 */
enum FunctionMode{
	HAND_DETECTION=0,
	AREA_DETECTION,
	AREA_DETECTION_START,
	AREA_DETECTION_END,
	DEPTH_MASK_DETECTION,
	REPOKE_DETECTION,
	SAVE_MASKS,
	LOAD_MASKS,
	QUIT,
	RGB,
	NUM_FUNCTION_MODES  
};

// Selection of output image
enum View {
	VIEW_UNKNOWN=-1,
	VIEW_NONE=0,
	VIEW_DEPTH,
	VIEW_MASK,
	VIEW_FILTERED,
	VIEW_AREAS,
	VIEW_FRONTMASK,
	VIEW_RGB,
	NUM_VIEWS
};

// List of output devices
/* Update constans in json_settings_editor.js if you change this enum.*/
enum DisplayMode {
	DISPLAY_MODE_NONE=0,
	DISPLAY_MODE_CV, // use OpenCV highgui for drawing window
	DISPLAY_MODE_WEB, //For webinterface 
	DISPLAY_MODE_DIRECTFB, //for non-X11 env, not implemented
	NUM_DISPLAY_MODES
};

// List of webserver operations
/* Update constans in json_settings_editor.js if you change this enum.*/
enum HttpAction {
	HTTP_ACTION_UPDATE_CONFIG=0,
	HTTP_ACTION_LOAD_CONFIG=1,
	HTTP_ACTION_SAVE_CONFIG=2,
	HTTP_ACTION_SET_AREA_DETECTION=3,
	HTTP_ACTION_REPOKE=4,
	HTTP_ACTION_SELECT_VIEW=5,
	HTTP_ACTION_SAVE_MASKS=6,
	HTTP_ACTION_LOAD_MASKS=7,
	HTTP_ACTION_QUIT_PROGRAM=8,
	HTTP_ACTION_RESET_CONFIG=9,
	HTTP_ACTION_GET_PREVIEW_IMAGE=10,
	HTTP_ACTION_REGENERATE_MASKS=12,
	HTTP_ACTION_SEND_COMMAND=40, //unused
	NUM_HTTP_ACTIONS
};

class Area{
	public:
		cv::Rect rect;//minx,miny, width and height. Position is absolute and ignore roi.
		int id;
		cv::Scalar color;
		double area;//Flaecheninhalt
		double repoke_x, repoke_y;
		int depth;// avarage depth of area ∈[0,255]
};


inline double min(double a,double b){return a<b?a:b;};
inline double max(double a,double b){return a>b?a:b;};

#endif
