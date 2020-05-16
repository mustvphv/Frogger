#include "game.h"
#include "driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define H 21
#define W 32

Game g;
Game gmenu;

static char level1[672] =
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
    "FAAAFFFFAAAFFFFAAFFFFAAAFFFFAAAF"
    "FAAAFFFFAAAFFFFAAFFFFAAAFFFFAAAF"
    "EEEEEEEEHHHHEEEEEEEEEEEEEEHHHHEE"
    "kkkkEEEEkkkkEEkkkkEEEEEkkkkEEEEE"
    "HHHHEEEEEEEEHHHHEEEEEEEEEEHHHHEE"
    "EEEEEEkkkkEEEEEEEEEEEEkkkkEEEEEE"
    "EEEEEEEEEEEEEEEEEEEEEEEEEEEEHHHH"
    "BBBBBBBBBBBBBBGBBBBBBBBBBBBBBBBB"
    "AAAAAAAAAAAAAAAAACAAAAAAAAAAAAAA"
    "AAAAAACAAAAAAAAAAAAAAAAAAAAAACAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAC"
    "DDAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

static char level2[672] =
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

static Entity entity[1];

static int dirx[] = {0, -1, 1, 0, 0 };
static int diry[] = {0, 0, 0, -1, 1 };

static int frogwin200_1=0;
static int frogwin200_2=0;
static int frogwin200_3=0;
static int frogwin200_4=0;
static int frogwin200_5=0;

int stop=0;

int VAR_musique=0;

static int score=0;

static int ScoreNiveauPrecedent=0;

static int niveau=1;

static int mort2frogger=0;

static int PeutReinit=0;

static unsigned char bg[H * W];
static unsigned char bgmenu[H * W];

static void remet_en_place(){
    if(frogwin200_1 == 1){
                    bg[97] = 18;
		    bg[98] = 19;
		    bg[99] = 20;
    }
    if(frogwin200_2 == 1){
                    bg[104] = 18;
		    bg[105] = 19;
		    bg[106] = 20;
    }
    if(frogwin200_3 == 1){
                    bg[111] = 18;
		    bg[112] = 19;
    }
    if(frogwin200_4 == 1){
                    bg[117] = 18;
		    bg[118] = 19;
		    bg[119] = 20;
    }
    if(frogwin200_5 == 1){
                    bg[124] = 18;
		    bg[125] = 19;
		    bg[126] = 20;
    }
}

static int salut[] = {1,10,20,6,2}, normal = 1,cases1[] = {1,1,1},cases2[] = {1,1,1};

//fonction faite par nous deux:
static void apparition1(int positiontochange,int enemy,int indice,int timetoadd){
        //partie faite par Pierre MARGALE:
	int i = positiontochange;
	salut[indice] += 1;	
	if((salut[indice] >= (50+timetoadd))){
		bg[i] = enemy;
		bg[i-1] = enemy;
		bg[i-2] = enemy;
		if(salut[indice] == (70+timetoadd)){
			salut[indice] = 1;
		}
 	}else{
        //partie faite par Mustapha Ilyès DAHMANI:
                if(frogwin200_1 == 1){
                    bg[97] = 18;
		    bg[98] = 19;
		    bg[99] = 20;
                }
                if(frogwin200_1 == 0){
                    bg[i] = 0;
		    bg[i-1] = 0;
		    bg[i-2] = 0;
                }

                if(frogwin200_2 == 1){
                    bg[104] = 18;
		    bg[105] = 19;
		    bg[106] = 20;
                }
                if(frogwin200_2 == 0){
                    bg[i] = 0;
		    bg[i-1] = 0;
		    bg[i-2] = 0;
                }

                if(frogwin200_4 == 1){
                    bg[117] = 18;
		    bg[118] = 19;
		    bg[119] = 20;
                }
                if(frogwin200_4 == 0){
                    bg[i] = 0;
		    bg[i-1] = 0;
		    bg[i-2] = 0;
                }

                if(frogwin200_5 == 1){
                    bg[124] = 18;
		    bg[125] = 19;
		    bg[126] = 20;
                }
                if(frogwin200_5 == 0){
                    bg[i] = 0;
		    bg[i-1] = 0;
		    bg[i-2] = 0;
                }
    }

}

