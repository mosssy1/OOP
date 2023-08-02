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
		 << "\tdensity = " << GetDensity() << std::endl
		 << "\tvolume = " << GetVolume() << std::endl
		 << "\tmassa = " << GetMass() << std::endl;
	AppendProperties(strm);
	return strm.str();
}