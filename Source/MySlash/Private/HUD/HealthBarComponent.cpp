// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HealthBarComponent.h"
#include "HUD/HealthBar.h"
#include "Components/ProgressBar.h"

void UHealthBarComponent::SetHealthPercent(float Percent)
{
	if (!HealthBarWidget)
	{
		HealthBarWidget = Cast<UHealthBar>(GetUserWidgetObject());//ȡ�ö��󣬲�תΪUHealthBar*
	}
	
	if (HealthBarWidget && HealthBarWidget->HealthBar)
	{	
		HealthBarWidget->HealthBar->SetPercent(Percent);
	}
}