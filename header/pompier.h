#ifndef PYROMANE_H
#define PYROMANE_H

class Pompier: public Minion{
	//protected:

	public:
		Pompier();
		void ettientFeu();
		virtual void action(Batiment* batiment);//car elle est défini
};
#endif