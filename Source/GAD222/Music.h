// Lukasz Dziedziczak 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Music.generated.h"

UCLASS()
class GAD222_API AMusic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAudioComponent* Layer_Percussive;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAudioComponent* Layer_Atmospheric;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAudioComponent* Layer_Piano;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAudioComponent* Layer_Bongos;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAudioComponent* Layer_Strings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAudioComponent* Layer_SquareWave;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MinVolume{ 0.001f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxVolume{ 1.0f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fading")
	float FadeCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fading")
	float FadeTime{ 3.0f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fading")
	bool bFadeInPercussive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fading")
	bool bFadeOutPercussive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fading")
	bool bFadeInAtmospheric;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fading")
	bool bFadeOutAtmospheric;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fading")
	bool bFadeInPiano;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fading")
	bool bFadeOutPiano;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fading")
	bool bFadeInBongos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fading")
	bool bFadeOutBongos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fading")
	bool bFadeInStrings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fading")
	bool bFadeOutStrings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fading")
	bool bFadeInSquareWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fading")
	bool bFadeOutSquareWave;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Start")
	bool bOnStartPercussive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Start")
	bool bOnStartAtmospheric;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Start")
	bool bOnStartPiano;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Start")
	bool bOnStartBongos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Start")
	bool bOnStartStrings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Start")
	bool bOnStartSquareWave;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void FadeInPercussive();

	UFUNCTION(BlueprintCallable)
	void FadeOutPercussive();

	UFUNCTION(BlueprintCallable)
	void FadeInAtmospheric();

	UFUNCTION(BlueprintCallable)
	void FadeOutAtmospheric();

	UFUNCTION(BlueprintCallable)
	void FadeInPiano();

	UFUNCTION(BlueprintCallable)
	void FadeOutPiano();

	UFUNCTION(BlueprintCallable)
	void FadeInBongos();

	UFUNCTION(BlueprintCallable)
	void FadeOutBongos();

	UFUNCTION(BlueprintCallable)
	void FadeInStrings();

	UFUNCTION(BlueprintCallable)
	void FadeOutStrings();

	UFUNCTION(BlueprintCallable)
	void FadeInSquareWave();

	UFUNCTION(BlueprintCallable)
	void FadeOutSquareWave();
};
