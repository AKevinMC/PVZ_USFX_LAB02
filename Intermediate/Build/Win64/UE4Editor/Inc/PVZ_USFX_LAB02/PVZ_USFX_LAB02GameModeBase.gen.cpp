// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PVZ_USFX_LAB02/PVZ_USFX_LAB02GameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePVZ_USFX_LAB02GameModeBase() {}
// Cross Module References
	PVZ_USFX_LAB02_API UClass* Z_Construct_UClass_APVZ_USFX_LAB02GameModeBase_NoRegister();
	PVZ_USFX_LAB02_API UClass* Z_Construct_UClass_APVZ_USFX_LAB02GameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_PVZ_USFX_LAB02();
// End Cross Module References
	void APVZ_USFX_LAB02GameModeBase::StaticRegisterNativesAPVZ_USFX_LAB02GameModeBase()
	{
	}
	UClass* Z_Construct_UClass_APVZ_USFX_LAB02GameModeBase_NoRegister()
	{
		return APVZ_USFX_LAB02GameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_APVZ_USFX_LAB02GameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_APVZ_USFX_LAB02GameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_PVZ_USFX_LAB02,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APVZ_USFX_LAB02GameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "PVZ_USFX_LAB02GameModeBase.h" },
		{ "ModuleRelativePath", "PVZ_USFX_LAB02GameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_APVZ_USFX_LAB02GameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APVZ_USFX_LAB02GameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_APVZ_USFX_LAB02GameModeBase_Statics::ClassParams = {
		&APVZ_USFX_LAB02GameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_APVZ_USFX_LAB02GameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_APVZ_USFX_LAB02GameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_APVZ_USFX_LAB02GameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_APVZ_USFX_LAB02GameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(APVZ_USFX_LAB02GameModeBase, 3298652829);
	template<> PVZ_USFX_LAB02_API UClass* StaticClass<APVZ_USFX_LAB02GameModeBase>()
	{
		return APVZ_USFX_LAB02GameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_APVZ_USFX_LAB02GameModeBase(Z_Construct_UClass_APVZ_USFX_LAB02GameModeBase, &APVZ_USFX_LAB02GameModeBase::StaticClass, TEXT("/Script/PVZ_USFX_LAB02"), TEXT("APVZ_USFX_LAB02GameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(APVZ_USFX_LAB02GameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
