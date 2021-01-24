// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef PROPERTYOBJECT_H
#define PROPERTYOBJECT_H

#include "MAPISchema.h"

namespace graphql::mapi::object {

class Property
	: public service::Object
{
protected:
	explicit Property();

public:
	virtual service::FieldResult<std::shared_ptr<service::Object>> getId(service::FieldParams&& params) const = 0;
	virtual service::FieldResult<std::shared_ptr<service::Object>> getValue(service::FieldParams&& params) const = 0;

private:
	std::future<service::ResolverResult> resolveId(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveValue(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

} /* namespace graphql::mapi::object */

#endif // PROPERTYOBJECT_H
