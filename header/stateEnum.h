#ifndef STATE_ENUM_H
#define STATE_ENUM_H

enum StateEnum {
	empty,
	wall,
	flame,
	minion,
	enterDoor,
	exitDoor,
	popCorn
};

enum SubStateEnum {
	subEmpty,
	wallWood,
	pompier,
	pyroman
};

static bool isSubstateOf(StateEnum state, SubStateEnum subState) {
	bool result = false;
	switch(state){
	case StateEnum::empty :
		case StateEnum::exitDoor :
		case StateEnum::popCorn :
		case StateEnum::flame :
			if(subState == SubStateEnum::subEmpty){
				result = true;
			}
			break;
		case StateEnum::wall :
			if(subState == SubStateEnum::subEmpty || subState == SubStateEnum::wallWood){
				result = true;
			}
			break;
		case StateEnum::minion :
			if(subState == SubStateEnum::subEmpty || subState == SubStateEnum::pompier|| subState == SubStateEnum::pyroman){
				result = true;
			}
			break;

	}
	return result;
}

#endif
