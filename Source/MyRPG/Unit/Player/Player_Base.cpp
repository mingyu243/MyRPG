#include "Player_Base.h"

#include "PlayerAnim.h"
#include "../../Main/Main_PC.h"
#include "../../Main/Main_HUD.h"
#include "../../Item/Weapon.h"
#include "../../Component/EquipmentComponent.h"
#include "../../Component/InventoryComponent.h"
#include "../../CustomDataTables.h"

#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/SkeletalMeshSocket.h"

APlayer_Base::APlayer_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EQUIPMENT")); // 대문자 단축키는 Ctrl + Shift + U.
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("INVENTORY"));
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SCENECAPTURE"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	SceneCapture->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Knight(TEXT("SkeletalMesh'/Game/ModularRPGHeroesPolyart/Meshes/OneMeshCharacters/KnightSK.KnightSK'"));
	if (SK_Knight.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Knight.Object);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_Player(TEXT("AnimBlueprint'/Game/Blueprints/Player/BP_PlayerAnim.BP_PlayerAnim_C'"));
	if (ABP_Player.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ABP_Player.Class);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.f), FRotator(0.0f, 270.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> RT_Player(TEXT("TextureRenderTarget2D'/Game/Blueprints/UI/RT_Player.RT_Player'"));
	if (RT_Player.Succeeded())
	{
		SceneCapture->TextureTarget = RT_Player.Object;
	}
	SceneCapture->SetRelativeLocationAndRotation(FVector(170.0f, 0.0f, 0.0f), FRotator(0.0f, 180.0f, 0.0f));
	SceneCapture->ShowFlags.Atmosphere = 0;
	SceneCapture->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth;
	SceneCapture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	SceneCapture->ShowOnlyActors.Add(this);

	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 300.0f);
	Camera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = true;
	GetCharacterMovement()->JumpZVelocity = 700.0f; // 점프 높이.

	IsAttacking = false;
	MaxCombo = 3;
	AttackEndComboState();
}

void APlayer_Base::BeginPlay()
{
	Super::BeginPlay();
	
	//AWeapon* NewWeapon = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(), FVector(-10.0f, 2.0f, 2.0f), FRotator(0.0f, 0.0f, -90.0f));
	//Equipment->SetWeapon(NewWeapon);

	AMain_PC* PC = Cast<AMain_PC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		AMain_HUD* HUD = Cast<AMain_HUD>(PC->GetHUD());
		if (HUD)
		{
			// UI와 데이터 바인딩.
			HUD->BindCharacterStat(GetCharacterStat());
			HUD->BindInventory(GetInventoryComponent());
			HUD->BindEquipment(GetEquipmentComponent());
		}
	}

	// 바로 장착하기.
	// EquipmentComponent->SetEquipment(EquipmentComponent->CreateEquipment(100)); // 옷

	// 테스트용 아이템 인벤토리에 추가.
	Inventory->AddItem(EquipmentComponent->CreateEquipment(102)); // 옷
	Inventory->AddItem(EquipmentComponent->CreateEquipment(111)); // 벨트
	Inventory->AddItem(EquipmentComponent->CreateEquipment(121)); // 머리 장식
	Inventory->AddItem(EquipmentComponent->CreateEquipment(133)); // 얼굴
	Inventory->AddItem(EquipmentComponent->CreateEquipment(141)); // 장갑
	Inventory->AddItem(EquipmentComponent->CreateEquipment(150)); // 헤어
	Inventory->AddItem(EquipmentComponent->CreateEquipment(182)); // 신발
	Inventory->AddItem(EquipmentComponent->CreateEquipment(193)); // 어깨 장식
	Inventory->AddItem(EquipmentComponent->CreateEquipment(500)); // 가방

	Inventory->AddItem(EquipmentComponent->CreateWeapon(200)); // 검
	Inventory->AddItem(EquipmentComponent->CreateWeapon(200)); // 검
	Inventory->AddItem(EquipmentComponent->CreateWeapon(200)); // 검
}

void APlayer_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayer_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APlayer_Base::StartJump);
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &APlayer_Base::Attack);

	PlayerInputComponent->BindAxis("LookUp", this, &APlayer_Base::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &APlayer_Base::Turn);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayer_Base::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayer_Base::MoveRight);
}

void APlayer_Base::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimBP = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
	AnimBP->OnMontageEnded.AddDynamic(this, &APlayer_Base::OnAttackMontageEnded);
	AnimBP->OnNextAttackCheck.AddUObject(this, &APlayer_Base::NextAttackCheck);

	// 장비를 장착할 메쉬 설정.
	EquipmentComponent->Init(GetMesh());
}

void APlayer_Base::Attack()
{
	CtoS_Attack();
}

void APlayer_Base::CtoS_Attack_Implementation()
{
	MC_Attack();
}

void APlayer_Base::MC_Attack_Implementation()
{
	if (GetCharacterMovement()->IsFalling()) return;

	if (IsAttacking == false) //if (CurrentCombo == 0)
	{
		IsAttacking = true;

		AttackStartComboState();
		AnimBP->PlayAttackMontage();
		AnimBP->JumpToAttackMontageSection(CurrentCombo);
	}
	else
	{
		if (FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo))
		{
			if (CanNextCombo)
			{
				IsComboInputOn = true;
			}
		}
	}
}

bool APlayer_Base::UseItem(UItem* Item)
{
	if (Item)
	{
		Item->Use(this);
		if (Inventory->RemoveItem(Item))
		{
			return true;
		}
	}
	return false;
}

bool APlayer_Base::TakeOffEquipment(UEquipment* Equipment)
{
	if (Equipment)
	{
		UEquipment* Pop = EquipmentComponent->PopEquipment(Equipment);
		if (Pop)
		{
			Inventory->AddItem(Pop);
			return true;
		}
	}
	return false;
}

void APlayer_Base::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void APlayer_Base::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayer_Base::MoveForward(float AxisValue)
{
	FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(Direction, AxisValue);
}

void APlayer_Base::MoveRight(float AxisValue)
{
	FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(Direction, AxisValue);
}

void APlayer_Base::StartJump()
{
	if (IsAttacking) return;

	bPressedJump = true; // ACharacter::Jump()를 호출한 것과 비슷함.
}

void APlayer_Base::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (IsAttacking)
	{
		if (CurrentCombo > 0)
		{
			IsAttacking = false;
			AttackEndComboState();
		}
	}
}

void APlayer_Base::NextAttackCheck()
{
	CanNextCombo = false;

	if (IsComboInputOn)
	{
		AttackStartComboState();
		AnimBP->JumpToAttackMontageSection(CurrentCombo);
	}
}

void APlayer_Base::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;

	// 마지막 공격이 아니면,
	if (FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1))
	{
		// CurrentCombo 1 증가.
		CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
	}
}

void APlayer_Base::AttackEndComboState()
{
	CanNextCombo = false;
	IsComboInputOn = false;

	CurrentCombo = 0;
}
