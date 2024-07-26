#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
private:
    std::string userName;
    std::string profile;
    std::vector<User*> friends;
    std::vector<User*> followers;
    std::vector<User*> followed;

public:
    User(const std::string& userName, const std::string& profile);

    std::string getUsername() const;
    std::string getProfile() const;

    void addFriend(User* user);
    void deleteFriend(User* user);
    void followUser(User* user);
    void stopFollowing(User* user);
    void addFollower(User* user);
    void removeFollower(User* user);

    std::vector<User*> getFriends() const;
    std::vector<User*> getFollowers() const;
    std::vector<User*> getFollowed() const;
};

#endif // USER_H
