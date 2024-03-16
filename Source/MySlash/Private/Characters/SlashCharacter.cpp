// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GroomComponent.h"
#include "item.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"
#include "HUD/SlashHUD.h"
#include "HUD/SlashOverlay.h"
#include "Component/AttributeComponent.h"
#include "Item/Soul.h"
#include "Items/Treasure.h"
#include "MySlash/DebugMacros.h"

// Sets default values
ASlashCharacter::ASlashCharacter()
{
	PrimaryActorTick.bCanEverTick = true;//�Ƿ���Tick������ʹ��

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;//����ת��ʱ����Ҳ��ת��
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);//����ת����ٶ�  yaw(z��)����Ϊ360

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true); 


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");


}

void ASlashCharacter::Tick(float DeltaTime)
{
	if (Attributes && SlashOverlay)
	{	
		Attributes->RegenStamina(DeltaTime);
		SlashOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}
}

void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//�����ź���� callback����
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ASlashCharacter::MoveForward);

	PlayerInputComponent->BindAxis(FName("Turn"), this, &ASlashCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ASlashCharacter::LookUp);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ASlashCharacter::MoveRight);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ASlashCharacter::Jump);
	PlayerInputComponent->BindAction(FName("Equip"), IE_Pressed, this, &ASlashCharacter::EKeyPressed);
	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &ASlashCharacter::Attack);
	PlayerInputComponent->BindAction(FName("Dodge"), IE_Pressed, this, &ASlashCharacter::Dodge);

}

void ASlashCharacter::Jump()
{
	if (IsUnoccupied())
	{	
		Super::Jump();
	}
}



float ASlashCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	SetHUDHealth();
	return DamageAmount;
}


void ASlashCharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	Super::GetHit_Implementation(ImpactPoint, Hitter);
	SetWeaponCollisionEnable(ECollisionEnabled::NoCollision);
	if (Attributes && Attributes->GetHealthPercent() > 0.f)
	{	
		ActionState = EActionState::EAS_HitReaction;
	}
}

void ASlashCharacter::SetOverlappingItem(Aitem* Item)
{
	OverlappingItem = Item;
}

void ASlashCharacter::AddSouls(ASoul* Soul)
{
	if (Attributes && SlashOverlay)
	{
		//�������ͽ��涼����
		Attributes->AddSouls(Soul->GetSouls());
		SlashOverlay->SetSouls(Attributes->GetSouls());
	}
}

void ASlashCharacter::AddGold(ATreasure* Treasure)
{
	if (Attributes && SlashOverlay)
	{
		//DRAW_SPHERE(GetActorLocation());

		Attributes->AddGold(Treasure->GetGold());
		SlashOverlay->SetGold(Attributes->GetGold());

	}
}

void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("EngageableTarget"));
	InitializeSlashOverlay();
}


void ASlashCharacter::MoveForward(float Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;//�����޷��� �ǿ��� ʱ�ƶ�

	//ʵ�ָ�����Ұ�����ǰ��(���ߺ���)
	if (Controller && Value != 0.f)
	{
		const FRotator ControlRotation = GetControlRotation();//�õ���������ת ����Ұ�ķ���
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);//ת��ֻ�迼��yaw�������������Ϊ0

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); //��ӷ��򣬲��õ���Ӧ�ĵ�λ���� X��ʾ��ǰ
		AddMovementInput(Direction, Value);
	}
	
	
}

void ASlashCharacter::MoveRight(float Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;//�����޷��� �ǿ��� ʱ�ƶ�

	//��moveforward��������

	if (Controller && Value != 0.f)
	{
		const FRotator ControlRotation = GetControlRotation();//�õ���������ת ����Ұ�ķ���
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);//ת��ֻ�迼��yaw�������������Ϊ0
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); //��ӷ��򣬲��õ���Ӧ�ĵ�λ���� Y��ʾ����
		AddMovementInput(Direction, Value);

	}
}

void ASlashCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);

}

void ASlashCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);

}

