#include "SocialNetwork.h"
#include <iostream>
#include <queue>
#include <unordered_set>
#include <algorithm>

SocialNetwork::~SocialNetwork() {
    for (auto& pair : users) {
        delete pair.second;
    }
}

void SocialNetwork::addUser(const std::string& userName, const std::string& profile) {
    if (users.find(userName) == users.end()) {
        users[userName] = new User(userName, profile);
        std::cout << "Usuario " << userName << " agregado exitosamente." << std::endl;
    }
    else {
        std::cout << "Usuario " << userName << "ya existe." << std::endl;
    }
}

void SocialNetwork::deleteUser(const std::string& userName) {
    auto it = users.find(userName);
    if (it != users.end()) {
        delete it->second;
        users.erase(it);
        std::cout << "Usuario " << userName << " borrado exitosamente." << std::endl;
    }
    else {
        std::cout << "Usuario " << userName << " no encontrado." << std::endl;
    }
}

void SocialNetwork::establishRelation(const std::string& userName1, const std::string& userName2, const std::string& type) {
    if (users.find(userName1) != users.end() && users.find(userName2) != users.end()) {
        Relation::Type connectionType = (type == "amigo") ? Relation::amigo : Relation::seguidor;
        Relation::createConnection(users[userName1], users[userName2], connectionType);
        std::cout << "Relacion establecida entre  " << userName1 << " y " << userName2 << "." << std::endl;
    }
    else {
        std::cout << "Uno o ambos usuarios no encontrados." << std::endl;
    }
}

void SocialNetwork::removeRelation(const std::string& userName1, const std::string& userName2, const std::string& type) {
    if (users.find(userName1) != users.end() && users.find(userName2) != users.end()) {
        Relation::Type connectionType = (type == "amigo") ? Relation::amigo : Relation::seguidor;
        Relation::removeConnection(users[userName1], users[userName2], connectionType);
        std::cout << "Relacion borrada entre  " << userName1 << " y " << userName2 << "." << std::endl;
    }
    else {
        std::cout << "Uno o ambos usuarios no encontrados." << std::endl;
    }
}

std::vector<User*> SocialNetwork::findCommonFriends(const std::string& userName1, const std::string& userName2) {
    std::vector<User*> commonFriends;
    if (users.find(userName1) != users.end() && users.find(userName2) != users.end()) {
        auto friends1 = users[userName1]->getFriends();
        auto friends2 = users[userName2]->getFriends();
        std::sort(friends1.begin(), friends1.end());
        std::sort(friends2.begin(), friends2.end());
        std::set_intersection(friends1.begin(), friends1.end(), friends2.begin(), friends2.end(), std::back_inserter(commonFriends));
    }
    return commonFriends;
}
void SocialNetwork::showUserRelations(const std::string& userName) const {
    auto it = users.find(userName);
    if (it == users.end()) {
        std::cout << "Usuario no encontrado." << std::endl;
        return;
    }

    User* user = it->second;

    std::cout << "User: " << user->getUsername() << std::endl;
    std::cout << "Informacion de Perfil: " << user->getProfile() << std::endl;

    std::cout << "Amigos: ";
    for (const auto& friendUser : user->getFriends()) {
        std::cout << friendUser->getUsername() << " ";
    }
    std::cout << std::endl;

    std::cout << "Seguidores: ";
    for (const auto& follower : user->getFollowers()) {
        std::cout << follower->getUsername() << " ";
    }
    std::cout << std::endl;

    std::cout << "Seguidos: ";
    for (const auto& followedUser : user->getFollowed()) {
        std::cout << followedUser->getUsername() << " ";
    }
    std::cout << std::endl;
}
void SocialNetwork::calculateShortestPath(const std::string& startUser, const std::string& endUser) {
    std::unordered_map<User*, User*> parentMap;
    std::unordered_map<User*, bool> visited;
    std::queue<User*> q;
    std::vector<User*> path;

    if (users.find(startUser) == users.end() || users.find(endUser) == users.end()) {
        std::cout << "Uno o ambos usuarios no existen." << std::endl;
        return;
    }

    User* start = users[startUser];
    User* end = users[endUser];

    q.push(start);
    visited[start] = true;
    parentMap[start] = nullptr;

    while (!q.empty()) {
        User* current = q.front();
        q.pop();

        if (current == end) {
            User* trace = end;
            while (trace != nullptr) {
                path.push_back(trace);
                trace = parentMap[trace];
            }
            std::reverse(path.begin(), path.end());

            std::cout << "Camino mas corto entre " << startUser << " y " << endUser << ": ";
            for (User* user : path) {
                std::cout << user->getUsername() << " ";
            }
            std::cout << std::endl;
            return;
        }

        for (User* neighbor : current->getFriends()) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
                parentMap[neighbor] = current;
            }
        }
    }

    std::cout << "No se encontro una ruta." << std::endl;
}


void SocialNetwork::showUsers() const {
    for (const auto& pair : users) {
        std::cout << "Nombre de usuario: " << pair.second->getUsername() << ", Infromacion de perfil: " << pair.second->getProfile() << std::endl;
    }
}
double SocialNetwork::calculateDensity() const {
    int numUsers = users.size();
    int numEdges = 0;

    for (const auto& pair : users) {
        numEdges += pair.second->getFriends().size(); // count all friends
        numEdges += pair.second->getFollowers().size(); // count all followers
        numEdges += pair.second->getFollowed().size(); // count all followed
    }

    // Since each edge is counted twice, divide by 2
    numEdges /= 2;

    // Density formula
    return (numEdges * 2.0) / (numUsers * (numUsers - 1));
}

