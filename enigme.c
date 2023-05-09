
/**
 * @file enigme.c 
 * @version 1.2
 * @date 2 ,mai 2023
 * @brief enigme de jeux  
 */#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include "enigme.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
/**
 * @brief to initialize the enigme  
 * @return Nothing 
 * @param enigme *enig
 * @param int ancienne 
 */
void init_enigme(enigme *enig,int ancienne[])
{
    int i;
    enig->fenetre_enigme=NULL;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    enig->image=NULL;
    enig->posim.x=0;
    enig->posim.y=0;
    enig->post.x=300;
    enig->post.y=50;
    for(i=0;i<6;i++)
    {
       ancienne[i]=0;
    }
}
/**
 * @brief pour remplir le fichier d enigme   
 * @return Nothing 
 * @param char fichier_question 

 */
void remplir_fichier(char fichier_question[])
{
    FILE *fq=NULL;
    fq=fopen(fichier_question,"w");
    if(fq==NULL) printf("erreur de l'ouverture");
    else
    {
	fprintf(fq,"Neil Armstrong undermined his accomplishment in Space? \nScientific thought is belongs to humankind? \nNasa will pay you to lie in bed for months at a time? \nPeople have walked on the planet Mars? \nMars is known as the purple planet? \nNasa was once sued for trespassing on Mars.? \n");
	fclose(fq);
    }
}
/**
 * @brief pour afficher lenigme  
 * @return Nothing 
 * @param enigme enig 
 * @param int ancienne
 * @param char fichier_question
 * @param int ligne  
 */
void afficher_enigme(enigme *enig,int ancienne[],char fichier_question[],int *ligne)
{
   FILE *fq=NULL;
   int i,ici=0,taille=200,l;
   char ch[200];
   SDL_Color couleur={255,128,64};
   do
   {  ici=0;
      l=1+random()%6;
  printf("\nvoici notre premier l :%d\n",l);
      for(i=0;i<6;i++)
      {
         if(ancienne[i]==l)
                 {
                    ici=1;
                    break;
                 }
      }
   }while(ici==1);
   for(i=0;i<6;i++)
   {
         if(ancienne[i]==0)
                 {
                    ancienne[i]=l;
                    break;
                 }
   }
   if(ancienne[5]!=0) { 
              	         for(i=0;i<6;i++)
              	         {
                            ancienne[i]=0;
              	         }
                      }
   enig->fenetre_enigme=SDL_SetVideoMode(1400,787,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
   enig->image=IMG_Load("space.png");
   enig->police=TTF_OpenFont("space.ttf",60);
   fq=fopen(fichier_question,"r");
   if(fq==NULL) printf("erreur de l'ouverture");
    else{ 
           (*ligne)=1;
	   while((fgets(ch,taille,fq)!=NULL)&&(*ligne<l))
	        {
	    	    (*ligne)++;
	        }
           enig->texte=TTF_RenderText_Blended(enig->police,ch,couleur);
	   SDL_BlitSurface(enig->image,NULL,enig->fenetre_enigme,&(enig->posim));
	   SDL_BlitSurface(enig->texte,NULL,enig->fenetre_enigme,&(enig->post));
	   SDL_Flip(enig->fenetre_enigme);
	   fclose(fq);
        }
   
}
/**
 * @brief initialisation des solutions  
 * @return Nothing 
 * @param int q 
 */
int solution(int q)
{
int s=0;
    switch(q)
    {
    case 1:
        s=2;
        break;
    case 2:
        s=1;
        break;
    case 3:
        s=1;
        break;
    case 4:
        s=2;
        break;
    case 5:
        s=2;
        break;
    case 6:
        s=1;
        break;
    }
    return s;
}
/**
 * @brief resolution de chaque reponse  
 * @return la reponse choisi 
 * @param int affiche 
 */
int resolution(int *affiche)
{
    SDL_Event event;
    int r=0;
    SDL_PollEvent(&event);
    switch(event.type)
    {

    case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
        case SDLK_a:
            r=1;
	    *affiche=1;
            break;
        case SDLK_z:
            r=2;
	    *affiche=1;
            break;
   
        }
        break;
    }
    return r;
}
/**
 * @brief pour afficher la resultat  
 * @return Nothing 
 * @param enigme enig 
 * @param int solution
 * @param resolution 
 */
void afficher_resultat(enigme *enig,int solution,int resolution)
{
   
    if(solution==resolution)
    {
        enig->image=IMG_Load("0.png");
        SDL_BlitSurface(enig->image,NULL,enig->fenetre_enigme,&(enig->posim));
        SDL_Flip(enig->fenetre_enigme);
        //p->score=p->score+20;
    }
    else
    {
        enig->image=IMG_Load("1.png");
        SDL_BlitSurface(enig->image,NULL,enig->fenetre_enigme,&(enig->posim));
        SDL_Flip(enig->fenetre_enigme);
        //p->score=p-score-20;
    }
}
/**
 * @brief vider  
 * @return Nothing 
 * @param enigme enig 
 */
void ffree(enigme *enig)
{
    TTF_CloseFont(enig->police);
    TTF_Quit();
    SDL_FreeSurface(enig->image);
    SDL_FreeSurface(enig->texte);
    SDL_Quit();
}
