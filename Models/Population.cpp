//
// Created by Pablo Rodriguez Quesada on 4/25/15.
//

#include "Population.h"
#include "../Algorithms/lifeLaboratory.h"
#include "Terrain.h"

#define COLOR_XML_PATH "res/populationColors.xml"
#define COLOR_XML_ROOT "POPULATION_COLORS"
#define COLOR_XML_NODE "color"

/** Construye una poblacion
 * @param Tree<Subject>* peopleTreeParam: primera generacion
 * @param char populationTypeParam: tipo de poblacion
 */
Population::Population(char populationTypeParam, int* activePopulationsOnManagerParam){
    //Reserva espacios
    colors = static_cast<unsigned char*>(malloc(3));
    rapidxml::xml_node<>* root_node;
    rapidxml::xml_document<> doc;
    rapidxml::file<> file(COLOR_XML_PATH);
    doc.parse<0>(file.data());
    root_node = doc.first_node(COLOR_XML_ROOT)->first_node(COLOR_XML_NODE);
    for(int i = 0; i<populationTypeParam; i++){
        root_node = root_node->next_sibling();
    }
    rapidxml::xml_attribute<>* tmpColor = root_node->first_attribute();
    for(int i = 0; i<3; i++){
        tmpColor = tmpColor->next_attribute();
        *(colors+i) = std::atoi(tmpColor->value());
    }
    activePopulationsOnManager = activePopulationsOnManagerParam;
    populationType = static_cast<char*>(malloc(sizeof(char)));
    *populationType = populationTypeParam;
    populationSize = static_cast<int*>(malloc(sizeof(int)));
    *populationSize = 0;
    fittest = static_cast<Subject**>(malloc(sizeof(Subject*) * 2 * SUBJECTS_BY_GENERATION));
    actualGeneration = static_cast<int*>(malloc(sizeof(int)));
    *actualGeneration = 1;
    populationTree = static_cast<Tree<Subject>*>(malloc(sizeof(Tree<Subject>)));
    new(populationTree) Tree<Subject>();
    defunct = static_cast<bool*>(malloc(sizeof(bool)));
    *defunct = false;
    position = static_cast<Vector2D*>(malloc(sizeof(Vector2D)));
    *position = (Terrain::getRandomFreePosition());
}

/**@brief: libera el espacio utilizado
 */
Population::~Population() {
    free(fittest);
    free(colors);
    free(populationTree);
    free(defunct);
    free(actualGeneration);
    free(populationSize);
    free(populationType);// tipo de la poblacion
    activePopulationsOnManager = 0;
}

/**@brief: inserta un nuevo miembro
 * @param Subject* father: padre del individuo
 * @param Subject* mother: madre del individuo
 * @param Chromosome* chromosome: cromosoma del individuo
 */
void Population::insertNewMember(Subject* father, Subject* mother, Chromosome* chromosome) {
    (*populationSize)++;
    populationTree->insertElement(Subject(father, mother, chromosome, (*actualGeneration),
                                          (*populationSize)*SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID + (*populationType),
                                          actualGeneration),
                                  *populationSize
                                 );
    Subject* selected = populationTree->searchElement(*populationSize);
    selected->start_p_thread();
    if((*(fittest+2*SUBJECTS_BY_GENERATION-1))->getFitness()<=selected->getFitness())updateFittest(selected);
    else selected->kill();
}

/**@brief: inserta un nuevo miembro
 * @param Subject* nuevo miembro
 */
void Population::insertNewMember(Subject* newMemberParam) {
    (*populationSize)++;
    populationTree->insertElement(
            Subject(newMemberParam, newMemberParam, newMemberParam->getGeneticInformation(), (*actualGeneration),
                    (*populationSize)*SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID + (*populationType), actualGeneration
                   ),
            *populationSize
            );
    Subject* selected = populationTree->searchElement(*populationSize);
    selected->start_p_thread();
    *(fittest+*populationSize-1) = selected;
}

/**@brief: inserta un nuevo miembro random
 */
void Population::createNewRandomMember() {
    (*populationSize)++;
    populationTree->insertElement(Subject((*populationSize)*SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID + (*populationType),
                                           actualGeneration, colors, Terrain::getFreePositionNear(*position)
                                         ),
                                  *populationSize
                                 );
    Subject* newMember = populationTree->searchElement(*populationSize);
    newMember->start_p_thread();
}

void Population::createNewStrongRandomMember() {
    (*populationSize)++;
    populationTree->insertElement(Subject((*populationSize)*SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID + (*populationType),
                                          actualGeneration, colors, Terrain::getFreePositionNear(*position),200
                                  ),
                                  *populationSize
    );
    Subject* newMember = populationTree->searchElement(*populationSize);
    newMember->start_p_thread();
}

/**@brief: inserta un nuevo miembro random
 * @param Subject* newMember: nuevo miembro
 */
