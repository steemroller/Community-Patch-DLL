/*	-------------------------------------------------------------------------------------------------------
	� 1991-2012 Take-Two Interactive Software and its subsidiaries.  Developed by Firaxis Games.  
	Sid Meier's Civilization V, Civ, Civilization, 2K Games, Firaxis Games, Take-Two Interactive Software 
	and their respective logos are all trademarks of Take-Two interactive Software, Inc.  
	All other marks and trademarks are the property of their respective owners.  
	All rights reserved. 
	------------------------------------------------------------------------------------------------------- */
#include "CvGameCoreDLLPCH.h"
#include "CvGameCoreDLLUtil.h"
#include "ICvDLLUserInterface.h"
#include "CvGameCoreUtils.h"
#include "CvInfosSerializationHelper.h"
#include "CvBarbarians.h"

#include "LintFree.h"

//======================================================================================================
//					CvBeliefEntry
//======================================================================================================
/// Constructor
CvBeliefEntry::CvBeliefEntry() :
	m_iMinPopulation(0),
	m_iMinFollowers(0),
	m_iMaxDistance(0),
	m_iCityGrowthModifier(0),
	m_iFaithFromKills(0),
	m_iFaithFromDyingUnits(0),
	m_iRiverHappiness(0),
	m_iHappinessPerCity(0),
	m_iHappinessPerXPeacefulForeignFollowers(0),
	m_iPlotCultureCostModifier(0),
	m_iCityRangeStrikeModifier(0),
	m_iCombatModifierEnemyCities(0),
	m_iCombatModifierFriendlyCities(0),
	m_iFriendlyHealChange(0),
	m_iCityStateFriendshipModifier(0),
	m_iLandBarbarianConversionPercent(0),
	m_iWonderProductionModifier(0),
	m_iPlayerHappiness(0),
	m_iPlayerCultureModifier(0),
	m_fHappinessPerFollowingCity(0),
	m_iGoldPerFollowingCity(0),
	m_iGoldPerXFollowers(0),
	m_iGoldWhenCityAdopts(0),
	m_iSciencePerOtherReligionFollower(0),
	m_iSpreadDistanceModifier(0),
	m_iSpreadStrengthModifier(0),
	m_iProphetStrengthModifier(0),
	m_iProphetCostModifier(0),
	m_iMissionaryStrengthModifier(0),
	m_iMissionaryCostModifier(0),
	m_iFriendlyCityStateSpreadModifier(0),
	m_iGreatPersonExpendedFaith(0),
	m_iCityStateMinimumInfluence(0),
	m_iCityStateInfluenceModifier(0),
	m_iOtherReligionPressureErosion(0),
	m_iSpyPressure(0),
	m_iInquisitorPressureRetention(0),
	m_iFaithBuildingTourism(0),

	m_bPantheon(false),
	m_bFounder(false),
	m_bFollower(false),
	m_bEnhancer(false),
	m_bReformer(false),
	m_bRequiresPeace(false),
	m_bConvertsBarbarians(false),
	m_bFaithPurchaseAllGreatPeople(false),
#if defined(MOD_BALANCE_CORE_BELIEFS_RESOURCE)
	m_bRequiresImprovement(false),
	m_bRequiresResource(false),
	m_bRequiresNoImprovement(false),
	m_bRequiresNoImprovementFeature(false),
#endif

#if defined(MOD_BALANCE_CORE_BELIEFS)
	m_bIsHalvedFollowers(false),
	m_piYieldPerPop(NULL),
	m_piYieldPerGPT(NULL),
	m_piYieldPerLux(NULL),
	m_piYieldPerBorderGrowth(NULL),
	m_piYieldPerHeal(NULL),
	m_piYieldPerBirth(NULL),
	m_piYieldPerScience(NULL),
	m_piYieldFromGPUse(NULL),
	m_piYieldBonusGoldenAge(NULL),
	m_piYieldFromSpread(NULL),
	m_piYieldFromForeignSpread(NULL),
	m_piYieldFromConquest(NULL),
	m_piYieldFromPolicyUnlock(NULL),
	m_piYieldFromEraUnlock(NULL),
	m_piYieldFromConversion(NULL),
	m_piYieldFromWLTKD(NULL),
	m_piYieldFromProposal(NULL),
	m_piYieldFromHost(NULL),
	m_piYieldFromKnownPantheons(NULL),
	m_iCombatVersusOtherReligionOwnLands(0),
	m_iCombatVersusOtherReligionTheirLands(0),
	m_iMissionaryInfluenceCS(0),
	m_iHappinessPerPantheon(0),
	m_iExtraVotes(0),
	m_piMaxYieldPerFollower(NULL),
#endif
#if defined(MOD_BALANCE_CORE)
	m_eRequiredCivilization(NO_CIVILIZATION),
#endif

	m_eObsoleteEra(NO_ERA),
	m_eResourceRevealed(NO_RESOURCE),
	m_eSpreadModifierDoublingTech(NO_TECH),

	m_paiCityYieldChange(NULL),
	m_paiHolyCityYieldChange(NULL),
	m_paiYieldChangePerForeignCity(NULL),
	m_paiYieldChangePerXForeignFollowers(NULL),
#if defined(MOD_API_UNIFIED_YIELDS)
	m_piYieldPerFollowingCity(NULL),
	m_piYieldPerXFollowers(NULL),
	m_piYieldPerOtherReligionFollower(NULL),
#endif
	m_piResourceQuantityModifiers(NULL),
	m_ppiImprovementYieldChanges(NULL),
	m_ppiBuildingClassYieldChanges(NULL),
	m_paiBuildingClassHappiness(NULL),
	m_paiBuildingClassTourism(NULL),
	m_ppaiFeatureYieldChange(NULL),
#if defined(MOD_API_UNIFIED_YIELDS)
	m_ppiYieldPerXTerrain(NULL),
	m_ppiYieldPerXFeature(NULL),
	m_ppiCityYieldFromUnimprovedFeature(NULL),
	m_ppiUnimprovedFeatureYieldChanges(NULL),
	m_paiLakePlotYieldChange(NULL),
#endif
	m_ppaiResourceYieldChange(NULL),
	m_ppaiTerrainYieldChange(NULL),
#if defined(MOD_API_UNIFIED_YIELDS)
	m_ppiTradeRouteYieldChange(NULL),
	m_ppiSpecialistYieldChange(NULL),
	m_ppiGreatPersonExpendedYield(NULL),
	m_piGoldenAgeGreatPersonRateModifier(NULL),
	m_piCapitalYieldChange(NULL),
	m_piCoastalCityYieldChange(NULL),
	m_piGreatWorkYieldChange(NULL),
	m_piYieldFromKills(NULL),
	m_piYieldFromBarbarianKills(NULL),
#endif
#if defined(MOD_RELIGION_PLOT_YIELDS)
	m_ppiPlotYieldChange(NULL),
	m_pbFaithPurchaseUnitSpecificEnabled(NULL),
#endif
	m_piResourceHappiness(NULL),
	m_piYieldChangeAnySpecialist(NULL),
	m_piYieldChangeTradeRoute(NULL),
	m_piYieldChangeNaturalWonder(NULL),
	m_piYieldChangeWorldWonder(NULL),
	m_piYieldModifierNaturalWonder(NULL),
	m_piMaxYieldModifierPerFollower(NULL),
	m_pbFaithPurchaseUnitEraEnabled(NULL),
	m_pbBuildingClassEnabled(NULL)
{
}

/// Destructor
CvBeliefEntry::~CvBeliefEntry()
{
	CvDatabaseUtility::SafeDelete2DArray(m_ppiImprovementYieldChanges);
	CvDatabaseUtility::SafeDelete2DArray(m_ppiBuildingClassYieldChanges);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiFeatureYieldChange);
#if defined(MOD_API_UNIFIED_YIELDS)
	CvDatabaseUtility::SafeDelete2DArray(m_ppiYieldPerXTerrain);
	CvDatabaseUtility::SafeDelete2DArray(m_ppiYieldPerXFeature);
	CvDatabaseUtility::SafeDelete2DArray(m_ppiCityYieldFromUnimprovedFeature);
	CvDatabaseUtility::SafeDelete2DArray(m_ppiUnimprovedFeatureYieldChanges);
#endif
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiResourceYieldChange);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiTerrainYieldChange);
#if defined(MOD_API_UNIFIED_YIELDS)
	CvDatabaseUtility::SafeDelete2DArray(m_ppiTradeRouteYieldChange);
	CvDatabaseUtility::SafeDelete2DArray(m_ppiSpecialistYieldChange);
	CvDatabaseUtility::SafeDelete2DArray(m_ppiGreatPersonExpendedYield);
#endif
#if defined(MOD_RELIGION_PLOT_YIELDS)
	if (MOD_RELIGION_PLOT_YIELDS) {
		CvDatabaseUtility::SafeDelete2DArray(m_ppiPlotYieldChange);
	}
#endif
}

/// Accessor:: Minimum population in this city for belief to be active (0 = no such requirement)
int CvBeliefEntry::GetMinPopulation() const
{
	return m_iMinPopulation;
}

/// Accessor:: Minimum followers in this city for belief to be active (0 = no such requirement)
int CvBeliefEntry::GetMinFollowers() const
{
	return m_iMinFollowers;
}

/// Accessor:: Maximum distance from a city of this religion for belief to be active (0 = no such requirement)
int CvBeliefEntry::GetMaxDistance() const
{
	return m_iMaxDistance;
}

/// Accessor:: Modifier to city growth rate
int CvBeliefEntry::GetCityGrowthModifier() const
{
	return m_iCityGrowthModifier;
}

/// Accessor:: Percentage of enemy strength received in Faith for killing him
int CvBeliefEntry::GetFaithFromKills() const
{
	return m_iFaithFromKills;
}

/// Accessor:: Faith received when a friendly unit dies
int CvBeliefEntry::GetFaithFromDyingUnits() const
{
	return m_iFaithFromDyingUnits;
}

/// Accessor:: Happiness from each city settled on a river
int CvBeliefEntry::GetRiverHappiness() const
{
	return m_iRiverHappiness;
}

/// Accessor:: Happiness per every X population in a city
int CvBeliefEntry::GetHappinessPerCity() const
{
	return m_iHappinessPerCity;
}

/// Accessor:: Happiness per every X population in a foreign city
int CvBeliefEntry::GetHappinessPerXPeacefulForeignFollowers() const
{
	return m_iHappinessPerXPeacefulForeignFollowers;
}

/// Accessor:: Boost in speed of acquiring tiles through culture
int CvBeliefEntry::GetPlotCultureCostModifier() const
{
	return m_iPlotCultureCostModifier;
}

/// Accessor:: Boost in city strike strength
int CvBeliefEntry::GetCityRangeStrikeModifier() const
{
	return m_iCityRangeStrikeModifier;
}

/// Accessor:: Boost in combat near enemy cities of this religion
int CvBeliefEntry::GetCombatModifierEnemyCities() const
{
	return m_iCombatModifierEnemyCities;
}

/// Accessor:: Boost in combat near friendly cities of this religion
int CvBeliefEntry::GetCombatModifierFriendlyCities() const
{
	return m_iCombatModifierFriendlyCities;
}

/// Accessor:: Additional healing in friendly territory
int CvBeliefEntry::GetFriendlyHealChange() const
{
	return m_iFriendlyHealChange;
}

/// Accessor:: Boost in city state influence effectiveness
int CvBeliefEntry::GetCityStateFriendshipModifier() const
{
	return m_iCityStateFriendshipModifier;
}

/// Accessor:: Chance of converting a barbarian camp guard
int CvBeliefEntry::GetLandBarbarianConversionPercent() const
{
	return m_iLandBarbarianConversionPercent;
}

/// Accessor:: boost in production speed for wonders prior to obsolete era
int CvBeliefEntry::GetWonderProductionModifier() const
{
	return m_iWonderProductionModifier;
}

