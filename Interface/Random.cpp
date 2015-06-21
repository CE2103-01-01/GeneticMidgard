//
// Created by pablo on 20/04/15.
//


#include "Random.h"


int fd =-1;
Stack<int> randomNumbers;
void trueRandom::init(){
    fd = open("/dev/ttyACM0", O_RDONLY | O_NOCTTY);
    if (fd == -1)
    {
        std::cout<<"C++ Random"<<std::endl;
        std::srand(std::time(NULL)); //use current time as seed for random generator
        return ;
    }
    std::cout << "Arduino Connected" << std::endl;
    pthread_t receive;
    pthread_create(&receive, NULL, &receive_numbers, NULL);

}

int trueRandom::getRandom(){
    if(fd==-1 || randomNumbers.empty())return std::rand();

    int number = randomNumbers.top();
    randomNumbers.pop();
    return number;
}

int trueRandom::randRange(int min, int max){
    return min + (rand() % (int)(max - min + 1));
}

float trueRandom::randRange(float min, float max){
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}

void *receive_numbers(void* ){
    char buff = 0;
    while(true) {
        if (randomNumbers.size()>200) sleep(10);
        bool first_valid =false;
        std::string number = "00";
        while (true) {
            read(fd, &buff, 1);
            if(buff!=10){
                first_valid=true;
                number[0] = number[1];
                number[1] = buff;
            }
            else{
                if (first_valid){
                    randomNumbers.push(std::atoi(number.c_str()));
                    //std::cout << randomNumbers.top() << std::endl;
                    break;
                }
                else break;
            }


            //std::cout << int(buff) << ", " << buff << std::endl;
        }
    }

}
