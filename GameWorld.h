#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class GameWorld // 游戏类，控制整个游戏过程
{
	friend class Display;
	friend class Sprite;
	friend class CollisionSystem;

	HWND		GameWindow;
	static const int MsPerFrame;
	double kFPS;

	struct {
		int LastTime, FrameCount, FPS;
	} FPS;

	int BufKey, CurKey;
	int Level;

	Display			*pScreen;
	Player			*pPlayer;
	BulletSystem	*pPlayerBulletSystem, *pEnermyBulletSystem;
	EnermySystem	*pEnermySystem;
	CollisionSystem *pCollisionSystem;

	void DrawSprite(Sprite *pSprite);
	void UpdateFPS();
	void ShowInfomation();
	double GetKFPS() { return kFPS; }
public:
	static const int Width, Height;
	static const double PI;
	int Time;
	GameWorld( HWND);
	~GameWorld();
	void Update();
	void KeyDown(WPARAM KeyCode);
	void KeyUp(WPARAM KeyCode);
	void EnermyFire(Enermy *pEnermy);
	void PlayerFire(Player *pPlayer);
	void ResetPlayer();
};

#endif