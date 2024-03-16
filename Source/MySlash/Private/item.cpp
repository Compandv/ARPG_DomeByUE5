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

	////打印文字到屏幕 相当于蓝图的print string
	//if (GEngine)
	//{
	//	//参数： 组别  持续时间  颜色  打印的文字
	//	GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Cyan, FString("print to screen!!!"));
	//}

	//UWorld* World = GetWorld();


	//
	////设置演员位置（以放置的位置为起点  x , y , z）
	//SetActorLocation(FVector(0.f, 0.f, 200.f));

	////设置旋转 
	//SetActorRotation(FRotator(0.f, 50.f, 0.f));

	//FVector location = GetActorLocation();

	////创建一个调试球 蓝图：Draw Debug Sphere
	////参数： 世界 中心的位置 半径  段数(段数越大，球更圆)   颜色  持续线(默认true true -> 调试球永存  false -> 又存在时间)  存在时间(默认0)
	////DrawDebugSphere(World, location, 25.f, 24, FColor::Red, false, 30.f);
	//DRAW_SPHERE(location);

	//FVector Forward = GetActorForwardVector();//前进向量，默认为单位向量
	////创建一个调试线 蓝图 Draw Debug Line
	////参数 世界  起始位置  终止位置 颜色  是否永存  持续时间  优先级(越小越高级，0为最高级) 线的粗细
	////if(World) DrawDebugLine(World, location, location + Forward * 100.f, FColor::Red, true, -1.f, 0, 1.f);
	////DRAW_LINE(location, location + Forward * 100);

	////创建一个调试线 蓝图 Draw Debug Point
	////参数 世界 位置(相较蓝图类放置的中心点)  尺寸  颜色  是否永存
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
	//达到范围就设置重叠item
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->SetOverlappingItem(this);
	}
}

void Aitem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//走出范围就设置没有重叠的item
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->SetOverlappingItem(nullptr);
	}
}

void Aitem::SpawnPickupSystem()
{
	//拾取之后播放拾取特效
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

