// Fill out your copyright notice in the Description page of Project Settings.

#pragma once //������ֹ��ͬͷ�ļ��ظ�����

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h" //�����������������ͷ�ļ� ��������

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

	//�����Actor�࣬pawn������������ʾ�ܽ������� ��������������ڵ�
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

	//��һ�����ɱ��������ʹ��ɫ��ײʱ�������ɣ���������������Դﵽ�Ŵ��ɫ��Ч��
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
};
