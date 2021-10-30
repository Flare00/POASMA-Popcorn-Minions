#ifndef STATE_ENUM_H
#define STATE_ENUM_H

enum StateEnum{
	empty,
	wall,
	flame,
	minion,
	exitDoor,
	popCorn
};

enum SubStateEnum{
	empty,
	wallWood,
	pompier,
	pyroman
}

bool isSubstateOf(StateEnum state, SubStateEnum subState){
	bool result = false;
	switch(state){
		case empty :
		case exitDoor :
		case popCorn :
		case flame :
			if(subState == SubStateEnum.empty){
				result = true;
			}
			break;
		case wall :
			if(subState == SubStateEnum.empty || subState == SubStateEnum.wallWood){
				result = true;
			}
			break;
		case minion :
			if(subState == SubStateEnum.empty || subState == SubStateEnum.pompier|| subState == SubStateEnum.pyroman){
				result = true;
			}
			break;

	}
	return result;
}

#endif
