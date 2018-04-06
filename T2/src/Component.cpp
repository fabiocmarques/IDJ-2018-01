//
// Created by fabio on 18/03/18.
//

#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject &associated) : associated(associated) {

}

Component::~Component() {

}

void Component::Start() {

}
