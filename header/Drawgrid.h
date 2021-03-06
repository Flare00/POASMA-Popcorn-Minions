#include "Vec3.h"
#include "Camera.h"
#include "batiment.h"
#include "PerlinNoise.h"
#include "minion.h"
#include "Simulation.h"

#define NOTHING 0
#define WALL 1
#define MINION 2
#define FIRE 3
#define EXIT 4

#define NB_TYPES 5

#define PI 3.1415926535897932384626433
#define TWO_PI 6.283185307179586

int** initGrid(int width, int height){
	int ** grid = new int*[width];

	for (int x = 0; x < width; ++x)
	{
		grid[x] = new int[height];

		for (int y = 0; y < height; ++y)
		{
			grid[x][y] = rand()%NB_TYPES;
		}
	}
	return grid;
}

void drawQuad(float x1, float y1,float x2, float y2,int zindex){
	glVertex3f(x2,y2,zindex*-0.005);
    glVertex3f(x1,y2,zindex*-0.005);
    glVertex3f(x1,y1,zindex*-0.005);
    glVertex3f(x2,y1,zindex*-0.005);
}

void drawWoodWall(float x, float y,float tilesize,int zindex){
	glColor3f(0.34, 0.16, 0.0);
	glBegin(GL_QUADS);

	drawQuad(x,
	 y,
	 x+tilesize,
	 y+tilesize,1);
	glEnd();
}
void drawWall(float x, float y,float tilesize,int zindex){
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);

	drawQuad(x,
	 y,
	 x+tilesize,
	 y+tilesize,1);
	glEnd();
}
void drawFire(float x, float y,float tilesize,int zindex){
	glColor3f(1.,0.,0.);

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x+tilesize/2,y+tilesize/2,zindex*-0.001);
	for (int i = 0 ; i <= 20 ; i += 1){
		double ang = i*(1.0/20)*TWO_PI;
		double rad = (i%2==0) ? tilesize/2 : tilesize/4;
	    glVertex3f(x+tilesize/2+rad*cos(ang),y+tilesize/2+rad*sin(ang),zindex*-0.001);
	}
	glEnd();
}
void drawMinion(float x, float y,float tilesize,int zindex){
	glColor3f(1.,1.,0.);

	glBegin(GL_POLYGON);
	for (double angle = 0 ; angle < TWO_PI ; angle += PI/8){
	    glVertex3f(x+tilesize/2+tilesize/2*cos(angle),y+tilesize/2+tilesize/2*sin(angle),zindex*-0.001);
	}
	glEnd();

	glColor3f(0.,0.,0.);
	glBegin(GL_LINES);
	for (double angle = 0 ; angle < TWO_PI ; angle += PI/4){
	    glVertex3f(x+tilesize/2,y+tilesize/2,(zindex-1)*-0.001);
	    glVertex3f(x+tilesize/2+tilesize/4*cos(angle),y+tilesize/2+tilesize/4*sin(angle),(zindex-1)*-0.001);
	}
	glEnd();

}
void drawPanikedMinion(float x, float y,float tilesize,int zindex){
	glColor3f(0.4,0.4,1.);

	glBegin(GL_POLYGON);
	for (double angle = 0 ; angle < TWO_PI ; angle += PI/8){
	    glVertex3f(x+tilesize/2+tilesize/2*cos(angle),y+tilesize/2+tilesize/2*sin(angle),zindex*-0.001);
	}
	glEnd();

	glColor3f(0.,0.,0.);
	glBegin(GL_LINES);
	for (double angle = 0 ; angle < TWO_PI ; angle += PI/4){
	    glVertex3f(x+tilesize/2,y+tilesize/2,(zindex-1)*-0.001);
	    glVertex3f(x+tilesize/2+tilesize/4*cos(angle),y+tilesize/2+tilesize/4*sin(angle),(zindex-1)*-0.001);
	}
	glEnd();
	

}
void drawPompier(float x, float y,float tilesize,int zindex){
	glColor3f(0.1f, 0.1f, 0.5f);

	glBegin(GL_POLYGON);
	for (double angle = 0 ; angle < TWO_PI ; angle += PI/8){
	    glVertex3f(x+tilesize/2+tilesize/2*cos(angle),y+tilesize/2+tilesize/2*sin(angle),zindex*-0.001);
	}
	glEnd();
	glLineWidth(3.0);
	glColor3f(1.,1.,0.2);
	glBegin(GL_LINES);
	for (double angle = 0 ; angle < TWO_PI ; angle += PI/4){
	    glVertex3f(x+tilesize/2,y+tilesize/2,(zindex-1)*-0.001);
	    glVertex3f(x+tilesize/2+tilesize/4*cos(angle),y+tilesize/2+tilesize/4*sin(angle),(zindex-1)*-0.001);
	}
	glEnd();
	glLineWidth(1.0);
	

}
void drawPyroman(float x, float y,float tilesize,int zindex){
	glColor3f(2.0f, 0.5f, 1.0f);//Violet

	glBegin(GL_POLYGON);
	for (double angle = 0 ; angle < TWO_PI ; angle += PI/8){
	    glVertex3f(x+tilesize/2+tilesize/2*cos(angle),y+tilesize/2+tilesize/2*sin(angle),zindex*-0.001);
	}
	glEnd();

	glColor3f(0.,0.,0.);
	glBegin(GL_LINES);
	for (double angle = 0 ; angle < TWO_PI ; angle += PI/4){
	    glVertex3f(x+tilesize/2,y+tilesize/2,(zindex-1)*-0.001);
	    glVertex3f(x+tilesize/2+tilesize/4*cos(angle),y+tilesize/2+tilesize/4*sin(angle),(zindex-1)*-0.001);
	}
	glEnd();
	

}
void drawEntrance(float x, float y,float tilesize,int zindex){
	glColor3f(0.0,0.0,0.5);
	glBegin(GL_QUADS);

	drawQuad(x,
	 y,
	 x+tilesize,
	 y+tilesize,1);
	glEnd();
}
void drawExit(float x, float y,float tilesize,int zindex){
	glColor3f(0.1,1,0.05);
	glBegin(GL_QUADS);

	drawQuad(x,
	 y,
	 x+tilesize,
	 y+tilesize,1);
	glEnd();
}
void drawAStarVisited(float x, float y,float tilesize,int zindex){
	glColor3f(1.,0.1,0.05);
	glBegin(GL_QUADS);

	drawQuad(x,
	 y,
	 x+tilesize,
	 y+tilesize,1);
	glEnd();
}
void drawAStarVisited2(float x, float y,float tilesize,int zindex){
	glColor3f(0.05,0.1,1.);
	glColor3f(0.7,0.7,0.9);
	glBegin(GL_QUADS);

	drawQuad(x,
	 y,
	 x+tilesize,
	 y+tilesize,zindex);
	glEnd();
}
void drawPopcorn(float x, float y,float tilesize,int zindex){
	PerlinNoise pn;



	double rad = tilesize/2;

	glColor3f(1.,1.,1.);
	glBegin(GL_POLYGON);
	glVertex3f(x+tilesize/2,y+tilesize/2,zindex*-0.001);
	int pas = 100;
	for (int i = 0 ; i <= pas ; i += 1){
		double ang = i*(1.0/pas)*TWO_PI;
		double rad = pn.noise(cos(ang)+10*x, sin(ang)+10*y,x*20+y)*(tilesize);

	    glVertex3f(x+tilesize/2+rad*cos(ang),y+tilesize/2+rad*sin(ang),zindex*-0.001);
	}
	glEnd();


	glColor3f(0.3,0.3,0.3);
	glBegin(GL_LINE_STRIP);
	for (int i = 0 ; i <= pas ; i += 1){
		double ang = i*(1.0/pas)*TWO_PI;
		double rad = pn.noise(cos(ang)+10*x, sin(ang)+10*y,x*20+y)*(tilesize);

	    glVertex3f(x+tilesize/2+rad*cos(ang),y+tilesize/2+rad*sin(ang),(zindex-1)*-0.001);
	}
	glEnd();

}

