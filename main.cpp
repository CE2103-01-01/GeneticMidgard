#include "Models/Population.h"

int main()
{
    //sf::Thread thread(&SocketLogic::getInstance);// Inicializar el socket
    //thread.launch();//NO QUITAR O MOVER

    Population* population = static_cast<Population*>(malloc(sizeof(Population)));
    new(population) Population(0);

    population->init_pthread();
    pthread_join(*population->get_pthread(),0);
    return 0;
}