# BlobLabirynth
A simple opengl exploration game

## Build and run

Configure once, then build and run from the project root:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./game.out
```
## Architecture

```
labyrinth.cpp  main()
   │  GLUT callbacks: display / idle / keyboard / close
   ▼
┌───────────────────────────────────────────────┐
│ Game                                          │
│   CreateShaders() ──► LoadShaders(.vert/.frag)│
│   CreateObjects() ──► SOIL(assets/blob.png)   │
│   update()  ──► object->update(game)          │
│   render()  ──► object->render(matrix, proj)  │
│   KeyDown() / KeyUp() ──► keystates           │
│   gridToScreenPosition()                      │
│   screenCollision() / collisionDetection()    │
│                                               │
│   owns: Mesh                                  │
│   owns: vector<unique_ptr<Object>> objects    │
└───────────────────────────────────────────────┘
                       │
                       ▼
┌───────────────────────────────────────────────┐
│ Object                                        │
│   position, size, angle, texture, mesh*       │
│   update(game)   (virtual)                    │
│   render(...)    ──► mesh->draw()             │
└───────────────────────────────────────────────┘
          ▲                         ▲
          │ inherits                │ instance
┌─────────────────────────┐   ┌──────────────┐
│ Player                  │   │ Wall         │
│   gridPosition, facing  │   │ (Object)     │
│   handleMovement()      │   └──────────────┘
│   canMoveTo()           │
│   uses Game::keystates  │
│   uses Game grid helpers│
└─────────────────────────┘

┌───────────────────────────────────────────────┐
│ Mesh                                          │
│   unit quad: VAO, VBO (pos/color/uv), EBO     │
│   draw()                                      │
└───────────────────────────────────────────────┘
```