/// Accessor:: boost in production speed for wonders prior to obsolete era
int CvBeliefEntry::GetPlayerHappiness() const
{
	return m_iPlayerHappiness;
}

/// Accessor:: boost in production speed for wonders prior to obsolete era
int CvBeliefEntry::GetPlayerCultureModifier() const
{
	return m_iPlayerCultureModifier;
}

/// Accessor:: amount of extra happiness from each city following this religion
float CvBeliefEntry::GetHappinessPerFollowingCity() const
{
	return m_fHappinessPerFollowingCity;
}

/// Accessor:: amount of extra gold from each city following this religion
int CvBeliefEntry::GetGoldPerFollowingCity() const
{
	return m_iGoldPerFollowingCity;
}

/// Accessor:: amount of extra gold from each city following this religion
int CvBeliefEntry::GetGoldPerXFollowers() const
{
	return m_iGoldPerXFollowers;
}

/// Accessor:: amount of extra gold from each city following this religion
int CvBeliefEntry::GetGoldWhenCityAdopts() const
{
	return m_iGoldWhenCityAdopts;
}

/// Accessor:: amount of science for each follower of another religion in city spread to
int CvBeliefEntry::GetSciencePerOtherReligionFollower() const
{
	return m_iSciencePerOtherReligionFollower;
}

/// Accessor:: extra distance in city-to-city religion spread
int CvBeliefEntry::GetSpreadDistanceModifier() const
{
	return m_iSpreadDistanceModifier;
}

/// Accessor:: extra strength in city-to-city religion spread
int CvBeliefEntry::GetSpreadStrengthModifier() const
{
	return m_iSpreadStrengthModifier;
}

/// Accessor:: prophet conversion strength modifier
int CvBeliefEntry::GetProphetStrengthModifier() const
{
	return m_iProphetStrengthModifier;
}

/// Accessor:: prophet cost discount
int CvBeliefEntry::GetProphetCostModifier() const
{
	return m_iProphetCostModifier;
}

/// Accessor:: missionary conversion strength modifier
int CvBeliefEntry::GetMissionaryStrengthModifier() const
{
	return m_iMissionaryStrengthModifier;
}

/// Accessor:: missionary cost discount
int CvBeliefEntry::GetMissionaryCostModifier() const
{
	return m_iMissionaryCostModifier;
}

/// Accessor: speed increase of spread to friendly city states
int CvBeliefEntry::GetFriendlyCityStateSpreadModifier() const
{
	return m_iFriendlyCityStateSpreadModifier;
}

/// Accessor: faith earned for each GP expended
int CvBeliefEntry::GetGreatPersonExpendedFaith() const
{
	return m_iGreatPersonExpendedFaith;
}

/// Accessor: minimum influence with city states of a shared religion
int CvBeliefEntry::GetCityStateMinimumInfluence() const
{
	return m_iCityStateMinimumInfluence;
}

/// Accessor: modifier to influence boosts with city states
int CvBeliefEntry::GetCityStateInfluenceModifier() const
{
	return m_iCityStateInfluenceModifier;
}

/// Accessor: percentage of religious pressure gain that becomes a drop in pressure of other religions
int CvBeliefEntry::GetOtherReligionPressureErosion() const
{
	return m_iOtherReligionPressureErosion;
}

/// Accessor: base religious pressure (before speed multiplier) from having a spy in a city
int CvBeliefEntry::GetSpyPressure() const
{
	return m_iSpyPressure;
}

/// Accessor: percentage of religious pressure retained if one of your cities is hit with an Inquisitor
int CvBeliefEntry::GetInquisitorPressureRetention() const
{
	return m_iInquisitorPressureRetention;
}

/// Accessor: how much tourism can I get from Buildings bought with Faith?
int CvBeliefEntry::GetFaithBuildingTourism() const
{
	return m_iFaithBuildingTourism;
}

/// Accessor: is this a belief a pantheon can adopt
bool CvBeliefEntry::IsPantheonBelief() const
{
	return m_bPantheon;
}

/// Accessor: is this a belief a religion founder can adopt
bool CvBeliefEntry::IsFounderBelief() const
{
	return m_bFounder;
}

/// Accessor: is this a belief a religion follower can adopt
bool CvBeliefEntry::IsFollowerBelief() const
{
	return m_bFollower;
}

/// Accessor: is this a belief that enhances the spread of the religion
bool CvBeliefEntry::IsEnhancerBelief() const
{
	return m_bEnhancer;
}

/// Accessor: is this a belief that is added with the Reformation social policy
bool CvBeliefEntry::IsReformationBelief() const
{
	return m_bReformer;
}

/// Accessor: is this a belief that requires you to be at peace to benefit?
bool CvBeliefEntry::RequiresPeace() const
{
	return m_bRequiresPeace;
}

/// Accessor: is this a belief that allows your missionaries to convert adjacent barbarians?
bool CvBeliefEntry::ConvertsBarbarians() const
{
	return m_bConvertsBarbarians;
}

/// Accessor: is this a belief that allows you to purchase any type of Great Person with Faith?
bool CvBeliefEntry::FaithPurchaseAllGreatPeople() const
{
	return m_bFaithPurchaseAllGreatPeople;
}

#if defined(MOD_BALANCE_CORE_BELIEFS_RESOURCE)
/// Accessor: is this a belief that grants faith only from improvements?
bool CvBeliefEntry::RequiresImprovement() const
{
	return m_bRequiresImprovement;
}
/// Accessor: is this a belief that grants faith only from resources?
bool CvBeliefEntry::RequiresResource() const
{
	return m_bRequiresResource;
}
/// Accessor: is this a belief that grants faith only from no improvements?
bool CvBeliefEntry::RequiresNoImprovement() const
{
	return m_bRequiresNoImprovement;
}
/// Accessor: is this a belief that grants faith only from no improvements on a feature?
bool CvBeliefEntry::RequiresNoImprovementFeature() const
{
	return m_bRequiresNoImprovementFeature;
}
#endif

#if defined(MOD_BALANCE_CORE_BELIEFS)
/// Accessor: is this a belief that grants half follower belief yields?
bool CvBeliefEntry::IsHalvedFollowers() const
{
	return m_bIsHalvedFollowers;
}
/// Accessor:: Yield Per Pop
int CvBeliefEntry::GetYieldPerPop(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldPerPop ? m_piYieldPerPop[i] : -1;
}
/// Accessor:: Yield Per GPT
int CvBeliefEntry::GetYieldPerGPT(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldPerGPT ? m_piYieldPerGPT[i] : -1;
}
/// Accessor:: Yield Per Luxury
int CvBeliefEntry::GetYieldPerLux(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldPerLux ? m_piYieldPerLux[i] : -1;
}
/// Accessor:: Yield Per Border Growth
int CvBeliefEntry::GetYieldPerBorderGrowth (int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldPerBorderGrowth ? m_piYieldPerBorderGrowth[i] : -1;
}
/// Accessor:: Yield Per Heal
int CvBeliefEntry::GetYieldPerHeal (int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldPerHeal ? m_piYieldPerHeal[i] : -1;
}
/// Accessor:: Yield Per Birth
int CvBeliefEntry::GetYieldPerBirth(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldPerBirth ? m_piYieldPerBirth[i] : -1;
}

/// Accessor:: Yield Per Science
int CvBeliefEntry::GetYieldPerScience(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldPerScience ? m_piYieldPerScience[i] : -1;
}
/// Accessor:: Yield Per GP Use
int CvBeliefEntry::GetYieldFromGPUse(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromGPUse ? m_piYieldFromGPUse[i] : -1;
}
/// Accessor:: Yield Bonus GA
int CvBeliefEntry::GetYieldBonusGoldenAge(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldBonusGoldenAge ? m_piYieldBonusGoldenAge[i] : -1;
}
/// Accessor:: Yield From Spread
int CvBeliefEntry::GetYieldFromSpread(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromSpread ? m_piYieldFromSpread[i] : -1;
}
/// Accessor:: Yield From Foreign Spread
int CvBeliefEntry::GetYieldFromForeignSpread(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromForeignSpread ? m_piYieldFromForeignSpread[i] : -1;
}
/// Accessor:: Yield Conquest
int CvBeliefEntry::GetYieldFromConquest(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromConquest ? m_piYieldFromConquest[i] : -1;
}
/// Accessor:: Yield Policy Unlock
int CvBeliefEntry::GetYieldFromPolicyUnlock(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromPolicyUnlock ? m_piYieldFromPolicyUnlock[i] : -1;
}
/// Accessor:: Yield Era Unlock
int CvBeliefEntry::GetYieldFromEraUnlock(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromEraUnlock ? m_piYieldFromEraUnlock[i] : -1;
}
/// Accessor:: Yield from Conversion
int CvBeliefEntry::GetYieldFromConversion(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromConversion ? m_piYieldFromConversion[i] : -1;
}
/// Accessor:: Yield from WTLKD
int CvBeliefEntry::GetYieldFromWLTKD(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromWLTKD ? m_piYieldFromWLTKD[i] : -1;
}
/// Accessor:: Yield from Proposal
int CvBeliefEntry::GetYieldFromProposal(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromProposal ? m_piYieldFromProposal[i] : -1;
}
/// Accessor:: Yield from Vote
int CvBeliefEntry::GetYieldFromHost(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromHost ? m_piYieldFromHost[i] : -1;
}
/// Accessor:: Yield from Known Pantheons
int CvBeliefEntry::GetYieldFromKnownPantheons(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromKnownPantheons ? m_piYieldFromKnownPantheons[i] : -1;
}
/// Accessor:: Yield from Followers
int CvBeliefEntry::GetMaxYieldPerFollower(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piMaxYieldPerFollower ? m_piMaxYieldPerFollower[i] : -1;
}
/// Accessor: combat bonus v. other in own lands
int CvBeliefEntry::GetCombatVersusOtherReligionOwnLands() const
{
	return m_iCombatVersusOtherReligionOwnLands;
}
/// Accessor: combat bonus v. other in enemy lands
int CvBeliefEntry::GetCombatVersusOtherReligionTheirLands() const
{
	return m_iCombatVersusOtherReligionTheirLands;
}
/// Accessor: missionary CS influence
int CvBeliefEntry::GetMissionaryInfluenceCS() const
{
	return m_iMissionaryInfluenceCS;
}
/// Accessor: Happy per pantheon known
int CvBeliefEntry::GetHappinessPerPantheon() const
{
	return m_iHappinessPerPantheon;
}
/// Accessor: Extra votes from WC
int CvBeliefEntry::GetExtraVotes() const
{
	return m_iExtraVotes;
}
#endif
#if defined(MOD_BALANCE_CORE)
//------------------------------------------------------------------------------
CivilizationTypes CvBeliefEntry::GetRequiredCivilization() const
{
	return m_eRequiredCivilization;
}
#endif
/// Accessor: era when wonder production modifier goes obsolete
EraTypes CvBeliefEntry::GetObsoleteEra() const
{
	return m_eObsoleteEra;
}

/// Accessor:: resource revealed near this city
ResourceTypes CvBeliefEntry::GetResourceRevealed() const
{
	return m_eResourceRevealed;
}

/// Accessor:: technology that doubles the effect of the SpreadStrengthModifier
TechTypes CvBeliefEntry::GetSpreadModifierDoublingTech() const
{
	return m_eSpreadModifierDoublingTech;
}

/// Accessor:: Get brief text description
const char* CvBeliefEntry::getShortDescription() const
{
	return m_strShortDescription;
}

/// Accessor:: Set brief text description
void CvBeliefEntry::setShortDescription(const char* szVal)
{
	m_strShortDescription = szVal;
}
#if defined(MOD_BALANCE_CORE)
/// Accessor:: Get brief text description
const char* CvBeliefEntry::getTooltip() const
{
	return m_strTooltip;
}

/// Accessor:: Set brief text description
void CvBeliefEntry::setTooltip(const char* szVal)
{
	m_strTooltip = szVal;
}
#endif

