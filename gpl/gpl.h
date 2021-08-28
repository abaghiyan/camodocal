#ifndef GPL_H
#define GPL_H

#include <algorithm>
#include <cmath>
#include <opencv2/core/core.hpp>
#ifndef M_E
#define	M_E	        2.71828182845904523536
#endif // !M_E
#ifndef M_LOG2E
#define	M_LOG2E	    1.44269504088896340736
#endif // !M_LOG2E
#ifndef M_LOG10E
#define	M_LOG10E	0.434294481903251827651
#endif // !M_LOG10E
#ifndef M_LN2
#define	M_LN2	    0.693147180559945309417
#endif // !M_LN2
#ifndef M_LN10
#define	M_LN10	    2.30258509299404568402
#endif // !M_LN10
#ifndef M_PI
#define	M_PI	    3.14159265358979323846
#endif // !M_PI
#ifndef M_PI_2
#define	M_PI_2	    1.57079632679489661923
#endif // !M_PI_2
#ifndef M_PI_4
#define	M_PI_4	    0.785398163397448309616
#endif // !M_PI_4
#ifndef M_1_PI
#define	M_1_PI	    0.318309886183790671538
#endif // !M_1_PI
#ifndef M_2_PI
#define	M_2_PI	    0.636619772367581343076
#endif // !M_2_PI
#ifndef M_2_SQRTPI
#define	M_2_SQRTPI	1.12837916709551257390
#endif // !M_2_SQRTPI
#ifndef M_SQRT2
#define	M_SQRT2	    1.41421356237309504880
#endif // !M_SQRT2
#ifndef M_SQRT1_2
#define	M_SQRT1_2	0.707106781186547524401
#endif // !M_SQRT1_2

namespace camodocal
{

template<class T>
const T clamp(const T& v, const T& a, const T& b)
{
	return std::min(b, std::max(a, v));
}

double hypot3(double x, double y, double z);
float hypot3f(float x, float y, float z);

template<class T>
const T normalizeTheta(const T& theta)
{
	T normTheta = theta;

	while (normTheta < - M_PI)
	{
		normTheta += 2.0 * M_PI;
	}
	while (normTheta > M_PI)
	{
		normTheta -= 2.0 * M_PI;
	}

	return normTheta;
}

double d2r(double deg);
float d2r(float deg);
double r2d(double rad);
float r2d(float rad);

double sinc(double theta);

template<class T>
const T square(const T& x)
{
	return x * x;
}

template<class T>
const T cube(const T& x)
{
	return x * x * x;
}

template<class T>
const T random(const T& a, const T& b)
{
	return static_cast<double>(rand()) / RAND_MAX * (b - a) + a;
}

template<class T>
const T randomNormal(const T& sigma)
{
    T x1, x2, w;

    do
    {
        x1 = 2.0 * random(0.0, 1.0) - 1.0;
        x2 = 2.0 * random(0.0, 1.0) - 1.0;
        w = x1 * x1 + x2 * x2;
    }
    while (w >= 1.0 || w == 0.0);

    w = sqrt((-2.0 * log(w)) / w);

    return x1 * w * sigma;
}

unsigned long long timeInMicroseconds(void);

double timeInSeconds(void);

void colorDepthImage(cv::Mat& imgDepth,
                     cv::Mat& imgColoredDepth,
                     float minRange, float maxRange);

bool colormap(const std::string& name, unsigned char idx,
              float& r, float& g, float& b);

std::vector<cv::Point2i> bresLine(int x0, int y0, int x1, int y1);
std::vector<cv::Point2i> bresCircle(int x0, int y0, int r);

void fitCircle(const std::vector<cv::Point2d>& points,
               double& centerX, double& centerY, double& radius);

std::vector<cv::Point2d> intersectCircles(double x1, double y1, double r1,
                                          double x2, double y2, double r2);

void LLtoUTM(double latitude, double longitude,
             double& utmNorthing, double& utmEasting,
             std::string& utmZone);
void UTMtoLL(double utmNorthing, double utmEasting,
             const std::string& utmZone,
             double& latitude, double& longitude);

long int timestampDiff(uint64_t t1, uint64_t t2);

}

#endif
