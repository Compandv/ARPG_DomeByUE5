#pragma once

//Ϊ��ɫ����һ��״̬ö��
//ö�ٵ�Լ���淶����ͷ��E �����class��������Ҫʹ��ö��ʱǰ��Ҫ�� ECharacterState:: ,�Դ˱���ͬ�����������
//���ǰ׺ECS_ (��Ϊ��ECharcaterState,ȡ���Ĵ�д��ĸ)  ���״̬���� ��� :uint8 ,��ʾΪ8λ����
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	//Ĭ����0��1��2һֱ����ȥ�������Զ��� 
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),//ʹ��������������ͼ�м�����ö���� displayName "Unequipped" ��ͬ
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