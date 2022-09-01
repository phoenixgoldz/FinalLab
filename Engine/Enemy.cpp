#include "Enemy.h"
#include "../Game/Player.h"
#include "Bullet.h"
#include "Engine.h"

void phoenix::Enemy::Initialize()
{
	m_fireTime = phoenix::randomf(2, 6);
	m_speed = phoenix::randomf(5, 20);
}

void phoenix::Enemy::Update()
{
	//decrease fire timer
	m_fireTime -= phoenix::g_time.deltaTime;
	if (m_fireTime <= 0)
	{
		phoenix::Transform transform = m_transform;
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(phoenix::Model{ "Bullet.txt" }, transform);
		//m_scene->Add(std::move(bullet));
	}

	//set rotation towards player
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		phoenix::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.GetAngle();
	}

	//calculate velocity of bullet
	phoenix::Vector2 direction{ 1,0 };
	direction = phoenix::Vector2::Rotate(direction, m_transform.rotation);
	phoenix::Vector2 const velocity = direction * m_speed * phoenix::g_time.deltaTime;

	//move bullet
	m_transform.position += velocity;

	//wrap 
	if (m_transform.position.x > g_renderer.GetWidth()) {m_transform.position.x = 0;}
	if (m_transform.position.x < 0) {m_transform.position.x =(float) g_renderer.GetWidth();}
	if (m_transform.position.y > g_renderer.GetHeight()) {m_transform.position.y = 0;}
	if (m_transform.position.y < 0) {m_transform.position.y =(float) g_renderer.GetHeight();}
}