//fonction faite par Pierre MARGALE:
static void apparition2(int positiontochange,int enemy,int indice){
	int i = positiontochange;
	
	normal += 1;
	salut[1] += 1;
	if(salut[1] >= 120){
		bg[i] = enemy;
		bg[i-1] = enemy;
		if(salut[1] == (140)){
			salut[1] = 10;
		}
	}else{
                if(frogwin200_3 == 1){
                    bg[111] = 13;
		    bg[112] = 14;
                }
                else{
                    bg[111] = 0;
		    bg[112] = 0;
                }
	}
}

//fonction faite par Pierre MARGALE:
static void changement_tortue(void){ 
	/* première ligne de tortue*/
	for(int i = 0; i<3; ++i){
		if(cases2[i] == 5){
			cases1[i] = 1;
			cases2[i] = 1;
		}
	}


	switch(bg[180]){
		case Tortue:
			if(cases1[0]<13){
				cases1[0] += 1;
				bg[180] = 43;
			}else{
				cases2[0] += 1;
				bg[180] = 55;
			}
			break;
		case Tortue2:
			if(cases1[0]<13){
				cases1[0] += 1;
				bg[180] = 56;
			}else{
				cases2[0] += 1;
				bg[180] = 55;
			}
			break;
		case Tortue3:
			if(cases1[0]<13){
				cases1[0] += 1;
				bg[180] = 42;
			}else{
				cases2[0] += 1;
				bg[180] = 55;
			}
			break;
			
		default:
			break;
	}

	switch(bg[160]){
		case Tortue:
			bg[160] = 43;
			break;
		case Tortue2:
			bg[160] = 56;
			break;
		case Tortuesouseau:
			bg[160] = 42;
			break;
		case Tortue3:
			bg[160] = 42;
			break;
		default:
			break;
	}
	switch(bg[187]){
		case Tortue:
			bg[187] = 43;
			break;
		case Tortue2:
			bg[187] = 56;
			break;
		case Tortuesouseau:
			bg[187] = 42;
			break;
		case Tortue3:
			bg[187] = 42;
			break;
		default:
			break;
	}
	switch(bg[165]){
		case Tortue:
			if(cases1[1]<13){
				cases1[1] += 1;
				bg[165] = 43;
				
			}else{
				cases2[1] += 1;
				bg[165] = 55;
			}
			break;
		case Tortue2:
			if(cases1[1]<13){
				cases1[1] += 1;
				bg[165] = 56;
			}else{
				cases2[1] += 1;
				bg[165] = 55;
			}
			break;
		case Tortuesouseau:
			if(cases1[1]<13){
				cases1[1] += 1;
				bg[165] = 12;
			}else{
				cases2[1] += 1;
				bg[165] = 55;
			}
			break;
		case Tortue3:
			if(cases1[1]<13){
				cases1[1] += 1;
				bg[165] = 42;
			}else{
				cases2[1] += 1;
				bg[165] = 55;
			}
			break;
		default:
			break;
	}
	switch(bg[170]){
		case Tortue:
			bg[170] = 43;
			break;
		case Tortue2:
			bg[170] = 56;
			break;
		case Tortuesouseau:
			bg[170] = 42;
			break;
		case Tortue3:
			bg[170] = 42;
			break;
		default:
			break;
	}
	switch(bg[175]){
		case Tortue:
			bg[175] = 43;
			break;
		case Tortue2:
			bg[175] = 56;
			break;
		case Tortuesouseau:
			bg[175] = 42;
			break;
		case Tortue3:
			bg[175] = 42;
			break;
		default:
			break;
	}

	/*seconde ligne de tortue*/
	switch(bg[224]){
		case Tortue:
			bg[224] = 43;
			break;
		case Tortue2:
			bg[224] = 56;
			break;
		case Tortue3:
			bg[224] = 42;
			break;
		default:
			break;
	}
	switch(bg[230]){
		case Tortue:
			bg[230] = 43;
			break;
		case Tortue2:
			bg[230] = 56;
			break;
		case Tortue3:
			bg[230] = 42;
			break;
		default:
			break;
	}
	switch(bg[237]){
		case Tortue:
                    if(cases1[2]<17){
                        cases1[2]+=1;
			bg[237] = 43;
                    }
                    else{
                        cases2[2]+=1;
			bg[237] = 55;
                    }
			break;
		case Tortue2:
                    if(cases1[2]<17){
                        cases1[2]+=1;
			bg[237] = 56;
                    }
                    else{
                        cases2[2]+=1;
			bg[237] = 55;
                    }
			break;
		case Tortue3:
                    if(cases1[2]<17){
                        cases1[2]+=1;
			bg[237] = 42;
                    }
                    else{
                        cases2[2]+=1;
			bg[237] = 55;
                    }
			break;
                case Tortuesouseau:
                    if(cases1[2]<17){
                        cases1[2]+=1;
			bg[237] = 43;
                    }
                    else{
                        cases2[2]+=1;
			bg[237] = 55;
                    }
			break;
		default:
			break;
	}
	switch(bg[244]){
		case Tortue:
			bg[244] = 43;
			break;
		case Tortue2:
			bg[244] = 56;
			break;
		case Tortue3:
			bg[244] = 42;
			break;
                case Tortuesouseau:
			bg[244] = 43;
			break;
		default:
			break;
	}
	switch(bg[251]){
		case Tortue:
			bg[251] = 43;
			break;
		case Tortue2:
			bg[251] = 56;
			break;
		case Tortue3:
			bg[251] = 42;
			break;
		default:
			break;
	}
}
//fonction faite par Pierre MARGALE:
static void move_tronc(void){
	if(bg[entity[0].y * W + entity[0].x] == Finbois){
		entity[0].x -= 1;
	}
/*
	if(bg[entity[0].y * W + entity[0].x] == Finbois2){
		entity[0].x += -1;
	}*/
}
//fonction faite par Pierre MARGALE:
static void move_tortue(void){
	if(bg[entity[0].y * W + entity[0].x] == Tortue || bg[entity[0].y * W +entity[0].x] == Tortue2 || bg[entity[0].y * W + entity[0].x] == Tortue3 ){
		entity[0].x += 1;
	}

}

