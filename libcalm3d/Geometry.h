#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "Common.h"
#include <math.h>
#include <functional>

NS_CALM_BEGIN

// for Point assignement operator and copy constructor
class Size;

class Point
{
public:
	float x;
	float y;

public:
	Point();
	Point(float x, float y);
	Point(const Point& other);
	explicit Point(const Size& size);

	Point& operator= (const Point& other);
	Point& operator= (const Size& size);
	Point operator+(const Point& right) const;
	Point& operator+=(const Point& right);
	Point operator-(const Point& right) const;
	Point& operator-=(const Point& right);
	Point operator-() const;

	bool operator==(const Point& right);
	bool operator!=(const Point& right);
	bool operator==(const Point& right) const;
	bool operator!=(const Point& right) const;

	Point operator*(float a) const;
	Point operator/(float a) const;

	void setPoint(float xx, float yy);
};

class Size
{
public:
	float width;
	float height;

public:
	Size();
	Size(float width, float height);
	Size(const Size& other);
	explicit Size(const Point& point);
	Size& operator= (const Size& other);
	Size& operator= (const Point& point);
	Size operator+(const Size& right) const;
	Size operator-(const Size& right) const;
	Size operator*(float a) const;
	Size operator/(float a) const;
	void setSize(float width, float height);
};

class Rect
{
public:
	Point origin;
	Size  size;

public:
	Rect();
	Rect(float x, float y, float width, float height);
	Rect(const Rect& other);
	Rect& operator= (const Rect& other);
	void setRect(float x, float y, float width, float height);
};


NS_CALM_END

#endif // _GEOMETRY_H_