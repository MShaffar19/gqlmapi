// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "MAPIObjects.h"

#include "graphqlservice/introspection/Introspection.h"

#include <algorithm>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

using namespace std::literals;

namespace graphql::mapi {
namespace object {

IntValue::IntValue()
	: service::Object({
		"PropValue",
		"IntValue"
	}, {
		{ R"gql(value)gql"sv, [this](service::ResolverParams&& params) { return resolveValue(std::move(params)); } },
		{ R"gql(__typename)gql"sv, [this](service::ResolverParams&& params) { return resolve_typename(std::move(params)); } }
	})
{
}

std::future<service::ResolverResult> IntValue::resolveValue(service::ResolverParams&& params)
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = getValue(service::FieldParams(std::move(params), std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<response::IntType>::convert(std::move(result), std::move(params));
}

std::future<service::ResolverResult> IntValue::resolve_typename(service::ResolverParams&& params)
{
	return service::ModifiedResult<response::StringType>::convert(response::StringType{ R"gql(IntValue)gql" }, std::move(params));
}

} /* namespace object */

void AddIntValueDetails(std::shared_ptr<schema::ObjectType> typeIntValue, const std::shared_ptr<schema::Schema>& schema)
{
	typeIntValue->AddFields({
		schema::Field::Make(R"gql(value)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType("Int")))
	});
}

} /* namespace graphql::mapi */
