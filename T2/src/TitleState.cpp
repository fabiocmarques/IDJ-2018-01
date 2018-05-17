//
// Created by fabio on 16/05/18.
//

#include <TitleState.h>
#include <State.h>
#include <Sprite.h>
#include <CameraFollower.h>
#include <StageState.h>
#include <Text.h>

TitleState::TitleState() : State() {
    shared_ptr<GameObject> go(new GameObject());
    Sprite *spr = new Sprite(*go, "assets/img/title.jpg");

    go->AddComponent(new CameraFollower(*go));
    go->AddComponent(spr);
    go->box.x = 0;
    go->box.y = 0;
    go->box.h = spr->GetHeight();
    go->box.w = spr->GetWidth();

    objectArray.emplace_back(go);

    shared_ptr<GameObject> go2(new GameObject());
    go2->box.x = 400;
    go2->box.y = 400;
    Text* txt = new Text(*go, "./assets/font/CallMeMaybe.ttf", 12, Text::SOLID, "Press SPACE to start!", {255, 0, 0, 255});
    go->AddComponent(txt);

    objectArray.emplace_back(go2);
}

TitleState::~TitleState() {

}

void TitleState::LoadAssets() {

}

void TitleState::Update(float dt) {
    if(!started){
        Start();
    }

    InputManager IM = InputManager::GetInstance();

    if (IM.IsKeyDown(ESCAPE_KEY) || IM.QuitRequested()) {
        quitRequested = true;
        return;
    }
    
    if (IM.KeyPress(SDLK_SPACE)) {
        StageState* stst = new StageState();
        Game::GetInstance().Push(stst);
    }

}

void TitleState::Render() {
    State::RenderArray();
}

void TitleState::Start() {
    State::Start();
}

void TitleState::Pause() {

}

void TitleState::Resume() {

}
