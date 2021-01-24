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

ItemUpdated::ItemUpdated()
	: service::Object({
		"ItemChange",
		"ItemUpdated"
	}, {
		{ R"gql(index)gql"sv, [this](service::ResolverParams&& params) { return resolveIndex(std::move(params)); } },
		{ R"gql(updated)gql"sv, [this](service::ResolverParams&& params) { return resolveUpdated(std::move(params)); } },
		{ R"gql(__typename)gql"sv, [this](service::ResolverParams&& params) { return resolve_typename(std::move(params)); } }
	})
{
}

std::future<service::ResolverResult> ItemUpdated::resolveIndex(service::ResolverParams&& params)
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = getIndex(service::FieldParams(std::move(params), std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<response::IntType>::convert(std::move(result), std::move(params));
}

std::future<service::ResolverResult> ItemUpdated::resolveUpdated(service::ResolverParams&& params)
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = getUpdated(service::FieldParams(std::move(params), std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<Item>::convert(std::move(result), std::move(params));
}

std::future<service::ResolverResult> ItemUpdated::resolve_typename(service::ResolverParams&& params)
{
	return service::ModifiedResult<response::StringType>::convert(response::StringType{ R"gql(ItemUpdated)gql" }, std::move(params));
}

} /* namespace object */

void AddItemUpdatedDetails(std::shared_ptr<schema::ObjectType> typeItemUpdated, const std::shared_ptr<schema::Schema>& schema)
{
	typeItemUpdated->AddFields({
		schema::Field::Make(R"gql(index)gql"sv, R"md(Index in the subscribed window)md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType("Int"))),
		schema::Field::Make(R"gql(updated)gql"sv, R"md(`Item` that was updated)md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType("Item")))
	});
}

} /* namespace graphql::mapi */
