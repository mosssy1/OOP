﻿#include <iostream>
#include "Car.h"
#include <map>

const std::map<int, std::pair<int, int>> gearSpeedRange = {
	{ -1, { -20, 0 } },
	{ 0, {0, 150} },
	{ 1, { 0, 30 } },
	{ 2, { 20, 50 } },
	{ 3, { 30, 60 } },
	{ 4, { 40, 90 } },
	{ 5, { 50, 150 } }
};

bool Car::TurnOnEngine()
{
	m_isEngineOn = true;

	return true;
}

bool Car::TurnOffEngine()
{
	if ((m_gear != 0) || (m_speed != 0))
	{
		m_lastErrorMessage = "Stop and shift to neutral to turn off the engine.\n";
		return false;
	}

	m_isEngineOn = false;

	return true;
}

bool CheckSpeedRange(int speed, int gear)
{
	if (speed < gearSpeedRange.at(gear).first || gearSpeedRange.at(gear).second < speed)
	{
		return false;
	}
	return true;
}

bool Car::SetGear(int gear)
{
	if (!IsTurnedOn())
	{
		m_lastErrorMessage = "Unable to set gear: Engine is turned off.";
		return false;
	}

	if (!gearSpeedRange.contains(gear))
	{
		m_lastErrorMessage = "Unable to set gear: invalid gear argument";
		return false;
	}

	switch (gear)
	{
	case -1:
		if (m_speed != 0)
		{
			if (m_gear != gear)
			{
				m_lastErrorMessage = "Unable to set reverse gear while moving.";
				return false;
			}

			return true;
		}
		break;

	case 0:
		break;

	case 1:
		[[fallthrough]];
	case 2:
		[[fallthrough]];
	case 3:
		[[fallthrough]];
	case 4:
		[[fallthrough]];
	case 5:
		if (!CheckSpeedRange(m_speed, gear)) 
		{
			m_lastErrorMessage = "Unable to set gear: unsuitable current speed";
			return false;
		}
		break;

	default:
		m_lastErrorMessage = "Internal error: invalid gear argument";
		return false;
	}

	m_gear = gear;
	return true;
}

bool Car::SetSpeed(int speed)
{
	if (speed < 0)
	{
		m_lastErrorMessage = "Unable to set speed: speed cannot be negative value.";
		return false;
	}

	if (!IsTurnedOn())
	{
		m_lastErrorMessage = "Unable to set speed: engine is turned off.";
		return false;
	}

	switch (m_gear)
	{
	case -1:
		if (-speed < gearSpeedRange.at(-1).first)
		{
			m_lastErrorMessage = "Unable to set speed: exceed reverse speed limit";
			return false;
		}
		m_speed = -speed;
		return true;

	case 0:
		if (speed > abs(m_speed))
		{
			m_lastErrorMessage = "Unable to set speed: impossible to accelerate at neutral gear";
			return false;
		}
		m_speed = (m_speed < 0) ? -speed : speed;
		return true;

	case 1:
		[[fallthrough]];
	case 2:
		[[fallthrough]];
	case 3:
		[[fallthrough]];
	case 4:
		[[fallthrough]];
	case 5:
		if (!CheckSpeedRange(speed, m_gear))
		{
			m_lastErrorMessage = "Unable to set speed: speed does not suite currently selected gear.";
			return false;
		}
		m_speed = speed;
		return true;

	default:
		m_lastErrorMessage = "Internal error: invalid gear value.";
		return false;
	}
}

bool Car::IsTurnedOn() const
{
	return m_isEngineOn;
}

Car::Direction Car::GetDirection() 
{
	if (m_speed > 0)
	{
		return Direction::FORWARD;
	}
	else
	{
		if (m_speed == 0)
		{
			return Direction::IMMOBILE;
		}
		else
		{
			return Direction::BACKWARD;
		}
	}
}

int Car::GetSpeed() const
{
	return abs(m_speed);
}

int Car::GetGear() const
{
	return m_gear;
}

std::string Car::GetLastErrorMessage() const
{
	return m_lastErrorMessage;
}
