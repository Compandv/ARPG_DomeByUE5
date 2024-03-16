// Fill out your copyright notice in the Description page of Project Settings.

#pragma once //用来防止相同头文件重复包含

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h" //这个必须是最后包含的头文件 否则会出错

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MYSLASH_API ABird : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();
	virtual void Tick(float DeltaTime) override;

	//相较于Actor类，pawn类多了这个，表示能接收输入 比如键盘鼠标的属于等
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void Turn(float Value);
	void LookUp(float Value);

private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BirdMesh;

	//加一个弹簧臂组件，能使角色碰撞时缩进弹簧，再由摄像机辅助以达到放大角色的效果
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
};
