//
// Created by pablo on 22/04/15.
//


#include "Genes.h"

Genes::Genes(char pDna[Gene::lenght]) {
 dna = malloc(sizeof((Gene::lenght*sizeof(char))));
 char* tmp =  static_cast<char*>(dna);
 for (int i = 0; i < Gene::lenght; ++i) {
  *(tmp+i) = pDna[i];
 }
};

Genes::Genes(void *pDna) {
 dna = pDna;

};


char Genes::getGene(Gene gen) {
 char* tmp =  static_cast<char*>(dna);
 return *(tmp+gen);
}
