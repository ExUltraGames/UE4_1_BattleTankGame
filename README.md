# UE4_1_BattleTankGame
Open world head to head tank battle game, with AI, terrain and advanced control, UE4
For Github Repository click [here](https://github.com/chineseburn/UE4_1_BattleTank)
Andrew Paine

---
## GDD

Tank Battle, open world head to head combat game
Terrain used for tactical advantage
Focus on flow & feel

Rules
Move anywhere, surrounded by mountains
Both players start with finite health and ammo
direct hit reduces health
last player standing = winner

Requirements
SFX - gun, explosion, barrel / turret moving, engine
Static Meshes (star with primitive objects) - simple tank comprising tracks, body, turret & barrel
Textures - add for visual flare later
Music - background music for tension

## Iterative Cycle
World -> tank-> control -> player 2 (AI or human) -> User Interface (UI) -> world (repeat)

## Commits
* BT01_UE4 Game Design Document (GDD)
* BT02_UE4 Iterative Cycle (IC)
* BT03_UE4 Unreal File Creation
* BT04_UE4 Landscape Creation
* BT05_UE4 Tank Creation & Binding
* BT06_UE4 Fix 3rd Person Camera
* BT07_UE4 Player UI widget & TankPlayerControl
* BT08_UE4 Startermenu + UI Scale, Mouse & Buttons
* BT09_UE4 Controller Ready Navigation StartMenu
* BT10_UE4 Unreal UI, UMG & C++
* BT11_UE4 Get PlayerController & Tick
* BT12_UE4 Aiming Component and test
* BT13_UE4 Finding Pixel coords
* BT14_UE4 DeprojectScreenToWorld
* BT15_UE4 LineTraceSingleByChannel()
* BT16_UE4 Unify Player & AI Aiming
* BT17_UE4 Creating Default Sub Objects
* BT18_UE4 BluePrintCallable()
* BT19_UE4 SuggestProjectileVelocity() (UGameStatics)
* BT20_UE4 FRotators, Barrel movement beginning
* BT21_UE4 221: Forward Declarations
* BT22_UE4 222: BlueprintSpawnableComponent()
* BT23_UE4 223: Execution Flow (Diagram for Tank)
* BT24_UE4 224:Forward Declarations & Debug
* BT25_UE4 226:Clamp()
* BT26_UE4 227: TankTurret Movement
* BT27_UE4 Tank ReBuild
* BT28_UE4 Setting Projectile (create cpp & bp class)
* BT29_UE4 Bug Investigation & collisions
* BT30_UE4 Projectile_2
* BT31_UE4 233: Projectile Movement Components
* BT32_UE4 234: Making AI Tanks Fire
* BT33_UE4 235: EditAnywhere vs EditDefaults only
* BT34_UE4 236: Adding a Quit button (UI) & Collisions
* BT35_UE4 237: Track Throttle (UStaticMeshComponent, BluePrintSpawnable)
* BT36_UE4 238: AppplyForceAtLocation() - applying forces to tank
* BT37_UE4 239: Physics Material & Friction
* BT38_UE4 240: Start Fly by Wire setup (intentions into commands, and for the AI)