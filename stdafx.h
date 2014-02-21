// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: 在此处引用程序要求的附加头文件
#include <list>
#include <cmath>
#include <time.h>
#include <sstream>
#include <fstream>

using namespace std;

#include "pre_declaretion.h" // 类前向声明
#include "Bitmap.h"
#include "GameWorld.h"
#include "Sprite.h"
#include "Display.h"
#include "Bullet.h"
#include "BulletSystem.h"
#include "FighterPlane.h"
#include "Player.h"
#include "Enermy.h"
#include "EnermySystem.h"
#include "CollisionSystem.h"