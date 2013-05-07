#include <LTBL/Utils.h>

#include <sstream>
#include <QString>

namespace ltbl
{
	float GetFloatVal(std::string strConvert)
	{
        QString str;
        str.fromStdString(strConvert);
        return static_cast<float>(str.toFloat());
        //return static_cast<float>(atof(strConvert.c_str()));
	}
}
