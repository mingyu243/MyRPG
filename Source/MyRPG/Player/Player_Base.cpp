#include "Player_Base.h"

#include "../Main/Main_PC.h"
#include "../Item/Weapon.h"
#include "PlayerAnim.h"

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
	MaxCombo = 4;
	AttackEndComboState();
}

void APlayer_Base::BeginPlay()
{
	Super::BeginPlay();
	
	AWeapon* NewWeapon = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(), FVector(-10.0f, 2.0f, 2.0f), FRotator(0.0f, 0.0f, -90.0f));
	SetWeapon(NewWeapon);
}

void APlayer_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayer_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
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
	AnimBP->OnAttackHitCheck.AddUObject(this, &APlayer_Base::AttackHitCheck);
}

void APlayer_Base::Attack()
{
	if (IsAttacking)
	{
		if (FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo))
		{
			if (CanNextCombo)
			{
				IsComboInputOn = true;
			}
		}
	}
	else
	{
		//if (CurrentCombo == 0)
		{
			AttackStartComboState();
			AnimBP->PlayAttackMontage();
			AnimBP->JumpToAttackMontageSection(CurrentCombo);
			IsAttacking = true;
		}
	}
}

void APlayer_Base::SetWeapon(AWeapon* NewWeapon)
{
	if (NewWeapon == nullptr) return;

	FName WeaponSocket(TEXT("hand_rSocket"));
	NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, WeaponSocket);
	NewWeapon->SetOwner(this);
	CurrentWeapon = NewWeapon;
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
	UE_LOG(LogClass, Warning, TEXT("NextAttackCheck"));
	CanNextCombo = false;

	if (IsComboInputOn)
	{
		UE_LOG(LogClass, Warning, TEXT("IsComboInputOn"));

		AttackStartComboState();
		AnimBP->JumpToAttackMontageSection(CurrentCombo);
	}
}

void APlayer_Base::AttackHitCheck()
{
	// 공격.
}

void APlayer_Base::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	if (FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1))
	{
		CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
		UE_LOG(LogClass, Warning, TEXT("AttackStartComboState : %d"), CurrentCombo);
	}
}

void APlayer_Base::AttackEndComboState()
{
	UE_LOG(LogClass, Warning, TEXT("AttackEndComboState : %d"), CurrentCombo);

	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}
