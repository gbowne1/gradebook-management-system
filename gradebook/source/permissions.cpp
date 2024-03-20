#include "../include/permissions.h"

#include <algorithm>
#include <unordered_set>

User::User(const std::string &userId)
		: userId(userId), ownedResourceIds() // Initialize ownedResourceIds
{
}

Scope User::getUserScope() const
{
	if (isAdmin())
	{
		return Scope::ANY; // Administrators have access to any resource
	}
	else if (isTeacher())
	{
		return Scope::OWNED_CLASSES; // Teachers have access to resources belonging to classes they own
	}
	else
	{
		return Scope::OWNED_RESOURCE; // Other users have access to resources they created
	}
}

bool User::hasPermission(Permission permission, Scope scope)
{
	// Create a PermissionScope object to search for
	PermissionScope searchPermissionScope = {permission, scope};

	// Check if the user has the permission with the correct scope
	if (permissionScopes.find(searchPermissionScope) == permissionScopes.end())
	{
		return false;
	}
	// TODO Add a check if the user has the permission with the correct scope
	return true;
}

void User::addOwnedResource(const std::string &resourceId)
{
	ownedResourceIds.insert(resourceId);
}

bool User::ownsResource(std::shared_ptr<Resource> resource)
{
	// Check ownership based on the owned resource IDs
	return ownedResourceIds.count(resource->getResourceId()) > 0;
}