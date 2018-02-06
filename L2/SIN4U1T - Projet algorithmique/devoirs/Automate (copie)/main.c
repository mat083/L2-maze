#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void disp(int i, int j, int **tab)
{
    for (int l=0;l<=j+1;l++) //bordure haute du cadre
        printf ("* ");
    printf("\n");
    for(int k=0;k<i;k++)
    {
        printf ("* "); //bordure gauche du cadre
        for (int l=0;l<j;l++)
        {
        if (tab[k][l]==0){printf("  ");}
        else if (tab[k][l]==-1){printf (". ");}//on affiche un espace ou * en fonction de la valeur contenue à tab[k][l]
        else if (tab[k][l]==1){printf ("* ");}//on affiche un espace ou * en fonction de la valeur contenue à tab[k][l]

        //printf("%d",tab[k][l]);
        //(tab[k][l]?printf("* ") :printf ("  "));//on affiche un espace ou * en fonction de la valeur contenue à tab[k][l]
        }
        printf ("*\n"); //bordure droite du cadre
    }
    for (int l=0;l<=j+1;l++) // bordure basse du cadre
        printf ("* ");
    printf ("\n\n");
}

suivant(int x,int *i, int *j,int**tab)
{
    switch (x)
    {
        case 1:++*i;break;
        case 2:++*j;break;
        case 4:--*i;break;
        case 8:--*j;break;
    }
}


