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
	glVertex3f(x2,y2,zindex*-0.001);
    glVertex3f(x1,y2,zindex*-0.001);
    glVertex3f(x1,y1,zindex*-0.001);
    glVertex3f(x2,y1,zindex*-0.001);
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
	glBegin(GL_QUADS);

	drawQuad(x+tilesize/4,
	y+tilesize/4,
	x+tilesize/4*3,
	y+tilesize/4*3,1);
	glEnd();
}
void drawMinion(float x, float y,float tilesize,int zindex){
	glColor3f(1.,1.,0.);
	glBegin(GL_QUADS);

	glVertex3f(x+tilesize/4,y+tilesize/4,zindex*-0.001);
    glVertex3f(x+tilesize/4*3,y+tilesize/4,zindex*-0.001);
    glVertex3f(x+tilesize/4*3,y+tilesize/4*3,zindex*-0.001);
    glVertex3f(x+tilesize/4,y+tilesize/4*3,zindex*-0.001);

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

void drawGrid(int** grid, int width, int height){

	float tilesize = 2.0 /(std::max(width,height));
	//std::cout<<tilesize<<std::endl;

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


    for (int x = 0; x < width; ++x){
		for (int y = 0; y < height; ++y){
			float xpos = -gridWidth/2 + x*tilesize;
			float ypos = -gridHeight/2 + y*tilesize;


			//std::cout<<"x="<<x<<" y="<<y<<std::endl;

			int type = grid[x][y];

			switch ( type )
			{
				case WALL:
					drawWall(xpos,ypos,tilesize,1);
					break;
				case MINION:
					drawMinion(xpos,ypos,tilesize,1);
					break;
				case FIRE:
					drawFire(xpos,ypos,tilesize,1);
					break;
				case EXIT:
					drawExit(xpos,ypos,tilesize,1);
					break;
					
			}

		}
	}
	
}



