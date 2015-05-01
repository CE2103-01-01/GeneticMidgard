//
// Created by root on 30/04/15.
//

#include "movilObjectManager.h"
using namespace pugi;
using namespace constantsSubjectXML;
movilObjectManager::movilObjectManager() {
    xml_document objectSource;
    objectSource.load_file("object.xml");
    int distance=std::distance(objectSource.children("MOVILOBJECT").begin(),objectSource.children("MOVILOBJECT").end());

}
movilObject::movilObject(movilObjectManager* control,std::string name,int caracteristic,int value)  {
    xml_document objectDocument;
    objectDocument.load_file(CONSTANT_XML_PATH);
   objectDocument.child("movilObject").attributes();
    manager = control;
    use = false;
    type=name;
    object = caracteristic;
    effect = value;
}
void movilObject::applyEffect(Subject *person) {
    if (use!=true) {
        use = true;
        if (object == 0) {


        }
        else if(object==1){

        }
        else if(object==2){

        }
        else if(object==3){

        }
        else if(object==4){

        }
        else if(object==5){

        }
        else if(object==6){

        }
        else if(object==7){

        }
        else if(object==8){

        }
        else if(object==9){

        }


    }
    
}
movilObject::~movilObject() {
}
std::string movilObject::getType() {
    return type;
}