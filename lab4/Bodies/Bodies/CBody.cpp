#include "CBody.h"

CBody::CBody()
{
}

CBody::~CBody()
{
}


std::string CBody::ToString(std::ostringstream& strm) const
{
	strm << GetType() << ":" << std::endl
		 << std::setprecision(10) 
		 << "\t���������� = " << GetDensity() << std::endl
		 << "\t����� = " << GetVolume() << std::endl
		 << "\t����� = " << GetMass() << std::endl;
	AppendProperties(strm);
	return strm.str();
}