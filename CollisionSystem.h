#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

class CollisionSystem
{
	Player		*pPlayer;
	EnermySystem	*pEnermySystem;
	BulletSystem	*pPlayerBulletSystem, *pEnermyBulletSystem;

	void CollisionSystem::CheckForCollision(Enermy *pFighterPlane, Bullet *pBullet);
	void CollisionSystem::CheckForCollision(Player *pFighterPlane, Bullet *pBullet);
	void CollisionSystem::CheckForCollision(Player *pPlayer, Enermy *pEnermy);
public:
	CollisionSystem(GameWorld *pgw);
	void Update();
};

#endif