// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);
    // leaving this on applies small constant force via component 'tick' (Optional)
	ForceComp->SetAutoActivate(false);

	ForceComp->Radius = 750.0f;
	ForceComp->ImpulseStrength = 2500.0f; //alternative: 200000.0 if bimpulsevelchange =  false 
    //optional, ignores 'mass' of other objects (if false, the impulse strenght will be much higher to push most objects depending on mass)
	ForceComp->bImpulseVelChange = true;

    // optional, default constructor of component already adds 4 object types to affect, excluding worldynamic 
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

	// binding either in constructor or in postinitializecomponents() below
	// MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}
void ASExplosiveBarrel::PostInitializeComponents()
{
	//dont forget to call parent function 
	Super::PostInitializeComponents();
	MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}
void ASExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Barrel"));

	// %s = string
	// %f = float
	// logs: "OtherActor: MyActor_1, at gametime: 124.4"
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);


	FString CombinedString = FString::Printf(TEXT("Hit at location %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr,FColor::Green, true);
}


