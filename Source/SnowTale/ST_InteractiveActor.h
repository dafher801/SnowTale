
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ST_InteractiveActor.generated.h"

UCLASS()
class SNOWTALE_API AST_InteractiveActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AST_InteractiveActor();

public:

	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class AActor* OtherActor);

	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, 
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
				int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Result);

	bool GetActivated() const;
	void SetActivated(bool Activated);

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Overlap")
		class UBoxComponent* BoxOverlap;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		class UStaticMeshComponent* Mesh;

	bool bActivated;

};
