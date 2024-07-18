//#include <iostream>
//#include <unordered_map>
//#include <string>
//#include <vector>
//#include "Enemigo.h"
//
//// Gestor de prototipos
//class EnemyManager {
//private:
//    std::unordered_map<std::string, Enemigo*> prototypes;
//
//public:
//    EnemyManager() {
//        prototypes["Serpiente"] = new Serpiente();
//        prototypes["Erizo"] = new Erizo();
//    }
//
//    ~EnemyManager() {
//        for (auto& pair : prototypes) {
//            delete pair.second;
//        }
//    }
//
//    Enemy* createEnemy(const std::string& type) {
//        return prototypes[type]->clone();
//    }
//};