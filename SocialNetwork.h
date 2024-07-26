#ifndef SOCIALNETWORK_H
#define SOCIALNETWORK_H

#include <string>
#include <unordered_map>
#include <vector>
#include "User.h"
#include "Relation.h"

class SocialNetwork {
public:
    SocialNetwork() = default;
    ~SocialNetwork();
    void addUser(const std::string& username, const std::string& profile);
    void deleteUser(const std::string& username);
    void establishRelation(const std::string& userName1, const std::string& userName2, const std::string& type);
    void removeRelation(const std::string& userName1, const std::string& userName2, const std::string& type);
    std::vector<User*> findCommonFriends(const std::string& userName1, const std::string& userName2);

    void showUserRelations(const std::string& userName) const;

    void calculateShortestPath(const std::string& startUser, const std::string& endUser);
    void showUsers() const;

    double calculateDensity() const;

private:
    std::unordered_map<std::string, User*> users;
};

#endif
