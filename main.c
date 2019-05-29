#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

//Pour pouvoir sauvegarder le labyrinthe généré dans un fichier
void save_laby(int li, int co, int **tab)
{
    printf("Entrez un nom de fichier pour votre laby dans rep courrant ou entrez  un chemin complet+nomde fichier\n");
    char chem[150];
    scanf("%s",&chem);
    printf("%c,chem");
    FILE *flaby=fopen(chem,"w"); //On va créer le fichier avec le nom saisi et l'ouvrir
    fprintf(flaby,"%d %d\n",li,co); //pour pas s'embeter, on place à la premiere ligne la valeur de li et de co

    for(int i=0;i<li;i++) //ensuite chaque cellule du tableau va être recopiée dans le fichier
    {
        for(int j=0;j<co;j++)
            fprintf(flaby,"%d ",tab[i][j]);
        fprintf(flaby,"\n"); //ligne suivante
    }
    fclose(flaby); // on ferme le fichier
}


//Fonction qui va gérer l'affichage
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
        if (tab[k][l]==0 ||tab[k][l]==8){printf("  ");} // la valeur 8 a été rajoutée par rapport à la fonction sortir1
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

//passer à la cellule suivante du laby selon la valeur de x
suivant(int x,int *i, int *j)
{
    switch (x)
    {
        case 1:++(*i);break;
        case 2:++(*j);break;
        case 4:--(*i);break;
        case 8:--(*j);break;
    }
}





