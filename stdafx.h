// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>
// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: �ڴ˴����ó���Ҫ��ĸ���ͷ�ļ�
#include <list>
#include <cmath>
#include <time.h>
#include <sstream>
#include <fstream>

using namespace std;

#include "pre_declaretion.h" // ��ǰ������
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