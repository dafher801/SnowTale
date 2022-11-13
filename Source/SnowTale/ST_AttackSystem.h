
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ST_AttackSystem.generated.h"

UCLASS()
class SNOWTALE_API AST_AttackSystem : public AActor
{
	GENERATED_BODY()

public:

	AST_AttackSystem();

public:

	// AttackSystem �۵� �� �� �����Ӹ��� ����Ǵ� ����
	virtual void Tick(float DeltaTime) override;

	// Unit���κ��� ���� ��û�� ������ �� ����Ǵ� ����
	virtual void Attack();

	// AttackSystem�� ������ �ִ� �߻�ü Ȥ�� 
	// ���ǿ� ���� ���������� ���� ����ϴ� ����
	virtual void SetOwner(AActor* NewOwner) override;

	bool IsActivated() const;
	void SetActivated(bool Activated);

protected:

	virtual void BeginPlay() override;

protected:

	bool bActivated;
	
};
