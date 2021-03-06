// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef BINARYVALUEOBJECT_H
#define BINARYVALUEOBJECT_H

#include "MAPISchema.h"

namespace graphql::mapi::object {

class BinaryValue
	: public service::Object
{
protected:
	explicit BinaryValue();

public:
	virtual service::FieldResult<response::IdType> getValue(service::FieldParams&& params) const = 0;

private:
	std::future<service::ResolverResult> resolveValue(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

} /* namespace graphql::mapi::object */

#endif // BINARYVALUEOBJECT_H