//fonction faite par Mustapha Ilyès DAHMANI:
static void rempli_barre2progression(){
    int i;
    for(i=0;i<32;++i){
        bg[576+i]=10;
    }
}

static double duree=0;
//fonction faite par Mustapha Ilyès DAHMANI:
static int calcul_duree(){
    duree+=1;
    if(stop==1){
        duree=0;
    }
    stop=0;
    return duree;
}

static int var_w1=W-1;
static int var_w2=W-2;
//fonction faite par Mustapha Ilyès DAHMANI:
static void vide_barre2progression(int valeur1, int valeur2){
    int x;
    if((calcul_duree())>=valeur1){
        bg[576+var_w1-valeur2]=0;
        bg[576+var_w2-valeur2]=0;
    }
}
static int ib2p=0;
static int jb2p=0;
//fonction faite par Mustapha Ilyès DAHMANI:
static void barre2progression(int valeur){
    for(ib2p=valeur, jb2p=0;ib2p<32*valeur;ib2p+=valeur, jb2p+=2){
        vide_barre2progression(ib2p, jb2p);
    }
}

//fonction faite par Mustapha Ilyès DAHMANI
static void TempsFini(){
    if(bg[576]==0){
        entity[0].y = 15;
        entity[0].x = 16;
        score=ScoreNiveauPrecedent;
        PeutReinit=1;
        stop=1;
        mort2frogger=1;
    }
}
//fonction faite tous les deux
static void deplace_enemy(int position_enemy, char s){
    int tmp, tmp2, i;
        if (s == 'D'){
            for(i=position_enemy;i<(position_enemy-1)+W;++i){
                tmp = bg[i];
                bg[i]=bg[i+1];
                bg[i+1]=tmp;
            }
        }
        if (s == 'G'){
            for(i=(position_enemy-2)+W;i>=position_enemy;--i){
                tmp = bg[i];
                bg[i]=bg[i+1];
                bg[i+1]=tmp;
            }
        }
}
//fonction faite par Mustapha Ilyès DAHMANI
void Frog200Points(){
    if((entity[0].y<=3) && ( (entity[0].x>=1 && entity[0].x<=3) ) && frogwin200_1==0){
        entity[0].y = 15;
        entity[0].x = 16;
        bg[65]=15;
        bg[66]=16;
        bg[67]=17;
        bg[97]=18;
        bg[98]=19;
        bg[99]=20;
        stop=1;
        score+=200;
        frogwin200_1=1;
    }
    if((entity[0].y<=3) && ( (entity[0].x>=8 && entity[0].x<=10) ) && frogwin200_2==0){
        entity[0].y = 15;
        entity[0].x = 16;
        bg[72]=15;
        bg[73]=16;
        bg[74]=17;
        bg[104]=18;
        bg[105]=19;
        bg[106]=20;
        stop=1;
        score+=200;
        frogwin200_2=1;
    }   
    if((entity[0].y<=3) && ( (entity[0].x>=15 && entity[0].x<=16) ) && frogwin200_3==0){
        entity[0].y = 15;
        entity[0].x = 16;
        bg[79]=11;
        bg[80]=12;
        bg[111]=13;
        bg[112]=14;
        stop=1;
        score+=200;
        frogwin200_3=1;
    }
    if((entity[0].y<=3) && ( (entity[0].x>=21 && entity[0].x<=23) ) && frogwin200_4==0){
        entity[0].y = 15;
        entity[0].x = 16;
        bg[85]=15;
        bg[86]=16;
        bg[87]=17;
        bg[117]=18;
        bg[118]=19;
        bg[119]=20;
        stop=1;
        score+=200;
        frogwin200_4=1;
    }
    if((entity[0].y<=3) && ( (entity[0].x>=28 && entity[0].x<=30) ) && frogwin200_5==0){
        entity[0].y = 15;
        entity[0].x = 16;
        bg[92]=15;
        bg[93]=16;
        bg[94]=17;
        bg[124]=18;
        bg[125]=19;
        bg[126]=20;
        stop=1;
        score+=200;
        frogwin200_5=1;
    }
}
//fonction faite par Mustapha Ilyès DAHMANI
static int compte_elements(char * s){
    int nb_elements=0;
    int i;
    for(i=0;s[i]!='\0';i++){
        nb_elements++;
    }
    return nb_elements;
}

