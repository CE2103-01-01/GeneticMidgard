#include "Proof/laboratoryProof.h"
#include "libs/rapidjson/reader.h"
#include "Network/SocketLogic.h"

int main()
{
    sf::Thread thread(&SocketLogic::getInstance);// Inicializar el socket
    thread.launch();//NO QUITAR O MOVER

    Tree<Subject>* proof = static_cast<Tree<Subject>*>(malloc(sizeof(Tree<Subject>)));
    new(proof) Tree<Subject>();

    Tree<int>* proof2 = static_cast<Tree<int>*>(malloc(sizeof(Tree<int>)));
    new(proof2) Tree<int>();

    for(int i =0; i<3000; i++){
        proof2->insertElement(i,i);
    }

    for(int i =0; i<3000; i++){
        std::cout << "Element " <<*(int*)(proof2->searchElement(i)) << " is on "<< (int*)(proof2->searchElement(i))  <<std::endl;
    }

    std::cout << "FINISH WITH INTEGERS" << std::endl;

    for(int i =0; i<3000; i++){
        proof->insertElement(Subject(i+1),i);
    }

    for(int i =0; i<3000; i++){
        std::cout << "ID " << ((Subject*)proof2->searchElement(i))->getID() << std::endl;
    }

    //laboratoryProof();
    return 0;


}