/// Accessor:: Additional yield
int CvBeliefEntry::GetCityYieldChange(int i) const
{
	return m_paiCityYieldChange ? m_paiCityYieldChange[i] : -1;
}

/// Accessor:: Additional player-level yield for controlling holy city
int CvBeliefEntry::GetHolyCityYieldChange(int i) const
{
	return m_paiHolyCityYieldChange ? m_paiHolyCityYieldChange[i] : -1;
}

/// Accessor:: Additional player-level yield for each foreign city converted
int CvBeliefEntry::GetYieldChangePerForeignCity(int i) const
{
	return m_paiYieldChangePerForeignCity ? m_paiYieldChangePerForeignCity[i] : -1;
}

/// Accessor:: Additional player-level yield for followers in foreign cities
int CvBeliefEntry::GetYieldChangePerXForeignFollowers(int i) const
{
	return m_paiYieldChangePerXForeignFollowers ? m_paiYieldChangePerXForeignFollowers[i] : -1;
}

#if defined(MOD_API_UNIFIED_YIELDS)
int CvBeliefEntry::GetYieldPerFollowingCity(int i) const
{
	return m_piYieldPerFollowingCity ? m_piYieldPerFollowingCity[i] : 0;
}

int CvBeliefEntry::GetYieldPerXFollowers(int i) const
{
	return m_piYieldPerXFollowers ? m_piYieldPerXFollowers[i] : 0;
}

int CvBeliefEntry::GetYieldPerOtherReligionFollower(int i) const
{
	return m_piYieldPerOtherReligionFollower ? m_piYieldPerOtherReligionFollower[i] : 0;
}
#endif

/// Accessor:: Additional quantity of a specific resource
int CvBeliefEntry::GetResourceQuantityModifier(int i) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piResourceQuantityModifiers ? m_piResourceQuantityModifiers[i] : -1;
}

/// Accessor:: Extra yield from an improvement
int CvBeliefEntry::GetImprovementYieldChange(ImprovementTypes eIndex1, YieldTypes eIndex2) const
{
	CvAssertMsg(eIndex1 < GC.getNumImprovementInfos(), "Index out of bounds");
	CvAssertMsg(eIndex1 > -1, "Index out of bounds");
	CvAssertMsg(eIndex2 < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(eIndex2 > -1, "Index out of bounds");
	return m_ppiImprovementYieldChanges ? m_ppiImprovementYieldChanges[eIndex1][eIndex2] : 0;
}

/// Yield change for a specific BuildingClass by yield type
int CvBeliefEntry::GetBuildingClassYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumBuildingClassInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppiBuildingClassYieldChanges[i][j];
}

/// Amount of extra Happiness per turn a BuildingClass provides
int CvBeliefEntry::GetBuildingClassHappiness(int i) const
{
	CvAssertMsg(i < GC.getNumBuildingClassInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_paiBuildingClassHappiness ? m_paiBuildingClassHappiness[i] : -1;
}

/// Amount of extra Tourism per turn a BuildingClass provides
int CvBeliefEntry::GetBuildingClassTourism(int i) const
{
	CvAssertMsg(i < GC.getNumBuildingClassInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_paiBuildingClassTourism ? m_paiBuildingClassTourism[i] : -1;
}

/// Change to Feature yield by type
int CvBeliefEntry::GetFeatureYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumFeatureInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiFeatureYieldChange ? m_ppaiFeatureYieldChange[i][j] : -1;
}

#if defined(MOD_API_UNIFIED_YIELDS)
int CvBeliefEntry::GetYieldPerXTerrainTimes100(int i, int j) const
{
	CvAssertMsg(i < GC.getNumTerrainInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppiYieldPerXTerrain ? m_ppiYieldPerXTerrain[i][j] : 0;
}
int CvBeliefEntry::GetYieldPerXFeatureTimes100(int i, int j) const
{
	CvAssertMsg(i < GC.getNumFeatureInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppiYieldPerXFeature ? m_ppiYieldPerXFeature[i][j] : 0;
}
int CvBeliefEntry::GetCityYieldFromUnimprovedFeature(int i, int j) const
{
	CvAssertMsg(i < GC.getNumFeatureInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppiCityYieldFromUnimprovedFeature ? m_ppiCityYieldFromUnimprovedFeature[i][j] : 0;
}

int CvBeliefEntry::GetUnimprovedFeatureYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumFeatureInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppiUnimprovedFeatureYieldChanges ? m_ppiUnimprovedFeatureYieldChanges[i][j] : 0;
}
int CvBeliefEntry::GetLakePlotYieldChange(int i) const
{
	return m_paiLakePlotYieldChange ? m_paiLakePlotYieldChange[i] : 0;
}
#endif

/// Change to Resource yield by type
int CvBeliefEntry::GetResourceYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiResourceYieldChange ? m_ppaiResourceYieldChange[i][j] : -1;
}

/// Change to yield by terrain
int CvBeliefEntry::GetTerrainYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumTerrainInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiTerrainYieldChange ? m_ppaiTerrainYieldChange[i][j] : -1;
}

#if defined(MOD_API_UNIFIED_YIELDS)
int CvBeliefEntry::GetTradeRouteYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumDomainInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppiTradeRouteYieldChange ? m_ppiTradeRouteYieldChange[i][j] : 0;
}

int CvBeliefEntry::GetSpecialistYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumSpecialistInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppiSpecialistYieldChange ? m_ppiSpecialistYieldChange[i][j] : 0;
}