static int highscore=0;
//fonction faite par Mustapha Ilyès DAHMANI
static int TrouveHighScore(){
    if(score>highscore){
        highscore=score;
    }
    return highscore;
}

static int niveau_precedent=0;
//fonction faite par Mustapha Ilyès DAHMANI
static void afficheScore(int score_local, int position_debut, char * score_HighOuCourant, int nombre_max2chiffres){
    int score_high = score_local;
    if(niveau>niveau_precedent && mort2frogger==1 && niveau_precedent>0){
        niveau=niveau_precedent;
        score_local=ScoreNiveauPrecedent;
    }
    if(strcmp(score_HighOuCourant, "score courant") == 0){
        bg[608]=24;
        bg[609]=25;
        bg[610]=26;
        bg[611]=27;
        bg[612]=28;
        bg[613]=29;
    }

    if(strcmp(score_HighOuCourant, "high score") == 0){
        bg[630]=21;
        bg[631]=22;
        bg[632]=23;
        bg[633]=21;
        bg[634]=24;
        bg[635]=25;
        bg[636]=26;
        bg[637]=27;
        bg[638]=28;
        bg[639]=29;
        score_local=score_high;
    }

    char * score_char = malloc(100*sizeof*score_char);
    int i;
    sprintf(score_char, "%d", score_local);

    int nb_elements_score_char = compte_elements(score_char);
    int j;
    for(j=nb_elements_score_char;j<=nombre_max2chiffres;j++){
        bg[position_debut+j]=0;
    }

    for(i=0;score_char[i]!='\0';++i){
        if(score_char[i] == '0'){
            bg[position_debut+i]=30;
        }
        else if(score_char[i] == '1'){
            bg[position_debut+i]=31;
        }
        else if(score_char[i] == '2'){
            bg[position_debut+i]=32;
        }
        else if(score_char[i] == '3'){
            bg[position_debut+i]=33;
        }
        else if(score_char[i] == '4'){
            bg[position_debut+i]=34;
        }
        else if(score_char[i] == '5'){
            bg[position_debut+i]=35;
        }
        else if(score_char[i] == '6'){
            bg[position_debut+i]=36;
        }
        else if(score_char[i] == '7'){
            bg[position_debut+i]=37;
        }
        else if(score_char[i] == '8'){
            bg[position_debut+i]=38;
        }
        else if(score_char[i] == '9'){
            bg[position_debut+i]=39;
        }
    }
}

