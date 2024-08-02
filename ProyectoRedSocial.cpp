#include <iostream>
#include "SocialNetwork.h"

void showMenu() {
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "|1. Agregar Usuario                 |" << std::endl;
    std::cout << "|2. Borrar Usuario                  |" << std::endl;
    std::cout << "|3. Crear una conexion              |" << std::endl;
    std::cout << "|4. Borrar una conexion             |" << std::endl;
    std::cout << "|5. Buscar amigos en comun          |" << std::endl;
    std::cout << "|6. Calcular el camino mas corto    |" << std::endl;
    std::cout << "|7. Mostrar Usuarios                |" << std::endl;
    std::cout << "|8. Mostrar  relaciones de Usuarios |" << std::endl;
    std::cout << "|9. Salir                           |" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
}

void populateInitialData(SocialNetwork& socialNetwork) {
    socialNetwork.addUser("Alice", "Profile of Alice");
    socialNetwork.addUser("Bob", "Profile of Bob");
    socialNetwork.addUser("Charlie", "Profile of Charlie");
    socialNetwork.addUser("David", "Profile of David");

    socialNetwork.establishRelation("Alice", "Bob", "amigo");
    socialNetwork.establishRelation("Alice", "Charlie", "amigo");
    socialNetwork.establishRelation("Bob", "Charlie", "amigo");
    socialNetwork.establishRelation("Charlie", "David", "amigo");

    socialNetwork.establishRelation("Alice", "David", "seguir");
    socialNetwork.establishRelation("Bob", "David", "seguir");
    socialNetwork.establishRelation("Charlie", "Alice", "seguir");
}

int main() {
    SocialNetwork socialNetwork;
    populateInitialData(socialNetwork);
    int option;
    std::string name, profile, name1, name2, type;

    do {
        showMenu();
        std::cout << std::endl;
        std::cout << "Seleccione una opcion: " << std::endl;
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar cualquier carácter residual en el buffer de entrada

        switch (option) {
        case 1:
            std::cout << "Ingrese el nombre de usuario: ";
            std::getline(std::cin, name);
            std::cout << "Ingrese su informacion de perfil: ";
            std::getline(std::cin, profile);
            socialNetwork.addUser(name, profile);
            break;
        case 2:
            std::cout << "Ingrese el nombre de usuario a borrar: ";
            std::getline(std::cin, name);
            socialNetwork.deleteUser(name);
            break;
        case 3:
            std::cout << "Ingrese el nombre del primer usuario: ";
            std::getline(std::cin, name1);
            std::cout << "Ingrese el nombre del segundo usuario: ";
            std::getline(std::cin, name2);
            std::cout << "Ingrese el tipo de conexion(amigo/seguir): ";
            std::getline(std::cin, type);
            socialNetwork.establishRelation(name1, name2, type);
            break;
        case 4:
            std::cout << "Ingrese el nombre del primer usuario: ";
            std::getline(std::cin, name1);
            std::cout << "Ingrese el nombre del segundo usuario: ";
            std::getline(std::cin, name2);
            std::cout << "Ingrese el tipo de conexion(amigo/seguir): ";
            std::getline(std::cin, type);
            socialNetwork.removeRelation(name1, name2, type);
            break;
        case 5:
            std::cout << "Ingrese el nombre del primer usuario: ";
            std::getline(std::cin, name1);
            std::cout << "Ingrese el nombre del segundo usuario: ";
            std::getline(std::cin, name2);
            {
                auto commonFriends = socialNetwork.findCommonFriends(name1, name2);
                std::cout << "Amigos en comun: ";
                for (auto* friendUser : commonFriends) {
                    std::cout << friendUser->getUsername() << " ";
                }
                std::cout << std::endl;
            }
            break;
        case 6:
            std::cout << "Ingrese el nombre del primer usuario: ";
            std::getline(std::cin, name1);
            std::cout << "Ingrese el nombre del segundo usuario: ";
            std::getline(std::cin, name2);
            socialNetwork.calculateShortestPath(name1, name2);
            break;
        case 7:
            socialNetwork.showUsers();
            break;
        case 8:
            std::cout << "Ingrese el usuario: ";
            std::getline(std::cin, name);
            socialNetwork.showUserRelations(name);
            break;
        case 9:
            std::cout << "Saliendo..." << std::endl;
            break;
        default:
            std::cout << "Opcion no es valida." << std::endl;
            break;
        }
    } while (option != 9);

    return 0;
}
