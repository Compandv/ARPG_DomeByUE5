// Fill out your copyright notice in the Description page of Project Settings.


#include "item.h"
#include "MySlash/MySlash.h"
#include "MySlash/DebugMacros.h"
#include "Components/SphereComponent.h"
#include "Interfaces/PickupInterface.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
Aitem::Aitem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

	ItemEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers"));
	ItemEffect->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void Aitem::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("Begin Play called!"));

	////��ӡ���ֵ���Ļ �൱����ͼ��print string
	//if (GEngine)
	//{
	//	//������ ���  ����ʱ��  ��ɫ  ��ӡ������
	//	GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Cyan, FString("print to screen!!!"));
	//}

	//UWorld* World = GetWorld();


	//
	////������Աλ�ã��Է��õ�λ��Ϊ���  x , y , z��
	//SetActorLocation(FVector(0.f, 0.f, 200.f));

	////������ת 
	//SetActorRotation(FRotator(0.f, 50.f, 0.f));

	//FVector location = GetActorLocation();

	////����һ�������� ��ͼ��Draw Debug Sphere
	////������ ���� ���ĵ�λ�� �뾶  ����(����Խ�����Բ)   ��ɫ  ������(Ĭ��true true -> ����������  false -> �ִ���ʱ��)  ����ʱ��(Ĭ��0)
	////DrawDebugSphere(World, location, 25.f, 24, FColor::Red, false, 30.f);
	//DRAW_SPHERE(location);

	//FVector Forward = GetActorForwardVector();//ǰ��������Ĭ��Ϊ��λ����
	////����һ�������� ��ͼ Draw Debug Line
	////���� ����  ��ʼλ��  ��ֹλ�� ��ɫ  �Ƿ�����  ����ʱ��  ���ȼ�(ԽСԽ�߼���0Ϊ��߼�) �ߵĴ�ϸ
	////if(World) DrawDebugLine(World, location, location + Forward * 100.f, FColor::Red, true, -1.f, 0, 1.f);
	////DRAW_LINE(location, location + Forward * 100);

	////����һ�������� ��ͼ Draw Debug Point
	////���� ���� λ��(�����ͼ����õ����ĵ�)  �ߴ�  ��ɫ  �Ƿ�����
	////if (World) { DrawDebugPoint(World, location + Forward * 100, 15.f, FColor::Red, true); }
	////DRAW_POINT(location + Forward * 100);

	//DRAW_VECTOR(location, location + Forward * 100);


	Sphere->OnComponentBeginOverlap.AddDynamic(this, &Aitem::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &Aitem::OnSphereEndOverlap);

}

float Aitem::TransformedSin()
{

	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float Aitem::TransformdCosin()
{
	return Amplitude* FMath::Cos(RunningTime * TimeConstant);
}



void Aitem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//�ﵽ��Χ�������ص�item
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->SetOverlappingItem(this);
	}
}

void Aitem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//�߳���Χ������û���ص���item
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->SetOverlappingItem(nullptr);
	}
}

void Aitem::SpawnPickupSystem()
{
	//ʰȡ֮�󲥷�ʰȡ��Ч
	if (PickupEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			PickupEffect,
			GetActorLocation()
		);
	}
}

void Aitem::SpawnPickupSound()
{
	if (PickupSound)
	{	
		UGameplayStatics::SpawnSoundAtLocation(
			this,
			PickupSound,
			GetActorLocation()
		);
	}
}

// Called every frame
void Aitem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	RunningTime += DeltaTime;

	if (ItemState == EItemState::EIS_Hovering)
	{	
		float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);

		AddActorWorldOffset(FVector(0, 0, DeltaZ));

	}


}

