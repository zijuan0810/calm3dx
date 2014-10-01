#include "Geometry.h"
#include <algorithm>
#include <cassert>

// implementation of Point
NS_CALM_BEGIN

Point::Point(void) : x(0), y(0)
{
}

Point::Point(float xx, float yy) : x(xx), y(yy)
{
}

Point::Point(const Point& other) : x(other.x), y(other.y)
{
}

Point::Point(const Size& size) : x(size.width), y(size.height)
{
}

Point& Point::operator= (const Point& other)
{
	setPoint(other.x, other.y);
	return *this;
}

Point& Point::operator= (const Size& size)
{
	setPoint(size.width, size.height);
	return *this;
}

Point Point::operator+(const Point& right) const
{
	return Point(this->x + right.x, this->y + right.y);
}

Point& Point::operator+=(const Point& right)
{
	this->x += right.x;
	this->y += right.y;
	return *this;
}

Point Point::operator-(const Point& right) const
{
	return Point(this->x - right.x, this->y - right.y);
}

Point& Point::operator-=(const Point& right)
{
	this->x -= right.x;
	this->y -= right.y;
	return *this;
}

Point Point::operator-() const
{
	return Point(-x, -y);
}

bool Point::operator==(const Point& right)
{
	return this->x == right.x && this->y == right.y;
}

bool Point::operator!=(const Point& right)
{
	return this->x != right.x || this->y != right.y;
}

bool Point::operator==(const Point& right) const
{
	return this->x == right.x && this->y == right.y;
}

bool Point::operator!=(const Point& right) const
{
	return this->x != right.x || this->y != right.y;
}

Point Point::operator*(float a) const
{
	return Point(this->x * a, this->y * a);
}

Point Point::operator/(float a) const
{
	assert(a != 0);
	return Point(this->x / a, this->y / a);
}

void Point::setPoint(float xx, float yy)
{
	this->x = xx;
	this->y = yy;
}


//
// implementation of Size
// 

Size::Size(void) : width(0), height(0)
{
}

Size::Size(float w, float h) : width(w), height(h)
{
}

Size::Size(const Size& other) : width(other.width), height(other.height)
{
}

Size::Size(const Point& point) : width(point.x), height(point.y)
{
}

Size& Size::operator= (const Size& other)
{
	setSize(other.width, other.height);
	return *this;
}

Size& Size::operator= (const Point& point)
{
	setSize(point.x, point.y);
	return *this;
}

Size Size::operator+(const Size& right) const
{
	return Size(this->width + right.width, this->height + right.height);
}

Size Size::operator-(const Size& right) const
{
	return Size(this->width - right.width, this->height - right.height);
}

Size Size::operator*(float a) const
{
	return Size(this->width * a, this->height * a);
}

Size Size::operator/(float a) const
{
	assert(a != 0);
	return Size(this->width / a, this->height / a);
}

void Size::setSize(float w, float h)
{
	this->width = w;
	this->height = h;
}

//
// implementation of Rect
//

Rect::Rect(void)
{
	setRect(0.0f, 0.0f, 0.0f, 0.0f);
}

Rect::Rect(float x, float y, float width, float height)
{
	setRect(x, y, width, height);
}

Rect::Rect(const Rect& other)
{
	setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
}

Rect& Rect::operator= (const Rect& other)
{
	setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
	return *this;
}

void Rect::setRect(float x, float y, float width, float height)
{
	// CGRect can support width<0 or height<0
	// CCASSERT(width >= 0.0f && height >= 0.0f, "width and height of Rect must not less than 0.");

	origin.x = x;
	origin.y = y;

	size.width = width;
	size.height = height;
}


NS_CALM_END