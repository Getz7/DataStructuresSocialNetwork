#ifndef RELATION_H
#define RELATION_H

#include "User.h"
#include <string>

class Relation {
private:
    User* user1;
    User* user2;
    std::string type;

public:
    enum Type {
        amigo,
        seguidor
    };
    Relation(User* user1, User* user2, const std::string& tipoConexion);

    User* getUser1() const;
    User* getUser2() const;
    std::string getType() const;

    static void createConnection(User* user1, User* user2, Type type);
    static void removeConnection(User* user1, User* user2, Type type);
};

#endif // CONEXION_H