int CvBeliefEntry::GetGreatPersonExpendedYield(int i, int j) const
{
	CvAssertMsg(i < GC.getNumGreatPersonInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppiGreatPersonExpendedYield ? m_ppiGreatPersonExpendedYield[i][j] : 0;
}

int CvBeliefEntry::GetGoldenAgeGreatPersonRateModifier(int i) const
{
	CvAssertMsg(i < GC.getNumGreatPersonInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piGoldenAgeGreatPersonRateModifier ? m_piGoldenAgeGreatPersonRateModifier[i] : 0;
}

int CvBeliefEntry::GetCapitalYieldChange(int i) const
{
	return m_piCapitalYieldChange ? m_piCapitalYieldChange[i] : 0;
}

int CvBeliefEntry::GetCoastalCityYieldChange(int i) const
{
	return m_piCoastalCityYieldChange ? m_piCoastalCityYieldChange[i] : 0;
}

int CvBeliefEntry::GetGreatWorkYieldChange(int i) const
{
	return m_piGreatWorkYieldChange ? m_piGreatWorkYieldChange[i] : 0;
}

/// Do we get one of our yields from defeating an enemy?
int CvBeliefEntry::GetYieldFromKills(YieldTypes eYield) const
{
	CvAssertMsg((int)eYield < NUM_YIELD_TYPES, "Yield type out of bounds");
	CvAssertMsg((int)eYield > -1, "Index out of bounds");
	return m_piYieldFromKills[(int)eYield];
}

/// Do we get one of our yields from defeating a barbarian?
int CvBeliefEntry::GetYieldFromBarbarianKills(YieldTypes eYield) const
{
	CvAssertMsg((int)eYield < NUM_YIELD_TYPES, "Yield type out of bounds");
	CvAssertMsg((int)eYield > -1, "Index out of bounds");
	return m_piYieldFromBarbarianKills[(int)eYield];
}
#endif

#if defined(MOD_RELIGION_PLOT_YIELDS)
/// Change to yield by plot
int CvBeliefEntry::GetPlotYieldChange(int i, int j) const
{
	if (MOD_API_PLOT_YIELDS) {
		CvAssertMsg(i < GC.getNumPlotInfos(), "Index out of bounds");
		CvAssertMsg(i > -1, "Index out of bounds");
		CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
		CvAssertMsg(j > -1, "Index out of bounds");
		return m_ppiPlotYieldChange ? m_ppiPlotYieldChange[i][j] : -1;
	} else {
		return 0;
	}
}
#endif

/// Happiness from a resource
int CvBeliefEntry::GetResourceHappiness(int i) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piResourceHappiness ? m_piResourceHappiness[i] : -1;
}

/// Yield boost from having a specialist of any type in city
int CvBeliefEntry::GetYieldChangeAnySpecialist(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldChangeAnySpecialist ? m_piYieldChangeAnySpecialist[i] : -1;
}

/// Yield boost from a trade route
int CvBeliefEntry::GetYieldChangeTradeRoute(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldChangeTradeRoute ? m_piYieldChangeTradeRoute[i] : -1;
}

/// Yield boost from a natural wonder
int CvBeliefEntry::GetYieldChangeNaturalWonder(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldChangeNaturalWonder ? m_piYieldChangeNaturalWonder[i] : -1;
}

/// Yield boost from a world wonder
int CvBeliefEntry::GetYieldChangeWorldWonder(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldChangeWorldWonder ? m_piYieldChangeWorldWonder[i] : -1;
}

/// Yield percentage boost from a natural wonder
int CvBeliefEntry::GetYieldModifierNaturalWonder(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldModifierNaturalWonder ? m_piYieldModifierNaturalWonder[i] : -1;
}

/// Do we get a yield modifier 
int CvBeliefEntry::GetMaxYieldModifierPerFollower(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piMaxYieldModifierPerFollower ? m_piMaxYieldModifierPerFollower[i] : -1;
}

/// Can we buy units of this era with faith?
bool CvBeliefEntry::IsFaithUnitPurchaseEra(int i) const
{
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(i < GC.getNumEraInfos(), "Index out of bounds");
	return m_pbFaithPurchaseUnitEraEnabled ? m_pbFaithPurchaseUnitEraEnabled[i] : false;
}
#if defined(MOD_BALANCE_CORE)
/// Can we buy units of this type with faith?
bool CvBeliefEntry::IsFaithUnitPurchaseSpecific(int i) const
{
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(i < GC.getNumUnitInfos(), "Index out of bounds");
	return m_pbFaithPurchaseUnitSpecificEnabled ? m_pbFaithPurchaseUnitSpecificEnabled[i] : false;
}
#endif
/// Can we buy units of this era with faith?
bool CvBeliefEntry::IsBuildingClassEnabled(int i) const
{
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(i < GC.getNumBuildingClassInfos(), "Index out of bounds");
	return m_pbBuildingClassEnabled ? m_pbBuildingClassEnabled[i] : false;
}

/// Load XML data
bool CvBeliefEntry::CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility)
{
	if(!CvBaseInfo::CacheResults(kResults, kUtility))
		return false;

	//Basic Properties
	setShortDescription(kResults.GetText("ShortDescription"));
#if defined(MOD_BALANCE_CORE)
	setTooltip(kResults.GetText("Tooltip"));
#endif

	m_iMinPopulation                  = kResults.GetInt("MinPopulation");
	m_iMinFollowers                   = kResults.GetInt("MinFollowers");
	m_iMaxDistance					  = kResults.GetInt("MaxDistance");
	m_iCityGrowthModifier		      = kResults.GetInt("CityGrowthModifier");
	m_iFaithFromKills				  = kResults.GetInt("FaithFromKills");
	m_iFaithFromDyingUnits			  = kResults.GetInt("FaithFromDyingUnits");
	m_iRiverHappiness				  = kResults.GetInt("RiverHappiness");
	m_iHappinessPerCity				  = kResults.GetInt("HappinessPerCity");
	m_iHappinessPerXPeacefulForeignFollowers  = kResults.GetInt("HappinessPerXPeacefulForeignFollowers");
	m_iPlotCultureCostModifier	      = kResults.GetInt("PlotCultureCostModifier");
	m_iCityRangeStrikeModifier	      = kResults.GetInt("CityRangeStrikeModifier");
	m_iCombatModifierEnemyCities      = kResults.GetInt("CombatModifierEnemyCities");
	m_iCombatModifierFriendlyCities   = kResults.GetInt("CombatModifierFriendlyCities");
	m_iFriendlyHealChange	          = kResults.GetInt("FriendlyHealChange");
	m_iCityStateFriendshipModifier    = kResults.GetInt("CityStateFriendshipModifier");
	m_iLandBarbarianConversionPercent = kResults.GetInt("LandBarbarianConversionPercent");
	m_iWonderProductionModifier       = kResults.GetInt("WonderProductionModifier");
	m_iPlayerHappiness			      = kResults.GetInt("PlayerHappiness");
	m_iPlayerCultureModifier          = kResults.GetInt("PlayerCultureModifier");
	m_fHappinessPerFollowingCity      = kResults.GetFloat("HappinessPerFollowingCity");
	m_iGoldPerFollowingCity           = kResults.GetInt("GoldPerFollowingCity");
	m_iGoldPerXFollowers              = kResults.GetInt("GoldPerXFollowers");
	m_iGoldWhenCityAdopts             = kResults.GetInt("GoldPerFirstCityConversion");
	m_iSciencePerOtherReligionFollower= kResults.GetInt("SciencePerOtherReligionFollower");
	m_iSpreadDistanceModifier         = kResults.GetInt("SpreadDistanceModifier");
	m_iSpreadStrengthModifier		  = kResults.GetInt("SpreadStrengthModifier");
	m_iProphetStrengthModifier        = kResults.GetInt("ProphetStrengthModifier");
	m_iProphetCostModifier            = kResults.GetInt("ProphetCostModifier");
	m_iMissionaryStrengthModifier     = kResults.GetInt("MissionaryStrengthModifier");
	m_iMissionaryCostModifier         = kResults.GetInt("MissionaryCostModifier");
	m_iFriendlyCityStateSpreadModifier= kResults.GetInt("FriendlyCityStateSpreadModifier");
	m_iGreatPersonExpendedFaith       = kResults.GetInt("GreatPersonExpendedFaith");
	m_iCityStateMinimumInfluence      = kResults.GetInt("CityStateMinimumInfluence");
	m_iCityStateInfluenceModifier     = kResults.GetInt("CityStateInfluenceModifier");
	m_iOtherReligionPressureErosion   = kResults.GetInt("OtherReligionPressureErosion");
	m_iSpyPressure					  = kResults.GetInt("SpyPressure");
	m_iInquisitorPressureRetention    = kResults.GetInt("InquisitorPressureRetention");
	m_iFaithBuildingTourism           = kResults.GetInt("FaithBuildingTourism");

	m_bPantheon						  = kResults.GetBool("Pantheon");
	m_bFounder						  = kResults.GetBool("Founder");
	m_bFollower						  = kResults.GetBool("Follower");
	m_bEnhancer						  = kResults.GetBool("Enhancer");
	m_bReformer						  = kResults.GetBool("Reformation");
	m_bRequiresPeace				  = kResults.GetBool("RequiresPeace");
	m_bConvertsBarbarians			  = kResults.GetBool("ConvertsBarbarians");
	m_bFaithPurchaseAllGreatPeople	  = kResults.GetBool("FaithPurchaseAllGreatPeople");

#if defined(MOD_BALANCE_CORE_BELIEFS_RESOURCE)
	m_bRequiresImprovement			  = kResults.GetBool("RequiresImprovement");
	m_bRequiresResource				  = kResults.GetBool("RequiresResource");
	m_bRequiresNoImprovement		  = kResults.GetBool("RequiresNoImprovement");
	m_bRequiresNoImprovementFeature	  = kResults.GetBool("RequiresNoImprovementFeature");
#endif
#if defined(MOD_BALANCE_CORE_BELIEFS)
	m_bIsHalvedFollowers			  = kResults.GetBool("HalvedFollowers");
	m_iCombatVersusOtherReligionOwnLands = kResults.GetInt("CombatVersusOtherReligionOwnLands");
	m_iCombatVersusOtherReligionTheirLands = kResults.GetInt("CombatVersusOtherReligionTheirLands");
	m_iMissionaryInfluenceCS = kResults.GetInt("MissionaryInfluenceCS");
	m_iHappinessPerPantheon = kResults.GetInt("HappinessPerPantheon");
	m_iExtraVotes = kResults.GetInt("ExtraVotes");
#endif
#if defined(MOD_BALANCE_CORE)
	const char* szCivilizationType = kResults.GetText("CivilizationType");
	m_eRequiredCivilization = (CivilizationTypes)GC.getInfoTypeForString(szCivilizationType, true);
#endif
	//References
	const char* szTextVal;
	szTextVal						  = kResults.GetText("ObsoleteEra");
	m_eObsoleteEra					  = (EraTypes)GC.getInfoTypeForString(szTextVal, true);
	szTextVal						  = kResults.GetText("ResourceRevealed");
	m_eResourceRevealed				  = (ResourceTypes)GC.getInfoTypeForString(szTextVal, true);
	szTextVal						  = kResults.GetText("SpreadModifierDoublingTech");
	m_eSpreadModifierDoublingTech     = (TechTypes)GC.getInfoTypeForString(szTextVal, true);

	//Arrays
	const char* szBeliefType = GetType();
	kUtility.SetYields(m_paiCityYieldChange, "Belief_CityYieldChanges", "BeliefType", szBeliefType);
	kUtility.SetYields(m_paiHolyCityYieldChange, "Belief_HolyCityYieldChanges", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldChangeAnySpecialist, "Belief_YieldChangeAnySpecialist", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldChangeTradeRoute, "Belief_YieldChangeTradeRoute", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldChangeNaturalWonder, "Belief_YieldChangeNaturalWonder", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldChangeWorldWonder, "Belief_YieldChangeWorldWonder", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldModifierNaturalWonder, "Belief_YieldModifierNaturalWonder", "BeliefType", szBeliefType);
#if defined(MOD_BALANCE_CORE_BELIEFS)
	kUtility.SetYields(m_piYieldPerPop, "Belief_YieldPerPop", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldPerGPT, "Belief_YieldPerGPT", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldPerLux, "Belief_YieldPerLux", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldPerBorderGrowth, "Belief_YieldPerBorderGrowth", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldPerHeal, "Belief_YieldPerHeal", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldPerBirth, "Belief_YieldPerBirth", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldPerScience, "Belief_YieldPerScience", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldFromGPUse, "Belief_YieldFromGPUse", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldBonusGoldenAge, "Belief_YieldBonusGoldenAge", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldFromSpread, "Belief_YieldFromSpread", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldFromForeignSpread, "Belief_YieldFromForeignSpread", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldFromConquest, "Belief_YieldFromConquest", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldFromPolicyUnlock, "Belief_YieldFromPolicyUnlock", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldFromEraUnlock, "Belief_YieldFromEraUnlock", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldFromConversion, "Belief_YieldFromConversion", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldFromWLTKD, "Belief_YieldFromWLTKD", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldFromProposal, "Belief_YieldFromProposal", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldFromHost, "Belief_YieldFromHost", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldFromKnownPantheons, "Belief_YieldFromKnownPantheons", "BeliefType", szBeliefType);
	kUtility.PopulateArrayByValue(m_piMaxYieldPerFollower, "Yields", "Belief_MaxYieldPerFollower", "YieldType", "BeliefType", szBeliefType, "Max");
#endif
	kUtility.PopulateArrayByValue(m_piMaxYieldModifierPerFollower, "Yields", "Belief_MaxYieldModifierPerFollower", "YieldType", "BeliefType", szBeliefType, "Max");
	kUtility.PopulateArrayByValue(m_piResourceHappiness, "Resources", "Belief_ResourceHappiness", "ResourceType", "BeliefType", szBeliefType, "HappinessChange");
	kUtility.PopulateArrayByValue(m_piResourceQuantityModifiers, "Resources", "Belief_ResourceQuantityModifiers", "ResourceType", "BeliefType", szBeliefType, "ResourceQuantityModifier");
	kUtility.PopulateArrayByValue(m_paiBuildingClassHappiness, "BuildingClasses", "Belief_BuildingClassHappiness", "BuildingClassType", "BeliefType", szBeliefType, "Happiness");
	kUtility.PopulateArrayByValue(m_paiBuildingClassTourism, "BuildingClasses", "Belief_BuildingClassTourism", "BuildingClassType", "BeliefType", szBeliefType, "Tourism");
	kUtility.PopulateArrayByValue(m_paiYieldChangePerForeignCity, "Yields", "Belief_YieldChangePerForeignCity", "YieldType", "BeliefType", szBeliefType, "Yield");
	kUtility.PopulateArrayByValue(m_paiYieldChangePerXForeignFollowers, "Yields", "Belief_YieldChangePerXForeignFollowers", "YieldType", "BeliefType", szBeliefType, "ForeignFollowers");
#if defined(MOD_API_UNIFIED_YIELDS)
	kUtility.PopulateArrayByValue(m_piYieldPerFollowingCity, "Yields", "Belief_YieldPerFollowingCity", "YieldType", "BeliefType", szBeliefType, "Yield");
	kUtility.PopulateArrayByValue(m_piYieldPerXFollowers, "Yields", "Belief_YieldPerXFollowers", "YieldType", "BeliefType", szBeliefType, "PerXFollowers");
	kUtility.PopulateArrayByValue(m_piYieldPerOtherReligionFollower, "Yields", "Belief_YieldPerOtherReligionFollower", "YieldType", "BeliefType", szBeliefType, "Yield");
	kUtility.PopulateArrayByValue(m_paiLakePlotYieldChange, "Yields", "Belief_LakePlotYield", "YieldType", "BeliefType", szBeliefType, "Yield");	
	kUtility.PopulateArrayByExistence(m_pbFaithPurchaseUnitSpecificEnabled, "Units", "Belief_SpecificFaithUnitPurchase", "UnitType", "BeliefType", szBeliefType);
#endif
	kUtility.PopulateArrayByExistence(m_pbFaithPurchaseUnitEraEnabled, "Eras", "Belief_EraFaithUnitPurchase", "EraType", "BeliefType", szBeliefType);
	kUtility.PopulateArrayByExistence(m_pbBuildingClassEnabled, "BuildingClasses", "Belief_BuildingClassFaithPurchase", "BuildingClassType", "BeliefType", szBeliefType);

	//ImprovementYieldChanges
	{
		kUtility.Initialize2DArray(m_ppiImprovementYieldChanges, "Improvements", "Yields");

		std::string strKey("Belief_ImprovementYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Improvements.ID as ImprovementID, Yields.ID as YieldID, Yield from Belief_ImprovementYieldChanges inner join Improvements on Improvements.Type = ImprovementType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int ImprovementID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppiImprovementYieldChanges[ImprovementID][YieldID] = yield;
		}
	}

	//BuildingClassYieldChanges
	{
		kUtility.Initialize2DArray(m_ppiBuildingClassYieldChanges, "BuildingClasses", "Yields");

		std::string strKey("Belief_BuildingClassYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select BuildingClasses.ID as BuildingClassID, Yields.ID as YieldID, YieldChange from Belief_BuildingClassYieldChanges inner join BuildingClasses on BuildingClasses.Type = BuildingClassType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int BuildingClassID = pResults->GetInt(0);
			const int iYieldID = pResults->GetInt(1);
			const int iYieldChange = pResults->GetInt(2);

			m_ppiBuildingClassYieldChanges[BuildingClassID][iYieldID] = iYieldChange;
		}
	}

	//FeatureYieldChanges
	{
		kUtility.Initialize2DArray(m_ppaiFeatureYieldChange, "Features", "Yields");

		std::string strKey("Belief_FeatureYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Features.ID as FeatureID, Yields.ID as YieldID, Yield from Belief_FeatureYieldChanges inner join Features on Features.Type = FeatureType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int FeatureID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiFeatureYieldChange[FeatureID][YieldID] = yield;
		}
	}

#if defined(MOD_API_UNIFIED_YIELDS)
	//CityYieldPerXTerrain
	if (MOD_API_UNIFIED_YIELDS) {
		kUtility.Initialize2DArray(m_ppiYieldPerXTerrain, "Terrains", "Yields");

		std::string strKey("Belief_CityYieldPerXTerrainTimes100");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Terrains.ID as TerrainID, Yields.ID as YieldID, Yield from Belief_CityYieldPerXTerrainTimes100 inner join Terrains on Terrains.Type = TerrainType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int TerrainID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppiYieldPerXTerrain[TerrainID][YieldID] = yield;
		}
	}
	//CityYieldPerXFeature
	if (MOD_API_UNIFIED_YIELDS) {
		kUtility.Initialize2DArray(m_ppiYieldPerXFeature, "Features", "Yields");

		std::string strKey("Belief_CityYieldPerXFeatureTimes100");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Features.ID as FeatureID, Yields.ID as YieldID, Yield from Belief_CityYieldPerXFeatureTimes100 inner join Features on Features.Type = FeatureType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int FeatureID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppiYieldPerXFeature[FeatureID][YieldID] = yield;
		}
	}
	//CityYieldFromUnimprovedFeature
	if (MOD_API_UNIFIED_YIELDS) {
		kUtility.Initialize2DArray(m_ppiCityYieldFromUnimprovedFeature, "Features", "Yields");

		std::string strKey("Belief_CityYieldFromUnimprovedFeature");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Features.ID as FeatureID, Yields.ID as YieldID, Yield from Belief_CityYieldFromUnimprovedFeature inner join Features on Features.Type = FeatureType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int FeatureID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppiCityYieldFromUnimprovedFeature[FeatureID][YieldID] = yield;
		}
	}

	//UnimprovedFeatureYieldChanges
	if (MOD_API_UNIFIED_YIELDS) {
		kUtility.Initialize2DArray(m_ppiUnimprovedFeatureYieldChanges, "Features", "Yields");

		std::string strKey("Belief_UnimprovedFeatureYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Features.ID as FeatureID, Yields.ID as YieldID, Yield from Belief_UnimprovedFeatureYieldChanges inner join Features on Features.Type = FeatureType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int FeatureID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppiUnimprovedFeatureYieldChanges[FeatureID][YieldID] = yield;
		}
	}