//fonction faite par Mustapha Ilyès DAHMANI
static void calcul_niveau(int position_debut, int nombre_max2chiffres){
    bg[0] = 44;
    bg[1] = 45;
    bg[2] = 46;
    bg[3] = 47;
    bg[4] = 48;
    bg[5] = 49;
    bg[6] = 0;

    char * niveau_char = malloc(100*sizeof*niveau_char);
    int i;
    sprintf(niveau_char, "%d", niveau);

    for(i=0;niveau_char[i]!='\0';++i){
        if(niveau_char[i] == '0'){
            bg[position_debut+i]=30;
        }
        else if(niveau_char[i] == '1'){
            bg[position_debut+i]=31;
        }
        else if(niveau_char[i] == '2'){
            bg[position_debut+i]=32;
        }
        else if(niveau_char[i] == '3'){
            bg[position_debut+i]=33;
        }
        else if(niveau_char[i] == '4'){
            bg[position_debut+i]=34;
        }
        else if(niveau_char[i] == '5'){
            bg[position_debut+i]=35;
        }
        else if(niveau_char[i] == '6'){
            bg[position_debut+i]=36;
        }
        else if(niveau_char[i] == '7'){
            bg[position_debut+i]=37;
        }
        else if(niveau_char[i] == '8'){
            bg[position_debut+i]=38;
        }
        else if(niveau_char[i] == '9'){
            bg[position_debut+i]=39;
        }
    }
}
//fonction faite par Mustapha Ilyès DAHMANI
static int peut_reinitialiser(){
    int pr = 0;
    if( (frogwin200_1 && frogwin200_2 && frogwin200_3 && frogwin200_4 && frogwin200_5) == 1){
        pr = 1;
        ScoreNiveauPrecedent=score;
    }
    else{
        pr = 0;
    }
    return pr;
}
//fonction faite par Mustapha Ilyès DAHMANI
static void reinitialisation(){
    if(peut_reinitialiser() == 1 || PeutReinit == 1){
        if(PeutReinit==0){
            sleep(1);
        }
        bg[65]=0;
        bg[66]=0;
        bg[67]=0;
        bg[97]=0;
        bg[98]=0;
        bg[99]=0;
        stop=1;
        frogwin200_1=0;
        bg[72]=0;
        bg[73]=0;
        bg[74]=0;
        bg[104]=0;
        bg[105]=0;
        bg[106]=0;
        stop=1;
        frogwin200_2=0;
        bg[79]=0;
        bg[80]=0;
        bg[111]=0;
        bg[112]=0;
        stop=1;
        frogwin200_3=0;
        bg[85]=0;
        bg[86]=0;
        bg[87]=0;
        bg[117]=0;
        bg[118]=0;
        bg[119]=0;
        stop=1;
        frogwin200_4=0;
        bg[92]=0;
        bg[93]=0;
        bg[94]=0;
        bg[124]=0;
        bg[125]=0;
        bg[126]=0;
        stop=1;
        frogwin200_5=0;
        if(PeutReinit == 0){
            niveau += 1;
        }
        PeutReinit=0;
    }
}

//fonction faite par Pierre MARGALE:
static void load_entity(void){
    g.entity[0].x = 16;
    g.entity[0].y = 15;
    g.entity[0].id = 0;

}

//fonction faite par Mustapha Ilyès DAHMANI:
static void difficulte_niveau(){
    if(niveau==1){
        barre2progression(500);
    }
    if(niveau>=2 && niveau <=4){
        barre2progression(400);
    }
    if(niveau>=5 && niveau <=6){
        barre2progression(300);
    }
    if(niveau>=6 && niveau <=8){
        barre2progression(200);
    }
    if(niveau>=9){
        barre2progression(100);
    }
}

//fonction faite tous les deux
static void process_move(int move) {
    

    entity[0].dir = move;
    int mamax = 0;
    int mamay = 5;
    int nextx = entity[0].x + dirx[move];
    int nexty = entity[0].y + diry[move];
    entity[0].dir = move;
    int tab_endroits_interdits[11]={Gazon, FrogGagnant1Petit, FrogGagnant2Petit, FrogGagnant3Petit, FrogGagnant4Petit, FrogGagnant1Grand, FrogGagnant2Grand, FrogGagnant3Grand, FrogGagnant4Grand, FrogGagnant5Grand, FrogGagnant6Grand};
    int i;
    for(i=0;i<11;++i){
        if(nextx < 0 || nextx >= W || nexty < 0 || nexty >= H || bg[nexty * W + nextx]==tab_endroits_interdits[i]){
	    return;
        }
	
    }
    entity[0].x = nextx;
    entity[0].y = nexty;
}
//fonction faite par nous deux
static void auto_move(void){
	    if(bg[entity[0].y * W + entity[0].x] == Cars || bg[entity[0].y * W + entity[0].x] == Camion || bg[entity[0].y * W + entity[0].x]==Fleur || bg[entity[0].y * W  + entity[0].x] == Croco || bg[entity[0].y * W + entity[0].x] == Water || bg[entity[0].y * W + entity[0].x] == Serpent || bg[entity[0].y * W + entity[0].x] == Tortuesouseau){
		    entity[0].y = 15;
	   	    entity[0].x = 16;
                    stop=1;
                    score=ScoreNiveauPrecedent;
                    mort2frogger=1;
                    PeutReinit=1;
	    }
            if(entity[0].x == W || entity[0].x == -1){
		    entity[0].y = 15;
		    entity[0].x = 16;
	    }
}

