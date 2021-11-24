#include "stateEnum.h"
#include "importOBJ.h"

struct Models{
    objModelInfo* empty;
    objModelInfo* wall;
    objModelInfo* wallWood;
    objModelInfo* flame;
    objModelInfo* minion;
    objModelInfo* pompier;
    objModelInfo* pyroman;
    objModelInfo* exitDoor;
    objModelInfo* popCorn;

    objModelInfo* getModel(StateEnum type){
        switch ( type )
            {
                case StateEnum::wall:
                    return(wall);
                    break;
                case StateEnum::minion:
                    return(minion);
                    break;
                case StateEnum::flame:
                    return(flame);
                    break;
                case StateEnum::exitDoor:
                    return(exitDoor);
                    break;
                case StateEnum::popCorn:
                    return(popCorn);
                    break;
                case StateEnum::pyroman:
                    return(pyroman);
                    break;
                case StateEnum::pompier:
                    return(pompier);
                    break;
            }
    }
};