int ch_poss(int i,int j, int li, int co, int **tab) //recherche des déplacements possibles
{
        disp(li,co,tab);
    int ch=0;//il y a max 3 cases adjascentes possibles (on évite de faire des aller retours inutiles on ne revient pas sur case visitée... ou pas par là)


//on desccend si :
//la casse existe i<li-1
//pas encore visitee (ou pas finie) !=0

    //BAS
    if (i<li-1 && tab[i+1][j]==1)
    {
    //cellules adjascentes à la destination hors bords
        if(i<li-2 && j<co-1 && j>0) //cas general

        {
                if(!(tab[i+1][j-1]<1 && ((tab[i][j-1]<1 &&tab[i][j]<1) || (tab[i+2][j-1]<1 && tab[i+2][j]<1)))) //groupement par 3 -> pas possible
                    if (!(tab[i+1][j+1]<1 && ((tab[i][j+1]<1 &&tab[i][j]<1) || (tab[i+2][j+1]<1 && tab[i+2][j]<1))))
                        ch+=1;
            //memes conditions si cell adj on reprend les memes conditions avec les valeurs hors tableau à 1;
        }
        else if(i<li-2 && j==0) //bord gauche
        {
          if(!(tab[i+2][j]<1)) //groupement par 3 -> pas possible
                    if (!(tab[i+1][j+1]<1 && (tab[i][j+1]<1  || (tab[i+2][j+1]<1 && tab[i+2][j]<1))))
                        ch+=1;
        }
        else if(i<li-2 && j==co-1) //bord droit
        {
            if(!(tab[i+1][j-1]<1 && tab[i][j-1]<1)) //groupement par 3 -> pas possible
                if (!(tab[i+2][j]<1))
                    ch+=1;
        }

        else if(i==li-2 && j<co-1 && j>0) //bord bas
        {    if(!(tab[i+1][j-1]<1 && tab[i][j-1]<1 ) || !(tab[i+1][j+1]<1 && tab[i][j+1]<1 &&tab[i][j]<1))// &roupement par 3 -> pas possible
                        ch+=1;
        }
        //bord haut inutile : on descend
        //angles
        else if(j==0 && i==li-2) //angle gauche
            {
                if (!(tab[i+1][j+1]>0 && tab[i][j+1]<0 ))
                    ch+=1;
            }
        else if(j==co-1 && i==li-2) // angle bas droite ok
        {
            if (!(tab[i+1][j-1]>0 && tab[i][j-1]<0 ))
                ch+=1;
        }
    } //FIN SI BAS


    //DROITE
    if (j<co-1 && tab[i][j+1]==1)
    {

        if(j<co-2 && i<li-1 && i>0) //cas general
        {

        if(!(tab[i-1][j+1]<1 && ((tab[i-1][j]<1 &&tab[i][j]<1) || (tab[i-1][j+2]<1 && tab[i][j+2]<1)))) //groupement par 3 -> pas possible
                if (!(tab[i+1][j+1]<1 && ((tab[i+1][j]<1 &&tab[i][j]<1) || (tab[i+1][j+2]<1 && tab[i][j+2]<1))))
                        ch+=2;
            //memes conditions si cell adj on reprend les memes conditions avec les valeurs hors tableau à 1;
        }
        else if(j<co-2 && i==0) //bord gauche
        {
          if(!(tab[i][j+2]<1))//groupement par 3 -> pas possible
                    if (!(tab[i+1][j+1]<1 && (tab[i+1][j]<1 || (tab[i+1][j+2]<1 && tab[i][j+2]<1))))
                        ch+=2;
        }
        else if(j<co-2 && i==li-1) //bord droit
        {
            if(!(tab[i-1][j+1]<1 && tab[i-1][j]<1 )) //groupement par 3 -> pas possible
                if (!(tab[i][j+2]<1))
                    ch+=2;
        }

        else if(j==co-2 && i<li-1 && i>0) //bord bas
        {    if(!(tab[i-1][j+1]<1 && tab[i-1][j]<1 ) || !(tab[i+1][j+1]<1 && tab[i+1][j]<1))// &roupement par 3 -> pas possible
                        ch+=2;
        }
        //bord haut inutile : on descend

        //angles
        else if(i==0 && j==co-2)
        {
            if (!(tab[i+1][j+1]<1 && tab[i+1][j]<1 ))
                ch+=2;
        }
        else if(j==co-2 && i==li-1) //angle droit OK
        {
            if (!(tab[i-1][j+1]<1 && tab[i-1][j]<1))
                ch+=2;
        }
    } //FIN SI DROITE


    //HAUT
    if (i>0 && tab[i-1][j]==1)
    {
    //cellules adjascentes à la destination hors bords
        if(i>1 && j<co-1 && j>0) //cas general

        {
            if(!(tab[i-1][j-1]<1 && ((tab[i][j-1]<1 &&tab[i][j]<1) || (tab[i-2][j-1]<1 && tab[i-2][j]<1)))) //groupement par 3 -> pas possible
                if (!(tab[i-1][j+1]<1 && ((tab[i][j+1]<1 &&tab[i][j]<1) || (tab[i-2][j+1]<1 && tab[i-2][j]<1))))
                    ch+=4;
            //memes conditions si cell adj on reprend les memes conditions avec les valeurs hors tableau à 1;
        }
        else if(i>1 && j==0) //bord gauche
        {
          if(!(tab[i-2][j]<1))//groupement par 3 -> pas possible
                    if (!(tab[i-1][j+1]<1 && (tab[i][j+1]<1  || (tab[i-2][j+1]<1 && tab[i-2][j]<1))))
                        ch+=4;
        }
        else if(i>1 && j==co-1) //bord droit //OK
        {
            if(!(tab[i-1][j-1]<1 && tab[i][j-1]<1 && tab[i][j]<1)) //groupement par 3 -> pas possible
                if (!(tab[i-2][j]<1))
                    ch+=4;
        }

        else if(i==1 && j<co-1 && j>0) //bord haut
        {    if(!(tab[i-1][j-1]<1 && tab[i][j-1]<1 &&tab[i][j]<1) || !(tab[i-1][j+1]<1 && tab[i][j+1]<1 &&tab[i][j]<1))// &roupement par 3 -> pas possible
                        ch+=4;
        }
        //bord haut inutile : on descend
        //angles
        else if(j==0 && i==1)
            {
                if (!(tab[i-1][j+1]<1 && tab[i][j+1]<1 ))
                    ch+=4;
            }
        else if(j==co-1 && i==1) //angle SUP droit OK
        {
            if (!(tab[i-1][j-1]<1 && tab[i][j-1]<1 ))
                ch+=4;
        }
    } //FIN SI HAUT

//GAUCHE
    if (j>0 && tab[i][j-1]==1)
    {
        if(j>1 && i<li-1 && i>0) //cas general //ok

        {
                if(!(tab[i-1][j-1]<1 && ((tab[i-1][j]<1 &&tab[i][j]<1) || (tab[i-1][j-2]<1 && tab[i][j-2]<1)))) //groupement par 3 -> pas possible
                    if (!(tab[i+1][j-1]<1 && ((tab[i+1][j]<1) || (tab[i+1][j-2]<1 && tab[i][j-2]<1))))
                        ch+=8;
            //memes conditions si cell adj on reprend les memes conditions avec les valeurs hors tableau à 1;
        }
        else if(j>1 && i==0) //bord HAUT
        {
          if(!(tab[i+1][j-1]<1 && tab[i+1][j]<1))//groupement par 3 -> pas possible
                 //   if (!(tab[i+1][j]<1))
                        ch+=8;
        }
        else if(j>1 && i==li-1) //bord bas OK
        {
            if(!(tab[i-1][j-1]<1 && tab[i-1][j]<1 )) //groupement par 3 -> pas possible
                if (!(tab[i][j-2]<1))
                    ch+=8;
        }

        else if(j==1 && i<li-1 && i>0) //bord gauche
        {    if(!( tab[i-1][j]<1  || (tab[i+1][j-1]<1 && tab[i+1][j]<1)))// &roupement par 3 -> pas possible
                        ch+=8;
        }
        //bord haut inutile : on descend

        //angles A VERIF
        else if(i==0 && j==1)
        {
            if (!(tab[i+1][j-1]<1 && tab[i+1][j]<1 ))
                ch+=8;
        }
        else if(j==1 && i==li-1) //angle bas gauche ok
        {
            if (!(tab[i-1][j-1]<1 && tab[i-1][j]<1 ))
                ch+=8;
        }
    } //FIN SI GAUCHE


    return (ch); //si ch=0 la case suivante soit n'existe pas soit totalement visitée
}




