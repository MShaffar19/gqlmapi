// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "Types.h"
#include "Unicode.h"

namespace graphql::mapi {

StringValue::StringValue(PCWSTR value)
	: m_value{ convert::utf8::to_utf8(value) }
{
}

StringValue::StringValue(std::string&& value)
	: m_value{ std::move(value) }
{
}

service::FieldResult<response::StringType> StringValue::getValue(service::FieldParams&& params) const
{
	return { m_value };
}

} // namespace graphql::mapi