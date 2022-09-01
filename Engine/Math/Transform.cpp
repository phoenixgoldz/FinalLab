#include "Transform.h"
#include <Json.h>

bool phoenix::Transform::Write(const rapidjson::Value& value) const
{


    return true;
}

bool phoenix::Transform::Read(const rapidjson::Value& value)
{
    READ_DATA(value, position);
    READ_DATA(value, scale);
    READ_DATA(value, rotation);

    return true;
}
