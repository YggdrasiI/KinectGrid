#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cv.h>

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
enum Changes {NO=0,MASK=1,MOTOR=2,
	CONFIG=4,MARGIN=8,AREAS=16,
	FRONT_MASK=32,TUIO_PROTOCOL=64,REPOKE=128,
	BACK_MASK=256,CLIPPING=512,
	ALL=1023};

/*
 * List of possible "states" of the main program.
 * I.e. hand detection mode, area detection mode, ...
 */
enum FunctionMode{ HAND_DETECTION, AREA_DETECTION, AREA_DETECTION_START,
	AREA_DETECTION_END,
	DEPTH_MASK_DETECTION, REPOKE_DETECTION, SAVE_MASKS, LOAD_MASKS };

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
