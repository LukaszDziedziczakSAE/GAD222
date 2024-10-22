// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableComputer.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.h"
#include "MediaPlayer.h"
#include "MediaSoundComponent.h"

AInteractableComputer::AInteractableComputer()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(GetRootComponent());

	VideoScreen = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Video Screen"));
	VideoScreen->SetupAttachment(GetRootComponent());

	MediaSoundComponent = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("Media Sound Component"));
	MediaSoundComponent->SetupAttachment(GetRootComponent());

	
}

void AInteractableComputer::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractableComputer::Interact(APlayerCharacter* PlayerCharacter)
{
	if (!CanInteract(PlayerCharacter)) return;

	UE_LOG(LogTemp, Warning, TEXT("Switching to Computer Interaction"));

	PlayerCharacter->SwitchCamera(this);
}

bool AInteractableComputer::CanInteract(APlayerCharacter* PlayerCharacter)
{
	return !PlayerCharacter->bInComputerView;
}

void AInteractableComputer::PlayVideo(UMediaSource* Media)
{
	VideoScreen->SetVisibility(true);
	MediaPlayer->OpenSource(Media);
	MediaPlayer->Play();

	MediaPlayer->OnEndReached.AddDynamic(this, &AInteractableComputer::FinishVideo);
}

void AInteractableComputer::FinishVideo()
{
	MediaPlayer->Pause();
	VideoScreen->SetVisibility(false);

	MediaPlayer->OnEndReached.Clear();
}


