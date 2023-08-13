#include "Boss.h"

ABoss::ABoss()
{
	PrimaryActorTick.bCanEverTick = true;

	StatComponent = CreateDefaultSubobject<UBossStatComponent>(TEXT("StatComponent"));
	BuffComponent = CreateDefaultSubobject<UBuffComponent>(TEXT("BuffComponent"));
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
}

void ABoss::Die() {
	BP_Die();
}