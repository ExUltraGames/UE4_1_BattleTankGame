
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
* BT04_UE4 185-191: Landscape Creation
* BT05_UE4 193-195: Tank Creation & Binding (195: DEFAULT PAWN SET)
* BT06_UE4 196/197: Fix 3rd Person Camera
* BT07_UE4 198: Player UI widget & TankPlayerControl
* BT08_UE4 199/200: Startermenu + UI Scale, Mouse & Buttons
* BT09_UE4 201: Controller Ready Navigation StartMenu
* BT10_UE4 202: Unreal UI, UMG & C++
* READ https://godbolt.org/ (code compiler)
* BT11_UE4 209/210: Get PlayerController & Tick - (ATank* GetControlledTank())
* BT12_UE4 Aiming Component and test
* BT13_UE4 212: Finding Pixel coords
* BT14_UE4 213: DeprojectScreenToWorld (project screen position to a world position)
* BT15_UE4 214: LineTraceSingleByChannel(), GetCameraLocation()
* BT16_UE4 215: Unify Player & AI Aiming
* BT17_UE4 216: Creating Default Sub Objects - CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
* BT18_UE4 217: BluePrintCallable() -  BARREL REFERENCE
* BT19_UE4 218/219: SuggestProjectileVelocity() (UGameStatics), GetSocketLocation(FName("Projectile"))
* BT20_UE4 220: FRotators, Barrel movement beginning
* BT21_UE4 222: Forward Declarations
* BT22_UE4 223: BlueprintSpawnableComponent() UCLASS( meta=(BlueprintSpawnableComponent) )
* BT23_UE4 224: Execution Flow (Diagram for Tank)
* BT24_UE4 225: Forward Declarations & Debug
* BT25_UE4 227: Clamp() - FMath::Clamp<float>
* BT26_UE4 228: TankTurret Movement
* BT27_UE4 Tank ReBuild
* BT28_UE4 229: Setting Projectile (create cpp & bp class) - Fire()
* BT29_UE4 231/232: Bug Investigation & collisions
* BT30_UE4 233: Projectile_2 (SpawnActor<>())
* BT31_UE4 234: Projectile Movement Components - (CreateDefaultSubobject<UTankAimingComponent>)
* BT32_UE4 235: Making AI Tanks Fire (GetWorld()->GetTimeSeconds(), (FPlatformTime::Seconds()))
* BT33_UE4 236: EditAnywhere vs EditDefaults only
* BT34_UE4 237: Adding a Quit button (UI) & Collisions
* BT35_UE4 238: Track Throttle (UStaticMeshComponent, BluePrintSpawnable)
* BT36_UE4 239: AppplyForceAtLocation() - applying forces to tank
* BT37_UE4 240: Physics Material & Friction
* BT38_UE4 241: Start Fly by Wire setup (intentions into commands, and for the AI)
* BT39_UE4 242: Using UPROPERTY(BlueprintReadOnly) (Add default movementcomponent and use in BP)   
* BT40_UE4 243: Better Component Architecture (Adding c++ components to BP and calling) - (UCLASS())
* BT41_UE4 244: Completing Manual Tank Movement (BIND inputs)
* BT42_UE4 245/246: Dissecting RequestDirectMove() & MoveToActor(), NavMesh
* BT43_UE4 247: DotProduct() Vector Operator ( Tank AI Movement forward back, COS) - GetSafeNormal() 
* BT44_UE4 248: CrossProduct() Vector Operator (tank AI rotate, SINE)
* BT45_UE4 249: Finalising Class Code (Finish Tank Movement)
* BT46_UE4 250: Use BluePrint Variables (UI Widget colour aiming) NOTE: (Aiming Comp Reference) - (UFUNCTION(BlueprintCallable, Category = Setup))
* BT47_UE4 251: Using Enum(erations)
* BT48_UE4 252: Refactor AimComponent, compiles but HARD CRASH
* BT49_UE4 253: Visual Studio Debugging (Hard Crash)+ code deletion & 253: Constructor and Begin Play Timing
* BT50_UE4 254/5: Constructor and Begin Play Timing & Decoupling Architecture
* BT51_UE4 256: BluePrintImplementable Event (TankPlayer and aiming, create UI) - UFUNCTION(BlueprintImplementableEvent)
* READ https://www.mathsisfun.com/algebra/vectors-dot-product.html
* BT52_UE4 257: ensure Assertion & Nullptr & error finding by pointer protection - if(!ensure()){ return; }
* BT53_UE4 258: Dependancy Mapping (analysis of C++ and .h files, map architecture)
* BT54_UE4 260: Starting from Green (Refactoring the architecture)
* BT55_UE4 261: Aiming without the TANK (Refactoring)
* BT56_UE4 262 & 263: Finishing refactor, solving ai movement issue (BP) + adding TickComponent() Back to an actor - (TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);)
* BT57_UE4 264: are two floats equal + sorted firing - (FVector::Equals())
* BT58_UE4 265: Programmatic Sideways Friction (stop slidding) - causes catastrophic FAILURE of movement RESTORE TO PREVIOUS CODE AND SKIP (GetRightVector()/GetComponentVelocity())
* BT59_UE4 RESTORED working coding post lecture 264
* BT60_UE4 266: RESTORE from course Github post OnComponentHit Event and solution clean (OnComponentHit / OnHit)
* BT61_UE4 267: Avoiding Boolean Flags & refactoring movement in tanktrack
* BT62_UE4 268: Improve Tank Aiming (shortest route & aim) - GetSightRayHitLocation(HitLocation)
* BT63_UE4 269: Tweaking Tank AI (create AIcontroller_BP) - GetFiringState()
* BT64_UE4 270: Ammo Display
* BT65_UE4 271/272: Making an AutoMortar (using BP class, components to create a mortar in BP)
* BT66_UE4 273: Reference Viewer (Source Control and Starter Content)
* BT67_UE4 274: Preparing for Particles (Setup Projectile Components & Create sub-objects)
* BT68_UE4 Added minimal Startcontent source control
* BT69_UE4 275/276: Particle Systems
* BT68_UE4 275 redo of particle system cpp
* BT69_UE4 276 redo & fix of particle system cpp
* BT70_UE4 277: FAttachmentTransformRules (ImpactBlast component) - AttachTo(RootComponent) 
* BT71_UE4 278: Radial Force component (Impulse)  & Caching > collisons & explosion
* BT72_UE4 279: GetTimerManager().SetTimer() - projectile destruction
* Fixed visibility of sphere
* preventing Tank fly (adding DownForce)
* BT73_UE4 280: TakeDamage() on Actors (Health) (UGameplayStatics::ApplyRadialDamage(), FMath::Clamp<int32>)
* BT74_UE4 281: Blueprint & healthbars (Getting Reference to Tank and pass into widget)
* BT75_UE4 282: The Observer Pattern (Dynamic Multi Cast Delegate, DCMDs) - (Broadcast(), SetPawn())
* READ: http://gameprogrammingpatterns.com/observer.html
* BT75_UE4 282b: The Observer Pattern (Dynamic Multi Cast Delegate, DCMDs) - continued (SetPawn())
* BT76_UE4 283/284: Finishing Off - Part 1 & 2 (StartSpectatingOnly(), DetachFromControllerPendingDestroy())
* Renumbering of lessons, adding methods to readme
* BT77_UE4 287: Swiching Cameras AND setting Tank Barrel MinElevation
* Tank Barrel MinElevation, removing magic numbers and making BP editable
* BT78_UE4 291: Creating Physics Constraints
* BT79_UE4 292: Making Springs (Suspension, shock absorption) + Physics stuff.
* BT80_UE4 293: Converting The Spring to C++ CPP (SprungWheel) (creating C++ components > BP)
* BT81_UE4 294: Attachment, Actors & Components (Spawnable Component)
* BT82_UE4 295: SpawnActorDeffered() / FinishSpawningActor() and BeginPlay
* AActor to ASprungWheel class to reduce Tank_BP SpawnPoint Component > Setup > Spawn ClassList
* BT83_UE4 296: Attaching Constraints in C++ (Adding Suspension) SetConstrainedComponents()
* BT84_UE4 297: Chaining Physics Constraints (Wheels attached to spring) - BUG no details tab!
* Bug sort - play and then reset to StaticMesh, restore point
* Bug workaround using solely c++ (ignore previous restore) 297: Chaining Physics Constraints COMPLETE
* BT84_UE4 298-299:Applying Wheel Driving Force (GetChildrenComponents(), Getters, Loops)
* BT85_UE4 300: Tick Groups AND Physics (apply force when on ground, OnHit)