#endif

	//ResourceYieldChanges
	{
		kUtility.Initialize2DArray(m_ppaiResourceYieldChange, "Resources", "Yields");

		std::string strKey("Belief_ResourceYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Resources.ID as ResourceID, Yields.ID as YieldID, Yield from Belief_ResourceYieldChanges inner join Resources on Resources.Type = ResourceType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int ResourceID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiResourceYieldChange[ResourceID][YieldID] = yield;
		}
	}

	//TerrainYieldChanges
	{
		kUtility.Initialize2DArray(m_ppaiTerrainYieldChange, "Terrains", "Yields");

		std::string strKey("Belief_TerrainYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Terrains.ID as TerrainID, Yields.ID as YieldID, Yield from Belief_TerrainYieldChanges inner join Terrains on Terrains.Type = TerrainType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int TerrainID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiTerrainYieldChange[TerrainID][YieldID] = yield;
		}
	}
	
#if defined(MOD_API_UNIFIED_YIELDS)
	//TradeRouteYieldChange
	if (MOD_API_UNIFIED_YIELDS) {
		kUtility.Initialize2DArray(m_ppiTradeRouteYieldChange, "Domains", "Yields");

		std::string strKey("Belief_TradeRouteYieldChange");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Domains.ID as DomainID, Yields.ID as YieldID, Yield from Belief_TradeRouteYieldChange inner join Domains on Domains.Type = DomainType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int DomainID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppiTradeRouteYieldChange[DomainID][YieldID] = yield;
		}
	}
	
	//SpecialistYieldChanges
	if (MOD_API_UNIFIED_YIELDS) {
		kUtility.Initialize2DArray(m_ppiSpecialistYieldChange, "Specialists", "Yields");

		std::string strKey("Belief_SpecialistYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Specialists.ID as SpecialistID, Yields.ID as YieldID, Yield from Belief_SpecialistYieldChanges inner join Specialists on Specialists.Type = SpecialistType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int SpecialistID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppiSpecialistYieldChange[SpecialistID][YieldID] = yield;
		}
	}
	
	//GreatPersonExpendedYield
	if (MOD_API_UNIFIED_YIELDS) {
		kUtility.Initialize2DArray(m_ppiGreatPersonExpendedYield, "GreatPersons", "Yields");

		std::string strKey("Belief_GreatPersonExpendedYield");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select GreatPersons.ID as GreatPersonID, Yields.ID as YieldID, Yield from Belief_GreatPersonExpendedYield inner join GreatPersons on GreatPersons.Type = GreatPersonType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int GreatPersonID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppiGreatPersonExpendedYield[GreatPersonID][YieldID] = yield;
		}
	}
	
	kUtility.PopulateArrayByValue(m_piGoldenAgeGreatPersonRateModifier, "GreatPersons", "Belief_GoldenAgeGreatPersonRateModifier", "GreatPersonType", "BeliefType", szBeliefType, "Modifier");
	kUtility.SetYields(m_piCapitalYieldChange, "Belief_CapitalYieldChanges", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piCoastalCityYieldChange, "Belief_CoastalCityYieldChanges", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piGreatWorkYieldChange, "Belief_GreatWorkYieldChanges", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldFromKills, "Belief_YieldFromKills", "BeliefType", szBeliefType);
	kUtility.SetYields(m_piYieldFromBarbarianKills, "Belief_YieldFromBarbarianKills", "BeliefType", szBeliefType);
#endif

#if defined(MOD_RELIGION_PLOT_YIELDS)
	if (MOD_RELIGION_PLOT_YIELDS)
	//PlotYieldChanges
	{
		kUtility.Initialize2DArray(m_ppiPlotYieldChange, "Plots", "Yields");

		std::string strKey("Belief_PlotYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Plots.ID as PlotID, Yields.ID as YieldID, Yield from Belief_PlotYieldChanges inner join Plots on Plots.Type = PlotType inner join Yields on Yields.Type = YieldType where BeliefType = ?");
		}

		pResults->Bind(1, szBeliefType);

		while(pResults->Step())
		{
			const int PlotID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppiPlotYieldChange[PlotID][YieldID] = yield;
		}
	}
#endif

	return true;
}

//=====================================
// CvBeliefXMLEntries
//=====================================
/// Constructor
CvBeliefXMLEntries::CvBeliefXMLEntries(void)
{

}

/// Destructor
CvBeliefXMLEntries::~CvBeliefXMLEntries(void)
{
	DeleteArray();
}

/// Returns vector of belief entries
std::vector<CvBeliefEntry*>& CvBeliefXMLEntries::GetBeliefEntries()
{
	return m_paBeliefEntries;
}

/// Number of defined beliefs
int CvBeliefXMLEntries::GetNumBeliefs()
{
	return m_paBeliefEntries.size();
}

/// Clear belief entries
void CvBeliefXMLEntries::DeleteArray()
{
	for(std::vector<CvBeliefEntry*>::iterator it = m_paBeliefEntries.begin(); it != m_paBeliefEntries.end(); ++it)
	{
		SAFE_DELETE(*it);
	}

	m_paBeliefEntries.clear();
}

/// Get a specific entry
CvBeliefEntry* CvBeliefXMLEntries::GetEntry(int index)
{
#if defined(MOD_BALANCE_CORE)
	return (index!=NO_BELIEF) ? m_paBeliefEntries[index] : NULL;
#else
	return m_paBeliefEntries[index];
#endif
}

//=====================================
// CvReligionBeliefs
//=====================================
/// Constructor
CvReligionBeliefs::CvReligionBeliefs():
	m_paiBuildingClassEnabled(NULL)
{
	Reset();
}

/// Destructor
CvReligionBeliefs::~CvReligionBeliefs(void)
{
	Uninit();
}

/// Copy Constructor with typical parameters
CvReligionBeliefs::CvReligionBeliefs(const CvReligionBeliefs& source)
{
	m_ReligionBeliefs = source.m_ReligionBeliefs;
#if defined(MOD_BALANCE_CORE)
	m_BeliefLookup = source.m_BeliefLookup;
	m_eReligion = source.m_eReligion;
#endif

	m_paiBuildingClassEnabled = FNEW(int[GC.getNumBuildingClassInfos()], c_eCiv5GameplayDLL, 0);
	for(int iI = 0; iI < GC.getNumBuildingClassInfos(); iI++)
	{
		CvBuildingClassInfo* pkBuildingClassInfo = GC.getBuildingClassInfo((BuildingClassTypes)iI);
		if(!pkBuildingClassInfo)
		{
			continue;
		}

		m_paiBuildingClassEnabled[iI] = source.m_paiBuildingClassEnabled[iI];
	}
}

/// Deallocate memory created in initialize
void CvReligionBeliefs::Uninit()
{
	SAFE_DELETE_ARRAY(m_paiBuildingClassEnabled);
}

