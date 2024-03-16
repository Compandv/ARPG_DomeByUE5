// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AttributeComponent.h"

UAttributeComponent::UAttributeComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	
}


void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();


	
}

void UAttributeComponent::ReceiveDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);

}

void UAttributeComponent::UseStamina(float StaminaCost)
{
	Stamina = FMath::Clamp(Stamina - StaminaCost, 0.f, MaxStamina);
}

float UAttributeComponent::GetHealthPercent()
{
	return Health / MaxHealth;
}

float UAttributeComponent::GetStaminaPercent()
{
	return Stamina / MaxStamina;
}

bool UAttributeComponent::IsAlive()
{

	return Health > 0.f;
}

void UAttributeComponent::AddSouls(int32 NumberOfSouls)
{
	Souls += NumberOfSouls;
}

void UAttributeComponent::AddGold(int32 NumberOfGold)
{
	Gold += NumberOfGold;
}



void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//RegenStamina(DeltaTime);
}

void UAttributeComponent::RegenStamina(float DeltaTime)
{
	//实现每秒恢复体力值  并限定范围再0和 maxStamina
	Stamina = FMath::Clamp(Stamina + StaminaRegenRate * DeltaTime, 0.f, MaxStamina);
}

