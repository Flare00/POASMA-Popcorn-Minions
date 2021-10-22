#ifndef PYROMANE_H
#define PYROMANE_H

class Pyromane: public Minion{
	//protected:
	public:
		Pyromane();
		void emetFeu();
		virtual void action(Batiment* batiment);
};
#endif