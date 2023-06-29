#include "CCone.h"


CCone::CCone(double baseRadius, double height, double destiny)
	:CSolidBody(destiny)
	, m_height(height)
	, m_baseRadius(baseRadius){}


double CCone::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetVolume() const
{
	return M_PI * pow(m_baseRadius, 2) * (m_height / 3);
}

std::string CCone::GetType() const
{
	return "�����";
}

CCone::~CCone()
{
}

void CCone::AppendProperties(std::ostringstream& strm) const
{
	strm << "\t������� ������ ������: " << GetBaseRadius() << std::endl
		 << "\t������ ������: " << GetHeight() << std::endl;
}
