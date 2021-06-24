#include "Player_Base.h"

#include "PlayerAnim.h"
#include "../../Main/Main_PC.h"
#include "../../Main/Main_HUD.h"
#include "../../Item/Weapon.h"
#include "../../Component/EquipmentComponent.h"
#include "../../Component/InventoryComponent.h"
#include "../../CustomDataTables.h"

#include "GameFramework/SpringArmComponent.h"
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
	Equipment = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EQUIPMENT")); // 대문자 단축키는 Ctrl + Shift + U.
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("INVENTORY"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

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
			HUD->BindCharacterStat(GetCharacterStat());
		}
	}

	// 테스트용 아이템 삽입. 오류났음... 집가서 알아보도록 하자..
	UWeapon* TestItem = NewObject<UWeapon>();
	TestItem->Init(200);

	Inventory->AddItem(TestItem);
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
	Equipment->Init(GetMesh());
}

UEquipmentComponent* APlayer_Base::GetEquipmentComponent()
{
	return Equipment;
}

class UInventoryComponent* APlayer_Base::GetInventoryComponent()
{
	return Inventory;
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

void APlayer_Base::UseItem(UItem* Item)
{
	if (Item)
	{
		Item->Use(this);
	}
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