//fonction faite par Mustapha Ilyès DAHMANI
static void cree_texte_menu(int position){
    bgmenu[position+1]=52;
    bgmenu[position+2]=27;
    bgmenu[position+3]=26;
    bgmenu[position+4]=23;
    bgmenu[position+5]=23;
    bgmenu[position+6]=28;
    bgmenu[position+7]=27;
}

//fonction faite par Mustapha Ilyès DAHMANI
static void cree_bouton_menu(int position){
    bgmenu[position]=48;
    bgmenu[position+1]=53;
    bgmenu[position+2]=53;
    bgmenu[position+3]=49;
    bgmenu[position+4]=54;
    bgmenu[position+5]=28;
    bgmenu[position+6]=51;
    bgmenu[position+8]=24;
    bgmenu[position+9]=49;
    bgmenu[position+10]=27;
    bgmenu[position+12]=28;
    bgmenu[position+13]=24;
    bgmenu[position+14]=53;
    bgmenu[position+15]=48;
    bgmenu[position+16]=25;
    bgmenu[position+17]=28;
    bgmenu[position+34]=53;
    bgmenu[position+35]=26;
    bgmenu[position+36]=49;
    bgmenu[position+37]=27;
    bgmenu[position+40]=50;
    bgmenu[position+41]=26;
    bgmenu[position+42]=49;
    bgmenu[position+43]=28;
    bgmenu[position+44]=51;
}

static int allume_jeu=0;

//fonction faite tous les deux
static void callback(void* d) {
    const Driver* dr = (Driver*)d;
    int move = dr->get_move();
    afficheScore(score,640, "score courant",6);
    afficheScore(TrouveHighScore(),662, "high score",6);
    calcul_niveau(7,6);
    Frog200Points();
    rempli_barre2progression();
    difficulte_niveau();
    TempsFini();
    reinitialisation();
    apparition1(99,40,0,41);
    apparition2(112,40,2);
    apparition1(106,41,1,16);
    apparition1(119,41,3,36);
    apparition1(126,40,4,50);   
    changement_tortue();
    move_tronc();
    move_tortue();
    deplace_enemy(160, 'G');
    deplace_enemy(224, 'G');
    deplace_enemy(288, 'D');
    deplace_enemy(320, 'D');
    deplace_enemy(352, 'D');
    deplace_enemy(384, 'D');
    deplace_enemy(416, 'G');
    deplace_enemy(128, 'D');
    deplace_enemy(192, 'D');
    deplace_enemy(256, 'D');
    process_move(move);
    auto_move();
    dr->draw_bg();
    dr->draw_entity(0);
    dr->update();
    remet_en_place();
}

static int deja_fait=1;
//fonction faite par Mustapha Ilyès DAHMANI
static void callback_menu(void* d) {
    const Driver* dr = (Driver*)d;
    int move = dr->touche_bouton();
    if(dr->touche_bouton() == 1){
        allume_jeu=1;
        if(deja_fait == 0){
            deja_fait=1;
        }
        init_game(dr);
    }

    cree_texte_menu(11);
    cree_bouton_menu(327);

    dr->draw_bg_menu();
    dr->update();
}

static int continuer = 1;

//fonction faite par tous les deux
void init_game(const Driver* dr) {
    int i;
    g.h = H;
    g.w = W;
    g.background = bg;
    g.entity = entity;
    gmenu.h = H;
    gmenu.w = W;
    gmenu.background = bgmenu;
    gmenu.entity = entity;
    for(int i = 0; i < H * W; ++i){
        g.background[i] = level1[i] - 'A';
        gmenu.background[i] = level2[i] - 'A';
    }
    if(allume_jeu==1){
        load_entity();
        dr->init(&g);
        dr->start(callback);
        
    }
    else{
        dr->init(&gmenu);
        dr->menu(callback_menu);
    }
}


