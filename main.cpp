#include "Proof/laboratoryProof.h"
#include "libs/rapidjson/reader.h"
#include "Network/SocketLogic.h"

int main()
{
    sf::Thread thread(&SocketLogic::getInstance);// Inicializar el socket
    thread.launch();//NO QUITAR O MOVER


    
    laboratoryProof();
    return 0;


}