/// Reset data members
void CvReligionBeliefs::Reset()
{
#if !defined(MOD_BALANCE_CORE_BELIEFS)
	m_iFaithFromDyingUnits = 0;
	m_iRiverHappiness = 0;
	m_iPlotCultureCostModifier = 0;
	m_iCityRangeStrikeModifier = 0;
	m_iCombatModifierEnemyCities = 0;
	m_iCombatModifierFriendlyCities = 0;
	m_iFriendlyHealChange = 0;
	m_iCityStateFriendshipModifier = 0;
	m_iLandBarbarianConversionPercent = 0;
	m_iSpreadDistanceModifier = 0;
	m_iSpreadStrengthModifier = 0;
	m_iProphetStrengthModifier = 0;
	m_iProphetCostModifier = 0;
	m_iMissionaryStrengthModifier = 0;
	m_iMissionaryCostModifier = 0;
	m_iFriendlyCityStateSpreadModifier = 0;
	m_iGreatPersonExpendedFaith = 0;
	m_iCityStateMinimumInfluence = 0;
	m_iCityStateInfluenceModifier = 0;
	m_iOtherReligionPressureErosion = 0;
	m_iSpyPressure = 0;
	m_iInquisitorPressureRetention = 0;
	m_iFaithBuildingTourism = 0;

#if defined(MOD_BALANCE_CORE_BELIEFS)
	m_iCombatVersusOtherReligionOwnLands = 0;
	m_iCombatVersusOtherReligionTheirLands = 0;
	m_iMissionaryInfluenceCS = 0;
	m_iHappinessPerPantheon = 0;
	m_iExtraVotes = 0;
#endif
#if defined(MOD_BALANCE_CORE)
	m_eRequiredCivilization = NO_CIVILIZATION;
#endif

	m_eObsoleteEra = NO_ERA;
	m_eResourceRevealed = NO_RESOURCE;
	m_eSpreadModifierDoublingTech = NO_TECH;
#endif

	m_ReligionBeliefs.clear();
#if defined(MOD_BALANCE_CORE)
	m_eReligion = NO_RELIGION;
	m_BeliefLookup = std::vector<int>(GC.GetGameBeliefs()->GetNumBeliefs(),0);
#endif

	m_paiBuildingClassEnabled = FNEW(int[GC.getNumBuildingClassInfos()], c_eCiv5GameplayDLL, 0);
	for(int iI = 0; iI < GC.getNumBuildingClassInfos(); iI++)
	{
		CvBuildingClassInfo* pkBuildingClassInfo = GC.getBuildingClassInfo((BuildingClassTypes)iI);
		if(!pkBuildingClassInfo)
		{
			continue;
		}

		m_paiBuildingClassEnabled[iI] = 0;
	}
}
#if defined(MOD_BALANCE_CORE)
void CvReligionBeliefs::SetReligion(ReligionTypes eReligion)
{
	m_eReligion = eReligion;
}
ReligionTypes CvReligionBeliefs::GetReligion() const
{
	return m_eReligion;
}
#endif
/// Store off data on bonuses from beliefs
void CvReligionBeliefs::AddBelief(BeliefTypes eBelief)
{
	CvAssert(eBelief != NO_BELIEF);
	if(eBelief == NO_BELIEF)
		return;

	CvBeliefEntry* belief = GC.GetGameBeliefs()->GetEntry(eBelief);
	CvAssert(belief != NULL);
	if(belief == NULL)
		return;
#if !defined(MOD_BALANCE_CORE_BELIEFS)
	m_iFaithFromDyingUnits += belief->GetFaithFromDyingUnits();
	m_iRiverHappiness += belief->GetRiverHappiness();
	m_iPlotCultureCostModifier += belief->GetPlotCultureCostModifier();
	m_iCityRangeStrikeModifier += belief->GetCityRangeStrikeModifier();
	m_iCombatModifierEnemyCities += belief->GetCombatModifierEnemyCities();
	m_iCombatModifierFriendlyCities += belief->GetCombatModifierFriendlyCities();
	m_iFriendlyHealChange += belief->GetFriendlyHealChange();
	m_iCityStateFriendshipModifier += belief->GetCityStateFriendshipModifier();
	m_iLandBarbarianConversionPercent += belief->GetLandBarbarianConversionPercent();
	m_iSpreadDistanceModifier += belief->GetSpreadDistanceModifier();
	m_iSpreadStrengthModifier += belief->GetSpreadStrengthModifier();
	m_iProphetStrengthModifier += belief->GetProphetStrengthModifier();
	m_iProphetCostModifier += belief->GetProphetCostModifier();
	m_iMissionaryStrengthModifier += belief->GetMissionaryStrengthModifier();
	m_iMissionaryCostModifier += belief->GetMissionaryCostModifier();
	m_iFriendlyCityStateSpreadModifier += belief->GetFriendlyCityStateSpreadModifier();
	m_iGreatPersonExpendedFaith += belief->GetGreatPersonExpendedFaith();
	m_iCityStateMinimumInfluence += belief->GetCityStateMinimumInfluence();
	m_iCityStateInfluenceModifier += belief->GetCityStateInfluenceModifier();
	m_iOtherReligionPressureErosion += belief->GetOtherReligionPressureErosion();
	m_iSpyPressure += belief->GetSpyPressure();
	m_iInquisitorPressureRetention += belief->GetInquisitorPressureRetention();
	m_iFaithBuildingTourism += belief->GetFaithBuildingTourism();
#if defined(MOD_BALANCE_CORE_BELIEFS)
	m_iCombatVersusOtherReligionOwnLands += belief->GetCombatVersusOtherReligionOwnLands();
	m_iCombatVersusOtherReligionTheirLands += belief->GetCombatVersusOtherReligionTheirLands();
	m_iMissionaryInfluenceCS += belief->GetMissionaryInfluenceCS();
	m_iHappinessPerPantheon += belief->GetHappinessPerPantheon();
	m_iExtraVotes += belief->GetExtraVotes();
#endif
#if defined(MOD_BALANCE_CORE)
	m_eRequiredCivilization = belief->GetRequiredCivilization();
#endif

	m_eObsoleteEra = belief->GetObsoleteEra();
	m_eResourceRevealed = belief->GetResourceRevealed();
#endif
	for (int iI = 0; iI < GC.getNumBuildingClassInfos(); iI++)
	{
		if (belief->IsBuildingClassEnabled(iI))
		{
			m_paiBuildingClassEnabled[iI]++;
		}
	}
#if !defined(MOD_BALANCE_CORE_BELIEFS)
	if(belief->GetSpreadModifierDoublingTech() != NO_TECH)
	{
		m_eSpreadModifierDoublingTech = belief->GetSpreadModifierDoublingTech();
	}
#endif

	m_ReligionBeliefs.push_back((int)eBelief);
#if defined(MOD_BALANCE_CORE)
	m_BeliefLookup[(int)(eBelief)] = 1;
#endif
}

/// Does this religion possess a specific belief?
bool CvReligionBeliefs::HasBelief(BeliefTypes eBelief) const
{
#if defined(MOD_BALANCE_CORE)
	if (eBelief==NO_BELIEF)
		return m_ReligionBeliefs.empty();

	return m_BeliefLookup[(int)(eBelief)]==1;
#else
	return (find(m_ReligionBeliefs.begin(), m_ReligionBeliefs.end(), (int)eBelief) != m_ReligionBeliefs.end());
#endif
}

/// Does this religion possess a specific belief?
BeliefTypes CvReligionBeliefs::GetBelief(int iIndex) const
{
	return (BeliefTypes)m_ReligionBeliefs[iIndex];
}

/// Does this religion possess a specific belief?
int CvReligionBeliefs::GetNumBeliefs() const
{
	return m_ReligionBeliefs.size();
}
#if defined(MOD_BALANCE_CORE)
bool CvReligionBeliefs::IsBeliefValid(BeliefTypes eBelief, ReligionTypes eReligion, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	if(ePlayer != NO_PLAYER)
	{
		if(eReligion != NO_RELIGION && (pBeliefs->GetEntry(eBelief)->IsFounderBelief() || pBeliefs->GetEntry(eBelief)->IsReformationBelief()))
		{
			if(!GC.getGame().GetGameReligions()->IsEligibleForFounderBenefits(eReligion, ePlayer))
			{	
				return false;
			}
			if(pCity != NULL && !pCity->GetCityReligions()->IsHolyCityForReligion(eReligion))
			{
				return false;
			}
		}
		if(eReligion != NO_RELIGION && pBeliefs->GetEntry(eBelief)->IsEnhancerBelief())
		{
			if(pCity != NULL && !pCity->GetCityReligions()->IsHolyCityForReligion(eReligion))
			{
				return false;
			}
		}
		if(pBeliefs->GetEntry(eBelief)->IsPantheonBelief())
		{
			if(pCity != NULL && !pCity->isCapital())
			{
				return false;
			}
		}
	}
	return true;
}
#endif
int CvReligionBeliefs::GetFaithFromDyingUnits(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetFaithFromDyingUnits();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetRiverHappiness(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetRiverHappiness();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetPlotCultureCostModifier(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetPlotCultureCostModifier();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetCityRangeStrikeModifier(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetCityRangeStrikeModifier();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetCombatModifierEnemyCities(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetCombatModifierEnemyCities();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetCombatModifierFriendlyCities(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetCombatModifierFriendlyCities();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetFriendlyHealChange(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetFriendlyHealChange();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetCityStateFriendshipModifier(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetCityStateFriendshipModifier();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetLandBarbarianConversionPercent(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetLandBarbarianConversionPercent();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetSpreadDistanceModifier(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetSpreadDistanceModifier();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetSpreadStrengthModifier(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetSpreadStrengthModifier();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetProphetStrengthModifier(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetProphetStrengthModifier();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetProphetCostModifier(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetProphetCostModifier();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetMissionaryStrengthModifier(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetMissionaryStrengthModifier();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetMissionaryCostModifier(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetMissionaryCostModifier();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetFriendlyCityStateSpreadModifier(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetFriendlyCityStateSpreadModifier();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetGreatPersonExpendedFaith(PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetGreatPersonExpendedFaith();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetCityStateMinimumInfluence(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetCityStateMinimumInfluence();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetCityStateInfluenceModifier(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetCityStateInfluenceModifier();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetOtherReligionPressureErosion(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetOtherReligionPressureErosion();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetSpyPressure(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetSpyPressure();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetInquisitorPressureRetention(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetInquisitorPressureRetention();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetFaithBuildingTourism(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetFaithBuildingTourism();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetCombatVersusOtherReligionOwnLands(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetCombatVersusOtherReligionOwnLands();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetCombatVersusOtherReligionTheirLands(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetCombatVersusOtherReligionTheirLands();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetMissionaryInfluenceCS(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetMissionaryInfluenceCS();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetHappinessPerPantheon(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;


	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetHappinessPerPantheon();
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetExtraVotes(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetExtraVotes();
		}
	}

	return rtnValue;
}
EraTypes CvReligionBeliefs::GetObsoleteEra(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();

	EraTypes eEra = NO_ERA;
	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			eEra = pBeliefs->GetEntry(*it)->GetObsoleteEra();
			break;
		}
	}

	return eEra;
}
ResourceTypes CvReligionBeliefs::GetResourceRevealed(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	ResourceTypes eResource = NO_RESOURCE;
	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			eResource = pBeliefs->GetEntry(*it)->GetResourceRevealed();
			break;
		}
	}

	return eResource;
}
TechTypes CvReligionBeliefs::GetSpreadModifierDoublingTech(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();

	TechTypes eTech = NO_TECH;
	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			eTech = pBeliefs->GetEntry(*it)->GetSpreadModifierDoublingTech();
			break;
		}
	}

	return eTech;
}
/// Faith from kills
int CvReligionBeliefs::GetFaithFromKills(int iDistance, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;
	int iRequiredDistance;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			iRequiredDistance = pBeliefs->GetEntry(*it)->GetMaxDistance();
			if(iRequiredDistance == 0 || iDistance <= iRequiredDistance)
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetFaithFromKills();
			}
		}
	}

	return rtnValue;
}

/// Happiness per city
int CvReligionBeliefs::GetHappinessPerCity(int iPopulation, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if(iPopulation >= pBeliefs->GetEntry(*it)->GetMinPopulation())
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetHappinessPerCity();
			}
		}
	}

	return rtnValue;
}

/// Happiness per X followers in foreign cities of powers you are not at war with
int CvReligionBeliefs::GetHappinessPerXPeacefulForeignFollowers(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer) && pBeliefs->GetEntry(*it)->GetHappinessPerXPeacefulForeignFollowers() > 0)
		{
			return pBeliefs->GetEntry(*it)->GetHappinessPerXPeacefulForeignFollowers();
		}
	}

	return 0;
}

/// Wonder production boost
int CvReligionBeliefs:: GetWonderProductionModifier(EraTypes eWonderEra, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if((int)eWonderEra < (int)pBeliefs->GetEntry(*it)->GetObsoleteEra())
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetWonderProductionModifier();
			}
		}
	}

	return rtnValue;
}

/// Player happiness boost
int CvReligionBeliefs:: GetPlayerHappiness(bool bAtPeace, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if(bAtPeace || !pBeliefs->GetEntry(*it)->RequiresPeace())
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetPlayerHappiness();
			}
		}
	}

	return rtnValue;
}

/// Player culture modifier
int CvReligionBeliefs:: GetPlayerCultureModifier(bool bAtPeace, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if(bAtPeace || !pBeliefs->GetEntry(*it)->RequiresPeace())
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetPlayerCultureModifier();
			}
		}
	}

	return rtnValue;
}

/// Happiness per following city
float CvReligionBeliefs:: GetHappinessPerFollowingCity(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	float rtnValue = 0.0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetHappinessPerFollowingCity();
		}
	}

	return rtnValue;
}

/// Gold per following city
int CvReligionBeliefs:: GetGoldPerFollowingCity(PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetGoldPerFollowingCity();
		}
	}

	return rtnValue;
}

/// Gold per following city
int CvReligionBeliefs:: GetGoldPerXFollowers(PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetGoldPerXFollowers();
		}
	}

	return rtnValue;
}

/// Gold per following city
int CvReligionBeliefs:: GetGoldWhenCityAdopts(PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetGoldWhenCityAdopts();
		}
	}

	return rtnValue;
}

/// Science per other religion follower
int CvReligionBeliefs:: GetSciencePerOtherReligionFollower(PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetSciencePerOtherReligionFollower();
		}
	}

	return rtnValue;
}

/// City growth modifier
int CvReligionBeliefs::GetCityGrowthModifier(bool bAtPeace, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if(bAtPeace || !pBeliefs->GetEntry(*it)->RequiresPeace())
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetCityGrowthModifier();
			}
		}
	}

	return rtnValue;
}

/// Extra yield
int CvReligionBeliefs::GetCityYieldChange(int iPopulation, YieldTypes eYield, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if(iPopulation >= pBeliefs->GetEntry(*it)->GetMinPopulation())
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetCityYieldChange(eYield);
			}
		}
	}

	return rtnValue;
}