void ASlashCharacter::EKeyPressed()
{
	//����E��ʰȡ
	//��ֻϣ���ص�ʱ
	
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		if (EquippedWeapon)
		{
			EquippedWeapon->Destroy();
		}
		EquipWeapon(OverlappingWeapon);
	}
	else
	{
		if (CanDisarm())
		{
			Disarm();
		}
		else if (CanArm())
		{
			
			Arm();
		}
	}
}



void ASlashCharacter::EquipWeapon(AWeapon* Weapon)
{
	Weapon->Equip(GetMesh(), FName("RightHandSocket"), this, this);
	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	OverlappingItem = nullptr;
	EquippedWeapon = Weapon;
}

void ASlashCharacter::Attack()
{
	Super::Attack();
	//����ǰ����Ƿ��ڿ���״̬ �Ѿ�ӵ������
	if (CanAttack())
	{
		PlayAttackMontage();//���� �����Ź�����̫��
		ActionState = EActionState::EAS_Attacking; //״̬��Ϊ����״̬
	}
}

void ASlashCharacter::Dodge()
{
	//if (IsOccupied()) return;//���Ͼ��޷���Ϲ����������ܣ������Ͽ���
	if (!HasEnoughStamina()) return;//����ֵ���� ֱ�Ӳ�������

	PlayDodgeMontage();
	ActionState = EActionState::EAS_Dodge;
	if (Attributes && SlashOverlay)
	{	
		Attributes->UseStamina(Attributes->GetDodgeCost());//�����������
		SlashOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());//���½���������
	}
}



void ASlashCharacter::AttackEnd()
{
	//���������лؿ���״̬
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::DodgeEnd()
{
	Super::DodgeEnd();
	ActionState = EActionState::EAS_Unoccupied;
}


bool ASlashCharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped;
}

bool ASlashCharacter::CanDisarm()
{
	return ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped;
}

void ASlashCharacter::Disarm()
{
	PlayEquipMontage(FName("UnEquip"));
	CharacterState = ECharacterState::ECS_Unequipped;
	ActionState = EActionState::EAS_EquippingWeapon;
}

bool ASlashCharacter::CanArm()
{
	return ActionState == EActionState::EAS_Unoccupied && CharacterState == ECharacterState::ECS_Unequipped && EquippedWeapon;
}

void ASlashCharacter::Arm()
{
	PlayEquipMontage(FName("Equip"));
	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	ActionState = EActionState::EAS_EquippingWeapon;
}

void ASlashCharacter::PlayEquipMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);

	}

}

void ASlashCharacter::Die_Implementation()
{
	Super::Die_Implementation();
	ActionState = EActionState::EAS_Dead;
	DisableMeshCollision();
}

bool ASlashCharacter::HasEnoughStamina()
{
	return Attributes && Attributes->GetStamina() > Attributes->GetDodgeCost();
}

bool ASlashCharacter::IsOccupied()
{
	return ActionState != EActionState::EAS_Unoccupied;
}

void ASlashCharacter::AttachWeaponToBack()
{
	if (EquippedWeapon)
	{	
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
	}
}

void ASlashCharacter::AttachWeaponToHand()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));
	}
}

void ASlashCharacter::FinishEquipping()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::HitReactEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::InitializeSlashOverlay()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		ASlashHUD* SlashHUD = Cast<ASlashHUD>(PlayerController->GetHUD());//ȡ��HUD,תΪʹ�õ�SlashHUD
		if (SlashHUD)
		{
			SlashOverlay = SlashHUD->GetSlashOverlay();
			if (SlashOverlay && Attributes)
			{
				SlashOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
				SlashOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
				SlashOverlay->SetGold(0);
				SlashOverlay->SetSouls(0);

			}
		}
	}
}

void ASlashCharacter::SetHUDHealth()
{
	if (SlashOverlay && Attributes)
	{
		SlashOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
	}
}

bool ASlashCharacter::IsUnoccupied()
{
	return ActionState == EActionState::EAS_Unoccupied;
}