void drawGrid(Simulation* s){


	vector<Etage*> etages = s->getBatiment()->getEtages();
	//cout << "W : Wall | w : Wood Wall | F : fire | p : pomier | P : pyromane | E : Entree | S : Sortie | C : PopCorn | X : erreur" << endl << endl;
	for (int i = 0, max = etages.size(); i < max; i++) {
		Etage* e = etages[i];

		int width = e->getWidth();
		int height = e->getHeight();
		float tilesize = 2.0 /(std::max(width,height));
		float gridWidth = tilesize * width;
		float gridHeight = tilesize * height;


		Vec3 backgound(0.7,0.7,0.7);
		


		///// le fond de la grille
		glColor3f(backgound[0],backgound[1],backgound[2]);
		glBegin(GL_QUADS);
		drawQuad(-gridWidth/2, -gridHeight/2,gridHeight/2,gridHeight/2,2);
		glEnd();

		////les carreaux

		glColor3f(0.9,0.9,0.9);
		glBegin(GL_LINES);
		for (int x = 0; x <= width; ++x){
			glVertex3f(-gridWidth/2 + x*tilesize,-gridHeight/2,0);
			glVertex3f(-gridWidth/2 + x*tilesize, gridHeight/2,0);
		}
		for (int y = 0; y <= height; ++y){
			glVertex3f(-gridWidth/2,-gridHeight/2 + y*tilesize,0);
			glVertex3f( gridWidth/2,-gridHeight/2 + y*tilesize,0);
		}

		glEnd();


	///////////////////////////new///////////////////////////

	
		for (int x = 0; x < 10; x++) {
			string ligne = "";

			for (int y = 0; y < 10; y++) {
				float xpos = -gridWidth/2 + x*tilesize;
				float ypos = -gridHeight/2 + y*tilesize;


				Case* c = e->getCase(x, y);
				switch (c->getState()) {
				case StateEnum::empty:
					ligne += "   ";
					break;
				case StateEnum::wall:
					if (isSubstateOf(c->getState(), c->getSubState())) {
						if (c->getSubState() == SubStateEnum::wallWood) {
							drawWoodWall(xpos,ypos,tilesize,2);
						}
						else {
							drawWall(xpos,ypos,tilesize,2);
						}
					}
					else {						
					}
					break;
				case StateEnum::flame:					
					drawFire(xpos,ypos,tilesize,2);
					break;
				case StateEnum::minion:
					if (isSubstateOf(c->getState(), c->getSubState())) {
						if (c->getSubState() == SubStateEnum::pompier) {							
							drawPompier(xpos,ypos,tilesize,2);
						}
						else if (c->getSubState() == SubStateEnum::pyroman) {							
							drawPyroman(xpos,ypos,tilesize,2);
						}
						else {
							drawMinion(xpos,ypos,tilesize,2);
							//drawPanikedMinion(xpos,ypos,tilesize,2); todo
						}
					}
					else {						
					}
					break;
				case StateEnum::enterDoor:					
					drawEntrance(xpos,ypos,tilesize,2);//c'est l'entree attention
					break;
				case StateEnum::exitDoor:					
					drawExit(xpos,ypos,tilesize,2);

					break;
				case StateEnum::popCorn:					
					drawPopcorn(xpos,ypos,tilesize,2);
					break;
				}
			}			
		}		
	}
}



