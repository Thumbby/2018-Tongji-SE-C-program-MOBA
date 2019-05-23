#include"TimeCounter.h"

bool TimeCounter::init()
{
	return true;
}

void TimeCounter::update(float dt)
{
	m_mftime += dt;
}

float TimeCounter::getfCurTime()
{
	return m_mftime;
}

void TimeCounter::start()
{
	m_mftime = 0;
	this->scheduleUpdate();
}