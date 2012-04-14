#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Resoluton of kinect images */
//#define KRES_X = 640;
//#define KRES_Y = 480;
static const int KRES_X = 640;
static const int KRES_Y = 480;

// tracker parameters
static const double TMINAREA   = 512;    // minimum area of blob to track
static const double TMAXRADIUS = 24;    // a blob is identified with a blob in the previous frame if it exists within this radius
//
//

inline double min(double a,double b){return a<b?a:b;};
inline double max(double a,double b){return a>b?a:b;};

#endif
