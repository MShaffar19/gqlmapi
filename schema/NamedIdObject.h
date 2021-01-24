// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef NAMEDIDOBJECT_H
#define NAMEDIDOBJECT_H

#include "MAPISchema.h"

namespace graphql::mapi::object {

class NamedId
	: public service::Object
{
protected:
	explicit NamedId();

public:
	virtual service::FieldResult<response::Value> getPropset(service::FieldParams&& params) const = 0;
	virtual service::FieldResult<std::shared_ptr<service::Object>> getId(service::FieldParams&& params) const = 0;

private:
	std::future<service::ResolverResult> resolvePropset(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveId(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

} /* namespace graphql::mapi::object */

#endif // NAMEDIDOBJECT_H
