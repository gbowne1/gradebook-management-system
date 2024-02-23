// File:   permissions.h
// Author: Andre Wlodkovski
// Date:   26 Jan 2024
// Time:   18:13:00
// Brief:  Permission system for GradeBook user hierarchy

#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_set>

enum Permission
{
	// Users
	CREATE_STUDENT,
	READ_STUDENT,
	UPDATE_STUDENT,
	DELETE_STUDENT,

	CREATE_TEACHER,
	READ_TEACHER,
	UPDATE_TEACHER,
	DELETE_TEACHER,

	CREATE_ADMINISTRATOR,
	READ_ADMINISTRATOR,
	UPDATE_ADMINISTRATOR,
	DELETE_ADMINISTRATOR,

	// Assignments
	CREATE_ASSIGNMENT,
	READ_ASSIGNMENT,
	UPDATE_ASSIGNMENT,
	DELETE_ASSIGNMENT,

	// Tests
	CREATE_TEST,
	READ_TEST,
	UPDATE_TEST,
	DELETE_TEST,

	// Grades
	CREATE_GRADE,
	READ_GRADE,
	UPDATE_GRADE,
	DELETE_GRADE
};

enum Scope
{
	// Action can be executed over the user's own resources
	SELF,

	// Action can be executed over resources created by the user
	OWNED_RESOURCE,

	// Action can be executed over resources belonging to classes the user owns
	OWNED_CLASSES,

	// Action can be executed over any resource
	ANY
};

struct PermissionScope
{
    Permission permission;
    Scope scope;

    bool operator==(const PermissionScope& other) const {
        return permission == other.permission && scope == other.scope;
    }
};
// Each resource can handle how it is owned by an user
// Resources and users are referenced with shared_ptr in order to handle inheritance
class Resource
{
public:
	virtual ~Resource() = default;
	virtual bool isOwnedBy(const std::string &userId) const = 0;
	virtual std::string getResourceId() const = 0; // Add this method
};

// Define a hash function for PermissionScope
struct PermissionScopeHash
{
    std::size_t operator()(const PermissionScope &ps) const
    {
        return std::hash<int>()(static_cast<int>(ps.permission)) ^ std::hash<int>()(static_cast<int>(ps.scope));
    }
};

class User
{
private:

	bool isAdmin() const {
        // Add logic to check if the user is an administrator
        // For example, you might check if the user has an 'admin' role
        // Return true if the user is an administrator, false otherwise
		return false;
	}

    bool isTeacher() const {
        // Add logic to check if the user is a teacher
        // For example, you might check if the user has a 'teacher' role
        // Return true if the user is a teacher, false otherwise
		return false;
    }

	std::unordered_set<PermissionScope, PermissionScopeHash> permissionScopes; // Use custom hash function
	std::string userId;
	std::unordered_set<std::string> ownedResourceIds;

public:
	User(const std::string &userId);
	virtual ~User() = default;

	bool hasPermission(Permission permission, Scope scope);
	void addOwnedResource(const std::string &resourceId);
	bool ownsResource(std::shared_ptr<Resource> resource);
	Scope getUserScope() const;
};

#endif