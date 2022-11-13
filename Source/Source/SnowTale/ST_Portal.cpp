
#include "ST_Portal.h"
#include "Kismet/GameplayStatics.h"

//void AST_Portal::Interact(AActor* OtherActor)
//{
//	Super::Interact(OtherActor);
//
//	UGameplayStatics::OpenLevel(GetWorld(), FName("Cinematic"));
//}

void AST_Portal::BeginPlay()
{
	Super::BeginPlay();

	SetActivated(false);
}