/// Extra holy city yield
int CvReligionBeliefs::GetHolyCityYieldChange (YieldTypes eYield, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			if(pCity->GetCityReligions()->IsHolyCityForReligion(GetReligion()))
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetHolyCityYieldChange(eYield);
			}
		}
	}

	return rtnValue;
}

/// Extra yield for foreign cities following religion
int CvReligionBeliefs::GetYieldChangePerForeignCity(YieldTypes eYield, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldChangePerForeignCity(eYield);
		}
	}

	return rtnValue;
}

/// Extra yield for foreign followers
int CvReligionBeliefs::GetYieldChangePerXForeignFollowers(YieldTypes eYield, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldChangePerXForeignFollowers(eYield);
		}
	}

	return rtnValue;
}

#if defined(MOD_API_UNIFIED_YIELDS)
int CvReligionBeliefs::GetYieldPerFollowingCity(YieldTypes eYield, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldPerFollowingCity(eYield);
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetLakePlotYieldChange(YieldTypes eYield, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetLakePlotYieldChange(eYield);
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetYieldPerXFollowers(YieldTypes eYield, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldPerXFollowers(eYield);
		}
	}

	return rtnValue;
}

int CvReligionBeliefs::GetYieldPerOtherReligionFollower(YieldTypes eYield, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldPerOtherReligionFollower(eYield);
		}
	}

	return rtnValue;
}
#endif

/// Extra yield from this improvement
int CvReligionBeliefs::GetResourceQuantityModifier(ResourceTypes eResource, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetResourceQuantityModifier(eResource);
		}
	}

	return rtnValue;
}

/// Extra yield from this improvement
int CvReligionBeliefs::GetImprovementYieldChange(ImprovementTypes eImprovement, YieldTypes eYield, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetImprovementYieldChange(eImprovement, eYield);
		}
	}

	return rtnValue;
}

/// Get yield change from beliefs for a specific building class
int CvReligionBeliefs::GetBuildingClassYieldChange(BuildingClassTypes eBuildingClass, YieldTypes eYieldType, int iFollowers, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(iFollowers >= pBeliefs->GetEntry(*it)->GetMinFollowers() && IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetBuildingClassYieldChange(eBuildingClass, eYieldType);
		}
	}

	return rtnValue;
}

/// Get Happiness from beliefs for a specific building class
int CvReligionBeliefs::GetBuildingClassHappiness(BuildingClassTypes eBuildingClass, int iFollowers, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if(iFollowers >= pBeliefs->GetEntry(*it)->GetMinFollowers())
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetBuildingClassHappiness(eBuildingClass);
			}
		}
	}

	return rtnValue;
}

/// Get Tourism from beliefs for a specific building class
int CvReligionBeliefs::GetBuildingClassTourism(BuildingClassTypes eBuildingClass, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetBuildingClassTourism(eBuildingClass);
		}
	}

	return rtnValue;
}

/// Get yield change from beliefs for a specific feature
int CvReligionBeliefs::GetFeatureYieldChange(FeatureTypes eFeature, YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetFeatureYieldChange(eFeature, eYieldType);
		}
	}

	return rtnValue;
}

#if defined(MOD_API_UNIFIED_YIELDS)
int CvReligionBeliefs::GetYieldPerXTerrainTimes100(TerrainTypes eTerrain, YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldPerXTerrainTimes100(eTerrain, eYieldType);
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetYieldPerXFeatureTimes100(FeatureTypes eFeature, YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldPerXFeatureTimes100(eFeature, eYieldType);
		}
	}

	return rtnValue;
}
int CvReligionBeliefs::GetCityYieldFromUnimprovedFeature(FeatureTypes eFeature, YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetCityYieldFromUnimprovedFeature(eFeature, eYieldType);
		}
	}

	return rtnValue;
}

int CvReligionBeliefs::GetUnimprovedFeatureYieldChange(FeatureTypes eFeature, YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetUnimprovedFeatureYieldChange(eFeature, eYieldType);
		}
	}

	return rtnValue;
}
#endif

/// Get yield change from beliefs for a specific resource
int CvReligionBeliefs::GetResourceYieldChange(ResourceTypes eResource, YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetResourceYieldChange(eResource, eYieldType);
		}
	}

	return rtnValue;
}

/// Get yield change from beliefs for a specific terrain
int CvReligionBeliefs::GetTerrainYieldChange(TerrainTypes eTerrain, YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetTerrainYieldChange(eTerrain, eYieldType);
		}
	}

	return rtnValue;
}

#if defined(MOD_API_UNIFIED_YIELDS)
int CvReligionBeliefs::GetTradeRouteYieldChange(DomainTypes eDomain, YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetTradeRouteYieldChange(eDomain, eYieldType);
		}
	}

	return rtnValue;
}

int CvReligionBeliefs::GetSpecialistYieldChange(SpecialistTypes eSpecialist, YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetSpecialistYieldChange(eSpecialist, eYieldType);
		}
	}

	return rtnValue;
}

int CvReligionBeliefs::GetGreatPersonExpendedYield(GreatPersonTypes eGreatPerson, YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetGreatPersonExpendedYield(eGreatPerson, eYieldType);
		}
	}

	return rtnValue;
}

int CvReligionBeliefs::GetGoldenAgeGreatPersonRateModifier(GreatPersonTypes eGreatPerson, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetGoldenAgeGreatPersonRateModifier(eGreatPerson);
		}
	}

	return rtnValue;
}

int CvReligionBeliefs::GetCapitalYieldChange(int iPopulation, YieldTypes eYield, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if(iPopulation >= pBeliefs->GetEntry(*it)->GetMinPopulation())
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetCapitalYieldChange(eYield);
			}
		}
	}

	return rtnValue;
}

int CvReligionBeliefs::GetCoastalCityYieldChange(int iPopulation, YieldTypes eYield, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if(iPopulation >= pBeliefs->GetEntry(*it)->GetMinPopulation())
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetCoastalCityYieldChange(eYield);
			}
		}
	}

	return rtnValue;
}

int CvReligionBeliefs::GetGreatWorkYieldChange(int iPopulation, YieldTypes eYield, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(iPopulation >= pBeliefs->GetEntry(*it)->GetMinPopulation())
		{
			if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetGreatWorkYieldChange(eYield);
			}
		}
	}

	return rtnValue;
}

/// Do we get one of our yields from defeating an enemy?
int CvReligionBeliefs::GetYieldFromKills(YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldFromKills(eYieldType);
		}
	}

	return rtnValue;
}

/// Do we get one of our yields from defeating a barbarian?
int CvReligionBeliefs::GetYieldFromBarbarianKills(YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldFromBarbarianKills(eYieldType);
		}
	}

	return rtnValue;
}
#endif

#if defined(MOD_RELIGION_PLOT_YIELDS)
/// Get yield change from beliefs for a specific plot
int CvReligionBeliefs::GetPlotYieldChange(PlotTypes ePlot, YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	if (MOD_RELIGION_PLOT_YIELDS) 
	{
		for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
		{
			if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetPlotYieldChange(ePlot, eYieldType);
			}
		}
	}

	return rtnValue;
}
#endif

// Get happiness boost from a resource
int CvReligionBeliefs::GetResourceHappiness(ResourceTypes eResource, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetResourceHappiness(eResource);
		}
	}

	return rtnValue;
}

/// Get yield change from beliefs for a specialist being present in city
int CvReligionBeliefs::GetYieldChangeAnySpecialist(YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldChangeAnySpecialist(eYieldType);
		}
	}

	return rtnValue;
}

/// Get yield change from beliefs for a trade route
int CvReligionBeliefs::GetYieldChangeTradeRoute(YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldChangeTradeRoute(eYieldType);
		}
	}

	return rtnValue;
}

/// Get yield change from beliefs for a natural wonder
int CvReligionBeliefs::GetYieldChangeNaturalWonder(YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldChangeNaturalWonder(eYieldType);
		}
	}

	return rtnValue;
}

/// Get yield change from beliefs for a world wonder
int CvReligionBeliefs::GetYieldChangeWorldWonder(YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldChangeWorldWonder(eYieldType);
		}
	}

	return rtnValue;
}

/// Get yield modifier from beliefs for a natural wonder
int CvReligionBeliefs::GetYieldModifierNaturalWonder(YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldModifierNaturalWonder(eYieldType);
		}
	}

	return rtnValue;
}

/// Get yield modifier from beliefs for a natural wonder
int CvReligionBeliefs::GetMaxYieldModifierPerFollower(YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetMaxYieldModifierPerFollower(eYieldType);
		}
	}

	return rtnValue;
}

/// Does this belief allow a building to be constructed?
bool CvReligionBeliefs::IsBuildingClassEnabled(BuildingClassTypes eType) const
{
	return m_paiBuildingClassEnabled[(int)eType];
}

/// Is there a belief that allows faith buying of units
bool CvReligionBeliefs::IsFaithBuyingEnabled(EraTypes eEra, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if (pBeliefs->GetEntry(*it)->IsFaithUnitPurchaseEra((int)eEra))
			{
				return true;
			}
		}
	}

	return false;
}
#if defined(MOD_BALANCE_CORE)
/// Is there a belief that allows faith buying of specific units?
bool CvReligionBeliefs::IsSpecificFaithBuyingEnabled(UnitTypes eUnit, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if (pBeliefs->GetEntry(*it)->IsFaithUnitPurchaseSpecific((int)eUnit))
			{
				return true;
			}
		}
	}

	return false;
}
#endif
/// Is there a belief that allows us to convert adjacent barbarians?
bool CvReligionBeliefs::IsConvertsBarbarians(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if (pBeliefs->GetEntry(*it)->ConvertsBarbarians())
			{
				return true;
			}
		}
	}

	return false;
}

/// Is there a belief that allows faith buying of all great people
bool CvReligionBeliefs::IsFaithPurchaseAllGreatPeople(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if (pBeliefs->GetEntry(*it)->FaithPurchaseAllGreatPeople())
			{
				return true;
			}
		}
	}

	return false;
}

