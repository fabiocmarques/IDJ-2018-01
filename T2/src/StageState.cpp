//
// Created by fabio on 15/03/18.
//


#include <CameraFollower.h>
#include <TileMap.h>
#include <Alien.h>
#include <PenguinBody.h>
#include "StageState.h"


StageState::StageState() : State() {
    shared_ptr<GameObject> go(new GameObject());
    Sprite *spr = new Sprite(*go, "assets/img/ocean.jpg");

    go->AddComponent(new CameraFollower(*go));
    go->AddComponent(spr);
    go->box.x = 0;
    go->box.y = 0;
    go->box.h = spr->GetHeight();
    go->box.w = spr->GetWidth();

    objectArray.emplace_back(go);


    shared_ptr<GameObject> go2(new GameObject());
    TileSet *ts = new TileSet(TILE_WIDTH, TILE_HEIGHT, "assets/img/tileset.png");
    TileMap *map = new TileMap(*go2, "assets/map/tileMap.txt", ts);


    go2->AddComponent(map);
    go2->box.x = 0;
    go2->box.y = 0;

    objectArray.emplace_back(go2);

    shared_ptr<GameObject> go3(new GameObject());
    go3->box.x += 512;
    go3->box.y += 300;
    Alien *a = new Alien(*go3, 6);
    go3->AddComponent(a);
    //go3->AddComponent(new CameraFollower(*go3, true));

    objectArray.emplace_back(go3);


    shared_ptr<GameObject> go4(new GameObject());
    go4->box.x += 704;
    go4->box.y += 640;
    PenguinBody *body = new PenguinBody(*go4);
    go4->AddComponent(body);
    //go3->AddComponent(new CameraFollower(*go3, true));

    Camera::Follow(go4.get());
    objectArray.emplace_back(go4);


    LoadAssets();
    quitRequested = false;
    backgroundMusic.Play();
    
    //Start();
}

StageState::~StageState() {
    
}

void StageState::LoadAssets() {
    backgroundMusic.Open("assets/audio/stageState.ogg");
}

void StageState::Update(float dt) {
    if(!started){
        Start();
    }
    
    InputManager IM = InputManager::GetInstance();
    vector<int> colliderIndexes;

    if (IM.IsKeyDown(ESCAPE_KEY) || IM.QuitRequested()) {
        quitRequested = true;
    }

    Camera::Update(dt);

    if (IM.KeyPress(SDLK_SPACE)) {
        Vec2 objPos =
                Vec2(200, 0).GetRotated(-M_PI + M_PI * (rand() % 1001) / 500.0) + Vec2(IM.GetMouseX(), IM.GetMouseY());
        AddObject(objPos.x + Camera::pos.x, objPos.y + Camera::pos.y);
    }

    for (int i = 0; i < (int) objectArray.size(); ++i) {
        objectArray[i]->Update(dt);

        Collider *col = (Collider *) objectArray[i]->GetComponent("Collider");

        if (col != nullptr) {
            colliderIndexes.emplace_back(i);
        }
    }


    for (int i = 0; i < (colliderIndexes.size() - 1); ++i) {
        Collider *col = (Collider *) objectArray[colliderIndexes[i]]->GetComponent("Collider");
        if (col == nullptr) {
            cout << "Wrong collider index." << endl;
            exit(1);
        }

        for (int j = i + 1; j < colliderIndexes.size(); ++j) {
            Collider *intCol = (Collider *) objectArray[colliderIndexes[j]]->GetComponent("Collider");

            if (intCol == nullptr) {
                cout << "Wrong internal loop collider index." << endl;
                exit(1);
            }

            bool colision = Collision::IsColliding(col->box, intCol->box,
                                                   (float) (objectArray[colliderIndexes[i]]->angleDeg * PI / 180),
                                                   (float) (objectArray[colliderIndexes[j]]->angleDeg * PI / 180));

            if (colision) {
                //cout << "Colides. i: " << i << " j: " << j <<  endl;
                objectArray[colliderIndexes[i]]->NotifyCollision(*(objectArray[colliderIndexes[j]].get()));
                objectArray[colliderIndexes[j]]->NotifyCollision(*(objectArray[colliderIndexes[i]].get()));
            }
        }
    }

    colliderIndexes.clear();

    for (int i = 0; i < (int) objectArray.size(); ++i) {
        if (objectArray[i]->IsDead()) {

            objectArray.erase(objectArray.begin() + i);

        }
    }
}

void StageState::Render() {
    State::RenderArray();
}

void StageState::Start() {
   State::Start();
}

void StageState::Pause() {

}

void StageState::Resume() {

}
