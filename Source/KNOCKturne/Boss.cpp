#include "Boss.h"
#include "BuffComponent.h"

ABoss::ABoss()
{
	PrimaryActorTick.bCanEverTick = true;

	BuffComponent = CreateDefaultSubobject<UBuffComponent>(TEXT("BuffComponent"));
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
}
