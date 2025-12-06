# 🧟 Zombie Shooter 2D

A fast-paced 2D top-down shooter game built from scratch with C++ and SDL2. Survive against endless waves of zombies in this challenging arcade-style game.

---

## 🎥 Gameplay Demo

![Gameplay Demo](gameplay.mp4)

*dowloade to watch gameplay footage*

---

## 🎮 Gameplay

Control your character with keyboard and mouse to survive against increasingly difficult waves of zombies. Each zombie kill increases your score, but watch out - they get faster and spawn more frequently over time!

### Objective
- Survive as long as possible
- Shoot zombies before they reach you
- Beat your high score

### Difficulty
- Zombies spawn faster as time passes
- Spawn rate increases every 30 seconds
- Maximum difficulty reached after 60 seconds

---

## 🎯 Controls

| Action | Control |
|--------|---------|
| **Movement** | W/A/S/D or Z/Q/S/D keys |
| **Aim** | Move mouse cursor |
| **Shoot** | Left Mouse Button |
| **Exit** | Close window |

---

## 🛠️ Technical Implementation

### Architecture
- **C++17** - Modern C++ features
- **SDL2** - Graphics, input, and rendering
- **Object-Oriented Design** - Clean inheritance hierarchy
- **Custom Game Engine** - Built from scratch

### Key Features
- Delta-time based game loop
- Custom collision detection system
- Sprite-based animations with flipping
- Dynamic difficulty scaling
- Health bar system for all entities
- Invulnerability frames after damage
- Explosion particle effects

---

## 📁 Project Structure

    zombie-shooter/
        ├── Game.h/cpp # Main game class and loop
        ├── Player.h/cpp # Player character with shooting mechanics
        ├── Zombie.h/cpp # Enemy AI and pathfinding
        ├── Character.h/cpp # Base character class (inheritance)
        ├── Bullet.h/cpp # Projectile system
        ├── Explosion.h/cpp # Visual effects and animations
        ├── GameObject.h/cpp # Base game object interface
        ├── Obstacle.h # Level design and walls
        ├── GData.h/cpp # Global constants and configuration
        ├── main.cpp # Application entry point
        └── assets/ # Game resources
            ├── topdownpack.png # Player spritesheet
            ├── Idle_Fly.png # Zombie idle animation
            └── Attack_Death.png # Death/explosion animation


### Class Hierarchy

    GameObject (abstract)
    ├── Character
    │       ├── Player
    │       └── Zombie
    ├── Bullet
    └── Explosion



---

## 🚀 How to Play

1. Launch the game from your terminal/command prompt
2. Read the controls displayed at startup
3. Press Enter to begin
4. Use WASD/ZQSD to move your character
5. Aim with your mouse and click to shoot
6. Survive as long as possible!

The game will show your final score (zombies killed) when you die.

---

## 🔧 Game Configuration

### Difficulty Settings
- Initial spawn interval: 5 seconds
- Minimum spawn interval: 0.5 seconds
- Difficulty increase rate: 0.03 per second
- Zombie health: 5 hits
- Player health: 10 hits

### Window Settings
- Resolution: 1280×720 pixels
- Title: "2D shooter zombie"
- VSync: Enabled
- Renderer: Hardware accelerated

---

## 📊 Scoring System

- Each zombie kill: +1 point
- Score displayed at game end
- No maximum score limit
- Survival time tracked

---

## 🎨 Visual Features

- Player rotation based on mouse position
- Zombie sprite flipping based on direction
- Health bars with color coding (green/yellow/red)
- Invulnerability blinking effect
- 8-frame explosion animation
- Smooth movement with delta time

---

## 🧠 AI System

Zombies feature:
- Pathfinding around obstacles
- Direct pursuit when path is clear
- Simple obstacle avoidance
- Window boundary detection

---

## 🐛 Known Issues / Future Improvements

### Current Limitations
- Basic collision detection (AABB)
- No sound effects
- No menu system
- No save/load functionality

### Planned Features
- [ ] Sound effects and background music
- [ ] Power-up system
- [ ] Different zombie types
- [ ] Level progression
- [ ] High score tracking
- [ ] Pause menu
- [ ] Graphics optimization

---

## 👤 Author

**Lehrach Abderrahmane**  
Game Developer & Computer Science Student

### Development Time
- Engine development: 2 weeks
- Game mechanics: 1 week
- Polish and bug fixing: 3 days

---

## 📝 License

This project is created for educational purposes and personal portfolio.  
All game assets are used under fair use for educational demonstration.

---

## 🙏 Acknowledgments

- SDL2 community for excellent documentation
- [OpenGameArt](https://itch.io/) for sprite references
- University coursework for foundation

---

*"Can you survive the zombie horde?"* 🧟‍♂️🔫
