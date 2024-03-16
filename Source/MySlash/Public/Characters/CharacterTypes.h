#pragma once

//为角色设置一个状态枚举
//枚举的约定规范：开头加E 且添加class（作用是要使用枚举时前面要加 ECharacterState:: ,以此保护同名误用情况）
//添加前缀ECS_ (因为是ECharcaterState,取他的大写字母)  添加状态不多 添加 :uint8 ,表示为8位整数
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	//默认是0，1，2一直排下去，可以自定义 
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),//使用这个宏可以让蓝图中见到的枚举是 displayName "Unequipped" 下同
	ECS_EquippedOneHandedWeapon UMETA(DisplayName = "Equipped One-Handed Weapon"),
	ECS_EquippedTwoHandedWeapon UMETA(DisplayName = "Equipped Two-Handed Weapon")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_HitReaction UMETA(DisplayName = "HitReaction"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	EAS_EquippingWeapon UMETA(DisplayName = "Equipping Weapon"),
	EAS_Dodge UMETA(DisplayName = "Dodge"),
	EAS_Dead UMETA(DisplayName = "Dead")

	
};

UENUM(BlueprintType)
enum  EDeathPose
{
	EAS_Death1 UMETA(DisplayName = "Death1"),
	EAS_Death2 UMETA(DisplayName = "Death2"),
	EAS_Death3 UMETA(DisplayName = "Death3"),
	EAS_Death4 UMETA(DisplayName = "Death4"),
	EAS_Death5 UMETA(DisplayName = "Death5"),
	EAS_Death6 UMETA(DisplayName = "Death6"),
	
	EDP_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	EES_NoState UMETA(DisplayName = "NoState"),
	EES_Dead UMETA(DisplayName = "Dead"),
	EES_Patrolling UMETA(DisplayName = "Patrolling"),
	EES_Chasing UMETA(DisplayName = "Chasing"),
	EES_Attacking UMETA(DisplayName = "Attacking"),
	EES_Engaged UMETA(DisplayName = "Engaged")


};