int** init(int li,int co)
{
    int **tab=NULL;
    tab=(int**)malloc(sizeof(int*)*li); //allocation espace mem pour stocker li pointeurs sur tableau d'entiers
    for(int cpt=0;cpt<li;cpt++)
    {
        tab[cpt]=(int*)malloc(sizeof(int)*co); //allocation d'espace memoire pour stocker co entiers
        for (int it2=0;it2<co;it2++)
            tab[cpt][it2]=1;
    }
    return (tab);
}

void adjacent(int li,int co,int **tab)
{
    srand(time(NULL));
    int i=rand()%li,j=rand()%co;
    int cpt=(li*co);
    int *chem=malloc(cpt*2*sizeof(int));
    int ichem=0; //indice pout chem[]
//cell non visitées /mur : 1
//cell partiellement tritée : -1
//cell traitée : 0
//mur : 1
    while ( ichem>=0)
    {
        int nbadj=0;
        tab[i][j]=-1; //la cellule corrante passe en statut visitée

        int adj=ch_poss(i,j,li,co,tab); //on cherche les directions possibles et stock dans adj
        int tmp[3]={0,0,0};//tmp représente le tableau des valeurs possibles
        chem[ichem]=i; //récupération de la position de i
        chem[++ichem]=j; //récupération de la position de j
        ++ichem;
        // decodage adj
        if(adj-8>=0)
        {
            tmp[nbadj++]=8;
            //++nbadj;
            adj-=8;
        }
        if(adj-4>=0)
        {
            tmp[nbadj++]=4;
            //++nbadj;
            adj-=4;
        }
        if(adj-2>=0)
        {
            tmp[nbadj++]=2;
            //++nbadj;
            adj-=2;
        }
        if(adj-1>=0)
        {
            tmp[nbadj++]=1;
            //++nbadj;
            adj-=1;
        }
        if(nbadj>0) //si des chemins n'ont pas été totalement explorés
        {

            //si il ne reste qu'une cellule possible, on défini directement que tous les parcours sont explorés
     //adj permet de récupérer la position atteignable(1+2+4+8)

            switch(rand()%nbadj)
            {
                case 0:suivant(tmp[0],&i,&j,tab);break;//i+2
                case 1:suivant(tmp[1],&i,&j,tab);break;//j+2
                case 2:suivant(tmp[2],&i,&j,tab);break;//i-2
                case 3:suivant(tmp[3],&i,&j,tab);break;//j-2
                default:break;
            }
        }
        else
        {
            tab[i][j]=0; //si on ne peut plus visiter on fout la case à 0

            if (ichem>3)// si on est bloqué, on remonte la file
            {
                ichem--;
                j=chem[ichem-=2];
                i=chem[--ichem];
            }
            else ichem=-1;
        }
      //  disp(li,co,tab);
    }
}

//cette fonction recoit en parametre l'adresse d'un tableau à 2 dimension et la taille de ce tableau. Elle va aficher un espace si la valeur dans le tableau est 0, et * si la valeur est 1. Le tableau sera encadré par des *
/*creer_cell(int li,int co,int*i,int*j,int**tab, int ichem)
{
    if(*i)


}*/
int** generer(int li, int co) //, int tab[li][co]
{
    int ** tab=init(li,co); //init du tableau : toutes les cellules sont à 1
    disp(li,co,tab); //azffichage du tableau initialisé
    int i=0,j=0;
    int *chemin=malloc(i*j*sizeof(int));
   // creer_cell(li,co, &i,&j,tab,chemin);
    adjacent(li,co,tab);

    while (li > 0 && tab[li-1][co-1]!=0 )
        tab[(--li)][co-1]=0;
    j=0;
    while (tab[0][j]!=0 && co-j>0)
        tab[0][j++]=0;




    printf("\n\n");

    return(tab);
}

int main()
{
    int li,co; //pour le test de la fonction disp. A supprimer par la suite
    printf("nombre de ligne");
    scanf("%d", &li);
    printf("nombre de colonnes");
    scanf("%d", &co);
    printf("%d lignes %d col \n\n",li,co);
int ** tab=generer(li,co);
disp(li,co,tab); // appel de la fonction, permettant l'afichage du tableau
sleep(130);
for (int a=0;a<li;a++)
    free(tab[a]);
free(tab);
return 0;
}






