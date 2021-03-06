// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityFramework.h"
#include "AFAbilityInterface.h"
#include "AFEffectsComponent.h"
#include "AFEffectTask_EffectAppliedToSelf.h"




UAFEffectTask_EffectAppliedToSelf::UAFEffectTask_EffectAppliedToSelf(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UAFEffectTask_EffectAppliedToSelf* UAFEffectTask_EffectAppliedToSelf::ListenEffectAppliedToSelf(UObject* OwningExtension, FName TaskName, AActor* OptionalExternalTarget, bool OnlyTriggerOnce)
{
	auto MyObj = NewEffectTask<UAFEffectTask_EffectAppliedToSelf>(OwningExtension, TaskName);
	MyObj->SetExternalTarget(OptionalExternalTarget);
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	
	return MyObj;
}

void UAFEffectTask_EffectAppliedToSelf::Activate()
{
	UAFEffectsComponent* ASC = GetTargetASC();
	if (ASC)
	{
		MyHandle = ASC->OnAppliedToSelf.AddUObject(this, &UAFEffectTask_EffectAppliedToSelf::GameplayEventCallback);//AddExecuteEvent(Tag, Delegate);
	}

	Super::Activate();
}

void UAFEffectTask_EffectAppliedToSelf::GameplayEventCallback(FAFContextHandle Context
	, FAFPropertytHandle Property
	, FAFEffectSpecHandle Spec)
{
	//if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnEvent.Broadcast(Context, Property, Spec);
	}
	if (OnlyTriggerOnce)
	{
		EndTask();
	}
}

void UAFEffectTask_EffectAppliedToSelf::SetExternalTarget(AActor* Actor)
{
	if (Actor)
	{
		
		if (IAFAbilityInterface* interface = Cast<IAFAbilityInterface>(Actor))
		{
			UseExternalTarget = true;
			OptionalExternalTarget = interface->GetEffectsComponent();
		}
		
	}
}

UAFEffectsComponent* UAFEffectTask_EffectAppliedToSelf::GetTargetASC()
{
	if (UseExternalTarget)
	{
		return OptionalExternalTarget;
	}

	return EffectsComponent;
}

void UAFEffectTask_EffectAppliedToSelf::OnDestroy(bool AbilityEnding)
{
	UAFEffectsComponent* ASC = GetTargetASC();
	if (ASC && MyHandle.IsValid())
	{
		ASC->OnAppliedToSelf.Remove(MyHandle);
	}

	Super::OnDestroy(AbilityEnding);
}
