//
// Created by fabio on 17/05/18.
//

#include <Sprite.h>
#include <GameData.h>
#include <CameraFollower.h>
#include <Text.h>
#include "EndState.h"

void EndState::LoadAssets(string path) {
    if (path.size() > 0) {
        backgroundMusic.Open(path);
    }
}

void EndState::Update(float dt) {
    if (!started) {
        Start();
    }

    InputManager IM = InputManager::GetInstance();

    if (IM.IsKeyDown(ESCAPE_KEY) || IM.QuitRequested()) {
        quitRequested = true;
        return;
    }

    if (IM.KeyPress(SDLK_SPACE)) {
        Game::GetInstance().Push("StageState");
        return;
    }

    State::UpdateArray(dt);
}

void EndState::Render() {
    State::RenderArray();
}

void EndState::Start() {
    State::StartArray();
    started = true;
}

void EndState::Pause() {

}

void EndState::Resume() {

}

EndState::EndState() {
    string imagePath = "";
    string audioPath = "";

    if (GameData::playerVictory) {
        imagePath = "./assets/img/win.jpg";
        audioPath = "./assets/audio/endStateWin.ogg";
    } else {
        imagePath = "./assets/img/lose.jpg";
        audioPath = "./assets/audio/endStateLose.ogg";
    }

    shared_ptr<GameObject> go(new GameObject());
    Sprite *spr = new Sprite(*go, imagePath);

    go->AddComponent(new CameraFollower(*go));
    go->AddComponent(spr);
    go->box.x = 0;
    go->box.y = 0;
    go->box.h = spr->GetHeight();
    go->box.w = spr->GetWidth();

    objectArray.emplace_back(go);

    shared_ptr<GameObject> go2(new GameObject());
    go2->box.x = 0;
    go2->box.y = 0;
    Text *txt = new Text(*go2, "./assets/font/CallMeMaybe.ttf", 28, Text::BLENDED,
                         "Press SPACE to restart or ESC to leave!", {255, 0, 0, 255}, 0, 100);
    go2->AddComponent(txt);

    objectArray.emplace_back(go2);

    LoadAssets(audioPath);
    backgroundMusic.Play();

}

EndState::~EndState() {

}

void EndState::LoadAssets() {

}
