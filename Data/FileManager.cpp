//
// Created by roberto on 25/05/15.
//

#include "FileManager.h"

/** Escritor de archivos
 * @brief guarda un archivo formato EXTENSION
 * @param: void* data: dato a guardar
 * @param: int id: numero de archivo
 * @param: int dSize: tamaño del dato
 */
void FileManager::writeFile(const char *data, int id, int dSize) {
    std::string path = constants::PROJECT_PATH + PATH + std::to_string(id) + EXTENSION;
    std::ofstream outFile(path, std::ios::binary);
    outFile.write(data, dSize);
    outFile.close();
}

/** Lector de archivos
 * @brief lee un archivo formato EXTENSION
 * @param: void* ret: dato a cargar
 * @param: int id: numero de archivo
 * @param: int retSize: tamaño del dato
 */
void FileManager::readFile(char *ret, int id, int size) {//T(11+6i)
    std::string path = constants::PROJECT_PATH + PATH + std::to_string(id) + EXTENSION;
    std::ifstream inFile(path, std::ios::binary);
    inFile.read(ret,size);
    inFile.close();
}

/** Borra archivo
 * @brief borra un archivo formato EXTENSION
 * @param: int id: numero de archivo
 */
void FileManager::deleteFile(int id){
    std::string path = constants::PROJECT_PATH + PATH + std::to_string(id) + EXTENSION;
    remove(path.c_str());
}