void Population::updateFittest(Subject* newMember) {
    //Se ingresa al metodo porque el parametro tiene mayor fitness que el ultimo, por eso se asigna para evitar
    //comparaciones redundantes
    if((*(fittest+2*SUBJECTS_BY_GENERATION-1))->getOpponent() && (*(fittest+2*SUBJECTS_BY_GENERATION-1))->getOpponent()->isAlive()) {
        newMember->setOpponent((*(fittest+2*SUBJECTS_BY_GENERATION-1))->getOpponent());
    }
    (*(fittest+2*SUBJECTS_BY_GENERATION-1))->kill();
    *(fittest+2*SUBJECTS_BY_GENERATION-1) = newMember;
    //Itera acomodando al nuevo miembro en la posicion correspondiente
    for(int i = 2*SUBJECTS_BY_GENERATION-1; i>0; i--){
        //Si el sujeto en i tiene mayor fitness que el de i-1, estan desordenados y se hace un swap
        if((*(fittest+i))->getFitness() > (*(fittest+i-1))->getFitness()){
            //Se crea un temporal con el sujeto en i-1
            Subject* tmp = *(fittest+i-1);
            //Se guarda el sujeto i en el campo i-1
            *(fittest+i-1) = *(fittest+i);
            //Se guarda el temporal en el campo i
            *(fittest+i) = tmp;
        }
    }
}

/**@brief: busca los muertos
 */
void Population::updateFittest() {
    int deficit = 0;
    //Itera acomodando al nuevo miembro en la posicion correspondiente
    for(int i = 2*SUBJECTS_BY_GENERATION-1; i>=0; i--){
        //Si un miembro esta muerto
        if(!((*(fittest+i))->isAlive())){
            deficit++;
            for(int j = i+1; j < 2*SUBJECTS_BY_GENERATION-deficit; j++){
                //Se acomoda al muerto al final
                Subject* tmp = *(fittest+j);
                *(fittest+j) = *(fittest+j-1);
                *(fittest+j-1) = tmp;
            }
        }
    }
    fillFittest();
}

/**@brief devuelve el tipo de poblacion
 * @return char
 */
void Population::updateGeneration() {
    (*actualGeneration)++;
}

/**@brief mata a todos los sujetos
 */
void Population::killEmAll() {
    for(int i = 0; i < 2*SUBJECTS_BY_GENERATION; i++){
        (*(fittest+i))->kill();
    }
}

/**@brief bandera de extincion
 * @return bool
 */
bool Population::isDefunct() {
    return *defunct;
}


/**@brief accede a los mejores
 * @return Subject**
 */
Subject** Population::getFittest() {
    return fittest;
}

/**@brief llena la lista de los mejores seres
 */
void Population::fillFittest(){
    if(*populationSize > INITIAL_NUMBER_OF_SUBJECTS){
        //Busca la cantidad de padres necesaria con mejor fitness
        for(int i = 0; i < SUBJECTS_BY_GENERATION; i++){
            if(populationTree->searchElement(*populationSize - i)->isSelected()) break;
            //Pregunta si esta lleno el espacio de los muertos y compara uno a uno los nuevos sujetos con los mejores
            //Hace cambios si el nacimiento es mejor o hubo muertos
            if(!(*(fittest + 2*SUBJECTS_BY_GENERATION-1))->isAlive() |
               populationTree->searchElement(*populationSize - i)->getFitness()
               >= (*(fittest + 2*SUBJECTS_BY_GENERATION-1))->getFitness()) {
                //Mata al menor
                (*(fittest + 2*SUBJECTS_BY_GENERATION-1))->kill();
                populationTree->searchElement(*populationSize - i)->changeSelection(true);
                //Coloca al nuevo mejor en el lugar del muerto
                (*(fittest + 2*SUBJECTS_BY_GENERATION-1)) = populationTree->searchElement(*populationSize - SUBJECTS_BY_GENERATION + i);
                //Busca la posicion real del nuevo miembro
                for(int j = 2*SUBJECTS_BY_GENERATION-2; j > 0; j--){
                    //Si la posicion anterior es mejor, hace el cambio
                    if((*(fittest + j))->getFitness() > (*(fittest + j-1))->getFitness()){
                        //Toma temporal y hace swap
                        Subject* tmp = (*(fittest + j-1));
                        *(fittest + j-1) = *(fittest + j);
                        *(fittest + j) = tmp;
                    }
                }
            }
        }
    }else{
        //Busca la cantidad de padres necesaria con mejor fitness
        for(int i = 0; i < 2*SUBJECTS_BY_GENERATION; i++){
            *(fittest+i) = populationTree->searchElement(i+1);
            (*(fittest+i))->changeSelection(true);
        }
    }
}

/**@brief bandera de extincion
 * @return bool
 */
void Population::exterminate(){
    killEmAll();
    *defunct = true;
    (*activePopulationsOnManager)--;
}

/**@brief id del ultimo sujeto
 * @return int
 */
int Population::getActualID(){
    return *populationSize;
}

/**@brief busca un sujeto y lo retorna
 * @paran long id: id de nacimiento = subject->getID()/SUBJECT_ID_MULTIPLIER_FOR_POPULATION_ID
 * @return Subject*
 */
Subject* Population::getSubject(long id){
    return populationTree->searchElement(id);
}

unsigned char Population::getColors()
{
    return *colors;
}