int ch_poss(int i,int j, int li, int co, int **tab) //recherche des déplacements possibles
{
        printf("\e[1;1H\e[2J");
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
        {
			if(!(tab[i+1][j-1]<1 && tab[i][j-1]<1 ) || !(tab[i+1][j+1]<1 && tab[i][j+1]<1 &&tab[i][j]<1))// &roupement par 3 -> pas possible
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
        {
            if(!(tab[i-1][j+1]<1 && tab[i-1][j]<1 ) || !(tab[i+1][j+1]<1 && tab[i+1][j]<1))// &roupement par 3 -> pas possible
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
        {
            if(!(tab[i-1][j-1]<1 && tab[i][j-1]<1 &&tab[i][j]<1) || !(tab[i-1][j+1]<1 && tab[i][j+1]<1 &&tab[i][j]<1))// &roupement par 3 -> pas possible
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

//Initialisation du tableau
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

//etude des cellules adjacentes à la cellule courante
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
        usleep(10000);//30000
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
                case 0:suivant(tmp[0],&i,&j);break;//i+2
                case 1:suivant(tmp[1],&i,&j);break;//j+2
                case 2:suivant(tmp[2],&i,&j);break;//i-2
                case 3:suivant(tmp[3],&i,&j);break;//j-2
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
    }
}


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


sortir1(int li, int co,int **tab)
{
    int i=0,j=0;
    int cpt=(li*co);
    int *chem=malloc(cpt*2*sizeof(int));
    int ichem=0; //indice pout chem[]
//cell non visitées /mur : 1
//cell partiellement tritée : -1
//cell traitée : 0
//mur : 1
    while (!(i==li-1 && j==co-1))
    {
        int nbadj=0;
        tab[i][j]=-1; //la cellule corrante passe en statut visitée


        int adj=0;//ch_poss(i,j,li,co,tab); //on cherche les directions possibles et stock dans adj

        if (i+1<li && tab[i+1][j]==0)
            adj+=1;
        if (j+1<co && tab[i][j+1]==0)
            adj+=2;
        if (i-1>=0 && tab[i-1][j]==0)
            adj+=4;
        if (j-1>=0 && tab[i][j-1]==0)
            adj+=8;

        int tmp[3]={0,0,0};//tmp représente le tableau des valeurs possibles
        chem[ichem]=i; //récupération de la position de i
        chem[++ichem]=j; //récupération de la position de j
        ++ichem;
        // decodage adj
        if(adj-8>=0)
        {
            tmp[nbadj++]=8;
            adj-=8;
        }
        if(adj-4>=0)
        {
            tmp[nbadj++]=4;
            adj-=4;
        }
        if(adj-2>=0)
        {
            tmp[nbadj++]=2;
            adj-=2;
        }
        if(adj-1>=0)
        {
            tmp[nbadj++]=1;
            adj-=1;
        }
        if(nbadj>0) //si des chemins n'ont pas été totalement explorés
        {
            //si il ne reste qu'une cellule possible, on défini directement que tous les parcours sont explorés
     //adj permet de récupérer la position atteignable(1+2+4+8)
            suivant(tmp[nbadj-1],&i,&j);
        }
        else
        {
            tab[i][j]=8; //si on ne peut plus visiter on fout la case à 8
            if (ichem>3)// si on est bloqué, on remonte la file
            {
                ichem--;
                j=chem[ichem-=2];
                i=chem[--ichem];
            }
            else ichem=-1;
        }
        usleep(50000);
        printf("\e[1;1H\e[2J"); //effacer l'ecran
        disp(li,co,tab); //bien penser à gerer le 8 comme " " pour que l'affichage des étapes intermédiaires soit correct
    }
    tab[i][j]=-1; // la derniere valeur est effectivement une cellule faisant partie du chemin
    //pour garder un tableau de sortie conforme, on remplace toutes les valeurs à 8 par 0
    for (int a =0;a<li;a++)
        for(int b=0;b<co;b++)
            if(tab[a][b]==8)
                tab[a][b]=0;
    printf("\e[1;1H\e[2J");
    printf("Un chemin a été trouvé !\n");
    disp(li,co,tab);
    sleep(3);
}

int menu()
{
    int choix;
    printf("MENU :\n");
    printf("1 - Generer\n"); //ret int**
    printf("2 - Charger labyrinthe\n"); //ret int **
    printf("0 - Quitter\n");
    int ret;
    scanf("%d",&ret);
    return ret;
}

//leberation de ma méoire allouée via malloc
liberer(int li,int**tab)
{
    for (int a=0;a<li;a++)
        free(tab[a]);
    free(tab);
}

//chargement du laby à partir d'un fichier
int ** load_laby(int *li,int *co)
{
    printf("Entrez un nom de fichier pour votre laby dans rep courrant ou entrez  un chemin complet+nomde fichier\n");
    char chem[150];
    scanf("%s",&chem);
    FILE *flaby=fopen(chem,"r");
    //on recupere les valeurs de li et de co dans le fichier et on initialise le tableau
    fscanf(flaby,"%d %d",&(*li),&(*co));
    int ** tab =init(*li,*co);
    //puis on remplit le tableau avec les valeurs
    for (int i=0; i<*li;i++)
        for (int j= 0; j<*co;j++)
            fscanf(flaby, "%d", &tab[i][j]);
    fclose(flaby);
    return (tab);
}

//solveur de laby
void sortir2(int li, int co,int **tab,int*deplacement,int regle)
{
    int i=0,j=0;
    int cpt=(li*co);
    int *chem=malloc(cpt*2*sizeof(int));
    int ichem=0; //indice pout chem[]
    int i_depl=0; //indice pour deplacement[]
    while (ichem>=0 && !(i==li-1 && j==co-1)) //tant qu'on n'a pas parcouru tout ce qui était parcorable et que la sortie n'a pas été trouvée
    {
        int nbadj=0;
        tab[i][j]=-1; //la cellule corrante passe en statut visitée
        int adj=0;//on cherche les directions possibles et stock dans adj
        if (i+1<li && tab[i+1][j]==0)
            adj+=1;
        if (j+1<co && tab[i][j+1]==0)
            adj+=2;
        if (i-1>=0 && tab[i-1][j]==0)
            adj+=4;
        if (j-1>=0 && tab[i][j-1]==0)
            adj+=8;

        int tmp[3]={0,0,0};//tmp représente le tableau des valeurs possibles
        chem[ichem]=i; //récupération de la position de i
        chem[++ichem]=j; //récupération de la position de j
        ++ichem;

        // decodage adj
        if(adj-8>=0)
        {
            tmp[nbadj++]=8;
            adj-=8;
        }
        if(adj-4>=0)
        {
            tmp[nbadj++]=4;
            adj-=4;
        }
        if(adj-2>=0)
        {
            tmp[nbadj++]=2;
            adj-=2;
        }
        if(adj-1>=0)
        {
            tmp[nbadj++]=1;
            adj-=1;
        }
        if(nbadj>0) //si des chemins n'ont pas été totalement explorés
        {
            if (regle==0)
            {
                //si il ne reste qu'une cellule possible, on défini directement que tous les parcours sont explorés
                //adj permet de récupérer la position atteignable(1+2+4+8)
                switch(tmp[nbadj-1])
                {
                    case 1:
                        deplacement[i_depl++]=5;
                        break;
                    case 2:
                        deplacement[i_depl++]=3;
                        break;
                    case 4:
                        deplacement[i_depl++]=4;
                        break;
                    case 8:
                        deplacement[i_depl++]=2;
                        break;
                }
                suivant(tmp[nbadj-1],&i,&j);
            }
            if (regle==1)
            {
                switch(tmp[0])
                {
                    case 1:
                        deplacement[i_depl++]=5;
                        break;
                    case 2:
                        deplacement[i_depl++]=3;
                        break;
                    case 4:
                        deplacement[i_depl++]=4;
                        break;
                    case 8:
                        deplacement[i_depl++]=2;
                        break;
                }
                suivant(tmp[0],&i,&j); // on récupere la derniere case du tableau. on favorise le premier élément entré soit le déplacement vers le haut, puis vers la gauche, puis la droite, puis le bas
            }
        }
        else
        {
            tab[i][j]=8; //si on ne peut plus visiter on fout la case à 8, valeur arbitraire >0 et neutre
            if (ichem>3)// si on est bloqué, on remonte la file
            {
                ichem--;
                j=chem[ichem-=2];
                i=chem[--ichem];
                deplacement[--i_depl] =-1; //ON PENSE AU NOUVEAU TABLEAU DE DEPLACEMENTS...
            }
            else ichem=-1;
        }
        usleep(20000);

        printf("\e[1;1H\e[2J"); //effacer l'ecran
        disp(li,co,tab); //bien penser à gerer le 8 comme " " pour que l'affichage des étapes intermédiaires soit correct
    }
    if (ichem<0)
    {
        printf("Ce labyrinthe semble avoir un souci...\n");
        sleep(2);
        exit (1);
    }
    tab[i][j]=-1; // la derniere valeur est effectivement une cellule faisant partie du chemin
    deplacement[i_depl]=-1; //il s'agit de la case de sortie
    //pour restituer le tableau initial tel qu'il a été confié, on remplace toutes les valeurs à 8 par 0
    for (int a =0;a<li;a++)
        for(int b=0;b<co;b++)
            if(tab[a][b]==8)
                tab[a][b]=0;
    printf("\e[1;1H\e[2J");
    printf("Un chemin a été trouvé !\n");
    disp(li,co,tab);
}

int main()
{
    int men=menu();
    int li,co;
    int ** tableau=NULL;
    while(men>0)
    {
        if(men==1) //cas 1 - générer
        {
            printf("nombre de ligne");
            scanf("%d", &li);
            printf("nombre de colonnes");
            scanf("%d", &co);
            printf("%d lignes %d col \n\n",li,co);
            tableau=generer(li,co);
            printf ("\e[1;1H\e[2J");
            printf ("Voici le labyrinthe généré...\n");
            disp(li,co,tableau); // appel de la fonction, permettant l'afichage du tableau
            printf ("sauvearder ? 1 - oui, 0 - non, 2 - Regenerer\n");
            int rep;
            scanf("%d",&rep);
            if(rep==1)
                save_laby(li,co,tableau);
            if(rep!=2)
                men=3;
        }
        if(men==2)    //cas 2 charger labyrinthe
        {
            tableau=load_laby(&li,&co);
            printf("Votre labyrinthe de %dlignes par %d colonnes est chargé chargement ...\n",li,co);
            printf("\nVoici votre labyrinthe :\n");
            disp(li,co,tableau);
            men=3;
        }
        if (men==3)    //cas 3 résoudre laby
        {
            printf ("Résolution  du labyrinthe...\n");
            int etat[li*co]; //tableau pour stocker les deplacements
            int regle=0;
            printf("Règles de transitions : 0 : Rapide - 1 : En profondeur");
            scanf("%d", &regle);
            sortir2(li,co,tableau,etat,regle);
            printf("déplacements : ");
            int var2=0,var3=0,var4=0,var5=0;
            for (int i=0;etat[i]!=-1;i++)
            {
                printf("%d ",etat[i]);
                switch (etat[i])
                {
                    case 2:
                        var2++;break;
                    case 3:
                        var3++;break;
                    case 4:
                        var4++;break;
                    case 5:
                        var5++;break;
                }
            }
            printf("-1\n");
            printf("Soient :\n");
            printf("\tvers le bas : %d déplacements\n",var5);
            printf("\tvers la droite : %d déplacements\n",var3);
            printf("\tvers le haut : %d déplacements\n",var4);
            printf("\tvers la gauche : %d déplacements\n",var2);
            printf("pour un total de : %d déplacements (hors sortie)\n",var2+var3+var4+var5);

            liberer(li,tableau);
            men=menu();
        }
    }
    //menu=5
    return 0;
}
