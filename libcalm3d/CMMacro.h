#ifndef _CMMACRO_H_
#define _CMMACRO_H_

#define NS_CALM_BEGIN namespace calm3d {
#define NS_CALM_END }

#define NS_MATH_BEGIN namespace zmath {
#define NS_MATH_END }

#define CM_SAFE_DELETE(p) delete (p); (p) = nullptr

#endif // _CMMACRO_H_