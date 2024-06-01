#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillIndexComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNOCKTURNE_API USkillIndexComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillIndexComponent();

	UFUNCTION(BlueprintCallable)
	void ConvertSkillIndex(int32 SkillIndex);
};