#if defined(MOD_BALANCE_CORE_BELIEFS_RESOURCE)
/// Is there a belief that requires improvements?
bool CvReligionBeliefs::RequiresImprovement(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if (pBeliefs->GetEntry(*it)->RequiresImprovement())
			{
				return true;
			}
		}
	}
	return false;
}
/// Is there a belief that requires improvements?
bool CvReligionBeliefs::RequiresNoImprovement(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if (pBeliefs->GetEntry(*it)->RequiresNoImprovement())
			{
				return true;
			}
		}
	}

	return false;
}
/// Is there a belief that requires improvements?
bool CvReligionBeliefs::RequiresNoImprovementFeature(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if (pBeliefs->GetEntry(*it)->RequiresNoImprovementFeature())
			{
				return true;
			}
		}
	}

	return false;
}
/// Is there a belief that requires a resource?
bool CvReligionBeliefs::RequiresResource(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if (pBeliefs->GetEntry(*it)->RequiresResource())
			{
				return true;
			}
		}
	}

	return false;
}
#endif
#if defined(MOD_BALANCE_CORE_BELIEFS)
/// Is there a belief that halves follower values?
bool CvReligionBeliefs::IsHalvedFollowers(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if (pBeliefs->GetEntry(*it)->IsHalvedFollowers())
			{
				return true;
			}
		}
	}

	return false;
}
/// Get yield modifier from beliefs for pop
int CvReligionBeliefs::GetYieldPerPop(YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldPerPop(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs for gpt
int CvReligionBeliefs::GetYieldPerGPT(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldPerGPT(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs for luxury
int CvReligionBeliefs::GetYieldPerLux(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldPerLux(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs for border growth
int CvReligionBeliefs::GetYieldPerBorderGrowth(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldPerBorderGrowth(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs for border growth
int CvReligionBeliefs::GetYieldPerHeal(YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldPerHeal(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs from birth
int CvReligionBeliefs::GetYieldPerBirth(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		//Does double duty for pantheons and followers, so needs two checks
		if(pBeliefs->GetEntry(*it)->IsFollowerBelief())
		{
			if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetYieldPerBirth(eYieldType);
			}
		}
		else
		{
			//No city here, because it is universal.
			if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
			{
				rtnValue += pBeliefs->GetEntry(*it)->GetYieldPerBirth(eYieldType);
			}
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs from science
int CvReligionBeliefs::GetYieldPerScience(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldPerScience(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs from GP Use
int CvReligionBeliefs::GetYieldFromGPUse(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldFromGPUse(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs from GA bonus
int CvReligionBeliefs::GetYieldBonusGoldenAge(YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldBonusGoldenAge(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs from spread
int CvReligionBeliefs::GetYieldFromSpread(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldFromSpread(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs from foreign spread
int CvReligionBeliefs::GetYieldFromForeignSpread(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldFromForeignSpread(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs from conquest
int CvReligionBeliefs::GetYieldFromConquest(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldFromConquest(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs from policy unlock
int CvReligionBeliefs::GetYieldFromPolicyUnlock(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldFromPolicyUnlock(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs from era unlock
int CvReligionBeliefs::GetYieldFromEraUnlock(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldFromEraUnlock(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs from city conversion
int CvReligionBeliefs::GetYieldFromConversion(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldFromConversion(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs from wtlkd
int CvReligionBeliefs::GetYieldFromWLTKD(YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldFromWLTKD(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs from passing a WC proposal
int CvReligionBeliefs::GetYieldFromProposal(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldFromProposal(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs from Hosting WC
int CvReligionBeliefs::GetYieldFromHost(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldFromHost(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield modifier from beliefs from Hosting WC
int CvReligionBeliefs::GetYieldFromKnownPantheons(YieldTypes eYieldType, PlayerTypes ePlayer, CvCity* pCity) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer, pCity))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetYieldFromKnownPantheons(eYieldType);
		}
	}

	return rtnValue;
}

/// Get yield from beliefs from # of followers
int CvReligionBeliefs::GetMaxYieldPerFollower(YieldTypes eYieldType, PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	int rtnValue = 0;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			rtnValue += pBeliefs->GetEntry(*it)->GetMaxYieldPerFollower(eYieldType);
		}
	}

	return rtnValue;
}
/// Get yield from beliefs from # of followers
CivilizationTypes CvReligionBeliefs::GetUniqueCiv(PlayerTypes ePlayer) const
{
	CvBeliefXMLEntries* pBeliefs = GC.GetGameBeliefs();
	CivilizationTypes eCivilization = NO_CIVILIZATION;

	for(BeliefList::const_iterator it = m_ReligionBeliefs.begin(); it != m_ReligionBeliefs.end(); ++it)
	{
		if(IsBeliefValid((BeliefTypes)*it, GetReligion(), ePlayer))
		{
			if(pBeliefs->GetEntry(*it)->GetRequiredCivilization() != NO_CIVILIZATION)
			{
				return pBeliefs->GetEntry(*it)->GetRequiredCivilization();
			}
		}
	}

	return eCivilization;
}
#endif
/// Serialization read
void CvReligionBeliefs::Read(FDataStream& kStream)
{
	// Version number to maintain backwards compatibility
	uint uiVersion;
	kStream >> uiVersion;
	MOD_SERIALIZE_INIT_READ(kStream);
#if !defined(MOD_BALANCE_CORE)
	kStream >> m_iFaithFromDyingUnits;
	kStream >> m_iRiverHappiness;
	kStream >> m_iPlotCultureCostModifier;
	kStream >> m_iCityRangeStrikeModifier;
	kStream >> m_iCombatModifierEnemyCities;
	kStream >> m_iCombatModifierFriendlyCities;
	kStream >> m_iFriendlyHealChange;
	kStream >> m_iCityStateFriendshipModifier;
	kStream >> m_iLandBarbarianConversionPercent;
	kStream >> m_iSpreadStrengthModifier;
	kStream >> m_iSpreadDistanceModifier;
	kStream >> m_iProphetStrengthModifier;
	kStream >> m_iProphetCostModifier;
	kStream >> m_iMissionaryStrengthModifier;
	kStream >> m_iMissionaryCostModifier;
	kStream >> m_iFriendlyCityStateSpreadModifier;
	kStream >> m_iGreatPersonExpendedFaith;
	kStream >> m_iCityStateMinimumInfluence;
	kStream >> m_iCityStateInfluenceModifier;
	kStream >> m_iOtherReligionPressureErosion;
	kStream >> m_iSpyPressure;
	kStream >> m_iInquisitorPressureRetention;
#if defined(MOD_BALANCE_CORE_BELIEFS)
	MOD_SERIALIZE_READ(60, kStream, m_iCombatVersusOtherReligionOwnLands, 0);
	MOD_SERIALIZE_READ(60, kStream, m_iCombatVersusOtherReligionTheirLands, 0);
	MOD_SERIALIZE_READ(60, kStream, m_iMissionaryInfluenceCS, 0);
	MOD_SERIALIZE_READ(60, kStream, m_iHappinessPerPantheon, 0);
	MOD_SERIALIZE_READ(60, kStream, m_iExtraVotes, 0);
#endif
#if defined(MOD_BALANCE_CORE)
	kStream >> m_eRequiredCivilization;
#endif
	if (uiVersion >= 2)
	{
		kStream >> m_iFaithBuildingTourism;
	}
	else
	{
		m_iFaithBuildingTourism = 0;
	}

	kStream >> m_eObsoleteEra;
	kStream >> m_eResourceRevealed;
	kStream >> m_eSpreadModifierDoublingTech;
#endif
#if defined(MOD_BALANCE_CORE)
	kStream >> m_eReligion;
#endif

	m_ReligionBeliefs.clear();
#if defined(MOD_BALANCE_CORE)
	m_BeliefLookup = std::vector<int>(GC.GetGameBeliefs()->GetNumBeliefs(),0);
#endif
	uint uiBeliefCount;
	kStream >> uiBeliefCount;
	while(uiBeliefCount--)
	{
		int iBeliefIndex = CvInfosSerializationHelper::ReadHashed(kStream);
		m_ReligionBeliefs.push_back(iBeliefIndex);
#if defined(MOD_BALANCE_CORE)
		m_BeliefLookup[iBeliefIndex] = 1;
#endif
	}

	BuildingClassArrayHelpers::Read(kStream, m_paiBuildingClassEnabled);
}

/// Serialization write
void CvReligionBeliefs::Write(FDataStream& kStream) const
{
	// Current version number
	uint uiVersion = 2;
	kStream << uiVersion;
	MOD_SERIALIZE_INIT_WRITE(kStream);
#if !defined(MOD_BALANCE_CORE)
	kStream << m_iFaithFromDyingUnits;
	kStream << m_iRiverHappiness;
	kStream << m_iPlotCultureCostModifier;
	kStream << m_iCityRangeStrikeModifier;
	kStream << m_iCombatModifierEnemyCities;
	kStream << m_iCombatModifierFriendlyCities;
	kStream << m_iFriendlyHealChange;
	kStream << m_iCityStateFriendshipModifier;
	kStream << m_iLandBarbarianConversionPercent;
	kStream << m_iSpreadStrengthModifier;
	kStream << m_iSpreadDistanceModifier;
	kStream << m_iProphetStrengthModifier;
	kStream << m_iProphetCostModifier;
	kStream << m_iMissionaryStrengthModifier;
	kStream << m_iMissionaryCostModifier;
	kStream << m_iFriendlyCityStateSpreadModifier;
	kStream << m_iGreatPersonExpendedFaith;
	kStream << m_iCityStateMinimumInfluence;
	kStream << m_iCityStateInfluenceModifier;
	kStream << m_iOtherReligionPressureErosion;
	kStream << m_iSpyPressure;
	kStream << m_iInquisitorPressureRetention;
#if defined(MOD_BALANCE_CORE_BELIEFS)
	MOD_SERIALIZE_WRITE(kStream, m_iCombatVersusOtherReligionOwnLands);
	MOD_SERIALIZE_WRITE(kStream, m_iCombatVersusOtherReligionTheirLands);
	MOD_SERIALIZE_WRITE(kStream, m_iMissionaryInfluenceCS);
	MOD_SERIALIZE_WRITE(kStream, m_iHappinessPerPantheon);
	MOD_SERIALIZE_WRITE(kStream, m_iExtraVotes);
#endif
#if defined(MOD_BALANCE_CORE)
	kStream << m_eRequiredCivilization;
#endif
	kStream << m_iFaithBuildingTourism;

	kStream << m_eObsoleteEra;
	kStream << m_eResourceRevealed;
	kStream << m_eSpreadModifierDoublingTech;
#endif
#if defined(MOD_BALANCE_CORE)
	kStream << m_eReligion;
#endif

	// m_ReligionBeliefs contains the BeliefTypes, which are indices into the religion info table (GC.getBeliefInfo).  Write out the info hashes
	kStream << m_ReligionBeliefs.size();
	for (uint i = 0; i < m_ReligionBeliefs.size(); ++i)
	{
		CvInfosSerializationHelper::WriteHashed(kStream, (BeliefTypes)m_ReligionBeliefs[i]);
	}

	BuildingClassArrayHelpers::Write(kStream, m_paiBuildingClassEnabled, GC.getNumBuildingClassInfos());
}

/// BELIEF HELPER CLASSES

/// Is there an adjacent barbarian naval unit that could be converted?
#if defined(MOD_EVENTS_UNIT_CAPTURE)
bool CvBeliefHelpers::ConvertBarbarianUnit(const CvUnit *pByUnit, UnitHandle pUnit)
#else
bool CvBeliefHelpers::ConvertBarbarianUnit(CvPlayer *pPlayer, UnitHandle pUnit)
#endif
{
	UnitHandle pNewUnit;
	CvPlot *pPlot = pUnit->plot();

#if defined(MOD_EVENTS_UNIT_CAPTURE)
	CvPlayer* pPlayer = &GET_PLAYER(pByUnit->getOwner());

	if (MOD_EVENTS_UNIT_CAPTURE) {
		GAMEEVENTINVOKE_HOOK(GAMEEVENT_UnitCaptured, pPlayer->GetID(), pByUnit->GetID(), pUnit->getOwner(), pUnit->GetID(), false, 4);
	}
#endif

	// Convert the barbarian into our unit
	pNewUnit = pPlayer->initUnit(pUnit->getUnitType(), pUnit->getX(), pUnit->getY(), pUnit->AI_getUnitAIType(), NO_DIRECTION, true /*bNoMove*/, false);
	CvAssertMsg(pNewUnit, "pNewUnit is not assigned a valid value");
	pNewUnit->convert(pUnit.pointer(), false);
	pNewUnit->setupGraphical();
	pNewUnit->finishMoves(); // No move first turn

	if(GC.getLogging() && GC.getAILogging())
	{
		CvString logMsg;
		logMsg.Format("Converted barbarian (with belief), X: %d, Y: %d", pUnit->getX(), pUnit->getY());
		pPlayer->GetHomelandAI()->LogHomelandMessage(logMsg);
	}

	CvString strBuffer = GetLocalizedText("TXT_KEY_NOTIFICATION_HEATHEN_CONVERTS");
	CvString strSummary = GetLocalizedText("TXT_KEY_NOTIFICATION_SUMMARY_HEATHEN_CONVERTS");
	pPlayer->GetNotifications()->Add(NOTIFICATION_GENERIC, strBuffer, strSummary, pUnit->getX(), pUnit->getY(), -1);

	if (pPlot->getImprovementType() == GC.getBARBARIAN_CAMP_IMPROVEMENT())
	{
		pPlot->setImprovementType(NO_IMPROVEMENT);

		CvBarbarians::DoBarbCampCleared(pPlot, pPlayer->GetID());
		pPlot->SetPlayerThatClearedBarbCampHere(pPlayer->GetID());

		// Don't give gold for Camps cleared by heathen conversion
	}

	return true;
}