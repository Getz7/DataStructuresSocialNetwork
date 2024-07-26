#include "Relation.h"

Relation::Relation(User* user1, User* user2, const std::string& type)
    : user1(user1), user2(user2), type(type) {}

User* Relation::getUser1() const {
    return user1;
}

User* Relation::getUser2() const {
    return user2;
}

std::string Relation::getType() const {
    return type;
}

void Relation::createConnection(User* user1, User* user2, Type type) {
    if (type == amigo) {
        user1->addFriend(user2);
        user2->addFriend(user1);
    }
    else if (type == seguidor) {
        user1->followUser(user2);
    }
}

void Relation::removeConnection(User* user1, User* user2, Type type) {
    if (type == amigo) {
        user1->deleteFriend(user2);
        user2->deleteFriend(user1);
    }
    else if (type == seguidor) {
        user1->stopFollowing(user2);
    }
}
