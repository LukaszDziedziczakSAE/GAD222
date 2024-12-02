// Lukasz Dziedziczak 2024


#include "Music.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMusic::AMusic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(RootComp);

	Layer_Percussive = CreateDefaultSubobject<UAudioComponent>(TEXT("Pecussive Layer"));
	Layer_Percussive->SetupAttachment(RootComp);
	
	Layer_Atmospheric = CreateDefaultSubobject<UAudioComponent>(TEXT("Atmospheric Layer"));
	Layer_Atmospheric->SetupAttachment(RootComp);
	
	Layer_Piano = CreateDefaultSubobject<UAudioComponent>(TEXT("Piano Layer"));
	Layer_Piano->SetupAttachment(RootComp);
	
	Layer_Bongos = CreateDefaultSubobject<UAudioComponent>(TEXT("Bongos Layer"));
	Layer_Bongos->SetupAttachment(RootComp);
	
	Layer_Strings = CreateDefaultSubobject<UAudioComponent>(TEXT("Strings Layer"));
	Layer_Strings->SetupAttachment(RootComp);
	
	Layer_SquareWave = CreateDefaultSubobject<UAudioComponent>(TEXT("SquareWave Layer"));
	Layer_SquareWave->SetupAttachment(RootComp);
	
}

// Called when the game starts or when spawned
void AMusic::BeginPlay()
{
	Super::BeginPlay();

	Layer_Percussive->AdjustVolume(0, MinVolume);
	Layer_Atmospheric->AdjustVolume(0, MinVolume);
	Layer_Piano->AdjustVolume(0, MinVolume);
	Layer_Bongos->AdjustVolume(0, MinVolume);
	Layer_Strings->AdjustVolume(0, MinVolume);
	Layer_SquareWave->AdjustVolume(0, MinVolume);

	if (bOnStartPercussive) FadeInPercussive();
	if (bOnStartAtmospheric) FadeInAtmospheric();
	if (bOnStartPiano) FadeInPiano();
	if (bOnStartBongos) FadeInBongos();
	if (bOnStartStrings) FadeInStrings();
	if (bOnStartSquareWave) FadeInSquareWave();
}

// Called every frame
void AMusic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMusic::FadeInPercussive()
{
	//if (Layer_Percussive->VolumeMultiplier == MaxVolume) return;
	Layer_Percussive->AdjustVolume(FadeTime, MaxVolume);
	UE_LOG(LogTemp, Display, TEXT("FadeInPercussive"));
}

void AMusic::FadeOutPercussive()
{
	//if (Layer_Percussive->VolumeMultiplier == MinVolume) return;
	Layer_Percussive->AdjustVolume(FadeTime, MinVolume);
	UE_LOG(LogTemp, Display, TEXT("FadeOutPercussive"));
}

void AMusic::FadeInAtmospheric()
{
	//if (Layer_Atmospheric->VolumeMultiplier == MaxVolume) return;
	Layer_Atmospheric->AdjustVolume(FadeTime, MaxVolume);
	UE_LOG(LogTemp, Display, TEXT("FadeInAtmospheric"));
}

void AMusic::FadeOutAtmospheric()
{
	//if (Layer_Atmospheric->VolumeMultiplier == MinVolume) return;
	Layer_Atmospheric->AdjustVolume(FadeTime, MinVolume);
	UE_LOG(LogTemp, Display, TEXT("FadeOutAtmospheric"));
}

void AMusic::FadeInPiano()
{
	//if (Layer_Piano->VolumeMultiplier == MaxVolume) return;
	Layer_Piano->AdjustVolume(FadeTime, MaxVolume);
	UE_LOG(LogTemp, Display, TEXT("FadeInPiano"));
}

void AMusic::FadeOutPiano()
{
	//if (Layer_Piano->VolumeMultiplier == MinVolume) return;
	Layer_Piano->AdjustVolume(FadeTime, MinVolume);
	UE_LOG(LogTemp, Display, TEXT("FadeOutPiano"));
}

void AMusic::FadeInBongos()
{
	//if (Layer_Bongos->VolumeMultiplier == MaxVolume) return;
	Layer_Bongos->AdjustVolume(FadeTime, MaxVolume);
	UE_LOG(LogTemp, Display, TEXT("FadeInBongos"));
}

void AMusic::FadeOutBongos()
{
	//if (Layer_Bongos->VolumeMultiplier == MinVolume) return;
	Layer_Bongos->AdjustVolume(FadeTime, MinVolume);
	UE_LOG(LogTemp, Display, TEXT("FadeOutBongos"));
}

void AMusic::FadeInStrings()
{
	//if (Layer_Strings->VolumeMultiplier == MaxVolume) return;
	Layer_Strings->AdjustVolume(FadeTime, MaxVolume);
	UE_LOG(LogTemp, Display, TEXT("FadeInStrings"));
}

void AMusic::FadeOutStrings()
{
	//if (Layer_Strings->VolumeMultiplier == MinVolume) return;
	Layer_Strings->AdjustVolume(FadeTime, MinVolume);
	UE_LOG(LogTemp, Display, TEXT("FadeOutStrings"));
}

void AMusic::FadeInSquareWave()
{
	//if (Layer_SquareWave->VolumeMultiplier == MaxVolume) return;
	Layer_SquareWave->AdjustVolume(FadeTime, MaxVolume);
	UE_LOG(LogTemp, Display, TEXT("FadeInSquareWave"));
}

void AMusic::FadeOutSquareWave()
{
	//if (Layer_SquareWave->VolumeMultiplier == MinVolume) return;
	Layer_SquareWave->AdjustVolume(FadeTime, MinVolume);
	UE_LOG(LogTemp, Display, TEXT("FadeOutSquareWave"));
}

