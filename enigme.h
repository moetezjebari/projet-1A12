/**
 * @file enigme.h
 * @version 1.2
 * @date 2 ,mai 2023
 * @brief enigme de jeux  
 */
#ifndef ENIGME_H_INCLUDED
#define ENIGME_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
/**
 * @brief structure enigme
 * @struct enigme 
 */
typedef struct
{
    SDL_Surface *fenetre_enigme; /*!< fenetre de l enigme >*/
    SDL_Surface *image; /*!< image a afficher >*/
    SDL_Surface *texte;/*!< texte a afficher  >*/
    TTF_Font *police; /*!< police a utiliser  >*/
    SDL_Rect posim,post; /*!< position dans l ecran  >*/
}enigme;


void init_enigme(enigme *enig,int ancienne[]);
void remplir_fichier(char fichier_question[]);
void afficher_enigme(enigme *enig,int *ancienne,char fichier_question[],int *ligne);
int solution(int q);
int resolution(int *affiche);
void afficher_resultat(enigme *enig,int solution,int resolution);
void ffree(enigme *enig);


#endif // ENIGME_H_INCLUDED
