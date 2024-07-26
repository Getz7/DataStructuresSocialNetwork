#include "User.h"
#include <algorithm>

User::User(const std::string& userName, const std::string& profile)
    : userName(userName), profile(profile) {}

std::string User::getUsername() const {
    return userName;
}

std::string User::getProfile() const {
    return profile;
}

void User::addFriend(User* user) {
    if (std::find(friends.begin(), friends.end(), user) == friends.end()) {
        friends.push_back(user);
    }
}

void User::deleteFriend(User* user) {
    friends.erase(std::remove(friends.begin(), friends.end(), user), friends.end());
}

void User::followUser(User* user) {
    if (std::find(followed.begin(), followed.end(), user) == followed.end()) {
        followed.push_back(user);
        user->addFollower(this);
    }
}

void User::stopFollowing(User* user) {
    followed.erase(std::remove(followed.begin(), followed.end(), user), followed.end());
    user->removeFollower(this);
}

void User::addFollower(User* user) {
    if (std::find(followers.begin(), followers.end(), user) == followers.end()) {
        followers.push_back(user);
    }
}

void User::removeFollower(User* user) {
    followers.erase(std::remove(followers.begin(), followers.end(), user), followers.end());
}

std::vector<User*> User::getFriends() const {
    return friends;
}

std::vector<User*> User::getFollowers() const {
    return followers;
}

std::vector<User*> User::getFollowed() const {
    return followed;
}
