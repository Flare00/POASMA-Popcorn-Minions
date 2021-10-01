class Batiment
{
private:
	int width;
	int height;

	Case** grid;

public:
	grid(int x, int y);
	~grid();

	bool fire(int x, int y);    //is there fire in (x,y)
	void getExits(int* tab, int* n); //fill the tab "tab" and set n to the number of exit


	bool flamable(x,y);
	Case* getCase(int x, int y);
	Case** getGrid();

};